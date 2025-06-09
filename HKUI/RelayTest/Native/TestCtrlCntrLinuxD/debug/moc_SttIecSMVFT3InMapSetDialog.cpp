/****************************************************************************
** Meta object code from reading C++ file 'SttIecSMVFT3InMapSetDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecSMVFT3InMapSetDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecSMVFT3InMapSetDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecSMVFT3InMapSetDialog[] = {

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
      29,   28,   28,   28, 0x0a,
      46,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecSMVFT3InMapSetDialog[] = {
    "QSttIecSMVFT3InMapSetDialog\0\0"
    "slot_OKClicked()\0slot_CancelClicked()\0"
};

void QSttIecSMVFT3InMapSetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecSMVFT3InMapSetDialog *_t = static_cast<QSttIecSMVFT3InMapSetDialog *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttIecSMVFT3InMapSetDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecSMVFT3InMapSetDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttIecSMVFT3InMapSetDialog,
      qt_meta_data_QSttIecSMVFT3InMapSetDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecSMVFT3InMapSetDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecSMVFT3InMapSetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecSMVFT3InMapSetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecSMVFT3InMapSetDialog))
        return static_cast<void*>(const_cast< QSttIecSMVFT3InMapSetDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttIecSMVFT3InMapSetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
