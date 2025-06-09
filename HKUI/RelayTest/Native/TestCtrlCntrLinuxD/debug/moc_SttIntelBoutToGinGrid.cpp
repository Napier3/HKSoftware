/****************************************************************************
** Meta object code from reading C++ file 'SttIntelBoutToGinGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/SttIntelBoutToGinGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIntelBoutToGinGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttIntelBoutToGinGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      67,   48,   23,   23, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CSttIntelBoutToGinGrid[] = {
    "CSttIntelBoutToGinGrid\0\0sig_GoutValue_Changed()\0"
    "nRowIndex,fActTime\0sig_GinRowIndex(int,float)\0"
};

void CSttIntelBoutToGinGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSttIntelBoutToGinGrid *_t = static_cast<CSttIntelBoutToGinGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_GoutValue_Changed(); break;
        case 1: _t->sig_GinRowIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CSttIntelBoutToGinGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttIntelBoutToGinGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_CSttIntelBoutToGinGrid,
      qt_meta_data_CSttIntelBoutToGinGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttIntelBoutToGinGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttIntelBoutToGinGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttIntelBoutToGinGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttIntelBoutToGinGrid))
        return static_cast<void*>(const_cast< CSttIntelBoutToGinGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int CSttIntelBoutToGinGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
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
void CSttIntelBoutToGinGrid::sig_GoutValue_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CSttIntelBoutToGinGrid::sig_GinRowIndex(int _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
