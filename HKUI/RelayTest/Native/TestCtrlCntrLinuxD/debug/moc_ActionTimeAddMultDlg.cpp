/****************************************************************************
** Meta object code from reading C++ file 'ActionTimeAddMultDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/ActTime/ActionTimeAddMultDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActionTimeAddMultDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QActionTimeAddMultDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      44,   22,   22,   22, 0x08,
      75,   69,   22,   22, 0x08,
     105,   69,   22,   22, 0x08,
     135,   69,   22,   22, 0x08,
     173,   69,   22,   22, 0x08,
     203,   69,   22,   22, 0x08,
     233,   22,   22,   22, 0x08,
     261,   22,   22,   22, 0x08,
     300,   22,   22,   22, 0x08,
     340,   22,   22,   22, 0x08,
     378,   22,   22,   22, 0x08,
     411,   22,   22,   22, 0x08,
     444,   22,   22,   22, 0x08,
     485,   22,   22,   22, 0x08,
     518,   22,   22,   22, 0x08,
     551,   22,   22,   22, 0x08,
     585,   22,   22,   22, 0x08,
     622,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QActionTimeAddMultDlg[] = {
    "QActionTimeAddMultDlg\0\0on_m_btnOk_clicked()\0"
    "on_m_btnCancel_clicked()\0state\0"
    "on_LN_Check_StateChanged(int)\0"
    "on_LL_Check_StateChanged(int)\0"
    "on_ThreePhase_Check_StateChanged(int)\0"
    "on_I0_Check_StateChanged(int)\0"
    "on_I2_Check_StateChanged(int)\0"
    "on_TestCheck_StateChanged()\0"
    "on_m_editSettingTime_editingFinished()\0"
    "on_m_editFaultCurrent_editingFinished()\0"
    "on_m_editFaultAngle_editingFinished()\0"
    "on_m_editLNVol_editingFinished()\0"
    "on_m_editLLVol_editingFinished()\0"
    "on_m_editThreePhaseVol_editingFinished()\0"
    "on_m_editI0Vol_editingFinished()\0"
    "on_m_editI2Vol_editingFinished()\0"
    "on_m_editRelErr_editingFinished()\0"
    "on_m_editAbsErrPos_editingFinished()\0"
    "on_m_editAbsErrNeg_editingFinished()\0"
};

void QActionTimeAddMultDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QActionTimeAddMultDlg *_t = static_cast<QActionTimeAddMultDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOk_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->on_LN_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_LL_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_ThreePhase_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_I0_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_I2_Check_StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_TestCheck_StateChanged(); break;
        case 8: _t->on_m_editSettingTime_editingFinished(); break;
        case 9: _t->on_m_editFaultCurrent_editingFinished(); break;
        case 10: _t->on_m_editFaultAngle_editingFinished(); break;
        case 11: _t->on_m_editLNVol_editingFinished(); break;
        case 12: _t->on_m_editLLVol_editingFinished(); break;
        case 13: _t->on_m_editThreePhaseVol_editingFinished(); break;
        case 14: _t->on_m_editI0Vol_editingFinished(); break;
        case 15: _t->on_m_editI2Vol_editingFinished(); break;
        case 16: _t->on_m_editRelErr_editingFinished(); break;
        case 17: _t->on_m_editAbsErrPos_editingFinished(); break;
        case 18: _t->on_m_editAbsErrNeg_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QActionTimeAddMultDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QActionTimeAddMultDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QActionTimeAddMultDlg,
      qt_meta_data_QActionTimeAddMultDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QActionTimeAddMultDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QActionTimeAddMultDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QActionTimeAddMultDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QActionTimeAddMultDlg))
        return static_cast<void*>(const_cast< QActionTimeAddMultDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QActionTimeAddMultDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
