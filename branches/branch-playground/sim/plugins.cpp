/***************************************************************************
                          plugins.cpp  -  description
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <qapplication.h>
#include <qdir.h>
#include <qfile.h>
#include <qlibrary.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextstream.h>

#include "simapi.h"
#include "sockfactory.h"
#include "fetch.h"
#include "exec.h"
#include "sax.h"
#include "xsl.h"
#include "builtinlogger.h"

#include <ctype.h>
#include <errno.h>

#ifndef  LTDL_SHLIB_EXT
# if defined(QT_MACOSX_VERSION) || defined(QT_MAC) /* MacOS needs .a */
#  define  LTDL_SHLIB_EXT ".a"
# else
#  if defined(_WIN32) || defined(_WIN64)
#   define  LTDL_SHLIB_EXT ".dll"
#  else
#   define  LTDL_SHLIB_EXT ".so"
#  endif
# endif
#endif

using namespace std;

namespace SIM
{

Plugin::Plugin(unsigned base)
{
    m_base = base;
    m_current = base;
}

unsigned Plugin::registerType()
{
    return m_current++;
}

void Plugin::boundTypes()
{
    m_current = (m_current | 0x3F) + 1;
}

QWidget *Plugin::createConfigWindow(QWidget*)
{
    return NULL;
}

QString Plugin::getConfig()
{
    return "";
}

typedef struct CmdDescr
{
    string arg;
    string descr;
} CmdDescr;

class PluginManagerPrivate : public EventReceiver
{
public:
    PluginManagerPrivate(int argc, char **argv);
    ~PluginManagerPrivate();
protected:
    void *processEvent(Event *e);

    bool findParam(const QString &param, const QString &descr, QString &res);
    void usage(const QString &);

    bool create(pluginInfo&);
    bool createPlugin(pluginInfo&);

    void release(pluginInfo&, bool bFree = true);
    void release(const QString &name);
    void release_all(Plugin *to);

    void load(pluginInfo&);
    void load(const QString &name);
    void load_all(Plugin *to);

    void saveState();
    void loadState();
    void reloadState();

    pluginInfo *getInfo(const QString &name);
    pluginInfo *getInfo(unsigned n);
    bool setInfo(const QString *name);

#ifndef WIN32
    unsigned long execute(const char *prg, const char *arg);
#endif

    int m_argc;
    char **m_argv;

    QString app_name;
    QStringList args;
    vector<pluginInfo> plugins;
    QStringList cmds;
    QStringList descrs;

    unsigned m_base;
    bool m_bLoaded;
    bool m_bInInit;
    bool m_bAbort;

    ExecManager  *m_exec;
    auto_ptr<BuiltinLogger> builtinLogger;

