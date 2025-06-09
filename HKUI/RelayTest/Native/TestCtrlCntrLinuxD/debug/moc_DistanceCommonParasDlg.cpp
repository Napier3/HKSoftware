/****************************************************************************
** Meta object code from reading C++ file 'DistanceCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Distance/DistanceCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceCommonParasDlg[] = {

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
      25,   24,   24,   24, 0x08,
      64,   24,   24,   24, 0x08,
     100,   24,   24,   24, 0x08,
     136,   24,   24,   24, 0x08,
     168,   24,   24,   24, 0x08,
     202,   24,   24,   24, 0x08,
     238,   24,   24,   24, 0x08,
     274,   24,   24,   24, 0x08,
     305,   24,   24,   24, 0x08,
     345,  339,   24,   24, 0x08,
     386,  339,   24,   24, 0x08,
     428,   24,   24,   24, 0x08,
     459,   24,   24,   24, 0x08,
     480,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceCommonParasDlg[] = {
    "QDistanceCommonParasDlg\0\0"
    "on_m_txtPreFaultTime_editingFinished()\0"
    "on_m_txtFaultTime_editingFinished()\0"
    "on_m_txtTimeAfter_editingFinished()\0"
    "on_m_txtILoad_editingFinished()\0"
    "on_m_txtILoadPh_editingFinished()\0"
    "on_m_txtBreakTime_editingFinished()\0"
    "on_m_txtCloseTime_editingFinished()\0"
    "on_m_txtVzPh_editingFinished()\0"
    "on_m_txtMinTime_editingFinished()\0"
    "index\0on_m_cmbBreaker_currentIndexChanged(int)\0"
    "on_m_cmbVzDefine_currentIndexChanged(int)\0"
    "on_m_txtLine_editingFinished()\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QDistanceCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceCommonParasDlg *_t = static_cast<QDistanceCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtPreFaultTime_editingFinished(); break;
        case 1: _t->on_m_txtFaultTime_editingFinished(); break;
        case 2: _t->on_m_txtTimeAfter_editingFinished(); break;
        case 3: _t->on_m_txtILoad_editingFinished(); break;
        case 4: _t->on_m_txtILoadPh_editingFinished(); break;
        case 5: _t->on_m_txtBreakTime_editingFinished(); break;
        case 6: _t->on_m_txtCloseTime_editingFinished(); break;
        case 7: _t->on_m_txtVzPh_editingFinished(); break;
        case 8: _t->on_m_txtMinTime_editingFinished(); break;
        case 9: _t->on_m_cmbBreaker_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_m_cmbVzDefine_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_m_txtLine_editingFinished(); break;
        case 12: _t->on_m_btnOK_clicked(); break;
        case 13: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDistanceCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDistanceCommonParasDlg,
      qt_meta_data_QDistanceCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceCommonParasDlg))
        return static_cast<void*>(const_cast< QDistanceCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDistanceCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
