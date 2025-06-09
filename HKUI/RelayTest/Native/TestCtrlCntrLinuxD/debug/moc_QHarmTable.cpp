/****************************************************************************
** Meta object code from reading C++ file 'QHarmTable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Harm/QHarmTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QHarmTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QHarmTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      37,   11,   11,   11, 0x05,
      60,   11,   11,   11, 0x05,
      82,   11,   11,   11, 0x05,
     104,   11,   11,   11, 0x05,
     128,   11,   11,   11, 0x05,
     151,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,  169,   11,   11, 0x08,
     205,  199,   11,   11, 0x08,
     258,  249,   11,   11, 0x08,
     283,  249,   11,   11, 0x08,
     308,  249,   11,   11, 0x08,
     334,  249,   11,   11, 0x08,
     357,  249,   11,   11, 0x08,
     380,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QHarmTable[] = {
    "QHarmTable\0\0sig_ChanelValueChanged()\0"
    "sig_CheckNullClicked()\0sig_CheckAllClicekd()\0"
    "sig_SendDataChanged()\0sig_ChIndexChanged(int)\0"
    "sig_WaveValueChanged()\0sig_updataParas()\0"
    ",\0slot_OnCellChanged(int,int)\0pItem\0"
    "slot_OnItemDoubleClicked(QTableWidgetItem*)\0"
    "strValue\0slot_UpdataVamp(QString)\0"
    "slot_UpdataIamp(QString)\0"
    "slot_UpdataHzamp(QString)\0"
    "slot_UpdataZX(QString)\0slot_UpdataFX(QString)\0"
    "slot_UpdataLX()\0"
};

void QHarmTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QHarmTable *_t = static_cast<QHarmTable *>(_o);
        switch (_id) {
        case 0: _t->sig_ChanelValueChanged(); break;
        case 1: _t->sig_CheckNullClicked(); break;
        case 2: _t->sig_CheckAllClicekd(); break;
        case 3: _t->sig_SendDataChanged(); break;
        case 4: _t->sig_ChIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_WaveValueChanged(); break;
        case 6: _t->sig_updataParas(); break;
        case 7: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slot_OnItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->slot_UpdataVamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->slot_UpdataIamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->slot_UpdataHzamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->slot_UpdataZX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->slot_UpdataFX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->slot_UpdataLX(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QHarmTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QHarmTable::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_QHarmTable,
      qt_meta_data_QHarmTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QHarmTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QHarmTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QHarmTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QHarmTable))
        return static_cast<void*>(const_cast< QHarmTable*>(this));
    if (!strcmp(_clname, "CCommonCtrlInterface"))
        return static_cast< CCommonCtrlInterface*>(const_cast< QHarmTable*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int QHarmTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollTableWidget::qt_metacall(_c, _id, _a);
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
void QHarmTable::sig_ChanelValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QHarmTable::sig_CheckNullClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QHarmTable::sig_CheckAllClicekd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QHarmTable::sig_SendDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QHarmTable::sig_ChIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QHarmTable::sig_WaveValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QHarmTable::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
