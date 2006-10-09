/***************************************************************************
                          cfg.cpp  -  description
                             -------------------
    begin                : Sun Mar 10 2002
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

#include "simapi.h"
#include "sockfactory.h"
#include "socket.h"

#include <errno.h>

#include <qfile.h>
#include <qtoolbar.h>
#include <qmainwindow.h>
#include <qstringlist.h>
#include <qapplication.h>
#include <qdir.h>

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

#ifdef USE_KDE
#include <qapplication.h>
#include <kglobal.h>
#include <kstddirs.h>
#include <kwin.h>
#include "kdeisversion.h"
#endif

#include <map>
using namespace std;

namespace SIM
{

void save_state()
{
    Event e(EventSaveState, NULL);
    e.process();
}

// ______________________________________________________________________________________

#ifdef WIN32

EXPORT bool makedir(char *p)
{
    char *r = strrchr(p, '\\');
    if (r == NULL) return true;
    *r = 0;
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    if(QApplication::winVersion()&Qt::WV_NT_based){
        InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
        sa.lpSecurityDescriptor = &sd;
    }
    CreateDirectoryA(p, &sa);
    DWORD dwAttr = GetFileAttributesA(p);
    if (dwAttr & FILE_ATTRIBUTE_READONLY)
        SetFileAttributesA(p, dwAttr & ~FILE_ATTRIBUTE_READONLY);
    *r = '\\';
    return true;
}

#else

EXPORT bool makedir(char *p)
{
    bool res = true;
    char *r = strrchr(p, '/');
    if (r == NULL) return res;
    *r = 0;
    struct stat st;
    if (stat(p, &st)){
        if (makedir(p)){
            if (mkdir(p, 0700)){
                log(L_ERROR, "Can't create %s: %s", p, strerror(errno));
                res = false;
            }
        }else{
            res = false;
        }
    }else{
        if ((st.st_mode & S_IFMT) != S_IFDIR){
            log(L_ERROR, "%s no directory", p);
            res = false;
        }
    }
    *r = '/';
    return res;
}

#endif

EXPORT QString app_file(const QString &f)
{
    QString app_file_name;
    QString fname = f;
#ifdef WIN32
    if ((fname[1] == ':') || (fname.left(2) == "\\\\"))
        return f;
    WCHAR buff[MAX_PATH];
    GetModuleFileNameW(NULL, buff, MAX_PATH);
    QString b = QString::fromUcs2((unsigned short*)buff);
    int idx = b.findRev('\\');
    if(idx != -1)
        b = b.left(idx+1);
    app_file_name = b;
    if (app_file_name.length() && (app_file_name.right(1) != "\\") && (app_file_name.right(1) != "/"))
        app_file_name += "\\";
#else
    if (fname[0] == '/')
        return f;
#ifdef USE_KDE
    if (qApp){
        QStringList lst = KGlobal::dirs()->findDirs("data", "sim");
        for (QStringList::Iterator it = lst.begin(); it != lst.end(); ++it){
            QFile fi(*it + f);
            if (fi.exists()){
                app_file_name = QDir::convertSeparators(fi.name());
                return app_file_name;
            }
        }
    }
#endif
    app_file_name = PREFIX "/share/apps/sim/";
#endif
    app_file_name += f;
    return QDir::convertSeparators(app_file_name);
}

// ______________________________________________________________________________________

EXPORT QString user_file(const QString &f)
{
    QString res = f;
    Event e(EventHomeDir, &res);
    if (e.process())
        return res;
    return app_file(f);
}

// ______________________________________________________________________________________

EXPORT string number(unsigned n)
{
    char b[32];
    snprintf(b, sizeof(b), "%u", n);
    return string(b);
}

EXPORT string trim(const char *from)
{
    string res;
    if (from == NULL)
        return res;
    res = from;
    int i;
    for (i = 0; i < (int)(res.length()); i++){
        if (res[i] != ' ')
            break;
    }
    if (i)
        res = res.substr(i);
    for (i = res.length() - 1; i >= 0; i--){
        if (res[i] != ' ')
            break;
    }
    if (i < (int)(res.length() - 1))
        res = res.substr(0, i + 1);
    return res;
}

char fromHex(char c)
{
    if ((c >= '0') && (c <= '9')) return (char)(c - '0');
    if ((c >= 'A') && (c <= 'F')) return (char)(c + 10 - 'A');
    if ((c >= 'a') && (c <= 'f')) return (char)(c + 10 - 'a');
    return (char)0;
}

EXPORT string getToken(char const *&p, char c, bool bUnEscape)
{
    string res;
    char const *start = p;
    for (; *p; p++){
        if (*p == c)
            break;
        if (*p == '\\'){
            p++;
            if (*p == 0)
                break;
            if (!bUnEscape)
                continue;
            char c = *p;
            int d = 0;
            switch (c){
            case 'n':
                c = '\n';
                break;
            case 'r':
                c = '\r';
                break;
            case 't':
                c = '\t';
                break;
            case 'x':
                if (p[1] && p[2]){
                    c = (char)((fromHex(p[1]) << 4) + fromHex(p[2]));
                    d = 2;
                }
                break;
            }
            if (start != p - 1){
                string part;
                part.append(start, (unsigned)(p - start - 1));
                res += part;
            }
            res += c;
            start = p + 1 + d;
            continue;
        }
    }
    if (start != p){
        string part;
        part.append(start, (unsigned)(p - start));
        res += part;
    }
    if (*p == c)
        p++;
    return res;
}

EXPORT string getToken(string &from, char c, bool bUnEscape)
{
    const char *p = from.c_str();
    string res = getToken(p, c, bUnEscape);
    from = string(p);
    return res;
}

EXPORT QString quoteChars(const QString &from, const char *chars, bool bQuoteSlash)
{
    QString     res;
    QString     quote_chars;

    quote_chars = chars;
    if (bQuoteSlash) {
        quote_chars += '\\';
    }
    for (int i = 0; i < (int) (from.length ()); i++) {
        QChar       c = from[i];
        if (quote_chars.contains (c)) {
            res += '\\';
        }
        res += c;
    }
    return res;
}

EXPORT QString getToken(QString &from, char c, bool bUnEscape)
{
    QString res;
    int i;
    for (i = 0; i < (int)from.length(); i++){
        if (from[i] == c)
            break;
        if (from[i] == '\\'){
            i++;
            if (i >= (int)from.length())
                break;
            if (!bUnEscape)
                res += "\\";
        }
        res += from[i];
    }
    if (i < (int)from.length()){
        from = from.mid(i + 1);
    }else{
        from = "";
    }
    return res;
}

EXPORT QCString getToken(QCString &from, char c, bool bUnEscape)
{
    QCString res;
    int i;
    for (i = 0; i < (int)from.length(); i++){
        if (from[i] == c)
            break;
        if (from[i] == '\\'){
            i++;
            if (i >= (int)from.length())
                break;
            if (!bUnEscape)
                res += "\\";
        }
        res += from[i];
    }
    if (i < (int)from.length()){
        from = from.mid(i + 1);
    }else{
        from = "";
    }
    return res;
}

// _______________________________________________________________________________________

bool set_ip(Data *p, unsigned long value, const char *host)
{
    IP *ip = p->ip();
    if (value == 0){
        if (ip == NULL)
            return false;
        delete ip;
        p->clear();
        return true;
    }
    if (ip == NULL)
        ip = new IP;
    p->setIP(ip);
    if (ip->ip() == value){
        if (host == NULL)
            ip->resolve();
        return false;
    }
    ip->set(value, host);
    return true;
}

unsigned long get_ip(const Data &p)
{
    const IP *ip = p.ip();
    if (ip)
        return ip->ip();
    return 0;
}

const char *get_host(const Data &p)
{
    const IP *ip = p.ip();
    if (ip && ip->host())
        return ip->host();
    return "";
}

// _______________________________________________________________________________________

EXPORT const QString &get_str(const Data &d, unsigned index)
{
    const Data::STRING_MAP &sm = d.strMap();
    Data::STRING_MAP::const_iterator it = sm.find(index);
    if(it != sm.end())
        return it.data();
    return QString::null;
}

EXPORT void set_str(Data *d, unsigned index, const QString &value)
{
    Data::STRING_MAP &sm = d->strMap();

    sm.replace(index, value);
}

// _______________________________________________________________________________________

EXPORT void free_data(const DataDef *def, void *d)
{
    Data *data = (Data*)d;
    for (; def->name; def++){
        unsigned type = def->type;
        for (unsigned i = 0; i < def->n_values; i++, data++){
            switch (type){
            case DATA_OBJECT:
                delete data->object();
                data->clear();
                break;
            case DATA_IP:
                delete data->ip();
                data->clear();
                break;
            case DATA_STRUCT:
                free_data((DataDef*)(def->def_value), data);
                i    += (def->n_values - 1);
                data += (def->n_values - 1);
                break;
            default:
                data->clear();
                break;
            }
        }
    }
}

void init_data(const DataDef *d, Data *data)
{
    for (const DataDef *def = d; def->name; def++){
        for (unsigned i = 0; i < def->n_values; i++, data++){
			data->clear();
            data->setName(def->name);
            data->setType(def->type);
            switch (def->type){
            case DATA_STRING:
                // when all our sources are utf-8, use QString::fromUtf8() here!
                data->str() = def->def_value ? QString(def->def_value) : QString::null;
                break;
            case DATA_STRLIST: {
                // this breaks on non latin1 defaults!
                QStringList sl = QStringList::split(',',def->def_value);
                Data::STRING_MAP sm;
                for(unsigned i = 0; i < sl.count(); i++) {
                    sm.insert(i, sm[(int)i]);
                }
                data->strMap() = sm;
            }
            case DATA_UTF:
                if (def->def_value){
                    data->str() = i18n(def->def_value);
                }
                break;
            case DATA_ULONG:
                data->asULong() = (unsigned long)(def->def_value);
                break;
            case DATA_LONG:
                data->asLong() = (long)(def->def_value);
                break;
            case DATA_BOOL:
                data->asBool() = (def->def_value != NULL);
                break;
            case DATA_OBJECT:
                data->setObject(NULL);
                break;
            case DATA_IP:
                data->setIP(NULL);
                break;
            case DATA_BINARY:
                data->asBinary() = QByteArray();
                break;
            case DATA_STRUCT:
                init_data((DataDef*)(def->def_value), data);
                data += (def->n_values - 1);
                i += (def->n_values - 1);
                break;
            default:
                break;
            }
        }
    }
}

const DataDef *find_key(const DataDef *def, const char *name, unsigned &offs)
{
    for (; def->name; def++){
        if (!strcmp(def->name, name))
            return def;
        if (def->type == DATA_STRUCT){
            unsigned save_offs = offs;
            const DataDef *res = find_key((DataDef*)(def->def_value), name, offs);
            if (res)
                return res;
            offs = save_offs;
        }
        offs += def->n_values;
    }
    return NULL;
}

EXPORT void load_data(const DataDef *d, void *_data, Buffer *cfg)
{
    Data *data = (Data*)_data;
    init_data(d, data);
    if (cfg == NULL)
        return;
    unsigned read_pos = cfg->readPos();
    char *line;
    for (;;){
        line = cfg->getLine();
        if (line == NULL)
            break;
        char *p = strchr(line, '=');
        if (p == NULL)
            continue;
        *p = 0;
        const char *value = p + 1;
        unsigned offs = 0;
        const DataDef *def = find_key(d, line, offs);
        *p = '=';
        if (def == NULL)
            continue;
        unsigned i;
        string v;
        Data *ld = data + offs;
        ld->setType(def->type);
        switch (def->type){
        case DATA_IP:
            p = (char*) strchr(value, ',');
            if (p){
                *p = 0;
                p++;
            }
            set_ip(ld, inet_addr(value), p);
            if (p)
                p[-1] = ',';
            break;
        case DATA_STRLIST:
            i = strtoul(value, NULL, 10);
            if (i == 0)
                break;
            value = strchr(value, '\"');
            if (value == NULL){
                set_str(ld, i, "\0");
                break;
            }
            value++;
            set_str(ld, i, getToken(value, '\"').c_str());
            break;
        case DATA_UTFLIST:
            i = strtoul(value, NULL, 10);
            if (i == 0)
                break;
            value = strchr(value, '\"');
            if (value == NULL){
                set_str(ld, i, "\0");
                break;
            }
            value++;
            v = getToken(value, '\"');
            if (*value == 'u'){
                set_str(ld, i, v.c_str());
            }else{
                QString s = QString::fromLocal8Bit(v.c_str());
                set_str(ld, i, s);
            }
            break;
        case DATA_UTF:
            for (i = 0; i < def->n_values; ld++){
                value = strchr(value, '\"');
                if (value == NULL)
                    break;
                value++;
                v = getToken(value, '\"');
                if (*value == 'u'){
                    ld->str() = QString::fromUtf8(v.c_str());
                }else{
                    ld->str() = QString::fromLocal8Bit(v.c_str());
                }
                i++;
                value = strchr(value, ',');
                if (value == NULL)
                    break;
                value++;
            }
            break;
        case DATA_STRING:
            for (i = 0; i < def->n_values; ld++){
                value = strchr(value, '\"');
                if (value == NULL)
                    break;
                value++;
                v = getToken(value, '\"');
                if (*value == 'u'){
                    ld->str() = QString::fromUtf8(v.c_str());
                }else{
                    ld->str() = QString::fromLocal8Bit(v.c_str());
                }
                i++;
                value = strchr(value, ',');
                if (value == NULL)
                    break;
                value++;
            }
            break;
        case DATA_LONG:
            for (i = 0; i < def->n_values; ld++){
                if (*value != ',')
                    ld->asLong() = atol(value);
                value = strchr(value, ',');
                i++;
                if (value == NULL)
                    break;
                value++;
            }
            break;
        case DATA_ULONG:
            for (i = 0; i < def->n_values; ld++){
                if (*value != ',')
                    ld->asULong() = strtoul(value, NULL, 10);
                value = strchr(value, ',');
                if (value == NULL)
                    break;
                value++;
            }
            break;
        case DATA_BOOL:
            for (i = 0; i < def->n_values; i++, ld++){
                p = (char *)strchr(value, ',');
                if (p)
                    *p = 0;
                if (*value){
                    if (!strcasecmp(value, "false") || !strcmp(value, "0")){
                        ld->asBool() = false;
                    }else{
                        ld->asBool() = true;
                    }
                }
                value = p;
                if (value == NULL)
                    break;
                value++;
            }
            break;
	default:
	    break;
        }
    }
    cfg->setReadPos(read_pos);
}

static char toHex(char c)
{
    c &= 0x0F;
    if (c < 10) return (char)(c + '0');
    return (char)(c - 10 + 'a');
}

static string quoteString(const char *str)
{
    Buffer quoted;
    if (str)
        quoted.init(strlen(str) + 5);
    quoted << "\"";
    if (str){
        for (unsigned char *p = (unsigned char*)str; *p; p++){
            switch (*p){
            case '\\':
                quoted << "\\\\";
                break;
            case '\r':
                break;
            case '\n':
                quoted << "\\n";
                break;
            case '\"':
                quoted << "\\\"";
                break;
            default:
                if (*p >= ' '){
                    quoted << *p;
                }else if (*p){
                    quoted << "\\x";
                    quoted << toHex((char)(*p >> 4));
                    quoted << toHex(*p);
                }
            }
        }
    }
    quoted << "\"" << (char)0;
    return quoted.data();
}

EXPORT string save_data(const DataDef *def, void *_data)
{
    Data *data = (Data*)_data;
    string res;
    for (; def->name; def++){
        string value;
        bool bSave = false;
        unsigned i;
        if (def->type == DATA_STRUCT){
            string s = save_data((DataDef*)(def->def_value), data);
            if (s.length()){
                if (res.length())
                    res += "\n";
                res += s;
            }
        }else  if (*def->name){
            Data *ld = data;
            switch (def->type){
            case DATA_IP:{
                    IP *p = ld->ip();
                    if (p && p->ip()){
                        struct in_addr inaddr;
                        inaddr.s_addr = p->ip();
                        value = inet_ntoa(inaddr);
                        const char *host = p->host();
                        if (host && *host){
                            value += ",";
                            value += host;
                        }
                        bSave = true;
                    }
                    break;
                }
            case DATA_STRLIST:{
                    const Data::STRING_MAP &p = ld->strMap();
                    if (p.count()){
                        for (Data::STRING_MAP::ConstIterator it = p.begin(); it != p.end(); ++it){
                            if (res.length())
                                res += "\n";
                            res += def->name;
                            res += "=";
                            res += number(it.key());
                            res += ",";
                            QString s = it.data();
                            QCString ls = s.local8Bit();
                            if (QString::fromLocal8Bit(ls) == s){
                                res += quoteString((const char*)ls);
                            }else{
                                res += quoteString((const char*)(s.utf8()));
                                res += "u";
                            }
                        }
                    }
                    break;
                }
            case DATA_UTFLIST:{
                    const Data::STRING_MAP &p = ld->strMap();
                    if (p.count()){
                        for (Data::STRING_MAP::ConstIterator it = p.begin(); it != p.end(); ++it){
                            if (res.length())
                                res += "\n";
                            res += def->name;
                            res += "=";
                            res += number(it.key());
                            res += ",";
                            QString s = it.data();
                            QCString ls = s.local8Bit();
                            if (QString::fromLocal8Bit(ls) == s){
                                res += quoteString((const char*)ls);
                            }else{
                                res += quoteString((const char*)(s.utf8()));
                                res += "u";
                            }
                        }
                    }
                    break;
                }
            case DATA_STRING:{
                    for (i = 0; i < def->n_values; i++, ld++){
                        QString &str = ld->str();
                        if(str.startsWith("Peter"))
                            log(L_DEBUG, "Peter!");
                        if (value.length())
                            value += ",";
                        if (def->def_value){
                            if (str != QString::fromAscii(def->def_value)){
                                bSave = true;
                            }
                        }else{
                            if (str.length()){
                                bSave = true;
                            }
                        }
                        if (bSave){
                            QCString ls = str.local8Bit();
                            if (QString::fromLocal8Bit(ls) == str){
                                value += quoteString((const char*)ls);
                            }else{
                                value += quoteString((const char*)(str.utf8()));
                                value += "u";
                            }
                        }
                    }
                    break;
                }
            case DATA_UTF:{
                    for (i = 0; i < def->n_values; i++, ld++){
                        QString &str = ld->str();
                        if(str.startsWith("Peter"))
                            log(L_DEBUG, "Peter!");
                        if (value.length())
                            value += ",";
                        if (def->def_value){
                            if (str != i18n(def->def_value))
                                bSave = true;
                        }else{
                            if (str.length())
                                bSave = true;
                        }
                        if (bSave){
                            QCString ls = str.local8Bit();
                            if (QString::fromLocal8Bit(ls) == str){
                                value += quoteString((const char*)ls);
                            }else{
                                value += quoteString((const char*)(str.utf8()));
                                value += "u";
                            }
                        }
                    }
                    break;
                }
            case DATA_BOOL:{
                    for (i = 0; i < def->n_values; i++, ld++){
                        bool p = ld->toBool();
                        if (value.length())
                            value += ",";
                        if (p != (def->def_value != 0)){
                            if (p){
                                value += "true";
                            }else{
                                value += "false";
                            }
                            bSave = true;
                        }
                    }
                    break;
                }
            case DATA_LONG:{
                    for (i = 0; i < def->n_values; i++, ld++){
                        long p = ld->toLong();
                        if (value.length())
                            value += ",";
                        if (p != (long)(def->def_value)){
                            char b[32];
                            snprintf(b, sizeof(b), "%li", p);
                            value += b;
                            bSave = true;
                        }
                    }
                    break;
                }
            case DATA_ULONG:{
                    for (i = 0; i < def->n_values; i++, ld++){
                        unsigned long p = ld->toULong();
                        if (value.length())
                            value += ",";
                        if (p != (unsigned long)(def->def_value)){
                            char b[32];
                            snprintf(b, sizeof(b), "%lu", p);
                            value += b;
                            bSave = true;
                        }
                    }
                    break;
                }
            default:
                break;
            }
            if (bSave){
                if (res.length())
                    res += "\n";
                res += def->name;
                res += "=";
                res += value;
            }
        }
        data += def->n_values;
    }
    return res;
}

// ______________________________________________________________________________________

#ifdef WIN32
#ifndef SM_CYSMCAPTION
#define SM_CYSMCAPTION          51
#endif
#endif

EXPORT void saveGeometry(QWidget *w, Geometry geo)
{
    if (w == NULL)
        return;
    QPoint pos = w->pos();
    QSize size = w->size();
    geo[LEFT].asLong()   = pos.x();
    geo[TOP].asLong()    = pos.y();
    geo[WIDTH].asLong()  = size.width();
    geo[HEIGHT].asLong() = size.height();
#ifdef WIN32
    if (GetWindowLongA(w->winId(), GWL_EXSTYLE) & WS_EX_TOOLWINDOW){
        int dc = GetSystemMetrics(SM_CYCAPTION);
        int ds = GetSystemMetrics(SM_CYSMCAPTION);
        geo[1].asLong() += dc - ds;
        geo[3].asLong() -= (dc - ds) * 2;
    }
#endif
#ifdef USE_KDE
#if KDE_IS_VERSION(3,2,0)
    KWin::WindowInfo info = KWin::windowInfo(w->winId());
    geo[4].asLong() = info.desktop();
    if (info.onAllDesktops())
        geo[4].asLong() = -1;
#else
    KWin::Info info = KWin::info(w->winId());
    geo[4].asLong() = info.desktop;
    if (info.onAllDesktops)
        geo[4].asLong() = -1;
#endif
#endif
}

EXPORT void restoreGeometry(QWidget *w, Geometry geo, bool bPos, bool bSize)
{
    if (w == NULL)
        return;
    QRect rc = screenGeometry();
    if (geo[WIDTH].toLong() > rc.width())
        geo[WIDTH].asLong() = rc.width();
    if (geo[HEIGHT].toLong() > rc.height())
        geo[HEIGHT].asLong() = rc.height();
    if (geo[LEFT].toLong() + geo[WIDTH].toLong() > rc.right())
        geo[LEFT].asLong() = rc.left() - geo[WIDTH].asLong();
    if (geo[TOP].toLong() + geo[HEIGHT].toLong() > rc.bottom())
        geo[TOP].asLong() = rc.top() - geo[HEIGHT].asLong();
    if (geo[LEFT].toLong() < rc.left())
        geo[LEFT].asLong() = rc.left();
    if (geo[TOP].toLong() < rc.top())
        geo[TOP].asLong() = rc.top();
    if (bPos)
        w->move(geo[LEFT].toLong(), geo[TOP].toLong());
    if (bSize)
        w->resize(geo[WIDTH].asLong(), geo[HEIGHT].asLong());
#ifdef USE_KDE
    if (geo[4].toLong() == -1){
        KWin::setOnAllDesktops(w->winId(), true);
    }else{
        KWin::setOnAllDesktops(w->winId(), false);
        KWin::setOnDesktop(w->winId(), geo[4].toLong());
    }
#endif
}

const long SAVE_STATE = -1;

EXPORT void saveToolbar(QToolBar *bar, Data state[7])
{
    for(int i = 0; i < 7; i++)
        state[i].clear();
    if (bar == NULL)
        return;
    QMainWindow *main = NULL;
    for (QWidget *w = bar->parentWidget(); w; w = w->parentWidget()){
        if (w->inherits("QMainWindow")){
            main = static_cast<QMainWindow*>(w);
            break;
        }
    }
    if (main == NULL)
        return;
    QMainWindow::ToolBarDock dock;
    int  index;
    bool nl;
    int  extraOffset;
    main->getLocation(bar, dock, index, nl, extraOffset);
    state[0].asLong() = SAVE_STATE;
    state[1].asLong() = (long)dock;
    state[2].asLong() = index;
    state[3].asLong() = nl ? 1 : 0;
    state[4].asLong() = extraOffset;
    if (dock == QMainWindow::TornOff){
        QPoint pos = bar->geometry().topLeft();
        state[5].asLong() = pos.x();
        state[6].asLong() = pos.y();
    }
}

EXPORT void restoreToolbar(QToolBar *bar, Data state[7])
{
    if (bar == NULL)
        return;
    if (state[0].asLong() != SAVE_STATE){
        if (state[1].asLong() == 0)
            state[1].asLong() = (unsigned)(QMainWindow::Top);
        state[2].asLong() = 0;
        state[3].asLong() = 0;
        state[4].asLong() = SAVE_STATE;
        state[5].asLong() = 0;
        state[6].asLong() = 0;
    }
    QMainWindow *main = NULL;
    for (QWidget *w = bar->parentWidget(); w; w = w->parentWidget()){
        if (w->inherits("QMainWindow")){
            main = static_cast<QMainWindow*>(w);
            break;
        }
    }
    if (main == NULL)
        return;
    QMainWindow::ToolBarDock dock = (QMainWindow::ToolBarDock)state[1].asLong();
    main->moveToolBar(bar, dock, state[2].asLong() != 0, state[3].asLong() != 0, state[4].asLong());
    if (dock == QMainWindow::TornOff)
        bar->move(state[5].asLong(), state[6].asLong());
}

// ----------------------------
// class Data
// ----------------------------
class EXPORT DataPrivate {
public:
    unsigned long        m_dataAsValue;
    bool                 m_dataAsBool;
    QString             *m_dataAsQString;
    Data::STRING_MAP    *m_dataAsQStringMap;
    QObject             *m_dataAsObject;
    IP                  *m_dataAsIP;
    QByteArray          *m_dataAsBinary; 
    DataPrivate() : m_dataAsValue(0), m_dataAsBool(false), m_dataAsQString(NULL),
                    m_dataAsQStringMap(NULL), m_dataAsObject(NULL), m_dataAsIP(NULL),
                    m_dataAsBinary(NULL) {}
};

Data::Data()
 : m_type(DATA_UNKNOWN), m_name("unknown"), data(NULL)
{
    clear();
}

Data::Data(const Data &d)
 : data(NULL)
{
    *this = d;
}

Data &Data::operator =(const Data &d)
{
    clear();
    m_name = d.m_name;
    m_type = d.m_type;
    switch(m_type) {
        case DATA_STRING:
            this->str() = d.str();
            break;
        case DATA_LONG:
        case DATA_ULONG:
            data->m_dataAsValue = d.data->m_dataAsValue;
            break;
        case DATA_BOOL:
            data->m_dataAsBool = d.data->m_dataAsBool;
            break;
        case DATA_STRMAP:
            this->strMap() = d.strMap();
            break;
        case DATA_IP:
            data->m_dataAsIP = d.data->m_dataAsIP;
            break;
        case DATA_OBJECT:
            data->m_dataAsObject = d.data->m_dataAsObject;
            break;
        case DATA_BINARY:
            this->asBinary() = d.toBinary();
            break;
        case DATA_UNKNOWN:
        case DATA_STRUCT:
        default:
            break;
    }
    return *this;
}

void Data::clear(bool bNew)
{
    if(data) {
        delete data->m_dataAsQString;
        delete data->m_dataAsQStringMap;
        delete data->m_dataAsBinary;
        delete data;
    }
    data = bNew ? new DataPrivate : NULL;
}

const QString &Data::str() const
{
    checkType(DATA_STRING);
    if(!data->m_dataAsQString)
        data->m_dataAsQString = new QString();
    return *data->m_dataAsQString;
}

QString &Data::str()
{
    checkType(DATA_STRING);
    if(!data->m_dataAsQString)
        data->m_dataAsQString = new QString();
    return *data->m_dataAsQString;
}

bool Data::setStr(const QString &s)
{
    checkType(DATA_STRING);
    if(data->m_dataAsQString && s == *data->m_dataAsQString)
        return false;
    if(!data->m_dataAsQString)
        data->m_dataAsQString = new QString(s);
    else
        *data->m_dataAsQString = s;
    return true;
}

const Data::STRING_MAP &Data::strMap() const
{
    checkType(DATA_STRMAP);
    if(!data->m_dataAsQStringMap)
        data->m_dataAsQStringMap = new STRING_MAP();
    return *data->m_dataAsQStringMap;
}

Data::STRING_MAP &Data::strMap()
{
    checkType(DATA_STRMAP);
    if(!data->m_dataAsQStringMap)
        data->m_dataAsQStringMap = new STRING_MAP();
    return *data->m_dataAsQStringMap;
}

bool Data::setStrMap(const STRING_MAP &s)
{
    checkType(DATA_STRMAP);
    // ... 
    if(!data->m_dataAsQStringMap)
        data->m_dataAsQStringMap = new STRING_MAP(s);
    else
        *data->m_dataAsQStringMap = s;
    return true;
}

long Data::toLong() const
{
    checkType(DATA_LONG);
    return data->m_dataAsValue;
}

long &Data::asLong()
{
    checkType(DATA_LONG);
    return (long&)data->m_dataAsValue;
}

bool Data::setLong(long d)
{
    checkType(DATA_LONG);
    if(d == (long)data->m_dataAsValue)
        return false;
    data->m_dataAsValue = (unsigned long)d;
    return true;
}

unsigned long Data::toULong() const
{
    checkType(DATA_ULONG);
    return data->m_dataAsValue;
}

unsigned long &Data::asULong()
{
    checkType(DATA_ULONG);
    return data->m_dataAsValue;
}
bool Data::setULong(unsigned long d)
{
    checkType(DATA_ULONG);
    if(d == data->m_dataAsValue)
        return false;
    data->m_dataAsValue = d;
    return true;
}

bool Data::toBool() const
{
    checkType(DATA_BOOL);
    return data->m_dataAsBool;
}

bool &Data::asBool()
{
    checkType(DATA_BOOL);
    return data->m_dataAsBool;
}

bool Data::setBool(bool d)
{
    checkType(DATA_BOOL);
    if(d == data->m_dataAsBool)
        return false;
    data->m_dataAsBool = d;
    return true;
}

const QObject* Data::object() const
{
    checkType(DATA_OBJECT);
    return data->m_dataAsObject;
}

QObject* Data::object()
{
    checkType(DATA_OBJECT);
    return data->m_dataAsObject;
}

bool Data::setObject(const QObject *d)
{
    checkType(DATA_OBJECT);
    if(d == data->m_dataAsObject)
        return false;
    data->m_dataAsObject = const_cast<QObject*>(d);
    return true;
}

const QByteArray &Data::toBinary() const
{
    checkType(DATA_BINARY);
    if(!data->m_dataAsBinary)
        data->m_dataAsBinary = new QByteArray();
    return *data->m_dataAsBinary;
}

QByteArray &Data::asBinary()
{
    checkType(DATA_BINARY);
    if(!data->m_dataAsBinary)
        data->m_dataAsBinary = new QByteArray();
    return *data->m_dataAsBinary;
}

bool Data::setBinary(const QByteArray &d)
{
    checkType(DATA_BINARY);
    if(data->m_dataAsBinary && d == *data->m_dataAsBinary)
        return false;
    if(!data->m_dataAsBinary)
        data->m_dataAsBinary = new QByteArray(d);
    else
        *data->m_dataAsBinary = d;
    return true;
}

const IP* Data::ip() const
{
    checkType(DATA_IP);
    return data->m_dataAsIP;
}

IP* Data::ip()
{
    checkType(DATA_IP);
    return data->m_dataAsIP;
}

bool Data::setIP(const IP *d)
{
    checkType(DATA_IP);
    if(d == data->m_dataAsIP)
        return false;
    data->m_dataAsIP = const_cast<IP*>(d);
    return true;
}

static const char *dataType2Name(DataType type)
{
    switch(type) {
        case DATA_UNKNOWN:
            return "uninitialized";
        case DATA_STRING:
            return "string";
        case DATA_LONG:
            return "long";
        case DATA_ULONG:
            return "ulong";
        case DATA_BOOL:
            return "bool";
        case DATA_STRMAP:
            return "stringmap";
        case DATA_IP:
            return "ip";
        case DATA_STRUCT:
            return "struct";
        case DATA_OBJECT:
            return "object";
        case DATA_BINARY:
            return "binary";
    }
    return "unknown";
}

void Data::checkType(DataType type) const
{
    DataType myType = m_type;
    if(myType == DATA_UTFLIST)
        myType = DATA_STRLIST;
    if(myType == DATA_UTF)
        myType = DATA_STRING;
    if(myType != type) {
        log( L_ERROR, "Using wrong data type %s instead %s for %s!",
             dataType2Name(type), dataType2Name(m_type), m_name.isEmpty() ? "??" : m_name.latin1() );
//        assert(0);
    }
}

void Data::setName(const QString &name)
{
    if(!name.isEmpty() && (m_name.isEmpty() || m_name == "unknown"))
        m_name = name;
}

const QString &Data::name() const
{
    return m_name;
}

void Data::setType(DataType type)
{
    m_type = type;
}

DataType Data::type() const
{
    return m_type;
}

}   // namespace SIM
