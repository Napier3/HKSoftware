/****************************************************************************
** Meta object code from reading C++ file 'SttReplayWaveformEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/TransPlay/SttReplayWaveformEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttReplayWaveformEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SttReplayWaveformEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   28,   28,   28, 0x0a,
      88,   28,   28,   28, 0x0a,
     122,   28,   28,   28, 0x0a,
     148,   28,   28,   28, 0x0a,
     181,   28,   28,   28, 0x0a,
     212,   28,   28,   28, 0x0a,
     248,  241,   28,   28, 0x0a,
     277,   28,   28,   28, 0x0a,
     309,   28,   28,   28, 0x0a,
     335,   28,   28,   28, 0x0a,
     368,   28,   28,   28, 0x0a,
     399,   28,   28,   28, 0x0a,
     430,   28,   28,   28, 0x0a,
     465,  241,   28,   28, 0x0a,
     500,   28,   28,   28, 0x0a,
     517,   28,   28,   28, 0x0a,
     534,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SttReplayWaveformEditWidget[] = {
    "SttReplayWaveformEditWidget\0\0"
    "sig_UpdateWaveSelectBack(bool)\0"
    "slot_InsertRbuttonClicked()\0"
    "slot_InsertNormalRbuttonClicked()\0"
    "slot_Insert_ZeroChanged()\0"
    "slot_Insert_DestinationChanged()\0"
    "slot_Insert_BeginTimeChanged()\0"
    "slot_Insert_EndTimeChanged()\0nIndex\0"
    "slot_Insert_TypeChanged(int)\0"
    "slot_Insert_CycleIndexChanged()\0"
    "slot_Delete_ZeroChanged()\0"
    "slot_Delete_DestinationChanged()\0"
    "slot_InsertNormal_ValChanged()\0"
    "slot_InsertNormal_CurChanged()\0"
    "slot_InsertNormal_OutTimeChanged()\0"
    "slot_InsertNormal_TypeChanged(int)\0"
    "slot_Insert_OK()\0slot_Delete_OK()\0"
    "slot_Wave_ReCovery()\0"
};

void SttReplayWaveformEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SttReplayWaveformEditWidget *_t = static_cast<SttReplayWaveformEditWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateWaveSelectBack((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_InsertRbuttonClicked(); break;
        case 2: _t->slot_InsertNormalRbuttonClicked(); break;
        case 3: _t->slot_Insert_ZeroChanged(); break;
        case 4: _t->slot_Insert_DestinationChanged(); break;
        case 5: _t->slot_Insert_BeginTimeChanged(); break;
        case 6: _t->slot_Insert_EndTimeChanged(); break;
        case 7: _t->slot_Insert_TypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_Insert_CycleIndexChanged(); break;
        case 9: _t->slot_Delete_ZeroChanged(); break;
        case 10: _t->slot_Delete_DestinationChanged(); break;
        case 11: _t->slot_InsertNormal_ValChanged(); break;
        case 12: _t->slot_InsertNormal_CurChanged(); break;
        case 13: _t->slot_InsertNormal_OutTimeChanged(); break;
        case 14: _t->slot_InsertNormal_TypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_Insert_OK(); break;
        case 16: _t->slot_Delete_OK(); break;
        case 17: _t->slot_Wave_ReCovery(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SttReplayWaveformEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SttReplayWaveformEditWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SttReplayWaveformEditWidget,
      qt_meta_data_SttReplayWaveformEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SttReplayWaveformEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SttReplayWaveformEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SttReplayWaveformEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SttReplayWaveformEditWidget))
        return static_cast<void*>(const_cast< SttReplayWaveformEditWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SttReplayWaveformEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SttReplayWaveformEditWidget::sig_UpdateWaveSelectBack(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
