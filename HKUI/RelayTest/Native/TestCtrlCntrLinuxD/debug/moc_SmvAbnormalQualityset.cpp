/****************************************************************************
** Meta object code from reading C++ file 'SmvAbnormalQualityset.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/SmvAbnormal/SmvAbnormalQualityset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SmvAbnormalQualityset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSmvAbnormalQualitySet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   23,   23,   23, 0x09,
      74,   23,   23,   23, 0x09,
     105,   99,   23,   23, 0x09,
     136,   99,   23,   23, 0x09,
     167,   99,   23,   23, 0x09,
     198,   99,   23,   23, 0x09,
     229,   99,   23,   23, 0x09,
     260,   99,   23,   23, 0x09,
     291,   99,   23,   23, 0x09,
     322,   99,   23,   23, 0x09,
     353,   99,   23,   23, 0x09,
     384,   99,   23,   23, 0x09,
     416,   99,   23,   23, 0x09,
     448,   99,   23,   23, 0x09,
     480,   99,   23,   23, 0x09,
     515,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSmvAbnormalQualitySet[] = {
    "QSmvAbnormalQualitySet\0\0"
    "sig_QualityPara(QList<int>&)\0"
    "slot_pbn_OKClicked()\0slot_pbn_CancelClicked()\0"
    "index\0slot_cmb_bit1StateChanged(int)\0"
    "slot_cmb_bit2StateChanged(int)\0"
    "slot_cmb_bit3StateChanged(int)\0"
    "slot_cmb_bit4StateChanged(int)\0"
    "slot_cmb_bit5StateChanged(int)\0"
    "slot_cmb_bit6StateChanged(int)\0"
    "slot_cmb_bit7StateChanged(int)\0"
    "slot_cmb_bit8StateChanged(int)\0"
    "slot_cmb_bit9StateChanged(int)\0"
    "slot_cmb_bit10StateChanged(int)\0"
    "slot_cmb_bit11StateChanged(int)\0"
    "slot_cmb_bit12StateChanged(int)\0"
    "slot_cmb_DispTypeStateChanged(int)\0"
    "slot_lne_DispTypeKeyBoard()\0"
};

void QSmvAbnormalQualitySet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSmvAbnormalQualitySet *_t = static_cast<QSmvAbnormalQualitySet *>(_o);
        switch (_id) {
        case 0: _t->sig_QualityPara((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 1: _t->slot_pbn_OKClicked(); break;
        case 2: _t->slot_pbn_CancelClicked(); break;
        case 3: _t->slot_cmb_bit1StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_cmb_bit2StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_cmb_bit3StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_cmb_bit4StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_cmb_bit5StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_cmb_bit6StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_cmb_bit7StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_cmb_bit8StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_cmb_bit9StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_cmb_bit10StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_cmb_bit11StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slot_cmb_bit12StateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_cmb_DispTypeStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slot_lne_DispTypeKeyBoard(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSmvAbnormalQualitySet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSmvAbnormalQualitySet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSmvAbnormalQualitySet,
      qt_meta_data_QSmvAbnormalQualitySet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSmvAbnormalQualitySet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSmvAbnormalQualitySet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSmvAbnormalQualitySet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSmvAbnormalQualitySet))
        return static_cast<void*>(const_cast< QSmvAbnormalQualitySet*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSmvAbnormalQualitySet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void QSmvAbnormalQualitySet::sig_QualityPara(QList<int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
