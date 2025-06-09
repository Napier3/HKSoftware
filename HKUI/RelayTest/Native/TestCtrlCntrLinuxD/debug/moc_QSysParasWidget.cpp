/****************************************************************************
** Meta object code from reading C++ file 'QSysParasWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/SysParas/QSysParasWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSysParasWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSysParasWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x0a,
      50,   17,   16,   16, 0x0a,
      78,   17,   16,   16, 0x0a,
     110,   16,   16,   16, 0x0a,
     153,   16,   16,   16, 0x0a,
     195,   16,   16,   16, 0x0a,
     233,   16,   16,   16, 0x0a,
     276,  269,   16,   16, 0x0a,
     312,  269,   16,   16, 0x0a,
     348,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSysParasWidget[] = {
    "QSysParasWidget\0\0nIndex\0"
    "slot_changeSecondSyn(int)\0"
    "slot_changeDigitalType(int)\0"
    "slot_changeDigitalMeasType(int)\0"
    "slot_radio_BCodePositiveLogicChanged(bool)\0"
    "slot_radio_BCodeNegtiveLogicChanged(bool)\0"
    "slot_radio_1588PeerDelayChanged(bool)\0"
    "slot_radio_1588ReqRespChanged(bool)\0"
    "nState\0slot_DigitalCheck_stateChanged(int)\0"
    "slot_WeakSelCheck_stateChanged(int)\0"
    "slot_OnLineEditClicked()\0"
};

void QSysParasWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSysParasWidget *_t = static_cast<QSysParasWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_changeSecondSyn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_changeDigitalType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_changeDigitalMeasType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_radio_BCodePositiveLogicChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_radio_BCodeNegtiveLogicChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_radio_1588PeerDelayChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slot_radio_1588ReqRespChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slot_DigitalCheck_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_WeakSelCheck_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_OnLineEditClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSysParasWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSysParasWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSysParasWidget,
      qt_meta_data_QSysParasWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSysParasWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSysParasWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSysParasWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSysParasWidget))
        return static_cast<void*>(const_cast< QSysParasWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSysParasWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
