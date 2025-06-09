/****************************************************************************
** Meta object code from reading C++ file 'CommonValueDialogState.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/CommonValueDialogState.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CommonValueDialogState.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CommonValueDialogState[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      51,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   23,   23,   23, 0x08,
      96,   23,   23,   23, 0x08,
     117,   23,   23,   23, 0x08,
     139,   23,   23,   23, 0x08,
     162,   23,   23,   23, 0x08,
     191,   23,   23,   23, 0x08,
     227,  221,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CommonValueDialogState[] = {
    "CommonValueDialogState\0\0"
    "sig_CommonValueOkClicked()\0"
    "sig_DcCoffsetStateChanged()\0"
    "slot_OkClicked()\0slot_CancelClicked()\0"
    "slot_lne_TouChanged()\0slot_lne_TouKeyBoard()\0"
    "slot_lne_RepeatTimeChanged()\0"
    "slot_lne_RepeatTimeKeyBoard()\0index\0"
    "slot_cmb_DCOFFSETChanged(int)\0"
};

void CommonValueDialogState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CommonValueDialogState *_t = static_cast<CommonValueDialogState *>(_o);
        switch (_id) {
        case 0: _t->sig_CommonValueOkClicked(); break;
        case 1: _t->sig_DcCoffsetStateChanged(); break;
        case 2: _t->slot_OkClicked(); break;
        case 3: _t->slot_CancelClicked(); break;
        case 4: _t->slot_lne_TouChanged(); break;
        case 5: _t->slot_lne_TouKeyBoard(); break;
        case 6: _t->slot_lne_RepeatTimeChanged(); break;
        case 7: _t->slot_lne_RepeatTimeKeyBoard(); break;
        case 8: _t->slot_cmb_DCOFFSETChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CommonValueDialogState::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CommonValueDialogState::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CommonValueDialogState,
      qt_meta_data_CommonValueDialogState, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CommonValueDialogState::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CommonValueDialogState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CommonValueDialogState::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommonValueDialogState))
        return static_cast<void*>(const_cast< CommonValueDialogState*>(this));
    return QDialog::qt_metacast(_clname);
}

int CommonValueDialogState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CommonValueDialogState::sig_CommonValueOkClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CommonValueDialogState::sig_DcCoffsetStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
