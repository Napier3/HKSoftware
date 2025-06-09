/****************************************************************************
** Meta object code from reading C++ file 'gradientchanneltable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/Gradient/gradientchanneltable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gradientchanneltable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GradientChannelTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   22,   21,   21, 0x09,
      64,   58,   21,   21, 0x09,
     102,   21,   21,   21, 0x09,
     128,   21,   21,   21, 0x09,
     155,   21,   21,   21, 0x09,
     189,  180,   21,   21, 0x09,
     214,  180,   21,   21, 0x09,
     239,  180,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_GradientChannelTable[] = {
    "GradientChannelTable\0\0row,col\0"
    "slot_OnCellChanged(int,int)\0pItem\0"
    "slot_OnItemClicked(QTableWidgetItem*)\0"
    "slot_ActIqualAmpClicked()\0"
    "slot_ActUEqualAmpClicked()\0"
    "slot_ActHzEqualClicked()\0strValue\0"
    "slot_UpdataVamp(QString)\0"
    "slot_UpdataIamp(QString)\0"
    "slot_UpdataHzamp(QString)\0"
};

void GradientChannelTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GradientChannelTable *_t = static_cast<GradientChannelTable *>(_o);
        switch (_id) {
        case 0: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_OnItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->slot_ActIqualAmpClicked(); break;
        case 3: _t->slot_ActUEqualAmpClicked(); break;
        case 4: _t->slot_ActHzEqualClicked(); break;
        case 5: _t->slot_UpdataVamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slot_UpdataIamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_UpdataHzamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GradientChannelTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GradientChannelTable::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_GradientChannelTable,
      qt_meta_data_GradientChannelTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GradientChannelTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GradientChannelTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GradientChannelTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GradientChannelTable))
        return static_cast<void*>(const_cast< GradientChannelTable*>(this));
    if (!strcmp(_clname, "CCommonCtrlInterface"))
        return static_cast< CCommonCtrlInterface*>(const_cast< GradientChannelTable*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int GradientChannelTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
