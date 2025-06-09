/****************************************************************************
** Meta object code from reading C++ file 'SynAddMultQuickDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynAddMultQuickDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynAddMultQuickDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynAddMultQuickDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   27,   21,   20, 0x08,
      66,   20,   20,   20, 0x08,
      98,   20,   20,   20, 0x08,
     131,   20,   20,   20, 0x08,
     163,   20,   20,   20, 0x08,
     196,   20,   20,   20, 0x08,
     215,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSynAddMultQuickDlg[] = {
    "QSynAddMultQuickDlg\0\0float\0pLineEdit\0"
    "slot_lne_Changed(QLineEdit*)\0"
    "slot_lneUPlus_editingFinished()\0"
    "slot_lneUMinus_editingFinished()\0"
    "slot_lneFPlus_editingFinished()\0"
    "slot_lneFMinus_editingFinished()\0"
    "slot_pbn_OKClick()\0slot_pbn_CancelClick()\0"
};

void QSynAddMultQuickDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynAddMultQuickDlg *_t = static_cast<QSynAddMultQuickDlg *>(_o);
        switch (_id) {
        case 0: { float _r = _t->slot_lne_Changed((*reinterpret_cast< QLineEdit*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 1: _t->slot_lneUPlus_editingFinished(); break;
        case 2: _t->slot_lneUMinus_editingFinished(); break;
        case 3: _t->slot_lneFPlus_editingFinished(); break;
        case 4: _t->slot_lneFMinus_editingFinished(); break;
        case 5: _t->slot_pbn_OKClick(); break;
        case 6: _t->slot_pbn_CancelClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSynAddMultQuickDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynAddMultQuickDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSynAddMultQuickDlg,
      qt_meta_data_QSynAddMultQuickDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynAddMultQuickDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynAddMultQuickDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynAddMultQuickDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynAddMultQuickDlg))
        return static_cast<void*>(const_cast< QSynAddMultQuickDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSynAddMultQuickDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
