/****************************************************************************
** Meta object code from reading C++ file 'SttCustomSetDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SttCustomSetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttCustomSetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SttCustomSetDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      36,   16,   16,   16, 0x0a,
      55,   16,   16,   16, 0x0a,
      70,   16,   16,   16, 0x0a,
      95,   16,   16,   16, 0x0a,
     136,  119,   16,   16, 0x0a,
     183,  119,   16,   16, 0x0a,
     249,  234,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SttCustomSetDlg[] = {
    "SttCustomSetDlg\0\0slot_OnBtnRemove()\0"
    "slot_OnBtnAddBar()\0slot_OnClose()\0"
    "slot_OnBtnInsertBefore()\0"
    "slot_OnBtnInsertAfter()\0pSetItem,nColumn\0"
    "slot_MeunTreeItemClicked(QTreeWidgetItem*,int)\0"
    "slot_FolatBarTreeItemClicked(QTreeWidgetItem*,int)\0"
    "pTreeItem,nCol\0"
    "slot_FloatBarTreeItemDoubleClicked(QTreeWidgetItem*,int)\0"
};

void SttCustomSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SttCustomSetDlg *_t = static_cast<SttCustomSetDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OnBtnRemove(); break;
        case 1: _t->slot_OnBtnAddBar(); break;
        case 2: _t->slot_OnClose(); break;
        case 3: _t->slot_OnBtnInsertBefore(); break;
        case 4: _t->slot_OnBtnInsertAfter(); break;
        case 5: _t->slot_MeunTreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slot_FolatBarTreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->slot_FloatBarTreeItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SttCustomSetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SttCustomSetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SttCustomSetDlg,
      qt_meta_data_SttCustomSetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SttCustomSetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SttCustomSetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SttCustomSetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SttCustomSetDlg))
        return static_cast<void*>(const_cast< SttCustomSetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SttCustomSetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
