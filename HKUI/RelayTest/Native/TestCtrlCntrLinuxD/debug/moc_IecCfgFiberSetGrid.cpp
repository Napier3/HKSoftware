/****************************************************************************
** Meta object code from reading C++ file 'IecCfgFiberSetGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/Grid/IecCfgFiberSetGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IecCfgFiberSetGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CIecCfgFiberSetGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIecCfgFiberSetGrid[] = {
    "CIecCfgFiberSetGrid\0\0nRow,nCol\0"
    "slot_doubleClicked(int,int)\0"
};

void CIecCfgFiberSetGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CIecCfgFiberSetGrid *_t = static_cast<CIecCfgFiberSetGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CIecCfgFiberSetGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CIecCfgFiberSetGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CIecCfgFiberSetGrid,
      qt_meta_data_CIecCfgFiberSetGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIecCfgFiberSetGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIecCfgFiberSetGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIecCfgFiberSetGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIecCfgFiberSetGrid))
        return static_cast<void*>(const_cast< CIecCfgFiberSetGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CIecCfgFiberSetGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
