/****************************************************************************
** Meta object code from reading C++ file 'SttFileSaveAsDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SttFileSaveAsDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttFileSaveAsDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttFileSaveAsDlg[] = {

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
      19,   18,   18,   18, 0x0a,
      34,   18,   18,   18, 0x0a,
      53,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttFileSaveAsDlg[] = {
    "QSttFileSaveAsDlg\0\0slot_OKClick()\0"
    "slot_CancelClick()\0slot_FileNameLineEditClicked()\0"
};

void QSttFileSaveAsDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttFileSaveAsDlg *_t = static_cast<QSttFileSaveAsDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClick(); break;
        case 1: _t->slot_CancelClick(); break;
        case 2: _t->slot_FileNameLineEditClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttFileSaveAsDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFileSaveAsDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttFileSaveAsDlg,
      qt_meta_data_QSttFileSaveAsDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFileSaveAsDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFileSaveAsDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFileSaveAsDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFileSaveAsDlg))
        return static_cast<void*>(const_cast< QSttFileSaveAsDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttFileSaveAsDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
