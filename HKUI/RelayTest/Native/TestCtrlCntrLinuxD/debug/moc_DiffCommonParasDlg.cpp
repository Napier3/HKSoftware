/****************************************************************************
** Meta object code from reading C++ file 'DiffCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Diff/DiffCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiffCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDiffCommonParasDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      59,   20,   20,   20, 0x08,
      98,   20,   20,   20, 0x08,
     134,   20,   20,   20, 0x08,
     176,  170,   20,   20, 0x08,
     219,   20,   20,   20, 0x08,
     250,   20,   20,   20, 0x08,
     282,   20,   20,   20, 0x08,
     314,   20,   20,   20, 0x08,
     346,   20,   20,   20, 0x08,
     379,   20,   20,   20, 0x08,
     412,   20,   20,   20, 0x08,
     445,   20,   20,   20, 0x08,
     478,   20,   20,   20, 0x08,
     511,   20,   20,   20, 0x08,
     544,   20,   20,   20, 0x08,
     577,   20,   20,   20, 0x08,
     610,   20,   20,   20, 0x08,
     643,  170,   20,   20, 0x08,
     684,  170,   20,   20, 0x08,
     725,  170,   20,   20, 0x08,
     766,  170,   20,   20, 0x08,
     815,  170,   20,   20, 0x08,
     860,  170,   20,   20, 0x08,
     909,  170,   20,   20, 0x08,
     958,  170,   20,   20, 0x08,
    1002,  170,   20,   20, 0x08,
    1046,  170,   20,   20, 0x08,
    1087,  170,   20,   20, 0x08,
    1131,   20,   20,   20, 0x08,
    1159,   20,   20,   20, 0x08,
    1188,  170,   20,   20, 0x08,
    1230,   20,   20,   20, 0x08,
    1261,   20,   20,   20, 0x08,
    1291,   20,   20,   20, 0x08,
    1321,   20,   20,   20, 0x08,
    1342,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDiffCommonParasDlg[] = {
    "QDiffCommonParasDlg\0\0"
    "on_m_txtPrepareTime_editingFinished()\0"
    "on_m_txtPreFaultTime_editingFinished()\0"
    "on_m_txtFaultTime_editingFinished()\0"
    "on_m_txtTimeAfter_editingFinished()\0"
    "index\0on_m_cmbKPSetMode_currentIndexChanged(int)\0"
    "slot_m_txtSn_editingFinished()\0"
    "slot_m_txtHUn_editingFinished()\0"
    "slot_m_txtMUn_editingFinished()\0"
    "slot_m_txtLUn_editingFinished()\0"
    "slot_m_txtCTPh_editingFinished()\0"
    "slot_m_txtCTPm_editingFinished()\0"
    "slot_m_txtCTPl_editingFinished()\0"
    "slot_m_txtCTSh_editingFinished()\0"
    "slot_m_txtCTSm_editingFinished()\0"
    "slot_m_txtCTSl_editingFinished()\0"
    "on_m_txtKphSet_editingFinished()\0"
    "on_m_txtKpmSet_editingFinished()\0"
    "on_m_txtKplSet_editingFinished()\0"
    "slot_m_cmbWindH_currentIndexChanged(int)\0"
    "slot_m_cmbWindM_currentIndexChanged(int)\0"
    "slot_m_cmbWindL_currentIndexChanged(int)\0"
    "slot_m_cmbPhCorrectMode_currentIndexChanged(int)\0"
    "slot_m_cmbAdoptWind_currentIndexChanged(int)\0"
    "on_m_cmbTransGroupMode1_currentIndexChanged(int)\0"
    "on_m_cmbTransGroupMode2_currentIndexChanged(int)\0"
    "slot_m_cmbJXFactor_currentIndexChanged(int)\0"
    "on_m_cmbSearchMode_currentIndexChanged(int)\0"
    "on_m_cmbCTPoint_currentIndexChanged(int)\0"
    "on_m_cmbIrEquation_currentIndexChanged(int)\0"
    "on_m_txtK_editingFinished()\0"
    "on_m_txtK2_editingFinished()\0"
    "on_m_cmbEarthing_currentIndexChanged(int)\0"
    "on_m_txtStep_editingFinished()\0"
    "on_m_txtVg1_editingFinished()\0"
    "on_m_txtVg2_editingFinished()\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QDiffCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDiffCommonParasDlg *_t = static_cast<QDiffCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtPrepareTime_editingFinished(); break;
        case 1: _t->on_m_txtPreFaultTime_editingFinished(); break;
        case 2: _t->on_m_txtFaultTime_editingFinished(); break;
        case 3: _t->on_m_txtTimeAfter_editingFinished(); break;
        case 4: _t->on_m_cmbKPSetMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_m_txtSn_editingFinished(); break;
        case 6: _t->slot_m_txtHUn_editingFinished(); break;
        case 7: _t->slot_m_txtMUn_editingFinished(); break;
        case 8: _t->slot_m_txtLUn_editingFinished(); break;
        case 9: _t->slot_m_txtCTPh_editingFinished(); break;
        case 10: _t->slot_m_txtCTPm_editingFinished(); break;
        case 11: _t->slot_m_txtCTPl_editingFinished(); break;
        case 12: _t->slot_m_txtCTSh_editingFinished(); break;
        case 13: _t->slot_m_txtCTSm_editingFinished(); break;
        case 14: _t->slot_m_txtCTSl_editingFinished(); break;
        case 15: _t->on_m_txtKphSet_editingFinished(); break;
        case 16: _t->on_m_txtKpmSet_editingFinished(); break;
        case 17: _t->on_m_txtKplSet_editingFinished(); break;
        case 18: _t->slot_m_cmbWindH_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slot_m_cmbWindM_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->slot_m_cmbWindL_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->slot_m_cmbPhCorrectMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slot_m_cmbAdoptWind_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_m_cmbTransGroupMode1_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_m_cmbTransGroupMode2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->slot_m_cmbJXFactor_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_m_cmbSearchMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_m_cmbCTPoint_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_m_cmbIrEquation_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_m_txtK_editingFinished(); break;
        case 30: _t->on_m_txtK2_editingFinished(); break;
        case 31: _t->on_m_cmbEarthing_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_m_txtStep_editingFinished(); break;
        case 33: _t->on_m_txtVg1_editingFinished(); break;
        case 34: _t->on_m_txtVg2_editingFinished(); break;
        case 35: _t->on_m_btnOK_clicked(); break;
        case 36: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDiffCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDiffCommonParasDlg,
      qt_meta_data_QDiffCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffCommonParasDlg))
        return static_cast<void*>(const_cast< QDiffCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDiffCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
