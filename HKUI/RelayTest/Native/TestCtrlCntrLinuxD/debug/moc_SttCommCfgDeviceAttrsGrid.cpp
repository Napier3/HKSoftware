/****************************************************************************
** Meta object code from reading C++ file 'SttCommCfgDeviceAttrsGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommConfigurationDlg/CommCfg/SttCommCfgDeviceAttrsGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttCommCfgDeviceAttrsGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SttCCommCfgDeviceAttrsGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,
      53,   27,   27,   27, 0x05,
      75,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
     108,  100,   27,   27, 0x0a,
     139,  100,   27,   27, 0x0a,
     171,  100,   27,   27, 0x0a,
     203,  100,   27,   27, 0x0a,
     240,  234,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SttCCommCfgDeviceAttrsGrid[] = {
    "SttCCommCfgDeviceAttrsGrid\0\0"
    "sig_ChangedDevAddr(long)\0sig_ChangedNetTable()\0"
    "sig_ChangedSerialTable()\0strText\0"
    "slot_CbPortNumChanged(QString)\0"
    "slot_CbBoudRateChanged(QString)\0"
    "slot_CbByteSizeChanged(QString)\0"
    "slot_CbStopBitChanged(QString)\0index\0"
    "slot_CbParityChanged(int)\0"
};

void SttCCommCfgDeviceAttrsGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SttCCommCfgDeviceAttrsGrid *_t = static_cast<SttCCommCfgDeviceAttrsGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_ChangedDevAddr((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 1: _t->sig_ChangedNetTable(); break;
        case 2: _t->sig_ChangedSerialTable(); break;
        case 3: _t->slot_CbPortNumChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slot_CbBoudRateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slot_CbByteSizeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->slot_CbStopBitChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->slot_CbParityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SttCCommCfgDeviceAttrsGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SttCCommCfgDeviceAttrsGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_SttCCommCfgDeviceAttrsGrid,
      qt_meta_data_SttCCommCfgDeviceAttrsGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SttCCommCfgDeviceAttrsGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SttCCommCfgDeviceAttrsGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SttCCommCfgDeviceAttrsGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SttCCommCfgDeviceAttrsGrid))
        return static_cast<void*>(const_cast< SttCCommCfgDeviceAttrsGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int SttCCommCfgDeviceAttrsGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SttCCommCfgDeviceAttrsGrid::sig_ChangedDevAddr(long _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SttCCommCfgDeviceAttrsGrid::sig_ChangedNetTable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SttCCommCfgDeviceAttrsGrid::sig_ChangedSerialTable()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
