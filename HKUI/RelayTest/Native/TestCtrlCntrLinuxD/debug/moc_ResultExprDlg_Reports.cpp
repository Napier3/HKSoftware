/****************************************************************************
** Meta object code from reading C++ file 'ResultExprDlg_Reports.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ResultExpr/ResultExprDlg_Reports.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultExprDlg_Reports.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QResultExprDlg_Reports[] = {

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
      31,   24,   23,   23, 0x08,
      56,   24,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QResultExprDlg_Reports[] = {
    "QResultExprDlg_Reports\0\0bCheck\0"
    "slot_btnOK_Clicked(bool)\0"
    "slot_btnCancel_Clicked(bool)\0"
};

void QResultExprDlg_Reports::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QResultExprDlg_Reports *_t = static_cast<QResultExprDlg_Reports *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_btnCancel_Clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QResultExprDlg_Reports::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QResultExprDlg_Reports::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QResultExprDlg_Reports,
      qt_meta_data_QResultExprDlg_Reports, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QResultExprDlg_Reports::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QResultExprDlg_Reports::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QResultExprDlg_Reports::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QResultExprDlg_Reports))
        return static_cast<void*>(const_cast< QResultExprDlg_Reports*>(this));
    return QDialog::qt_metacast(_clname);
}

int QResultExprDlg_Reports::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
