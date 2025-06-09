/****************************************************************************
** Meta object code from reading C++ file 'SmvAbnormalMessageset.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/SmvAbnormal/SmvAbnormalMessageset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SmvAbnormalMessageset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSmvAbnormalMessageSet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   24,   23,   23, 0x08,
      79,   23,   23,   23, 0x08,
     107,   23,   23,   23, 0x08,
     133,   23,   23,   23, 0x08,
     158,   23,   23,   23, 0x08,
     189,   23,   23,   23, 0x08,
     215,   23,   23,   23, 0x08,
     239,   23,   23,   23, 0x08,
     262,   23,   23,   23, 0x08,
     288,   23,   23,   23, 0x08,
     314,   23,   23,   23, 0x08,
     344,   23,   23,   23, 0x08,
     369,   23,   23,   23, 0x08,
     394,   23,   23,   23, 0x08,
     423,   23,   23,   23, 0x08,
     450,   23,   23,   23, 0x08,
     476,   23,   23,   23, 0x08,
     508,   23,   23,   23, 0x08,
     535,   23,   23,   23, 0x08,
     560,   23,   23,   23, 0x08,
     584,   23,   23,   23, 0x08,
     610,   23,   23,   23, 0x08,
     637,   23,   23,   23, 0x08,
     658,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSmvAbnormalMessageSet[] = {
    "QSmvAbnormalMessageSet\0\0pEditLine,bIsNor\0"
    "slot_edit_changed(QSttLineEdit*,bool)\0"
    "slot_lne_sourceMacChanged()\0"
    "slot_lne_destMACChanged()\0"
    "slot_lne_VIanIDChanged()\0"
    "slot_lne_VIanPriorityChanged()\0"
    "slot_lne_nettypeChanged()\0"
    "slot_lne_APPIDChanged()\0slot_lne_SVIDChanged()\0"
    "slot_cmb_synchroChanged()\0"
    "slot_lne_versionChanged()\0"
    "slot_lne_sampledelayChanged()\0"
    "slot_lne_datsetChanged()\0"
    "slot_lne_RefrTmChanged()\0"
    "slot_lne_sourceMacKeyBoard()\0"
    "slot_lne_destMACKeyBoard()\0"
    "slot_lne_VIanIDKeyBoard()\0"
    "slot_lne_VIanPriorityKeyBoard()\0"
    "slot_lne_nettypeKeyBoard()\0"
    "slot_lne_APPIDKeyBoard()\0"
    "slot_lne_SVIDKeyBoard()\0"
    "slot_lne_datsetKeyBoard()\0"
    "slot_lne_versionKeyBoard()\0"
    "slot_pbn_OkClicked()\0slot_pbn_Cancle()\0"
};

void QSmvAbnormalMessageSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSmvAbnormalMessageSet *_t = static_cast<QSmvAbnormalMessageSet *>(_o);
        switch (_id) {
        case 0: _t->slot_edit_changed((*reinterpret_cast< QSttLineEdit*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->slot_lne_sourceMacChanged(); break;
        case 2: _t->slot_lne_destMACChanged(); break;
        case 3: _t->slot_lne_VIanIDChanged(); break;
        case 4: _t->slot_lne_VIanPriorityChanged(); break;
        case 5: _t->slot_lne_nettypeChanged(); break;
        case 6: _t->slot_lne_APPIDChanged(); break;
        case 7: _t->slot_lne_SVIDChanged(); break;
        case 8: _t->slot_cmb_synchroChanged(); break;
        case 9: _t->slot_lne_versionChanged(); break;
        case 10: _t->slot_lne_sampledelayChanged(); break;
        case 11: _t->slot_lne_datsetChanged(); break;
        case 12: _t->slot_lne_RefrTmChanged(); break;
        case 13: _t->slot_lne_sourceMacKeyBoard(); break;
        case 14: _t->slot_lne_destMACKeyBoard(); break;
        case 15: _t->slot_lne_VIanIDKeyBoard(); break;
        case 16: _t->slot_lne_VIanPriorityKeyBoard(); break;
        case 17: _t->slot_lne_nettypeKeyBoard(); break;
        case 18: _t->slot_lne_APPIDKeyBoard(); break;
        case 19: _t->slot_lne_SVIDKeyBoard(); break;
        case 20: _t->slot_lne_datsetKeyBoard(); break;
        case 21: _t->slot_lne_versionKeyBoard(); break;
        case 22: _t->slot_pbn_OkClicked(); break;
        case 23: _t->slot_pbn_Cancle(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSmvAbnormalMessageSet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSmvAbnormalMessageSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSmvAbnormalMessageSet,
      qt_meta_data_QSmvAbnormalMessageSet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSmvAbnormalMessageSet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSmvAbnormalMessageSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSmvAbnormalMessageSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSmvAbnormalMessageSet))
        return static_cast<void*>(const_cast< QSmvAbnormalMessageSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSmvAbnormalMessageSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
