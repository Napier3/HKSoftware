/****************************************************************************
** Meta object code from reading C++ file 'SttReplayModuleChWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/TransPlay/SttReplayModuleChWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttReplayModuleChWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttReplayModuleChWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      48,   26,   25,   25, 0x05,
      77,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     111,  104,   25,   25, 0x0a,
     134,  104,   25,   25, 0x0a,
     158,  104,   25,   25, 0x0a,
     182,   25,   25,   25, 0x0a,
     198,   25,   25,   25, 0x0a,
     224,   25,   25,   25, 0x0a,
     250,   25,   25,   25, 0x0a,
     278,   25,   25,   25, 0x0a,
     296,   25,   25,   25, 0x0a,
     314,   25,   25,   25, 0x0a,
     332,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSttReplayModuleChWidget[] = {
    "CSttReplayModuleChWidget\0\0"
    "nModuleIndex,nChIndex\0"
    "sig_ModuleChChanged(int,int)\0"
    "sig_ModuleChRangeChanged()\0nIndex\0"
    "slot_ChSelChanged(int)\0slot_AChSelChanged(int)\0"
    "slot_BChSelChanged(int)\0slot_KChanged()\0"
    "slot_OpenRcdFileClicked()\0"
    "slot_SttLineEditChanged()\0"
    "slot_FloatLineEditChanged()\0"
    "slot_ChangedPT1()\0slot_ChangedPT2()\0"
    "slot_ChangedCT1()\0slot_ChangedCT2()\0"
};

void CSttReplayModuleChWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSttReplayModuleChWidget *_t = static_cast<CSttReplayModuleChWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_ModuleChChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_ModuleChRangeChanged(); break;
        case 2: _t->slot_ChSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_AChSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_BChSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_KChanged(); break;
        case 6: _t->slot_OpenRcdFileClicked(); break;
        case 7: _t->slot_SttLineEditChanged(); break;
        case 8: _t->slot_FloatLineEditChanged(); break;
        case 9: _t->slot_ChangedPT1(); break;
        case 10: _t->slot_ChangedPT2(); break;
        case 11: _t->slot_ChangedCT1(); break;
        case 12: _t->slot_ChangedCT2(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CSttReplayModuleChWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttReplayModuleChWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSttReplayModuleChWidget,
      qt_meta_data_CSttReplayModuleChWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttReplayModuleChWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttReplayModuleChWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttReplayModuleChWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttReplayModuleChWidget))
        return static_cast<void*>(const_cast< CSttReplayModuleChWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSttReplayModuleChWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CSttReplayModuleChWidget::sig_ModuleChChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CSttReplayModuleChWidget::sig_ModuleChRangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
