/****************************************************************************
** Meta object code from reading C++ file 'QSttMUTimeTestWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Manual/QSttMUTimeTestWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttMUTimeTestWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMUTimeTestWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   40,   21,   21, 0x08,
      79,   21,   21,   21, 0x08,
     104,   21,   21,   21, 0x08,
     134,   21,   21,   21, 0x08,
     153,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttMUTimeTestWidget[] = {
    "QSttMUTimeTestWidget\0\0sig_updataParas()\0"
    "bValue\0slot_OnPPSSetRadioChanged(bool)\0"
    "slot_OnOutCheckChanged()\0"
    "slot_OnDelayCompEditChanged()\0"
    "slot_AssistTimer()\0slot_ResultUpdateTimer()\0"
};

void QSttMUTimeTestWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMUTimeTestWidget *_t = static_cast<QSttMUTimeTestWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        case 1: _t->slot_OnPPSSetRadioChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_OnOutCheckChanged(); break;
        case 3: _t->slot_OnDelayCompEditChanged(); break;
        case 4: _t->slot_AssistTimer(); break;
        case 5: _t->slot_ResultUpdateTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMUTimeTestWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMUTimeTestWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttMUTimeTestWidget,
      qt_meta_data_QSttMUTimeTestWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMUTimeTestWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMUTimeTestWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMUTimeTestWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMUTimeTestWidget))
        return static_cast<void*>(const_cast< QSttMUTimeTestWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttMUTimeTestWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void QSttMUTimeTestWidget::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
