/****************************************************************************
** Meta object code from reading C++ file 'SttPxEngineDvmTreeCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/SMARTTESTINTERFACE/QT/SttPxEngineDvmTreeCtrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttPxEngineDvmTreeCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttPxEngineDvmTreeCtrl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      59,   24,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QSttPxEngineDvmTreeCtrl[] = {
    "QSttPxEngineDvmTreeCtrl\0\0"
    "sig_MouseMoveGbTree(QMouseEvent*)\0"
    "sig_focusOutEventGbTree(QFocusEvent*)\0"
};

void QSttPxEngineDvmTreeCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttPxEngineDvmTreeCtrl *_t = static_cast<QSttPxEngineDvmTreeCtrl *>(_o);
        switch (_id) {
        case 0: _t->sig_MouseMoveGbTree((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->sig_focusOutEventGbTree((*reinterpret_cast< QFocusEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttPxEngineDvmTreeCtrl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttPxEngineDvmTreeCtrl::staticMetaObject = {
    { &CExBaseListTreeCtrl::staticMetaObject, qt_meta_stringdata_QSttPxEngineDvmTreeCtrl,
      qt_meta_data_QSttPxEngineDvmTreeCtrl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttPxEngineDvmTreeCtrl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttPxEngineDvmTreeCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttPxEngineDvmTreeCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttPxEngineDvmTreeCtrl))
        return static_cast<void*>(const_cast< QSttPxEngineDvmTreeCtrl*>(this));
    if (!strcmp(_clname, "CScrollCtrlInterface"))
        return static_cast< CScrollCtrlInterface*>(const_cast< QSttPxEngineDvmTreeCtrl*>(this));
    return CExBaseListTreeCtrl::qt_metacast(_clname);
}

int QSttPxEngineDvmTreeCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CExBaseListTreeCtrl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QSttPxEngineDvmTreeCtrl::sig_MouseMoveGbTree(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSttPxEngineDvmTreeCtrl::sig_focusOutEventGbTree(QFocusEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
