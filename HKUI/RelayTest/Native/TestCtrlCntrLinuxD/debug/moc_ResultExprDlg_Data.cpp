/****************************************************************************
** Meta object code from reading C++ file 'ResultExprDlg_Data.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ResultExpr/ResultExprDlg_Data.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultExprDlg_Data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QResultExprDlg_Data[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   21,   20,   20, 0x08,
      53,   21,   20,   20, 0x08,
      82,   21,   20,   20, 0x08,
     106,   20,   20,   20, 0x08,
     144,  137,   20,   20, 0x08,
     188,  169,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QResultExprDlg_Data[] = {
    "QResultExprDlg_Data\0\0bCheck\0"
    "slot_btnOK_Clicked(bool)\0"
    "slot_btnCancel_Clicked(bool)\0"
    "slot_SelectReport(bool)\0"
    "slot_btnChangeReport_Clicked()\0nIndex\0"
    "slot_currentChanged(int)\0pCurItem,pPrevItem\0"
    "slot_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

void QResultExprDlg_Data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QResultExprDlg_Data *_t = static_cast<QResultExprDlg_Data *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_btnCancel_Clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_SelectReport((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_btnChangeReport_Clicked(); break;
        case 4: _t->slot_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QResultExprDlg_Data::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QResultExprDlg_Data::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QResultExprDlg_Data,
      qt_meta_data_QResultExprDlg_Data, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QResultExprDlg_Data::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QResultExprDlg_Data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QResultExprDlg_Data::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QResultExprDlg_Data))
        return static_cast<void*>(const_cast< QResultExprDlg_Data*>(this));
    return QDialog::qt_metacast(_clname);
}

int QResultExprDlg_Data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
