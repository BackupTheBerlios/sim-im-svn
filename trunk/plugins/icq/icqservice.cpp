/***************************************************************************
                          icqservice.cpp  -  description
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
#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <qtimer.h>
#include <qbuffer.h>
#include <qimage.h>

using namespace std;
using namespace SIM;

const unsigned short ICQ_SNACxSRV_ERROR         = 0x0001;
const unsigned short ICQ_SNACxSRV_READYxCLIENT  = 0x0002;
const unsigned short ICQ_SNACxSRV_READYxSERVER	= 0x0003;
const unsigned short ICQ_SNACxSRV_SERVICExREQ	= 0x0004;
const unsigned short ICQ_SNACxSRV_SERVICExRESP	= 0x0005;
const unsigned short ICQ_SNACxSRV_REQxRATExINFO = 0x0006;
const unsigned short ICQ_SNACxSRV_RATExINFO     = 0x0007;
const unsigned short ICQ_SNACxSRV_RATExACK      = 0x0008;
const unsigned short ICQ_SNACxSRV_RATExDEL      = 0x0009;   /* Not implemented */
const unsigned short ICQ_SNACxSRV_RATExCHANGE   = 0x000A;
const unsigned short ICQ_SNACxSRV_PAUSE         = 0x000B;
const unsigned short ICQ_SNACxSRV_PAUSExACK     = 0x000C;
const unsigned short ICQ_SNACxSRV_RESUME        = 0x000D;
const unsigned short ICQ_SNACxSRV_GETxUSERxINFO = 0x000E;
const unsigned short ICQ_SNACxSRV_NAMExINFO     = 0x000F;
const unsigned short ICQ_SNACxSRV_EVIL          = 0x0010;
const unsigned short ICQ_SNACxSRV_SETxIDLE      = 0x0011;
const unsigned short ICQ_SNACxSRV_MIGRATE       = 0x0012;
const unsigned short ICQ_SNACxSRV_MOTD          = 0x0013;
const unsigned short ICQ_SNACxSRV_PRIVATY_FLAGS = 0x0014;   /* Not implemented */
const unsigned short ICQ_SNACxSRV_IMxICQ        = 0x0017;
const unsigned short ICQ_SNACxSRV_ACKxIMxICQ    = 0x0018;
const unsigned short ICQ_SNACxSRV_SETxSTATUS    = 0x001E;
const unsigned short ICQ_SNACxSRV_EXT_STATUS    = 0x0021;

