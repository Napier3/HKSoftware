/****************************************************************************
** Meta object code from reading C++ file 'channelpowertable.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/ChannelParaSet/channelpowertable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'channelpowertable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QChannelPowerTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      62,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     120,  112,   19,   19, 0x09,
     154,  148,   19,   19, 0x09,
     202,  198,   19,   19, 0x09,
     229,   19,   19,   19, 0x09,
     253,   19,   19,   19, 0x09,
     280,   19,   19,   19, 0x09,
     303,   19,   19,   19, 0x09,
     330,   19,   19,   19, 0x09,
     353,   19,   19,   19, 0x09,
     376,   19,   19,   19, 0x09,
     399,   19,   19,   19, 0x09,
     425,   19,   19,   19, 0x09,
     449,   19,   19,   19, 0x09,
     476,   19,   19,   19, 0x09,
     500,   19,   19,   19, 0x09,
     524,   19,   19,   19, 0x09,
     548,   19,   19,   19, 0x09,
     570,   19,   19,   19, 0x09,
     592,   19,   19,   19, 0x09,
     626,  617,   19,   19, 0x09,
     651,  617,   19,   19, 0x09,
     676,  617,   19,   19, 0x09,
     702,  617,   19,   19, 0x09,
     725,  617,   19,   19, 0x09,
     748,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QChannelPowerTable[] = {
    "QChannelPowerTable\0\0"
    "moudleType,channelNum,valueFlag,datavalue\0"
    "sig_ChannelValueChanged(MOUDLEType,int,int,float)\0"
    "row,col\0slot_OnCellChanged(int,int)\0"
    "pItem\0slot_OnItemDoubleClicked(QTableWidgetItem*)\0"
    "pos\0slot_TableShowMent(QPoint)\0"
    "slot_ActUAmpEDClicked()\0"
    "slot_ActPerUAmpEDClicked()\0"
    "slot_ActUZeroClicked()\0"
    "slot_ActUEqualAmpClicked()\0"
    "slot_ActIAmp1Clicked()\0slot_ActIAmp5Clicked()\0"
    "slot_ActIAmp0Clicked()\0slot_ActIqualAmpClicked()\0"
    "slot_ActIAmpEDClicked()\0"
    "slot_ActPerIAmpEDClicked()\0"
    "slot_ActPhasePClicked()\0slot_ActPhaseNClicked()\0"
    "slot_ActPhaseZClicked()\0slot_ActHz50Clicked()\0"
    "slot_ActHz60Clicked()\0slot_ActHzEqualClicked()\0"
    "strValue\0slot_UpdataVamp(QString)\0"
    "slot_UpdataIamp(QString)\0"
    "slot_UpdataHzamp(QString)\0"
    "slot_UpdataZX(QString)\0slot_UpdataFX(QString)\0"
    "slot_UpdataLX()\0"
};

void QChannelPowerTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QChannelPowerTable *_t = static_cast<QChannelPowerTable *>(_o);
        switch (_id) {
        case 0: _t->sig_ChannelValueChanged((*reinterpret_cast< MOUDLEType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_OnItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->slot_TableShowMent((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->slot_ActUAmpEDClicked(); break;
        case 5: _t->slot_ActPerUAmpEDClicked(); break;
        case 6: _t->slot_ActUZeroClicked(); break;
        case 7: _t->slot_ActUEqualAmpClicked(); break;
        case 8: _t->slot_ActIAmp1Clicked(); break;
        case 9: _t->slot_ActIAmp5Clicked(); break;
        case 10: _t->slot_ActIAmp0Clicked(); break;
        case 11: _t->slot_ActIqualAmpClicked(); break;
        case 12: _t->slot_ActIAmpEDClicked(); break;
        case 13: _t->slot_ActPerIAmpEDClicked(); break;
        case 14: _t->slot_ActPhasePClicked(); break;
        case 15: _t->slot_ActPhaseNClicked(); break;
        case 16: _t->slot_ActPhaseZClicked(); break;
        case 17: _t->slot_ActHz50Clicked(); break;
        case 18: _t->slot_ActHz60Clicked(); break;
        case 19: _t->slot_ActHzEqualClicked(); break;
        case 20: _t->slot_UpdataVamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->slot_UpdataIamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->slot_UpdataHzamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->slot_UpdataZX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->slot_UpdataFX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->slot_UpdataLX(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QChannelPowerTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QChannelPowerTable::staticMetaObject = {
    { &QScrollTableWidget::staticMetaObject, qt_meta_stringdata_QChannelPowerTable,
      qt_meta_data_QChannelPowerTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QChannelPowerTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QChannelPowerTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QChannelPowerTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QChannelPowerTable))
        return static_cast<void*>(const_cast< QChannelPowerTable*>(this));
    if (!strcmp(_clname, "CCommonCtrlInterface"))
        return static_cast< CCommonCtrlInterface*>(const_cast< QChannelPowerTable*>(this));
    return QScrollTableWidget::qt_metacast(_clname);
}

int QChannelPowerTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void QChannelPowerTable::sig_ChannelValueChanged(MOUDLEType _t1, int _t2, int _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
