/****************************************************************************
** Meta object code from reading C++ file 'SttIecConfigDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecConfigDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecConfigDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecConfigDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      48,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   20,   20,   20, 0x09,
      90,   20,   20,   20, 0x09,
     117,   20,   20,   20, 0x09,
     144,   20,   20,   20, 0x09,
     172,   20,   20,   20, 0x09,
     194,   20,   20,   20, 0x09,
     230,  218,   20,   20, 0x09,
     273,  218,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecConfigDialog[] = {
    "QSttIecConfigDialog\0\0sig_IecCfgDataMngrUpdate()\0"
    "sig_IecCfg_New()\0slot_OpenCfgBtnClicked()\0"
    "slot_SaveAsCfgBtnClicked()\0"
    "slot_ImportSCLBtnClicked()\0"
    "slot_IecCfgDataMngrUpdate()\0"
    "slot_SaveBtnClicked()\0slot_CancelBtnClicked()\0"
    "item,column\0slot_TreeItemClicked(QTreeWidgetItem*,int)\0"
    "slot_TreeItemChanged(QTreeWidgetItem*,int)\0"
};

void QSttIecConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecConfigDialog *_t = static_cast<QSttIecConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->sig_IecCfgDataMngrUpdate(); break;
        case 1: _t->sig_IecCfg_New(); break;
        case 2: _t->slot_OpenCfgBtnClicked(); break;
        case 3: _t->slot_SaveAsCfgBtnClicked(); break;
        case 4: _t->slot_ImportSCLBtnClicked(); break;
        case 5: _t->slot_IecCfgDataMngrUpdate(); break;
        case 6: _t->slot_SaveBtnClicked(); break;
        case 7: _t->slot_CancelBtnClicked(); break;
        case 8: _t->slot_TreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->slot_TreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecConfigDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttIecConfigDialog,
      qt_meta_data_QSttIecConfigDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecConfigDialog))
        return static_cast<void*>(const_cast< QSttIecConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttIecConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QSttIecConfigDialog::sig_IecCfgDataMngrUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttIecConfigDialog::sig_IecCfg_New()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
