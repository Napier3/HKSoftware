/****************************************************************************
** Meta object code from reading C++ file 'GradientSettingDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Gradient/GradientSettingDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GradientSettingDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGradientSettingDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      42,   20,   20,   20, 0x08,
      67,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGradientSettingDlg[] = {
    "QGradientSettingDlg\0\0on_m_btnOK_clicked()\0"
    "on_m_btnCancel_clicked()\0"
    "slot_ck_BinaryInStateChanged(int)\0"
};

void QGradientSettingDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QGradientSettingDlg *_t = static_cast<QGradientSettingDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnOK_clicked(); break;
        case 1: _t->on_m_btnCancel_clicked(); break;
        case 2: _t->slot_ck_BinaryInStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QGradientSettingDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QGradientSettingDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QGradientSettingDlg,
      qt_meta_data_QGradientSettingDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGradientSettingDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGradientSettingDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGradientSettingDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGradientSettingDlg))
        return static_cast<void*>(const_cast< QGradientSettingDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QGradientSettingDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
