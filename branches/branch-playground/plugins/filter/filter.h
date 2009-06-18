/***************************************************************************
                          filter.h  -  description
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

#ifndef _FILTER_H
#define _FILTER_H

#include <QObject>

#include "cfg.h"
#include "event.h"
#include "plugins.h"
#include "propertyhub.h"

class QWidget;

struct FilterUserData
{
    SIM::Data	SpamList;
};

class QStringList;

class FilterPlugin : virtual public QObject, public SIM::Plugin, public SIM::EventReceiver, public SIM::PropertyHub
{
    Q_OBJECT
public:
    FilterPlugin(unsigned, Buffer *cfg);
    virtual ~FilterPlugin();
protected slots:
    void addToIgnore(void*);
protected:
    unsigned long user_data_id;
    unsigned long CmdIgnoreList;
    unsigned long CmdIgnore;
    unsigned long CmdIgnoreText;
    virtual bool processEvent(SIM::Event *e);
    virtual QWidget *createConfigWindow(QWidget *parent);
    virtual Q3CString getConfig();
    bool checkSpam(const QString &text, const QString &filter);
    void getWords(const QString &text, QStringList &words, bool bPattern);
};

#endif

