/****************************************************************************
** Meta object code from reading C++ file 'SequenceManualEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/SequenceManu/SequenceManualEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SequenceManualEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SequenceEstimateGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   22,   21,   21, 0x09,
      66,   58,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SequenceEstimateGrid[] = {
    "SequenceEstimateGrid\0\0row,col\0"
    "slot_OnCellChanged(int,int)\0strText\0"
    "slot_cmbErrorChanged(QString)\0"
};

void SequenceEstimateGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SequenceEstimateGrid *_t = static_cast<SequenceEstimateGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_cmbErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SequenceEstimateGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SequenceEstimateGrid::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_SequenceEstimateGrid,
      qt_meta_data_SequenceEstimateGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SequenceEstimateGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SequenceEstimateGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SequenceEstimateGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SequenceEstimateGrid))
        return static_cast<void*>(const_cast< SequenceEstimateGrid*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int SequenceEstimateGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_SequenceManualEstimateDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x09,
      48,   26,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SequenceManualEstimateDlg[] = {
    "SequenceManualEstimateDlg\0\0"
    "slot_btnOK_Clicked()\0slot_btnCancel_Clicked()\0"
};

void SequenceManualEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SequenceManualEstimateDlg *_t = static_cast<SequenceManualEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked(); break;
        case 1: _t->slot_btnCancel_Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SequenceManualEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SequenceManualEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SequenceManualEstimateDlg,
      qt_meta_data_SequenceManualEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SequenceManualEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SequenceManualEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SequenceManualEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SequenceManualEstimateDlg))
        return static_cast<void*>(const_cast< SequenceManualEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SequenceManualEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
