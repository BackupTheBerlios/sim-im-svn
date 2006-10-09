/***************************************************************************
                          discoinfo.cpp  -  description
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
#include "discoinfo.h"
#include "jabberbrowser.h"
#include "jabber.h"
#include "jabberaboutinfo.h"
#include "listview.h"

#include <qpixmap.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qtabwidget.h>
#include <qpushbutton.h>

using namespace SIM;

extern DataDef jabberUserData[];

DiscoInfo::DiscoInfo(JabberBrowser *browser, const QString &features,
                     const QString &name, const QString &type, const QString &category)
        : DiscoInfoBase(browser, NULL, false, WDestructiveClose)
{
    m_browser = browser;
    SET_WNDPROC("jbrowser")
    setIcon(Pict("Jabber_online"));
    setTitle();
    setButtonsPict(this);
    connect(buttonApply, SIGNAL(clicked()), this, SLOT(apply()));
    m_bVersion = true;
    m_bTime    = true;
    m_bLast	   = true;
    m_bStat	   = true;
    m_bVCard   = true;
    m_about    = NULL;
    m_features = features;
    m_name	   = name;
    m_type	   = type;
    m_category = category;
    load_data(jabberUserData, &m_data, NULL);
    disableWidget(edtJName);
    disableWidget(edtType);
    disableWidget(edtCategory);
    edtNameSpace->setReadOnly(true);
    disableWidget(edtName);
    disableWidget(edtVersion);
    disableWidget(edtSystem);
    disableWidget(edtTime);
    disableWidget(edtLast);
    lstStat->addColumn(i18n("Name"));
    lstStat->addColumn(i18n("Units"));
    lstStat->addColumn(i18n("Value"));
    lstStat->setExpandingColumn(2);
    btnUrl->setPixmap(Pict("home"));
    connect(btnUrl, SIGNAL(clicked()), this, SLOT(goUrl()));
    connect(edtUrl, SIGNAL(textChanged(const QString&)), this, SLOT(urlChanged(const QString&)));
}

DiscoInfo::~DiscoInfo()
{
    free_data(jabberUserData, &m_data);
    m_browser->m_info = NULL;
}

void DiscoInfo::setTitle()
{
    setCaption(m_url);
}

void DiscoInfo::reset()
{
    if (m_about){
        tabInfo->removePage(m_about);
        delete m_about;
        m_about = NULL;
    }
    if (m_browser->m_list->currentItem()){
        m_url  = m_browser->m_list->currentItem()->text(COL_JID);
        m_node = m_browser->m_list->currentItem()->text(COL_NODE);
    }
    free_data(jabberUserData, &m_data);
    load_data(jabberUserData, &m_data, NULL);
    m_data.ID.str() = m_url;
    m_data.Node.str() = m_node;
    setTitle();
    edtJName->setText(m_name);
    edtType->setText(m_type);
    edtCategory->setText(m_category);
    edtNameSpace->setText(m_features);
    bool bVersion = false;
    bool bTime    = false;
    bool bLast	  = false;
    bool bStat	  = false;
    bool bVCard	  = false;
    QString mf = m_features;
    while (!mf.isEmpty()){
        QString f = getToken(mf, '\n');
        if (f == "jabber:iq:version")
            bVersion = true;
        if (f == "jabber:iq:time")
            bTime = true;
        if (f == "jabber:iq:last")
            bLast = true;
        if (f == "http://jabber.org/protocol/stats")
            bStat = true;
        if (f == "vcard-temp")
            bVCard = true;
    }
    int pos = 1;
    if (bVersion != m_bVersion){
        m_bVersion = bVersion;
        if (m_bVersion){
            tabInfo->insertTab(tabVersion, i18n("&Version"), pos++);
        }else{
            tabInfo->removePage(tabVersion);
        }
    }else if (m_bVersion){
        pos++;
    }
    edtName->setText("");
    edtVersion->setText("");
    edtSystem->setText("");
    m_versionId = m_bVersion ? m_browser->m_client->versionInfo(m_url, m_node) : "";
    if ((bTime || bLast) != (m_bTime || m_bLast)){
        m_bTime = bTime;
        m_bLast = bLast;
        if (m_bTime || m_bLast){
            tabInfo->insertTab(tabTime, i18n("&Time"), pos++);
        }else{
            tabInfo->removePage(tabTime);
        }
    }else if (m_bTime || m_bLast){
        pos++;
    }
    edtTime->setText("");
    edtLast->setText("");
    if (m_bTime){
        edtTime->show();
        m_timeId = m_browser->m_client->timeInfo(m_url, m_node);
    }else{
        edtTime->hide();
        m_timeId = "";
    }
    if (m_bLast){
        edtLast->show();
        m_lastId = m_browser->m_client->lastInfo(m_url, m_node);
    }else{
        edtLast->hide();
        m_lastId = "";
    }
    lstStat->clear();
    if (bStat != m_bStat){
        m_bStat = bStat;
        if (m_bStat){
            tabInfo->insertTab(tabStat, i18n("&Stat"), pos++);
        }else{
            tabInfo->removePage(tabStat);
        }
    }else if (m_bStat){
        pos++;
    }
    m_statId = m_bStat ? m_browser->m_client->statInfo(m_url, m_node) : "";
    if (bVCard != m_bVCard){
        m_bVCard = bVCard;
        if (m_bVCard || m_bVCard){
            tabInfo->insertTab(tabVCard, i18n("&Info"), pos++);
        }else{
            tabInfo->removePage(tabVCard);
        }
    }else if (m_bVCard){
        pos++;
    }
    edtFirstName->setText("");
    edtNick->setText("");
    edtBirthday->setText("");
    edtUrl->setText("");
    edtEMail->setText("");
    edtPhone->setText("");
    if (bVCard){
        m_about = new JabberAboutInfo(tabInfo, &m_data, m_browser->m_client);
        tabInfo->insertTab(m_about, i18n("About info"), pos++);
        m_browser->m_client->info_request(&m_data, true);
    }
}

void *DiscoInfo::processEvent(Event *e)
{
    if (e->type() == EventVCard){
        JabberUserData *data = (JabberUserData*)(e->param());
        if (m_data.ID.str() == data->ID.str() && m_data.Node.str() == data->Node.str()){
            edtFirstName->setText(data->FirstName.str());
            edtNick->setText(data->Nick.str());
            edtBirthday->setText(data->Bday.str());
            edtUrl->setText(data->Url.str());
            urlChanged(edtUrl->text());
            edtEMail->setText(data->EMail.str());
            edtPhone->setText(data->Phone.str());
        }
    }
    if (e->type() == EventDiscoItem){
        DiscoItem *item = (DiscoItem*)(e->param());
        if (m_versionId == item->id){
            m_versionId = "";
            edtName->setText(item->name);
            edtVersion->setText(item->jid);
            edtSystem->setText(item->node);
            return e->param();
        }
        if (m_timeId == item->id){
            m_timeId = "";
            edtTime->setText(item->jid);
            return e->param();
        }
        if (m_statId == item->id){
            if (item->jid.isEmpty()){
                m_statId = "";
                return e->param();
            }
            QListViewItem *i = new QListViewItem(lstStat);
            i->setText(0, item->jid);
            i->setText(1, item->name);
            i->setText(2, item->node);
            return e->param();
        }
        if (m_lastId == item->id){
            m_lastId = "";
            unsigned ss = item->jid.toUInt();
            unsigned mm = ss / 60;
            ss -= mm * 60;
            unsigned hh = mm / 60;
            mm -= hh * 60;
            unsigned dd = hh / 24;
            hh -= dd * 24;
            QString date;
            if (dd){
                date  = i18n("%n day", "%n days", dd);
                date += " ";
            }
            QString time;
            time.sprintf("%02u:%02u:%02u", hh, mm, ss);
            date += time;
            edtLast->setText(date);
            return e->param();
        }
    }
    return NULL;
}

void DiscoInfo::resizeEvent(QResizeEvent *e)
{
    DiscoInfoBase::resizeEvent(e);
    lstStat->adjustColumn();
}

void DiscoInfo::accept()
{
    apply();
    DiscoInfoBase::accept();
}

void DiscoInfo::apply()
{
    if (m_bVCard && m_about){
        m_about->apply(m_browser->m_client, &m_data);
        m_data.FirstName.str()  = edtFirstName->text();
        m_data.Nick.str()       = edtNick->text();
        m_data.Bday.str()       = edtBirthday->text();
        m_data.Url.str()        = edtUrl->text();
        m_data.EMail.str()      = edtEMail->text();
        m_data.Phone.str()      = edtPhone->text();
        m_browser->m_client->setClientInfo(&m_data);
    }
}

void DiscoInfo::goUrl()
{
    QString url = edtUrl->text();
    if (url.isEmpty())
        return;
    Event e(EventGoURL, (void*)&url);
    e.process();
}

void DiscoInfo::urlChanged(const QString &text)
{
    btnUrl->setEnabled(!text.isEmpty());
}

#ifndef NO_MOC_INCLUDES
#include "discoinfo.moc"
#endif

