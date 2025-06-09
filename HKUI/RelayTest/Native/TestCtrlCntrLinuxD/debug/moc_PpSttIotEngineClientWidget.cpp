/****************************************************************************
** Meta object code from reading C++ file 'PpSttIotEngineClientWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/SMARTTESTINTERFACE/QT/PpSttIotEngineClientWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PpSttIotEngineClientWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPpSttIotEngineClientWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   29,   28,   28, 0x05,
      73,   29,   28,   28, 0x05,
     108,   29,   28,   28, 0x05,
     151,  142,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     183,   28,   28,   28, 0x08,
     214,   28,   28,   28, 0x08,
     244,   28,   28,   28, 0x08,
     276,   28,   28,   28, 0x08,
     300,   28,   28,   28, 0x08,
     329,   28,   28,   28, 0x08,
     359,   28,   28,   28, 0x08,
     389,   28,   28,   28, 0x08,
     419,   28,   28,   28, 0x08,
     450,   28,   28,   28, 0x08,
     477,   28,   28,   28, 0x08,
     505,   28,   28,   28, 0x08,
     532,   28,   28,   28, 0x08,
     561,   28,   28,   28, 0x08,
     591,   28,   28,   28, 0x08,
     621,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPpSttIotEngineClientWidget[] = {
    "QPpSttIotEngineClientWidget\0\0wParam,lParam\0"
    "sig_OnCommCommandMsg(int,int)\0"
    "sig_OnEngineSystemMessage(int,int)\0"
    "sig_OnEngineEventMessage(int,int)\0"
    "pCommCfg\0sig_OnConfigDevice(CDataGroup*)\0"
    "on_m_btnConfigDevice_clicked()\0"
    "on_m_btnCloseDevice_clicked()\0"
    "on_m_btnConnectDevice_clicked()\0"
    "on_m_btnReset_clicked()\0"
    "on_m_btnEnumDevice_clicked()\0"
    "on_m_btnEnumLDevice_clicked()\0"
    "on_m_btnEnumDataset_clicked()\0"
    "on_m_btnReadDataset_clicked()\0"
    "on_m_btnWriteDataset_clicked()\0"
    "on_m_btnReadZone_clicked()\0"
    "on_m_btnWriteZone_clicked()\0"
    "on_m_btnStartRpt_clicked()\0"
    "on_m_btnStopReport_clicked()\0"
    "on_m_btnOpenDvmFile_clicked()\0"
    "on_m_btnSaveDvmFile_clicked()\0"
    "on_m_btnAddDevice_clicked()\0"
};

void QPpSttIotEngineClientWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPpSttIotEngineClientWidget *_t = static_cast<QPpSttIotEngineClientWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_OnCommCommandMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_OnEngineSystemMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sig_OnEngineEventMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->sig_OnConfigDevice((*reinterpret_cast< CDataGroup*(*)>(_a[1]))); break;
        case 4: _t->on_m_btnConfigDevice_clicked(); break;
        case 5: _t->on_m_btnCloseDevice_clicked(); break;
        case 6: _t->on_m_btnConnectDevice_clicked(); break;
        case 7: _t->on_m_btnReset_clicked(); break;
        case 8: _t->on_m_btnEnumDevice_clicked(); break;
        case 9: _t->on_m_btnEnumLDevice_clicked(); break;
        case 10: _t->on_m_btnEnumDataset_clicked(); break;
        case 11: _t->on_m_btnReadDataset_clicked(); break;
        case 12: _t->on_m_btnWriteDataset_clicked(); break;
        case 13: _t->on_m_btnReadZone_clicked(); break;
        case 14: _t->on_m_btnWriteZone_clicked(); break;
        case 15: _t->on_m_btnStartRpt_clicked(); break;
        case 16: _t->on_m_btnStopReport_clicked(); break;
        case 17: _t->on_m_btnOpenDvmFile_clicked(); break;
        case 18: _t->on_m_btnSaveDvmFile_clicked(); break;
        case 19: _t->on_m_btnAddDevice_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPpSttIotEngineClientWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPpSttIotEngineClientWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QPpSttIotEngineClientWidget,
      qt_meta_data_QPpSttIotEngineClientWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPpSttIotEngineClientWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPpSttIotEngineClientWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPpSttIotEngineClientWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPpSttIotEngineClientWidget))
        return static_cast<void*>(const_cast< QPpSttIotEngineClientWidget*>(this));
    if (!strcmp(_clname, "CExBaseListTreeOptrInterface"))
        return static_cast< CExBaseListTreeOptrInterface*>(const_cast< QPpSttIotEngineClientWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QPpSttIotEngineClientWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void QPpSttIotEngineClientWidget::sig_OnCommCommandMsg(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QPpSttIotEngineClientWidget::sig_OnEngineSystemMessage(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QPpSttIotEngineClientWidget::sig_OnEngineEventMessage(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QPpSttIotEngineClientWidget::sig_OnConfigDevice(CDataGroup * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
