/****************************************************************************
** Meta object code from reading C++ file 'LineVolGradientEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/LineVolGradient/LineVolGradientEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LineVolGradientEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LineVolGradientEstimateGrid[] = {

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
      37,   29,   28,   28, 0x09,
      73,   65,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LineVolGradientEstimateGrid[] = {
    "LineVolGradientEstimateGrid\0\0row,col\0"
    "slot_OnCellChanged(int,int)\0strText\0"
    "slot_cmbErrorChanged(QString)\0"
};

void LineVolGradientEstimateGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineVolGradientEstimateGrid *_t = static_cast<LineVolGradientEstimateGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_cmbErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LineVolGradientEstimateGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineVolGradientEstimateGrid::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_LineVolGradientEstimateGrid,
      qt_meta_data_LineVolGradientEstimateGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineVolGradientEstimateGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineVolGradientEstimateGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineVolGradientEstimateGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineVolGradientEstimateGrid))
        return static_cast<void*>(const_cast< LineVolGradientEstimateGrid*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int LineVolGradientEstimateGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_LineVolGradientEstimateDlg[] = {

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
      28,   27,   27,   27, 0x09,
      49,   27,   27,   27, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LineVolGradientEstimateDlg[] = {
    "LineVolGradientEstimateDlg\0\0"
    "slot_btnOK_Clicked()\0slot_btnCancel_Clicked()\0"
};

void LineVolGradientEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineVolGradientEstimateDlg *_t = static_cast<LineVolGradientEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked(); break;
        case 1: _t->slot_btnCancel_Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LineVolGradientEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineVolGradientEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LineVolGradientEstimateDlg,
      qt_meta_data_LineVolGradientEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineVolGradientEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineVolGradientEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineVolGradientEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineVolGradientEstimateDlg))
        return static_cast<void*>(const_cast< LineVolGradientEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int LineVolGradientEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
