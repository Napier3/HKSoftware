/****************************************************************************
** Meta object code from reading C++ file 'GradientGroupGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Gradient/GradientGroupGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GradientGroupGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGradientGroupGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   20,   19,   19, 0x09,
     114,   62,   19,   19, 0x09,
     155,   19,   19,   19, 0x09,
     179,   19,   19,   19, 0x09,
     206,   19,   19,   19, 0x09,
     229,   19,   19,   19, 0x09,
     256,   19,   19,   19, 0x09,
     279,   19,   19,   19, 0x09,
     302,   19,   19,   19, 0x09,
     325,   19,   19,   19, 0x09,
     351,   19,   19,   19, 0x09,
     375,   19,   19,   19, 0x09,
     402,   19,   19,   19, 0x09,
     426,   19,   19,   19, 0x09,
     450,   19,   19,   19, 0x09,
     474,   19,   19,   19, 0x09,
     496,   19,   19,   19, 0x09,
     518,   19,   19,   19, 0x09,
     552,  543,   19,   19, 0x09,
     577,  543,   19,   19, 0x09,
     602,  543,   19,   19, 0x09,
     625,  543,   19,   19, 0x09,
     648,   19,   19,   19, 0x09,
     664,  543,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QGradientGroupGrid[] = {
    "QGradientGroupGrid\0\0nRow,nCol\0"
    "slot_cellDoubleClicked(int,int)\0"
    "currentRow,currentColumn,previousRow,previousColumn\0"
    "slot_CurrentCellChanged(int,int,int,int)\0"
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
    "slot_UpdataZX(QString)\0slot_UpdataFX(QString)\0"
    "slot_UpdataLX()\0slot_UpdataHzamp(QString)\0"
};

void QGradientGroupGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QGradientGroupGrid *_t = static_cast<QGradientGroupGrid *>(_o);
        switch (_id) {
        case 0: _t->slot_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_CurrentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->slot_ActUAmpEDClicked(); break;
        case 3: _t->slot_ActPerUAmpEDClicked(); break;
        case 4: _t->slot_ActUZeroClicked(); break;
        case 5: _t->slot_ActUEqualAmpClicked(); break;
        case 6: _t->slot_ActIAmp1Clicked(); break;
        case 7: _t->slot_ActIAmp5Clicked(); break;
        case 8: _t->slot_ActIAmp0Clicked(); break;
        case 9: _t->slot_ActIqualAmpClicked(); break;
        case 10: _t->slot_ActIAmpEDClicked(); break;
        case 11: _t->slot_ActPerIAmpEDClicked(); break;
        case 12: _t->slot_ActPhasePClicked(); break;
        case 13: _t->slot_ActPhaseNClicked(); break;
        case 14: _t->slot_ActPhaseZClicked(); break;
        case 15: _t->slot_ActHz50Clicked(); break;
        case 16: _t->slot_ActHz60Clicked(); break;
        case 17: _t->slot_ActHzEqualClicked(); break;
        case 18: _t->slot_UpdataVamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->slot_UpdataIamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->slot_UpdataZX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->slot_UpdataFX((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->slot_UpdataLX(); break;
        case 23: _t->slot_UpdataHzamp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QGradientGroupGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QGradientGroupGrid::staticMetaObject = {
    { &QSettingGridBase::staticMetaObject, qt_meta_stringdata_QGradientGroupGrid,
      qt_meta_data_QGradientGroupGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGradientGroupGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGradientGroupGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGradientGroupGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGradientGroupGrid))
        return static_cast<void*>(const_cast< QGradientGroupGrid*>(this));
    return QSettingGridBase::qt_metacast(_clname);
}

int QGradientGroupGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSettingGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
