/****************************************************************************
** Meta object code from reading C++ file 'WeakSetGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/SysParas/WeakSetGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WeakSetGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWeakSetGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x09,
      52,   13,   13,   13, 0x09,
      84,   13,   13,   13, 0x09,
     113,  109,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CWeakSetGrid[] = {
    "CWeakSetGrid\0\0nRow,nCol\0"
    "slot_OnItemClicked(int,int)\0"
    "slot_ThreePhaseEqualActlicked()\0"
    "slot_AllEqualActlicked()\0pos\0"
    "slot_GridShowMenu(QPoint)\0"
};

void CWeakSetGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CWeakSetGrid *_t = static_cast<CWeakSetGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_OnItemClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_ThreePhaseEqualActlicked(); break;
        case 2: _t->slot_AllEqualActlicked(); break;
        case 3: _t->slot_GridShowMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CWeakSetGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CWeakSetGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CWeakSetGrid,
      qt_meta_data_CWeakSetGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CWeakSetGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CWeakSetGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CWeakSetGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWeakSetGrid))
        return static_cast<void*>(const_cast< CWeakSetGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CWeakSetGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
