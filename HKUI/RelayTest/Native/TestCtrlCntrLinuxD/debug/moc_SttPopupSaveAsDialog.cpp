/****************************************************************************
** Meta object code from reading C++ file 'SttPopupSaveAsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/PopupDialog/SttPopupSaveAsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttPopupSaveAsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttPopupSaveAsDialog[] = {

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
      28,   23,   22,   22, 0x0a,
      68,   61,   22,   22, 0x0a,
     103,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttPopupSaveAsDialog[] = {
    "QSttPopupSaveAsDialog\0\0arg1\0"
    "on_FileName_textChanged(QString)\0"
    "nState\0slot_ExternalPathStateChanged(int)\0"
    "slot_OKClicked()\0"
};

void QSttPopupSaveAsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttPopupSaveAsDialog *_t = static_cast<QSttPopupSaveAsDialog *>(_o);
        switch (_id) {
        case 0: _t->on_FileName_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->slot_ExternalPathStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_OKClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttPopupSaveAsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttPopupSaveAsDialog::staticMetaObject = {
    { &QSttFileDlgBase::staticMetaObject, qt_meta_stringdata_QSttPopupSaveAsDialog,
      qt_meta_data_QSttPopupSaveAsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttPopupSaveAsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttPopupSaveAsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttPopupSaveAsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttPopupSaveAsDialog))
        return static_cast<void*>(const_cast< QSttPopupSaveAsDialog*>(this));
    return QSttFileDlgBase::qt_metacast(_clname);
}

int QSttPopupSaveAsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttFileDlgBase::qt_metacall(_c, _id, _a);
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
