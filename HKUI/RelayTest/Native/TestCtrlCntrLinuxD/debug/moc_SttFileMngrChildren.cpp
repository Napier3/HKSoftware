/****************************************************************************
** Meta object code from reading C++ file 'SttFileMngrChildren.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/FileMngr/SttFileMngrChildren.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttFileMngrChildren.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttFileMngrChildren[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      45,   40,   21,   21, 0x05,
      71,   40,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   21,   21,   21, 0x0a,
     118,   21,   21,   21, 0x0a,
     139,   21,   21,   21, 0x0a,
     160,   21,   21,   21, 0x0a,
     179,   21,   21,   21, 0x0a,
     198,   40,   21,   21, 0x0a,
     225,   40,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttFileMngrChildren[] = {
    "QSttFileMngrChildren\0\0sig_ShowXFolder()\0"
    "bRet\0sig_UpdateImprotFile(int)\0"
    "sig_UpdateExportFile(int)\0"
    "slot_ImportClicked()\0slot_ExportClicked()\0"
    "slot_DeleteClicked()\0slot_BackClicked()\0"
    "slot_ShowXFolder()\0slot_UpdateImprotFile(int)\0"
    "slot_UpdateExportFile(int)\0"
};

void QSttFileMngrChildren::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttFileMngrChildren *_t = static_cast<QSttFileMngrChildren *>(_o);
        switch (_id) {
        case 0: _t->sig_ShowXFolder(); break;
        case 1: _t->sig_UpdateImprotFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_UpdateExportFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_ImportClicked(); break;
        case 4: _t->slot_ExportClicked(); break;
        case 5: _t->slot_DeleteClicked(); break;
        case 6: _t->slot_BackClicked(); break;
        case 7: _t->slot_ShowXFolder(); break;
        case 8: _t->slot_UpdateImprotFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_UpdateExportFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttFileMngrChildren::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFileMngrChildren::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttFileMngrChildren,
      qt_meta_data_QSttFileMngrChildren, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFileMngrChildren::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFileMngrChildren::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFileMngrChildren::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFileMngrChildren))
        return static_cast<void*>(const_cast< QSttFileMngrChildren*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttFileMngrChildren*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttFileMngrChildren::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QSttFileMngrChildren::sig_ShowXFolder()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttFileMngrChildren::sig_UpdateImprotFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSttFileMngrChildren::sig_UpdateExportFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
