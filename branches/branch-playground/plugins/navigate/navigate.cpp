/***************************************************************************
                          navigate.cpp  -  description
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

#include "navigate.h"
#include "navcfg.h"
#include "core.h"

#ifdef USE_KDE
#include <kapplication.h>
#endif

#ifndef WIN32
#include <qurl.h>
#endif

using namespace std;
using namespace SIM;

#ifdef WIN32
#include <windows.h>
#include <shellapi.h>
#include <ddeml.h>

class DDEbase
{
public:
    DDEbase();
    ~DDEbase();
    operator DWORD() { return m_idDDE; }
    static DDEbase *base;
protected:
    DWORD m_idDDE;
    static HDDEDATA CALLBACK DDECallback(UINT, UINT, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
};

DDEbase *DDEbase::base = NULL;

DDEbase::DDEbase()
{
    m_idDDE = 0;
    FARPROC lpDdeProc = MakeProcInstance((FARPROC) DDECallback, hInstance);
    DdeInitializeW((LPDWORD) &m_idDDE, (PFNCALLBACK) lpDdeProc,	APPCMD_CLIENTONLY, 0L);
    base = this;
}

DDEbase::~DDEbase()
{
    base = NULL;
    if (m_idDDE)
        DdeUninitialize(m_idDDE);
}

HDDEDATA CALLBACK DDEbase::DDECallback(UINT, UINT, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD)
{
    return NULL;
}

class DDEstring
{
public:
    DDEstring(const QString &name);
    ~DDEstring();
    operator HSZ() { return hSz; }
protected:
    HSZ hSz;
};

DDEstring::DDEstring(const QString &name) : hSz(NULL)
{
    hSz = DdeCreateStringHandleW(*DDEbase::base, (LPCWSTR)name.ucs2(), CP_WINANSI);
}

DDEstring::~DDEstring()
{
    if (hSz)
        DdeFreeStringHandle(*DDEbase::base, hSz);
}

class DDEdataHandle
{
public:
    DDEdataHandle(const char *text);
    DDEdataHandle(HDDEDATA data);
    ~DDEdataHandle();
    operator HDDEDATA() { return hData; }
    operator const char *();
protected:
    HDDEDATA hData;
};

DDEdataHandle::DDEdataHandle(const char *text)
{
    hData = DdeCreateDataHandle(*DDEbase::base, (unsigned char*)text, strlen(text) + 1, 0, NULL, CF_TEXT, 0);
}

DDEdataHandle::DDEdataHandle(HDDEDATA data)
{
    hData = data;
}

DDEdataHandle::~DDEdataHandle()
{
    if (hData) DdeFreeDataHandle(hData);
}

DDEdataHandle::operator const char*()
{
    if (hData == NULL)
        return NULL;
    return (const char*)DdeAccessData(hData, NULL);
}

class DDEconversation
{
protected:
    HCONV hConv;
public:
    DDEconversation(const QString &_server, const QString &_topic);
    ~DDEconversation();
    operator HCONV() { return hConv; }
    HDDEDATA Execute(const QString &cmd);
};

DDEconversation::DDEconversation(const QString &_server, const QString &_topic)
        : hConv(NULL)
{
    DDEstring server(_server);
    DDEstring topic(_topic);
    hConv = DdeConnect(*DDEbase::base, server, topic, NULL);
}

DDEconversation::~DDEconversation()
{
    if (hConv)
        DdeDisconnect(hConv);
}

HDDEDATA DDEconversation::Execute(const QString &cmd)
{
    if (hConv == NULL)
        return NULL;
    DDEstring c(cmd);
    DWORD res = NULL;
    HDDEDATA hData = DdeClientTransaction(NULL, 0, hConv, c, CF_TEXT, XTYP_REQUEST, 30000, &res);
    if (hData == NULL)
        DdeGetLastError((DWORD)DDEbase::base);
    return hData;
}

class RegEntry
{
public:
    RegEntry(HKEY hRootKey, const QString &path);
    ~RegEntry();
    operator HKEY() { return hKey; }
    QString value(const QString &key);
protected:
    HKEY hKey;
};

string getCurrentUrl()
{
    RegEntry r(HKEY_CLASSES_ROOT, "HTTP\\Shell\\open\\ddeexec\\application");
    string topic = r.value("");
    if (topic.empty())
        return "";

    DDEbase b;
    DDEconversation conv(topic.c_str(), "WWW_GetWindowInfo");
    DDEdataHandle answer(conv.Execute("-1"));
    const char *url = answer;
    return url;
}

RegEntry::RegEntry(HKEY hRootKey, const QString &path)
{
    if (RegOpenKeyW(hRootKey, (LPCWSTR)path.ucs2(), &hKey) != ERROR_SUCCESS)
        hKey = NULL;
}

RegEntry::~RegEntry()
{
    if (hKey)
        RegCloseKey(hKey);
}

QString RegEntry::value(const QString &key)
{
    if (hKey == NULL)
        return "";
    long size = 0;
    if (RegQueryValueW(hKey, (LPCWSTR)key.ucs2(), NULL, &size) != ERROR_SUCCESS)
        return "";
    QMemArray<unsigned short> ma(size);
    if (RegQueryValueW(hKey, (LPCWSTR)key.ucs2(), (LPWSTR)ma.data(), &size) != ERROR_SUCCESS)
        return "";
    return QString::fromUcs2(ma);
}

#endif

Plugin *createNavigatePlugin(unsigned base, bool, ConfigBuffer *config)
{
    Plugin *plugin = new NavigatePlugin(base, config);
    return plugin;
}

static PluginInfo info =
    {
        I18N_NOOP("Navigate"),
        I18N_NOOP("Plugin provides navigation on hyperlinks, call an external browser and mailer"),
        VERSION,
        createNavigatePlugin,
        PLUGIN_DEFAULT
    };

EXPORT_PROC PluginInfo* GetPluginInfo()
{
    return &info;
}

/*
typedef struct NavigateData
{
     char *Browser;
     char *Mailer;
} NavigateData;
*/
static DataDef navigateData[] =
    {
#ifdef WIN32
        { "NewWindow", DATA_BOOL, 1, 0 },
#else
#ifdef USE_KDE
        { "Browser", DATA_STRING, 1, "konqueror" },
        { "Mailer", DATA_STRING, 1, "kmail" },
        { "UseKDE", DATA_BOOL, 1, DATA(1) },
#else
        { "Browser", DATA_STRING, 1, "netscape" },
        { "Mailer", DATA_STRING, 1, "netscape mailto:%s" },
#endif
#endif
        { NULL, DATA_UNKNOWN, 0, 0 }
    };