void ICQClient::snac_service(unsigned short type, unsigned short)
{
    switch (type){
    case ICQ_SNACxSRV_PAUSE:
        log(L_DEBUG, "Server pause");
        m_bNoSend = true;
        snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_PAUSExACK);
        m_socket->writeBuffer << ICQ_SNACxFAM_SERVICE
        << ICQ_SNACxFAM_LOCATION
        << ICQ_SNACxFAM_BUDDY
        << ICQ_SNACxFAM_MESSAGE
        << ICQ_SNACxFAM_BOS
        << ICQ_SNACxFAM_PING
        << ICQ_SNACxFAM_LISTS
        << ICQ_SNACxFAM_VARIOUS
        << ICQ_SNACxFAM_LOGIN;
        sendPacket(true);
        break;
    case ICQ_SNACxSRV_RESUME:
        log(L_DEBUG, "Server resume");
        m_bNoSend = false;
        processSendQueue();
        break;
    case ICQ_SNACxSRV_MIGRATE:{
            log(L_DEBUG, "Server migrate");
            m_bNoSend = true;
            int i;
            unsigned short cnt;
            unsigned short fam[0x17];

            m_socket->readBuffer >> cnt;
            for (i = 0; i < cnt; i++) {
                m_socket->readBuffer >> fam[i];
            }
            TlvList tlv(m_socket->readBuffer);
            Tlv *tlv_adr    = tlv(0x05);
            Tlv *tlv_cookie = tlv(0x06);
            for (; i >= 0; i--) {
                setServiceSocket(tlv_adr,tlv_cookie,fam[i]);
            }
            break;
        }
    case ICQ_SNACxSRV_RATExCHANGE:{
            const char *msg_text = NULL;
            unsigned short msg_code;
            unsigned short class_id;
            unsigned long  window_size;
            unsigned long  clear_level;
            unsigned long  alert_level;
            unsigned long  limit_level;
            unsigned long  discon_level;
            unsigned long  current_level;
            unsigned long  max_level;
            unsigned long  last_send;
            char current_state;
            m_socket->readBuffer >> msg_code
            >> class_id
            >> window_size
            >> clear_level
            >> alert_level
            >> limit_level
            >> discon_level
            >> current_level
            >> max_level
            >> last_send
            >> current_state;
            if (type == ICQ_SNACxSRV_RATExCHANGE){
                switch (msg_code) {
                case 0x0001:
                    msg_text = "Rate limits parameters changed";
                    break;
                case 0x0002:
                    msg_text = "Rate limits warning";
                    break;
                case 0x0003:
                    msg_text = "Rate limit hit";
                    break;
                case 0x0004:
                    msg_text = "Rate limit clear";
                    break;
                default:
                    msg_text = "Unknown";
                }
                log(L_DEBUG, "%s", msg_text);
            }
            log(L_DEBUG, "grp: %02X, ws: %04lX, cl %04lX, al %04lX, ll %04lX, dl: %04lX, cur %04lX, ml %04lX",
                class_id,window_size,clear_level,alert_level,limit_level,discon_level,
                current_level,max_level);
            if (--class_id < m_rates.size()){
                RateInfo &r = m_rates[class_id];
                r.m_winSize  = window_size;
                r.m_maxLevel = max_level;
                r.m_minLevel = alert_level;
                r.m_curLevel = current_level;
                r.m_lastSend = QDateTime::currentDateTime();
                processSendQueue();
            }
            break;
        }
    case ICQ_SNACxSRV_RATExINFO: {
            bool bNew =  m_rates.size() == 0;
            m_rates.clear();
            unsigned short n_rates;
            m_socket->readBuffer >> n_rates;
            unsigned n;
            for (n = 0; n < n_rates; n++){
                unsigned short class_id;
                unsigned long  window_size;
                unsigned long  clear_level;
                unsigned long  alert_level;
                unsigned long  limit_level;
                unsigned long  discon_level;
                unsigned long  current_level;
                unsigned long  max_level;
                unsigned long  last_send;
                char current_state;
                m_socket->readBuffer
                >> class_id
                >> window_size
                >> clear_level
                >> alert_level
                >> limit_level
                >> discon_level
                >> current_level
                >> max_level
                >> last_send
                >> current_state;
                log(L_DEBUG, "grp: %02X, ws: %04lX, cl %04lX, al %04lX, ll %04lX, dl: %04lX, cur %04lX, ml %04lX, cs: %d",
                    class_id,window_size,clear_level,alert_level,limit_level,discon_level,
                    current_level,max_level, current_state);
                RateInfo r;
                r.m_winSize		= window_size;
                r.m_minLevel	= alert_level;
                r.m_maxLevel	= max_level;
                r.m_curLevel	= current_level;
                r.m_lastSend	= QDateTime::currentDateTime();
                m_rates.push_back(r);
            }
            for (n = 0; n < n_rates; n++){
                unsigned short class_id;
                unsigned short pairs;
                m_socket->readBuffer
                >> class_id
                >> pairs;
                class_id--;
                for (unsigned i = 0; i < pairs; i++){
                    unsigned long snac;
                    m_socket->readBuffer >> snac;
                    if (class_id >= m_rates.size())
                        continue;
                    RATE_MAP::iterator it = m_rate_grp.find(snac);
                    if (it != m_rate_grp.end())
                        continue;
                    m_rate_grp.insert(RATE_MAP::value_type(snac, class_id));
                }
            }
            snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_RATExACK);
            m_socket->writeBuffer << 0x00010002L << 0x00030004L << 0x0005;
            sendPacket(true);
            if(!bNew)
                break;
            snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_GETxUSERxINFO);
            sendPacket(true);
            listsRequest();
            locationRequest();
            buddyRequest();
            icmbRequest();
            bosRequest();
        }
        break;
    case ICQ_SNACxSRV_MOTD:
        break;
    case ICQ_SNACxSRV_ACKxIMxICQ:
        requestRateInfo();
        break;
    case ICQ_SNACxSRV_EXT_STATUS: {
            QByteArray shash(16);
            unsigned short nType;
            char flags, size;

            m_socket->readBuffer >> nType;
            if(nType == 0)  // SSBI ready
                break;
            if(nType == 2)  // iChat message
                break;

            m_socket->readBuffer >> flags >> size;
            shash.resize(size);
            m_socket->readBuffer.unpack(shash.data(), shash.size());

            QImage img(getPicture());
            if(img.isNull())
                break;

            QByteArray ba;
            QBuffer buf(ba);
            if(!buf.open(IO_WriteOnly)) {
                log(L_ERROR, "Can't open QByteArray for writing!");
                break;
            }
            if(!img.save(&buf, "JPEG")) {
                log(L_ERROR, "Can't save QImage to QBuffer");
                break;
            }
            buf.close();
            QByteArray hash = md5(ba.data(), ba.size());

            if(hash != shash) {
                log(L_WARN, "The buddyIcon on server does not match the local one - updating");
                uploadBuddy(&data.owner);
                break;
            }
            uploadBuddyIcon(1, img);
        }
        break;
    case ICQ_SNACxSRV_NAMExINFO:{
            QString screen = m_socket->readBuffer.unpackScreen();
            if (screen.length() == 0){
                char n;
                m_socket->readBuffer >> n;
                m_socket->readBuffer.incReadPos(n);
                screen = m_socket->readBuffer.unpackScreen();
            }
            if (screen.toULong() != data.owner.Uin.toULong()){
                log(L_WARN, "Not my name info (%s)", screen.latin1());
                break;
            }
            m_socket->readBuffer.incReadPos(4);
            TlvList tlv(m_socket->readBuffer);
            Tlv *tlvIP = tlv(0x000A);
            if (tlvIP)
                set_ip(&data.owner.IP, htonl((uint32_t)(*tlvIP)));
            break;
        }
    case ICQ_SNACxSRV_SERVICExRESP:{
            TlvList tlv(m_socket->readBuffer);
            Tlv *tlv_id = tlv(0x0D);
            if (!tlv_id){
                log(L_WARN, "No service id in response");
                break;
            }
            Tlv *tlv_adr    = tlv(0x05);
            Tlv *tlv_cookie = tlv(0x06);
            setServiceSocket(tlv_adr,tlv_cookie,(uint16_t)(*tlv_id));
            break;
        }
    case ICQ_SNACxSRV_READYxSERVER:
        snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_IMxICQ);
        if (m_bAIM){
            m_socket->writeBuffer
            << 0x00010003L
            << 0x00130003L
            << 0x00020001L
            << 0x00030001L
            << 0x00040001L
            << 0x00060001L
            << 0x00080001L
            << 0x00090001L
            << 0x000A0001L
            << 0x000B0001L;
        }else{
            m_socket->writeBuffer
            << 0x00010004L
            << 0x00130004L
            << 0x00020001L
            << 0x00030001L
            << 0x00150001L
            << 0x00040001L
            << 0x00060001L
            << 0x00090001L
            << 0x000A0001L
            << 0x000B0001L;
        }
        sendPacket(true);
        break;
    case ICQ_SNACxSRV_ERROR:
        break;
    case ICQ_SNACxSRV_EVIL:{
            unsigned short level;
            m_socket->readBuffer.unpack(level);
            QString from = m_socket->readBuffer.unpackScreen();
            data.owner.WarningLevel.asULong() = level;
            if (from.isEmpty())
                from = i18n("anonymous");
            EventError::ClientErrorData d;
            d.client  = this;
            d.code    = 0;
            d.err_str = I18N_NOOP("You've been warned by %1");
            d.args    = from;
            d.flags   = EventError::ClientErrorData::E_INFO;
            d.options = NULL;
            d.id      = CmdShowWarning;
            EventClientError e(d);
            e.process();
            break;
        }
    default:
        log(L_WARN, "Unknown service family type %04X", type);
    }
}

