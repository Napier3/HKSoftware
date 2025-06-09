/****************************************************************************
** Meta object code from reading C++ file 'RecloseAccBinarySignalDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/RecloseAcc/RecloseAccBinarySignalDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecloseAccBinarySignalDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRecloseAccBinarySignalDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x0a,
      49,   27,   27,   27, 0x0a,
      80,   74,   27,   27, 0x08,
     123,   74,   27,   27, 0x08,
     173,   27,   27,   27, 0x08,
     215,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QRecloseAccBinarySignalDlg[] = {
    "QRecloseAccBinarySignalDlg\0\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
    "index\0on_m_cbbBinSelect_currentIndexChanged(int)\0"
    "on_m_cbbOutputSwitchMode_currentIndexChanged(int)\0"
    "on_m_editOutputKeepTime_editingFinished()\0"
    "on_m_editOutputDelayTime_editingFinished()\0"
};

void QRecloseAccBinarySignalDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRecloseAccBinarySignalDlg *_t = static_cast<QRecloseAccBinarySignalDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOk_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->on_m_cbbBinSelect_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_cbbOutputSwitchMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_m_editOutputKeepTime_editingFinished(); break;
        case 5: _t->on_m_editOutputDelayTime_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QRecloseAccBinarySignalDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRecloseAccBinarySignalDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QRecloseAccBinarySignalDlg,
      qt_meta_data_QRecloseAccBinarySignalDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRecloseAccBinarySignalDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRecloseAccBinarySignalDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRecloseAccBinarySignalDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRecloseAccBinarySignalDlg))
        return static_cast<void*>(const_cast< QRecloseAccBinarySignalDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QRecloseAccBinarySignalDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
