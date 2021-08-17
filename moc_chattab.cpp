/****************************************************************************
** Meta object code from reading C++ file 'chattab.h'
**
** Created: Wed Jan 13 11:44:38 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chattab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chattab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IRCUserItem[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_IRCUserItem[] = {
    "IRCUserItem\0"
};

const QMetaObject IRCUserItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IRCUserItem,
      qt_meta_data_IRCUserItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IRCUserItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IRCUserItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IRCUserItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IRCUserItem))
        return static_cast<void*>(const_cast< IRCUserItem*>(this));
    if (!strcmp(_clname, "QTreeWidgetItem"))
        return static_cast< QTreeWidgetItem*>(const_cast< IRCUserItem*>(this));
    return QObject::qt_metacast(_clname);
}

int IRCUserItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ChatTab[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,    9,    8,    8, 0x08,
      58,   54,    8,    8, 0x08,
     106,    9,    8,    8, 0x08,
     146,    8,    8,    8, 0x08,
     178,  173,    8,    8, 0x08,
     212,  204,    8,    8, 0x08,
     239,    8,    8,    8, 0x08,
     260,    8,    8,    8, 0x08,
     283,    8,    8,    8, 0x08,
     305,    8,    8,    8, 0x08,
     326,    8,    8,    8, 0x08,
     350,    8,    8,    8, 0x08,
     373,    8,    8,    8, 0x08,
     405,  399,    8,    8, 0x08,
     439,  434,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ChatTab[] = {
    "ChatTab\0\0index\0on_cmbOptions_currentIndexChanged(int)\0"
    "pos\0on_treeUsers_customContextMenuRequested(QPoint)\0"
    "on_treeUsers_doubleClicked(QModelIndex)\0"
    "on_txtChat_returnPressed()\0nick\0"
    "IRC_DoNickChange(QString)\0channel\0"
    "IRC_DoChannelJoin(QString)\0"
    "IRC_Action_PM_User()\0IRC_Action_Kick_User()\0"
    "IRC_Action_Ban_User()\0IRC_Action_Op_User()\0"
    "IRC_Action_Voice_User()\0IRC_Action_DeOp_User()\0"
    "IRC_Action_DeVoice_User()\0topic\0"
    "IRC_SetChannelTopic(QString)\0mode\0"
    "IRC_SetChannelMode(QString)\0"
};

const QMetaObject ChatTab::staticMetaObject = {
    { &TalkWindowTab::staticMetaObject, qt_meta_stringdata_ChatTab,
      qt_meta_data_ChatTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChatTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChatTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChatTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatTab))
        return static_cast<void*>(const_cast< ChatTab*>(this));
    return TalkWindowTab::qt_metacast(_clname);
}

int ChatTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TalkWindowTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmbOptions_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_treeUsers_customContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: on_treeUsers_doubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: on_txtChat_returnPressed(); break;
        case 4: IRC_DoNickChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: IRC_DoChannelJoin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: IRC_Action_PM_User(); break;
        case 7: IRC_Action_Kick_User(); break;
        case 8: IRC_Action_Ban_User(); break;
        case 9: IRC_Action_Op_User(); break;
        case 10: IRC_Action_Voice_User(); break;
        case 11: IRC_Action_DeOp_User(); break;
        case 12: IRC_Action_DeVoice_User(); break;
        case 13: IRC_SetChannelTopic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: IRC_SetChannelMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
