/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewSwing.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Swing/SttMacroParaEditViewSwing.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewSwing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewSwing[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   28,   27,   27, 0x08,
      69,   28,   27,   27, 0x08,
     101,   28,   27,   27, 0x08,
     142,   27,   27,   27, 0x08,
     171,   27,   27,   27, 0x08,
     199,   27,   27,   27, 0x08,
     216,   27,   27,   27, 0x08,
     255,   27,   27,   27, 0x08,
     292,   27,   27,   27, 0x08,
     330,   27,   27,   27, 0x08,
     368,   27,   27,   27, 0x08,
     404,   27,   27,   27, 0x08,
     434,   27,   27,   27, 0x08,
     467,   27,   27,   27, 0x08,
     504,   27,   27,   27, 0x08,
     541,   27,   27,   27, 0x08,
     574,   27,   27,   27, 0x08,
     612,  606,   27,   27, 0x08,
     652,  606,   27,   27, 0x08,
     695,  606,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewSwing[] = {
    "QSttMacroParaEditViewSwing\0\0state\0"
    "on_Refault_Check_StateChanged(int)\0"
    "on_Dzdt_Check_StateChanged(int)\0"
    "on_Reciprocating_Check_StateChanged(int)\0"
    "on_m_btnResultEval_clicked()\0"
    "on_m_btnTestParas_clicked()\0"
    "on_DataChanged()\0"
    "on_m_editPAngleStart_editingFinished()\0"
    "on_m_editPAngleEnd_editingFinished()\0"
    "on_m_editSwingCycle_editingFinished()\0"
    "on_m_editSwingCount_editingFinished()\0"
    "on_m_editEmEnRate_editingFinished()\0"
    "on_m_editZ1_editingFinished()\0"
    "on_m_editISet1_editingFinished()\0"
    "on_m_editFaultTime_editingFinished()\0"
    "on_m_editAmplitude_editingFinished()\0"
    "on_m_editPhase_editingFinished()\0"
    "on_m_editDzdt_editingFinished()\0index\0"
    "on_m_cbbK0Mode_currentIndexChanged(int)\0"
    "on_m_cbbFaultType_currentIndexChanged(int)\0"
    "on_m_cbbTripPoint_currentIndexChanged(int)\0"
};

void QSttMacroParaEditViewSwing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewSwing *_t = static_cast<QSttMacroParaEditViewSwing *>(_o);
        switch (_id) {
        case 0: _t->on_Refault_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_Dzdt_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_Reciprocating_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_btnResultEval_clicked(); break;
        case 4: _t->on_m_btnTestParas_clicked(); break;
        case 5: _t->on_DataChanged(); break;
        case 6: _t->on_m_editPAngleStart_editingFinished(); break;
        case 7: _t->on_m_editPAngleEnd_editingFinished(); break;
        case 8: _t->on_m_editSwingCycle_editingFinished(); break;
        case 9: _t->on_m_editSwingCount_editingFinished(); break;
        case 10: _t->on_m_editEmEnRate_editingFinished(); break;
        case 11: _t->on_m_editZ1_editingFinished(); break;
        case 12: _t->on_m_editISet1_editingFinished(); break;
        case 13: _t->on_m_editFaultTime_editingFinished(); break;
        case 14: _t->on_m_editAmplitude_editingFinished(); break;
        case 15: _t->on_m_editPhase_editingFinished(); break;
        case 16: _t->on_m_editDzdt_editingFinished(); break;
        case 17: _t->on_m_cbbK0Mode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_m_cbbFaultType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_m_cbbTripPoint_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewSwing::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewSwing::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewSwing,
      qt_meta_data_QSttMacroParaEditViewSwing, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewSwing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewSwing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewSwing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewSwing))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewSwing*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewSwing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
