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

string Plugin::getConfig()
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

    bool findParam(EventArg *a);
    void usage(const QString &);

    bool create(pluginInfo&);
    bool createPlugin(pluginInfo&);

    void release(pluginInfo&, bool bFree = true);
    void release(const QString &name);
    void release_all(Plugin *to);

    void load(pluginInfo&);
    void load(const QString &name);
    void load_all(EventPluginsLoad *p);

    void saveState();
    void loadState();
    void reloadState();

    pluginInfo *getInfo(const QString &name);
    pluginInfo *getInfo(unsigned n);
    bool setInfo(const QString &name);

#ifndef WIN32
    unsigned long execute(const QString &prg, const QStringList &args);
#endif

    QString app_name;
    QStringList args;
    vector<pluginInfo> plugins;
    QStringList cmds;
    QStringList descrs;

    unsigned m_base;
    bool m_bLoaded;
    bool m_bInInit;
    bool m_bAbort;

    ExecManager	 *m_exec;
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

bool findPluginsInBuildDir(const QDir &appDir, const QString &subdir, QStringList &pluginsList)
{
    QDir pluginsDir(appDir.absFilePath("plugins"));
    log(L_DEBUG, "Searching for plugins in build directory '%s'...", static_cast<const char*>(pluginsDir.path()));
    int count = 0;
    // trunk/plugins/*
    const QStringList pluginDirs = pluginsDir.entryList("*", QDir::Dirs);
    for (QStringList::const_iterator it = pluginDirs.begin(); it != pluginDirs.end(); ++it) {
        const QDir pluginDir( *it );
        // trunk/plugins/$plugin_name/$subdir/$plugin_name.so
        const QString pluginFilename = pluginsDir.filePath(QDir( pluginDir.filePath(subdir) ).
                                                           filePath(pluginDir.dirName() + LTDL_SHLIB_EXT));
        if (QFile::exists(pluginFilename)) {
            log(L_DEBUG, "Found '%s'...", static_cast<const char*>(pluginFilename));
            pluginsList.append(pluginFilename);
            count++;
            }
    }
    log(L_DEBUG, "%i plugins found.", count);
    return count > 0;
}