void ICQClient::requestRateInfo()
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_REQxRATExINFO);
    sendPacket(true);
}

void ICQClient::setServiceSocket(Tlv *tlv_addr, Tlv *tlv_cookie, unsigned short service)
{
    ServiceSocket *s = NULL;
    for (list<ServiceSocket*>::iterator it = m_services.begin(); it != m_services.end(); ++it){
        if ((*it)->id() == service){
            s = *it;
            break;
        }
    }
    if (!s){
        log(L_WARN, "Service not found");
        return;
    }
    if (!tlv_addr){
        s->error_state("No address for service", 0);
        return;
    }
    if (!tlv_cookie){
        s->error_state("No cookie for service", 0);
        return;
    }
    unsigned short port = getPort();
    QCString addr(tlv_addr->byteArray());
    int idx = addr.find(':');
    if(idx != -1) {
        port = addr.mid(idx + 1).toUShort();
        addr = addr.left(idx);
    }
    if (s->connected())
        s->close();
    QByteArray ba = tlv_cookie->byteArray();
    ba.resize(ba.size()-1);
    s->connect(addr, port, ba);
}
void ICQClient::sendClientReady()
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_READYxCLIENT);
    m_socket->writeBuffer
    << 0x00010004L << 0x011008E4L
    << 0x00130004L << 0x011008E4L
    << 0x00020001L << 0x011008E4L
    << 0x00030001L << 0x011008E4L
    << 0x00150001L << 0x011008E4L
    << 0x00040001L << 0x011008E4L
    << 0x00060001L << 0x011008E4L
    << 0x00090001L << 0x011008E4L
    << 0x000A0001L << 0x011008E4L
    << 0x000B0001L << 0x011008E4L;

    sendPacket(true);
}

