/****************************************************************************
** Meta object code from reading C++ file 'CurrInverAddMultDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/CurrInverseTime/CurrInverAddMultDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CurrInverAddMultDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCurrInverAddMultDlg[] = {

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
      28,   22,   21,   21, 0x08,
      68,   21,   21,   21, 0x08,
     105,   21,   21,   21, 0x08,
     143,   21,   21,   21, 0x08,
     173,   21,   21,   21, 0x08,
     212,   21,   21,   21, 0x08,
     251,   21,   21,   21, 0x08,
     289,   22,   21,   21, 0x08,
     333,   21,   21,   21, 0x08,
     367,   21,   21,   21, 0x08,
     399,   21,   21,   21, 0x08,
     432,   21,   21,   21, 0x08,
     452,   21,   21,   21, 0x08,
     476,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCurrInverAddMultDlg[] = {
    "QCurrInverAddMultDlg\0\0index\0"
    "on_m_cmbSelect_currentIndexChanged(int)\0"
    "on_m_lineFaultVolt_editingFinished()\0"
    "on_m_lineFaultAngle_editingFinished()\0"
    "on_m_lineHz_editingFinished()\0"
    "on_m_lineChangeStart_editingFinished()\0"
    "on_m_lineChangeFinal_editingFinished()\0"
    "on_m_lineChangeStep_editingFinished()\0"
    "on_m_cmbErrorLogic_currentIndexChanged(int)\0"
    "on_m_lineRelErr_editingFinished()\0"
    "on_m_linePlus_editingFinished()\0"
    "on_m_lineMinus_editingFinished()\0"
    "on_pbn_Ok_clicked()\0on_pbn_Cancel_clicked()\0"
    "slot_chb_faultTypeClicked()\0"
};

void QCurrInverAddMultDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCurrInverAddMultDlg *_t = static_cast<QCurrInverAddMultDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_cmbSelect_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_m_lineFaultVolt_editingFinished(); break;
        case 2: _t->on_m_lineFaultAngle_editingFinished(); break;
        case 3: _t->on_m_lineHz_editingFinished(); break;
        case 4: _t->on_m_lineChangeStart_editingFinished(); break;
        case 5: _t->on_m_lineChangeFinal_editingFinished(); break;
        case 6: _t->on_m_lineChangeStep_editingFinished(); break;
        case 7: _t->on_m_cmbErrorLogic_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_lineRelErr_editingFinished(); break;
        case 9: _t->on_m_linePlus_editingFinished(); break;
        case 10: _t->on_m_lineMinus_editingFinished(); break;
        case 11: _t->on_pbn_Ok_clicked(); break;
        case 12: _t->on_pbn_Cancel_clicked(); break;
        case 13: _t->slot_chb_faultTypeClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCurrInverAddMultDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCurrInverAddMultDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QCurrInverAddMultDlg,
      qt_meta_data_QCurrInverAddMultDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCurrInverAddMultDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCurrInverAddMultDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCurrInverAddMultDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCurrInverAddMultDlg))
        return static_cast<void*>(const_cast< QCurrInverAddMultDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QCurrInverAddMultDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
