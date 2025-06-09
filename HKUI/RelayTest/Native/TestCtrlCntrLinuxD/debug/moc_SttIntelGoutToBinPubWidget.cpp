/****************************************************************************
** Meta object code from reading C++ file 'SttIntelGoutToBinPubWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/SttIntelGoutToBinPubWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIntelGoutToBinPubWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIntelGoutToBinPubWidget[] = {

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
      29,   28,   28,   28, 0x05,
      52,   28,   28,   28, 0x05,
      76,   28,   28,   28, 0x05,
      97,   28,   28,   28, 0x05,
     124,  114,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     146,   28,   28,   28, 0x08,
     179,   28,   28,   28, 0x08,
     204,   28,   28,   28, 0x08,
     223,   28,   28,   28, 0x08,
     245,  114,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttIntelGoutToBinPubWidget[] = {
    "QSttIntelGoutToBinPubWidget\0\0"
    "sig_GooseDataChanged()\0sig_RepairDataChanged()\0"
    "sig_GoutMapChanged()\0sig_RevertData()\0"
    "nRowIndex\0sig_GoutRowIndex(int)\0"
    "slot_chb_RepairStateChanged(int)\0"
    "slot_pbn_RevertClicked()\0slot_dataChanged()\0"
    "slot_GoutMapChanged()\0slot_GoutRowIndex(int)\0"
};

void QSttIntelGoutToBinPubWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIntelGoutToBinPubWidget *_t = static_cast<QSttIntelGoutToBinPubWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_GooseDataChanged(); break;
        case 1: _t->sig_RepairDataChanged(); break;
        case 2: _t->sig_GoutMapChanged(); break;
        case 3: _t->sig_RevertData(); break;
        case 4: _t->sig_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_chb_RepairStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_pbn_RevertClicked(); break;
        case 7: _t->slot_dataChanged(); break;
        case 8: _t->slot_GoutMapChanged(); break;
        case 9: _t->slot_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIntelGoutToBinPubWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIntelGoutToBinPubWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIntelGoutToBinPubWidget,
      qt_meta_data_QSttIntelGoutToBinPubWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIntelGoutToBinPubWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIntelGoutToBinPubWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIntelGoutToBinPubWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIntelGoutToBinPubWidget))
        return static_cast<void*>(const_cast< QSttIntelGoutToBinPubWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIntelGoutToBinPubWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QSttIntelGoutToBinPubWidget::sig_GooseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttIntelGoutToBinPubWidget::sig_RepairDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QSttIntelGoutToBinPubWidget::sig_GoutMapChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QSttIntelGoutToBinPubWidget::sig_RevertData()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QSttIntelGoutToBinPubWidget::sig_GoutRowIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
