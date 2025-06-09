/****************************************************************************
** Meta object code from reading C++ file 'DistanceSearchAddMultDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/DistanceSearch/DistanceSearchAddMultDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceSearchAddMultDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceSearchAddMultDlg[] = {

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
     135,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     237,   26,   26,   26, 0x08,
     258,   26,   26,   26, 0x08,
     283,   26,   26,   26, 0x08,
     323,   26,   26,   26, 0x08,
     363,   26,   26,   26, 0x08,
     410,  404,   26,   26, 0x08,
     452,   26,   26,   26, 0x08,
     487,   26,   26,   26, 0x08,
     522,   26,   26,   26, 0x08,
     558,   26,   26,   26, 0x08,
     594,   26,   26,   26, 0x08,
     634,   26,   26,   26, 0x08,
     674,   26,   26,   26, 0x08,
     709,   26,   26,   26, 0x08,
     746,   26,   26,   26, 0x08,
     780,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceSearchAddMultDlg[] = {
    "QDistanceSearchAddMultDlg\0\0"
    "nFaultType,dSettingTime,nZoneType,dBegZ,dBegAng,dEndZ,dEndAng,dFaultCu"
    "r,dFaultVolt,dRelErr,dAbsErr,nErrType\0"
    "sig_AddDistanceSearchItem(int,double,int,double,double,double,double,d"
    "ouble,double,double,double,int)\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
    "on_m_editLNActionTime_editingFinished()\0"
    "on_m_editLLActionTime_editingFinished()\0"
    "on_m_editLLLActionTime_editingFinished()\0"
    "index\0on_m_cbbZoneType_currentIndexChanged(int)\0"
    "on_m_editOrigImp_editingFinished()\0"
    "on_m_editOrigAng_editingFinished()\0"
    "on_m_editFaultCur_editingFinished()\0"
    "on_m_editFaultVol_editingFinished()\0"
    "on_m_editSearchAngBeg_editingFinished()\0"
    "on_m_editSearchAngEnd_editingFinished()\0"
    "on_m_editAngStep_editingFinished()\0"
    "on_m_editSearchLen_editingFinished()\0"
    "on_m_editRelErr_editingFinished()\0"
    "on_m_editAbsErr_editingFinished()\0"
};

void QDistanceSearchAddMultDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceSearchAddMultDlg *_t = static_cast<QDistanceSearchAddMultDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_AddDistanceSearchItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])),(*reinterpret_cast< double(*)>(_a[9])),(*reinterpret_cast< double(*)>(_a[10])),(*reinterpret_cast< double(*)>(_a[11])),(*reinterpret_cast< int(*)>(_a[12]))); break;
        case 1: _t->on_m_btnOk_clicked(); break;
        case 2: _t->on_m_btnCancel_clicked(); break;
        case 3: _t->on_m_editLNActionTime_editingFinished(); break;
        case 4: _t->on_m_editLLActionTime_editingFinished(); break;
        case 5: _t->on_m_editLLLActionTime_editingFinished(); break;
        case 6: _t->on_m_cbbZoneType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_m_editOrigImp_editingFinished(); break;
        case 8: _t->on_m_editOrigAng_editingFinished(); break;
        case 9: _t->on_m_editFaultCur_editingFinished(); break;
        case 10: _t->on_m_editFaultVol_editingFinished(); break;
        case 11: _t->on_m_editSearchAngBeg_editingFinished(); break;
        case 12: _t->on_m_editSearchAngEnd_editingFinished(); break;
        case 13: _t->on_m_editAngStep_editingFinished(); break;
        case 14: _t->on_m_editSearchLen_editingFinished(); break;
        case 15: _t->on_m_editRelErr_editingFinished(); break;
        case 16: _t->on_m_editAbsErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDistanceSearchAddMultDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceSearchAddMultDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDistanceSearchAddMultDlg,
      qt_meta_data_QDistanceSearchAddMultDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceSearchAddMultDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceSearchAddMultDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceSearchAddMultDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceSearchAddMultDlg))
        return static_cast<void*>(const_cast< QDistanceSearchAddMultDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDistanceSearchAddMultDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QDistanceSearchAddMultDlg::sig_AddDistanceSearchItem(int _t1, double _t2, int _t3, double _t4, double _t5, double _t6, double _t7, double _t8, double _t9, double _t10, double _t11, int _t12)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