void ICQClient::sendLogonStatus()
{
    if (getInvisible())
        sendInvisible(false);
    sendContactList();

    time_t now = time(NULL);
    if (data.owner.PluginInfoTime.toULong() == 0)
        data.owner.PluginInfoTime.asULong() = now;
    if (data.owner.PluginStatusTime.toULong() == 0)
        data.owner.PluginStatusTime.asULong() = now;
    if (data.owner.InfoUpdateTime.toULong() == 0)
        data.owner.InfoUpdateTime.asULong() = now;
    data.owner.OnlineTime.asULong() = now;
    if (getContacts()->owner()->getPhones() != data.owner.PhoneBook.str()){
        data.owner.PhoneBook.str() = getContacts()->owner()->getPhones();
        data.owner.PluginInfoTime.asULong() = now;
    }
    if (getPicture() != data.owner.Picture.str()){
        data.owner.Picture.str() = getPicture();
        data.owner.PluginInfoTime.asULong() = now;
    }
    if (getContacts()->owner()->getPhoneStatus() != data.owner.FollowMe.toULong()){
        data.owner.FollowMe.asULong() = getContacts()->owner()->getPhoneStatus();
        data.owner.PluginStatusTime.asULong() = now;
    }

    Buffer directInfo(25);
    fillDirectInfo(directInfo);

    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_logonStatus));
    m_socket->writeBuffer.tlv(0x0008, (unsigned short)0);
    m_socket->writeBuffer.tlv(0x000C, directInfo);
    m_socket->writeBuffer.tlv(0x001f, (unsigned short)0);

    sendPacket(true);
    if (!getInvisible())
        sendInvisible(true);
    sendIdleTime();
    m_status = m_logonStatus;
}

void ICQClient::setInvisible()
{
    if (getInvisible())
        sendInvisible(false);
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_status));
    sendPacket(true);
    if (!getInvisible())
        sendInvisible(true);
}

void ICQClient::sendStatus()
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_status));
    sendPacket(true);
    sendIdleTime();
}

