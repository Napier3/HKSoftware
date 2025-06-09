/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewHarm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Harm/SttMacroParaEditViewHarm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewHarm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewHarm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x05,
      45,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   26,   26,   26, 0x09,
      90,   26,   26,   26, 0x09,
     116,   26,   26,   26, 0x09,
     135,   26,   26,   26, 0x09,
     159,   26,   26,   26, 0x09,
     181,   26,   26,   26, 0x09,
     207,   26,   26,   26, 0x09,
     235,  224,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewHarm[] = {
    "QSttMacroParaEditViewHarm\0\0sig_updataParas()\0"
    "sig_SwitchParaOKClicked()\0slot_updateParas()\0"
    "slot_SwitchStateChanged()\0slot_LockChanged()\0"
    "slot_GooseDataChanged()\0slot_FT3DataChanged()\0"
    "slot_pbnAutoClicked(bool)\0slot_SetToZero()\0"
    "nCurrIndex\0slot_currentChangedTabWidget(int)\0"
};

void QSttMacroParaEditViewHarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewHarm *_t = static_cast<QSttMacroParaEditViewHarm *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        case 1: _t->sig_SwitchParaOKClicked(); break;
        case 2: _t->slot_updateParas(); break;
        case 3: _t->slot_SwitchStateChanged(); break;
        case 4: _t->slot_LockChanged(); break;
        case 5: _t->slot_GooseDataChanged(); break;
        case 6: _t->slot_FT3DataChanged(); break;
        case 7: _t->slot_pbnAutoClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_SetToZero(); break;
        case 9: _t->slot_currentChangedTabWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewHarm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewHarm::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewHarm,
      qt_meta_data_QSttMacroParaEditViewHarm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewHarm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewHarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewHarm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewHarm))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewHarm*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewHarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewHarm::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttMacroParaEditViewHarm::sig_SwitchParaOKClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
