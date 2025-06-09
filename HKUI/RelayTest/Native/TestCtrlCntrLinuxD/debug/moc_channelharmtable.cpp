/****************************************************************************
** Meta object code from reading C++ file 'channelharmtable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/ChannelParaSet/channelharmtable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'channelharmtable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CComboBoxHarmDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CComboBoxHarmDelegate[] = {
    "CComboBoxHarmDelegate\0"
};

void CComboBoxHarmDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CComboBoxHarmDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CComboBoxHarmDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_CComboBoxHarmDelegate,
      qt_meta_data_CComboBoxHarmDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CComboBoxHarmDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CComboBoxHarmDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CComboBoxHarmDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CComboBoxHarmDelegate))
        return static_cast<void*>(const_cast< CComboBoxHarmDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int CComboBoxHarmDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QChannelHarmTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      61,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     119,  111,   18,   18, 0x09,
     153,  147,   18,   18, 0x09,
     195,  191,   18,   18, 0x09,
     229,  222,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QChannelHarmTable[] = {
    "QChannelHarmTable\0\0"
    "moudleType,channelNum,valueFlag,harmvalue\0"
    "sig_ChannelValueChanged(MOUDLEType,int,int,float)\0"
    "row,col\0slot_OnCellChanged(int,int)\0"
    "pItem\0slot_OnItemClicked(QTableWidgetItem*)\0"
    "pos\0slot_TableShowMent(QPoint)\0editor\0"
    "slot_HarmCountChanged(QWidget*)\0"
};

void QChannelHarmTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QChannelHarmTable *_t = static_cast<QChannelHarmTable *>(_o);
        switch (_id) {
        case 0: _t->sig_ChannelValueChanged((*reinterpret_cast< MOUDLEType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_OnItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->slot_TableShowMent((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->slot_HarmCountChanged((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QChannelHarmTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QChannelHarmTable::staticMetaObject = {
    { &QChannelTable::staticMetaObject, qt_meta_stringdata_QChannelHarmTable,
      qt_meta_data_QChannelHarmTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QChannelHarmTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QChannelHarmTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QChannelHarmTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QChannelHarmTable))
        return static_cast<void*>(const_cast< QChannelHarmTable*>(this));
    return QChannelTable::qt_metacast(_clname);
}

int QChannelHarmTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChannelTable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QChannelHarmTable::sig_ChannelValueChanged(MOUDLEType _t1, int _t2, int _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
