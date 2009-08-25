/* This file is part of the KDE libraries
   Copyright (C) 2000 Daniel M. Duley <mosfet@kde.org>
   Copyright (C) 2002 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kpopup.h"

#ifndef USE_KDE

#include <QCursor>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>
#include <QStyle>
#include "log.h"
//Added by qt3to4:
#include <QContextMenuEvent>
#include <QStyleOptionHeader>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <Q3PopupMenu>
#include <QHideEvent>
#include <QKeyEvent>
#include <QMenuItem>

KPopupTitle::KPopupTitle(QWidget *parent, const char *name)
    : QWidget(parent, name)
{
    setMinimumSize(16, fontMetrics().height()+8);
}

void KPopupTitle::setTitle(const QString &text, const QPixmap *icon)
{
    titleStr = text;
    if (icon)
        miniicon = *icon;
    else
        miniicon.resize(0, 0);

    calcSize();
}

void KPopupTitle::setText( const QString &text )
{
    titleStr = text;
    calcSize();
}

void KPopupTitle::setIcon( const QPixmap &pix )
{
    miniicon = pix;
    calcSize();
}

void KPopupTitle::calcSize()
{
    QFont f = font();
    f.setBold(true);
    int w = miniicon.width()+QFontMetrics(f).width(titleStr);
    int h = QMAX( fontMetrics().height(), miniicon.height() );
    setMinimumSize( w+16, h+8 );
}

void KPopupTitle::paintEvent(QPaintEvent *)
{
	QRect r(rect());
	QPainter p(this);
	//QStyleOptionHeader option;
	//option.initFrom(this);
	//style()->drawPrimitive(QStyle::PE_HeaderSection, &p, r, palette().active());

	if (!miniicon.isNull())
		p.drawPixmap(4, (r.height()-miniicon.height())/2, miniicon);

	if (!titleStr.isNull())
	{
		p.setPen(palette().active().text());
		QFont f = p.font();
		f.setBold(true);
		p.setFont(f);
		if(!miniicon.isNull())
		{
			p.drawText(miniicon.width()+8, 0, width()-(miniicon.width()+8),
					height(), Qt::AlignLeft | Qt::AlignVCenter | Qt::SingleLine,
					titleStr);
		}
		else
		{
			p.drawText(0, 0, width(), height(),
					Qt::AlignCenter | Qt::SingleLine, titleStr);
		}
	}
}

QSize KPopupTitle::sizeHint() const
{
    return minimumSize();
}

class KPopupMenu::KPopupMenuPrivate
{
public:
    KPopupMenuPrivate ()
        : noMatches(false)
        , shortcuts(false)
        , autoExec(false)
        , lastHitIndex(-1)
        , state(Qt::NoButton)
        , m_ctxMenu(0)
    {}

    ~KPopupMenuPrivate ()
    {
        delete m_ctxMenu;
    }

    QString m_lastTitle;

    // variables for keyboard navigation
    QTimer clearTimer;

    bool noMatches : 1;
    bool shortcuts : 1;
    bool autoExec : 1;

    QString keySeq;
    QString originalText;

    int lastHitIndex;
    Qt::ButtonState state;

    // support for RMB menus on menus
    Q3PopupMenu* m_ctxMenu;
    static bool s_continueCtxMenuShow;
    static int s_highlightedItem;
    static KPopupMenu* s_contextedMenu;
};

int KPopupMenu::KPopupMenuPrivate::s_highlightedItem(-1);
KPopupMenu* KPopupMenu::KPopupMenuPrivate::s_contextedMenu(0);
bool KPopupMenu::KPopupMenuPrivate::s_continueCtxMenuShow(true);

KPopupMenu::KPopupMenu(QWidget *parent, const char *name)
    : Q3PopupMenu(parent, name)
{
    d = new KPopupMenuPrivate;
    resetKeyboardVars();
    connect(&(d->clearTimer), SIGNAL(timeout()), SLOT(resetKeyboardVars()));
}

KPopupMenu::~KPopupMenu()
{
    if (KPopupMenuPrivate::s_contextedMenu == this)
    {
        KPopupMenuPrivate::s_contextedMenu = 0;
        KPopupMenuPrivate::s_highlightedItem = -1;
    }

    delete d;
}

int KPopupMenu::insertTitle(const QString &text, int id, int index)
{
	int ret = insertItem(text, id, index);
	setItemEnabled(ret, false);
	return ret;
}

int KPopupMenu::insertTitle(const QPixmap &icon, const QString &text, int id,
                            int index)
{
    int ret = insertItem(icon, text, id, index);
    setItemEnabled(ret, false);
    return ret;
}

void KPopupMenu::changeTitle(int id, const QString &text)
{
    QMenuItem *item = findItem(id);
    if(item)
	{
        item->setText(text);
    }
}

void KPopupMenu::changeTitle(int id, const QPixmap &icon, const QString &text)
{
    QMenuItem *item = findItem(id);
    if(item)
	{
		item->setText(text);
		item->setIcon(icon);
    }
}

QString KPopupMenu::title(int id) const
{
    if(id == -1) // obsolete
        return d->m_lastTitle;
    QMenuItem *item = findItem(id);
    if(item){
		/*
        if(item->widget())
            return ((KPopupTitle *)item->widget())->title();
        else
            qWarning("KPopupMenu: title() called with non-title id %d.", id);
			*/
		return item->text();
    }
    else
        qWarning("KPopupMenu: title() called with invalid id %d.", id);
    return QString::null;
}

