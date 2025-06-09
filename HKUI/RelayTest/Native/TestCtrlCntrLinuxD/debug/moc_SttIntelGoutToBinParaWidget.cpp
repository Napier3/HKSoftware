/****************************************************************************
** Meta object code from reading C++ file 'SttIntelGoutToBinParaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/SttIntelGoutToBinParaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIntelGoutToBinParaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIntelGoutToBinParaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x05,
      53,   29,   29,   29, 0x05,
      77,   29,   29,   29, 0x05,
      94,   29,   29,   29, 0x05,
     125,  115,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
     147,   29,   29,   29, 0x09,
     171,   29,   29,   29, 0x09,
     196,   29,   29,   29, 0x09,
     214,   29,   29,   29, 0x09,
     236,  115,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIntelGoutToBinParaWidget[] = {
    "QSttIntelGoutToBinParaWidget\0\0"
    "sig_GooseDataChanged()\0sig_RepairDataChanged()\0"
    "sig_RevertData()\0sig_GoutMapChanged()\0"
    "nRowIndex\0sig_GoutRowIndex(int)\0"
    "slot_GooseDataChanged()\0"
    "slot_RepairDataChanged()\0slot_RevertData()\0"
    "slot_GoutMapChanged()\0slot_GoutRowIndex(int)\0"
};

void QSttIntelGoutToBinParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIntelGoutToBinParaWidget *_t = static_cast<QSttIntelGoutToBinParaWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_GooseDataChanged(); break;
        case 1: _t->sig_RepairDataChanged(); break;
        case 2: _t->sig_RevertData(); break;
        case 3: _t->sig_GoutMapChanged(); break;
        case 4: _t->sig_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_GooseDataChanged(); break;
        case 6: _t->slot_RepairDataChanged(); break;
        case 7: _t->slot_RevertData(); break;
        case 8: _t->slot_GoutMapChanged(); break;
        case 9: _t->slot_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIntelGoutToBinParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIntelGoutToBinParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIntelGoutToBinParaWidget,
      qt_meta_data_QSttIntelGoutToBinParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIntelGoutToBinParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIntelGoutToBinParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIntelGoutToBinParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIntelGoutToBinParaWidget))
        return static_cast<void*>(const_cast< QSttIntelGoutToBinParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIntelGoutToBinParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QSttIntelGoutToBinParaWidget::sig_GooseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttIntelGoutToBinParaWidget::sig_RepairDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QSttIntelGoutToBinParaWidget::sig_RevertData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QSttIntelGoutToBinParaWidget::sig_GoutMapChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QSttIntelGoutToBinParaWidget::sig_GoutRowIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
