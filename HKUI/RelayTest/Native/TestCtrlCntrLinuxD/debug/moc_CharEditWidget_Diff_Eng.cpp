/****************************************************************************
** Meta object code from reading C++ file 'CharEditWidget_Diff_Eng.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/InternationalModeUI/CharEditWidget_Diff_Eng.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharEditWidget_Diff_Eng.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditGrid_DiffLine_Eng[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,
      61,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,   83,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditGrid_DiffLine_Eng[] = {
    "QCharEditGrid_DiffLine_Eng\0\0"
    "sig_TestPointsErrorBandChanged()\0"
    "sig_DiffCharChanged()\0nRow,nCol\0"
    "slot_doubleClicked(int,int)\0"
};

void QCharEditGrid_DiffLine_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditGrid_DiffLine_Eng *_t = static_cast<QCharEditGrid_DiffLine_Eng *>(_o);
        switch (_id) {
        case 0: _t->sig_TestPointsErrorBandChanged(); break;
        case 1: _t->sig_DiffCharChanged(); break;
        case 2: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditGrid_DiffLine_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditGrid_DiffLine_Eng::staticMetaObject = {
    { &QCharEditGridBase::staticMetaObject, qt_meta_stringdata_QCharEditGrid_DiffLine_Eng,
      qt_meta_data_QCharEditGrid_DiffLine_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditGrid_DiffLine_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditGrid_DiffLine_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditGrid_DiffLine_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditGrid_DiffLine_Eng))
        return static_cast<void*>(const_cast< QCharEditGrid_DiffLine_Eng*>(this));
    return QCharEditGridBase::qt_metacast(_clname);
}

int QCharEditGrid_DiffLine_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCharEditGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QCharEditGrid_DiffLine_Eng::sig_TestPointsErrorBandChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QCharEditGrid_DiffLine_Eng::sig_DiffCharChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_QCharEditGrid_Param_Diff[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   26,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditGrid_Param_Diff[] = {
    "QCharEditGrid_Param_Diff\0\0nRow,nCol\0"
    "slot_doubleClicked(int,int)\0"
};

void QCharEditGrid_Param_Diff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditGrid_Param_Diff *_t = static_cast<QCharEditGrid_Param_Diff *>(_o);
        switch (_id) {
        case 0: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditGrid_Param_Diff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditGrid_Param_Diff::staticMetaObject = {
    { &QCharEditGridBase::staticMetaObject, qt_meta_stringdata_QCharEditGrid_Param_Diff,
      qt_meta_data_QCharEditGrid_Param_Diff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditGrid_Param_Diff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditGrid_Param_Diff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditGrid_Param_Diff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditGrid_Param_Diff))
        return static_cast<void*>(const_cast< QCharEditGrid_Param_Diff*>(this));
    return QCharEditGridBase::qt_metacast(_clname);
}

int QCharEditGrid_Param_Diff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCharEditGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_QCharEditGrid_Section_Diff[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   28,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditGrid_Section_Diff[] = {
    "QCharEditGrid_Section_Diff\0\0nRow,nCol\0"
    "slot_doubleClicked(int,int)\0"
};

void QCharEditGrid_Section_Diff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditGrid_Section_Diff *_t = static_cast<QCharEditGrid_Section_Diff *>(_o);
        switch (_id) {
        case 0: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditGrid_Section_Diff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditGrid_Section_Diff::staticMetaObject = {
    { &QCharEditGridBase::staticMetaObject, qt_meta_stringdata_QCharEditGrid_Section_Diff,
      qt_meta_data_QCharEditGrid_Section_Diff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditGrid_Section_Diff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditGrid_Section_Diff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditGrid_Section_Diff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditGrid_Section_Diff))
        return static_cast<void*>(const_cast< QCharEditGrid_Section_Diff*>(this));
    return QCharEditGridBase::qt_metacast(_clname);
}

int QCharEditGrid_Section_Diff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCharEditGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_QCharEditWidget_Diff_Eng[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   26,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   25,   25,   25, 0x08,
      88,   25,   25,   25, 0x08,
     112,   25,   25,   25, 0x08,
     136,   25,   25,   25, 0x08,
     160,   25,   25,   25, 0x08,
     185,   25,   25,   25, 0x08,
     222,   25,   25,   25, 0x08,
     259,   25,   25,   25, 0x08,
     293,   25,   25,   25, 0x08,
     326,   25,   25,   25, 0x08,
     360,   25,   25,   25, 0x08,
     393,   25,   25,   25, 0x08,
     427,   25,   25,   25, 0x08,
     460,   25,   25,   25, 0x08,
     494,   25,   25,   25, 0x08,
     528,  520,   25,   25, 0x08,
     574,   25,   25,   25, 0x08,
     608,   25,   25,   25, 0x08,
     631,   25,   25,   25, 0x08,
     658,   25,   25,   25, 0x08,
     690,  683,   25,   25, 0x08,
     730,  683,   25,   25, 0x08,
     760,  683,   25,   25, 0x08,
     790,   25,   25,   25, 0x08,
     819,   25,   25,   25, 0x08,
     851,   25,   25,   25, 0x08,
     894,  886,   25,   25, 0x08,
     925,  683,   25,   25, 0x08,
     966,  683,   25,   25, 0x08,
     997,   25,   25,   25, 0x08,
    1027,   25,   25,   25, 0x08,
    1062,   25,   25,   25, 0x08,
    1098,   25,   25,   25, 0x08,
    1149,   25,   25,   25, 0x08,
    1192,  683,   25,   25, 0x08,
    1233,  683,   25,   25, 0x08,
    1275,  683,   25,   25, 0x08,
    1317,  683,   25,   25, 0x08,
    1360,   25,   25,   25, 0x08,
    1408, 1395,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_Diff_Eng[] = {
    "QCharEditWidget_Diff_Eng\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "on_m_chkStart_clicked()\0on_m_chkLine1_clicked()\0"
    "on_m_chkLine2_clicked()\0on_m_chkLine3_clicked()\0"
    "on_m_chkLineSd_clicked()\0"
    "on_m_edtSet_Istart_editingFinished()\0"
    "on_m_edtSet_Kstart_editingFinished()\0"
    "on_m_edtSet_Ip1_editingFinished()\0"
    "on_m_edtSet_K1_editingFinished()\0"
    "on_m_edtSet_Ip2_editingFinished()\0"
    "on_m_edtSet_K2_editingFinished()\0"
    "on_m_edtSet_Ip3_editingFinished()\0"
    "on_m_edtSet_K3_editingFinished()\0"
    "on_m_edtSet_Isd_editingFinished()\0"
    "on_m_onlineEdit_Changed()\0strText\0"
    "slot_m_cbTypeSel_currentIndexChanged(QString)\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_radioNormal_Clicked()\0"
    "slot_radioHarm_Clicked()\0nIndex\0"
    "slot_CmbSettingMinAxisIndexChanged(int)\0"
    "slot_CmbInSeIndexChanged(int)\0"
    "slot_CmbHarmIndexChanged(int)\0"
    "slot_InSet_editingFinished()\0"
    "slot_HarmCoef_editingFinished()\0"
    "slot_Currm_DiffTypeTabChanged(int)\0"
    "checked\0slot_m_radioUser_toggled(bool)\0"
    "slot_CmbSettingMinAxis2IndexChanged(int)\0"
    "slot_CmbInSe2IndexChanged(int)\0"
    "slot_InSet2_editingFinished()\0"
    "slot_m_editIDoor_editingFinished()\0"
    "slot_m_editIQuick_editingFinished()\0"
    "slot_ShowGridDatas_EmitCharChanged(CExBaseObject*)\0"
    "on_m_editCustomHarmIndex_editingFinished()\0"
    "slot_CmbCombinedFeatureIndexChanged(int)\0"
    "slot_CmbCombinedFeature2IndexChanged(int)\0"
    "slot_CmbZeroSeqElimiTypeIndexChanged(int)\0"
    "slot_CmbZeroSeqElimiType2IndexChanged(int)\0"
    "slot_UpdateCharByCombinedFeature()\0"
    "bIsCharRaise\0CalByCombinedFeature(BOOL)\0"
};

void QCharEditWidget_Diff_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_Diff_Eng *_t = static_cast<QCharEditWidget_Diff_Eng *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_m_chkStart_clicked(); break;
        case 2: _t->on_m_chkLine1_clicked(); break;
        case 3: _t->on_m_chkLine2_clicked(); break;
        case 4: _t->on_m_chkLine3_clicked(); break;
        case 5: _t->on_m_chkLineSd_clicked(); break;
        case 6: _t->on_m_edtSet_Istart_editingFinished(); break;
        case 7: _t->on_m_edtSet_Kstart_editingFinished(); break;
        case 8: _t->on_m_edtSet_Ip1_editingFinished(); break;
        case 9: _t->on_m_edtSet_K1_editingFinished(); break;
        case 10: _t->on_m_edtSet_Ip2_editingFinished(); break;
        case 11: _t->on_m_edtSet_K2_editingFinished(); break;
        case 12: _t->on_m_edtSet_Ip3_editingFinished(); break;
        case 13: _t->on_m_edtSet_K3_editingFinished(); break;
        case 14: _t->on_m_edtSet_Isd_editingFinished(); break;
        case 15: _t->on_m_onlineEdit_Changed(); break;
        case 16: _t->slot_m_cbTypeSel_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->slot_TestPointsErrorBandChanged(); break;
        case 18: _t->slot_DiffCharChanged(); break;
        case 19: _t->slot_radioNormal_Clicked(); break;
        case 20: _t->slot_radioHarm_Clicked(); break;
        case 21: _t->slot_CmbSettingMinAxisIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slot_CmbInSeIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->slot_CmbHarmIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->slot_InSet_editingFinished(); break;
        case 25: _t->slot_HarmCoef_editingFinished(); break;
        case 26: _t->slot_Currm_DiffTypeTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_m_radioUser_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->slot_CmbSettingMinAxis2IndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->slot_CmbInSe2IndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->slot_InSet2_editingFinished(); break;
        case 31: _t->slot_m_editIDoor_editingFinished(); break;
        case 32: _t->slot_m_editIQuick_editingFinished(); break;
        case 33: _t->slot_ShowGridDatas_EmitCharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1]))); break;
        case 34: _t->on_m_editCustomHarmIndex_editingFinished(); break;
        case 35: _t->slot_CmbCombinedFeatureIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->slot_CmbCombinedFeature2IndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->slot_CmbZeroSeqElimiTypeIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->slot_CmbZeroSeqElimiType2IndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->slot_UpdateCharByCombinedFeature(); break;
        case 40: _t->CalByCombinedFeature((*reinterpret_cast< BOOL(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_Diff_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_Diff_Eng::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_Diff_Eng,
      qt_meta_data_QCharEditWidget_Diff_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_Diff_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_Diff_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_Diff_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_Diff_Eng))
        return static_cast<void*>(const_cast< QCharEditWidget_Diff_Eng*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_Diff_Eng*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditWidget_Diff_Eng*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_Diff_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void QCharEditWidget_Diff_Eng::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
