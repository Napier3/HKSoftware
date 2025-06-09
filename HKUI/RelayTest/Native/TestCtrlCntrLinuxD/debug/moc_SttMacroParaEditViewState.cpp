/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewState.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/SttMacroParaEditViewState.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewState.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewState[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,
      46,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   27,   27,   27, 0x09,
      98,   27,   27,   27, 0x09,
     117,   27,   27,   27, 0x09,
     137,   27,   27,   27, 0x09,
     154,   27,   27,   27, 0x09,
     175,   27,   27,   27, 0x09,
     196,   27,   27,   27, 0x09,
     215,   27,   27,   27, 0x09,
     239,  232,   27,   27, 0x09,
     268,   27,   27,   27, 0x09,
     285,   27,   27,   27, 0x09,
     303,   27,   27,   27, 0x09,
     319,   27,   27,   27, 0x09,
     339,   27,   27,   27, 0x09,
     356,   27,   27,   27, 0x09,
     386,   27,   27,   27, 0x09,
     405,   27,   27,   27, 0x09,
     434,   27,   27,   27, 0x09,
     467,   27,   27,   27, 0x09,
     489,   27,   27,   27, 0x09,
     518,   27,   27,   27, 0x09,
     544,   27,   27,   27, 0x09,
     568,   27,   27,   27, 0x09,
     595,  590,   27,   27, 0x09,
     641,  630,   27,   27, 0x09,
     675,   27,   27,   27, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewState[] = {
    "QSttMacroParaEditViewState\0\0"
    "sig_updataParas()\0sig_DataOfChannelChanged()\0"
    "slot_UpdateVecterViews()\0slot_updateParas()\0"
    "slot_PreviosState()\0slot_NextState()\0"
    "slot_InsertStateBF()\0slot_InsertStateAF()\0"
    "slot_DeleteState()\0slot_EditState()\0"
    "nIndex\0slot_StatesIndexChanged(int)\0"
    "slot_BinarySet()\0slot_CommonPara()\0"
    "slot_Estimate()\0slot_SettingValue()\0"
    "slot_ShortClac()\0slot_DiffCurrCalcBtnClicked()\0"
    "slot_GradientSet()\0slot_chb_DcStateChanged(int)\0"
    "slot_chb_DcPlusStateChanged(int)\0"
    "slot_lne_TaoChanged()\0"
    "slot_DcCoffsetStateChanged()\0"
    "slot_SwitchStateChanged()\0"
    "slot_GooseDataChanged()\0slot_FT3DataChanged()\0"
    "para\0slot_ShortCalcuOk(ShortCalcuPara&)\0"
    "nCurrIndex\0slot_currentChangedTabWidget(int)\0"
    "slot_UpdateToolButtons()\0"
};

void QSttMacroParaEditViewState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewState *_t = static_cast<QSttMacroParaEditViewState *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        case 1: _t->sig_DataOfChannelChanged(); break;
        case 2: _t->slot_UpdateVecterViews(); break;
        case 3: _t->slot_updateParas(); break;
        case 4: _t->slot_PreviosState(); break;
        case 5: _t->slot_NextState(); break;
        case 6: _t->slot_InsertStateBF(); break;
        case 7: _t->slot_InsertStateAF(); break;
        case 8: _t->slot_DeleteState(); break;
        case 9: _t->slot_EditState(); break;
        case 10: _t->slot_StatesIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_BinarySet(); break;
        case 12: _t->slot_CommonPara(); break;
        case 13: _t->slot_Estimate(); break;
        case 14: _t->slot_SettingValue(); break;
        case 15: _t->slot_ShortClac(); break;
        case 16: _t->slot_DiffCurrCalcBtnClicked(); break;
        case 17: _t->slot_GradientSet(); break;
        case 18: _t->slot_chb_DcStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slot_chb_DcPlusStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->slot_lne_TaoChanged(); break;
        case 21: _t->slot_DcCoffsetStateChanged(); break;
        case 22: _t->slot_SwitchStateChanged(); break;
        case 23: _t->slot_GooseDataChanged(); break;
        case 24: _t->slot_FT3DataChanged(); break;
        case 25: _t->slot_ShortCalcuOk((*reinterpret_cast< ShortCalcuPara(*)>(_a[1]))); break;
        case 26: _t->slot_currentChangedTabWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_UpdateToolButtons(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewState::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewState::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewState,
      qt_meta_data_QSttMacroParaEditViewState, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewState::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewState::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewState))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewState*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewState::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttMacroParaEditViewState::sig_DataOfChannelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
