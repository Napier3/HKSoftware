/****************************************************************************
** Meta object code from reading C++ file 'SttFileSelectGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/PopupDialog/SttFileSelectGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttFileSelectGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttFileSelectGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   51,   19,   19, 0x0a,
      83,   20,   19,   19, 0x0a,
     162,  110,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSttFileSelectGrid[] = {
    "CSttFileSelectGrid\0\0nRow\0"
    "sig_UpdateCheckState(int)\0nRow,nCol\0"
    "slot_clicked(int,int)\0slot_UpdateCheckState(int)\0"
    "currentRow,currentColumn,previousRow,previousColumn\0"
    "slot_CurrentCellChanged(int,int,int,int)\0"
};

void CSttFileSelectGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSttFileSelectGrid *_t = static_cast<CSttFileSelectGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateCheckState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_UpdateCheckState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_CurrentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CSttFileSelectGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttFileSelectGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CSttFileSelectGrid,
      qt_meta_data_CSttFileSelectGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttFileSelectGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttFileSelectGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttFileSelectGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttFileSelectGrid))
        return static_cast<void*>(const_cast< CSttFileSelectGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CSttFileSelectGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void CSttFileSelectGrid::sig_UpdateCheckState(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
