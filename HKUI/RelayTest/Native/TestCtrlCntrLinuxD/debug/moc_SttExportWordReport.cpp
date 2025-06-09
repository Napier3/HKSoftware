/****************************************************************************
** Meta object code from reading C++ file 'SttExportWordReport.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/ExportWordRpt/SttExportWordReport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttExportWordReport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttExportWordReport[] = {

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
      22,   21,   21,   21, 0x0a,
      37,   21,   21,   21, 0x0a,
      54,   21,   21,   21, 0x0a,
      73,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttExportWordReport[] = {
    "QSttExportWordReport\0\0slot_SelPath()\0"
    "slot_ExportRpt()\0slot_PrevClicked()\0"
    "slot_NextClicked()\0"
};

void QSttExportWordReport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttExportWordReport *_t = static_cast<QSttExportWordReport *>(_o);
        switch (_id) {
        case 0: _t->slot_SelPath(); break;
        case 1: _t->slot_ExportRpt(); break;
        case 2: _t->slot_PrevClicked(); break;
        case 3: _t->slot_NextClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttExportWordReport::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttExportWordReport::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttExportWordReport,
      qt_meta_data_QSttExportWordReport, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttExportWordReport::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttExportWordReport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttExportWordReport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttExportWordReport))
        return static_cast<void*>(const_cast< QSttExportWordReport*>(this));
    if (!strcmp(_clname, "CExBaseListTreeOptrInterface"))
        return static_cast< CExBaseListTreeOptrInterface*>(const_cast< QSttExportWordReport*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttExportWordReport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
