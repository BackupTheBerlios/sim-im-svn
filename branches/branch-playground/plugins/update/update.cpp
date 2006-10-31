/***************************************************************************
                          update.cpp  -  description
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

#include "update.h"
#include "socket.h"
#include "core.h"
#include "ballonmsg.h"

#include <time.h>
#include <stdio.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qwidgetlist.h>
#include <qregexp.h>

using namespace SIM;

const unsigned CHECK_INTERVAL = 60 * 60 * 24;

Plugin *createUpdatePlugin(unsigned base, bool, ConfigBuffer *config)
{
    Plugin *plugin = new UpdatePlugin(base, config);
    return plugin;
}

static PluginInfo info =
    {
        I18N_NOOP("Update"),
        I18N_NOOP("Plugin provides notifications about update SIM software"),
        VERSION,
        createUpdatePlugin,
        PLUGIN_DEFAULT
    };

EXPORT_PROC PluginInfo* GetPluginInfo()
{
    return &info;
}

static DataDef updateData[] =
    {
        { "Time", DATA_ULONG, 1, 0 },
        { NULL, DATA_UNKNOWN, 0, 0 }
    };

UpdatePlugin::UpdatePlugin(unsigned base, ConfigBuffer *config)
        : Plugin(base)
{
    load_data(updateData, &data, config);
    CmdGo = registerType();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(15000);
}

UpdatePlugin::~UpdatePlugin()
{
    free_data(updateData, &data);
}

QString UpdatePlugin::getConfig()
{
    return save_data(updateData, &data);
}

void UpdatePlugin::timeout()
{
    if (!getSocketFactory()->isActive() || !isDone())
        return;
    if ((unsigned)time(NULL) >= getTime() + CHECK_INTERVAL){
        QString url = "http://sim.shutoff.ru/cgi-bin/update1.pl?v=" VERSION;
#ifdef WIN32
        url += "&os=1";
#else
#ifdef QT_MACOSX_VERSION
        url += "&os=2";
#endif
#endif
#ifdef CVS_BUILD
        url += "&cvs=";
        for (const char *p = __DATE__; *p; p++){
            if (*p == ' '){
                url += "%20";
                continue;
            }
            url += *p;
        }
#else
        url += "&release";
#endif
        url += "&l=";
        QString s = i18n("Message", "%n messages", 1);
        s = s.replace(QRegExp("1 "), "");
        for (int i = 0; i < (int)(s.length()); i++){
            unsigned short c = s[i].unicode();
            if ((c == ' ') || (c == '%') || (c == '=') || (c == '&')){
                char b[5];
                sprintf(b, "%02X", c);
                url += b;
            }else if (c > 0x77){
                char b[10];
                sprintf(b, "#%04X", c);
                url += b;
            }else{
                url += (char)c;
            }
        }
        fetch(url, QString::null, NULL, false);
    }
}

#if 0
I18N_NOOP("Show details")
I18N_NOOP("Remind later")
#endif

bool UpdatePlugin::done(unsigned, Buffer&, const char *headers)
{
    QString h = getHeader("Location", headers);
    if (!h.isEmpty()){
        Command cmd;
        cmd->id		= CmdStatusBar;
        Event eWidget(EventCommandWidget, cmd);
        QWidget *statusWidget = (QWidget*)(eWidget.process());
        if (statusWidget == NULL)
            return false;
        m_url = h;
        clientErrorData d;
        d.client  = NULL;
        d.err_str = I18N_NOOP("New version SIM is released");
        d.code	  = 0;
        d.args    = QString::null;
        d.flags	  = ERR_INFO;
        d.options = "Show details\x00Remind later\x00\x00";
        d.id	  = CmdGo;
        Event e(EventShowError, &d);
        e.process();
    }
    setTime(time(NULL));
    Event e(EventSaveState);
    e.process();
    return false;
}

void *UpdatePlugin::processEvent(Event *e)
{
    if (e->type() == EventCommandExec){
        CommandDef *cmd = (CommandDef*)(e->param());
        if (cmd->id == CmdGo){
            Event eGo(EventGoURL, (void*)&m_url);
            eGo.process();
            setTime(time(NULL));
            m_url = QString::null;
            Event eSave(EventSaveState);
            eSave.process();
            return e->param();
        }
    }
    return NULL;
}

QString UpdatePlugin::getHeader(const char *name, const char *headers)
{
    for (const char *h = headers; *h; h += strlen(h) + 1){
        QString header = h;
        QString key = getToken(header, ':');
        if (key != name)
            continue;
        return header.stripWhiteSpace();
    }
    return "";
}

#ifndef NO_MOC_INCLUDES
#include "update.moc"
#endif