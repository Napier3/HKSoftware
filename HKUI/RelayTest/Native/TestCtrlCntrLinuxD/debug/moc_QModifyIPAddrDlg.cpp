/****************************************************************************
** Meta object code from reading C++ file 'QModifyIPAddrDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/NetworkConfig/QModifyIPAddrDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QModifyIPAddrDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QModifyIPAddrDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   17,   17,   17, 0x08,
      95,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QModifyIPAddrDlg[] = {
    "QModifyIPAddrDlg\0\0strIP,strSubNetMask\0"
    "sig_ModifyTesterIP_OK(QString&,QString)\0"
    "slot_OKClicked()\0slot_CancelClicked()\0"
};

void QModifyIPAddrDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QModifyIPAddrDlg *_t = static_cast<QModifyIPAddrDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_ModifyTesterIP_OK((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slot_OKClicked(); break;
        case 2: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QModifyIPAddrDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QModifyIPAddrDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QModifyIPAddrDlg,
      qt_meta_data_QModifyIPAddrDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QModifyIPAddrDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QModifyIPAddrDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QModifyIPAddrDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QModifyIPAddrDlg))
        return static_cast<void*>(const_cast< QModifyIPAddrDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QModifyIPAddrDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QModifyIPAddrDlg::sig_ModifyTesterIP_OK(QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
