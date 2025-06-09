/****************************************************************************
** Meta object code from reading C++ file 'SttMUTestIecCbSelWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMUTestIecCbSelWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMUTestIecCbSelWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x08,
      43,   25,   25,   25, 0x08,
      64,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttMUTestIecCbSelWidget[] = {
    "QSttMUTestIecCbSelWidget\0\0slot_OKClicked()\0"
    "slot_CancelClicked()\0slot_Timer()\0"
};

void QSttMUTestIecCbSelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMUTestIecCbSelWidget *_t = static_cast<QSttMUTestIecCbSelWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        case 2: _t->slot_Timer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttMUTestIecCbSelWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMUTestIecCbSelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttMUTestIecCbSelWidget,
      qt_meta_data_QSttMUTestIecCbSelWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMUTestIecCbSelWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMUTestIecCbSelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMUTestIecCbSelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMUTestIecCbSelWidget))
        return static_cast<void*>(const_cast< QSttMUTestIecCbSelWidget*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttMUTestIecCbSelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttMUTestIecCbSelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