void ICQClient::sendPluginInfoUpdate(unsigned plugin_id)
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_status));
    Buffer directInfo(25);
    fillDirectInfo(directInfo);
    m_socket->writeBuffer.tlv(0x000C, directInfo);
    Buffer b;
    b << (char)2;
    b.pack(data.owner.PluginInfoTime.toULong());
    b.pack((unsigned short)2);
    b.pack((unsigned short)1);
    b.pack((unsigned short)2);
    b.pack((char*)plugins[plugin_id], sizeof(plugin));
    b.pack(data.owner.PluginInfoTime.toULong());
    b << (char)0;
    m_socket->writeBuffer.tlv(0x0011, b);
    m_socket->writeBuffer.tlv(0x0012, (unsigned short)0);
    sendPacket(false);
}

void ICQClient::sendPluginStatusUpdate(unsigned plugin_id, unsigned long status)
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_logonStatus));
    Buffer directInfo(25);
    fillDirectInfo(directInfo);
    m_socket->writeBuffer.tlv(0x000C, directInfo);
    Buffer b;
    b << (char)3;
    b.pack(data.owner.PluginStatusTime.toULong());
    b.pack((unsigned short)0);
    b.pack((unsigned short)1);
    b.pack((unsigned short)1);
    b.pack((char*)plugins[plugin_id], sizeof(plugin));
    b << (char)1;
    b.pack(status);
    b.pack(data.owner.PluginStatusTime.toULong());
    b.pack((unsigned short)0);
    b.pack((unsigned short)0);
    b.pack((unsigned short)1);
    m_socket->writeBuffer.tlv(0x0011, b);
    m_socket->writeBuffer.tlv(0x0012, (unsigned short)0);
    sendPacket(false);
}

void ICQClient::sendUpdate()
{
    if (m_nUpdates == 0)
        return;
    if (--m_nUpdates)
        return;
    data.owner.InfoUpdateTime.asULong() = time(NULL);
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxSTATUS);
    m_socket->writeBuffer.tlv(0x0006, fullStatus(m_status));
    Buffer directInfo(25);
    fillDirectInfo(directInfo);
    m_socket->writeBuffer.tlv(0x000C, directInfo);
    sendPacket(false);
}

void ICQClient::fillDirectInfo(Buffer &directInfo)
{
    set_ip(&data.owner.RealIP, m_socket->localHost());
    if (getHideIP()){
        directInfo
        << (unsigned long)0
        << (unsigned long)0;
    }else{
        directInfo
        << (unsigned long)htonl(get_ip(data.owner.RealIP))
        << (unsigned short)0
        << (unsigned short)data.owner.Port.toULong();
    }

    char mode = DIRECT_MODE_DIRECT;
    unsigned long ip1 = get_ip(data.owner.IP);
    unsigned long ip2 = get_ip(data.owner.RealIP);
    if (ip1 && ip2 && (ip1 != ip2))
        mode = DIRECT_MODE_INDIRECT;
    switch (m_socket->socket()->mode()){
    case Socket::Indirect:
        mode = DIRECT_MODE_INDIRECT;
        break;
    case Socket::Web:
        mode = DIRECT_MODE_DENIED;
        break;
    default:
        break;
    }
    directInfo
    << mode
    << (char)0x00
    << (char)ICQ_TCP_VERSION;

    directInfo
    << data.owner.DCcookie.toULong()
    << 0x00000050L
    << 0x00000003L
    << data.owner.InfoUpdateTime.toULong()
    << data.owner.PluginInfoTime.toULong()
    << data.owner.PluginStatusTime.toULong()
    << (unsigned short) 0x0000;
}

void ICQClient::sendIdleTime()
{
    // avoid traffic
    if(!m_bIdleTime && getIdleTime() == 0)
        return;
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SETxIDLE);
    if(getIdleTime()) {
        unsigned long idle = time(NULL) - getIdleTime();
        if (idle <= 0)
            idle = 1;
        m_socket->writeBuffer << idle;
        m_bIdleTime = true;
    } else {
        m_socket->writeBuffer << (unsigned long)0;
        m_bIdleTime = false;
    }
    sendPacket(false);
}

void ICQClient::requestService(ServiceSocket *s)
{
    snac(ICQ_SNACxFAM_SERVICE, ICQ_SNACxSRV_SERVICExREQ, true);
    m_socket->writeBuffer << s->id();
    sendPacket(true);
}
