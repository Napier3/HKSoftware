/****************************************************************************
** Meta object code from reading C++ file 'QPowerDirAddMultDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/QPowerDirAddMultDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPowerDirAddMultDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPowerDirAddMultDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   27,   21,   20, 0x08,
      69,   20,   20,   20, 0x08,
     100,   20,   20,   20, 0x08,
     141,   20,   20,   20, 0x08,
     176,   20,   20,   20, 0x08,
     209,   20,   20,   20, 0x08,
     242,   20,   20,   20, 0x08,
     278,   20,   20,   20, 0x08,
     313,   20,   20,   20, 0x08,
     348,   20,   20,   20, 0x08,
     375,   20,   20,   20, 0x08,
     399,   20,   20,   20, 0x08,
     423,   20,   20,   20, 0x08,
     447,   20,   20,   20, 0x08,
     472,   20,   20,   20, 0x08,
     497,   20,   20,   20, 0x08,
     522,   20,   20,   20, 0x08,
     549,   20,   20,   20, 0x08,
     580,   20,   20,   20, 0x08,
     604,   20,   20,   20, 0x08,
     628,   20,   20,   20, 0x08,
     652,   20,   20,   20, 0x08,
     677,   20,   20,   20, 0x08,
     702,   20,   20,   20, 0x08,
     727,   20,   20,   20, 0x08,
     757,   20,   20,   20, 0x08,
     791,   20,   20,   20, 0x08,
     821,   20,   20,   20, 0x08,
     840,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPowerDirAddMultDlg[] = {
    "QPowerDirAddMultDlg\0\0float\0pLineEdit\0"
    "slot_lne_Changed(QSttLineEdit*)\0"
    "slot_lneStep_editingFinished()\0"
    "slot_lneMaxSensitAngle_editingFinished()\0"
    "slot_lneActRange_editingFinished()\0"
    "slot_lneFaultV_editingFinished()\0"
    "slot_lneFaultI_editingFinished()\0"
    "slot_lneFaultTime_editingFinished()\0"
    "slot_lneAbsError_editingFinished()\0"
    "slot_lneRelError_editingFinished()\0"
    "slot_chb_TestTypeClicked()\0"
    "slot_chb_ATypeClicked()\0slot_chb_BTypeClicked()\0"
    "slot_chb_CTypeClicked()\0"
    "slot_chb_ABTypeClicked()\0"
    "slot_chb_BCTypeClicked()\0"
    "slot_chb_CATypeClicked()\0"
    "slot_chb_ZeroTypeClicked()\0"
    "slot_chb_NegativeTypeClicked()\0"
    "slot_chb_ATestClicked()\0slot_chb_BTestClicked()\0"
    "slot_chb_CTestClicked()\0"
    "slot_chb_ABTestClicked()\0"
    "slot_chb_BCTestClicked()\0"
    "slot_chb_CATestClicked()\0"
    "slot_chb_ZeroSeqTestClicked()\0"
    "slot_chb_NegativeSeqTestClicked()\0"
    "slot_cmb_EerrorType_Changed()\0"
    "slot_pbn_OKClick()\0slot_pbn_CancelClick()\0"
};

void QPowerDirAddMultDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPowerDirAddMultDlg *_t = static_cast<QPowerDirAddMultDlg *>(_o);
        switch (_id) {
        case 0: { float _r = _t->slot_lne_Changed((*reinterpret_cast< QSttLineEdit*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 1: _t->slot_lneStep_editingFinished(); break;
        case 2: _t->slot_lneMaxSensitAngle_editingFinished(); break;
        case 3: _t->slot_lneActRange_editingFinished(); break;
        case 4: _t->slot_lneFaultV_editingFinished(); break;
        case 5: _t->slot_lneFaultI_editingFinished(); break;
        case 6: _t->slot_lneFaultTime_editingFinished(); break;
        case 7: _t->slot_lneAbsError_editingFinished(); break;
        case 8: _t->slot_lneRelError_editingFinished(); break;
        case 9: _t->slot_chb_TestTypeClicked(); break;
        case 10: _t->slot_chb_ATypeClicked(); break;
        case 11: _t->slot_chb_BTypeClicked(); break;
        case 12: _t->slot_chb_CTypeClicked(); break;
        case 13: _t->slot_chb_ABTypeClicked(); break;
        case 14: _t->slot_chb_BCTypeClicked(); break;
        case 15: _t->slot_chb_CATypeClicked(); break;
        case 16: _t->slot_chb_ZeroTypeClicked(); break;
        case 17: _t->slot_chb_NegativeTypeClicked(); break;
        case 18: _t->slot_chb_ATestClicked(); break;
        case 19: _t->slot_chb_BTestClicked(); break;
        case 20: _t->slot_chb_CTestClicked(); break;
        case 21: _t->slot_chb_ABTestClicked(); break;
        case 22: _t->slot_chb_BCTestClicked(); break;
        case 23: _t->slot_chb_CATestClicked(); break;
        case 24: _t->slot_chb_ZeroSeqTestClicked(); break;
        case 25: _t->slot_chb_NegativeSeqTestClicked(); break;
        case 26: _t->slot_cmb_EerrorType_Changed(); break;
        case 27: _t->slot_pbn_OKClick(); break;
        case 28: _t->slot_pbn_CancelClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPowerDirAddMultDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPowerDirAddMultDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QPowerDirAddMultDlg,
      qt_meta_data_QPowerDirAddMultDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPowerDirAddMultDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPowerDirAddMultDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPowerDirAddMultDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPowerDirAddMultDlg))
        return static_cast<void*>(const_cast< QPowerDirAddMultDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QPowerDirAddMultDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
