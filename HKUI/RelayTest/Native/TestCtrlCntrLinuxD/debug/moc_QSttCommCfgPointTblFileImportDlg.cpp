/****************************************************************************
** Meta object code from reading C++ file 'QSttCommCfgPointTblFileImportDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommConfigurationDlg/PointTblFile/QSttCommCfgPointTblFileImportDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttCommCfgPointTblFileImportDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttCommCfgPointTblFileImportDlg[] = {

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
      34,   33,   33,   33, 0x0a,
      63,   33,   33,   33, 0x0a,
      90,   33,   33,   33, 0x0a,
     107,   33,   33,   33, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttCommCfgPointTblFileImportDlg[] = {
    "QSttCommCfgPointTblFileImportDlg\0\0"
    "slot_ImportPointBtnClicked()\0"
    "slot_EditPointBtnClicked()\0slot_OKClicked()\0"
    "slot_CancelClicked()\0"
};

void QSttCommCfgPointTblFileImportDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttCommCfgPointTblFileImportDlg *_t = static_cast<QSttCommCfgPointTblFileImportDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_ImportPointBtnClicked(); break;
        case 1: _t->slot_EditPointBtnClicked(); break;
        case 2: _t->slot_OKClicked(); break;
        case 3: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttCommCfgPointTblFileImportDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttCommCfgPointTblFileImportDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttCommCfgPointTblFileImportDlg,
      qt_meta_data_QSttCommCfgPointTblFileImportDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttCommCfgPointTblFileImportDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttCommCfgPointTblFileImportDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttCommCfgPointTblFileImportDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttCommCfgPointTblFileImportDlg))
        return static_cast<void*>(const_cast< QSttCommCfgPointTblFileImportDlg*>(this));
    if (!strcmp(_clname, "CExBaseListTreeOptrInterface"))
        return static_cast< CExBaseListTreeOptrInterface*>(const_cast< QSttCommCfgPointTblFileImportDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttCommCfgPointTblFileImportDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
