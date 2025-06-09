/****************************************************************************
** Meta object code from reading C++ file 'QWaveGraphWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/WaveGraphWidget/QWaveGraphWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QWaveGraphWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QWaveGraphWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   17,   17,   17, 0x0a,
     106,   17,   17,   17, 0x0a,
     130,   17,   17,   17, 0x0a,
     154,   17,   17,   17, 0x0a,
     165,   17,   17,   17, 0x0a,
     177,   17,   17,   17, 0x0a,
     190,   17,   17,   17, 0x0a,
     204,   17,   17,   17, 0x0a,
     217,   17,   17,   17, 0x0a,
     230,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QWaveGraphWidget[] = {
    "QWaveGraphWidget\0\0dValueA,dValueB\0"
    "sig_UpdateTwoCursorTimeValues(double,double)\0"
    "slot_UpdateDrawWaveGraph()\0"
    "slotDrawOptr_PrevPage()\0slotDrawOptr_NextPage()\0"
    "MoveLeft()\0MoveRight()\0ZoomInChan()\0"
    "ZoomOutChan()\0slot_Reset()\0ZoomInTime()\0"
    "ZoomOutTime()\0"
};

void QWaveGraphWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QWaveGraphWidget *_t = static_cast<QWaveGraphWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateTwoCursorTimeValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->slot_UpdateDrawWaveGraph(); break;
        case 2: _t->slotDrawOptr_PrevPage(); break;
        case 3: _t->slotDrawOptr_NextPage(); break;
        case 4: _t->MoveLeft(); break;
        case 5: _t->MoveRight(); break;
        case 6: _t->ZoomInChan(); break;
        case 7: _t->ZoomOutChan(); break;
        case 8: _t->slot_Reset(); break;
        case 9: _t->ZoomInTime(); break;
        case 10: _t->ZoomOutTime(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QWaveGraphWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QWaveGraphWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QWaveGraphWidget,
      qt_meta_data_QWaveGraphWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QWaveGraphWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QWaveGraphWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QWaveGraphWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QWaveGraphWidget))
        return static_cast<void*>(const_cast< QWaveGraphWidget*>(this));
    if (!strcmp(_clname, "CViewAnalyse"))
        return static_cast< CViewAnalyse*>(const_cast< QWaveGraphWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QWaveGraphWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QWaveGraphWidget::sig_UpdateTwoCursorTimeValues(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
