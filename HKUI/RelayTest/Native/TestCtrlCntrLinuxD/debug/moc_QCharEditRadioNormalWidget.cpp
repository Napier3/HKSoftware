/****************************************************************************
** Meta object code from reading C++ file 'QCharEditRadioNormalWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/QCharEditRadioNormalWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCharEditRadioNormalWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditRadioNormalWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   28,   27,   27, 0x05,
      66,   27,   27,   27, 0x05,
     101,   27,   27,   27, 0x05,
     125,   27,   27,   27, 0x05,
     152,   27,   27,   27, 0x05,
     189,   27,   27,   27, 0x05,
     218,   27,   27,   27, 0x05,
     241,   27,   27,   27, 0x05,
     268,  265,   27,   27, 0x05,
     299,   27,   27,   27, 0x05,
     323,   27,   27,   27, 0x05,
     344,   27,   27,   27, 0x05,
     377,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
     410,   27,   27,   27, 0x08,
     434,   27,   27,   27, 0x08,
     458,   27,   27,   27, 0x08,
     482,   27,   27,   27, 0x08,
     507,   27,   27,   27, 0x08,
     544,   27,   27,   27, 0x08,
     581,   27,   27,   27, 0x08,
     615,   27,   27,   27, 0x08,
     648,   27,   27,   27, 0x08,
     682,   27,   27,   27, 0x08,
     715,   27,   27,   27, 0x08,
     749,   27,   27,   27, 0x08,
     782,  775,   27,   27, 0x08,
     804,  775,   27,   27, 0x08,
     828,   27,   27,   27, 0x08,
     857,   27,   27,   27, 0x08,
     894,  888,   27,   27, 0x08,
     936,  929,   27,   27, 0x08,
     976,   27,   27,   27, 0x08,
    1010,   27,   27,   27, 0x08,
    1033,  888,   27,   27, 0x08,
    1063,  888,   27,   27, 0x08,
    1104, 1098,   27,   27, 0x08,
    1138, 1132,   27,   27, 0x08,
    1174, 1167,   27,   27, 0x08,
    1207, 1203,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditRadioNormalWidget[] = {
    "QCharEditRadioNormalWidget\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "sig_ChangeSettingMinAxisIndex(int)\0"
    "sig_ChangeICMAxisName()\0"
    "sig_MainWidgetCharChange()\0"
    "sig_IdValue_editingFinished(CString)\0"
    "sig_ChangeTranSortIndex(int)\0"
    "sig_ChangeInset(float)\0sig_ChangeCTPoint(bool)\0"
    ",,\0sig_UpdateChar(bool,bool,bool)\0"
    "sig_ChangeIstart(float)\0sig_ChangeIsd(float)\0"
    "sig_TestPointsErrorBandChanged()\0"
    "sig_ActiveSegment(CCharElement*)\0"
    "on_m_chkStart_clicked()\0on_m_chkLine1_clicked()\0"
    "on_m_chkLine2_clicked()\0"
    "on_m_chkLineSd_clicked()\0"
    "on_m_edtSet_Istart_editingFinished()\0"
    "on_m_edtSet_Kstart_editingFinished()\0"
    "on_m_edtSet_Ip1_editingFinished()\0"
    "on_m_edtSet_K1_editingFinished()\0"
    "on_m_edtSet_Ip2_editingFinished()\0"
    "on_m_edtSet_K2_editingFinished()\0"
    "on_m_edtSet_Isd_editingFinished()\0"
    "on_m_onlineEdit_Changed()\0bState\0"
    "slot_btnUserAdd(bool)\0slot_btnUserClear(bool)\0"
    "slot_InSet_editingFinished()\0"
    "slot_IdValue_editingFinished()\0index\0"
    "slot_cmb_TranSortIndexChanged(int)\0"
    "nIndex\0slot_CmbSettingMinAxisIndexChanged(int)\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_HarmChangeTransSort(int)\0"
    "slot_HarmChangeSettingMinAxis(int)\0"
    "InSet\0slot_HarmChangeInSet(float)\0"
    "bAmbo\0slot_HarmChangeCTPoint(bool)\0"
    "Istart\0slot_HarmChangeIstart(float)\0"
    "Isd\0slot_HarmChangeIsd(float)\0"
};

void QCharEditRadioNormalWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditRadioNormalWidget *_t = static_cast<QCharEditRadioNormalWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_ChangeSettingMinAxisIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_ChangeICMAxisName(); break;
        case 3: _t->sig_MainWidgetCharChange(); break;
        case 4: _t->sig_IdValue_editingFinished((*reinterpret_cast< CString(*)>(_a[1]))); break;
        case 5: _t->sig_ChangeTranSortIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sig_ChangeInset((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->sig_ChangeCTPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sig_UpdateChar((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 9: _t->sig_ChangeIstart((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->sig_ChangeIsd((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->sig_TestPointsErrorBandChanged(); break;
        case 12: _t->sig_ActiveSegment((*reinterpret_cast< CCharElement*(*)>(_a[1]))); break;
        case 13: _t->on_m_chkStart_clicked(); break;
        case 14: _t->on_m_chkLine1_clicked(); break;
        case 15: _t->on_m_chkLine2_clicked(); break;
        case 16: _t->on_m_chkLineSd_clicked(); break;
        case 17: _t->on_m_edtSet_Istart_editingFinished(); break;
        case 18: _t->on_m_edtSet_Kstart_editingFinished(); break;
        case 19: _t->on_m_edtSet_Ip1_editingFinished(); break;
        case 20: _t->on_m_edtSet_K1_editingFinished(); break;
        case 21: _t->on_m_edtSet_Ip2_editingFinished(); break;
        case 22: _t->on_m_edtSet_K2_editingFinished(); break;
        case 23: _t->on_m_edtSet_Isd_editingFinished(); break;
        case 24: _t->on_m_onlineEdit_Changed(); break;
        case 25: _t->slot_btnUserAdd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->slot_btnUserClear((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->slot_InSet_editingFinished(); break;
        case 28: _t->slot_IdValue_editingFinished(); break;
        case 29: _t->slot_cmb_TranSortIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->slot_CmbSettingMinAxisIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->slot_TestPointsErrorBandChanged(); break;
        case 32: _t->slot_DiffCharChanged(); break;
        case 33: _t->slot_HarmChangeTransSort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->slot_HarmChangeSettingMinAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->slot_HarmChangeInSet((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 36: _t->slot_HarmChangeCTPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->slot_HarmChangeIstart((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 38: _t->slot_HarmChangeIsd((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditRadioNormalWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditRadioNormalWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditRadioNormalWidget,
      qt_meta_data_QCharEditRadioNormalWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditRadioNormalWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditRadioNormalWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditRadioNormalWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditRadioNormalWidget))
        return static_cast<void*>(const_cast< QCharEditRadioNormalWidget*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditRadioNormalWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditRadioNormalWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void QCharEditRadioNormalWidget::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCharEditRadioNormalWidget::sig_ChangeSettingMinAxisIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCharEditRadioNormalWidget::sig_ChangeICMAxisName()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QCharEditRadioNormalWidget::sig_MainWidgetCharChange()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QCharEditRadioNormalWidget::sig_IdValue_editingFinished(CString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCharEditRadioNormalWidget::sig_ChangeTranSortIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QCharEditRadioNormalWidget::sig_ChangeInset(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QCharEditRadioNormalWidget::sig_ChangeCTPoint(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QCharEditRadioNormalWidget::sig_UpdateChar(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QCharEditRadioNormalWidget::sig_ChangeIstart(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QCharEditRadioNormalWidget::sig_ChangeIsd(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QCharEditRadioNormalWidget::sig_TestPointsErrorBandChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void QCharEditRadioNormalWidget::sig_ActiveSegment(CCharElement * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
