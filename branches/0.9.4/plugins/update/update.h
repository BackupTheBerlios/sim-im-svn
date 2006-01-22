/***************************************************************************
                          update.h  -  description
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

#ifndef _UPDATE_H
#define _UPDATE_H

#include "simapi.h"
#include "fetch.h"

typedef struct UpdateData
{
    SIM::Data	Time;
} UpdateData;

class UpdatePlugin : public QObject, public SIM::Plugin, public FetchClient, public SIM::EventReceiver
{
    Q_OBJECT
public:
    UpdatePlugin(unsigned, Buffer*);
    virtual ~UpdatePlugin();
protected slots:
    void timeout();
protected:
    unsigned CmdGo;
    bool done(unsigned code, Buffer &data, const char *headers);
    virtual std::string getConfig();
    void *processEvent(SIM::Event*);
    std::string getHeader(const char *name, const char *headers);
    std::string m_url;
    PROP_ULONG(Time);
    UpdateData data;
};

#endif

