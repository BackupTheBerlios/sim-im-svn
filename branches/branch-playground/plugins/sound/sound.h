/***************************************************************************
                          sound.h  -  description
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

#ifndef _SOUND_H
#define _SOUND_H

#include "simapi.h"

typedef struct SoundData
{
#ifdef USE_KDE
    SIM::Data	UseArts;
#endif
    SIM::Data	Player;
    SIM::Data	StartUp;
    SIM::Data	FileDone;
    SIM::Data	MessageSent;
} SoundData;

typedef struct SoundUserData
{
    SIM::Data	Alert;
    SIM::Data	Receive;
    SIM::Data	NoSoundIfActive;
    SIM::Data	Disable;
} SoundUserData;

class CorePlugin;
class QTimer;
class QSound;

class SoundPlugin : public QObject, public SIM::Plugin, public SIM::EventReceiver
{
    Q_OBJECT
public:
    SoundPlugin(unsigned, bool, ConfigBuffer*);
    virtual ~SoundPlugin();
#ifdef USE_KDE
    PROP_BOOL(UseArts);
#endif
    PROP_STR(Player);
    PROP_STR(StartUp);
    PROP_STR(FileDone);
    PROP_STR(MessageSent);
    unsigned long CmdSoundDisable;
    unsigned EventSoundChanged;
protected slots:
    void checkSound();
    void childExited(int, int);
protected:
    unsigned long user_data_id;
    virtual void *processEvent(SIM::Event*);
    virtual QString getConfig();
    virtual QWidget *createConfigWindow(QWidget *parent);
    QString fullName(const QString&);
    QString messageSound(unsigned type, SoundUserData *data);
    void playSound(const QString&);
    void processQueue();
    QString		    m_current;
    QStringList 	m_queue;
    QSound			*m_sound;
    QTimer			*m_checkTimer;
#ifndef WIN32
    long             m_player;
#endif
    SoundData	data;
    CorePlugin	*core;
    bool	    m_bChanged;
    friend class SoundConfig;
    friend class SoundUserConfig;
};

#endif
