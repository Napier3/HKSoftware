/****************************************************************************
** Meta object code from reading C++ file 'CharEditWidget_Diff.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/CharEditWidget_Diff.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharEditWidget_Diff.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditGrid_DiffLine[] = {

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
      24,   23,   23,   23, 0x05,
      57,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   79,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditGrid_DiffLine[] = {
    "QCharEditGrid_DiffLine\0\0"
    "sig_TestPointsErrorBandChanged()\0"
    "sig_DiffCharChanged()\0nRow,nCol\0"
    "slot_doubleClicked(int,int)\0"
};

void QCharEditGrid_DiffLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditGrid_DiffLine *_t = static_cast<QCharEditGrid_DiffLine *>(_o);
        switch (_id) {
        case 0: _t->sig_TestPointsErrorBandChanged(); break;
        case 1: _t->sig_DiffCharChanged(); break;
        case 2: _t->slot_doubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditGrid_DiffLine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditGrid_DiffLine::staticMetaObject = {
    { &QCharEditGridBase::staticMetaObject, qt_meta_stringdata_QCharEditGrid_DiffLine,
      qt_meta_data_QCharEditGrid_DiffLine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditGrid_DiffLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditGrid_DiffLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditGrid_DiffLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditGrid_DiffLine))
        return static_cast<void*>(const_cast< QCharEditGrid_DiffLine*>(this));
    return QCharEditGridBase::qt_metacast(_clname);
}

int QCharEditGrid_DiffLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QCharEditGrid_DiffLine::sig_TestPointsErrorBandChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QCharEditGrid_DiffLine::sig_DiffCharChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_QCharEditWidget_LineDiff[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
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
     125,   25,   25,   25, 0x08,
     162,   25,   25,   25, 0x08,
     196,   25,   25,   25, 0x08,
     229,   25,   25,   25, 0x08,
     263,   25,   25,   25, 0x08,
     296,   25,   25,   25, 0x08,
     322,   25,   25,   25, 0x08,
     356,   25,   25,   25, 0x08,
     379,   25,   25,   25, 0x08,
     410,   25,   25,   25, 0x08,
     445,  438,   25,   25, 0x08,
     467,  438,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_LineDiff[] = {
    "QCharEditWidget_LineDiff\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "on_m_chkLine2_clicked()\0"
    "on_m_edtSet_Istart_editingFinished()\0"
    "on_m_edtSet_Kstart_editingFinished()\0"
    "on_m_edtSet_Ip1_editingFinished()\0"
    "on_m_edtSet_K1_editingFinished()\0"
    "on_m_edtSet_Ip2_editingFinished()\0"
    "on_m_edtSet_K2_editingFinished()\0"
    "on_m_onlineEdit_Changed()\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_IdValue_editingFinished()\0"
    "slot_MaxIdEditingFinished()\0bState\0"
    "slot_btnUserAdd(bool)\0slot_btnUserClear(bool)\0"
};

void QCharEditWidget_LineDiff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_LineDiff *_t = static_cast<QCharEditWidget_LineDiff *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_m_chkLine2_clicked(); break;
        case 2: _t->on_m_edtSet_Istart_editingFinished(); break;
        case 3: _t->on_m_edtSet_Kstart_editingFinished(); break;
        case 4: _t->on_m_edtSet_Ip1_editingFinished(); break;
        case 5: _t->on_m_edtSet_K1_editingFinished(); break;
        case 6: _t->on_m_edtSet_Ip2_editingFinished(); break;
        case 7: _t->on_m_edtSet_K2_editingFinished(); break;
        case 8: _t->on_m_onlineEdit_Changed(); break;
        case 9: _t->slot_TestPointsErrorBandChanged(); break;
        case 10: _t->slot_DiffCharChanged(); break;
        case 11: _t->slot_IdValue_editingFinished(); break;
        case 12: _t->slot_MaxIdEditingFinished(); break;
        case 13: _t->slot_btnUserAdd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->slot_btnUserClear((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_LineDiff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_LineDiff::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_LineDiff,
      qt_meta_data_QCharEditWidget_LineDiff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_LineDiff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_LineDiff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_LineDiff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_LineDiff))
        return static_cast<void*>(const_cast< QCharEditWidget_LineDiff*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_LineDiff*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditWidget_LineDiff*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_LineDiff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void QCharEditWidget_LineDiff::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QCharEditWidget_Diff[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   21,   21,   21, 0x08,
      84,   21,   21,   21, 0x08,
     108,   21,   21,   21, 0x08,
     132,   21,   21,   21, 0x08,
     156,   21,   21,   21, 0x08,
     181,   21,   21,   21, 0x08,
     218,   21,   21,   21, 0x08,
     255,   21,   21,   21, 0x08,
     289,   21,   21,   21, 0x08,
     322,   21,   21,   21, 0x08,
     356,   21,   21,   21, 0x08,
     389,   21,   21,   21, 0x08,
     423,   21,   21,   21, 0x08,
     456,   21,   21,   21, 0x08,
     490,   21,   21,   21, 0x08,
     516,   21,   21,   21, 0x08,
     550,   21,   21,   21, 0x08,
     573,   21,   21,   21, 0x08,
     611,  604,   21,   21, 0x08,
     633,  604,   21,   21, 0x08,
     657,   21,   21,   21, 0x08,
     684,   21,   21,   21, 0x08,
     716,  709,   21,   21, 0x08,
     756,  709,   21,   21, 0x08,
     786,  709,   21,   21, 0x08,
     816,   21,   21,   21, 0x08,
     845,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_Diff[] = {
    "QCharEditWidget_Diff\0\0,\0"
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
    "on_m_onlineEdit_Changed()\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_IdValue_editingFinished()\0bState\0"
    "slot_btnUserAdd(bool)\0slot_btnUserClear(bool)\0"
    "slot_radioNormal_Clicked()\0"
    "slot_radioHarm_Clicked()\0nIndex\0"
    "slot_CmbSettingMinAxisIndexChanged(int)\0"
    "slot_CmbInSeIndexChanged(int)\0"
    "slot_CmbHarmIndexChanged(int)\0"
    "slot_InSet_editingFinished()\0"
    "slot_HarmCoef_editingFinished()\0"
};

void QCharEditWidget_Diff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_Diff *_t = static_cast<QCharEditWidget_Diff *>(_o);
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
        case 16: _t->slot_TestPointsErrorBandChanged(); break;
        case 17: _t->slot_DiffCharChanged(); break;
        case 18: _t->slot_IdValue_editingFinished(); break;
        case 19: _t->slot_btnUserAdd((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->slot_btnUserClear((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->slot_radioNormal_Clicked(); break;
        case 22: _t->slot_radioHarm_Clicked(); break;
        case 23: _t->slot_CmbSettingMinAxisIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->slot_CmbInSeIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->slot_CmbHarmIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->slot_InSet_editingFinished(); break;
        case 27: _t->slot_HarmCoef_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_Diff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_Diff::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_Diff,
      qt_meta_data_QCharEditWidget_Diff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_Diff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_Diff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_Diff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_Diff))
        return static_cast<void*>(const_cast< QCharEditWidget_Diff*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_Diff*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditWidget_Diff*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_Diff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void QCharEditWidget_Diff::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QCharEditWidget_ElecRailwayDiff[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   33,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   32,   32,   32, 0x08,
     108,   97,   32,   32, 0x08,
     139,   32,   32,   32, 0x08,
     160,   32,   32,   32, 0x08,
     194,   32,   32,   32, 0x08,
     217,   32,   32,   32, 0x08,
     244,   32,   32,   32, 0x08,
     269,   32,   32,   32, 0x08,
     338,  294,   32,   32, 0x08,
     386,  370,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_ElecRailwayDiff[] = {
    "QCharEditWidget_ElecRailwayDiff\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "on_m_onlineEdit_Changed()\0strIdValue\0"
    "IdValue_NormalEditing(CString)\0"
    "ChangeMainWin_Char()\0"
    "slot_TestPointsErrorBandChanged()\0"
    "slot_DiffCharChanged()\0"
    "slot_radioNormal_Clicked()\0"
    "slot_radioHarm_Clicked()\0"
    "slot_ChangeICMAxisName()\0"
    "bUpdateTable,bCharTypeChanged,bParasChanged\0"
    "slot_UpdateChar(bool,bool,bool)\0"
    "pCurrSelElement\0slot_ActiveSegment(CCharElement*)\0"
};

void QCharEditWidget_ElecRailwayDiff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_ElecRailwayDiff *_t = static_cast<QCharEditWidget_ElecRailwayDiff *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_m_onlineEdit_Changed(); break;
        case 2: _t->IdValue_NormalEditing((*reinterpret_cast< CString(*)>(_a[1]))); break;
        case 3: _t->ChangeMainWin_Char(); break;
        case 4: _t->slot_TestPointsErrorBandChanged(); break;
        case 5: _t->slot_DiffCharChanged(); break;
        case 6: _t->slot_radioNormal_Clicked(); break;
        case 7: _t->slot_radioHarm_Clicked(); break;
        case 8: _t->slot_ChangeICMAxisName(); break;
        case 9: _t->slot_UpdateChar((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 10: _t->slot_ActiveSegment((*reinterpret_cast< CCharElement*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_ElecRailwayDiff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_ElecRailwayDiff::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_ElecRailwayDiff,
      qt_meta_data_QCharEditWidget_ElecRailwayDiff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_ElecRailwayDiff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_ElecRailwayDiff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_ElecRailwayDiff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_ElecRailwayDiff))
        return static_cast<void*>(const_cast< QCharEditWidget_ElecRailwayDiff*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_ElecRailwayDiff*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_ElecRailwayDiff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QCharEditWidget_ElecRailwayDiff::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
