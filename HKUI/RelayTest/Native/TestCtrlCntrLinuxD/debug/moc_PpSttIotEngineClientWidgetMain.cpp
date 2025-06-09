/****************************************************************************
** Meta object code from reading C++ file 'PpSttIotEngineClientWidgetMain.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/SMARTTESTINTERFACE/QT/PpSttIotEngineClientWidgetMain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PpSttIotEngineClientWidgetMain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPpSttIotEngineClientWidgetMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   32,   32,   32, 0x0a,
      66,   32,   32,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QPpSttIotEngineClientWidgetMain[] = {
    "QPpSttIotEngineClientWidgetMain\0\0"
    "sig_NewDevice()\0slot_NewDevice()\0"
    "slot_InitCmdTimer()\0"
};

void QPpSttIotEngineClientWidgetMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPpSttIotEngineClientWidgetMain *_t = static_cast<QPpSttIotEngineClientWidgetMain *>(_o);
        switch (_id) {
        case 0: _t->sig_NewDevice(); break;
        case 1: _t->slot_NewDevice(); break;
        case 2: _t->slot_InitCmdTimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QPpSttIotEngineClientWidgetMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPpSttIotEngineClientWidgetMain::staticMetaObject = {
    { &QPpSttIotEngineClientWidget::staticMetaObject, qt_meta_stringdata_QPpSttIotEngineClientWidgetMain,
      qt_meta_data_QPpSttIotEngineClientWidgetMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPpSttIotEngineClientWidgetMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPpSttIotEngineClientWidgetMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPpSttIotEngineClientWidgetMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPpSttIotEngineClientWidgetMain))
        return static_cast<void*>(const_cast< QPpSttIotEngineClientWidgetMain*>(this));
    return QPpSttIotEngineClientWidget::qt_metacast(_clname);
}

int QPpSttIotEngineClientWidgetMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPpSttIotEngineClientWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QPpSttIotEngineClientWidgetMain::sig_NewDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
