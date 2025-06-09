/****************************************************************************
** Meta object code from reading C++ file 'SttIntelGoutToBinGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/SttIntelGoutToBinGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIntelGoutToBinGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttIntelGoutToBinGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      48,   23,   23,   23, 0x05,
      80,   70,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     115,  102,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CSttIntelGoutToBinGrid[] = {
    "CSttIntelGoutToBinGrid\0\0sig_GoutValue_Changed()\0"
    "sig_GoutMap_Changed()\0nRowIndex\0"
    "sig_GoutRowIndex(int)\0nrow,ncolumn\0"
    "slot_GridCellClicked(int,int)\0"
};

void CSttIntelGoutToBinGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSttIntelGoutToBinGrid *_t = static_cast<CSttIntelGoutToBinGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_GoutValue_Changed(); break;
        case 1: _t->sig_GoutMap_Changed(); break;
        case 2: _t->sig_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_GridCellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CSttIntelGoutToBinGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttIntelGoutToBinGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CSttIntelGoutToBinGrid,
      qt_meta_data_CSttIntelGoutToBinGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttIntelGoutToBinGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttIntelGoutToBinGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttIntelGoutToBinGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttIntelGoutToBinGrid))
        return static_cast<void*>(const_cast< CSttIntelGoutToBinGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CSttIntelGoutToBinGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CSttIntelGoutToBinGrid::sig_GoutValue_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CSttIntelGoutToBinGrid::sig_GoutMap_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CSttIntelGoutToBinGrid::sig_GoutRowIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
