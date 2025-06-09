/****************************************************************************
** Meta object code from reading C++ file 'qgooseparawidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/qgooseparawidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgooseparawidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGooseParaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      41,   17,   17,   17, 0x05,
      65,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   17,   17,   17, 0x09,
     110,   17,   17,   17, 0x09,
     135,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QGooseParaWidget[] = {
    "QGooseParaWidget\0\0sig_GooseDataChanged()\0"
    "sig_RepairDataChanged()\0sig_GoutMapChanged()\0"
    "slot_GooseDataChanged()\0"
    "slot_RepairDataChanged()\0slot_GoutMapChanged()\0"
};

void QGooseParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QGooseParaWidget *_t = static_cast<QGooseParaWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_GooseDataChanged(); break;
        case 1: _t->sig_RepairDataChanged(); break;
        case 2: _t->sig_GoutMapChanged(); break;
        case 3: _t->slot_GooseDataChanged(); break;
        case 4: _t->slot_RepairDataChanged(); break;
        case 5: _t->slot_GoutMapChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QGooseParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QGooseParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QGooseParaWidget,
      qt_meta_data_QGooseParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGooseParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGooseParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGooseParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGooseParaWidget))
        return static_cast<void*>(const_cast< QGooseParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QGooseParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QGooseParaWidget::sig_GooseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QGooseParaWidget::sig_RepairDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QGooseParaWidget::sig_GoutMapChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