QPixmap KPopupMenu::titlePixmap(int id) const
{
    QMenuItem *item = findItem(id);
    if(item)
	{
		/*
        if(item->widget())
            return ((KPopupTitle *)item->widget())->icon();
        else
            qWarning("KPopupMenu: titlePixmap() called with non-title id %d.", id);
		*/
		return item->icon().pixmap();
    }
    else
        qWarning("KPopupMenu: titlePixmap() called with invalid id %d.", id);
    QPixmap tmp;
    return tmp;
}

/**
 * This is re-implemented for keyboard navigation.
 */
void KPopupMenu::closeEvent(QCloseEvent*e)
{
    if (d->shortcuts)
        resetKeyboardVars();
    Q3PopupMenu::closeEvent(e);
}

void KPopupMenu::activateItemAt(int index)
{
    d->state = Qt::NoButton;
    Q3PopupMenu::activateItemAt(index);
}

Qt::ButtonState KPopupMenu::state() const
{
    return d->state;
}

void KPopupMenu::keyPressEvent(QKeyEvent* e)
{
    d->state = Qt::NoButton;
    if (!d->shortcuts) {
        // continue event processing by Qpopup
        //e->ignore();
        d->state = e->state();
        Q3PopupMenu::keyPressEvent(e);
        return;
    }

    int i = 0;
    bool firstpass = true;
    QString keyString = e->text();

    // check for common commands dealt with by QPopup
    int key = e->key();
    if (key == Qt::Key_Escape || key == Qt::Key_Return || key == Qt::Key_Enter
            || key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Left
            || key == Qt::Key_Right || key == Qt::Key_F1) {

        resetKeyboardVars();
        // continue event processing by Qpopup
        //e->ignore();
        d->state = e->state();
        Q3PopupMenu::keyPressEvent(e);
        return;
    } else if ( key == Qt::Key_Shift || key == Qt::Key_Control || key == Qt::Key_Alt || key == Qt::Key_Meta )
	return Q3PopupMenu::keyPressEvent(e);

    // check to see if the user wants to remove a key from the sequence (backspace)
    // or clear the sequence (delete)
    if (!d->keySeq.isNull()) {

        if (key == Qt::Key_Backspace) {

            if (d->keySeq.length() == 1) {
                resetKeyboardVars();
                return;
            }

            // keep the last sequence in keyString
            keyString = d->keySeq.left(d->keySeq.length() - 1);

            // allow sequence matching to be tried again
            resetKeyboardVars();

        } else if (key == Qt::Key_Delete) {
            resetKeyboardVars();

            // clear active item
            setActiveItem(0);
            return;

        } else if (d->noMatches) {
            // clear if there are no matches
            resetKeyboardVars();

            // clear active item
            setActiveItem(0);

        } else {
            // the key sequence is not a null string
            // therefore the lastHitIndex is valid
            i = d->lastHitIndex;
        }
    }
	else if (key == Qt::Key_Backspace/* && parent()*/)
	{
        // backspace with no chars in the buffer... go back a menu.
        hide();
        resetKeyboardVars();
        return;
    }

    d->keySeq += keyString;
    int seqLen = d->keySeq.length();

    for (; i < (int)count(); i++) {
        // compare typed text with text of this entry
        int j = idAt(i);

        // don't search disabled entries
        if (!isItemEnabled(j))
            continue;

        QString thisText;

        // retrieve the right text
        // (the last selected item one may have additional ampersands)
        if (i == d->lastHitIndex)
            thisText = d->originalText;
        else
            thisText = text(j);

        // if there is an accelerator present, remove it
        if ((int)accel(j) != 0)
            thisText = thisText.replace("&", QString::null);

        // chop text to the search length
        thisText = thisText.left(seqLen);

        // do the search
        if (!thisText.find(d->keySeq, 0, false)) {

            if (firstpass) {
                // match
                setActiveItem(i);

                // check to see if we're underlining a different item
                if (d->lastHitIndex != i)
                    // yes; revert the underlining
                    changeItem(idAt(d->lastHitIndex), d->originalText);

                // set the original text if it's a different item
                if (d->lastHitIndex != i || d->lastHitIndex == -1)
                    d->originalText = text(j);

                // underline the currently selected item
                changeItem(j, underlineText(d->originalText, d->keySeq.length()));

                // remember what's going on
                d->lastHitIndex = i;

                // start/restart the clear timer
                d->clearTimer.start(5000, true);

                // go around for another try, to see if we can execute
                firstpass = false;
            } else {
                // don't allow execution
                return;
            }
        }

        // fall through to allow execution
    }

    if (!firstpass) {
        if (d->autoExec) {
            // activate anything
            activateItemAt(d->lastHitIndex);
            resetKeyboardVars();

        } else if (findItem(idAt(d->lastHitIndex))/* &&
                 findItem(idAt(d->lastHitIndex))->popup()*/)
		{
            // only activate sub-menus
            activateItemAt(d->lastHitIndex);
            resetKeyboardVars();
        }

        return;
    }

    // no matches whatsoever, clean up
    resetKeyboardVars(true);
    //e->ignore();
    Q3PopupMenu::keyPressEvent(e);
}

