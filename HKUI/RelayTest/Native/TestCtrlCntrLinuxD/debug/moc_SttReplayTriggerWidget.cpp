/****************************************************************************
** Meta object code from reading C++ file 'SttReplayTriggerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/TransPlay/SttReplayTriggerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttReplayTriggerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttReplayTriggerWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x0a,
      46,   24,   24,   24, 0x0a,
      71,   24,   24,   24, 0x0a,
      93,   24,   24,   24, 0x0a,
     120,   24,   24,   24, 0x0a,
     151,   24,   24,   24, 0x0a,
     173,   24,   24,   24, 0x0a,
     196,   24,   24,   24, 0x0a,
     222,   24,   24,   24, 0x0a,
     251,   24,   24,   24, 0x0a,
     280,   24,   24,   24, 0x0a,
     309,   24,   24,   24, 0x0a,
     338,   24,   24,   24, 0x0a,
     367,   24,   24,   24, 0x0a,
     396,   24,   24,   24, 0x0a,
     425,   24,   24,   24, 0x0a,
     454,   24,   24,   24, 0x0a,
     483,   24,   24,   24, 0x0a,
     513,   24,   24,   24, 0x0a,
     546,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSttReplayTriggerWidget[] = {
    "CSttReplayTriggerWidget\0\0slot_NoTripClicked()\0"
    "slot_ManualTripClicked()\0slot_GpsTripClicked()\0"
    "slot_BinaryInTripClicked()\0"
    "slot_TripAfterModeChanged(int)\0"
    "slot_GpsTimeChanged()\0slot_CycleNumChanged()\0"
    "slot_SttLineEditChanged()\0"
    "slot_ck_In1StateChanged(int)\0"
    "slot_ck_In2StateChanged(int)\0"
    "slot_ck_In3StateChanged(int)\0"
    "slot_ck_In4StateChanged(int)\0"
    "slot_ck_In5StateChanged(int)\0"
    "slot_ck_In6StateChanged(int)\0"
    "slot_ck_In7StateChanged(int)\0"
    "slot_ck_In8StateChanged(int)\0"
    "slot_ck_In9StateChanged(int)\0"
    "slot_ck_In10StateChanged(int)\0"
    "slot_radio_AndStateChanged(bool)\0"
    "slot_radio_OrStateChanged(bool)\0"
};

void CSttReplayTriggerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSttReplayTriggerWidget *_t = static_cast<CSttReplayTriggerWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_NoTripClicked(); break;
        case 1: _t->slot_ManualTripClicked(); break;
        case 2: _t->slot_GpsTripClicked(); break;
        case 3: _t->slot_BinaryInTripClicked(); break;
        case 4: _t->slot_TripAfterModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_GpsTimeChanged(); break;
        case 6: _t->slot_CycleNumChanged(); break;
        case 7: _t->slot_SttLineEditChanged(); break;
        case 8: _t->slot_ck_In1StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_ck_In2StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_ck_In3StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_ck_In4StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_ck_In5StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_ck_In6StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slot_ck_In7StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_ck_In8StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slot_ck_In9StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->slot_ck_In10StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->slot_radio_AndStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->slot_radio_OrStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CSttReplayTriggerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttReplayTriggerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSttReplayTriggerWidget,
      qt_meta_data_CSttReplayTriggerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttReplayTriggerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttReplayTriggerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttReplayTriggerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttReplayTriggerWidget))
        return static_cast<void*>(const_cast< CSttReplayTriggerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSttReplayTriggerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
