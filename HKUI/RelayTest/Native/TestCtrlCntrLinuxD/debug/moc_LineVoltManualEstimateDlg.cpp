/****************************************************************************
** Meta object code from reading C++ file 'LineVoltManualEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/LineVoltManu/LineVoltManualEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LineVoltManualEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LineVoltEstimateGrid[] = {

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

static const char qt_meta_stringdata_LineVoltEstimateGrid[] = {
    "LineVoltEstimateGrid\0\0row,col\0"
    "slot_OnCellChanged(int,int)\0strText\0"
    "slot_cmbErrorChanged(QString)\0"
};

void LineVoltEstimateGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineVoltEstimateGrid *_t = static_cast<LineVoltEstimateGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_cmbErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LineVoltEstimateGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineVoltEstimateGrid::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_LineVoltEstimateGrid,
      qt_meta_data_LineVoltEstimateGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineVoltEstimateGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineVoltEstimateGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineVoltEstimateGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineVoltEstimateGrid))
        return static_cast<void*>(const_cast< LineVoltEstimateGrid*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int LineVoltEstimateGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_LineVoltManualEstimateDlg[] = {

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

static const char qt_meta_stringdata_LineVoltManualEstimateDlg[] = {
    "LineVoltManualEstimateDlg\0\0"
    "slot_btnOK_Clicked()\0slot_btnCancel_Clicked()\0"
};

void LineVoltManualEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineVoltManualEstimateDlg *_t = static_cast<LineVoltManualEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked(); break;
        case 1: _t->slot_btnCancel_Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LineVoltManualEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineVoltManualEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LineVoltManualEstimateDlg,
      qt_meta_data_LineVoltManualEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineVoltManualEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineVoltManualEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineVoltManualEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineVoltManualEstimateDlg))
        return static_cast<void*>(const_cast< LineVoltManualEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int LineVoltManualEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