NavigatePlugin::NavigatePlugin(unsigned base, ConfigBuffer *config)
        : Plugin(base)
{
    load_data(navigateData, &data, config);
    CmdMail = registerType();
    CmdMailList = registerType();
    MenuMail = registerType();
    CmdCopyLocation = registerType();

    Event eMenu(EventMenuCreate, (void*)MenuMail);
    eMenu.process();

    Command cmd;
    cmd->id          = CmdMail;
    cmd->text        = I18N_NOOP("Send mail");
    cmd->icon		 = "mail_generic";
    cmd->menu_id     = MenuContact;
    cmd->menu_grp    = 0x30F0;
    cmd->popup_id    = 0;
    cmd->flags		 = COMMAND_CHECK_STATE;

    Event eCmd(EventCommandCreate, cmd);
    eCmd.process();

    cmd->id			 = CmdMailList;
    cmd->text		 = "_";
    cmd->menu_grp	 = 0x1000;
    cmd->menu_id	 = MenuMail;
    eCmd.process();

    cmd->id		= CmdCopyLocation;
    cmd->text		= I18N_NOOP("Copy &location");
    cmd->icon		= "";
    cmd->menu_id	= MenuTextEdit;
    cmd->menu_grp	= 0x7010;
    eCmd.process();

    cmd->menu_id	= MenuMsgView;
    eCmd.process();
}

NavigatePlugin::~NavigatePlugin()
{
    Event eCmd(EventCommandRemove, (void*)CmdMail);
    eCmd.process();
    Event eMenuRemove(EventMenuRemove, (void*)MenuMail);
    eMenuRemove.process();
    free_data(navigateData, &data);
}

