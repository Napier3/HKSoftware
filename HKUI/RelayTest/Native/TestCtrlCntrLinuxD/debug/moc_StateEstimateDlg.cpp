/****************************************************************************
** Meta object code from reading C++ file 'StateEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/StateEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateEstimateGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x08,
      57,   19,   18,   18, 0x08,
      95,   87,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StateEstimateGrid[] = {
    "StateEstimateGrid\0\0strText\0"
    "slot_StateBinChanged(QString)\0"
    "slot_cmbErrorChanged(QString)\0row,col\0"
    "slot_OnCellChanged(int,int)\0"
};

void StateEstimateGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateEstimateGrid *_t = static_cast<StateEstimateGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_StateBinChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->slot_cmbErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StateEstimateGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateEstimateGrid::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_StateEstimateGrid,
      qt_meta_data_StateEstimateGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateEstimateGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateEstimateGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateEstimateGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateEstimateGrid))
        return static_cast<void*>(const_cast< StateEstimateGrid*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int StateEstimateGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_StateEstimateDlg[] = {

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
      18,   17,   17,   17, 0x09,
      39,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StateEstimateDlg[] = {
    "StateEstimateDlg\0\0slot_btnOK_Clicked()\0"
    "slot_btnCancel_Clicked()\0"
};

void StateEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateEstimateDlg *_t = static_cast<StateEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked(); break;
        case 1: _t->slot_btnCancel_Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StateEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StateEstimateDlg,
      qt_meta_data_StateEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateEstimateDlg))
        return static_cast<void*>(const_cast< StateEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int StateEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
