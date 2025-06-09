/****************************************************************************
** Meta object code from reading C++ file 'IecCfgDataGridBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/Grid/IecCfgDataGridBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IecCfgDataGridBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QFiberSelectedComBoxDelegBase[] = {

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

static const char qt_meta_stringdata_QFiberSelectedComBoxDelegBase[] = {
    "QFiberSelectedComBoxDelegBase\0"
};

void QFiberSelectedComBoxDelegBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QFiberSelectedComBoxDelegBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QFiberSelectedComBoxDelegBase::staticMetaObject = {
    { &QExBaseListComBoxDelegBase::staticMetaObject, qt_meta_stringdata_QFiberSelectedComBoxDelegBase,
      qt_meta_data_QFiberSelectedComBoxDelegBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFiberSelectedComBoxDelegBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFiberSelectedComBoxDelegBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFiberSelectedComBoxDelegBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFiberSelectedComBoxDelegBase))
        return static_cast<void*>(const_cast< QFiberSelectedComBoxDelegBase*>(this));
    return QExBaseListComBoxDelegBase::qt_metacast(_clname);
}

int QFiberSelectedComBoxDelegBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListComBoxDelegBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CIecCfgDataGridBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   21,   20,   20, 0x05,
      85,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     136,  126,   20,   20, 0x0a,
     164,   21,   20,   20, 0x0a,
     208,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIecCfgDataGridBase[] = {
    "CIecCfgDataGridBase\0\0pIecCfgDataBase,nRow\0"
    "sig_UpdateCheckState(CIecCfgDataBase*,int)\0"
    "sig_FiberSelUpdate(CIecCfgDataBase*,int)\0"
    "nRow,nCol\0slot_doubleClicked(int,int)\0"
    "slot_UpdateCheckState(CIecCfgDataBase*,int)\0"
    "slot_FiberSelUpdate(CIecCfgDataBase*,int)\0"
};

void CIecCfgDataGridBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CIecCfgDataGridBase *_t = static_cast<CIecCfgDataGridBase *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateCheckState((*reinterpret_cast< CIecCfgDataBase*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_FiberSelUpdate((*reinterpret_cast< CIecCfgDataBase*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_UpdateCheckState((*reinterpret_cast< CIecCfgDataBase*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_FiberSelUpdate((*reinterpret_cast< CIecCfgDataBase*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CIecCfgDataGridBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CIecCfgDataGridBase::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CIecCfgDataGridBase,
      qt_meta_data_CIecCfgDataGridBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIecCfgDataGridBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIecCfgDataGridBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIecCfgDataGridBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIecCfgDataGridBase))
        return static_cast<void*>(const_cast< CIecCfgDataGridBase*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CIecCfgDataGridBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CIecCfgDataGridBase::sig_UpdateCheckState(CIecCfgDataBase * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CIecCfgDataGridBase::sig_FiberSelUpdate(CIecCfgDataBase * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
