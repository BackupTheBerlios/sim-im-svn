/***************************************************************************
                          jabberworkinfo.cpp  -  description
                             -------------------
    begin                : Sun Mar 17 2002
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

#include "jabberclient.h"
#include "simapi.h"
#include "jabberworkinfo.h"
#include "jabber.h"

#include <qlineedit.h>
#include <qstringlist.h>

using namespace SIM;

JabberWorkInfo::JabberWorkInfo(QWidget *parent, struct JabberUserData *data, JabberClient *client)
        : JabberWorkInfoBase(parent)
{
    m_client  = client;
    m_data	  = data;
    if (m_data){
        edtCompany->setReadOnly(true);
        edtDepartment->setReadOnly(true);
        edtTitle->setReadOnly(true);
        edtRole->setReadOnly(true);
    }
    fill(m_data);
}

void JabberWorkInfo::apply()
{
}

int str_cmp(const char *s1, const char *s2);

void *JabberWorkInfo::processEvent(Event *e)
{
    if (e->type() == EventContactChanged){
        Contact *contact = (Contact*)(e->param());
        if (contact->clientData.have(m_data))
            fill(m_data);
    }
    if ((e->type() == EventClientChanged) && (m_data == 0)){
        Client *client = (Client*)(e->param());
        if (client == m_client)
            fill(m_data);
    }
    if (m_data && (e->type() == EventVCard)){
        JabberUserData *data = (JabberUserData*)(e->param());
        if (m_data->ID.str() == data->ID.str() && m_data->Node.str() == data->Node.str())
            fill(data);
    }
    return NULL;
}

void JabberWorkInfo::fill(JabberUserData *data)
{
    if (data == NULL) data = &m_client->data.owner;
    edtCompany->setText(data->OrgName.str());
    edtDepartment->setText(data->OrgUnit.str());
    edtTitle->setText(data->Title.str());
    edtRole->setText(data->Role.str());
}

void JabberWorkInfo::apply(Client *client, void *_data)
{
    if (client != m_client)
        return;
    JabberUserData *data = (JabberUserData*)_data;
    data->OrgName.str() = edtCompany->text();
    data->OrgUnit.str() = edtDepartment->text();
    data->Title.str()   = edtTitle->text();
    data->Role.str()    = edtRole->text();
}

#ifndef NO_MOC_INCLUDES
#include "jabberworkinfo.moc"
#endif
