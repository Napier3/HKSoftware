/****************************************************************************
** Meta object code from reading C++ file 'ppcommconfigdlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/SMARTTESTINTERFACE/QT/CommConfigWidget/ppcommconfigdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ppcommconfigdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PpCommConfigDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      42,   16,   16,   16, 0x08,
      64,   16,   16,   16, 0x08,
      86,   16,   16,   16, 0x08,
     113,  108,   16,   16, 0x08,
     149,  108,   16,   16, 0x08,
     185,  108,   16,   16, 0x08,
     221,  108,   16,   16, 0x08,
     257,   16,   16,   16, 0x08,
     280,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PpCommConfigDlg[] = {
    "PpCommConfigDlg\0\0on_m_btnSerial_clicked()\0"
    "on_m_btnCms_clicked()\0on_m_btnNet_clicked()\0"
    "on_m_btnMms_clicked()\0arg1\0"
    "on_m_btnTcpServer_stateChanged(int)\0"
    "on_m_btnTcpClient_stateChanged(int)\0"
    "on_m_btnUdpServer_stateChanged(int)\0"
    "on_m_btnUdpClient_stateChanged(int)\0"
    "on_m_btnSave_clicked()\0on_m_btnCancel_clicked()\0"
};

void PpCommConfigDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PpCommConfigDlg *_t = static_cast<PpCommConfigDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnSerial_clicked(); break;
        case 1: _t->on_m_btnCms_clicked(); break;
        case 2: _t->on_m_btnNet_clicked(); break;
        case 3: _t->on_m_btnMms_clicked(); break;
        case 4: _t->on_m_btnTcpServer_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_m_btnTcpClient_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_m_btnUdpServer_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_m_btnUdpClient_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_btnSave_clicked(); break;
        case 9: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PpCommConfigDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PpCommConfigDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PpCommConfigDlg,
      qt_meta_data_PpCommConfigDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PpCommConfigDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PpCommConfigDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PpCommConfigDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PpCommConfigDlg))
        return static_cast<void*>(const_cast< PpCommConfigDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int PpCommConfigDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
