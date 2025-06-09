/****************************************************************************
** Meta object code from reading C++ file 'QCharacteristicEditDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/QCharacteristicEditDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCharacteristicEditDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharacteristicEditDlg[] = {

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
      24,   23,   23,   23, 0x0a,
      41,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QCharacteristicEditDlg[] = {
    "QCharacteristicEditDlg\0\0slot_OKClicked()\0"
    "slot_CancelClicked()\0"
};

void QCharacteristicEditDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharacteristicEditDlg *_t = static_cast<QCharacteristicEditDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QCharacteristicEditDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharacteristicEditDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QCharacteristicEditDlg,
      qt_meta_data_QCharacteristicEditDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharacteristicEditDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharacteristicEditDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharacteristicEditDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharacteristicEditDlg))
        return static_cast<void*>(const_cast< QCharacteristicEditDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QCharacteristicEditDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
