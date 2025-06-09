/****************************************************************************
** Meta object code from reading C++ file 'SttIecSMV92Widget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecSMV92Widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecSMV92Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecSMV92Widget[] = {

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
      20,   19,   19,   19, 0x09,
      48,   19,   19,   19, 0x09,
      78,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecSMV92Widget[] = {
    "QSttIecSMV92Widget\0\0slot_SMV92OtherSetClicked()\0"
    "slot_lne_SmpRateEditClicked()\0"
    "slot_lne_SmpRateEdit_editingFinished()\0"
};

void QSttIecSMV92Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecSMV92Widget *_t = static_cast<QSttIecSMV92Widget *>(_o);
        switch (_id) {
        case 0: _t->slot_SMV92OtherSetClicked(); break;
        case 1: _t->slot_lne_SmpRateEditClicked(); break;
        case 2: _t->slot_lne_SmpRateEdit_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttIecSMV92Widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecSMV92Widget::staticMetaObject = {
    { &QSttIecConfigWidgetBase::staticMetaObject, qt_meta_stringdata_QSttIecSMV92Widget,
      qt_meta_data_QSttIecSMV92Widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecSMV92Widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecSMV92Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecSMV92Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecSMV92Widget))
        return static_cast<void*>(const_cast< QSttIecSMV92Widget*>(this));
    if (!strcmp(_clname, "CIecConfigInterface"))
        return static_cast< CIecConfigInterface*>(const_cast< QSttIecSMV92Widget*>(this));
    return QSttIecConfigWidgetBase::qt_metacast(_clname);
}

int QSttIecSMV92Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttIecConfigWidgetBase::qt_metacall(_c, _id, _a);
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
