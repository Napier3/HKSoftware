/****************************************************************************
** Meta object code from reading C++ file 'DistanceBinarysDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Distance/DistanceBinarysDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceBinarysDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceBinarysDlg[] = {

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
      27,   21,   20,   20, 0x08,
      72,   20,   20,   20, 0x08,
     108,   20,   20,   20, 0x08,
     143,   20,   20,   20, 0x08,
     164,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceBinarysDlg[] = {
    "QDistanceBinarysDlg\0\0index\0"
    "on_m_cmb_SwitchMode_currentIndexChanged(int)\0"
    "on_m_txtDelayTime_editingFinished()\0"
    "on_m_txtKeepTime_editingFinished()\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
};

void QDistanceBinarysDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceBinarysDlg *_t = static_cast<QDistanceBinarysDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_cmb_SwitchMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_m_txtDelayTime_editingFinished(); break;
        case 2: _t->on_m_txtKeepTime_editingFinished(); break;
        case 3: _t->on_m_btnOK_clicked(); break;
        case 4: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDistanceBinarysDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceBinarysDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDistanceBinarysDlg,
      qt_meta_data_QDistanceBinarysDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceBinarysDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceBinarysDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceBinarysDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceBinarysDlg))
        return static_cast<void*>(const_cast< QDistanceBinarysDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDistanceBinarysDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
