/****************************************************************************
** Meta object code from reading C++ file 'goosepubwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/goosepubwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'goosepubwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GoosePubWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      39,   15,   15,   15, 0x05,
      63,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   15,   15,   15, 0x08,
     117,   15,   15,   15, 0x08,
     150,   15,   15,   15, 0x08,
     169,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GoosePubWidget[] = {
    "GoosePubWidget\0\0sig_GooseDataChanged()\0"
    "sig_RepairDataChanged()\0sig_GoutMapChanged()\0"
    "slot_chb_InvertStateChanged(int)\0"
    "slot_chb_RepairStateChanged(int)\0"
    "slot_dataChanged()\0slot_GoutMapChanged()\0"
};

void GoosePubWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GoosePubWidget *_t = static_cast<GoosePubWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_GooseDataChanged(); break;
        case 1: _t->sig_RepairDataChanged(); break;
        case 2: _t->sig_GoutMapChanged(); break;
        case 3: _t->slot_chb_InvertStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_chb_RepairStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_dataChanged(); break;
        case 6: _t->slot_GoutMapChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GoosePubWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GoosePubWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GoosePubWidget,
      qt_meta_data_GoosePubWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GoosePubWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GoosePubWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GoosePubWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GoosePubWidget))
        return static_cast<void*>(const_cast< GoosePubWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GoosePubWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GoosePubWidget::sig_GooseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GoosePubWidget::sig_RepairDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GoosePubWidget::sig_GoutMapChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
