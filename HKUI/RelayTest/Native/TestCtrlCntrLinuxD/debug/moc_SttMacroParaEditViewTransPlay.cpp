/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewTransPlay.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/TransPlay/SttMacroParaEditViewTransPlay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewTransPlay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewTransPlay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x05,
      63,   58,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
     117,   95,   31,   31, 0x09,
     147,   31,   31,   31, 0x09,
     175,   31,   31,   31, 0x09,
     188,   58,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewTransPlay[] = {
    "QSttMacroParaEditViewTransPlay\0\0"
    "sig_UpdateDrawWaveGraph()\0bRet\0"
    "sig_UpdateOpenComtradeFile(int)\0"
    "nModuleIndex,nChIndex\0"
    "slot_ModuleChChanged(int,int)\0"
    "slot_ModuleChRangeChanged()\0slot_Timer()\0"
    "slot_UpdateOpenComtradeFile(int)\0"
};

void QSttMacroParaEditViewTransPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewTransPlay *_t = static_cast<QSttMacroParaEditViewTransPlay *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateDrawWaveGraph(); break;
        case 1: _t->sig_UpdateOpenComtradeFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_ModuleChChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_ModuleChRangeChanged(); break;
        case 4: _t->slot_Timer(); break;
        case 5: _t->slot_UpdateOpenComtradeFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewTransPlay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewTransPlay::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewTransPlay,
      qt_meta_data_QSttMacroParaEditViewTransPlay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewTransPlay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewTransPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewTransPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewTransPlay))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewTransPlay*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewTransPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewTransPlay::sig_UpdateDrawWaveGraph()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttMacroParaEditViewTransPlay::sig_UpdateOpenComtradeFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
