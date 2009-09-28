
#include <vector>
#include <list>
#include "client.h"
#include "contactlistprivate.h"
#include "group.h"
#include "misc.h"
#include "contacts/contact.h"

namespace SIM
{
    static DataDef _clientData[] =
    {
        { "ManualStatus", DATA_ULONG, 1, DATA(1) },
        { "CommonStatus", DATA_BOOL, 1, DATA(1) },
        { "Password", DATA_UTF, 1, 0 },
        { "", DATA_BOOL, 1, DATA(1) },      // SavePassword
        { "", DATA_UTF, 1, 0 },             // PreviousPassword
        { "Invisible", DATA_BOOL, 1, 0 },
        { "LastSend", DATA_STRLIST, 1, 0 },
        { NULL, DATA_UNKNOWN, 0, 0 }
    };

    Client::Client(Protocol *protocol, Buffer *cfg)
    {
        load_data(_clientData, &data, cfg);

        // now uncrypt password somehow
        QString pswd = getPassword();
        if (pswd.length() && (pswd[0] == '$')) {
            pswd = pswd.mid(1);
            QString new_pswd;
            unsigned short temp = 0x4345;
            QString tmp;
            do {
                QString sub_str = getToken(pswd, '$');
                temp ^= sub_str.toUShort(0,16);
                new_pswd += tmp.setUtf16(&temp,1);
                temp = sub_str.toUShort(0,16);
            } while (pswd.length());
            setPassword(new_pswd);
        }

        m_protocol = protocol;
        m_status = STATUS_OFFLINE;
        m_state  = Offline;
    }

    void Client::setStatus(unsigned status, bool bCommon)
    {
        setManualStatus(status);
        setCommonStatus(bCommon);
        EventClientChanged(this).process();
    }

    Client::~Client()
    {
        freeData();
    }

    QString Client::resources(void*)
    {
        return QString::null;
    }

    QString Client::contactName(void*)
    {
        return i18n(protocol()->description()->text);
    }

    CommandDef *Client::infoWindows(Contact*, void*)
    {
        return NULL;
    }

    QWidget *Client::infoWindow(QWidget*, Contact*, void*, unsigned)
    {
        return NULL;
    }

    CommandDef *Client::configWindows()
    {
        return NULL;
    }

    QWidget *Client::configWindow(QWidget*, unsigned)
    {
        return NULL;
    }

    QString Client::contactTip(void*)
    {
        return QString::null;
    }

    void Client::updateInfo(Contact *contact, void *data)
    {
        if(data)
        {
            EventContact(contact, EventContact::eFetchInfoFailed).process();
        }
        else
        {
            EventClientChanged(this).process();
        }
    }

    void Client::freeData()
    {
        ContactListPrivate *p = getContacts()->p;
        for (std::vector<Client*>::iterator it = p->clients.begin(); it != p->clients.end(); ++it){
            if ((*it) != this)
                continue;
            p->clients.erase(it);
            if (!getContacts()->p->bNoRemove){
                EventClientsChanged e;
                e.process();
            }
            break;
        }
        Group *grp;
        ContactList::GroupIterator itg;
        while ((grp = ++itg) != NULL){
            if (grp->clientData.size() == 0)
                continue;
            grp->clientData.freeClientData(this);
            if (!getContacts()->p->bNoRemove){
                EventGroup e(grp, EventGroup::eChanged);
                e.process();
            }
        }

        Contact *contact;
        ContactList::ContactIterator itc;
        std::list<Contact*> forRemove;
        while ((contact = ++itc) != NULL){
            if (contact->clientData.size() == 0)
                continue;
            contact->clientData.freeClientData(this);
            if (contact->clientData.size()){
                if (!getContacts()->p->bNoRemove){
                    contact->setup();
                    EventContact e(contact, EventContact::eChanged);
                    e.process();
                }
                continue;
            }
            forRemove.push_back(contact);
        }
        std::list<Contact*>::iterator itr;
        for (itr = forRemove.begin(); itr != forRemove.end(); ++itr){
            Contact *contact = *itr;
            delete contact;
        }
        free_data(_clientData, &data);
    }

    QByteArray Client::getConfig()
    {
        QString real_pswd = getPassword();
        QString pswd = getPassword();

        // crypt password somehow
        if (pswd.length()) {
            QString new_passwd;
            unsigned short temp = 0x4345;
            for (int i = 0; i < (int)(pswd.length()); i++) {
                temp ^= (pswd[i].unicode());
                new_passwd += '$';
                new_passwd += QString::number(temp,16);
            }
            setPassword(new_passwd);
        }
        QString prev = getPreviousPassword();
        if (!prev.isEmpty())
            setPassword(prev);
        if (!getSavePassword())
            setPassword(NULL);
        QByteArray res = save_data(_clientData, &data);
        setPassword(real_pswd);
        return res;
    }

    void Client::setClientInfo(void*)
    {
    }

    bool Client::compareData(void*, void*)
    {
        return false;
    }

    void Client::setState(State state, const QString &text, unsigned code)
    {
        m_state = state;
        EventClientChanged(this).process();
        if (state == Error){
            EventNotification::ClientNotificationData d;
            d.client  = this;
            d.text = text;
            d.code    = code;
            d.args    = QString::null;
            d.flags   = EventNotification::ClientNotificationData::E_ERROR;
            d.options = QString::null;
            d.id      = 0;
            for (unsigned i = 0; i < getContacts()->nClients(); i++){
                if (getContacts()->getClient(i) == this){
                    d.id = i + 1;
                    break;
                }
            }
            EventClientNotification e(d);
            e.process();
        }
    }

    void Client::contactsLoaded()
    {
    }

}

// vim: set expandtab:
