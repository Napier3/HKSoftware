/****************************************************************************
** Meta object code from reading C++ file 'QLowVolAssessDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowVol/QLowVolAssessDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QLowVolAssessDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowVolAssessDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      39,   17,   17,   17, 0x0a,
      72,   64,   17,   17, 0x0a,
     106,   98,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QLowVolAssessDlg[] = {
    "QLowVolAssessDlg\0\0slot_btnOK_Clicked()\0"
    "slot_btnCancel_Clicked()\0row,col\0"
    "slot_cellClicked(int,int)\0strText\0"
    "slot_cmbErrorChanged(QString)\0"
};

void QLowVolAssessDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowVolAssessDlg *_t = static_cast<QLowVolAssessDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_btnOK_Clicked(); break;
        case 1: _t->slot_btnCancel_Clicked(); break;
        case 2: _t->slot_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_cmbErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QLowVolAssessDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowVolAssessDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QLowVolAssessDlg,
      qt_meta_data_QLowVolAssessDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowVolAssessDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowVolAssessDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowVolAssessDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowVolAssessDlg))
        return static_cast<void*>(const_cast< QLowVolAssessDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QLowVolAssessDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
