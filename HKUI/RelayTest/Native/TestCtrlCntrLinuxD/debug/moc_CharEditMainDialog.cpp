/****************************************************************************
** Meta object code from reading C++ file 'CharEditMainDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/InternationalModeUI/CharEditMainDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharEditMainDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditMainDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      50,   21,   20,   20, 0x0a,
     112,   96,   20,   20, 0x0a,
     154,   20,   20,   20, 0x0a,
     176,   20,   20,   20, 0x0a,
     193,   20,   20,   20, 0x0a,
     214,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditMainDialog[] = {
    "QCharEditMainDialog\0\0pCharacteristic,bCharChanged\0"
    "slot_UpdateDrawCharacters(CExBaseObject*,int)\0"
    "pCharacteristic\0"
    "slot_UpdateDrawCharacters(CExBaseObject*)\0"
    "slot_LeftButtonDown()\0slot_OKClicked()\0"
    "slot_CancelClicked()\0slot_ImportCharClicked()\0"
};

void QCharEditMainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditMainDialog *_t = static_cast<QCharEditMainDialog *>(_o);
        switch (_id) {
        case 0: _t->slot_UpdateDrawCharacters((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_UpdateDrawCharacters((*reinterpret_cast< CExBaseObject*(*)>(_a[1]))); break;
        case 2: _t->slot_LeftButtonDown(); break;
        case 3: _t->slot_OKClicked(); break;
        case 4: _t->slot_CancelClicked(); break;
        case 5: _t->slot_ImportCharClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditMainDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditMainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QCharEditMainDialog,
      qt_meta_data_QCharEditMainDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditMainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditMainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditMainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditMainDialog))
        return static_cast<void*>(const_cast< QCharEditMainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QCharEditMainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
