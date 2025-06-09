/****************************************************************************
** Meta object code from reading C++ file 'PpSttIotEngineClientAppWnd.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/SMARTTESTINTERFACE/QT/PpSttIotEngineClientAppWnd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PpSttIotEngineClientAppWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPpSttIotEngineClientWidgetWnd[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      46,   32,   31,   31, 0x05,
      76,   32,   31,   31, 0x05,
     111,   32,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
     145,   32,   31,   31, 0x08,
     176,   32,   31,   31, 0x08,
     212,   32,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPpSttIotEngineClientWidgetWnd[] = {
    "QPpSttIotEngineClientWidgetWnd\0\0"
    "wParam,lParam\0sig_OnCommCommandMsg(int,int)\0"
    "sig_OnEngineSystemMessage(int,int)\0"
    "sig_OnEngineEventMessage(int,int)\0"
    "slot_OnCommCommandMsg(int,int)\0"
    "slot_OnEngineSystemMessage(int,int)\0"
    "slot_OnEngineEventMessage(int,int)\0"
};

void QPpSttIotEngineClientWidgetWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPpSttIotEngineClientWidgetWnd *_t = static_cast<QPpSttIotEngineClientWidgetWnd *>(_o);
        switch (_id) {
        case 0: _t->sig_OnCommCommandMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_OnEngineSystemMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sig_OnEngineEventMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_OnCommCommandMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_OnEngineSystemMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slot_OnEngineEventMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPpSttIotEngineClientWidgetWnd::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPpSttIotEngineClientWidgetWnd::staticMetaObject = {
    { &CWnd::staticMetaObject, qt_meta_stringdata_QPpSttIotEngineClientWidgetWnd,
      qt_meta_data_QPpSttIotEngineClientWidgetWnd, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPpSttIotEngineClientWidgetWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPpSttIotEngineClientWidgetWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPpSttIotEngineClientWidgetWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPpSttIotEngineClientWidgetWnd))
        return static_cast<void*>(const_cast< QPpSttIotEngineClientWidgetWnd*>(this));
    return CWnd::qt_metacast(_clname);
}

int QPpSttIotEngineClientWidgetWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CWnd::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QPpSttIotEngineClientWidgetWnd::sig_OnCommCommandMsg(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QPpSttIotEngineClientWidgetWnd::sig_OnEngineSystemMessage(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QPpSttIotEngineClientWidgetWnd::sig_OnEngineEventMessage(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
