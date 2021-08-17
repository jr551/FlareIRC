/****************************************************************************
** Meta object code from reading C++ file 'ircsocket.h'
**
** Created: Sat 16. Jan 16:46:16 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ircsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ircsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IRCConnection[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      31,   14,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      88,   73,   14,   14, 0x05,
     146,  123,   14,   14, 0x05,
     202,  187,   14,   14, 0x05,
     258,  232,   14,   14, 0x05,
     332,  306,   14,   14, 0x05,
     399,  381,   14,   14, 0x05,
     444,  440,   14,   14, 0x05,
     499,  471,   14,   14, 0x05,
     546,  541,   14,   14, 0x05,
     585,  569,   14,   14, 0x05,
     631,  617,   14,   14, 0x05,
     679,  665,   14,   14, 0x05,
     723,  713,   14,   14, 0x05,
     759,  753,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     782,   14,   14,   14, 0x08,
     817,  805,   14,   14, 0x08,
     860,   14,   14,   14, 0x08,
     883,   14,   14,   14, 0x08,
     921,  909,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IRCConnection[] = {
    "IRCConnection\0\0IRC_Connected()\0"
    "IRC_Disconnected()\0IRC_ReadyForCommands()\0"
    "source,channel\0IRC_JoinedChannel(QString,QString)\0"
    "source,channel,quitMsg\0"
    "IRC_LeftChannel(QString,QString,QString)\0"
    "source,quitMsg\0IRC_UserQuit(QString,QString)\0"
    "source,channel,whom,modes\0"
    "IRC_ModeChange(QString,QString,QString,QString)\0"
    "source,context,msg,action\0"
    "IRC_ChannelMessage(QString,QString,QString,bool)\0"
    "source,msg,action\0"
    "IRC_PrivateMessage(QString,QString,bool)\0"
    "msg\0IRC_ServerMessage(QString)\0"
    "source,channel,whom,message\0"
    "IRC_Kick(QString,QString,QString,QString)\0"
    "line\0IRC_MOTD_Line(QString)\0oldNick,newNick\0"
    "IRC_NickChange(QString,QString)\0"
    "channel,users\0IRC_UserList(QString,QStringList)\0"
    "channel,topic\0IRC_ChannelTopic(QString,QString)\0"
    "user,data\0IRC_UserInfo(QString,QString)\0"
    "error\0IRC_Error(e_IRC_Error)\0"
    "Connection_ReadyRead()\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "Connection_Connected()\0Connection_Disconnected()\0"
    "socketState\0"
    "Connection_StateChanged(QAbstractSocket::SocketState)\0"
};

const QMetaObject IRCConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IRCConnection,
      qt_meta_data_IRCConnection, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IRCConnection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IRCConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IRCConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IRCConnection))
        return static_cast<void*>(const_cast< IRCConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int IRCConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: IRC_Connected(); break;
        case 1: IRC_Disconnected(); break;
        case 2: IRC_ReadyForCommands(); break;
        case 3: IRC_JoinedChannel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: IRC_LeftChannel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: IRC_UserQuit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: IRC_ModeChange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 7: IRC_ChannelMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 8: IRC_PrivateMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 9: IRC_ServerMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: IRC_Kick((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 11: IRC_MOTD_Line((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: IRC_NickChange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: IRC_UserList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 14: IRC_ChannelTopic((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: IRC_UserInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: IRC_Error((*reinterpret_cast< e_IRC_Error(*)>(_a[1]))); break;
        case 17: Connection_ReadyRead(); break;
        case 18: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 19: Connection_Connected(); break;
        case 20: Connection_Disconnected(); break;
        case 21: Connection_StateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void IRCConnection::IRC_Connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void IRCConnection::IRC_Disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void IRCConnection::IRC_ReadyForCommands()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void IRCConnection::IRC_JoinedChannel(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IRCConnection::IRC_LeftChannel(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void IRCConnection::IRC_UserQuit(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void IRCConnection::IRC_ModeChange(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void IRCConnection::IRC_ChannelMessage(QString _t1, QString _t2, QString _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void IRCConnection::IRC_PrivateMessage(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void IRCConnection::IRC_ServerMessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void IRCConnection::IRC_Kick(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void IRCConnection::IRC_MOTD_Line(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void IRCConnection::IRC_NickChange(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void IRCConnection::IRC_UserList(QString _t1, QStringList _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void IRCConnection::IRC_ChannelTopic(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void IRCConnection::IRC_UserInfo(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void IRCConnection::IRC_Error(e_IRC_Error _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_END_MOC_NAMESPACE
