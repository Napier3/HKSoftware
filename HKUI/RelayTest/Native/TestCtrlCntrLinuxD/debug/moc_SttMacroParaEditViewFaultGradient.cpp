/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewFaultGradient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/FaultGradient/SttMacroParaEditViewFaultGradient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewFaultGradient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewFaultGradient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      60,   36,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
     119,  112,   35,   35, 0x0a,
     158,  112,   35,   35, 0x0a,
     196,  112,   35,   35, 0x0a,
     236,  112,   35,   35, 0x0a,
     280,  271,   35,   35, 0x0a,
     320,  271,   35,   35, 0x0a,
     371,   35,   35,   35, 0x0a,
     396,   35,   35,   35, 0x0a,
     421,   35,   35,   35, 0x0a,
     447,   35,   35,   35, 0x0a,
     468,   35,   35,   35, 0x0a,
     491,   35,   35,   35, 0x0a,
     512,   35,   35,   35, 0x0a,
     538,   35,   35,   35, 0x0a,
     562,   35,   35,   35, 0x0a,
     586,   35,   35,   35, 0x0a,
     608,   35,   35,   35, 0x0a,
     641,   35,   35,   35, 0x0a,
     672,   35,   35,   35, 0x0a,
     702,   35,   35,   35, 0x0a,
     732,   35,   35,   35, 0x0a,
     791,  765,   35,   35, 0x0a,
     845,   35,   35,   35, 0x0a,
     869,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewFaultGradient[] = {
    "QSttMacroParaEditViewFaultGradient\0\0"
    "type,strTitle,fdown,fup\0"
    "sig_YRangeChanged(changed_type,QString,float,float)\0"
    "nIndex\0on_ReturnType_currentIndexChanged(int)\0"
    "on_FaultMode_currentIndexChanged(int)\0"
    "on_ChangeValue_currentIndexChanged(int)\0"
    "on_VMType_currentIndexChanged(int)\0"
    "pCurrBtn\0on_GrpBin_ButtonClick(QAbstractButton*)\0"
    "on_GrpOutNormalError_ButtonClick(QAbstractButton*)\0"
    "on_AndStateChanged(bool)\0"
    "on_MoreOut_ButtonClick()\0"
    "on_Estimate_ButtonClick()\0"
    "on_EditInit_Finish()\0on_EditFinish_Finish()\0"
    "on_EditStep_Finish()\0on_EditFaultTime_Finish()\0"
    "on_EditShortVm_Finish()\0on_EditShortVa_Finish()\0"
    "on_EditAngle_Finish()\0"
    "on_EditTimeBeforeChange_Finish()\0"
    "on_EditTimeBeforeFail_Finish()\0"
    "on_EditFaultBeforeVm_Finish()\0"
    "on_EditFaultBeforeVa_Finish()\0"
    "on_EditFaultBeforeAngle_Finish()\0"
    "ftime,fv,fstart,fend,down\0"
    "GetStateMonitorYRange(float,float,float,float,float&)\0"
    "SetStateMonitorYRange()\0ConvertChannelAndType()\0"
};

void QSttMacroParaEditViewFaultGradient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewFaultGradient *_t = static_cast<QSttMacroParaEditViewFaultGradient *>(_o);
        switch (_id) {
        case 0: _t->sig_YRangeChanged((*reinterpret_cast< changed_type(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->on_ReturnType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_FaultMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_ChangeValue_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_VMType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_GrpBin_ButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 6: _t->on_GrpOutNormalError_ButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 7: _t->on_AndStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_MoreOut_ButtonClick(); break;
        case 9: _t->on_Estimate_ButtonClick(); break;
        case 10: _t->on_EditInit_Finish(); break;
        case 11: _t->on_EditFinish_Finish(); break;
        case 12: _t->on_EditStep_Finish(); break;
        case 13: _t->on_EditFaultTime_Finish(); break;
        case 14: _t->on_EditShortVm_Finish(); break;
        case 15: _t->on_EditShortVa_Finish(); break;
        case 16: _t->on_EditAngle_Finish(); break;
        case 17: _t->on_EditTimeBeforeChange_Finish(); break;
        case 18: _t->on_EditTimeBeforeFail_Finish(); break;
        case 19: _t->on_EditFaultBeforeVm_Finish(); break;
        case 20: _t->on_EditFaultBeforeVa_Finish(); break;
        case 21: _t->on_EditFaultBeforeAngle_Finish(); break;
        case 22: _t->GetStateMonitorYRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 23: _t->SetStateMonitorYRange(); break;
        case 24: _t->ConvertChannelAndType(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewFaultGradient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewFaultGradient::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewFaultGradient,
      qt_meta_data_QSttMacroParaEditViewFaultGradient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewFaultGradient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewFaultGradient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewFaultGradient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewFaultGradient))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewFaultGradient*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMacroParaEditViewFaultGradient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewFaultGradient::sig_YRangeChanged(changed_type _t1, QString _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
