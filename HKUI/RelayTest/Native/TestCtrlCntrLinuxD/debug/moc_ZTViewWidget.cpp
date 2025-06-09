/****************************************************************************
** Meta object code from reading C++ file 'ZTViewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/ZTViewWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZTViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QZTViewWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x05,
      55,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   14,   14,   14, 0x0a,
      98,   14,   14,   14, 0x0a,
     121,   14,   14,   14, 0x0a,
     142,   14,   14,   14, 0x0a,
     170,   14,   14,   14, 0x0a,
     192,   14,   14,   14, 0x0a,
     216,   14,   14,   14, 0x0a,
     240,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QZTViewWidget[] = {
    "QZTViewWidget\0\0fx,fy\0"
    "sig_AddPointLocation(float,float)\0"
    "sig_LeftButtonDown()\0slotDrawOptr_ZoomIn()\0"
    "slotDrawOptr_ZoomOut()\0slotDrawOptr_Reset()\0"
    "slot_ActionTestAddClicked()\0"
    "slotDrawOptr_MoveUp()\0slotDrawOptr_MoveDown()\0"
    "slotDrawOptr_MoveLeft()\0"
    "slotDrawOptr_MoveRight()\0"
};

void QZTViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QZTViewWidget *_t = static_cast<QZTViewWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_AddPointLocation((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->sig_LeftButtonDown(); break;
        case 2: _t->slotDrawOptr_ZoomIn(); break;
        case 3: _t->slotDrawOptr_ZoomOut(); break;
        case 4: _t->slotDrawOptr_Reset(); break;
        case 5: _t->slot_ActionTestAddClicked(); break;
        case 6: _t->slotDrawOptr_MoveUp(); break;
        case 7: _t->slotDrawOptr_MoveDown(); break;
        case 8: _t->slotDrawOptr_MoveLeft(); break;
        case 9: _t->slotDrawOptr_MoveRight(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QZTViewWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QZTViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QZTViewWidget,
      qt_meta_data_QZTViewWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QZTViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QZTViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QZTViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QZTViewWidget))
        return static_cast<void*>(const_cast< QZTViewWidget*>(this));
    if (!strcmp(_clname, "CInternationalZTInterface"))
        return static_cast< CInternationalZTInterface*>(const_cast< QZTViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QZTViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QZTViewWidget::sig_AddPointLocation(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QZTViewWidget::sig_LeftButtonDown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