    friend class PluginManager;
};

static bool cmp_plugin(pluginInfo p1, pluginInfo p2)
{
    QString s1 = p1.name.lower();
    QString s2 = p2.name.lower();

    if(s1 < s2)
        return true;
    if(s1 > s2)
        return false;
    return false;
}

PluginManagerPrivate::PluginManagerPrivate(int argc, char **argv)
        : EventReceiver(LowPriority)
{
    m_argc = argc;
    m_argv = argv;
    unsigned logLevel = L_ERROR | L_WARN;
#ifdef DEBUG
    logLevel |= L_DEBUG;
#endif
    builtinLogger.reset(new BuiltinLogger(logLevel));

    m_exec = new ExecManager;

    app_name = QString::fromLocal8Bit(*argv);
    for (argv++, argc--; argc > 0; argv++, argc--)
        args.push_back(QString::fromLocal8Bit(*argv));

    m_base = 0;
    m_bLoaded = false;
    m_bInInit = true;

    QStringList pluginsList;
#ifdef WIN32
    QDir pluginDir(app_file("plugins"));
#else
    QDir pluginDir(PLUGIN_PATH);
#endif
    /* do some test so we can blame when sim can't access / find
       the plugins */
    pluginsList = pluginDir.entryList("*" LTDL_SHLIB_EXT);
    if (pluginsList.isEmpty()) {
        log(L_ERROR,
            "Can't access %s or directory contains no plugins!",
            pluginDir.path().ascii());
        m_bAbort = true;
        return;
    }
    m_bAbort = false;

    log(L_DEBUG,"Loading plugins from %s",pluginDir.path().ascii());
    for (QStringList::Iterator it = pluginsList.begin(); it != pluginsList.end(); ++it){
        QString f = *it;
        int p = f.findRev('.');
        if (p > 0)
            f = f.left(p);
        pluginInfo info;
        info.plugin      = NULL;
#ifdef WIN32
        info.name        = f.lower();
#else
        info.name        = f;
#endif
        info.cfg         = NULL;
        info.bDisabled   = false;
        info.bNoCreate   = false;
        info.bFromCfg    = false;
        info.module      = NULL;
        info.info        = NULL;
        info.base        = 0;
        plugins.push_back(info);
        log(L_DEBUG,"Found plugin %s",info.name.local8Bit().data());
    }
    Event eCorePlugin(EventGetPluginInfo, (void*)"_core");
    pluginInfo *coreInfo = static_cast<pluginInfo*>(eCorePlugin.process());
    if (!coreInfo) {
        log(L_ERROR,"Fatal error: Core plugin failed to load. Aborting!");
        m_bAbort = true;
        return;
    }
    sort(plugins.begin(), plugins.end(), cmp_plugin);
    for (vector<pluginInfo>::iterator itp = plugins.begin(); itp != plugins.end(); ++itp){
        create((*itp));
        if (m_bAbort)
            return;
    }
    Event eStart(EventInit);
    if (eStart.process() == (void*)-1) {
        log(L_ERROR,"EventInit failed - aborting!");
        m_bAbort = true;
        return;
    }
    for (QStringList::iterator it_args = args.begin(); it_args != args.end(); ++it_args){
        if ((*it_args).length()){
            usage(*it_args);
            break;
        }
    }
    m_bInInit = false;
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    release_all(NULL);
    delete m_exec;
    setLogEnable(false);
    XSL::cleanup();
    SAXParser::cleanup();
}

void *PluginManagerPrivate::processEvent(Event *e)
{
    CmdParam *p;
#ifndef WIN32
    ExecParam *exec;
#endif
    switch (e->type()){
    case EventArg:
        p = (CmdParam*)(e->param());
        return (void*)findParam(p->arg, p->descr, p->value);
    case EventPluginGetInfo: {
        unsigned long info = (unsigned long)e->param();
        return getInfo(info);
    }
    case EventApplyPlugin:
        return (void*)setInfo((QString*)e->param());
    case EventPluginsUnload:
        release_all((Plugin*)(e->param()));
        return e->param();
    case EventPluginsLoad:
        load_all((Plugin*)(e->param()));
        return e->param();
    case EventUnloadPlugin:
        release(*((QString*)e->param()));
        return e->param();
    case EventLoadPlugin:
        load(*((QString*)e->param()));
        return e->param();
    case EventSaveState:
        saveState();
        break;
    case EventGetPluginInfo:
        return getInfo((const char*)(e->param()));
    case EventArgc:
        return (void*)m_argc;
    case EventArgv:
        return (void*)m_argv;
#ifndef WIN32
    case EventExec:
        exec = (ExecParam*)(e->param());
        return (void*)execute(exec->cmd, exec->arg);
#endif
    default:
        break;
    }
    return NULL;
}

pluginInfo *PluginManagerPrivate::getInfo(const QString &name)
{
    for (unsigned n = 0; n < plugins.size(); n++){
        pluginInfo &info = plugins[n];
        if (info.name == name)
            return &info;
    }
    return NULL;
}

void PluginManagerPrivate::release_all(Plugin *to)
{
    for (int n = plugins.size() - 1; n >= 0; n--){
        pluginInfo &info = plugins[n];
        if (to && (info.plugin == to))
            break;
        if (to && info.info && (info.info->flags & (PLUGIN_PROTOCOL & ~PLUGIN_NOLOAD_DEFAULT)))
            continue;
        release(info, to != NULL);
        info.bDisabled = false;
        info.bFromCfg  = false;
        if (info.cfg){
            delete info.cfg;
            info.cfg = NULL;
        }
    }
}

void PluginManagerPrivate::load(const QString &name)
{
    pluginInfo *info = getInfo(name);
    if (info)
        load(*info);
}

void PluginManagerPrivate::load(pluginInfo &info)
{
    if (info.module == NULL){
#ifdef WIN32
        QString pluginName = "plugins\\";
        pluginName += info.name;
#else
        QString pluginName;
        if( pluginName[0] != '/' ) {
            pluginName = PLUGIN_PATH;
            pluginName += "/";
            pluginName += info.name;
        }
#endif
        QString fullName = app_file(pluginName);
        info.module = new QLibrary(fullName);
        if (info.module == NULL) {
            QCString cstr = QString("Can't load plugin " + info.name + "\n").local8Bit();
            qWarning(cstr.data());
        }
    }
    if (info.module == NULL)
        return;
    if (info.info == NULL){
        PluginInfo* (*getInfo)() = NULL;
        getInfo = (PluginInfo* (*)()) info.module->resolve("GetPluginInfo");
        if (getInfo == NULL){
            // fprintf and log() doesn't work here...
            QCString cstr = QString("Plugin " + info.name + " hasn't entry GetPluginInfo\n").local8Bit();
            qWarning(cstr.data());
            release(info);
            return;
        }
        info.info = getInfo();
#ifndef WIN32
# ifdef USE_KDE
        if (!(info.info->flags & PLUGIN_KDE_COMPILE)){
            QCString cstr = QString("Plugin " + info.name + " is compiled without KDE support!\n").local8Bit();
            qWarning(cstr.data());
            release(info);
            return;
        }
# else
        if (info.info->flags & PLUGIN_KDE_COMPILE){
            QCString cstr = QString("Plugin " + info.name + " is compiled with KDE support!\n").local8Bit();
            qWarning(cstr.data());
            release(info);
            return;
        }
# endif
#endif
    }
}

bool PluginManagerPrivate::create(pluginInfo &info)
{
    if (info.plugin)
        return true;
    QString param;
    QString descr;
    QString value;
    param = "--enable-";
    param += info.name;
    if (findParam(param, QString::null, value)){
        info.bDisabled = false;
        info.bFromCfg = true;
    }
    param = "--disable-";
    param += info.name;
    if (findParam(param, QString::null, value)){
        info.bDisabled = true;
        info.bFromCfg = true;
    }
    if (info.bDisabled)
        return false;
    load(info);
    if (info.info == NULL)
        return false;
    if (m_bInInit && (info.info->flags & (PLUGIN_PROTOCOL & ~PLUGIN_NOLOAD_DEFAULT))){
        info.bDisabled = true;
        release(info);
        return false;
    }
    return createPlugin(info);
}

bool PluginManagerPrivate::createPlugin(pluginInfo &info)
{
    if (!info.bFromCfg && (info.info->flags & (PLUGIN_NOLOAD_DEFAULT & ~PLUGIN_DEFAULT))){
        info.bDisabled = true;
        release(info);
        return false;
    }
    log(L_DEBUG, "Load plugin %s", info.name.local8Bit().data());
    if (!m_bLoaded && !(info.info->flags & (PLUGIN_NO_CONFIG_PATH & ~PLUGIN_DEFAULT))){
        loadState();
        if (info.bDisabled || (!info.bFromCfg && (info.info->flags & (PLUGIN_NOLOAD_DEFAULT & ~PLUGIN_DEFAULT)))){
            release(info);
            return false;
        }
    }
    if (info.base == 0){
        m_base += 0x1000;
        info.base = m_base;
    }
    info.plugin = info.info->create(info.base, m_bInInit, info.cfg);
    if ((unsigned long)(info.plugin) == ABORT_LOADING){
        m_bAbort = true;
        info.plugin = NULL;
    }
    if (info.plugin == NULL){
        info.bNoCreate = true;
        info.bDisabled = true;
        return false;
    }
    if (info.cfg){
        delete info.cfg;
        info.cfg = NULL;
    }
    if (info.info->flags & PLUGIN_RELOAD){
        reloadState();
        loadState();
    }
    Event e(EventPluginChanged, &info);
    e.process();
    return true;
}

void PluginManagerPrivate::load_all(Plugin *from)
{
    if (from == (Plugin*)ABORT_LOADING){
        m_bAbort = true;
        qApp->quit();
        return;
    }
    reloadState();
    unsigned i;
    for (i = 0; i < plugins.size(); i++){
        pluginInfo &info = plugins[i];
        if (info.plugin == from)
            break;
    }
    for (; i < plugins.size(); i++)
        create(plugins[i]);
}

void PluginManagerPrivate::release(const QString &name)
{
    pluginInfo *info = getInfo(name);
    if (info)
        release(*info);
}

void PluginManagerPrivate::release(pluginInfo &info, bool bFree)
{
    if (info.plugin){
        log(L_DEBUG, "Unload plugin %s", info.name.local8Bit().data());
        delete info.plugin;
        info.plugin = NULL;
        Event e(EventPluginChanged, &info);
        e.process();
    }
    if (info.module){
        if (bFree)
            delete info.module;
        info.module = NULL;
    }
    info.info = NULL;
}

pluginInfo *PluginManagerPrivate::getInfo(unsigned n)
{
    if (n >= plugins.size())
        return NULL;
    pluginInfo &info = plugins[n];
    return &info;
}

bool PluginManagerPrivate::setInfo(const QString *name)
{
    pluginInfo *info = getInfo(*name);
    if (info == NULL)
        return false;
    if (info->bDisabled){
        if (info->plugin == NULL)
            return false;
        release(*info);
        load(*info);
        return true;
    }
    if (info->plugin)
        return false;
    info->bFromCfg = true;
    load(*info);
    createPlugin(*info);
    return true;
}

static char PLUGINS_CONF[] = "plugins.conf";
static char ENABLE[] = "enable";
static char DISABLE[] = "disable";
static char BACKUP_SUFFIX[] = "~";

void PluginManagerPrivate::saveState()
{
    if (m_bAbort)
        return;
    getContacts()->save();
    QString cfgName = user_file(PLUGINS_CONF);
    QFile f(cfgName + BACKUP_SUFFIX); // use backup file for this ...
    if (!f.open(IO_WriteOnly | IO_Truncate)){
        log(L_ERROR, "Can't create %s", f.name().local8Bit().data());
        return;
    }
	QTextStream ts(&f);
    for (unsigned i = 0; i < plugins.size(); i++){
        pluginInfo &info = plugins[i];
        ts << "["
		   << info.name
		   << "]\n"
		   << ( info.bDisabled ? DISABLE : ENABLE )
		   << ","
		   << info.base
		   << "\n";
        if (info.plugin){
            QString cfg = info.plugin->getConfig();
            if (cfg.length()){
				ts << cfg.local8Bit() << "\n";
            }
        }
    }

    const int status = f.status();
    const QString errorMessage = f.errorString();
    f.close();
    if (status != IO_Ok) {
        log(L_ERROR, "I/O error during writing to file %s : %s",f.name().local8Bit().data(), errorMessage.local8Bit().data());
        return;
    }

    // rename to normal file
    QFileInfo fileInfo(f.name());
    QString desiredFileName = fileInfo.fileName();
    desiredFileName = desiredFileName.left(desiredFileName.length() - strlen(BACKUP_SUFFIX));
#ifdef WIN32
    fileInfo.dir().remove(desiredFileName);
#endif
    if (!fileInfo.dir().rename(fileInfo.fileName(), desiredFileName)) {
        log(L_ERROR, QString("Can't rename file %s to %s"), fileInfo.fileName().local8Bit().data(), desiredFileName.local8Bit().data());
        return;
    }
}

const unsigned long NO_PLUGIN = (unsigned long)(-1);

void PluginManagerPrivate::reloadState()
{
    m_bLoaded = false;
    for (unsigned i = 0; i < plugins.size(); i++){
        pluginInfo &info = plugins[i];
        if (info.cfg){
            delete info.cfg;
            info.cfg = NULL;
        }
    }
}

void PluginManagerPrivate::loadState()
{
    if (m_bLoaded) return;

    m_bLoaded = true;
    QFile f(user_file(PLUGINS_CONF));

    if (!f.exists()) {
        /* Maybe first start ? */
        QDir dir(user_file(NULL));
        if (!dir.exists()) {
            log(L_WARN, "Creating directory %s",dir.absPath().ascii());
            if (!dir.mkdir(dir.absPath())) {
                log(L_ERROR, "Can't create directory %s",dir.absPath().ascii());
                return;
            }
        }
        if (f.open(IO_WriteOnly))
            f.close();
        else {
            log(L_ERROR, "Can't create %s",f.name().ascii());
            return;
        }
    }

    if (!f.open(IO_ReadOnly)){
        log(L_ERROR, "Can't open %s", f.name().ascii());
        return;
    }

    ConfigBuffer cfg(&f);

    if (cfg.length() <= 0){
        log(L_ERROR, "Can't read %s", f.name().ascii());
        return;
    }

    bool continous=TRUE;
    while(continous) {

        QString section = cfg.getSection();

        if (section.isEmpty())
            return;
        unsigned long i = NO_PLUGIN;
        for (unsigned n = 0; n < plugins.size(); n++)
            if (section == plugins[n].name){
                i = n;
                break;
            }

        if (i == NO_PLUGIN)
            continue;

        pluginInfo &info = plugins[i];
        QString line = cfg.getLine();

        if (line.isEmpty())
            continue;
        QString token = line.section(',',0,0);
        QString dword = line.section(',',1,1);
        if (token == ENABLE){
            info.bDisabled = false;
            info.bFromCfg  = true;
        }
        else if (token == DISABLE){
            info.bDisabled = true;
            info.bFromCfg  = true;
        }
        else {continue;}

        info.base = dword.toLong();

        if (info.base > m_base)
            m_base = info.base;

        if (cfg.dataAvailable()){
            plugins[i].cfg = cfg.getData();
        }
    }
}

bool PluginManagerPrivate::findParam(const QString &p, const QString &descriptor, QString &value)
{
    if (!descriptor.isEmpty()){
        cmds.push_back(p);
        descrs.push_back(descriptor);
    }
    value = QString::null;
    if (p.endsWith(":")){
        unsigned size = p.length();
        for (QStringList::iterator it = args.begin(); it != args.end(); ++it){
            if (!(*it).startsWith(p))
                continue;
            value = (*it).mid(size);
            if (value.length()){
                *it = QString::null;
                return true;
            }
            ++it;
            if (it != args.end()){
                value = (*it);
                *it = QString::null;
                --it;
                *it = QString::null;
                return true;
            } else {
                return true;
            }
        }
    }else{
        QStringList::iterator it = args.find(p);
        if(it != args.end()) {
            value = (*it);
            *it = QString::null;
            return true;
        }
    }
    return false;
}

void PluginManagerPrivate::usage(const QString &err)
{
    QString title = i18n("Bad option %1") .arg(err);
    QString text = i18n("Usage: %1 ") .arg(app_name);
    QString comment;
    QStringList::iterator itc = cmds.begin();
    QStringList::iterator itd = descrs.begin();
    for (; itc != cmds.end(); ++itc, ++itd){
        QString p = *itc;
        bool bParam = false;
        if (p.endsWith(":")){
            bParam = true;
            p = p.left(p.length() - 1);
        }
        text += "[";
        text += p;
        if (bParam)
            text += "<arg>";
        text += "] ";
        comment += "\t";
        comment += p;
        if (bParam)
            comment += "<arg>";
        comment += "\t - ";
        comment += i18n((*itd));
        comment += "\n";
    }
    text += "\n";
    text += comment;
    QMessageBox::critical(NULL, title, text, "Quit", 0);
}

#ifndef WIN32
unsigned long PluginManagerPrivate::execute(const char *prg, const char *arg)
{
    if (*prg == 0)
        return 0;
    QString p = QString::fromLocal8Bit(prg);
    if (p.find("%s") >= 0){
        p.replace(QRegExp("%s"), arg);
    }else{
        p += " ";
        p += QString::fromLocal8Bit(arg);
    }
    log(L_DEBUG, "Exec: %s", (const char*)p.local8Bit());
    QStringList s = QStringList::split(" ", p);
    char **arglist = new char*[s.count()+1];
    unsigned i = 0;
    for ( QStringList::Iterator it = s.begin(); it != s.end(); ++it, i++ ) {
        string arg;
        arg = (*it).local8Bit();
        arglist[i] = strdup(arg.c_str());
    }
    arglist[i] = NULL;
    pid_t child = fork();
    if (child == -1){
        log(L_WARN, "Can't fork: %s", strerror(errno));
        for (char **p = arglist; *p != NULL; p++)
            free(*p);
        delete[] arglist;
        return 0;
    }
    if(!child) {
        execvp(arglist[0], arglist);
        // when we're here an error occured ...
        // a write to the logoutput isn't possible because we haven't
        // these descriptors anymore - so we need printf
        printf("can't execute %s: %s", arglist[0], strerror(errno));
        _exit(-1);
    }
    for (char **p = arglist; *p != NULL; p++)
        free(*p);
    delete[] arglist;
    return child;
}
#endif

void createIcons();
void deleteIcons();

PluginManager::PluginManager(int argc, char **argv)
{
    EventReceiver::initList();
    factory = new SIMSockets;
    contacts = new ContactList;
    FetchManager::manager = new FetchManager;
    createIcons();
    p = new PluginManagerPrivate(argc, argv);
}

void deleteResolver();

PluginManager::~PluginManager()
{
    Event e(EventQuit);
    e.process();
    contacts->clearClients();
    delete p;
    delete FetchManager::manager;
    delete contacts;
    delete factory;
    deleteIcons();
    EventReceiver::destroyList();
    deleteResolver();
}

bool PluginManager::isLoaded()
{
    return !p->m_bAbort;
}

ContactList *PluginManager::contacts = NULL;
SocketFactory *PluginManager::factory = NULL;

}