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
    DdeInitialize((LPDWORD) &m_idDDE, (PFNCALLBACK) lpDdeProc,	APPCMD_CLIENTONLY, 0L);
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
    hSz = DdeCreateStringHandle(*DDEbase::base, (WCHAR*)name.ucs2(), CP_WINUNICODE);
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

QString getCurrentUrl()
{
    RegEntry r(HKEY_CLASSES_ROOT, "HTTP\\Shell\\open\\ddeexec\\application");
    QString topic = r.value("");
    if (topic.isEmpty())
		return QString::null;

    DDEbase b;
    DDEconversation conv(topic, "WWW_GetWindowInfo");
    DDEdataHandle answer(conv.Execute("-1"));
    const char *url = answer;
    return url;
}

RegEntry::RegEntry(HKEY hRootKey, const QString &path)
{
    if (RegOpenKey(hRootKey, (LPCWSTR)path.ucs2(), &hKey) != ERROR_SUCCESS)
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
		return QString::null;
    long size = 0;
    if (RegQueryValue(hKey, (LPCWSTR)key.ucs2(), NULL, &size) != ERROR_SUCCESS)
        return QString::null;
    QMemArray<unsigned short> ba(size + 1);
	ba.fill(0);
    if (RegQueryValue(hKey, (LPCWSTR)key.ucs2(), (LPWSTR)ba.data(), &size) != ERROR_SUCCESS)
		return QString::null;
	return QString::fromUcs2(ba.data());
}

#endif

Plugin *createNavigatePlugin(unsigned base, bool, Buffer *config)
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


NavigatePlugin::NavigatePlugin(unsigned base, Buffer *config)
        : Plugin(base)
{
    load_data(navigateData, &data, config);
    CmdMail = registerType();
    CmdMailList = registerType();
    MenuMail = registerType();
    CmdCopyLocation = registerType();

    EventMenu(MenuMail, EventMenu::eAdd).process();

    Command cmd;
    cmd->id          = CmdMail;
    cmd->text        = I18N_NOOP("Send mail");
    cmd->icon		 = "mail_generic";
    cmd->menu_id     = MenuContact;
    cmd->menu_grp    = 0x30F0;
    cmd->popup_id    = 0;
    cmd->flags		 = COMMAND_CHECK_STATE;
    EventCommandCreate(cmd).process();

    cmd->id			 = CmdMailList;
    cmd->text		 = "_";
    cmd->menu_grp	 = 0x1000;
    cmd->menu_id	 = MenuMail;
    EventCommandCreate(cmd).process();

    cmd->id         = CmdCopyLocation;
    cmd->text		= I18N_NOOP("Copy &location");
    cmd->icon		= QString::null;
    cmd->menu_id	= MenuTextEdit;
    cmd->menu_grp	= 0x7010;
    EventCommandCreate(cmd).process();

    cmd->menu_id	= MenuMsgView;
    EventCommandCreate(cmd).process();
}

NavigatePlugin::~NavigatePlugin()
{
    EventCommandRemove(CmdMail).process();
    EventMenu(MenuMail, EventMenu::eRemove).process();

    free_data(navigateData, &data);
}

bool NavigatePlugin::processEvent(Event *e)
{
#ifdef WIN32
    if (e->type() == eEventGetURL){
        EventGetURL *u = static_cast<EventGetURL*>(e);
        u->setUrl(getCurrentUrl());
        return true;
    }
#endif
    if (e->type() == eEventGoURL){
        EventGoURL *u = static_cast<EventGoURL*>(e);
        QString url = u->url();
        QString proto;
        if (url.length() == 0)
            return false;
        int n = url.find(':');
        if (n < 0)
            return false;
        proto = url.left(n);
        if ((proto != "http") &&
                (proto != "https") &&
                (proto != "ftp") &&
                (proto != "file") &&
                (proto != "mailto") &&
                (proto != "file"))
            return false;
#ifdef WIN32
        bool bExec = false;
        if (getNewWindow()){
            QString key_name = proto + "\\Shell\\Open";
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
                    STARTUPINFO si;
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&si, sizeof(si));
                    si.cb = sizeof(si);
                    ZeroMemory(&pi, sizeof(pi));
                    if (CreateProcess(NULL, (LPWSTR)prg.ucs2(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
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
            ShellExecute(NULL, NULL, (LPCWSTR)url.ucs2(), NULL, NULL, SW_SHOWNORMAL);
        }
#else
#ifdef USE_KDE
        if (getUseKDE())
        {
            if (proto == "mailto")
                kapp->invokeMailer(QString(url.mid(proto.length() + 1)), QString::null);
            else
                kapp->invokeBrowser(url);
            return true;
        }
#endif // USE_KDE
        QString param;
        if (proto == "mailto"){
            param = getMailer();
            url = url.mid(proto.length() + 1);
        }else{
            param = getBrowser();
			QUrl qurl(url);
			QString encodedUrl = qurl.toString(true, false);
			url = encodedUrl;
        }
        EventExec(param, url).process();
#endif // WIN32
        return true;
    } else
    if (e->type() == eEventAddHyperlinks){
        EventAddHyperlinks *h = static_cast<EventAddHyperlinks*>(e);
        h->setText(parseUrl(h->text()));
        return true;
    } else
    if (e->type() == eEventCheckState){
        EventCheckState *ecs = static_cast<EventCheckState*>(e);
        CommandDef *cmd = ecs->cmd();
        if (cmd->id == CmdMail){
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return false;
            QString mails = contact->getEMails();
            if (mails.length() == 0)
                return false;
            int nMails = 0;
            while (mails.length()){
                getToken(mails, ';');
                nMails++;
            }
            cmd->popup_id = (nMails <= 1) ? 0 : MenuMail;
            return true;
        }
        if (cmd->id == CmdMailList){
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact == NULL)
                return false;
            QString mails = contact->getEMails();
            if (mails.length() == 0)
                return false;
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
            return true;
        }
    } else
    if (e->type() == eEventCommandExec){
        EventCommandExec *ece = static_cast<EventCommandExec*>(e);
        CommandDef *cmd = ece->cmd();
        if (cmd->id == CmdMail){
            QString mail;
            Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
            if (contact)
                mail = contact->getEMails();
            mail = getToken(mail, ';', false);
            mail = getToken(mail, '/');
            if (mail.length()){
                QString addr = "mailto:" + mail;
                EventGoURL eMail(addr);
                eMail.process();
            }
            return true;
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
                        QString addr = "mailto:" + mail;
                        EventGoURL(addr).process();
                    }
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

QCString NavigatePlugin::getConfig()
{
    return save_data(navigateData, &data);
}

QWidget *NavigatePlugin::createConfigWindow(QWidget *parent)
{
    return new NavCfg(parent, this);
}
