/****************************************************************************
** Meta object code from reading C++ file 'settingselectdlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SettingCtrls/settingselectdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingselectdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingSelectDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   18,   17,   17, 0x05,
      65,   17,   17,   17, 0x05,
      79,   17,   17,   17, 0x05,
      91,   17,   17,   17, 0x05,
     112,  106,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     135,  129,   17,   17, 0x0a,
     178,  171,   17,   17, 0x0a,
     207,   17,   17,   17, 0x08,
     239,   17,   17,   17, 0x08,
     270,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingSelectDlg[] = {
    "SettingSelectDlg\0\0sFormat,sName\0"
    "sig_ShowSetting(QString,QString)\0"
    "sig_Setting()\0sig_Clear()\0sig_ClearAll()\0"
    "bHide\0sig_Cannel(bool)\0pItem\0"
    "slot_SelectModeData(CExBaseObject*)\0"
    "sValue\0slot_SelectModeData(QString)\0"
    "on_pushButton_Setting_clicked()\0"
    "on_pushButton_cannel_clicked()\0"
    "on_pushButton_AllCannel_clicked()\0"
};

void SettingSelectDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SettingSelectDlg *_t = static_cast<SettingSelectDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_ShowSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sig_Setting(); break;
        case 2: _t->sig_Clear(); break;
        case 3: _t->sig_ClearAll(); break;
        case 4: _t->sig_Cannel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_SelectModeData((*reinterpret_cast< CExBaseObject*(*)>(_a[1]))); break;
        case 6: _t->slot_SelectModeData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_Setting_clicked(); break;
        case 8: _t->on_pushButton_cannel_clicked(); break;
        case 9: _t->on_pushButton_AllCannel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SettingSelectDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SettingSelectDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SettingSelectDlg,
      qt_meta_data_SettingSelectDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingSelectDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingSelectDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingSelectDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingSelectDlg))
        return static_cast<void*>(const_cast< SettingSelectDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SettingSelectDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void SettingSelectDlg::sig_ShowSetting(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingSelectDlg::sig_Setting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SettingSelectDlg::sig_Clear()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SettingSelectDlg::sig_ClearAll()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SettingSelectDlg::sig_Cannel(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
