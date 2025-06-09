/****************************************************************************
** Meta object code from reading C++ file 'SttIecSmvWaveMainWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/SttIecSmvWaveMainWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecSmvWaveMainWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecSmvWaveMainWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      37,   25,   25,   25, 0x0a,
      49,   25,   25,   25, 0x0a,
      62,   25,   25,   25, 0x0a,
      76,   25,   25,   25, 0x0a,
      89,   25,   25,   25, 0x0a,
     102,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecSmvWaveMainWidget[] = {
    "QSttIecSmvWaveMainWidget\0\0MoveLeft()\0"
    "MoveRight()\0ZoomInChan()\0ZoomOutChan()\0"
    "slot_Reset()\0ZoomInTime()\0ZoomOutTime()\0"
};

void QSttIecSmvWaveMainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecSmvWaveMainWidget *_t = static_cast<QSttIecSmvWaveMainWidget *>(_o);
        switch (_id) {
        case 0: _t->MoveLeft(); break;
        case 1: _t->MoveRight(); break;
        case 2: _t->ZoomInChan(); break;
        case 3: _t->ZoomOutChan(); break;
        case 4: _t->slot_Reset(); break;
        case 5: _t->ZoomInTime(); break;
        case 6: _t->ZoomOutTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttIecSmvWaveMainWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecSmvWaveMainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIecSmvWaveMainWidget,
      qt_meta_data_QSttIecSmvWaveMainWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecSmvWaveMainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecSmvWaveMainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecSmvWaveMainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecSmvWaveMainWidget))
        return static_cast<void*>(const_cast< QSttIecSmvWaveMainWidget*>(this));
    if (!strcmp(_clname, "CSttIecRcdFuncInterface"))
        return static_cast< CSttIecRcdFuncInterface*>(const_cast< QSttIecSmvWaveMainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIecSmvWaveMainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
