/****************************************************************************
** Meta object code from reading C++ file 'SttReportHeadSetDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SttReportHeadSetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttReportHeadSetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttReportHeadSetDlg[] = {

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
      33,   22,   21,   21, 0x0a,
      76,   21,   21,   21, 0x0a,
      91,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttReportHeadSetDlg[] = {
    "QSttReportHeadSetDlg\0\0pItem,nCol\0"
    "slot_TreeItemChanged(QTreeWidgetItem*,int)\0"
    "slot_OKClick()\0slot_CancelClick()\0"
};

void QSttReportHeadSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttReportHeadSetDlg *_t = static_cast<QSttReportHeadSetDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_TreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_OKClick(); break;
        case 2: _t->slot_CancelClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttReportHeadSetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttReportHeadSetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttReportHeadSetDlg,
      qt_meta_data_QSttReportHeadSetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttReportHeadSetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttReportHeadSetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttReportHeadSetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttReportHeadSetDlg))
        return static_cast<void*>(const_cast< QSttReportHeadSetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttReportHeadSetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
