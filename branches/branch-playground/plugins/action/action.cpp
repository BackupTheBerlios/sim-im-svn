/***************************************************************************
                          action.cpp  -  description
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

#include <QTimer>
#include <QProcess>
#include <QList>

#include "log.h"
#include "unquot.h"
#include "core.h"

#include "action.h"
#include "actioncfg.h"

using namespace std;
using namespace SIM;

Plugin *createActionPlugin(unsigned base, bool, Buffer*)
{
    Plugin *plugin = new ActionPlugin(base);
    return plugin;
}

static PluginInfo info =
    {
        I18N_NOOP("Action"),
        I18N_NOOP("Plugin execute external programs on event or from contact menu"),
        VERSION,
        createActionPlugin,
        PLUGIN_NOLOAD_DEFAULT
    };

EXPORT_PROC PluginInfo* GetPluginInfo()
{
    return &info;
}

static DataDef actionUserData[] =
    {
        { "OnLine", DATA_UTF, 1, 0 },
        { "Status", DATA_UTF, 1, 0 },
        { "Message", DATA_UTFLIST, 1, 0 },
        { "Menu", DATA_UTFLIST, 1, 0 },
        { "NMenu", DATA_ULONG, 1, 0 },
        { NULL, DATA_UNKNOWN, 0, 0 }
    };

static ActionPlugin *plugin = NULL;

static QWidget *getActionSetup(QWidget *parent, void *data)
{
    return new ActionConfig(parent, (ActionUserData*)data, plugin);
}

ActionPlugin::ActionPlugin(unsigned base)
        : Plugin(base), EventReceiver(HighPriority)
{
    plugin = this;

    action_data_id = getContacts()->registerUserData(info.title, actionUserData);
    CmdAction = registerType();

    Command cmd;
    cmd->id		 = action_data_id;
    cmd->text	 = I18N_NOOP("&Action");
    cmd->icon	 = "run";
    cmd->param	 = (void*)getActionSetup;
    EventAddPreferences(cmd).process();

    cmd->id		 = CmdAction;
    cmd->text	 = "_";
    cmd->icon	 = QString::null;
    cmd->flags	 = COMMAND_CHECK_STATE;
    cmd->menu_id = MenuContact;
    cmd->menu_grp = 0xC000;
    cmd->param	 = NULL;
    EventCommandCreate(cmd).process();

    EventGetPluginInfo ePlugin("_core");
    ePlugin.process();
    const pluginInfo *info = ePlugin.info();
    core = static_cast<CorePlugin*>(info->plugin);
}

ActionPlugin::~ActionPlugin()
{
    EventCommandRemove(CmdAction).process();
    EventRemovePreferences(action_data_id).process();
    getContacts()->unregisterUserData(action_data_id);
}

QWidget *ActionPlugin::createConfigWindow(QWidget *parent)
{
    ActionUserData *data = (ActionUserData*)(getContacts()->getUserData(action_data_id));
    return new ActionConfig(parent, data, this);
}

class MsgProcess : public QProcess
{
protected:
    Message *m_msg;
public:
    MsgProcess(Message *msg, QObject *parent = 0)
        : QProcess(parent), m_msg(msg)
    {}
    Message *msg() const { return m_msg; }
};

bool ActionPlugin::processEvent(Event *e)
{
    switch (e->type() ) {
    case eEventCheckCommandState: {
        EventCheckCommandState *ecs = static_cast<EventCheckCommandState*>(e);
        CommandDef *cmd = ecs->cmd();
        if ((cmd->id == CmdAction) && (cmd->menu_id == MenuContact)){
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return false;
            ActionUserData *data = (ActionUserData*)(contact->getUserData(action_data_id));
            if ((data == NULL) || (data->NMenu.toULong() == 0))
                return false;
            CommandDef *cmds = new CommandDef[data->NMenu.toULong() + 1];
            unsigned n = 0;
            for (unsigned i = 0; i < data->NMenu.toULong(); i++){
                QString str = get_str(data->Menu, i + 1);
                QString item = getToken(str, ';');
                int pos = item.indexOf("&IP;");
                if (pos >= 0){
                    EventGetContactIP e(contact);
                    if (!e.process())
                        continue;
                }
                pos = item.indexOf("&Mail;");
                if (pos >= 0){
                    if (contact->getEMails().isEmpty())
                        continue;
                }
                pos = item.indexOf("&Phone;");
                if (pos >= 0){
                    if (contact->getPhones().isEmpty())
                        continue;
                }
                cmds[n].id = CmdAction + i;
                cmds[n].text = "_";
                cmds[n].text_wrk = item;
                n++;
            }
            if (n == 0){
                delete[] cmds;
                return false;
            }
            cmd->param = cmds;
            cmd->flags |= COMMAND_RECURSIVE;
            return true;
        }
        break;
    }
    case eEventCommandExec: {
        EventCommandExec *ece = static_cast<EventCommandExec*>(e);
        CommandDef *cmd = ece->cmd();
        if ((cmd->menu_id == MenuContact) && (cmd->id >= CmdAction)){
            unsigned n = cmd->id - CmdAction;
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return false;
            ActionUserData *data = (ActionUserData*)(contact->getUserData(action_data_id));
            if ((data == NULL) || (n >= data->NMenu.toULong()))
                return false;
            QString str = get_str(data->Menu, n + 1);
            getToken(str, ';');
            EventTemplate::TemplateExpand t;
            t.tmpl     = str;
            t.contact  = contact;
            t.receiver = this;
            t.param    = NULL;
            EventTemplateExpand(&t).process();
            return true;
        }
        break;
    }
    case eEventContact: {
        EventContact *ec = static_cast<EventContact*>(e);
        if(ec->action() != EventContact::eOnline)
            break;
        Contact *contact = ec->contact();
        if (contact == NULL)
            return false;
        ActionUserData *data = (ActionUserData*)(contact->getUserData(action_data_id));
        if ((data == NULL) || (data->OnLine.str().isEmpty()))
            return false;
        EventTemplate::TemplateExpand t;
        t.tmpl     = data->OnLine.str();
        t.contact  = contact;
        t.receiver = this;
        t.param    = NULL;
        EventTemplateExpand(&t).process();
        return true;
    }
    case eEventMessageReceived: {
        EventMessage *em = static_cast<EventMessage*>(e);
        Message *msg = em->msg();
        Contact *contact = getContacts()->contact(msg->contact());
        if (contact == NULL)
            return false;
        ActionUserData *data = (ActionUserData*)(contact->getUserData(action_data_id));
        if (data == NULL)
            return false;
        if (msg->type() == MessageStatus){
            if (data->Status.str().isEmpty())
                return false;
            EventTemplate::TemplateExpand t;
            t.tmpl     = data->Status.str();
            t.contact  = contact;
            t.receiver = this;
            t.param    = NULL;
            EventTemplateExpand(&t).process();
            return false;
        }
        QString cmd = get_str(data->Message, msg->baseType());
        if (cmd.isEmpty())
            return false;
        EventTemplate::TemplateExpand t;
        t.tmpl	   = cmd;
        t.contact  = contact;
        t.receiver = this;
        t.param	   = msg;
        EventTemplateExpand(&t).process();
        return true;
    }
    case eEventTemplateExpanded: {
        EventTemplate *et = static_cast<EventTemplate*>(e);
        EventTemplate::TemplateExpand *t = et->templateExpand();
        Message *msg = (Message*)(t->param);
        QProcess *proc;
        if (msg){
            QString text = t->tmpl + unquoteText(msg->presentation());
            proc = new MsgProcess(msg, this);
            connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)),
                    this, SLOT(msg_ready(int, QProcess::ExitStatus)));
            proc->start(text);
        }else{
            proc = new QProcess(this);
            connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)),
                    this, SLOT(ready(int, QProcess::ExitStatus)));
            proc->start(t->tmpl);
        }
        break;
    }
    default:
        break;
    }
    return false;
}

void ActionPlugin::ready(int exitCode, QProcess::ExitStatus exitStatus)
{
    // if this does not work as expected we've to remember the pid + QProcess ptr in a map
    // using a list is not the correct way to go!
    QProcess *p = qobject_cast<QProcess*>(sender());
    if(!p)
        return;
    if (exitStatus != QProcess::NormalExit || exitCode != 0)
        log(L_WARN, "QProcess fail: %u, %u", exitStatus, exitCode);
    p->deleteLater();
}

void ActionPlugin::msg_ready(int exitCode, QProcess::ExitStatus exitStatus)
{
    // if this does not work as expected we've to remember the pid + QProcess ptr in a map
    // using a list is not the correct way to go!
    QProcess *p = qobject_cast<QProcess*>(sender());
    if(!p)
        return;
    Message *msg = static_cast<MsgProcess*>(p)->msg();
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        EventMessageReceived e(msg);
        if (!e.process(this))
            delete msg;
    }else{
        QByteArray bOut = p->readAllStandardOutput();
        if (!bOut.isEmpty()){
            msg->setFlags(msg->getFlags() & ~MESSAGE_RICHTEXT);
            msg->setText(QString::fromLocal8Bit(bOut));
            EventMessageReceived e(msg);
            if (!e.process(this))
                delete msg;
        }else{
            delete msg;
        }
    }
    p->deleteLater();
}
