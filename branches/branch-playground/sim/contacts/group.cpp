
#include <vector>

#include "group.h"

#include "contacts.h"
#include "contact.h"
#include "contactlistprivate.h"

namespace SIM
{
    DataDef groupData[] =
    {
        { "Name", DATA_UTF, 1, 0 },
        { NULL, DATA_UNKNOWN, 0, 0 }
    };

    Group::Group(unsigned long id, Buffer *cfg)
    {
        m_id = id;
        load_data(groupData, &data, cfg);
        m_userData = UserData::create();
        userdata()->setValue("id", (uint)id);
    }

    Group::~Group()
    {
        if (!getContacts()->p->bNoRemove){
            Contact *contact;
            ContactList::ContactIterator itc;
            while ((contact = ++itc) != NULL){
                if (contact->getGroup() != (int)id())
                    continue;
                contact->setGroup(0);
                EventContact e(contact, EventContact::eChanged);
                e.process();
            }
            EventGroup e(this, EventGroup::eDeleted);
            e.process();
        }
        free_data(groupData, &data);
        std::vector<Group*> &groups = getContacts()->p->groups;
        for (std::vector<Group*>::iterator it = groups.begin(); it != groups.end(); ++it){
            if ((*it) == this){
                groups.erase(it);
                break;
            }
        }
    }

    PropertyHubPtr Group::getUserData(const QString& id, bool bCreate)
    {
        PropertyHubPtr hub = m_userData->getUserData(id);
        if(!hub.isNull())
            return hub;
        if(bCreate)
            return m_userData->createUserData(id);
        return getContacts()->getUserData(id);
    }

    QString Group::getName()
    {
        return userdata()->value("Name").toString();
    }

    void Group::setName(const QString& name)
    {
        userdata()->setValue("Name", name);
    }
}

// vim: set expandtab:

