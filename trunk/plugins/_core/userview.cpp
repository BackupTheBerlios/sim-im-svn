/***************************************************************************
                          userview.cpp  -  description
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

#include "userview.h"
#include "simapi.h"
#include "core.h"
#include "intedit.h"
#include "ballonmsg.h"
#include "linklabel.h"
#include "container.h"
#include "userwnd.h"

#include <qpainter.h>
#include <qpixmap.h>
#include <qheader.h>
#include <qobjectlist.h>
#include <qpopupmenu.h>
#include <qtimer.h>
#include <qstyle.h>
#include <qapplication.h>
#include <qwidgetlist.h>
#include <qcursor.h>

using namespace std;
using namespace SIM;

const unsigned BLINK_TIMEOUT    = 500;
const unsigned BLINK_COUNT      = 8;

struct JoinContacts
{
    unsigned	contact1;
    unsigned	contact2;
};

static JoinContacts joinContactsData;

UserView::UserView()
        : UserListBase(NULL)
{
    m_bBlink = false;
    m_bUnreadBlink = false;
    m_bShowOnline = CorePlugin::m_plugin->getShowOnLine();
    m_bShowEmpty = CorePlugin::m_plugin->getShowEmptyGroup();

    setBackgroundMode(NoBackground);
    viewport()->setBackgroundMode(NoBackground);

    mTipItem = NULL;
    m_tip = NULL;
    m_searchTip = NULL;
    m_current = NULL;

    setTreeStepSize(0);

    setVScrollBarMode(CorePlugin::m_plugin->getNoScroller() ? QScrollView::AlwaysOff : QScrollView::Auto);
    setHScrollBarMode(QScrollView::AlwaysOff);

    tipTimer = new QTimer(this);
    connect(tipTimer, SIGNAL(timeout()), this, SLOT(showTip()));
    blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blink()));
    unreadTimer = new QTimer(this);
    connect(unreadTimer, SIGNAL(timeout()), this, SLOT(unreadBlink()));

    topLevelWidget()->installEventFilter(this);
    viewport()->installEventFilter(this);

    m_dropContactId = 0;
    m_dropItem = NULL;
    m_searchItem = NULL;

    setFrameStyle(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    EventAddWidget(this, true, EventAddWidget::eMainWindow).process();
    clear();

    setGroupMode(CorePlugin::m_plugin->getGroupMode(), true);

    edtGroup = new IntLineEdit(viewport());
    edtContact = new IntLineEdit(viewport());
    edtGroup->hide();
    edtContact->hide();
    QFont font;
    int size = font.pixelSize();
    if (size <= 0){
        size = font.pointSize();
        font.setPointSize(size * 3 / 4);
    }else{
        font.setPixelSize(size * 3 / 4);
    }
    font.setBold(true);
    edtGroup->setFont(font);
    connect(edtGroup, SIGNAL(escape()), this, SLOT(editEscape()));
    connect(edtGroup, SIGNAL(returnPressed()), this, SLOT(editGroupEnter()));
    connect(edtGroup, SIGNAL(focusOut()), this, SLOT(editGroupEnter()));
    connect(edtContact, SIGNAL(escape()), this, SLOT(editEscape()));
    connect(edtContact, SIGNAL(returnPressed()), this, SLOT(editContactEnter()));
    connect(edtContact, SIGNAL(focusOut()), this, SLOT(editContactEnter()));
}

UserView::~UserView()
{
    if (m_tip)
        delete m_tip;
    if (m_searchTip)
        delete m_searchTip;
}

void UserView::paintEmptyArea(QPainter *p, const QRect &r)
{
    if ((r.width() == 0) || (r.height() == 0))
        return;
    QPixmap bg(r.width(), r.height());
    QPainter pp(&bg);
    pp.fillRect(QRect(0, 0, r.width(), r.height()), colorGroup().base());
    EventPaintView::PaintView pv;
    pv.p        = &pp;
    pv.pos      = viewport()->mapToParent(r.topLeft());
    pv.size	= r.size();
    pv.win      = this;
    pv.isStatic = false;
    pv.height   = r.height();
    pv.margin   = 0;
    pv.isGroup  = false;
    QListViewItem *item = firstChild();
    if (item)
        pv.height = item->height();
    EventPaintView e(&pv);
    e.process();
    pp.end();
    p->drawPixmap(r.topLeft(), bg);
    setStaticBackground(pv.isStatic);
}

int UserView::heightItem(UserViewItemBase *base)
{
    QFont f(font());
    int h = 0;
    if (base->type() == GRP_ITEM){
        if (CorePlugin::m_plugin->getSmallGroupFont()){
            int size = f.pixelSize();
            if (size <= 0){
                size = f.pointSize();
                f.setPointSize(size * 3 / 4);
            }else{
                f.setPixelSize(size * 3 / 4);
            }
        }
        h = 14;
    }
    if (base->type() == USR_ITEM){
        ContactItem *item = static_cast<ContactItem*>(base);
        QString icons = item->text(CONTACT_ICONS);
        while (!icons.isEmpty()){
            QString icon = getToken(icons, ',');
            QImage img = Image(icon);
            if (img.height() > h)
                h = img.height();
        }
        if (item->m_unread){
            CommandDef *def = CorePlugin::m_plugin->messageTypes.find(item->m_unread);
            if (def){
                QImage img = Image(def->icon);
                if (img.height() > h)
                    h = img.height();
            }
        }
    }
    QFontMetrics fm(f);
    int fh = fm.height();
    if (fh > h)
        h = fh;
    return h + 2;
}


void UserView::drawItem(UserViewItemBase *base, QPainter *p, const QColorGroup &cg, int width, int margin)
{
    if (base->type() == GRP_ITEM){
        GroupItem *item = static_cast<GroupItem*>(base);
        QString text;
        if (item->id()){
            Group *grp = getContacts()->group(item->id());
            if (grp){
                text = grp->getName();
            }else{
                text = "???";
            }
        }else{
            text = i18n("Not in list");
        }
        if (item->m_nContacts){
            text += " (";
            if (item->m_nContactsOnline){
                text += QString::number(item->m_nContactsOnline);
                text += "/";
            }
            text += QString::number(item->m_nContacts);
            text += ")";
        }
        QImage img = Image(item->isOpen() ? "expanded" : "collapsed");
        if (!img.isNull())
            p->drawImage(2 + margin, (item->height() - img.height()) / 2, img);
        int x = 24 + margin;
        if (!item->isOpen() && item->m_unread){
            CommandDef *def = CorePlugin::m_plugin->messageTypes.find(item->m_unread);
            if (def){
                img = Image(def->icon);
                if (!img.isNull()){
                    if (m_bUnreadBlink)
                        p->drawImage(x, (item->height() - img.height()) / 2, img);
                    x += img.width() + 2;
                }
            }
        }
        if (!CorePlugin::m_plugin->getUseSysColors())
            p->setPen(CorePlugin::m_plugin->getColorGroup());
        QFont f(font());
        if (CorePlugin::m_plugin->getSmallGroupFont()){
            int size = f.pixelSize();
            if (size <= 0){
                size = f.pointSize();
                f.setPointSize(size * 3 / 4);
            }else{
                f.setPixelSize(size * 3 / 4);
            }
        }
        f.setBold(true);
        p->setFont(f);
        x = item->drawText(p, x, width, text);
        if (CorePlugin::m_plugin->getGroupSeparator())
            item->drawSeparator(p, x, width, cg);
        return;
    }
    if (base->type() == USR_ITEM){
        ContactItem *item = static_cast<ContactItem*>(base);
        QFont f(font());
        if (item->style() & CONTACT_ITALIC){
            if (CorePlugin::m_plugin->getVisibleStyle()  & STYLE_ITALIC)
                f.setItalic(true);
            if (CorePlugin::m_plugin->getVisibleStyle()  & STYLE_UNDER)
                f.setUnderline(true);
            if (CorePlugin::m_plugin->getVisibleStyle()  & STYLE_STRIKE)
                f.setStrikeOut(true);
        }
        if (item->style() & CONTACT_UNDERLINE){
            if (CorePlugin::m_plugin->getAuthStyle()  & STYLE_ITALIC)
                f.setItalic(true);
            if (CorePlugin::m_plugin->getAuthStyle()  & STYLE_UNDER)
                f.setUnderline(true);
            if (CorePlugin::m_plugin->getAuthStyle()  & STYLE_STRIKE)
                f.setStrikeOut(true);
        }
        if (item->style() & CONTACT_STRIKEOUT){
            if (CorePlugin::m_plugin->getInvisibleStyle()  & STYLE_ITALIC)
                f.setItalic(true);
            if (CorePlugin::m_plugin->getInvisibleStyle()  & STYLE_UNDER)
                f.setUnderline(true);
            if (CorePlugin::m_plugin->getInvisibleStyle()  & STYLE_STRIKE)
                f.setStrikeOut(true);
        }
        QString icons = item->text(CONTACT_ICONS);
        QString icon = getToken(icons, ',');
        if (item->m_unread && m_bUnreadBlink){
            CommandDef *def = CorePlugin::m_plugin->messageTypes.find(item->m_unread);
            if (def)
                icon = def->icon;
        }
        int x = margin;
        if (icon.length()){
            QImage img = Image(icon);
            if (!img.isNull()){
                x += 2;
                p->drawImage(x, (item->height() - img.height()) / 2, img);
                x += img.width() + 2;
            }
        }
        if (x < 24)
            x = 24;
        if (!item->isSelected() || !hasFocus() || !CorePlugin::m_plugin->getUseDblClick()){
            if (CorePlugin::m_plugin->getUseSysColors()){
                if (item->status() != STATUS_ONLINE)
                    p->setPen(palette().disabled().text());
            }else{
                switch (item->status()){
                case STATUS_ONLINE:
                    p->setPen(CorePlugin::m_plugin->getColorOnline());
                    break;
                case STATUS_AWAY:
                    p->setPen(CorePlugin::m_plugin->getColorAway());
                    break;
                case STATUS_NA:
                    p->setPen(CorePlugin::m_plugin->getColorNA());
                    break;
                case STATUS_DND:
                    p->setPen(CorePlugin::m_plugin->getColorDND());
                    break;
                default:
                    p->setPen(CorePlugin::m_plugin->getColorOffline());
                    break;
                }
            }
        }
        if (item->m_bBlink){
            f.setBold(true);
        }else{
            f.setBold(false);
        }
        p->setFont(f);
        QString highlight;
        QString text = item->text(CONTACT_TEXT);
        int pos=0;
        if (!m_search.isEmpty()){
            pos=text.upper().find(m_search.upper());
            //Search from the beginning of contact name
            /*if (text.left(m_search.length()).upper() == m_search.upper())
                highlight = text.left(m_search.length());*/
            //Search for substring in contact name
            if (pos>-1)
                highlight=text.mid(pos,m_search.length());
        }
        int save_x = x;
        x = item->drawText(p, x, width, text);
        if (pos>0)
            /*drawText returns bounding x coordinate of the output +5,
              so to have actual x coordinate to draw, we ned to -4*/
            save_x = item->drawText(p, save_x, width, text.left(pos)) - 4;
        x += 2;
        if (!highlight.isEmpty()){
            QPen oldPen = p->pen();
            QColor oldBg = p->backgroundColor();
            p->setBackgroundMode(OpaqueMode);
            if (item == m_searchItem){
                if ((item == currentItem()) && CorePlugin::m_plugin->getUseDblClick()){
                    p->setBackgroundColor(cg.highlightedText());
                    p->setPen(cg.highlight());
                }else{
                    p->setBackgroundColor(cg.highlight());
                    p->setPen(cg.highlightedText());
                }
            }else{
                p->setBackgroundColor(oldPen.color());
                p->setPen(oldBg);
            }
            item->drawText(p, save_x, width, highlight);
            p->setPen(oldPen);
            p->setBackgroundColor(oldBg);
            p->setBackgroundMode(TransparentMode);
        }
        unsigned xIcon = width;
        while (icons.length()){
            icon = getToken(icons, ',');
            QImage img = Image(icon);
            if (!img.isNull()){
                xIcon -= img.width() + 2;
                if (xIcon < (unsigned)x)
                    break;
                p->drawImage(xIcon, (item->height() - img.height()) / 2, img);
            }
        }
        return;
    }
    UserListBase::drawItem(base, p, cg, width, margin);
}

void *UserView::processEvent(Event *e)
{
    switch (e->type()){
    case eEventRepaintView:
        setVScrollBarMode(CorePlugin::m_plugin->getNoScroller() ? QScrollView::AlwaysOff : QScrollView::Auto);
        break;
    case eEventInit:
        m_bInit = true;
        fill();
        break;
    case eEventContact: {
        EventContact *ec = static_cast<EventContact*>(e);
        if(ec->action() != EventContact::eOnline)
            break;
        Contact *contact = ec->contact();
        if (m_bInit){
            bool bStart = blinks.empty();
            list<BlinkCount>::iterator it;
            for (it = blinks.begin(); it != blinks.end(); ++it){
                if ((*it).id == contact->id())
                    break;
            }
            if (it != blinks.end()){
                (*it).count = BLINK_COUNT;
                return NULL;
            }
            BlinkCount bc;
            bc.id = contact->id();
            bc.count = BLINK_COUNT;
            blinks.push_back(bc);
            if (bStart)
                blinkTimer->start(BLINK_TIMEOUT);
            return NULL;
        }
        break;
    }
    case EventMessageDeleted:
    case EventMessageRead:
    case EventMessageReceived:{
            Message *msg = (Message*)(e->param());
            addContactForUpdate(msg->contact());
            break;
        }
    case eEventCommandExec:{
            EventCommandExec *ece = static_cast<EventCommandExec*>(e);
            CommandDef *cmd = ece->cmd();
            if (cmd->menu_id == MenuContact){
                Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                if (contact){
                    if (cmd->id == CmdContactDelete){
                        QListViewItem *item = findContactItem(contact->id());
                        if (item){
                            ensureItemVisible(item);
                            QRect rc = itemRect(item);
                            QPoint p = viewport()->mapToGlobal(rc.topLeft());
                            rc = QRect(p.x(), p.y(), rc.width(), rc.height());
                            m_bRemoveHistory = CorePlugin::m_plugin->getRemoveHistory();
                            BalloonMsg::ask((void*)contact->id(),
                                            i18n("Delete \"%1\"?") .arg(contact->getName()),
                                            this, SLOT(deleteContact(void*)), NULL, &rc, NULL,
                                            i18n("Remove history"), &m_bRemoveHistory);
                        }
                        return (void*)1;
                    }
                    if (cmd->id == CmdContactRename){
                        QListViewItem *item = findContactItem(contact->id());
                        if (item){
                            setCurrentItem(item);
                            renameContact();
                        }
                        return (void*)1;
                    }
                    if (cmd->id == CmdShowAlways){
                        ListUserData *data = (ListUserData*)(contact->getUserData(CorePlugin::m_plugin->list_data_id, true));
                        if (data){
                            bool bShow = false;
                            if (cmd->flags & COMMAND_CHECKED)
                                bShow = true;
                            if (data->ShowAlways.toBool() != bShow){
                                data->ShowAlways.asBool() = bShow;
                                EventContact(contact, EventContact::eChanged).process();
                            }
                        }
                        return (void*)1;
                    }
                    if (cmd->id == CmdClose){
                        UserWnd *wnd = NULL;
                        QWidgetList  *list = QApplication::topLevelWidgets();
                        QWidgetListIt it(*list);
                        QWidget * w;
                        while ((w = it.current()) != NULL){
                            if (w->inherits("Container")){
                                Container *c =  static_cast<Container*>(w);
                                wnd = c->wnd((unsigned long)(cmd->param));
                                if (wnd)
                                    break;
                            }
                            ++it;
                        }
                        delete list;
                        if (wnd){
                            delete wnd;
                            return (void*)1;
                        }
                    }
                    if (cmd->id > CmdSendMessage){
                        Command c;
                        c->id	   = cmd->id - CmdSendMessage;
                        c->menu_id = MenuMessage;
                        c->param   = (void*)(contact->id());
                        c->flags   = cmd->flags;
                        EventCommandExec eCmd(c);
                        if (eCmd.process())
                            return (void*)1;
                    }
                }
            }
            if (cmd->menu_id == MenuContactGroup){
                Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                if (contact){
                    Group *grp = getContacts()->group(cmd->id - CmdContactGroup);
                    if (grp && (grp->id() != contact->getGroup())){
                        contact->setGroup(grp->id());
                        EventContact eChanged(contact, EventContact::eChanged);
                        eChanged.process();
                        return (void*)1;
                    }
                }
            }
            if (cmd->menu_id == MenuContainer){
                Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                if (contact){
                    Container *from = NULL;
                    Container *to = NULL;
                    QWidgetList  *list = QApplication::topLevelWidgets();
                    QWidgetListIt it(*list);
                    QWidget * w;
                    unsigned max_id = 0;
                    while ((w = it.current()) != NULL){
                        if (w->inherits("Container")){
                            Container *c = static_cast<Container*>(w);
                            if (c->getId() == cmd->id)
                                to = c;
                            if (c->wnd(contact->id()))
                                from = c;
                            if (!(c->getId() & CONTAINER_GRP)){
                                if (max_id < c->getId())
                                    max_id = c->getId();
                            }
                        }
                        ++it;
                    }
                    if (from && to && (from == to))
                        return (void*)1;
                    UserWnd *userWnd = NULL;
                    if (from){
                        userWnd = from->wnd(contact->id());
                        from->removeUserWnd(userWnd);
                    }
                    if (userWnd == NULL)
                        userWnd = new UserWnd(contact->id(), NULL, true, true);
                    if (to == NULL)
                        to = new Container(max_id + 1);
                    to->init();
                    to->addUserWnd(userWnd, true);
                    to->setNoSwitch(true);
                    raiseWindow(to);
                    to->setNoSwitch(false);
                }
                return (void*)1;
            }
            if (cmd->id == CmdOnline){
                CorePlugin::m_plugin->setShowOnLine((cmd->flags & COMMAND_CHECKED) != 0);
                m_bShowOnline = (cmd->flags & COMMAND_CHECKED);
                if (cmd->menu_id){
                    CommandDef c = *cmd;
                    c.bar_id	= ToolBarMain;
                    c.bar_grp   = 0x4000;
                    EventCommandChange(&c).process();
                }
                fill();
            }
            if (cmd->id == CmdEmptyGroup){
                CorePlugin::m_plugin->setShowEmptyGroup((cmd->flags & COMMAND_CHECKED) != 0);
                m_bShowEmpty = (cmd->flags & COMMAND_CHECKED);
                fill();
            }
            if (cmd->id == CmdGrpOff)
                setGroupMode(0);
            if (cmd->id == CmdGrpMode1)
                setGroupMode(1);
            if (cmd->id == CmdGrpMode2)
                setGroupMode(2);
            if (cmd->id == CmdGrpCreate){
                if (CorePlugin::m_plugin->getGroupMode()){
                    /* Show empty groups because a new group is empty... */
                    CorePlugin::m_plugin->setShowEmptyGroup(true);
                    m_bShowEmpty = true;
                    fill();
                    Group *g = getContacts()->group(0, true);
                    drawUpdates();
                    QListViewItem *item = findGroupItem(g->id());
                    if (item){
                        setCurrentItem(item);
                        QTimer::singleShot(0, this, SLOT(renameGroup()));
                    }
                }
                return (void*)1;
            }
            if (cmd->id == CmdGrpRename){
                QListViewItem *item = findGroupItem((unsigned long)(cmd->param));
                if (item){
                    setCurrentItem(item);
                    renameGroup();
                }
                return (void*)1;
            }
            if (cmd->id == CmdGrpUp){
                unsigned long grp_id = (unsigned long)(cmd->param);
                getContacts()->moveGroup(grp_id, true);
                QListViewItem *item = findGroupItem(grp_id);
                if (item){
                    ensureItemVisible(item);
                    setCurrentItem(item);
                }
                return (void*)1;
            }
            if (cmd->id == CmdGrpDown){
                unsigned long grp_id = (unsigned long)(cmd->param);
                getContacts()->moveGroup(grp_id, false);
                QListViewItem *item = findGroupItem(grp_id);
                if (item){
                    ensureItemVisible(item);
                    setCurrentItem(item);
                }
                return (void*)1;
            }
            if (cmd->id == CmdGrpDelete){
                unsigned long grp_id = (unsigned long)(cmd->param);
                QListViewItem *item = findGroupItem(grp_id);
                Group *g = getContacts()->group(grp_id);
                if (item && g){
                    ensureItemVisible(item);
                    QRect rc = itemRect(item);
                    QPoint p = viewport()->mapToGlobal(rc.topLeft());
                    rc = QRect(p.x(), p.y(), rc.width(), rc.height());
                    BalloonMsg::ask((void*)grp_id,
                                    i18n("Delete \"%1\"?") .arg(g->getName()),
                                    this, SLOT(deleteGroup(void*)), NULL, &rc);
                }
            }
            break;
        }
    case eEventCheckState:{
            EventCheckState *ecs = static_cast<EventCheckState*>(e);
            CommandDef *cmd = ecs->cmd();
            if (cmd->menu_id == MenuGroups){
                cmd->flags = cmd->flags & (~COMMAND_CHECKED);
                if (((cmd->id == CmdGrpOff) && (CorePlugin::m_plugin->getGroupMode() == 0)) ||
                        ((cmd->id == CmdGrpMode1) && (CorePlugin::m_plugin->getGroupMode() == 1)) ||
                        ((cmd->id == CmdGrpMode2) && (CorePlugin::m_plugin->getGroupMode() == 2)) ||
                        ((cmd->id == CmdOnline) && CorePlugin::m_plugin->getShowOnLine()))
                    cmd->flags |= COMMAND_CHECKED;
                if (cmd->id == CmdEmptyGroup){
                    if (CorePlugin::m_plugin->getGroupMode() == 0)
                        return NULL;
                    if (CorePlugin::m_plugin->getShowEmptyGroup())
                        cmd->flags |= COMMAND_CHECKED;
                }
                return (void*)1;
            }
            if (cmd->menu_id == MenuContact){
                if (cmd->id == CmdContactTitle){
                    Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                    if (contact){
                        cmd->text_wrk = contact->getName();
                        return (void*)1;
                    }
                }
                if (cmd->id == CmdShowAlways){
                    Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                    if (contact){
                        ListUserData *data = (ListUserData*)(contact->getUserData(CorePlugin::m_plugin->list_data_id, true));
                        cmd->flags &= ~COMMAND_CHECKED;
                        if (data && data->ShowAlways.toBool())
                            cmd->flags |= COMMAND_CHECKED;
                        return (void*)1;
                    }
                }
                if (cmd->id == CmdClose){
                    UserWnd *wnd = NULL;
                    QWidgetList  *list = QApplication::topLevelWidgets();
                    QWidgetListIt it(*list);
                    QWidget * w;
                    while ((w = it.current()) != NULL){
                        if (w->inherits("Container")){
                            wnd = static_cast<Container*>(w)->wnd((unsigned long)(cmd->param));
                            if (wnd)
                                break;
                        }
                        ++it;
                    }
                    delete list;
                    return wnd; // ok
                }
                if (cmd->id == CmdSendMessage){
                    EventMenuGetDef eMenu(MenuMessage);
                    eMenu.process();
                    CommandsDef *cmdsMsg = eMenu.defs();
                    unsigned nCmds = 1;
                    {
                        CommandsList it(*cmdsMsg, true);
                        while (++it)
                            nCmds++;
                    }

                    CommandDef *cmds = new CommandDef[nCmds];
                    nCmds = 0;

                    CommandsList it(*cmdsMsg, true);
                    CommandDef *c;
                    while ((c = ++it) != NULL){
                        cmds[nCmds] = *c;
                        cmds[nCmds].id = CmdSendMessage + c->id;
                        cmds[nCmds].menu_id = MenuContact;
                        nCmds++;
                    }
                    cmd->param = cmds;
                    cmd->flags |= COMMAND_RECURSIVE;
                    return (void*)1;
                }
                if (cmd->id > CmdSendMessage){
                    Command c;
                    c->id	   = cmd->id - CmdSendMessage;
                    c->menu_id = MenuMessage;
                    c->param   = cmd->param;
                    void *res = EventCheckState(c).process();
                    if (res && (c->flags & COMMAND_RECURSIVE)){
                        cmd->flags |= COMMAND_RECURSIVE;
                        cmd->param = c->param;
                    }
                    if (res) {
                        cmd->flags = c->flags;
                    }
                    return res;
                }
            }
            if (cmd->menu_id == MenuContactGroup){
                if (cmd->id == CmdContactGroup){
                    unsigned grpId = 0;
                    Contact *contact = getContacts()->contact((unsigned long)(cmd->param));
                    if (contact)
                        grpId = contact->getGroup();
                    unsigned nGroups = 0;
                    Group *grp;
                    ContactList::GroupIterator it;
                    while ((grp = ++it) != NULL)
                        nGroups++;
                    CommandDef *cmds = new CommandDef[nGroups + 1];
                    it.reset();
                    nGroups = 0;
                    while ((grp = ++it) != NULL){
                        if (grp->id() == 0) continue;
                        CommandDef &c = cmds[nGroups++];
                        c = *cmd;
                        c.id = CmdContactGroup + grp->id();
                        c.flags = COMMAND_DEFAULT;
                        if ((grp->id() == grpId) && contact->id())
                            c.flags |= COMMAND_CHECKED;
                        c.text_wrk = grp->getName();
                    }
                    CommandDef &c = cmds[nGroups++];
                    c = *cmd;
                    c.text = I18N_NOOP("Not in list");
                    c.id = CmdContactGroup;
                    c.flags = COMMAND_DEFAULT;
                    if (grpId == 0)
                        c.flags = COMMAND_CHECKED;
                    cmds[nGroups].clear();
                    cmd->flags |= COMMAND_RECURSIVE;
                    cmd->param = cmds;
                    return (void*)1;
                }
            }
            if (cmd->menu_id == MenuGroup){
                unsigned long grp_id = (unsigned long)(cmd->param);
                if (grp_id){
                    if (cmd->id == CmdGrpTitle){
                        Group *g = getContacts()->group(grp_id);
                        if (g)
                            cmd->text_wrk = g->getName();
                        return (void*)1;
                    }
                    if ((cmd->id == CmdGrpDelete) || (cmd->id == CmdGrpRename)){
                        cmd->flags &= ~COMMAND_CHECKED;
                        return (void*)1;
                    }
                    if (cmd->id == CmdGrpUp){
                        if (getContacts()->groupIndex(grp_id) <= 1)
                            cmd->flags |= COMMAND_DISABLED;
                        cmd->flags &= ~COMMAND_CHECKED;
                        return (void*)1;
                    }
                    if (cmd->id == CmdGrpDown){
                        if (getContacts()->groupIndex(grp_id) >= getContacts()->groupCount() - 1)
                            cmd->flags |= COMMAND_DISABLED;
                        cmd->flags &= ~COMMAND_CHECKED;
                        return (void*)1;
                    }
                }else{
                    if (cmd->id == CmdGrpTitle){
                        cmd->text = I18N_NOOP("Not in list");
                        return (void*)1;
                    }
                }
            }
            if (cmd->id == CmdGrpCreate) {
                cmd->flags &= ~COMMAND_CHECKED;
                return CorePlugin::m_plugin->getGroupMode() ? e->param() : NULL;
            }
            break;
        }
    case eEventIconChanged:
        viewport()->repaint();
        break;
    case eEventRaiseWindow:{
            EventRaiseWindow *w = static_cast<EventRaiseWindow*>(e);
            QWidget *o = w->widget();
            if (o && o->inherits("MainWindow"))
                QTimer::singleShot(0, this, SLOT(adjustColumn()));
            break;
        }
    }
    return UserListBase::processEvent(e);
}

void UserView::deleteGroup(void *p)
{
    Group *grp = getContacts()->group((unsigned long)p);
    if (grp)
        delete grp;
}

void UserView::deleteContact(void *p)
{
    Contact *contact = getContacts()->contact((unsigned long)p);
    if (contact == NULL)
        return;
    ContactItem *item = findContactItem(contact->id());
    if (item)
        setCurrentItem(item);
    CorePlugin::m_plugin->setRemoveHistory(m_bRemoveHistory);
    if (!m_bRemoveHistory)
        contact->setFlags(contact->getFlags() | CONTACT_NOREMOVE_HISTORY);
    delete contact;
}

void UserView::renameGroup()
{
    QListViewItem *item = currentItem();
    if (item == NULL)
        return;
    UserViewItemBase *i = static_cast<UserViewItemBase*>(item);
    if (i->type() != GRP_ITEM)
        return;
    GroupItem *grpItem = static_cast<GroupItem*>(item);
    Group *g = getContacts()->group(grpItem->id());
    if (g){
        ensureItemVisible(item);
        QString name = g->getName();
        QRect rc = itemRect(item);
        rc.setLeft(rc.left() + 18);
        edtGroup->id = g->id();
        edtGroup->setGeometry(rc);
        edtGroup->setText(name.length() ? name : i18n("New group"));
        edtGroup->setSelection(0, edtGroup->text().length());
        edtGroup->show();
        edtGroup->setFocus();
    }
}

void UserView::renameContact()
{
    QListViewItem *item = currentItem();
    if (item == NULL)
        return;
    UserViewItemBase *i = static_cast<UserViewItemBase*>(item);
    if (i->type() != USR_ITEM)
        return;
    ContactItem *contactItem = static_cast<ContactItem*>(item);
    Contact *contact = getContacts()->contact(contactItem->id());
    if (contact){
        ensureItemVisible(item);
        QString name = contact->getName();
        QRect rc = itemRect(item);
        rc.setLeft(rc.left() + 18);
        edtContact->id = contact->id();
        edtContact->setGeometry(rc);
        edtContact->setText(name);
        edtContact->setSelection(0, edtGroup->text().length());
        edtContact->show();
        edtContact->setFocus();
    }
}

void UserView::setGroupMode(unsigned mode, bool bFirst)
{
    if (!bFirst && (CorePlugin::m_plugin->getGroupMode() == mode))
        return;
    CorePlugin::m_plugin->setGroupMode(mode);
    m_groupMode = mode;
    Command cmd;
    cmd->id          = CmdGroup;
    cmd->text        = I18N_NOOP("&Groups");
    cmd->icon        = CorePlugin::m_plugin->getGroupMode() ? "grp_on" : "grp_off";
    cmd->bar_id      = ToolBarMain;
    cmd->bar_grp     = 0x4000;
    cmd->menu_id     = MenuMain;
    cmd->menu_grp    = 0x6001;
    cmd->popup_id    = MenuGroups;

    EventCommandCreate(cmd).process();

    fill();
}

bool UserView::eventFilter(QObject *obj, QEvent *e)
{
    bool res = ListView::eventFilter(obj, e);
    if (obj->inherits("QMainWindow")){
        if (e->type() == QEvent::Hide)
            hideTip();
        if (e->type() == QEvent::Show)
            QTimer::singleShot(0, this, SLOT(repaintView()));
    }
    if ((obj == viewport()) && (e->type() == QEvent::Leave))
        hideTip();
    return res;
}

void UserView::contentsMousePressEvent(QMouseEvent *e)
{
    hideTip();
    stopSearch();
    UserListBase::contentsMousePressEvent(e);
}

void UserView::focusOutEvent(QFocusEvent *e)
{
    stopSearch();
    UserListBase::focusOutEvent(e);
}

void UserView::contentsMouseMoveEvent(QMouseEvent *e)
{
    QListViewItem *list_item = itemAt(contentsToViewport(e->pos()));
    showTip(list_item);
    ListView::contentsMouseMoveEvent(e);
}

void UserView::contentsMouseReleaseEvent(QMouseEvent *e)
{
    QListViewItem *item = m_pressedItem;
    UserListBase::contentsMouseReleaseEvent(e);
    if (item){
        if (!CorePlugin::m_plugin->getUseDblClick()){
            m_current = item;
            QTimer::singleShot(0, this, SLOT(doClick()));
        }
    }
}

void UserView::contentsMouseDoubleClickEvent(QMouseEvent *e)
{
    UserListBase::contentsMouseDoubleClickEvent(e);
    m_current = itemAt(contentsToViewport(e->pos()));
    QTimer::singleShot(0, this, SLOT(doClick()));
}

void UserView::doClick()
{
    if (m_current == NULL)
        return;
    if (m_current->isExpandable() && !CorePlugin::m_plugin->getUseDblClick()){
        m_current->setOpen(!m_current->isOpen());
    }else if (static_cast<UserViewItemBase*>(m_current)->type() == USR_ITEM){
        ContactItem *item = static_cast<ContactItem*>(m_current);
        Event e(EventDefaultAction, (void*)(item->id()));
        e.process();
    }
    m_current = NULL;
}

void UserView::keyPressEvent(QKeyEvent *e)
{
    if (CorePlugin::m_plugin->getUseDblClick() || m_searchItem){
        if (m_searchItem) {
	    int store = 0;
	    list<QListViewItem*> items;
	    list<QListViewItem*>::iterator it;
            search(items);
	    if (!items.empty()) {
	        for (it = items.begin(); it != items.end(); ++it)
  	            if (*it == m_searchItem) {
		    store = 1;
	        }
	        if (!store) m_searchItem = items.front();
	    } else {
	        m_search = "";
	        m_searchItem = NULL;
            }
	    setCurrentItem(m_searchItem);
	}
        switch (e->key()){
        case Key_Return:
        case Key_Enter:
            m_current = currentItem();
            QTimer::singleShot(0, this, SLOT(doClick()));
            return;
        }
    }
    bool bTip = false;
    if (m_searchItem && (m_searchItem == mTipItem))
        bTip = true;
    list<QListViewItem*> old_items;
    list<QListViewItem*> new_items;
    switch (e->key()){
    case Key_BackSpace:
        if (m_search.isEmpty()){
            UserListBase::keyPressEvent(e);
            return;
        }
        search(old_items);
        m_search = m_search.left(m_search.length() - 1);
        if (m_search.isEmpty()){
            m_searchItem = NULL;
            list<QListViewItem*>::iterator it;
            for (it = closed_items.begin(); it != closed_items.end(); ++it)
                 (*it)->setOpen(FALSE);
        }else{
            search(new_items);
            if (new_items.empty()){
                m_search = "";
                m_searchItem = NULL;
            }else{
                m_searchItem = new_items.front();
            }
        }
        break;
    case Key_Escape:
        if (m_search.isEmpty()){
            UserListBase::keyPressEvent(e);
            return;
        }
        stopSearch();
        return;
    case Key_Up:
        if (m_search.isEmpty()){
            UserListBase::keyPressEvent(e);
            return;
        }
        if (m_searchItem){
            search(old_items);
            list<QListViewItem*>::iterator it_old;
            for (it_old = old_items.begin(); it_old != old_items.end(); ++it_old)
                if ((*it_old) == m_searchItem)
                    break;
            if (it_old != old_items.begin())
                it_old--;
            if (it_old == old_items.begin()){
                QApplication::beep();
                return;
            }
            m_searchItem = *it_old;
        }
        break;
    case Key_Down:
        if (m_search.isEmpty()){
            UserListBase::keyPressEvent(e);
            return;
        }
        if (m_searchItem){
            search(old_items);
            list<QListViewItem*>::iterator it_old;
            for (it_old = old_items.begin(); it_old != old_items.end(); ++it_old)
                if ((*it_old) == m_searchItem)
                    break;
            if (it_old != old_items.end())
                it_old++;
            if (it_old == old_items.end()){
                QApplication::beep();
                return;
            }
            m_searchItem = *it_old;
        }
        break;
    case Key_Plus:
    case Key_Minus:
        if (m_search.isEmpty()){
            QListViewItem *item = currentItem();
            if (item && item->isExpandable()){
                UserListBase::keyPressEvent(e);
                return;
            }
        }
    case Key_Delete:
        // e->text() is not empty, but we don't need to specially handle Del
        UserListBase::keyPressEvent(e);
        return;
    default:
        QString t = e->text();
        if (t.isEmpty()){
            UserListBase::keyPressEvent(e);
            return;
        }
        if (m_search.isEmpty()) {
            closed_items.clear();
            for (QListViewItem *item = firstChild(); item; item = item->nextSibling())
                 if (item->isExpandable() && !(item->isOpen()))
                     closed_items.push_back(item);
        }
        QString save_search = m_search;
        search(old_items);
        m_search += t;
        search(new_items);
        if (new_items.empty()){
            m_search = save_search;
            search(new_items);
            QApplication::beep();
            return;
        }else{
            m_searchItem = new_items.front();
        }
    }
    list<QListViewItem*>::iterator it_old;
    list<QListViewItem*>::iterator it_new;
    for (it_old = old_items.begin(); it_old != old_items.end(); ++it_old){
        for (it_new = new_items.begin(); it_new != new_items.end(); ++it_new)
            if (*it_new == *it_old)
                break;
        if (it_new == new_items.end())
            new_items.push_back(*it_old);
    }
    for (it_new = new_items.begin(); it_new != new_items.end(); ++it_new)
        (*it_new)->repaint();
    setCurrentItem(m_searchItem);
    if (m_searchItem){
        ensureItemVisible(m_searchItem);
        showTip(m_searchItem);
    }
    if (m_search.isEmpty() || (m_searchItem == NULL)){
        if (m_searchTip)
            m_searchTip->hide();
        if (bTip)
            hideTip();
    }else{
        QString tip = i18n("Search: %1") .arg(m_search);
        if (m_searchTip){
            m_searchTip->setText(tip);
        }else{
            m_searchTip = new TipLabel( tip);
            connect(m_searchTip, SIGNAL(finished()), this, SLOT(searchTipDestroyed()));
        }
        QRect tipRect = itemRect(m_searchItem);
        QPoint p = viewport()->mapToGlobal(tipRect.topLeft());
        m_searchTip->show(QRect(p.x(), p.y(), tipRect.width(), tipRect.height()), true);
    }
}

void UserView::stopSearch()
{
    if (m_search.isEmpty())
        return;
    if (m_searchItem == mTipItem)
        hideTip();
    list<QListViewItem*> old_items;
    search(old_items);
    m_search = "";
    m_searchItem = NULL;
    list<QListViewItem*>::iterator it_old;
    for (it_old = old_items.begin(); it_old != old_items.end(); ++it_old)
        (*it_old)->repaint();
    if (m_searchTip)
        m_searchTip->hide();
}

bool UserView::getMenu(QListViewItem *list_item, unsigned long &id, void* &param)
{
    if (list_item == NULL)
        return false;

    UserViewItemBase *item = static_cast<UserViewItemBase*>(list_item);
    switch (item->type()){
    case GRP_ITEM:{
            GroupItem *grpItem = static_cast<GroupItem*>(item);
            id    = MenuGroup;
            param = (void*)(grpItem->id());
            return true;
        }
    case USR_ITEM:{
            ContactItem *contactItem = static_cast<ContactItem*>(item);
            id    = MenuContact;
            param = (void*)(contactItem->id());
            return true;
        }
    }
    return false;
}

void UserView::editEscape()
{
    edtGroup->hide();
    edtContact->hide();
}

void UserView::editGroupEnter()
{
    edtGroup->hide();
    Group *g = getContacts()->group(edtGroup->id);
    if (!(g && edtGroup->text().length())) return;
    g->setName(edtGroup->text());
    EventGroup e(g, EventGroup::eChanged);
    e.process();
}

void UserView::editContactEnter()
{
    edtContact->hide();
    Contact *c = getContacts()->contact(edtContact->id);
    if (!(c && edtContact->text().length())) return;
    c->setName(edtContact->text());
    EventContact e(c, EventContact::eChanged);
    e.process();
}

unsigned UserView::getUnread(unsigned contact_id)
{
    for (list<msg_id>::iterator it = CorePlugin::m_plugin->unread.begin(); it != CorePlugin::m_plugin->unread.end(); ++it){
        if ((*it).contact == contact_id){
            if (!unreadTimer->isActive()){
                m_bUnreadBlink = true;
                unreadTimer->start(BLINK_TIMEOUT);
            }
            return (*it).type;
        }
    }
    return 0;
}

void UserView::fill()
{
    hideTip();
    UserListBase::fill();
}

void UserView::tipDestroyed()
{
    m_tip = NULL;
}

void UserView::searchTipDestroyed()
{
    m_searchTip = NULL;
}

void UserView::showTip(QListViewItem *list_item)
{
    if (list_item != mTipItem){
        hideTip();
        mTipItem = NULL;
        if (list_item){
            UserViewItemBase *base_item = dynamic_cast<UserViewItemBase*>(list_item);
            if (!base_item)
				log(L_DEBUG, "UserView::showTip() with wrong param");
			else
				if (base_item->type() == USR_ITEM){
					mTipItem = list_item;
					tipTimer->start(1000, true);
				}
        }
    }
}

