/****************************************************************************
** Meta object code from reading C++ file 'optionswindow.h'
**
** Created: Sat 16. Jan 16:46:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../optionswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptionsWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      40,   14,   14,   14, 0x08,
      61,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OptionsWindow[] = {
    "OptionsWindow\0\0on_chkUseIdent_clicked()\0"
    "on_btnSave_clicked()\0on_btnCancel_clicked()\0"
};

const QMetaObject OptionsWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_OptionsWindow,
      qt_meta_data_OptionsWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWindow))
        return static_cast<void*>(const_cast< OptionsWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int OptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_chkUseIdent_clicked(); break;
        case 1: on_btnSave_clicked(); break;
        case 2: on_btnCancel_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
