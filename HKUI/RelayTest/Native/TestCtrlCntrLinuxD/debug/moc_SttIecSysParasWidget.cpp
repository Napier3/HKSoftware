/****************************************************************************
** Meta object code from reading C++ file 'SttIecSysParasWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecSysParasWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecSysParasWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttSysParasWidget[] = {

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
      20,   19,   19,   19, 0x0a,
      49,   19,   19,   19, 0x0a,
      78,   19,   19,   19, 0x0a,
     106,   19,   19,   19, 0x0a,
     136,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttSysParasWidget[] = {
    "QSttSysParasWidget\0\0slot_PkgSendTypeChanged(int)\0"
    "slot_ParasSetSelChanged(int)\0"
    "slot_PkgSendSelChanged(int)\0"
    "slot_OtherSetPushBtnClicked()\0"
    "slot_lne_Clicked()\0"
};

void QSttSysParasWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttSysParasWidget *_t = static_cast<QSttSysParasWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_PkgSendTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_ParasSetSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_PkgSendSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_OtherSetPushBtnClicked(); break;
        case 4: _t->slot_lne_Clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttSysParasWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttSysParasWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttSysParasWidget,
      qt_meta_data_QSttSysParasWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttSysParasWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttSysParasWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttSysParasWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttSysParasWidget))
        return static_cast<void*>(const_cast< QSttSysParasWidget*>(this));
    if (!strcmp(_clname, "CIecConfigInterface"))
        return static_cast< CIecConfigInterface*>(const_cast< QSttSysParasWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttSysParasWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