void UserView::hideTip()
{
    tipTimer->stop();
    mTipItem = NULL;
    if (m_tip)
        m_tip->hide();
}

void UserView::showTip()
{
    ContactItem *item = NULL;
    if (mTipItem){
        UserViewItemBase *base_item = static_cast<UserViewItemBase*>(mTipItem);
        if (base_item->type() == USR_ITEM)
            item = static_cast<ContactItem*>(mTipItem);
    }
    if (item == NULL)
        return;
    Contact *contact = getContacts()->contact(item->id());
    if (contact == NULL)
        return;
    QString tip = contact->tipText();
    if (m_tip){
        m_tip->setText(tip);
    }else{
        m_tip = new TipLabel( tip);
        connect(m_tip, SIGNAL(finished()), this, SLOT(tipDestroyed()));
    }
    QRect tipRect = itemRect(mTipItem);
    QPoint p = viewport()->mapToGlobal(tipRect.topLeft());
    m_tip->show(QRect(p.x(), p.y(), tipRect.width(), tipRect.height()));
}

static void resetUnread(QListViewItem *item, list<QListViewItem*> &grp)
{
    if (static_cast<UserViewItemBase*>(item)->type() == GRP_ITEM){
        list<QListViewItem*>::iterator it;
        for (it = grp.begin(); it != grp.end(); ++it)
            if ((*it) == item)
                break;
        if (it == grp.end()){
            GroupItem *group = static_cast<GroupItem*>(item);
            if (group->m_unread){
                group->m_unread = 0;
                if (!group->isOpen())
                    group->repaint();
            }
        }
    }
    if (!item->isExpandable())
        return;
    for (item = item->firstChild(); item; item = item->nextSibling())
        resetUnread(item, grp);
}

void UserView::unreadBlink()
{
    m_bUnreadBlink = !m_bUnreadBlink;
    list<unsigned> blinks;
    list<unsigned>::iterator itb;
    for (list<msg_id>::iterator it = CorePlugin::m_plugin->unread.begin(); it != CorePlugin::m_plugin->unread.end(); ++it){
        for (itb = blinks.begin(); itb != blinks.end(); ++itb)
            if ((*itb) == (*it).contact)
                break;
        if (itb != blinks.end())
            continue;
        blinks.push_back((*it).contact);
    }
    list<QListViewItem*> grps;
    if (blinks.empty()){
        unreadTimer->stop();
    }else{
        for (itb = blinks.begin(); itb != blinks.end(); ++itb){
            ContactItem *contact = findContactItem((*itb), NULL);
            if (contact == NULL)
                return;
            repaintItem(contact);
            if (CorePlugin::m_plugin->getGroupMode() && !contact->parent()->isOpen()){
                GroupItem *group = static_cast<GroupItem*>(contact->parent());
                group->m_unread = contact->m_unread;
                repaintItem(group);
                grps.push_back(group);
            }
        }
    }
    if (CorePlugin::m_plugin->getGroupMode()){
        for (QListViewItem *item = firstChild(); item; item = item->nextSibling()){
            resetUnread(item, grps);
        }
    }
}

void UserView::blink()
{
    m_bBlink = !m_bBlink;
    list<BlinkCount>::iterator it;
    for (it = blinks.begin(); it != blinks.end();){
        ContactItem *contact = findContactItem((*it).id, NULL);
        if (contact == NULL){
            blinks.erase(it);
            it = blinks.begin();
            break;
        }
        contact->m_bBlink = m_bBlink;
        repaintItem(contact);
        ++it;
    }
    if (m_bBlink)
        return;
    for (it = blinks.begin(); it != blinks.end(); ++it)
        (*it).count--;
    for (it = blinks.begin(); it != blinks.end(); ){
        if ((*it).count){
            ++it;
            continue;
        }
        blinks.erase(it);
        it = blinks.begin();
    }
    if (blinks.size() == 0)
        blinkTimer->stop();
}

void UserView::deleteItem(QListViewItem *item)
{
    if (item == NULL)
        return;
    if (item == mTipItem)
        hideTip();
    if (item == m_pressedItem)
        m_pressedItem = NULL;
    if (item == m_searchItem)
        stopSearch();
    UserListBase::deleteItem(item);
}

class UserViewContactDragObject : public ContactDragObject
{
public:
    UserViewContactDragObject(UserView *view, Contact *contact);
    ~UserViewContactDragObject();
};

UserViewContactDragObject::UserViewContactDragObject(UserView *view, Contact *contact)
        : ContactDragObject(view, contact)
{
	QTimer *dragTimer = new QTimer(this);
	connect(dragTimer, SIGNAL(timeout()), view, SLOT(dragScroll()));
	dragTimer->start(200);
}

UserViewContactDragObject::~UserViewContactDragObject()
{
}

QDragObject *UserView::dragObject()
{
    if (currentItem() == NULL)
        return NULL;
    UserViewItemBase *base_item = static_cast<UserViewItemBase*>(currentItem());
    if (base_item->type() != USR_ITEM)
        return NULL;
    ContactItem *item = static_cast<ContactItem*>(currentItem());
    Contact *contact = getContacts()->contact(item->id());
    if (contact == NULL)
        return NULL;
    return new UserViewContactDragObject(this, contact);
}

void UserView::contentsDragEnterEvent(QDragEnterEvent *e)
{
    dragEvent(e, false);
}

void UserView::contentsDragMoveEvent(QDragMoveEvent *e)
{
    dragEvent(e, false);
}

void UserView::contentsDropEvent(QDropEvent *e)
{
    dragEvent(e, true);
}

void UserView::dragEvent(QDropEvent *e, bool isDrop)
{
    QListViewItem *list_item = itemAt(contentsToViewport(e->pos()));
    if (list_item == NULL){
        e->ignore();
        return;
    }
    UserViewItemBase *item = static_cast<UserViewItemBase*>(list_item);
    switch (item->type()){
    case GRP_ITEM:
        if (ContactDragObject::canDecode(e)){
            if (isDrop){
                Contact *contact = ContactDragObject::decode(e);
                m_dropItem = item;
                m_dropContactId = contact->id();
                contact->setFlags(contact->getFlags() & ~CONTACT_DRAG);
                QTimer::singleShot(0, this, SLOT(doDrop()));
            }
            e->accept();
            return;
        }
        break;
    case USR_ITEM:{
            if (ContactDragObject::canDecode(e)){
                Contact *contact = ContactDragObject::decode(e);
                if (static_cast<ContactItem*>(item)->id() == contact->id()){
                    e->ignore();
                    return;
                }
                if (isDrop){
                    m_dropItem = item;
                    m_dropContactId = contact->id();
                    contact->setFlags(contact->getFlags() & ~CONTACT_DRAG);
                    QTimer::singleShot(0, this, SLOT(doDrop()));
                }
                e->accept();
                return;
            }
            Message *msg = NULL;
            CommandDef *cmd;
            CommandsMapIterator it(CorePlugin::m_plugin->messageTypes);
            while ((cmd = ++it) != NULL){
                MessageDef *def = (MessageDef*)(cmd->param);
                if (def && def->drag){
                    msg = def->drag(e);
                    if (msg){
                        unsigned type = cmd->id;
                        Command cmd;
                        cmd->id      = type;
                        cmd->menu_id = MenuMessage;
                        cmd->param	 = (void*)(static_cast<ContactItem*>(item)->id());
                        if (EventCheckState(cmd).process())
                            break;
                    }
                }
            }
            if (msg){
                if (isDrop){
                    msg->setContact(static_cast<ContactItem*>(item)->id());
                    Event e(EventOpenMessage, &msg);
                    e.process();
                }
                delete msg;
                return;
            }
            if (QTextDrag::canDecode(e)){
                QString str;
                if (QTextDrag::decode(e, str)){
                    e->accept();
                    if (isDrop){
                        Message *msg = new Message(MessageGeneric);
                        msg->setText(str);
                        msg->setContact(static_cast<ContactItem*>(item)->id());
                        Event e(EventOpenMessage, &msg);
                        e.process();
                        delete msg;
                    }
                    return;
                }
            }
            break;
        }
    }
    e->ignore();
}

