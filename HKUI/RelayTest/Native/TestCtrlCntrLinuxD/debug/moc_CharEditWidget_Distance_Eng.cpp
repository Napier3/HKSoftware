/****************************************************************************
** Meta object code from reading C++ file 'CharEditWidget_Distance_Eng.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/InternationalModeUI/CharEditWidget_Distance_Eng.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharEditWidget_Distance_Eng.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditGrid_Param_Eng[] = {

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

static const char qt_meta_stringdata_QCharEditGrid_Param_Eng[] = {
    "QCharEditGrid_Param_Eng\0"
};

void QCharEditGrid_Param_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QCharEditGrid_Param_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditGrid_Param_Eng::staticMetaObject = {
    { &QCharEditGrid_Param::staticMetaObject, qt_meta_stringdata_QCharEditGrid_Param_Eng,
      qt_meta_data_QCharEditGrid_Param_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditGrid_Param_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditGrid_Param_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditGrid_Param_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditGrid_Param_Eng))
        return static_cast<void*>(const_cast< QCharEditGrid_Param_Eng*>(this));
    return QCharEditGrid_Param::qt_metacast(_clname);
}

int QCharEditGrid_Param_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCharEditGrid_Param::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QCharEditWidget_DistanceSearch_Eng[] = {

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
      38,   36,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   74,   35,   35, 0x08,
     112,   35,   35,   35, 0x08,
     135,   35,   35,   35, 0x08,
     161,   35,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_DistanceSearch_Eng[] = {
    "QCharEditWidget_DistanceSearch_Eng\0\0"
    ",\0sig_CharChanged(CExBaseObject*,int)\0"
    "pObj\0slot_ZkAddChar(CCharacteristic*)\0"
    "slot_ZkPbnAddClicked()\0slot_btnEditCharClicked()\0"
    "slot_ZkPbnDelClicked()\0"
};

void QCharEditWidget_DistanceSearch_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_DistanceSearch_Eng *_t = static_cast<QCharEditWidget_DistanceSearch_Eng *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_ZkAddChar((*reinterpret_cast< CCharacteristic*(*)>(_a[1]))); break;
        case 2: _t->slot_ZkPbnAddClicked(); break;
        case 3: _t->slot_btnEditCharClicked(); break;
        case 4: _t->slot_ZkPbnDelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_DistanceSearch_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_DistanceSearch_Eng::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_DistanceSearch_Eng,
      qt_meta_data_QCharEditWidget_DistanceSearch_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_DistanceSearch_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_DistanceSearch_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_DistanceSearch_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_DistanceSearch_Eng))
        return static_cast<void*>(const_cast< QCharEditWidget_DistanceSearch_Eng*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_DistanceSearch_Eng*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QCharEditWidget_DistanceSearch_Eng*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_DistanceSearch_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void QCharEditWidget_DistanceSearch_Eng::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
