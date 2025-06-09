/****************************************************************************
** Meta object code from reading C++ file 'SttFileMoveDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/FileMngr/SttFileMoveDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttFileMoveDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttFileMoveDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x05,
      48,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   16,   16,   16, 0x0a,
      95,   16,   16,   16, 0x0a,
     116,   16,   16,   16, 0x0a,
     137,   16,   16,   16, 0x0a,
     156,   17,   16,   16, 0x0a,
     183,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttFileMoveDlg[] = {
    "QSttFileMoveDlg\0\0bRet\0sig_UpdateImprotFile(int)\0"
    "sig_UpdateExportFile(int)\0"
    "slot_ImportClicked()\0slot_ExportClicked()\0"
    "slot_DeleteClicked()\0slot_BackClicked()\0"
    "slot_UpdateImprotFile(int)\0"
    "slot_UpdateExportFile(int)\0"
};

void QSttFileMoveDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttFileMoveDlg *_t = static_cast<QSttFileMoveDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateImprotFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_UpdateExportFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_ImportClicked(); break;
        case 3: _t->slot_ExportClicked(); break;
        case 4: _t->slot_DeleteClicked(); break;
        case 5: _t->slot_BackClicked(); break;
        case 6: _t->slot_UpdateImprotFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_UpdateExportFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttFileMoveDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFileMoveDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttFileMoveDlg,
      qt_meta_data_QSttFileMoveDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFileMoveDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFileMoveDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFileMoveDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFileMoveDlg))
        return static_cast<void*>(const_cast< QSttFileMoveDlg*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttFileMoveDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttFileMoveDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QSttFileMoveDlg::sig_UpdateImprotFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSttFileMoveDlg::sig_UpdateExportFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
