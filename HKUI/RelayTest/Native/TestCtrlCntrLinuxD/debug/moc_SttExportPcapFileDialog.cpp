/****************************************************************************
** Meta object code from reading C++ file 'SttExportPcapFileDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/SttExportPcapFileDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttExportPcapFileDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttExportPcapFileDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      51,   25,   25,   25, 0x0a,
      76,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttExportPcapFileDialog[] = {
    "QSttExportPcapFileDialog\0\0"
    "slot_SelSrcFileClicked()\0"
    "slot_StartTransClicked()\0slot_OKClicked()\0"
};

void QSttExportPcapFileDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttExportPcapFileDialog *_t = static_cast<QSttExportPcapFileDialog *>(_o);
        switch (_id) {
        case 0: _t->slot_SelSrcFileClicked(); break;
        case 1: _t->slot_StartTransClicked(); break;
        case 2: _t->slot_OKClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttExportPcapFileDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttExportPcapFileDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttExportPcapFileDialog,
      qt_meta_data_QSttExportPcapFileDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttExportPcapFileDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttExportPcapFileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttExportPcapFileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttExportPcapFileDialog))
        return static_cast<void*>(const_cast< QSttExportPcapFileDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttExportPcapFileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
