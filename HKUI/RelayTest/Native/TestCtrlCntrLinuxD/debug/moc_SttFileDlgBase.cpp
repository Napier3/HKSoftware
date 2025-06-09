/****************************************************************************
** Meta object code from reading C++ file 'SttFileDlgBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/PopupDialog/SttFileDlgBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttFileDlgBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttFileDlgBase[] = {

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
      19,   17,   16,   16, 0x0a,
      69,   62,   16,   16, 0x0a,
     104,   16,   16,   16, 0x0a,
     121,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttFileDlgBase[] = {
    "QSttFileDlgBase\0\0,\0"
    "slot_TreeItemClicked(QTreeWidgetItem*,int)\0"
    "nState\0slot_ExternalPathStateChanged(int)\0"
    "slot_OKClicked()\0slot_CancelClicked()\0"
};

void QSttFileDlgBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttFileDlgBase *_t = static_cast<QSttFileDlgBase *>(_o);
        switch (_id) {
        case 0: _t->slot_TreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_ExternalPathStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_OKClicked(); break;
        case 3: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttFileDlgBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFileDlgBase::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttFileDlgBase,
      qt_meta_data_QSttFileDlgBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFileDlgBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFileDlgBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFileDlgBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFileDlgBase))
        return static_cast<void*>(const_cast< QSttFileDlgBase*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttFileDlgBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
