/****************************************************************************
** Meta object code from reading C++ file 'VolInverAddMultDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/VolInverseTime/VolInverAddMultDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolInverAddMultDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QVolInverAddMultDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   27,   21,   20, 0x08,
      66,   20,   20,   20, 0x08,
     105,   20,   20,   20, 0x08,
     142,   20,   20,   20, 0x08,
     180,   20,   20,   20, 0x08,
     216,   20,   20,   20, 0x08,
     253,   20,   20,   20, 0x08,
     283,   20,   20,   20, 0x08,
     318,   20,   20,   20, 0x08,
     351,   20,   20,   20, 0x08,
     385,   20,   20,   20, 0x08,
     417,   20,   20,   20, 0x08,
     445,   20,   20,   20, 0x08,
     464,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QVolInverAddMultDlg[] = {
    "QVolInverAddMultDlg\0\0float\0pLineEdit\0"
    "slot_lne_Changed(QLineEdit*)\0"
    "slot_lneVChangeStart_editingFinished()\0"
    "slot_lneVChangeEnd_editingFinished()\0"
    "slot_lneVChangeStep_editingFinished()\0"
    "slot_lneDLCurrent_editingFinished()\0"
    "slot_lneFPhaseDiff_editingFinished()\0"
    "slot_lneFre_editingFinished()\0"
    "slot_lneRelative_editingFinished()\0"
    "slot_lneAbsAdd_editingFinished()\0"
    "slot_lneAbsDown_editingFinished()\0"
    "slot_cmb_ErrorType_Changed(int)\0"
    "slot_chb_faultTypeClicked()\0"
    "slot_pbn_OKClick()\0slot_pbn_CancelClick()\0"
};

void QVolInverAddMultDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QVolInverAddMultDlg *_t = static_cast<QVolInverAddMultDlg *>(_o);
        switch (_id) {
        case 0: { float _r = _t->slot_lne_Changed((*reinterpret_cast< QLineEdit*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 1: _t->slot_lneVChangeStart_editingFinished(); break;
        case 2: _t->slot_lneVChangeEnd_editingFinished(); break;
        case 3: _t->slot_lneVChangeStep_editingFinished(); break;
        case 4: _t->slot_lneDLCurrent_editingFinished(); break;
        case 5: _t->slot_lneFPhaseDiff_editingFinished(); break;
        case 6: _t->slot_lneFre_editingFinished(); break;
        case 7: _t->slot_lneRelative_editingFinished(); break;
        case 8: _t->slot_lneAbsAdd_editingFinished(); break;
        case 9: _t->slot_lneAbsDown_editingFinished(); break;
        case 10: _t->slot_cmb_ErrorType_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_chb_faultTypeClicked(); break;
        case 12: _t->slot_pbn_OKClick(); break;
        case 13: _t->slot_pbn_CancelClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QVolInverAddMultDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QVolInverAddMultDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QVolInverAddMultDlg,
      qt_meta_data_QVolInverAddMultDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QVolInverAddMultDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QVolInverAddMultDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QVolInverAddMultDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QVolInverAddMultDlg))
        return static_cast<void*>(const_cast< QVolInverAddMultDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QVolInverAddMultDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
