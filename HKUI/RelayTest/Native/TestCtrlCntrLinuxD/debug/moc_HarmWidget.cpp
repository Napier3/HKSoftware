/****************************************************************************
** Meta object code from reading C++ file 'HarmWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Harm/HarmWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HarmWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHarmWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      29,   12,   12,   12, 0x05,
      50,   47,   12,   12, 0x05,
      78,   47,   12,   12, 0x05,
     108,  106,   12,   12, 0x05,
     139,  106,   12,   12, 0x05,
     169,   12,   12,   12, 0x05,
     193,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     218,  211,   12,   12, 0x0a,
     244,  211,   12,   12, 0x0a,
     277,  270,   12,   12, 0x0a,
     305,   12,   12,   12, 0x0a,
     330,   12,   12,   12, 0x0a,
     357,   12,   12,   12, 0x0a,
     382,   12,   12,   12, 0x0a,
     409,   12,   12,   12, 0x0a,
     434,   12,   12,   12, 0x0a,
     464,   12,   12,   12, 0x0a,
     494,   12,   12,   12, 0x0a,
     520,   12,   12,   12, 0x0a,
     542,   12,   12,   12, 0x0a,
     564,   12,   12,   12, 0x0a,
     587,   12,   12,   12, 0x0a,
     607,   12,   12,   12, 0x0a,
     631,   12,   12,   12, 0x0a,
     663,  656,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QHarmWidget[] = {
    "QHarmWidget\0\0sig_SetToZero()\0"
    "sig_LockChanged()\0,,\0sig_AddValue(int,int,float)\0"
    "sig_DelValue(int,int,float)\0,\0"
    "sig_SelectDataChanged(int,int)\0"
    "sig_WaveValueChanged(int,int)\0"
    "sig_ChIndexChanged(int)\0sig_updataParas()\0"
    "nIndex\0slot_UChannelChanged(int)\0"
    "slot_IChannelChanged(int)\0bState\0"
    "slot_AutoStateChanged(bool)\0"
    "slot_WaveValueUChanged()\0"
    "slot_ChanelValueUChanged()\0"
    "slot_WaveValueIChanged()\0"
    "slot_ChanelValueIChanged()\0"
    "slot_ChIndexChanged(int)\0"
    "slot_lne_BasicHarmHzChanged()\0"
    "slot_lne_BasicHarmHzClicked()\0"
    "slot_pbn_SetZeroClicked()\0"
    "slot_pbn_AddClicked()\0slot_pbn_DelClicked()\0"
    "slot_pbn_LockClicked()\0slot_pbn_Estimate()\0"
    "slot_VolSelBtnClicked()\0"
    "slot_CurrSelBtnClicked()\0nValue\0"
    "slot_ResetChangeFlag(int)\0"
};

void QHarmWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHarmWidget *_t = static_cast<QHarmWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_SetToZero(); break;
        case 1: _t->sig_LockChanged(); break;
        case 2: _t->sig_AddValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 3: _t->sig_DelValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 4: _t->sig_SelectDataChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->sig_WaveValueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->sig_ChIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->sig_updataParas(); break;
        case 8: _t->slot_UChannelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_IChannelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_AutoStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->slot_WaveValueUChanged(); break;
        case 12: _t->slot_ChanelValueUChanged(); break;
        case 13: _t->slot_WaveValueIChanged(); break;
        case 14: _t->slot_ChanelValueIChanged(); break;
        case 15: _t->slot_ChIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slot_lne_BasicHarmHzChanged(); break;
        case 17: _t->slot_lne_BasicHarmHzClicked(); break;
        case 18: _t->slot_pbn_SetZeroClicked(); break;
        case 19: _t->slot_pbn_AddClicked(); break;
        case 20: _t->slot_pbn_DelClicked(); break;
        case 21: _t->slot_pbn_LockClicked(); break;
        case 22: _t->slot_pbn_Estimate(); break;
        case 23: _t->slot_VolSelBtnClicked(); break;
        case 24: _t->slot_CurrSelBtnClicked(); break;
        case 25: _t->slot_ResetChangeFlag((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHarmWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHarmWidget::staticMetaObject = {
    { &QParaSetBase::staticMetaObject, qt_meta_stringdata_QHarmWidget,
      qt_meta_data_QHarmWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHarmWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHarmWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHarmWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHarmWidget))
        return static_cast<void*>(const_cast< QHarmWidget*>(this));
    return QParaSetBase::qt_metacast(_clname);
}

int QHarmWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QParaSetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void QHarmWidget::sig_SetToZero()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QHarmWidget::sig_LockChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QHarmWidget::sig_AddValue(int _t1, int _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QHarmWidget::sig_DelValue(int _t1, int _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QHarmWidget::sig_SelectDataChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QHarmWidget::sig_WaveValueChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QHarmWidget::sig_ChIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QHarmWidget::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
