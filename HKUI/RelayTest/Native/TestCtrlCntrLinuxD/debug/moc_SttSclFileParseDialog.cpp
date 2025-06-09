/****************************************************************************
** Meta object code from reading C++ file 'SttSclFileParseDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttSclFileParseDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttSclFileParseDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttSclFileParseDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   23,   23,   23, 0x09,
      78,   23,   23,   23, 0x09,
     105,   23,   23,   23, 0x09,
     135,   23,   23,   23, 0x09,
     171,  159,   23,   23, 0x09,
     214,   23,   23,   23, 0x09,
     242,   23,   23,   23, 0x09,
     270,   23,   23,   23, 0x0a,
     309,  299,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttSclFileParseDialog[] = {
    "QSttSclFileParseDialog\0\0"
    "sig_IecCfgDataMngrUpdate()\0"
    "slot_OneKeyCfgBtnClicked()\0"
    "slot_SCLSelectBtnClicked()\0"
    "slot_ImportIecCfgBtnClicked()\0"
    "slot_CancelBtnClicked()\0item,column\0"
    "slot_TreeItemClicked(QTreeWidgetItem*,int)\0"
    "slot_IedSearchtextclicked()\0"
    "slot_IedSearchtextChanged()\0"
    "slot_UpdateSelectCtrlsGrid()\0pos,index\0"
    "slot_UpdateSketchMapWidgetSize(int,int)\0"
};

void QSttSclFileParseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttSclFileParseDialog *_t = static_cast<QSttSclFileParseDialog *>(_o);
        switch (_id) {
        case 0: _t->sig_IecCfgDataMngrUpdate(); break;
        case 1: _t->slot_OneKeyCfgBtnClicked(); break;
        case 2: _t->slot_SCLSelectBtnClicked(); break;
        case 3: _t->slot_ImportIecCfgBtnClicked(); break;
        case 4: _t->slot_CancelBtnClicked(); break;
        case 5: _t->slot_TreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slot_IedSearchtextclicked(); break;
        case 7: _t->slot_IedSearchtextChanged(); break;
        case 8: _t->slot_UpdateSelectCtrlsGrid(); break;
        case 9: _t->slot_UpdateSketchMapWidgetSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttSclFileParseDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttSclFileParseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttSclFileParseDialog,
      qt_meta_data_QSttSclFileParseDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttSclFileParseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttSclFileParseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttSclFileParseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttSclFileParseDialog))
        return static_cast<void*>(const_cast< QSttSclFileParseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttSclFileParseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QSttSclFileParseDialog::sig_IecCfgDataMngrUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
