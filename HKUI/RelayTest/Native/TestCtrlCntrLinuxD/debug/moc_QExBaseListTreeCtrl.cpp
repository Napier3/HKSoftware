/****************************************************************************
** Meta object code from reading C++ file 'QExBaseListTreeCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QExBaseListTreeCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CExBaseListTreeCtrl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   21,   20,   20, 0x05,
      65,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,  113,   20,   20, 0x0a,
     171,  113,   20,   20, 0x0a,
     214,  113,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CExBaseListTreeCtrl[] = {
    "CExBaseListTreeCtrl\0\0,\0"
    "sig_TreeItemClicked(QTreeWidgetItem*,int)\0"
    "sig_TreeItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "pTreeItem,nCol\0"
    "slot_TreeItemClicked(QTreeWidgetItem*,int)\0"
    "slot_TreeItemChanged(QTreeWidgetItem*,int)\0"
    "slot_TreeItemDoubleClicked(QTreeWidgetItem*,int)\0"
};

void CExBaseListTreeCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CExBaseListTreeCtrl *_t = static_cast<CExBaseListTreeCtrl *>(_o);
        switch (_id) {
        case 0: _t->sig_TreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_TreeItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_TreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_TreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_TreeItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CExBaseListTreeCtrl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CExBaseListTreeCtrl::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_CExBaseListTreeCtrl,
      qt_meta_data_CExBaseListTreeCtrl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CExBaseListTreeCtrl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CExBaseListTreeCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CExBaseListTreeCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CExBaseListTreeCtrl))
        return static_cast<void*>(const_cast< CExBaseListTreeCtrl*>(this));
    if (!strcmp(_clname, "CExBaseCtrlOptrInterface"))
        return static_cast< CExBaseCtrlOptrInterface*>(const_cast< CExBaseListTreeCtrl*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int CExBaseListTreeCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CExBaseListTreeCtrl::sig_TreeItemClicked(QTreeWidgetItem * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CExBaseListTreeCtrl::sig_TreeItemDoubleClicked(QTreeWidgetItem * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
