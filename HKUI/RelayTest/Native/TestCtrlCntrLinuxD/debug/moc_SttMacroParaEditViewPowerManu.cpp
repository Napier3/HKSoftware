/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewPowerManu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/PowerManu/SttMacroParaEditViewPowerManu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewPowerManu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewPowerManu[] = {

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
      32,   31,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   31,   31,   31, 0x09,
      81,   31,   31,   31, 0x09,
     111,   31,   31,   31, 0x09,
     143,   31,   31,   31, 0x09,
     186,   31,   31,   31, 0x09,
     227,   31,   31,   31, 0x09,
     268,   31,   31,   31, 0x09,
     310,   31,   31,   31, 0x09,
     345,  339,   31,   31, 0x09,
     398,  339,   31,   31, 0x09,
     445,  339,   31,   31, 0x09,
     495,   31,   31,   31, 0x09,
     525,   31,   31,   31, 0x09,
     555,   31,   31,   31, 0x09,
     585,   31,   31,   31, 0x09,
     615,   31,   31,   31, 0x09,
     648,   31,   31,   31, 0x09,
     682,   31,   31,   31, 0x09,
     717,   31,   31,   31, 0x09,
     750,   31,   31,   31, 0x09,
     785,   31,   31,   31, 0x09,
     839,  804,   31,   31, 0x09,
     894,   31,   31,   31, 0x09,
     918,   31,   31,   31, 0x09,
     940,   31,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewPowerManu[] = {
    "QSttMacroParaEditViewPowerManu\0\0"
    "sig_updataParas()\0slot_Lock_PushButton_clicked()\0"
    "slot_Add_PushButton_clicked()\0"
    "slot_Minus_PushButton_clicked()\0"
    "slot_StartValue_LineEdit_editingFinished()\0"
    "slot_EndValue_LineEdit_editingFinished()\0"
    "slot_StepTime_LineEdit_editingFinished()\0"
    "slot_StepValue_LineEdit_editingFinished()\0"
    "slot_Auto_CheckBox_clicked()\0index\0"
    "slot_ChGradientTypeComboBox_currentIndexChanged(int)\0"
    "slot_ChSelectComboBox_currentIndexChanged(int)\0"
    "slot_ChangedTypeComboBox_currentIndexChanged(int)\0"
    "slot_Bout_CheckBox1_clicked()\0"
    "slot_Bout_CheckBox2_clicked()\0"
    "slot_Bout_CheckBox3_clicked()\0"
    "slot_Bout_CheckBox4_clicked()\0"
    "slot_StepTime_LineEdit_Changed()\0"
    "slot_StepValue_LineEdit_Changed()\0"
    "slot_StartValue_LineEdit_Changed()\0"
    "slot_EndValue_LineEdit_Changed()\0"
    "slot_BinarySetPushButton_clicked()\0"
    "slot_updateParas()\0"
    "str,fstep,valueFlag,AddOrMinus,bDC\0"
    "slot_ChannelTableItemValue(QString,float,int,int,bool)\0"
    "slot_GooseDataChanged()\0slot_FT3DataChanged()\0"
    "slot_EstimatePushButton_clicked()\0"
};

void QSttMacroParaEditViewPowerManu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewPowerManu *_t = static_cast<QSttMacroParaEditViewPowerManu *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        case 1: _t->slot_Lock_PushButton_clicked(); break;
        case 2: _t->slot_Add_PushButton_clicked(); break;
        case 3: _t->slot_Minus_PushButton_clicked(); break;
        case 4: _t->slot_StartValue_LineEdit_editingFinished(); break;
        case 5: _t->slot_EndValue_LineEdit_editingFinished(); break;
        case 6: _t->slot_StepTime_LineEdit_editingFinished(); break;
        case 7: _t->slot_StepValue_LineEdit_editingFinished(); break;
        case 8: _t->slot_Auto_CheckBox_clicked(); break;
        case 9: _t->slot_ChGradientTypeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_ChSelectComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_ChangedTypeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_Bout_CheckBox1_clicked(); break;
        case 13: _t->slot_Bout_CheckBox2_clicked(); break;
        case 14: _t->slot_Bout_CheckBox3_clicked(); break;
        case 15: _t->slot_Bout_CheckBox4_clicked(); break;
        case 16: _t->slot_StepTime_LineEdit_Changed(); break;
        case 17: _t->slot_StepValue_LineEdit_Changed(); break;
        case 18: _t->slot_StartValue_LineEdit_Changed(); break;
        case 19: _t->slot_EndValue_LineEdit_Changed(); break;
        case 20: _t->slot_BinarySetPushButton_clicked(); break;
        case 21: _t->slot_updateParas(); break;
        case 22: _t->slot_ChannelTableItemValue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 23: _t->slot_GooseDataChanged(); break;
        case 24: _t->slot_FT3DataChanged(); break;
        case 25: _t->slot_EstimatePushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewPowerManu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewPowerManu::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewPowerManu,
      qt_meta_data_QSttMacroParaEditViewPowerManu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewPowerManu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewPowerManu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewPowerManu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewPowerManu))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewPowerManu*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewPowerManu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
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
void QSttMacroParaEditViewPowerManu::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
