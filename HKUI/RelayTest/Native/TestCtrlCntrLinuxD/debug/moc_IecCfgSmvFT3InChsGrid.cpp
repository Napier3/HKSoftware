/****************************************************************************
** Meta object code from reading C++ file 'IecCfgSmvFT3InChsGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/Grid/IecCfgSmvFT3InChsGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IecCfgSmvFT3InChsGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CIecCfgSmvFT3InChsGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      40,   24,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   70,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIecCfgSmvFT3InChsGrid[] = {
    "CIecCfgSmvFT3InChsGrid\0\0isBinMapEnabled\0"
    "sig_UpdateBinMapEnabled(bool)\0nRow,nCol\0"
    "slot_BinMap_Clicked(int,int)\0"
};

void CIecCfgSmvFT3InChsGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CIecCfgSmvFT3InChsGrid *_t = static_cast<CIecCfgSmvFT3InChsGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateBinMapEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_BinMap_Clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CIecCfgSmvFT3InChsGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CIecCfgSmvFT3InChsGrid::staticMetaObject = {
    { &CIecCfgChsGridBase::staticMetaObject, qt_meta_stringdata_CIecCfgSmvFT3InChsGrid,
      qt_meta_data_CIecCfgSmvFT3InChsGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIecCfgSmvFT3InChsGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIecCfgSmvFT3InChsGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIecCfgSmvFT3InChsGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIecCfgSmvFT3InChsGrid))
        return static_cast<void*>(const_cast< CIecCfgSmvFT3InChsGrid*>(this));
    return CIecCfgChsGridBase::qt_metacast(_clname);
}

int CIecCfgSmvFT3InChsGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CIecCfgChsGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CIecCfgSmvFT3InChsGrid::sig_UpdateBinMapEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
