/****************************************************************************
** Meta object code from reading C++ file 'SttMUTestChsSetDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/MUTest/SttMUTestChsSetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMUTestChsSetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMUTestChsSetDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      38,   20,   20,   20, 0x0a,
      59,   20,   20,   20, 0x0a,
      87,   20,   20,   20, 0x0a,
     118,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMUTestChsSetDlg[] = {
    "QSttMUTestChsSetDlg\0\0slot_OKClicked()\0"
    "slot_CancelClicked()\0slot_BtnClickedAllClicked()\0"
    "slot_BtnDisClickedAllClicked()\0"
    "slot_BtnInvertClicked()\0"
};

void QSttMUTestChsSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMUTestChsSetDlg *_t = static_cast<QSttMUTestChsSetDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        case 2: _t->slot_BtnClickedAllClicked(); break;
        case 3: _t->slot_BtnDisClickedAllClicked(); break;
        case 4: _t->slot_BtnInvertClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttMUTestChsSetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMUTestChsSetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttMUTestChsSetDlg,
      qt_meta_data_QSttMUTestChsSetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMUTestChsSetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMUTestChsSetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMUTestChsSetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMUTestChsSetDlg))
        return static_cast<void*>(const_cast< QSttMUTestChsSetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttMUTestChsSetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
