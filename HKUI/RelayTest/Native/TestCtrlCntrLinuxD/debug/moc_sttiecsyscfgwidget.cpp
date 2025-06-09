/****************************************************************************
** Meta object code from reading C++ file 'sttiecsyscfgwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/sttiecsyscfgwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sttiecsyscfgwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecSysCfgWidget[] = {

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
      21,   20,   20,   20, 0x0a,
      50,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecSysCfgWidget[] = {
    "QSttIecSysCfgWidget\0\0slot_ParasSetSelChanged(int)\0"
    "slot_PkgSendSelChanged(int)\0"
};

void QSttIecSysCfgWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecSysCfgWidget *_t = static_cast<QSttIecSysCfgWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_ParasSetSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_PkgSendSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecSysCfgWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecSysCfgWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIecSysCfgWidget,
      qt_meta_data_QSttIecSysCfgWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecSysCfgWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecSysCfgWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecSysCfgWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecSysCfgWidget))
        return static_cast<void*>(const_cast< QSttIecSysCfgWidget*>(this));
    if (!strcmp(_clname, "CIecConfigInterface"))
        return static_cast< CIecConfigInterface*>(const_cast< QSttIecSysCfgWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIecSysCfgWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
