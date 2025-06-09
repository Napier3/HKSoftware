/****************************************************************************
** Meta object code from reading C++ file 'QChMapsDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/ChRsMap/QChMapsDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QChMapsDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QChMapsDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      95,   11,   11,   11, 0x0a,
     120,   11,   11,   11, 0x0a,
     147,   11,   11,   11, 0x0a,
     174,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QChMapsDlg[] = {
    "QChMapsDlg\0\0bSysParasHasChanged\0"
    "sig_UpdateChRsMaps(BOOL)\0slot_OKClicked()\0"
    "slot_CancelClicked()\0slot_DefautMapsClicked()\0"
    "slot_ImportChMapsClicked()\0"
    "slot_ExportChMapsClicked()\0"
    "slot_LockMapsChecked(int)\0"
};

void QChMapsDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QChMapsDlg *_t = static_cast<QChMapsDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateChRsMaps((*reinterpret_cast< BOOL(*)>(_a[1]))); break;
        case 1: _t->slot_OKClicked(); break;
        case 2: _t->slot_CancelClicked(); break;
        case 3: _t->slot_DefautMapsClicked(); break;
        case 4: _t->slot_ImportChMapsClicked(); break;
        case 5: _t->slot_ExportChMapsClicked(); break;
        case 6: _t->slot_LockMapsChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QChMapsDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QChMapsDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QChMapsDlg,
      qt_meta_data_QChMapsDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QChMapsDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QChMapsDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QChMapsDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QChMapsDlg))
        return static_cast<void*>(const_cast< QChMapsDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QChMapsDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QChMapsDlg::sig_UpdateChRsMaps(BOOL _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
