/****************************************************************************
** Meta object code from reading C++ file 'DiffAddBatchDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Diff/DiffAddBatchDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiffAddBatchDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDiffCharGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QDiffCharGrid[] = {
    "QDiffCharGrid\0"
};

void QDiffCharGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QDiffCharGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffCharGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_QDiffCharGrid,
      qt_meta_data_QDiffCharGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffCharGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffCharGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffCharGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffCharGrid))
        return static_cast<void*>(const_cast< QDiffCharGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int QDiffCharGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QDiffAddBatchDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      41,   17,   17,   17, 0x08,
      65,   17,   17,   17, 0x08,
      99,   17,   17,   17, 0x08,
     133,   17,   17,   17, 0x08,
     180,  172,   17,   17, 0x08,
     210,  172,   17,   17, 0x08,
     240,  172,   17,   17, 0x08,
     270,  172,   17,   17, 0x08,
     298,  172,   17,   17, 0x08,
     326,  172,   17,   17, 0x08,
     354,  172,   17,   17, 0x08,
     382,  172,   17,   17, 0x08,
     410,  172,   17,   17, 0x08,
     438,  172,   17,   17, 0x08,
     476,  467,   17,   17, 0x08,
     495,   17,   17,   17, 0x08,
     530,  524,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDiffAddBatchDlg[] = {
    "QDiffAddBatchDlg\0\0on_m_btnSave_clicked()\0"
    "on_m_btnClose_clicked()\0"
    "on_m_txtTime_lr_editingFinished()\0"
    "on_m_txtTime_ld_editingFinished()\0"
    "on_m_txtMaxFaultTime_editingFinished()\0"
    "checked\0on_m_check_Rate_clicked(bool)\0"
    "on_m_check_Harm_clicked(bool)\0"
    "on_m_check_Time_clicked(bool)\0"
    "on_m_check_AN_clicked(bool)\0"
    "on_m_check_BN_clicked(bool)\0"
    "on_m_check_CN_clicked(bool)\0"
    "on_m_check_AB_clicked(bool)\0"
    "on_m_check_BC_clicked(bool)\0"
    "on_m_check_CA_clicked(bool)\0"
    "on_m_check_ABC_clicked(bool)\0nMinaxis\0"
    "UpdateMinaxis(int)\0on_m_btnResEvaluat_clicked()\0"
    "index\0on_tabWidget_currentChanged(int)\0"
};

void QDiffAddBatchDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDiffAddBatchDlg *_t = static_cast<QDiffAddBatchDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnSave_clicked(); break;
        case 1: _t->on_m_btnClose_clicked(); break;
        case 2: _t->on_m_txtTime_lr_editingFinished(); break;
        case 3: _t->on_m_txtTime_ld_editingFinished(); break;
        case 4: _t->on_m_txtMaxFaultTime_editingFinished(); break;
        case 5: _t->on_m_check_Rate_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_m_check_Harm_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_m_check_Time_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_m_check_AN_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_m_check_BN_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_m_check_CN_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_m_check_AB_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_m_check_BC_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_m_check_CA_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_m_check_ABC_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->UpdateMinaxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_m_btnResEvaluat_clicked(); break;
        case 17: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDiffAddBatchDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffAddBatchDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDiffAddBatchDlg,
      qt_meta_data_QDiffAddBatchDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffAddBatchDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffAddBatchDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffAddBatchDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffAddBatchDlg))
        return static_cast<void*>(const_cast< QDiffAddBatchDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDiffAddBatchDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
