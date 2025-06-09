/****************************************************************************
** Meta object code from reading C++ file 'SynBinarysDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynBinarysDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynBinarysDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynBinarysDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x08,
      62,   15,   15,   15, 0x08,
      99,   16,   15,   15, 0x08,
     138,   16,   15,   15, 0x08,
     177,   16,   15,   15, 0x08,
     216,   16,   15,   15, 0x08,
     256,   16,   15,   15, 0x08,
     297,   16,   15,   15, 0x08,
     338,   16,   15,   15, 0x08,
     379,   16,   15,   15, 0x08,
     420,   15,   15,   15, 0x08,
     441,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSynBinarysDlg[] = {
    "QSynBinarysDlg\0\0index\0"
    "on_m_cmbKStart_currentIndexChanged(int)\0"
    "on_m_lineCloseTime_editingFinished()\0"
    "on_m_cmbBout1_currentIndexChanged(int)\0"
    "on_m_cmbBout2_currentIndexChanged(int)\0"
    "on_m_cmbBout3_currentIndexChanged(int)\0"
    "on_m_cmbBinSyn_currentIndexChanged(int)\0"
    "on_m_cmbBinIncV_currentIndexChanged(int)\0"
    "on_m_cmbBinDecV_currentIndexChanged(int)\0"
    "on_m_cmbBinIncF_currentIndexChanged(int)\0"
    "on_m_cmbBinDecF_currentIndexChanged(int)\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QSynBinarysDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynBinarysDlg *_t = static_cast<QSynBinarysDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_cmbKStart_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_m_lineCloseTime_editingFinished(); break;
        case 2: _t->on_m_cmbBout1_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_cmbBout2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_m_cmbBout3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_m_cmbBinSyn_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_m_cmbBinIncV_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_m_cmbBinDecV_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_cmbBinIncF_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_m_cmbBinDecF_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_m_btnOK_clicked(); break;
        case 11: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSynBinarysDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynBinarysDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSynBinarysDlg,
      qt_meta_data_QSynBinarysDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynBinarysDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynBinarysDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynBinarysDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynBinarysDlg))
        return static_cast<void*>(const_cast< QSynBinarysDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSynBinarysDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
