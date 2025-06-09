/****************************************************************************
** Meta object code from reading C++ file 'PowerDirBinarySignalDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/PowerDirBinarySignalDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PowerDirBinarySignalDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPowerDirBinarySignalDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      47,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QPowerDirBinarySignalDlg[] = {
    "QPowerDirBinarySignalDlg\0\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
};

void QPowerDirBinarySignalDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPowerDirBinarySignalDlg *_t = static_cast<QPowerDirBinarySignalDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOk_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QPowerDirBinarySignalDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPowerDirBinarySignalDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QPowerDirBinarySignalDlg,
      qt_meta_data_QPowerDirBinarySignalDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPowerDirBinarySignalDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPowerDirBinarySignalDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPowerDirBinarySignalDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPowerDirBinarySignalDlg))
        return static_cast<void*>(const_cast< QPowerDirBinarySignalDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QPowerDirBinarySignalDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
