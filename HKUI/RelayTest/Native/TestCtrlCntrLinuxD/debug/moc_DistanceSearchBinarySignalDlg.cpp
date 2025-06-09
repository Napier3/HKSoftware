/****************************************************************************
** Meta object code from reading C++ file 'DistanceSearchBinarySignalDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/DistanceSearch/DistanceSearchBinarySignalDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceSearchBinarySignalDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceSearchBinarySignalDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x0a,
      53,   31,   31,   31, 0x0a,
      78,   31,   31,   31, 0x0a,
     120,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceSearchBinarySignalDlg[] = {
    "QDistanceSearchBinarySignalDlg\0\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
    "on_m_editOutputKeepTime_editingFinished()\0"
    "on_m_editOutputDelayTime_editingFinished()\0"
};

void QDistanceSearchBinarySignalDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceSearchBinarySignalDlg *_t = static_cast<QDistanceSearchBinarySignalDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOk_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->on_m_editOutputKeepTime_editingFinished(); break;
        case 3: _t->on_m_editOutputDelayTime_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QDistanceSearchBinarySignalDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceSearchBinarySignalDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDistanceSearchBinarySignalDlg,
      qt_meta_data_QDistanceSearchBinarySignalDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceSearchBinarySignalDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceSearchBinarySignalDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceSearchBinarySignalDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceSearchBinarySignalDlg))
        return static_cast<void*>(const_cast< QDistanceSearchBinarySignalDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDistanceSearchBinarySignalDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
