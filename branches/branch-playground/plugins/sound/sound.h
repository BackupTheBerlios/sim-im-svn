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

#include "cfg.h"
#include "event.h"
#include "plugins.h"
#include "propertyhub.h"

#include <QObject>
#include <QProcess>
#include <QByteArray>
#ifdef Q_WS_X11
    #include "phonon/mediaobject.h"
    #include "phonon/audiooutput.h"
#endif
#if defined( Q_WS_WIN ) || defined( Q_WS_MAC )
    #include <Phonon/MediaObject>
    #include <Phonon/AudioOutput>
#endif

struct SoundData
{
    SIM::Data	Player;
    SIM::Data	StartUp;
    SIM::Data	FileDone;
    SIM::Data	MessageSent;
};

struct SoundUserData
{
    SIM::Data	Alert;
    SIM::Data	Receive;
    SIM::Data	NoSoundIfActive;
    SIM::Data	Disable;
};

class CorePlugin;
class QTimer;
class QSound;

class SoundPlugin : virtual public SIM::PropertyHub, public SIM::Plugin, public SIM::EventReceiver
{
    Q_OBJECT
public:
    SoundPlugin(unsigned, bool, Buffer*);
    virtual ~SoundPlugin();

	void playSound(const QString& path);

    SIM::SIMEvent EventSoundChanged;

protected:
	QString messageSound(unsigned type, unsigned long contact_id);
    virtual bool processEvent(SIM::Event *e);
    virtual QWidget *createConfigWindow(QWidget *parent);
    friend class SoundConfig;
    friend class SoundUserConfig;

private:
	Phonon::MediaObject* m_media;
	unsigned long CmdSoundDisable;

};

#endif

