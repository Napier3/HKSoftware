/****************************************************************************
** Meta object code from reading C++ file 'QSttManualBinBoutDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Manual/QSttManualBinBoutDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttManualBinBoutDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttManualBinBoutDlg[] = {

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
      22,   21,   21,   21, 0x08,
      43,   21,   21,   21, 0x08,
      68,   21,   21,   21, 0x08,
     102,   21,   21,   21, 0x08,
     126,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttManualBinBoutDlg[] = {
    "QSttManualBinBoutDlg\0\0on_m_btnOK_clicked()\0"
    "on_m_btnCancel_clicked()\0"
    "slot_ck_BinaryInStateChanged(int)\0"
    "on_m_editDelayChanged()\0"
    "on_m_editDelayed_editingFinished()\0"
};

void QSttManualBinBoutDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttManualBinBoutDlg *_t = static_cast<QSttManualBinBoutDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOK_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->slot_ck_BinaryInStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_editDelayChanged(); break;
        case 4: _t->on_m_editDelayed_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttManualBinBoutDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttManualBinBoutDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttManualBinBoutDlg,
      qt_meta_data_QSttManualBinBoutDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttManualBinBoutDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttManualBinBoutDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttManualBinBoutDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttManualBinBoutDlg))
        return static_cast<void*>(const_cast< QSttManualBinBoutDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttManualBinBoutDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
