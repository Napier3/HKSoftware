/****************************************************************************
** Meta object code from reading C++ file 'SwingImpChartWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Swing/SwingImpChartWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SwingImpChartWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSwingImpChartWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   22,   21,   21, 0x05,
      63,   22,   21,   21, 0x05,
     100,   22,   21,   21, 0x05,
     134,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,  155,   21,   21, 0x0a,
     213,   21,   21,   21, 0x0a,
     229,   21,   21,   21, 0x0a,
     251,   21,   21,   21, 0x0a,
     274,   21,   21,   21, 0x0a,
     295,   21,   21,   21, 0x0a,
     320,   21,   21,   21, 0x0a,
     342,   21,   21,   21, 0x0a,
     366,   21,   21,   21, 0x0a,
     390,   21,   21,   21, 0x0a,
     415,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSwingImpChartWidget[] = {
    "QSwingImpChartWidget\0\0fx,fy\0"
    "sig_PlotDoubleClicked(float,float)\0"
    "sig_UpdatePointLocation(float,float)\0"
    "sig_AddPointLocation(float,float)\0"
    "sig_LeftButtonDown()\0pCharacteristic\0"
    "slot_UpdateDrawCharacters(CExBaseObject*)\0"
    "slot_ZKDel(int)\0slotDrawOptr_ZoomIn()\0"
    "slotDrawOptr_ZoomOut()\0slotDrawOptr_Reset()\0"
    "slotDrawOptr_MouseZoom()\0slotDrawOptr_MoveUp()\0"
    "slotDrawOptr_MoveDown()\0slotDrawOptr_MoveLeft()\0"
    "slotDrawOptr_MoveRight()\0"
    "slot_ActionTestAddClicked()\0"
};

void QSwingImpChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSwingImpChartWidget *_t = static_cast<QSwingImpChartWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_PlotDoubleClicked((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->sig_UpdatePointLocation((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 2: _t->sig_AddPointLocation((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->sig_LeftButtonDown(); break;
        case 4: _t->slot_UpdateDrawCharacters((*reinterpret_cast< CExBaseObject*(*)>(_a[1]))); break;
        case 5: _t->slot_ZKDel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotDrawOptr_ZoomIn(); break;
        case 7: _t->slotDrawOptr_ZoomOut(); break;
        case 8: _t->slotDrawOptr_Reset(); break;
        case 9: _t->slotDrawOptr_MouseZoom(); break;
        case 10: _t->slotDrawOptr_MoveUp(); break;
        case 11: _t->slotDrawOptr_MoveDown(); break;
        case 12: _t->slotDrawOptr_MoveLeft(); break;
        case 13: _t->slotDrawOptr_MoveRight(); break;
        case 14: _t->slot_ActionTestAddClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSwingImpChartWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSwingImpChartWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSwingImpChartWidget,
      qt_meta_data_QSwingImpChartWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSwingImpChartWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSwingImpChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSwingImpChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSwingImpChartWidget))
        return static_cast<void*>(const_cast< QSwingImpChartWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSwingImpChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void QSwingImpChartWidget::sig_PlotDoubleClicked(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSwingImpChartWidget::sig_UpdatePointLocation(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSwingImpChartWidget::sig_AddPointLocation(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSwingImpChartWidget::sig_LeftButtonDown()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
