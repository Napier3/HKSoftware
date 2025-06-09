/****************************************************************************
** Meta object code from reading C++ file 'LowFreqCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowFreq/LowFreqCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowFreqCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowFreqCommonParasDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      68,   62,   23,   23, 0x08,
     117,  109,   23,   23, 0x08,
     152,   23,   23,   23, 0x08,
     173,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLowFreqCommonParasDlg[] = {
    "QLowFreqCommonParasDlg\0\0"
    "on_m_txt_SteadyTime_editingFinished()\0"
    "index\0on_m_cmb_VBlock_currentIndexChanged(int)\0"
    "checked\0on_m_rBtn_FreqChange_toggled(bool)\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QLowFreqCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowFreqCommonParasDlg *_t = static_cast<QLowFreqCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_txt_SteadyTime_editingFinished(); break;
        case 1: _t->on_m_cmb_VBlock_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_m_rBtn_FreqChange_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_m_btnOK_clicked(); break;
        case 4: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QLowFreqCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowFreqCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QLowFreqCommonParasDlg,
      qt_meta_data_QLowFreqCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowFreqCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowFreqCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowFreqCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowFreqCommonParasDlg))
        return static_cast<void*>(const_cast< QLowFreqCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QLowFreqCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
