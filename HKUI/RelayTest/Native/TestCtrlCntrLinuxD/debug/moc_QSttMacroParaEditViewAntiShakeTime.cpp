/****************************************************************************
** Meta object code from reading C++ file 'QSttMacroParaEditViewAntiShakeTime.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttMacroParaEditViewAntiShakeTime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewAntiShakeTime[] = {

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
      36,   35,   35,   35, 0x0a,
      55,   35,   35,   35, 0x0a,
      84,   77,   35,   35, 0x0a,
     112,   77,   35,   35, 0x0a,
     136,   77,   35,   35, 0x0a,
     157,   77,   35,   35, 0x0a,
     180,   35,   35,   35, 0x0a,
     205,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewAntiShakeTime[] = {
    "QSttMacroParaEditViewAntiShakeTime\0\0"
    "slot_AddTestItem()\0slot_DeleteTestItem()\0"
    "nIndex\0slot_CmbIntervalSelect(int)\0"
    "slot_CmbTestObject(int)\0slot_CmbBoutSet(int)\0"
    "slot_CmbInitState(int)\0slot_EditAntiShakeTime()\0"
    "slot_EditSOEResolution()\0"
};

void QSttMacroParaEditViewAntiShakeTime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewAntiShakeTime *_t = static_cast<QSttMacroParaEditViewAntiShakeTime *>(_o);
        switch (_id) {
        case 0: _t->slot_AddTestItem(); break;
        case 1: _t->slot_DeleteTestItem(); break;
        case 2: _t->slot_CmbIntervalSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_CmbTestObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_CmbBoutSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_CmbInitState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_EditAntiShakeTime(); break;
        case 7: _t->slot_EditSOEResolution(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewAntiShakeTime::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewAntiShakeTime::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewAntiShakeTime,
      qt_meta_data_QSttMacroParaEditViewAntiShakeTime, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewAntiShakeTime::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewAntiShakeTime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewAntiShakeTime::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewAntiShakeTime))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewAntiShakeTime*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewAntiShakeTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
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