void UserView::doDrop()
{
    if (m_dropItem == NULL)
        return;
    Contact *contact = getContacts()->contact(m_dropContactId);
    if (contact == NULL)
        return;
    switch (static_cast<UserViewItemBase*>(m_dropItem)->type()){
    case GRP_ITEM:{
            GroupItem *grp_item = static_cast<GroupItem*>(m_dropItem);
            contact->setGroup(grp_item->id());
            contact->setIgnore(false);
            contact->setFlags(contact->getFlags() & ~CONTACT_TEMPORARY);
            EventContact eContact(contact, EventContact::eChanged);
            eContact.process();
            break;
        }
    case USR_ITEM:{
            ContactItem *contact_item = static_cast<ContactItem*>(m_dropItem);
            Contact *contact1 = getContacts()->contact(contact_item->id());
            if (contact1 == NULL)
                break;
            joinContactsData.contact1 = contact_item->id();
            joinContactsData.contact2 = m_dropContactId;
            ensureItemVisible(contact_item);
            QRect rc = itemRect(contact_item);
            QPoint p = viewport()->mapToGlobal(rc.topLeft());
            rc = QRect(p.x(), p.y(), rc.width(), rc.height());
            BalloonMsg::ask(NULL,
                            i18n("Join \"%1\" and \"%2\"?")
                            .arg(contact1->getName())
                            .arg(contact->getName()),
                            this,
                            SLOT(joinContacts(void*)),
                            SLOT(cancelJoinContacts(void*)), &rc);
            break;
        }
    }
    m_dropContactId = 0;
    m_dropItem = NULL;
}

void UserView::joinContacts(void*)
{
    Contact *contact1 = getContacts()->contact(joinContactsData.contact1);
    Contact *contact2 = getContacts()->contact(joinContactsData.contact2);
    if ((contact1 == NULL) || (contact2 == NULL))
        return;
    contact1->clientData.join(contact2->clientData);
    if (!contact2->getPhones().isEmpty()){
        QString phones = contact1->getPhones();
        if (!phones.isEmpty())
            phones += ";";
        phones += contact2->getPhones();
        contact1->setPhones(phones);
    }
    if (!contact2->getEMails().isEmpty()){
        QString mails = contact1->getEMails();
        if (!mails.isEmpty())
            mails += ";";
        mails += contact2->getEMails();
        contact1->setEMails(mails);
    }
    delete contact2;
    contact1->setup();
    EventContact e(contact1, EventContact::eChanged);
    e.process();
}

void UserView::cancelJoinContacts(void*)
{
    Contact *contact2 = getContacts()->contact(joinContactsData.contact2);
    if (contact2 && (contact2->getFlags() & CONTACT_TEMPORARY))
        delete contact2;
}

void UserView::sortAll()
{
    sort();
    for (QListViewItem *item = firstChild(); item; item = item->nextSibling())
        sortAll(item);
}

void UserView::sortAll(QListViewItem *item)
{
    item->sort();
    for (item = item->firstChild(); item; item = item->nextSibling())
        sortAll(item);
}

void UserView::search(list<QListViewItem*> &items)
{
    if (m_search.isEmpty())
        return;
    list<QListViewItem*>::iterator it;
    for (it = closed_items.begin(); it != closed_items.end(); ++it)
         (*it)->setOpen(FALSE);
    for (QListViewItem *item = firstChild(); item; item = item->nextSibling())
        search(item, items);
}

void UserView::search(QListViewItem *item, list<QListViewItem*> &items)
{
  if (item->isExpandable()){
        for (QListViewItem *child = item->firstChild(); child; child = child->nextSibling())
            search(child, items);
    }
    if (static_cast<UserViewItemBase*>(item)->type() != USR_ITEM)
        return;
    QString name = item->text(CONTACT_TEXT);
    log(L_DEBUG, "Contact List search: Examining name %s", (const char *)name.local8Bit());
    //Search from the beginning of contact name
    //if (name.left(m_search.length()).upper() == m_search.upper())
    //Search for substring in contact name
    if (name.upper().find(m_search.upper())>-1) {
        log(L_DEBUG, "Contact List search: Found name %s", (const char *)name.local8Bit());
        item->parent()->setOpen(TRUE);
        items.push_back(item);
    } else {
      void *data;
      Contact *contact = getContacts()->contact(static_cast<ContactItem*>(item)->id());
        ClientDataIterator it(contact->clientData);
        while ((data = ++it) != NULL){
          Client *client = contact->clientData.activeClient(data, it.client());
          if (client == NULL)
              continue;
          QString contactName = client->contactName(data);
          log(L_DEBUG, "Contact List search: Examining ID %s", (const char *)contactName.local8Bit());
          if (contactName.upper().find(m_search.upper())>-1) {
              log(L_DEBUG, "Contact List search: Found ID %s", (const char *)contactName.local8Bit());
              item->parent()->setOpen(TRUE);
              items.push_back(item);
              break;
          }
        }
    }
}

void UserView::dragScroll() //rewrite!?
{
    QPoint pos = QCursor::pos();
    pos = viewport()->mapFromGlobal(pos);
    if ((pos.x() < 0) || (pos.x() > viewport()->width()))
        return;
    QListViewItem *item = NULL;
    if (pos.y() < 0){
        pos = QPoint(pos.x(), -1);
        item = itemAt(pos);
    }else if (pos.y() > viewport()->height()){
        pos = QPoint(pos.x(), viewport()->height() - 1);
        item = itemAt(pos); //<== crash, it does not return item, sometimes in QGList append() no mem allocation is possible :-/ ???
        if (item){
            pos = QPoint(pos.x(), viewport()->height() - 1 + item->height());
            item = itemAt(pos);
        }
    }
    if (item)
        ensureItemVisible(item);
}

#ifndef NO_MOC_INCLUDES
#include "userview.moc"
#endif


