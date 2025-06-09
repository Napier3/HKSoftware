/****************************************************************************
** Meta object code from reading C++ file 'DiffCBOpResultEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/DiffCBOp/DiffCBOpResultEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiffCBOpResultEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDiffCBOpResultEstimateDlg[] = {

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
      28,   27,   27,   27, 0x0a,
      49,   27,   27,   27, 0x0a,
      81,   74,   27,   27, 0x0a,
     124,   27,   27,   27, 0x0a,
     155,   27,   27,   27, 0x0a,
     188,   27,   27,   27, 0x0a,
     222,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDiffCBOpResultEstimateDlg[] = {
    "QDiffCBOpResultEstimateDlg\0\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
    "nIndex\0on_m_cmbFluatType_currentIndexChanged(int)\0"
    "on_m_txtRel3_editingFinished()\0"
    "on_m_txtPlus_3_editingFinished()\0"
    "on_m_txtMinus_3_editingFinished()\0"
    "on_m_EditSetting_editingFinished()\0"
};

void QDiffCBOpResultEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDiffCBOpResultEstimateDlg *_t = static_cast<QDiffCBOpResultEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOK_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->on_m_cmbFluatType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_txtRel3_editingFinished(); break;
        case 4: _t->on_m_txtPlus_3_editingFinished(); break;
        case 5: _t->on_m_txtMinus_3_editingFinished(); break;
        case 6: _t->on_m_EditSetting_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDiffCBOpResultEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffCBOpResultEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDiffCBOpResultEstimateDlg,
      qt_meta_data_QDiffCBOpResultEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffCBOpResultEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffCBOpResultEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffCBOpResultEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffCBOpResultEstimateDlg))
        return static_cast<void*>(const_cast< QDiffCBOpResultEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDiffCBOpResultEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