bool KPopupMenu::focusNextPrevChild( bool next )
{
    resetKeyboardVars();
    return Q3PopupMenu::focusNextPrevChild( next );
}

QString KPopupMenu::underlineText(const QString& text, uint length)
{
    QString ret = text;
    for (uint i = 0; i < length; i++) {
        if (ret.at(2*i) != '&')
            ret.insert(2*i, "&");
    }
    return ret;
}

void KPopupMenu::resetKeyboardVars(bool noMatches /* = false */)
{
    // Clean up keyboard variables
    if (d->lastHitIndex != -1) {
        changeItem(idAt(d->lastHitIndex), d->originalText);
        d->lastHitIndex = -1;
    }

    if (!noMatches) {
        d->keySeq = QString::null;
    }

    d->noMatches = noMatches;
}

void KPopupMenu::setKeyboardShortcutsEnabled(bool enable)
{
    d->shortcuts = enable;
}

void KPopupMenu::setKeyboardShortcutsExecute(bool enable)
{
    d->autoExec = enable;
}
/**
 * End keyboard navigation.
 */

/**
 * RMB menus on menus
 */

void KPopupMenu::mousePressEvent(QMouseEvent* e)
{
    if (d->m_ctxMenu && d->m_ctxMenu->isVisible())
    {
        // hide on a second context menu event
        d->m_ctxMenu->hide();
    }

    Q3PopupMenu::mousePressEvent(e);
}

void KPopupMenu::mouseReleaseEvent(QMouseEvent* e)
{
    // Save the button, and the modifiers from state()
    d->state = Qt::ButtonState(e->button() | (e->state() & Qt::KeyButtonMask));
    
    if ( !d->m_ctxMenu || !d->m_ctxMenu->isVisible() )
	Q3PopupMenu::mouseReleaseEvent(e);
}

Q3PopupMenu* KPopupMenu::contextMenu()
{
    if (!d->m_ctxMenu)
    {
        d->m_ctxMenu = new Q3PopupMenu(this);
        connect(d->m_ctxMenu, SIGNAL(aboutToHide()), this, SLOT(ctxMenuHiding()));
    }

    return d->m_ctxMenu;
}

const Q3PopupMenu* KPopupMenu::contextMenu() const
{
    return const_cast< KPopupMenu* >( this )->contextMenu();
}

void KPopupMenu::hideContextMenu()
{
    KPopupMenuPrivate::s_continueCtxMenuShow = false;
}

int KPopupMenu::contextMenuFocusItem()
{
    return KPopupMenuPrivate::s_highlightedItem;
}

KPopupMenu* KPopupMenu::contextMenuFocus()
{
    return KPopupMenuPrivate::s_contextedMenu;
}

void KPopupMenu::itemHighlighted(int /* whichItem */)
{
    if (!d->m_ctxMenu || !d->m_ctxMenu->isVisible())
    {
        return;
    }

    d->m_ctxMenu->hide();
    showCtxMenu(mapFromGlobal(QCursor::pos()));
}

