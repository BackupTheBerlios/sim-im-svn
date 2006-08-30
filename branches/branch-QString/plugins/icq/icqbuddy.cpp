/***************************************************************************
                          icqbuddy.cpp  -  description
                             -------------------
    begin                : Sun Mar 10 2002
    copyright            : (C) 2002 by Vladimir Shutoff
    email                : vovan@shutoff.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "icqclient.h"

#include <time.h>
#include <stdio.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#endif

using namespace std;
using namespace SIM;

const unsigned short ICQ_SNACxBDY_REQUESTxRIGHTS   = 0x0002;
const unsigned short ICQ_SNACxBDY_RIGHTSxGRANTED   = 0x0003;
const unsigned short ICQ_SNACxBDY_ADDxTOxLIST      = 0x0004;
const unsigned short ICQ_SNACxBDY_REMOVExFROMxLIST = 0x0005;
const unsigned short ICQ_SNACxBDY_USERONLINE	   = 0x000B;
const unsigned short ICQ_SNACxBDY_USEROFFLINE	   = 0x000C;

const unsigned short TLV_USER_CLASS         = 0x0001;
const unsigned short TLV_USER_SIGNON_TIME   = 0x0003;
const unsigned short TLV_USER_MEMBER_SINCE  = 0x0005; // not interpreted
const unsigned short TLV_USER_STATUS        = 0x0006;
const unsigned short TLV_USER_EXT_IP        = 0x000A;
const unsigned short TLV_USER_DC_INFO       = 0x000C;
const unsigned short TLV_USER_CAPS          = 0x000D;
const unsigned short TLV_USER_ONLINE_TIME   = 0x000F; // not interpreted
const unsigned short TLV_USER_TIMES_UPDATED = 0x0011; // ????
const unsigned short TLV_USER_NEWCAPS       = 0x0019;
const unsigned short TLV_USER_BUDDYINFO     = 0x001D;

static QString makeCapStr( const capability cap, unsigned size )
{
    QString str = "", tmp;
    for(unsigned int i = 0; i < size; i++ ) {
        str += tmp.sprintf( "0x%02x ", cap[i] );
    }
    return str;
}

void ICQClient::snac_buddy(unsigned short type, unsigned short)
{
    QString screen;
    Contact *contact;
    ICQUserData *data;
    switch (type){
    case ICQ_SNACxBDY_RIGHTSxGRANTED:
        log(L_DEBUG, "Buddy rights granted");
        break;
    case ICQ_SNACxBDY_USEROFFLINE:
        screen = m_socket->readBuffer.unpackScreen();
        data = findContact(screen, NULL, false, contact);
        if (data && (data->Status.toULong() != ICQ_STATUS_OFFLINE)){
            setOffline(data);
            StatusMessage m;
            m.setContact(contact->id());
            m.setClient(dataName(data));
            m.setStatus(STATUS_OFFLINE);
            m.setFlags(MESSAGE_RECEIVED);
            Event e(EventMessageReceived, &m);
            e.process();
        }
        break;
    case ICQ_SNACxBDY_USERONLINE:
        screen = m_socket->readBuffer.unpackScreen();
        data = findContact(screen, NULL, false, contact);
        if (data){
            bool bChanged     = false;
            bool bAwayChanged = false;
            unsigned long prevStatus = data->Status.toULong();

            unsigned short level, len;
            m_socket->readBuffer >> level >> len;
            data->WarningLevel.asULong() = level;

            TlvList tlv(m_socket->readBuffer);

            Tlv *tlvClass = tlv(TLV_USER_CLASS);
            if (tlvClass){
                unsigned short userClass = *tlvClass;
                if (userClass != data->Class.toULong()){
                    if ((userClass & CLASS_AWAY) != (data->Class.toULong() & CLASS_AWAY)){
                        data->StatusTime.asULong() = (unsigned long)time(NULL);
                        bAwayChanged = true;
                    }
                    data->Class.asULong() = userClass;
                    bChanged = true;
                }
                if (data->Uin.toULong() == 0){
                    if (userClass & CLASS_AWAY){
                        fetchAwayMessage(data);
                    }else{
                        data->AutoReply.str() = QString::null;
                    }
                }
            }

            // Status TLV
            Tlv *tlvStatus = tlv(TLV_USER_STATUS);
            if (tlvStatus){
                unsigned long status = *tlvStatus;
                if (status != data->Status.toULong()){
                    data->Status.asULong() = status;
                    if ((status & 0xFF) == 0)
                        data->AutoReply.str() = QString::null;
                    data->StatusTime.asULong() = (unsigned long)time(NULL);
                }
            }else if (data->Status.toULong() == ICQ_STATUS_OFFLINE){
                data->Status.asULong() = ICQ_STATUS_ONLINE;
                data->StatusTime.asULong() = (unsigned long)time(NULL);
            }

            // Online time TLV
            Tlv *tlvOnlineTime = tlv(TLV_USER_SIGNON_TIME);
            if (tlvOnlineTime){
                unsigned long OnlineTime = *tlvOnlineTime;
                if (OnlineTime != data->OnlineTime.toULong()){
                    data->OnlineTime.asULong() = OnlineTime;
                    bChanged = true;
                }
            }
            Tlv *tlvNATime = tlv(0x0004);
            if (tlvNATime){
                unsigned short na_time = *tlvNATime;
                unsigned long StatusTime = (unsigned long)time(NULL) - na_time * 60;
                if (StatusTime != data->StatusTime.toULong()){
                    data->StatusTime.asULong() = StatusTime;
                    bChanged = true;
                }
            }

            // IP TLV
            Tlv *tlvIP = tlv(TLV_USER_EXT_IP);
            if (tlvIP)
                bChanged |= set_ip(&data->IP, htonl((unsigned long)(*tlvIP)));

            // short caps tlv
            Tlv *tlvCapShort = tlv(TLV_USER_NEWCAPS);
            if(tlvCapShort) {
                data->Caps.asULong() = 0;
                data->Caps2.asULong() = 0;

                Buffer info(*tlvCapShort);

                for (; info.readPos() < info.size(); ){
                    unsigned char shortcap[2];
                    info.unpack((char*)shortcap, sizeof(shortcap));
                    for (unsigned i = 0;; i++) {
                        if(!memcmp(&capabilities[i][2], shortcap, sizeof(shortcap))) {
                            setCap(data, (cap_id_t)i);
                            break;
                        }
                        // we don't go through all caps, only the first ones starting with 0x09
                        if (*capabilities[i] != '\x09') {
                            log( L_DEBUG, "%lu unknown cap %s", data->Uin.toULong(),
                                          makeCapStr( shortcap, sizeof(shortcap) ).latin1() );
                            break;
                        }
                    }
                }
            }
            // normal cap tlv
            Tlv *tlvCapability = tlv(TLV_USER_CAPS);
            if (tlvCapability) {
                if (!tlvCapShort) {
                    data->Caps.asULong() = 0;
                    data->Caps2.asULong() = 0;
                }
                Buffer info(*tlvCapability);
                for (; info.readPos() < info.size(); ){
                    capability cap;
                    info.unpack((char*)cap, sizeof(capability));
                    for (unsigned i = 0;; i++){
                        unsigned size = sizeof(capability);
                        if (i == CAP_SIMOLD)
                            size--;

                        if (*capabilities[i] == 0) {
                            log( L_DEBUG, "%lu unknown cap %s", data->Uin.toULong(), makeCapStr( cap, size ).latin1() );
                            break;
                        }
                        if ((i == CAP_MICQ) || (i == CAP_LICQ) || (i == CAP_SIM) || (i == CAP_KOPETE))
                            size -= 4;
                        if ((i == CAP_ANDRQ))
                            size -= 7;
                        if ((i == CAP_MIRANDA))
                            size -= 8;
                        if ((i == CAP_JIMM))
                            size -= 11;
                        if (!memcmp(cap, capabilities[i], size)){
                            if (i == CAP_SIMOLD){
                                unsigned char build = cap[sizeof(capability)-1];
                                if (build && ((build == 0x92) || (build < (1 << 6)))) continue;
                                data->Build.asULong() = build;
                            }
                            if ((i == CAP_MICQ) || (i == CAP_LICQ) || (i == CAP_SIM) || (i == CAP_KOPETE)){
                                unsigned char *p = (unsigned char*)cap;
                                p += 12;
                                data->Build.asULong() = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
                            }
                            if ((i == CAP_ANDRQ)) {
                                unsigned char *p = (unsigned char*)cap;
                                p += 9;
                                data->Build.asULong() = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
                            }
                            if ((i == CAP_MIRANDA)) {
                                unsigned char *p = (unsigned char*)cap;
                                p += 8;
                                data->Build.asULong() = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
                            }
                            if ((i == CAP_JIMM)) {
                                char *p = (char*)cap;
                                p += 5;
                                QString str = QString::fromAscii(p, 10);
                                QStringList sl = QStringList::split('.', str);
                                unsigned char maj = 0, min = 0;
                                unsigned short rev = 0;
                                if(sl.count() > 0)
                                    maj = sl[0].toUShort();
                                if(sl.count() > 1)
                                    min = sl[1].toUShort();
                                if(sl.count() > 2)
                                    rev = sl[2].toUShort();

                                data->Build.asULong() = (maj << 24) + (min << 16) + rev;
                            }
                            setCap(data, (cap_id_t)i);
                            break;
                        }
                    }
                }
            }
            // buddy info
            Tlv *tlvBuddy = tlv(TLV_USER_BUDDYINFO);
            if (tlvBuddy) {
                const QByteArray &ba = data->buddyHash.toBinary();
                unsigned short iconID;
                unsigned char iconFlags, hashSize;
                Buffer info(*tlvBuddy);
                QByteArray hash(16);
                QString fname = ICQClient::avatarFile(data);
                QFileInfo fi(fname);

                info >> iconID >> iconFlags >> hashSize;
                hash.resize(hashSize);
                info.unpack(hash.data(), hashSize);
                if( data->buddyID.toULong() != iconID ||
                    ba.data() != hash.data() ||
                   !fi.exists() || fi.size() == 0) {
                    data->buddyID.asULong() = iconID;
                    data->buddyHash.asBinary() = hash;
                    requestBuddy(data);
                }
           }

            unsigned long infoUpdateTime = 0;
            unsigned long pluginInfoTime = 0;
            unsigned long pluginStatusTime = 0;

            // Direct connection info
            Tlv *tlvDirect = tlv(TLV_USER_DC_INFO);
            if (tlvDirect){
                Buffer info(*tlvDirect);
                unsigned long  realIP;
                unsigned short port;
                char mode, version, junk;
                info >> realIP;
                info.incReadPos(2);
                info >> port;
                if (realIP == 0x7F000001)
                    realIP = 0;
                bChanged |= set_ip(&data->RealIP, htonl(realIP));
                data->Port.asULong() = port;
                unsigned long DCcookie;
                info >> mode >> junk >> version >> DCcookie;
                data->DCcookie.asULong() = DCcookie;
                info.incReadPos(8);
                info
                >> infoUpdateTime
                >> pluginInfoTime
                >> pluginStatusTime;
                if (mode == MODE_DENIED) mode = MODE_INDIRECT;
                if ((mode != MODE_DIRECT) && (mode != MODE_INDIRECT))
                    mode = MODE_INDIRECT;
                data->Mode.asULong()    = mode;
                data->Version.asULong() = version;
            }

            Tlv *tlvPlugin = tlv(0x0011);
            if (tlvPlugin && data->Uin.toULong()){
                Buffer info(*tlvPlugin);
                char type;
                unsigned long time;
                info >> type;
                info.unpack(time);
                plugin p;
                unsigned plugin_index;
                unsigned long plugin_status;
                switch (type){
                case 1:
                    addFullInfoRequest(data->Uin.toULong());
                    break;
                case 2:
                    if		((getInvisible() && data->VisibleId.toULong()) ||
                            (!getInvisible() && (data->InvisibleId.toULong() == 0))){
                        info.incReadPos(6);
                        info.unpack((char*)p, sizeof(p));
                        data->PluginInfoTime.asULong() = time;
                        for (plugin_index = 0; plugin_index < PLUGIN_NULL; plugin_index++)
                            if (!memcmp(p, plugins[plugin_index], sizeof(p)))
                                break;
                        switch (plugin_index){
                        case PLUGIN_PHONEBOOK:
                            log(L_DEBUG, "Updated phonebook");
                            addPluginInfoRequest(data->Uin.toULong(), plugin_index);
                            break;
                        case PLUGIN_PICTURE:
                            log(L_DEBUG, "Updated picture");
                            addPluginInfoRequest(data->Uin.toULong(), plugin_index);
                            break;
                        case PLUGIN_QUERYxINFO:
                            log(L_DEBUG, "Updated info plugin list");
                            addPluginInfoRequest(data->Uin.toULong(), plugin_index);
                            break;
                        default:
                            if (plugin_index >= PLUGIN_NULL)
                                log(L_WARN, "Unknown plugin sign (%04X %04X)",
                                    type, plugin_index);
                        }
                    }
                    break;
                case 3:
                    info.incReadPos(6);
                    info.unpack((char*)p, sizeof(p));
                    info.incReadPos(1);
                    info.unpack(plugin_status);
                    data->PluginStatusTime.asULong() = time;
                    for (plugin_index = 0; plugin_index < PLUGIN_NULL; plugin_index++)
                        if (!memcmp(p, plugins[plugin_index], sizeof(p)))
                            break;
                    switch (plugin_index){
                    case PLUGIN_FOLLOWME:
                        if (data->FollowMe.toULong() == plugin_status)
                            break;
                        data->FollowMe.asULong() = plugin_status;
                        bChanged = true;
                        break;
                    case PLUGIN_FILESERVER:
                        if ((data->SharedFiles.toBool() != 0) == (plugin_status != 0))
                            break;
                        data->SharedFiles.asBool() = (plugin_status != 0);
                        bChanged = true;
                        break;
                    case PLUGIN_ICQPHONE:
                        if (data->ICQPhone.toULong() == plugin_status)
                            break;
                        data->ICQPhone.asULong() = plugin_status;
                        bChanged = true;
                        break;
                    default:
                        if (plugin_index >= PLUGIN_NULL)
                            log(L_WARN, "Unknown plugin sign (%04X %04X)",
                                type, plugin_index);
                    }
                    break;

                }
            }else{
                data->InfoUpdateTime.asULong()   = infoUpdateTime;
                data->PluginInfoTime.asULong()   = pluginInfoTime;
                data->PluginStatusTime.asULong() = pluginStatusTime;
                if (!getDisableAutoUpdate() &&
                        ((getInvisible() && data->VisibleId.toULong()) ||
                         (!getInvisible() && (data->InvisibleId.toULong() == 0)))){
                    if (infoUpdateTime == 0)
                        infoUpdateTime = 1;
                    if (infoUpdateTime != data->InfoFetchTime.toULong())
                        addFullInfoRequest(data->Uin.toULong());
                    if ((data->PluginInfoTime.toULong() != data->PluginInfoFetchTime.toULong())){
                        if (data->PluginInfoTime.toULong())
                            addPluginInfoRequest(data->Uin.toULong(), PLUGIN_QUERYxINFO);
                    }
                    if ((data->PluginInfoTime.toULong() != data->PluginInfoFetchTime.toULong()) ||
                            (data->PluginStatusTime.toULong() != data->PluginStatusFetchTime.toULong())){
                        if (data->SharedFiles.toBool()){
                            data->SharedFiles.asBool() = false;
                            bChanged = true;
                        }
                        if (data->FollowMe.toULong()){
                            data->FollowMe.asULong() = 0;
                            bChanged = true;
                        }
                        if (data->ICQPhone.toULong()){
                            data->ICQPhone.asULong() = 0;
                            bChanged = true;
                        }
                        if (data->PluginStatusTime.toULong())
                            addPluginInfoRequest(data->Uin.toULong(), PLUGIN_QUERYxSTATUS);
                    }
                }
            }
            if (data->bInvisible.toBool()){
                data->bInvisible.asBool() = false;
                bChanged = true;
            }
            if (bChanged){
                Event e(EventContactChanged, contact);
                e.process();
            }
            if ((data->Status.toULong() != prevStatus) || bAwayChanged){
                unsigned status = STATUS_OFFLINE;
                if ((data->Status.toULong() & 0xFFFF) != ICQ_STATUS_OFFLINE){
                    status = STATUS_ONLINE;
                    if (data->Status.toULong() & ICQ_STATUS_DND){
                        status = STATUS_DND;
                    }else if (data->Status.toULong() & ICQ_STATUS_OCCUPIED){
                        status = STATUS_OCCUPIED;
                    }else if (data->Status.toULong() & ICQ_STATUS_NA){
                        status = STATUS_NA;
                    }else if (data->Status.toULong() & ICQ_STATUS_AWAY){
                        status = STATUS_AWAY;
                    }else if (data->Status.toULong() & ICQ_STATUS_FFC){
                        status = STATUS_FFC;
                    }
                }
                if ((status == STATUS_ONLINE) && (data->Class.toULong() & CLASS_AWAY))
                    status = STATUS_AWAY;
                StatusMessage m;
                m.setContact(contact->id());
                m.setClient(dataName(data));
                m.setStatus(status);
                m.setFlags(MESSAGE_RECEIVED);
                Event e(EventMessageReceived, &m);
                e.process();
                if (!contact->getIgnore() &&
                        ((data->Class.toULong() & CLASS_AWAY) == 0) &&
                        (((data->Status.toULong() & 0xFF) == ICQ_STATUS_ONLINE) &&
                         (((prevStatus & 0xFF) != ICQ_STATUS_ONLINE)) || bAwayChanged) &&
                        (((prevStatus & 0xFFFF) != ICQ_STATUS_OFFLINE) ||
                         (data->OnlineTime.toULong() > this->data.owner.OnlineTime.toULong()))){
                    Event e(EventContactOnline, contact);
                    e.process();
                }
                if (!getDisableAutoReplyUpdate() && ((data->Status.toULong() & 0xFF) != ICQ_STATUS_ONLINE)){
                    if ((getInvisible() && data->VisibleId.toULong()) ||
                            (!getInvisible() && (data->InvisibleId.toULong() == 0)))
                        addPluginInfoRequest(data->Uin.toULong(), PLUGIN_AR);
                }
            }
        }
        break;
    default:
        log(L_WARN, "Unknown buddy family type %04X", type);
    }
}

void ICQClient::buddyRequest()
{
    snac(ICQ_SNACxFAM_BUDDY, ICQ_SNACxBDY_REQUESTxRIGHTS);
    sendPacket(true);
}

void ICQClient::sendContactList()
{
    buddies.clear();
    Contact *contact;
    ContactList::ContactIterator it;
    while ((contact = ++it) != NULL){
        ClientDataIterator it_data(contact->clientData, this);
        ICQUserData *data;
        while ((data = (ICQUserData*)(++it_data)) != NULL){
            if (data->IgnoreId.toULong() == 0)
                buddies.push_back(screen(data));
        }
    }
    if (buddies.empty()) return;
    snac(ICQ_SNACxFAM_BUDDY, ICQ_SNACxBDY_ADDxTOxLIST);
    it.reset();
    while ((contact = ++it) != NULL){
        ClientDataIterator it_data(contact->clientData, this);
        ICQUserData *data;
        while ((data = (ICQUserData*)(++it_data)) != NULL){
            if (data->IgnoreId.toULong() == 0)
                m_socket->writeBuffer.packScreen(screen(data));
        }
    }
    sendPacket(true);
}

void ICQClient::addBuddy(Contact *contact)
{
    if (getState() != Connected)
        return;
    if (contact->id() == 0)
        return;
    ICQUserData *data;
    ClientDataIterator it_data(contact->clientData, this);
    while ((data = (ICQUserData*)(++it_data)) != NULL){
        QStringList::iterator it = buddies.find(screen(data));
        if (it != buddies.end())
            continue;
        if ((data->IgnoreId.toULong() == 0)  && (data->WaitAuth.toBool() || (data->GrpId.toULong() == 0))){
            snac(ICQ_SNACxFAM_BUDDY, ICQ_SNACxBDY_ADDxTOxLIST);
            m_socket->writeBuffer.packScreen(screen(data));
            sendPacket(true);
            buddies.push_back(screen(data));
        }
    }
}

void ICQClient::removeBuddy(Contact *contact)
{
    if (getState() != Connected)
        return;
    if (contact->id() == 0)
        return;
    ICQUserData *data;
    ClientDataIterator it_data(contact->clientData, this);
    while ((data = (ICQUserData*)(++it_data)) != NULL){
        QStringList::iterator it = buddies.find(screen(data));
        if (it == buddies.end())
            continue;
        snac(ICQ_SNACxFAM_BUDDY, ICQ_SNACxBDY_REMOVExFROMxLIST);
        m_socket->writeBuffer.packScreen(screen(data));
        sendPacket(true);
        buddies.erase(it);
    }
}