PluginManagerPrivate::PluginManagerPrivate(int argc, char **argv)
        : EventReceiver(LowPriority)
{
    m_bAbort = false;
    unsigned logLevel = L_ERROR | L_WARN;
    // #ifdef DEBUG // zowers: commented out ifdef to be able to get some output from users even on production systems
    logLevel |= L_DEBUG;
    // #endif
    builtinLogger.reset(new BuiltinLogger(logLevel));

    m_exec = new ExecManager;

    app_name = QString::fromLocal8Bit(*argv);
    for (argv++, argc--; argc > 0; argv++, argc--)
        args.push_back(QString::fromLocal8Bit(*argv));

    m_base = 0;
    m_bLoaded = false;
    m_bInInit = true;

    QStringList pluginsList;
    QDir appDir(qApp->applicationDirPath());
    if ( findPluginsInBuildDir(appDir, ".", pluginsList)                    // cmake location is source dir itself
         || findPluginsInBuildDir(appDir.path() + "/..", ".", pluginsList)  // 
         || findPluginsInBuildDir(appDir, ".libs", pluginsList)             // autotools location is .libs subdur
         || findPluginsInBuildDir(appDir.path() + "/..", ".libs", pluginsList) )
    {
        log(L_DEBUG,"Loading plugins from build directory!");
    } else {

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
    }
    for (QStringList::iterator it = pluginsList.begin(); it != pluginsList.end(); ++it){
        QString f = QFileInfo(*it).fileName();
        int p = f.findRev('.');
        if (p > 0)
            f = f.left(p);
        pluginInfo info;
        info.plugin		 = NULL;
#ifdef WIN32
        info.name        = f.lower();
#else
        info.name		 = f;
#endif
        info.filePath    = *it;
        info.cfg		 = NULL;
        info.bDisabled	 = false;
        info.bNoCreate	 = false;
        info.bFromCfg	 = false;
        info.module		 = NULL;
        info.info		 = NULL;
        info.base		 = 0;
        plugins.push_back(info);
        log(L_DEBUG,"Found plugin %s",info.name.local8Bit().data());
    }
    EventGetPluginInfo ePlugin("_core");
    ePlugin.process();
    const pluginInfo *coreInfo = ePlugin.info();
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
    EventInit eStart;
    eStart.process();
    if (eStart.abortLoading()) {
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
    switch (e->type()){
	case eEventArg: {
        EventArg *a = static_cast<EventArg*>(e);
        return (void*)findParam(a);
	}
    case eEventGetPluginInfo: {
        EventGetPluginInfo *info = static_cast<EventGetPluginInfo*>(e);
        if(info->pluginName().isEmpty())
            info->setInfo(getInfo(info->idx()));
        else
            info->setInfo(getInfo(info->pluginName()));
        return (void*)1;
    }
    case eEventApplyPlugin: {
        EventApplyPlugin *p = static_cast<EventApplyPlugin*>(e);
        return (void*)setInfo(p->pluginName());
    }
    case eEventPluginsUnload: {
        EventPluginsUnload *p = static_cast<EventPluginsUnload*>(e);
        release_all(p->plugin());
        return (void*)1;
    }
    case eEventPluginsLoad: {
        EventPluginsLoad *p = static_cast<EventPluginsLoad*>(e);
        load_all(p);
        return (void*)1;
    }
    case eEventUnloadPlugin: {
        EventUnloadPlugin *p = static_cast<EventUnloadPlugin*>(e);
        release(p->pluginName());
        return (void*)1;
    }
    case eEventLoadPlugin: {
        EventLoadPlugin *p = static_cast<EventLoadPlugin*>(e);
        load(p->pluginName());
        return e->param();
    }
    case eEventSaveState:
        saveState();
        break;
    case eEventGetArgs: {
        EventGetArgs *ga = static_cast<EventGetArgs*>(e);
        ga->setArgs(qApp->argc(), qApp->argv());
        return (void*)1;
    }
#ifndef WIN32
    case eEventExec: {
        EventExec *exec = static_cast<EventExec*>(e);
        exec->setPid(execute(exec->cmd(), exec->args()));
        return (void*)1;
    }
#endif
    default:
        break;
    }
    return NULL;
}

pluginInfo *PluginManagerPrivate::getInfo(const QString &name)
{
    if (name.isEmpty())
        return NULL;
    for (size_t n = 0; n < plugins.size(); n++){
        pluginInfo &info = plugins[n];
        if (info.name == name)
            return &info;
    }
    return NULL;
}

void PluginManagerPrivate::release_all(Plugin *to)
{
    for (size_t n = plugins.size() - 1; n > 0; n--){
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
        QString pluginName = info.filePath;
        if( pluginName[0] != '/' ) {
            pluginName = PLUGIN_PATH;
            pluginName += "/";
            pluginName += info.name;
            pluginName += LTDL_SHLIB_EXT;
        }
#endif
        QString fullName = app_file(pluginName);
        info.module = new QLibrary(fullName);
        if (info.module == NULL)
            fprintf(stderr, "Can't load plugin %s\n", info.name.local8Bit().data());
    }
    if (info.module == NULL)
        return;
    if (info.info == NULL){
        PluginInfo* (*getInfo)() = NULL;
        getInfo = (PluginInfo* (*)()) info.module->resolve("GetPluginInfo");
        if (getInfo == NULL){
            fprintf(stderr, "Plugin %s doesn't have the GetPluginInfo entry\n", info.name.local8Bit().data());
            release(info);
            return;
        }
        info.info = getInfo();
#ifndef WIN32
#ifdef USE_KDE
        if (!(info.info->flags & PLUGIN_KDE_COMPILE)){
            fprintf(stderr, "Plugin %s is compiled without KDE support!\n", info.name.local8Bit().data());
            release(info);
            return;
        }
#else
if (info.info->flags & PLUGIN_KDE_COMPILE){
        fprintf(stderr, "Plugin %s is compiled with KDE support!\n", info.name.local8Bit().data());
        release(info);
        return;
    }
#endif
#endif
    }
}

bool PluginManagerPrivate::create(pluginInfo &info)
{
    if (info.plugin)
        return true;
	EventArg a1("--enable-" + info.name);
    if (findParam(&a1)){
        info.bDisabled = false;
        info.bFromCfg = true;
    }
	EventArg a2("--disable-" + info.name);
    if (findParam(&a2)){
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
    EventPluginChanged e(&info);
    e.process();
    return true;
}

void PluginManagerPrivate::load_all(EventPluginsLoad *p)
{
    if (p->abortLoading()){
        m_bAbort = true;
        qApp->quit();
        return;
    }
    Plugin *from = p->plugin();
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
        EventPluginChanged e(&info);
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

bool PluginManagerPrivate::setInfo(const QString &name)
{
    pluginInfo *info = getInfo(name);
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
        log(L_ERROR, "Can't create %s", (const char*)f.name().local8Bit());
        return;
    }
    for (unsigned i = 0; i < plugins.size(); i++){
        pluginInfo &info = plugins[i];
        QCString line = "[";
        line += QFile::encodeName(info.name);
        line += "]\n";
        line += info.bDisabled ? DISABLE : ENABLE;
        line += ",";
        line += QString::number(info.base);
        line += "\n";
        f.writeBlock(line, line.length());
        if (info.plugin){
            string cfg = info.plugin->getConfig();
            if (cfg.length()){
                f.writeBlock(cfg.c_str(), cfg.length());
                f.writeBlock("\n", 1);
            }
        }
    }

    const int status = f.status();
    const QString errorMessage = f.errorString();
    f.close();
    if (status != IO_Ok) {
        log(L_ERROR, "I/O error during writing to file %s : %s", (const char*)f.name().local8Bit(), (const char*)errorMessage.local8Bit());
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
        log(L_ERROR, "Can't rename file %s to %s", (const char*)fileInfo.fileName().local8Bit(), (const char*)desiredFileName.local8Bit());
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
    if (m_bLoaded)
		return;

    m_bLoaded = true;
    QFile f(user_file(PLUGINS_CONF));

    if (!f.exists()) {
        /* Maybe first start ? */
        QDir dir(user_file(QString::null));
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

    Buffer cfg = f.readAll();

    bool continous=TRUE;
    while(continous) {

        QCString section = cfg.getSection();

        if (section.isEmpty())
            return;
        unsigned long i = NO_PLUGIN;
        for (unsigned n = 0; n < plugins.size(); n++)
            if (section == QFile::encodeName(plugins[n].name).data()){
                i = n;
                break;
            }

        if (i == NO_PLUGIN)
            continue;

        pluginInfo &info = plugins[i];
        QCString line = cfg.getLine();

        if (line.isEmpty())
            continue;
        QCString token = getToken(line, ',');
        if (token == ENABLE){
            info.bDisabled = false;
            info.bFromCfg  = true;
        }
        else if (token == DISABLE){
            info.bDisabled = true;
            info.bFromCfg  = true;
        }
        else
			continue;

        info.base = line.toULong();

        if (info.base > m_base)
            m_base = info.base;

        if (cfg.readPos() < cfg.writePos()){
            plugins[i].cfg = new Buffer;
            plugins[i].cfg->pack(cfg.data(cfg.readPos()), cfg.writePos() - cfg.readPos());
        }
    }
}

bool PluginManagerPrivate::findParam(EventArg *a)
{
	bool bRet = false;
	if (!a->desc().isEmpty()){
        cmds.push_back(a->arg());
        descrs.push_back(a->desc());
    }
    QString value = QString::null;
    if (a->arg().endsWith(":")){
        unsigned size = a->arg().length();
        for (QStringList::iterator it = args.begin(); it != args.end(); ++it){
            if (!(*it).startsWith(a->arg()))
                continue;
            value = (*it).mid(size);
            if (value.length()){
                *it = QString::null;
                bRet = true;
				break;
            }
            ++it;
            if (it != args.end()){
                value = (*it);
                *it = QString::null;
                --it;
                *it = QString::null;
            }
			bRet = true;
			break;
        }
    }else{
        QStringList::iterator it = args.find(a->arg());
        if(it != args.end()) {
            value = (*it);
            *it = QString::null;
            bRet = true;
        }
    }
	a->setValue(value);
    return bRet;
}

void PluginManagerPrivate::usage(const QString &err)
{
    QString title = i18n("Bad option %1").arg(err);
    QString text = i18n("Usage: %1 ").arg(app_name);
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
        text += "[" + p;
        if (bParam)
            text += "<arg>";
        text += "] ";
        comment += "\t" + p;
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
unsigned long PluginManagerPrivate::execute(const QString &prg, const QStringList &args)
{
    if (prg.isEmpty())
        return 0;

    log(L_DEBUG, "Exec: %s", (const char*)prg.local8Bit());
    // FIXME: use QProcess instead!
    QStringList s = args;
    char **arglist = new char*[s.count()+1];
    arglist[0] = strdup((const char*)prg.local8Bit());
    unsigned i = 1;
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
    EventQuit e;
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
