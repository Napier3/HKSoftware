/****************************************************************************
** Meta object code from reading C++ file 'SttImportDvmFileWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ImportDvmFile/SttImportDvmFileWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttImportDvmFileWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttImportDvmFileWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   24,   24,   24, 0x0a,
      71,   24,   24,   24, 0x0a,
      88,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttImportDvmFileWidget[] = {
    "QSttImportDvmFileWidget\0\0"
    "sig_FreeImportDvmFileWidget()\0"
    "slot_PreClick()\0slot_NextClick()\0"
    "slot_CancelClick()\0"
};

void QSttImportDvmFileWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttImportDvmFileWidget *_t = static_cast<QSttImportDvmFileWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_FreeImportDvmFileWidget(); break;
        case 1: _t->slot_PreClick(); break;
        case 2: _t->slot_NextClick(); break;
        case 3: _t->slot_CancelClick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttImportDvmFileWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttImportDvmFileWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttImportDvmFileWidget,
      qt_meta_data_QSttImportDvmFileWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttImportDvmFileWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttImportDvmFileWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttImportDvmFileWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttImportDvmFileWidget))
        return static_cast<void*>(const_cast< QSttImportDvmFileWidget*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttImportDvmFileWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttImportDvmFileWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QSttImportDvmFileWidget::sig_FreeImportDvmFileWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
