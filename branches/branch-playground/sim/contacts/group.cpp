
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
        m_userdata = new PropertyHub("");
        m_userdata->setValue("id", (uint)id);
    }

    Group::~Group()
    {
        if (!getContacts()->p->bNoRemove){
            Contact *contact;
            ContactList::ContactIterator itc;
            while ((contact = ++itc) != NULL){
                if (contact->getGroup() != id())
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
        delete m_userdata;
    }

    void *Group::getUserData(unsigned id, bool bCreate)
    {
        void *res = userData.getUserData(id, bCreate);
        if (res)
            return res;
        if (bCreate)
            return userData.getUserData(id, true);
        return getContacts()->getUserData(id);
    }
}

// vim: set expandtab:

