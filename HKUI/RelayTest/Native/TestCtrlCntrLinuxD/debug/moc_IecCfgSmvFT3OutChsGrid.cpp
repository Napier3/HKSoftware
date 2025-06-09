/****************************************************************************
** Meta object code from reading C++ file 'IecCfgSmvFT3OutChsGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/Grid/IecCfgSmvFT3OutChsGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IecCfgSmvFT3OutChsGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QFT3OutChMapComBoxDelegBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QFT3OutChMapComBoxDelegBase[] = {
    "QFT3OutChMapComBoxDelegBase\0"
};

void QFT3OutChMapComBoxDelegBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QFT3OutChMapComBoxDelegBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QFT3OutChMapComBoxDelegBase::staticMetaObject = {
    { &QIecCfgChsComBoxDelegBase::staticMetaObject, qt_meta_stringdata_QFT3OutChMapComBoxDelegBase,
      qt_meta_data_QFT3OutChMapComBoxDelegBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFT3OutChMapComBoxDelegBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFT3OutChMapComBoxDelegBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFT3OutChMapComBoxDelegBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFT3OutChMapComBoxDelegBase))
        return static_cast<void*>(const_cast< QFT3OutChMapComBoxDelegBase*>(this));
    return QIecCfgChsComBoxDelegBase::qt_metacast(_clname);
}

int QFT3OutChMapComBoxDelegBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIecCfgChsComBoxDelegBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CIecCfgSmvFT3OutChsGrid[] = {

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
      39,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   75,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIecCfgSmvFT3OutChsGrid[] = {
    "CIecCfgSmvFT3OutChsGrid\0\0bSetInitValue\0"
    "sig_UpdateInitValueBtnEnabled(bool)\0"
    "nRow,nCol\0slot_SetInitValueBtn_Clicked(int,int)\0"
};

void CIecCfgSmvFT3OutChsGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CIecCfgSmvFT3OutChsGrid *_t = static_cast<CIecCfgSmvFT3OutChsGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateInitValueBtnEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_SetInitValueBtn_Clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CIecCfgSmvFT3OutChsGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CIecCfgSmvFT3OutChsGrid::staticMetaObject = {
    { &CIecCfgChsGridBase::staticMetaObject, qt_meta_stringdata_CIecCfgSmvFT3OutChsGrid,
      qt_meta_data_CIecCfgSmvFT3OutChsGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIecCfgSmvFT3OutChsGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIecCfgSmvFT3OutChsGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIecCfgSmvFT3OutChsGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIecCfgSmvFT3OutChsGrid))
        return static_cast<void*>(const_cast< CIecCfgSmvFT3OutChsGrid*>(this));
    return CIecCfgChsGridBase::qt_metacast(_clname);
}

int CIecCfgSmvFT3OutChsGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CIecCfgSmvFT3OutChsGrid::sig_UpdateInitValueBtnEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
