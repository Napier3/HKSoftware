/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewIntelligentTerminal.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IntelligentTerminal/SttMacroParaEditViewIntelligentTerminal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewIntelligentTerminal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewIntelligentTerminal[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   41,   41,   41, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   41,   41,   41, 0x09,
     115,   95,   41,   41, 0x09,
     140,   41,   41,   41, 0x09,
     159,   41,   41,   41, 0x09,
     183,   41,   41,   41, 0x09,
     215,  205,   41,   41, 0x09,
     238,   41,   41,   41, 0x09,
     275,  256,   41,   41, 0x09,
     310,  303,   41,   41, 0x09,
     335,  303,   41,   41, 0x09,
     372,  361,   41,   41, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewIntelligentTerminal[] = {
    "QSttMacroParaEditViewIntelligentTerminal\0"
    "\0sig_updataParas()\0"
    "slot_BinarySetPushButton_clicked()\0"
    "nbout,bStateChanged\0slot_setBinOut(int,bool)\0"
    "slot_updateParas()\0slot_GooseDataChanged()\0"
    "slot_FT3DataChanged()\0nRowIndex\0"
    "slot_GoutRowIndex(int)\0slot_RevertData()\0"
    "nRowIndex,fActTime\0slot_GinRowIndex(int,float)\0"
    "nindex\0slot_TabPageChanged(int)\0"
    "slot_Tab_cellClicked(int)\0pEventInfo\0"
    "slot_UpdateEventMsgTime(CEventResult*)\0"
};

void QSttMacroParaEditViewIntelligentTerminal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewIntelligentTerminal *_t = static_cast<QSttMacroParaEditViewIntelligentTerminal *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        case 1: _t->slot_BinarySetPushButton_clicked(); break;
        case 2: _t->slot_setBinOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->slot_updateParas(); break;
        case 4: _t->slot_GooseDataChanged(); break;
        case 5: _t->slot_FT3DataChanged(); break;
        case 6: _t->slot_GoutRowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_RevertData(); break;
        case 8: _t->slot_GinRowIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 9: _t->slot_TabPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_Tab_cellClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_UpdateEventMsgTime((*reinterpret_cast< CEventResult*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewIntelligentTerminal::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewIntelligentTerminal::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewIntelligentTerminal,
      qt_meta_data_QSttMacroParaEditViewIntelligentTerminal, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewIntelligentTerminal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewIntelligentTerminal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewIntelligentTerminal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewIntelligentTerminal))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewIntelligentTerminal*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewIntelligentTerminal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewIntelligentTerminal::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
