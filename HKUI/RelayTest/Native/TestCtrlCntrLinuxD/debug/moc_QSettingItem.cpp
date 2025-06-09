/****************************************************************************
** Meta object code from reading C++ file 'QSettingItem.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SettingCtrls/QSettingItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSettingItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSettingItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x0a,
      55,   13,   13,   13, 0x0a,
      70,   13,   13,   13, 0x0a,
      89,   83,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSettingItem[] = {
    "QSettingItem\0\0item\0"
    "slot_itemPressed(QTableWidgetItem*)\0"
    "slot_Setting()\0slot_Clear()\0bHide\0"
    "slot_Cannel(bool)\0"
};

void QSettingItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSettingItem *_t = static_cast<QSettingItem *>(_o);
        switch (_id) {
        case 0: _t->slot_itemPressed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->slot_Setting(); break;
        case 2: _t->slot_Clear(); break;
        case 3: _t->slot_Cannel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSettingItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSettingItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSettingItem,
      qt_meta_data_QSettingItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSettingItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSettingItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSettingItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSettingItem))
        return static_cast<void*>(const_cast< QSettingItem*>(this));
    if (!strcmp(_clname, "QGV_ITEM"))
        return static_cast< QGV_ITEM*>(const_cast< QSettingItem*>(this));
    if (!strcmp(_clname, "CSettingInterface"))
        return static_cast< CSettingInterface*>(const_cast< QSettingItem*>(this));
    return QObject::qt_metacast(_clname);
}

int QSettingItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