void KPopupMenu::showCtxMenu(QPoint pos) //pos unused
{
    QMenuItem* item = findItem(KPopupMenuPrivate::s_highlightedItem);
    if (item)
    {
		SIM::log(SIM::L_DEBUG, "KPopupMenu::showCtxMenu FIXME!!!!");
		//FIXME
		/*
        Q3PopupMenu* subMenu = item->popup();
        if (subMenu)
        {
            disconnect(subMenu, SIGNAL(aboutToShow()), this, SLOT(ctxMenuHideShowingMenu()));
        }
		*/
    }

	/*
    KPopupMenuPrivate::s_highlightedItem = idAt(pos);

    if (KPopupMenuPrivate::s_highlightedItem == -1)
    {
        KPopupMenuPrivate::s_contextedMenu = 0;
        return;
    }

    emit aboutToShowContextMenu(this, KPopupMenuPrivate::s_highlightedItem, d->m_ctxMenu);

    Q3PopupMenu* subMenu = findItem(KPopupMenuPrivate::s_highlightedItem)->popup();
    if (subMenu)
    {
        connect(subMenu, SIGNAL(aboutToShow()), SLOT(ctxMenuHideShowingMenu()));
        QTimer::singleShot(100, subMenu, SLOT(hide()));
    }

    if (!KPopupMenuPrivate::s_continueCtxMenuShow)
    {
        KPopupMenuPrivate::s_continueCtxMenuShow = true;
        return;
    }

    KPopupMenuPrivate::s_contextedMenu = this;
    d->m_ctxMenu->popup(this->mapToGlobal(pos));
    connect(this, SIGNAL(highlighted(int)), this, SLOT(itemHighlighted(int)));
	*/
}

/*
 * this method helps prevent submenus popping up while we have a context menu
 * showing
 */
void KPopupMenu::ctxMenuHideShowingMenu()
{
    QMenuItem* item = findItem(KPopupMenuPrivate::s_highlightedItem);
    if (item)
    {
		SIM::log(SIM::L_DEBUG, "KPopupMenu::ctxMenuHideShowingMenu() FIXME!!!!");
		/*
        Q3PopupMenu* subMenu = item->popup();
        if (subMenu)
        {
            QTimer::singleShot(0, subMenu, SLOT(hide()));
        }
		*/
    }
}

void KPopupMenu::ctxMenuHiding()
{
    if (KPopupMenuPrivate::s_highlightedItem)
    {
		/*
        Q3PopupMenu* subMenu = findItem(KPopupMenuPrivate::s_highlightedItem)->popup();
        if (subMenu)
        {
            disconnect(subMenu, SIGNAL(aboutToShow()), this, SLOT(ctxMenuHideShowingMenu()));
        }
		*/
    }

    disconnect(this, SIGNAL(highlighted(int)), this, SLOT(itemHighlighted(int)));
    KPopupMenuPrivate::s_continueCtxMenuShow = true;
}

void KPopupMenu::contextMenuEvent(QContextMenuEvent* e)
{
    if (d->m_ctxMenu)
    {
		/*
        if (e->reason() == QContextMenuEvent::Mouse)
        {
            showCtxMenu(e->pos());
        }
        else if (actItem != -1)
        {
            showCtxMenu(itemGeometry(actItem).center());
        }

        e->accept();
        return;
		*/
    }

    Q3PopupMenu::contextMenuEvent(e);
}

void KPopupMenu::hideEvent(QHideEvent*)
{
    if (d->m_ctxMenu && d->m_ctxMenu->isVisible())
    {
        // we need to block signals here when the ctxMenu is showing
        // to prevent the QPopupMenu::activated(int) signal from emitting
        // when hiding with a context menu, the user doesn't expect the
        // menu to actually do anything.
        // since hideEvent gets called very late in the process of hiding
        // (deep within QWidget::hide) the activated(int) signal is the
        // last signal to be emitted, even after things like aboutToHide()
        // AJS
        blockSignals(true);
        d->m_ctxMenu->hide();
        blockSignals(false);
    }
}
/**
 * end of RMB menus on menus support
 */

// Obsolete
KPopupMenu::KPopupMenu(const QString& title, QWidget *parent, const char *name)
    : Q3PopupMenu(parent, name)
{
    d = new KPopupMenuPrivate;
    insertTitle(title);
}

// Obsolete
void KPopupMenu::setTitle(const QString &title)
{
    insertItem(title);
    d->m_lastTitle = title;
}

void KPopupTitle::virtual_hook( int, void* )
{ /*BASE::virtual_hook( id, data );*/ }

void KPopupMenu::virtual_hook( int, void* )
{ /*BASE::virtual_hook( id, data );*/ }

/*
#ifndef NO_MOC_INCLUDES
#include "kpopup.moc"
#endif
*/

#endif
