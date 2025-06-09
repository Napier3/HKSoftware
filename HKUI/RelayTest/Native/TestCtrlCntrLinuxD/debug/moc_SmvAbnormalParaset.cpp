/****************************************************************************
** Meta object code from reading C++ file 'SmvAbnormalParaset.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/SmvAbnormal/SmvAbnormalParaset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SmvAbnormalParaset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSmvAbnormalParaset[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   21,   20,   20, 0x09,
      54,   21,   20,   20, 0x09,
      84,   20,   20,   20, 0x09,
     113,   20,   20,   20, 0x09,
     143,   20,   20,   20, 0x09,
     177,   20,   20,   20, 0x09,
     212,   20,   20,   20, 0x09,
     239,   20,   20,   20, 0x09,
     273,  267,   20,   20, 0x09,
     302,   20,   20,   20, 0x09,
     333,   20,   20,   20, 0x09,
     365,   20,   20,   20, 0x09,
     398,   20,   20,   20, 0x09,
     433,   20,   20,   20, 0x09,
     458,   20,   20,   20, 0x09,
     484,   20,   20,   20, 0x09,
     510,   20,   20,   20, 0x09,
     537,   20,   20,   20, 0x09,
     566,   20,   20,   20, 0x09,
     596,   20,   20,   20, 0x09,
     625,   20,   20,   20, 0x09,
     655,   20,   20,   20, 0x09,
     682,   20,   20,   20, 0x09,
     710,   20,   20,   20, 0x09,
     735,   20,   20,   20, 0x09,
     764,   20,   20,   20, 0x09,
     791,   20,   20,   20, 0x09,
     819,   20,   20,   20, 0x09,
     851,   20,   20,   20, 0x09,
     883,   20,   20,   20, 0x09,
     912,   20,   20,   20, 0x09,
     947,   20,   20,   20, 0x09,
     982,  972,   20,   20, 0x09,
    1012,   20,   20,   20, 0x09,
    1039,   20,   20,   20, 0x09,
    1064,   20,   20,   20, 0x09,
    1093, 1086,   20,   20, 0x09,
    1133,   20,   20,   20, 0x09,
    1155,   20,   20,   20, 0x09,
    1190, 1178,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSmvAbnormalParaset[] = {
    "QSmvAbnormalParaset\0\0index\0"
    "slot_cmb_APPIDChanged(int)\0"
    "slot_cmb_sendtypeChanged(int)\0"
    "slot_lne_sendcircleChanged()\0"
    "slot_lne_sendcircleKeyBoard()\0"
    "slot_lne_circlepersecondChanged()\0"
    "slot_lne_circlepersecondKeyBoard()\0"
    "slot_lne_sendtimeChanged()\0"
    "slot_lne_sendtimeKeyBoard()\0state\0"
    "slot_ck_losestepChanged(int)\0"
    "slot_lne_flypointvoltChanged()\0"
    "slot_lne_flypointvoltKeyBoard()\0"
    "slot_lne_flypoitcurrentChanged()\0"
    "slot_lne_flypointcurrentKeyBoard()\0"
    "slot_lne_jitterChanged()\0"
    "slot_lne_jitterKeyBoard()\0"
    "slot_lne_errcmptChanged()\0"
    "slot_lne_errcmptKeyBoard()\0"
    "slot_lne_offsettimeChanged()\0"
    "slot_lne_offsettingKeyBoard()\0"
    "slot_lne_modifytimeChanged()\0"
    "slot_lne_modifytimeKeyBoard()\0"
    "slot_lne_indexerrChanged()\0"
    "slot_lne_indexerrKeyBoard()\0"
    "slot_radio_lostClicked()\0"
    "slot_radio_flypointClicked()\0"
    "slot_radio_jitterClicked()\0"
    "slot_radio_errcmptClicked()\0"
    "slot_radio_delayoffsetClicked()\0"
    "slot_radio_delaymodifyClicked()\0"
    "slot_radio_indexerrClicked()\0"
    "slot_radio_qualityinvalidChanged()\0"
    "slot_CkUabcIabcClicked()\0pointlist\0"
    "slot_ValidPoint(QList<bool>&)\0"
    "slot_pbn_AbnomalPointSet()\0"
    "slot_ptn_ChannelSelect()\0slot_pbn_MessageSet()\0"
    "nState\0slot_checkBox_SelOrgPkgSet_changed(int)\0"
    "slot_pbn_qualitySet()\0slot_radio_noClicked()\0"
    "listQuality\0slot_QualityParaChanged(QList<int>&)\0"
};

void QSmvAbnormalParaset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSmvAbnormalParaset *_t = static_cast<QSmvAbnormalParaset *>(_o);
        switch (_id) {
        case 0: _t->slot_cmb_APPIDChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_cmb_sendtypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_lne_sendcircleChanged(); break;
        case 3: _t->slot_lne_sendcircleKeyBoard(); break;
        case 4: _t->slot_lne_circlepersecondChanged(); break;
        case 5: _t->slot_lne_circlepersecondKeyBoard(); break;
        case 6: _t->slot_lne_sendtimeChanged(); break;
        case 7: _t->slot_lne_sendtimeKeyBoard(); break;
        case 8: _t->slot_ck_losestepChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_lne_flypointvoltChanged(); break;
        case 10: _t->slot_lne_flypointvoltKeyBoard(); break;
        case 11: _t->slot_lne_flypoitcurrentChanged(); break;
        case 12: _t->slot_lne_flypointcurrentKeyBoard(); break;
        case 13: _t->slot_lne_jitterChanged(); break;
        case 14: _t->slot_lne_jitterKeyBoard(); break;
        case 15: _t->slot_lne_errcmptChanged(); break;
        case 16: _t->slot_lne_errcmptKeyBoard(); break;
        case 17: _t->slot_lne_offsettimeChanged(); break;
        case 18: _t->slot_lne_offsettingKeyBoard(); break;
        case 19: _t->slot_lne_modifytimeChanged(); break;
        case 20: _t->slot_lne_modifytimeKeyBoard(); break;
        case 21: _t->slot_lne_indexerrChanged(); break;
        case 22: _t->slot_lne_indexerrKeyBoard(); break;
        case 23: _t->slot_radio_lostClicked(); break;
        case 24: _t->slot_radio_flypointClicked(); break;
        case 25: _t->slot_radio_jitterClicked(); break;
        case 26: _t->slot_radio_errcmptClicked(); break;
        case 27: _t->slot_radio_delayoffsetClicked(); break;
        case 28: _t->slot_radio_delaymodifyClicked(); break;
        case 29: _t->slot_radio_indexerrClicked(); break;
        case 30: _t->slot_radio_qualityinvalidChanged(); break;
        case 31: _t->slot_CkUabcIabcClicked(); break;
        case 32: _t->slot_ValidPoint((*reinterpret_cast< QList<bool>(*)>(_a[1]))); break;
        case 33: _t->slot_pbn_AbnomalPointSet(); break;
        case 34: _t->slot_ptn_ChannelSelect(); break;
        case 35: _t->slot_pbn_MessageSet(); break;
        case 36: _t->slot_checkBox_SelOrgPkgSet_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->slot_pbn_qualitySet(); break;
        case 38: _t->slot_radio_noClicked(); break;
        case 39: _t->slot_QualityParaChanged((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSmvAbnormalParaset::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSmvAbnormalParaset::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSmvAbnormalParaset,
      qt_meta_data_QSmvAbnormalParaset, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSmvAbnormalParaset::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSmvAbnormalParaset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSmvAbnormalParaset::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSmvAbnormalParaset))
        return static_cast<void*>(const_cast< QSmvAbnormalParaset*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSmvAbnormalParaset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
