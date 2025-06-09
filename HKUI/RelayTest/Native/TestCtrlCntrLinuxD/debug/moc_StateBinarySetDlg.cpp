/****************************************************************************
** Meta object code from reading C++ file 'StateBinarySetDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/StateBinarySetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateBinarySetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QStateBinarySetDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x09,
      37,   19,   19,   19, 0x09,
      58,   19,   19,   19, 0x09,
      99,   19,   19,   19, 0x09,
     132,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QStateBinarySetDlg[] = {
    "QStateBinarySetDlg\0\0slot_OkClicked()\0"
    "slot_CancelClicked()\0"
    "slot_lne_OutPutHoldTimeChangedKeyBoard()\0"
    "slot_lne_OutPutHoldTimeChanged()\0"
    "slot_chb_OutPutHoldTimeStateChanged(int)\0"
};

void QStateBinarySetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QStateBinarySetDlg *_t = static_cast<QStateBinarySetDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OkClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        case 2: _t->slot_lne_OutPutHoldTimeChangedKeyBoard(); break;
        case 3: _t->slot_lne_OutPutHoldTimeChanged(); break;
        case 4: _t->slot_chb_OutPutHoldTimeStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QStateBinarySetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QStateBinarySetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QStateBinarySetDlg,
      qt_meta_data_QStateBinarySetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QStateBinarySetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QStateBinarySetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QStateBinarySetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QStateBinarySetDlg))
        return static_cast<void*>(const_cast< QStateBinarySetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QStateBinarySetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
