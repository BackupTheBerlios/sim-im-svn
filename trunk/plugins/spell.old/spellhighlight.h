/***************************************************************************
                          spellhighlight.h  -  description
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

#ifndef _SPELLHIGHLIGHT_H
#define _SPELLHIGHLIGHT_H

#include <stack>

#include <qstring.h>
#include <qstringlist.h>
#include <qsyntaxhighlighter.h>

#include "html.h"

#include "spell.h"

using std::stack;

class SpellHighlighter : public QObject, public QSyntaxHighlighter, public SIM::HTMLParser, public SIM::EventReceiver
{
    Q_OBJECT
public:
    SpellHighlighter(QTextEdit *edit, SpellPlugin *m_plugin);
    ~SpellHighlighter();
signals:
    void check(const QString &);
protected slots:
    void slotMisspelling(const QString &originalWord);
    void slotConfigChanged();
    void reformat();
    void restore();
protected:
    MAP_BOOL m_words;
    int m_paragraph;
    int highlightParagraph( const QString &text, int endStateOfLastPara );
    virtual void text(const QString &text);
    virtual void tag_start(const QString &tag, const list<QString> &options);
    virtual void tag_end(const QString &tag);
    virtual bool processEvent(SIM::Event *e);
    void flush();
    void flushText();
    int m_pos;
    int m_index;
    int m_parag;
    int m_start_word;
    int m_curStart;
    bool m_bError;
    bool m_bDirty;
    bool m_bCheck;
    bool m_bInError;
    bool m_bDisable;
    stack<bool> m_fonts;
    QString		m_curText;
    QString		m_curWord;
    QString     m_word;
    QStringList	m_sug;
    SpellPlugin *m_plugin;
};

#endif
