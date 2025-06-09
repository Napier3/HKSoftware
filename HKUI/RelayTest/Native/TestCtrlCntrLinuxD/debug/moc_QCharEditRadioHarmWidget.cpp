/****************************************************************************
** Meta object code from reading C++ file 'QCharEditRadioHarmWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/QCharEditRadioHarmWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCharEditRadioHarmWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditRadioHarmWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   26,   25,   25, 0x05,
      64,   25,   25,   25, 0x05,
      88,   25,   25,   25, 0x05,
     115,   25,   25,   25, 0x05,
     152,   25,   25,   25, 0x05,
     181,   25,   25,   25, 0x05,
     216,   25,   25,   25, 0x05,
     239,   25,   25,   25, 0x05,
     266,  263,   25,   25, 0x05,
     297,   25,   25,   25, 0x05,
     321,   25,   25,   25, 0x05,
     342,   25,   25,   25, 0x05,
     375,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     408,   25,   25,   25, 0x08,
     445,   25,   25,   25, 0x08,
     479,   25,   25,   25, 0x08,
     505,   25,   25,   25, 0x08,
     539,   25,   25,   25, 0x08,
     562,   25,   25,   25, 0x08,
     600,  593,   25,   25, 0x08,
     622,  593,   25,   25, 0x08,
     653,  646,   25,   25, 0x08,
     693,  646,   25,   25, 0x08,
     729,  723,   25,   25, 0x08,
     764,   25,   25,   25, 0x08,
     793,   25,   25,   25, 0x08,
     825,  723,   25,   25, 0x08,
     857,  723,   25,   25, 0x08,
     900,  894,   25,   25, 0x08,
     936,  930,   25,   25, 0x08,
     974,  967,   25,   25, 0x08,
    1009, 1005,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditRadioHarmWidget[] = {
    "QCharEditRadioHarmWidget\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "sig_ChangeICMAxisName()\0"
    "sig_MainWidgetCharChange()\0"
    "sig_IdValue_editingFinished(CString)\0"
    "sig_ChangeTranSortIndex(int)\0"
    "sig_ChangeSettingMinAxisIndex(int)\0"
    "sig_ChangeInset(float)\0sig_ChangeCTPoint(bool)\0"
    ",,\0sig_UpdateChar(bool,bool,bool)\0"
    "sig_ChangeIstart(float)\0sig_ChangeIsd(float)\0"
    "sig_TestPointsErrorBandChanged()\0"
    "sig_ActiveSegment(CCharElement*)\0"
    "on_m_edtSet_Istart_editingFinished()\0"
    "on_m_edtSet_Isd_editingFinished()\0"
    "on_m_onlineEdit_Changed()\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_IdValue_editingFinished()\0bState\0"
    "slot_btnUserAdd(bool)\0slot_btnUserClear(bool)\0"
    "nIndex\0slot_CmbSettingMinAxisIndexChanged(int)\0"
    "slot_CmbHarmIndexChanged(int)\0index\0"
    "slot_cmb_TranSortIndexChanged(int)\0"
    "slot_InSet_editingFinished()\0"
    "slot_HarmCoef_editingFinished()\0"
    "slot_normalChangeTransSort(int)\0"
    "slot_normalChangeSettingMinAxis(int)\0"
    "InSet\0slot_normalChangeInSet(float)\0"
    "bAmbo\0slot_normalChangeCTPoint(bool)\0"
    "Istart\0slot_normalChangeIstart(float)\0"
    "Isd\0slot_normalChangeIsd(float)\0"
};

void QCharEditRadioHarmWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditRadioHarmWidget *_t = static_cast<QCharEditRadioHarmWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_ChangeICMAxisName(); break;
        case 2: _t->sig_MainWidgetCharChange(); break;
        case 3: _t->sig_IdValue_editingFinished((*reinterpret_cast< CString(*)>(_a[1]))); break;
        case 4: _t->sig_ChangeTranSortIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_ChangeSettingMinAxisIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sig_ChangeInset((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->sig_ChangeCTPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sig_UpdateChar((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 9: _t->sig_ChangeIstart((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->sig_ChangeIsd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->sig_TestPointsErrorBandChanged(); break;
        case 12: _t->sig_ActiveSegment((*reinterpret_cast< CCharElement*(*)>(_a[1]))); break;
        case 13: _t->on_m_edtSet_Istart_editingFinished(); break;
        case 14: _t->on_m_edtSet_Isd_editingFinished(); break;
        case 15: _t->on_m_onlineEdit_Changed(); break;
        case 16: _t->slot_TestPointsErrorBandChanged(); break;
        case 17: _t->slot_DiffCharChanged(); break;
        case 18: _t->slot_IdValue_editingFinished(); break;
        case 19: _t->slot_btnUserAdd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->slot_btnUserClear((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->slot_CmbSettingMinAxisIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slot_CmbHarmIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->slot_cmb_TranSortIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->slot_InSet_editingFinished(); break;
        case 25: _t->slot_HarmCoef_editingFinished(); break;
        case 26: _t->slot_normalChangeTransSort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_normalChangeSettingMinAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->slot_normalChangeInSet((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 29: _t->slot_normalChangeCTPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->slot_normalChangeIstart((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 31: _t->slot_normalChangeIsd((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditRadioHarmWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditRadioHarmWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditRadioHarmWidget,
      qt_meta_data_QCharEditRadioHarmWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditRadioHarmWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditRadioHarmWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditRadioHarmWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditRadioHarmWidget))
        return static_cast<void*>(const_cast< QCharEditRadioHarmWidget*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditRadioHarmWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditRadioHarmWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void QCharEditRadioHarmWidget::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCharEditRadioHarmWidget::sig_ChangeICMAxisName()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QCharEditRadioHarmWidget::sig_MainWidgetCharChange()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QCharEditRadioHarmWidget::sig_IdValue_editingFinished(CString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCharEditRadioHarmWidget::sig_ChangeTranSortIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCharEditRadioHarmWidget::sig_ChangeSettingMinAxisIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QCharEditRadioHarmWidget::sig_ChangeInset(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QCharEditRadioHarmWidget::sig_ChangeCTPoint(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QCharEditRadioHarmWidget::sig_UpdateChar(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QCharEditRadioHarmWidget::sig_ChangeIstart(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QCharEditRadioHarmWidget::sig_ChangeIsd(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QCharEditRadioHarmWidget::sig_TestPointsErrorBandChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void QCharEditRadioHarmWidget::sig_ActiveSegment(CCharElement * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
