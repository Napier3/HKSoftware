/****************************************************************************
** Meta object code from reading C++ file 'HarmParaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Harm/HarmParaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HarmParaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHarmParaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      42,   16,   16,   16, 0x05,
      66,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      99,   93,   16,   16, 0x0a,
     132,   93,   16,   16, 0x0a,
     168,   16,   16,   16, 0x0a,
     192,   16,   16,   16, 0x0a,
     214,   16,   16,   16, 0x0a,
     237,   16,   16,   16, 0x0a,
     264,   16,   16,   16, 0x0a,
     288,   16,   16,   16, 0x0a,
     310,   16,   16,   16, 0x0a,
     333,   16,   16,   16, 0x0a,
     360,   16,   16,   16, 0x0a,
     390,   16,   16,   16, 0x0a,
     419,   16,   16,   16, 0x0a,
     448,   16,   16,   16, 0x0a,
     477,   16,   16,   16, 0x0a,
     506,   16,   16,   16, 0x0a,
     535,   16,   16,   16, 0x0a,
     564,   16,   16,   16, 0x0a,
     593,   16,   16,   16, 0x0a,
     622,   16,   16,   16, 0x0a,
     651,   16,   16,   16, 0x0a,
     681,   16,   16,   16, 0x0a,
     711,   16,   16,   16, 0x0a,
     741,   16,   16,   16, 0x0a,
     771,   16,   16,   16, 0x0a,
     801,   16,   16,   16, 0x0a,
     831,   16,   16,   16, 0x0a,
     861,   16,   16,   16, 0x0a,
     891,   16,   16,   16, 0x0a,
     921,   16,   16,   16, 0x0a,
     951,   16,   16,   16, 0x0a,
     982,   16,   16,   16, 0x0a,
    1015,   16,   16,   16, 0x0a,
    1047,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QHarmParaWidget[] = {
    "QHarmParaWidget\0\0sig_OutPutStateChanged()\0"
    "sig_InPutStateChanged()\0"
    "sig_AutoStateChanged(bool)\0index\0"
    "slot_cmb_ChanelIndexChanged(int)\0"
    "slot_cmb_HarmOrderIndexChanged(int)\0"
    "slot_lne_StartChanged()\0slot_lne_EndChanged()\0"
    "slot_lne_StepChanged()\0"
    "slot_lne_StepTimeChanged()\0"
    "slot_lne_StartClicked()\0slot_lne_EndClicked()\0"
    "slot_lne_StepClicked()\0"
    "slot_lne_StepTimeClicked()\0"
    "slot_ck_AutoStateChanged(int)\0"
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
    "slot_ck_Out1StateChanged(int)\0"
    "slot_ck_Out2StateChanged(int)\0"
    "slot_ck_Out3StateChanged(int)\0"
    "slot_ck_Out4StateChanged(int)\0"
    "slot_ck_Out5StateChanged(int)\0"
    "slot_ck_Out6StateChanged(int)\0"
    "slot_ck_Out7StateChanged(int)\0"
    "slot_ck_Out8StateChanged(int)\0"
    "slot_ck_Out9StateChanged(int)\0"
    "slot_ck_Out10StateChanged(int)\0"
    "slot_radio_AndStateChanged(bool)\0"
    "slot_radio_OrStateChanged(bool)\0"
    "slot_radio_HarmGradTypeStateChanged(bool)\0"
};

void QHarmParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHarmParaWidget *_t = static_cast<QHarmParaWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_OutPutStateChanged(); break;
        case 1: _t->sig_InPutStateChanged(); break;
        case 2: _t->sig_AutoStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_cmb_ChanelIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_cmb_HarmOrderIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_lne_StartChanged(); break;
        case 6: _t->slot_lne_EndChanged(); break;
        case 7: _t->slot_lne_StepChanged(); break;
        case 8: _t->slot_lne_StepTimeChanged(); break;
        case 9: _t->slot_lne_StartClicked(); break;
        case 10: _t->slot_lne_EndClicked(); break;
        case 11: _t->slot_lne_StepClicked(); break;
        case 12: _t->slot_lne_StepTimeClicked(); break;
        case 13: _t->slot_ck_AutoStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slot_ck_In1StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_ck_In2StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slot_ck_In3StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->slot_ck_In4StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->slot_ck_In5StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slot_ck_In6StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->slot_ck_In7StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->slot_ck_In8StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slot_ck_In9StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->slot_ck_In10StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->slot_ck_Out1StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->slot_ck_Out2StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->slot_ck_Out3StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_ck_Out4StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->slot_ck_Out5StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->slot_ck_Out6StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->slot_ck_Out7StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->slot_ck_Out8StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->slot_ck_Out9StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->slot_ck_Out10StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->slot_radio_AndStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->slot_radio_OrStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->slot_radio_HarmGradTypeStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHarmParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHarmParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QHarmParaWidget,
      qt_meta_data_QHarmParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHarmParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHarmParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHarmParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHarmParaWidget))
        return static_cast<void*>(const_cast< QHarmParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QHarmParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void QHarmParaWidget::sig_OutPutStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QHarmParaWidget::sig_InPutStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QHarmParaWidget::sig_AutoStateChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
