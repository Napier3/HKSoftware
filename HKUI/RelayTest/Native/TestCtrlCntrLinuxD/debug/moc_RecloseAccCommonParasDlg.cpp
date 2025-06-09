/****************************************************************************
** Meta object code from reading C++ file 'RecloseAccCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/RecloseAcc/RecloseAccCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecloseAccCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRecloseAccCommonParasDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x08,
      67,   26,   26,   26, 0x08,
      88,   26,   26,   26, 0x08,
     113,   26,   26,   26, 0x08,
     156,  150,   26,   26, 0x08,
     203,   26,   26,   26, 0x08,
     236,   26,   26,   26, 0x08,
     271,  150,   26,   26, 0x08,
     325,   26,   26,   26, 0x08,
     365,   26,   26,   26, 0x08,
     405,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QRecloseAccCommonParasDlg[] = {
    "QRecloseAccCommonParasDlg\0\0"
    "on_m_editPreFaultTime_editingFinished()\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
    "on_m_editFaultTime_editingFinished()\0"
    "index\0on_m_cbbFaultTrigMode_currentIndexChanged(int)\0"
    "on_m_editILoad_editingFinished()\0"
    "on_m_editILoadPh_editingFinished()\0"
    "on_m_cbbSimulateBreakerDelay_currentIndexChanged(int)\0"
    "on_m_editBrkBreakTime_editingFinished()\0"
    "on_m_editBrkCloseTime_editingFinished()\0"
    "on_m_editActionTime_editingFinished()\0"
};

void QRecloseAccCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRecloseAccCommonParasDlg *_t = static_cast<QRecloseAccCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_editPreFaultTime_editingFinished(); break;
        case 1: _t->on_m_btnOk_clicked(); break;
        case 2: _t->on_m_btnCancel_clicked(); break;
        case 3: _t->on_m_editFaultTime_editingFinished(); break;
        case 4: _t->on_m_cbbFaultTrigMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_m_editILoad_editingFinished(); break;
        case 6: _t->on_m_editILoadPh_editingFinished(); break;
        case 7: _t->on_m_cbbSimulateBreakerDelay_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_editBrkBreakTime_editingFinished(); break;
        case 9: _t->on_m_editBrkCloseTime_editingFinished(); break;
        case 10: _t->on_m_editActionTime_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QRecloseAccCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRecloseAccCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QRecloseAccCommonParasDlg,
      qt_meta_data_QRecloseAccCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRecloseAccCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRecloseAccCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRecloseAccCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRecloseAccCommonParasDlg))
        return static_cast<void*>(const_cast< QRecloseAccCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QRecloseAccCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
