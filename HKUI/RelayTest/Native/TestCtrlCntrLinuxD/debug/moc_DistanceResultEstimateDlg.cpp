/****************************************************************************
** Meta object code from reading C++ file 'DistanceResultEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Distance/DistanceResultEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceResultEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceResultEstimateDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x08,
      49,   27,   27,   27, 0x08,
      74,   27,   27,   27, 0x08,
     105,   27,   27,   27, 0x08,
     138,   27,   27,   27, 0x08,
     172,   27,   27,   27, 0x08,
     203,   27,   27,   27, 0x08,
     236,   27,   27,   27, 0x08,
     270,   27,   27,   27, 0x08,
     301,   27,   27,   27, 0x08,
     334,   27,   27,   27, 0x08,
     368,   27,   27,   27, 0x08,
     399,   27,   27,   27, 0x08,
     432,   27,   27,   27, 0x08,
     466,   27,   27,   27, 0x08,
     497,   27,   27,   27, 0x08,
     530,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceResultEstimateDlg[] = {
    "QDistanceResultEstimateDlg\0\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
    "on_m_txtRel1_editingFinished()\0"
    "on_m_txtPlus_1_editingFinished()\0"
    "on_m_txtMinus_1_editingFinished()\0"
    "on_m_txtRel2_editingFinished()\0"
    "on_m_txtPlus_2_editingFinished()\0"
    "on_m_txtMinus_2_editingFinished()\0"
    "on_m_txtRel3_editingFinished()\0"
    "on_m_txtPlus_3_editingFinished()\0"
    "on_m_txtMinus_3_editingFinished()\0"
    "on_m_txtRel4_editingFinished()\0"
    "on_m_txtPlus_4_editingFinished()\0"
    "on_m_txtMinus_4_editingFinished()\0"
    "on_m_txtRel5_editingFinished()\0"
    "on_m_txtPlus_5_editingFinished()\0"
    "on_m_txtMinus_5_editingFinished()\0"
};

void QDistanceResultEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceResultEstimateDlg *_t = static_cast<QDistanceResultEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOK_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->on_m_txtRel1_editingFinished(); break;
        case 3: _t->on_m_txtPlus_1_editingFinished(); break;
        case 4: _t->on_m_txtMinus_1_editingFinished(); break;
        case 5: _t->on_m_txtRel2_editingFinished(); break;
        case 6: _t->on_m_txtPlus_2_editingFinished(); break;
        case 7: _t->on_m_txtMinus_2_editingFinished(); break;
        case 8: _t->on_m_txtRel3_editingFinished(); break;
        case 9: _t->on_m_txtPlus_3_editingFinished(); break;
        case 10: _t->on_m_txtMinus_3_editingFinished(); break;
        case 11: _t->on_m_txtRel4_editingFinished(); break;
        case 12: _t->on_m_txtPlus_4_editingFinished(); break;
        case 13: _t->on_m_txtMinus_4_editingFinished(); break;
        case 14: _t->on_m_txtRel5_editingFinished(); break;
        case 15: _t->on_m_txtPlus_5_editingFinished(); break;
        case 16: _t->on_m_txtMinus_5_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QDistanceResultEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceResultEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDistanceResultEstimateDlg,
      qt_meta_data_QDistanceResultEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceResultEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceResultEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceResultEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceResultEstimateDlg))
        return static_cast<void*>(const_cast< QDistanceResultEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDistanceResultEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