void *NavigatePlugin::processEvent(Event *e)
{
#ifdef WIN32
    if (e->type() == EventGetURL){
        string *url = (string*)(e->param());
        *url = getCurrentUrl();
        return e->param();
    }
#endif
    if (e->type() == EventGoURL){
        QString url = *((QString*)(e->param()));
        QString proto;
        if (url.isEmpty())
            return NULL;
        int n = url.find(':');
        if(n < 0)
            return NULL;
        proto = url.left(n);
        if ((proto != "http") &&
                (proto != "https") &&
                (proto != "ftp") &&
                (proto != "file") &&
                (proto != "mailto") &&
                (proto != "file"))
            return NULL;
#ifdef WIN32
        bool bExec = false;
        if (getNewWindow()){
            QString key_name = proto;
            key_name += "\\Shell\\Open";
            RegEntry rp(HKEY_CLASSES_ROOT, key_name);
            QString prg    = rp.value("command");
            QString action = rp.value("ddeexec");
            QString topic  = rp.value("ddeexec\\Topic");
            QString server = rp.value("ddeexec\\Application");
            if (!action.isEmpty()){
                int pos = action.find("%1");
                if (pos >= 0)
                    action = action.left(pos) + url + action.mid(pos + 2);
                pos = prg.find("%1");
                if (pos >= 0)
                    prg = prg.left(pos) + url + prg.mid(pos + 2);
                if (!prg.isEmpty()){
                    STARTUPINFOA si;
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&si, sizeof(si));
                    si.cb = sizeof(si);
                    ZeroMemory(&pi, sizeof(pi));
                    // don't use CreateProcessW this way (see msdn)!
                    if (CreateProcessA(NULL, (LPSTR)prg.latin1(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
                        WaitForInputIdle(pi.hProcess, INFINITE);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }
                }
                DDEbase b;
                DDEconversation conv(server, topic);
                if (conv.Execute(action))
                    bExec = true;
            }
        }
        if (!bExec){
            if (proto == "file")
                url = url.mid(5);
            ShellExecuteW(NULL, NULL, (LPCWSTR)url.ucs2(), NULL, NULL, SW_SHOWNORMAL);
        }
#else
#ifdef USE_KDE
        if (getUseKDE())
        {
            if (proto == "mailto")
                kapp->invokeMailer(QString(url.mid(proto.length() + 1)), QString::null);
            else
                kapp->invokeBrowser(url);
            return e->param();
        }
#endif // USE_KDE
        ExecParam execParam;
        if (proto == "mailto"){
            execParam.cmd = getMailer();
            url = url.mid(proto.length() + 1);
        }else{
            execParam.cmd = getBrowser();
            QUrl qurl(url);
            QString encodedUrl = qurl.toString(true, false);
            url = encodedUrl.latin1();
        }
        execParam.arg = url.latin1();
        Event eExec(EventExec, &execParam);
        eExec.process();
#endif // WIN32
        return e->param();
    }
    if (e->type() == EventAddHyperlinks){
        QString *text = (QString*)(e->param());
        *text = parseUrl(*text);
        return e->param();
    }
    if (e->type() == EventCheckState){
        CommandDef *cmd = (CommandDef*)(e->param());
        if (cmd->id == CmdMail){
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return NULL;
            QString mails = contact->getEMails();
            if (mails.length() == 0)
                return NULL;
            int nMails = 0;
            while (mails.length()){
                getToken(mails, ';');
                nMails++;
            }
            cmd->popup_id = (nMails <= 1) ? 0 : MenuMail;
            return e->param();
        }
        if (cmd->id == CmdMailList){
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return NULL;
            QString mails = contact->getEMails();
            if (mails.length() == 0)
                return NULL;
            int nMails = 0;
            while (mails.length()){
                getToken(mails, ';');
                nMails++;
            }
            CommandDef *cmds = new CommandDef[nMails + 1];
            unsigned n = 0;
            mails = contact->getEMails();
            while (mails.length()){
                QString mail = getToken(mails, ';', false);
                mail = getToken(mail, '/');
                cmds[n] = *cmd;
                cmds[n].id = CmdMailList + n;
                cmds[n].flags = COMMAND_DEFAULT;
                cmds[n].text_wrk = mail;
                n++;
            }
            cmds[n].clear();
            cmd->param = cmds;
            cmd->flags |= COMMAND_RECURSIVE;
            return e->param();
        }
    }
    if (e->type() == EventCommandExec){
        CommandDef *cmd = (CommandDef*)(e->param());
        if (cmd->id == CmdMail){
            QString mail;
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact)
                mail = contact->getEMails();
            mail = getToken(mail, ';', false);
            mail = getToken(mail, '/');
            if (mail.length()){
                QString addr = "mailto:";
                addr += mail;
                Event eMail(EventGoURL, (void*)&addr);
                eMail.process();
            }
            return e->param();
        }
        if (cmd->menu_id == MenuMail){
            unsigned n = cmd->id - CmdMailList;
            QString mails;
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact)
                mails = contact->getEMails();
            while (mails.length()){
                QString mail = getToken(mails, ';', false);
                if (n-- == 0){
                    mail = getToken(mail, '/');
                    if (mail.length()){
                        QString addr = "mailto:";
                        addr += mail;
                        Event eMail(EventGoURL, (void*)&addr);
                        eMail.process();
                    }
                    break;
                }
            }
            return e->param();
        }
    }
    return NULL;
}

QString NavigatePlugin::getConfig()
{
    return save_data(navigateData, &data);
}

QWidget *NavigatePlugin::createConfigWindow(QWidget *parent)
{
    return new NavCfg(parent, this);
}