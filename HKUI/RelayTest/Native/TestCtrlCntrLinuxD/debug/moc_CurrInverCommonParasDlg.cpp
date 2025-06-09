/****************************************************************************
** Meta object code from reading C++ file 'CurrInverCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/CurrInverseTime/CurrInverCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CurrInverCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCurrInverseCommonParasDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   28,   27,   27, 0x08,
      74,   28,   27,   27, 0x08,
     102,   27,   27,   27, 0x08,
     142,   27,   27,   27, 0x08,
     179,   27,   27,   27, 0x08,
     216,   27,   27,   27, 0x08,
     247,   27,   27,   27, 0x08,
     277,   27,   27,   27, 0x08,
     307,   27,   27,   27, 0x08,
     337,   27,   27,   27, 0x08,
     374,   27,   27,   27, 0x08,
     395,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCurrInverseCommonParasDlg[] = {
    "QCurrInverseCommonParasDlg\0\0index\0"
    "slot_cmb_Value_currentIndexChanged(int)\0"
    "slot_cmb_CTPos_Changed(int)\0"
    "slot_lne_PreFaultTime_editingFinished()\0"
    "slot_lne_FaultVolt_editingFinished()\0"
    "slot_lne_FaultCurr_editingFinished()\0"
    "slot_lne_Ang_editingFinished()\0"
    "slot_lne_Hz_editingFinished()\0"
    "slot_lne_In_editingFinished()\0"
    "slot_lne_Ip_editingFinished()\0"
    "slot_lne_FaultTime_editingFinished()\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QCurrInverseCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCurrInverseCommonParasDlg *_t = static_cast<QCurrInverseCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_cmb_Value_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_cmb_CTPos_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_lne_PreFaultTime_editingFinished(); break;
        case 3: _t->slot_lne_FaultVolt_editingFinished(); break;
        case 4: _t->slot_lne_FaultCurr_editingFinished(); break;
        case 5: _t->slot_lne_Ang_editingFinished(); break;
        case 6: _t->slot_lne_Hz_editingFinished(); break;
        case 7: _t->slot_lne_In_editingFinished(); break;
        case 8: _t->slot_lne_Ip_editingFinished(); break;
        case 9: _t->slot_lne_FaultTime_editingFinished(); break;
        case 10: _t->on_m_btnOK_clicked(); break;
        case 11: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCurrInverseCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCurrInverseCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QCurrInverseCommonParasDlg,
      qt_meta_data_QCurrInverseCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCurrInverseCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCurrInverseCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCurrInverseCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCurrInverseCommonParasDlg))
        return static_cast<void*>(const_cast< QCurrInverseCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QCurrInverseCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
