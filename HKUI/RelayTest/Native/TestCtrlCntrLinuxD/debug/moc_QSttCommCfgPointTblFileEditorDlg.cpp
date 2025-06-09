/****************************************************************************
** Meta object code from reading C++ file 'QSttCommCfgPointTblFileEditorDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommConfigurationDlg/PointTblFile/QSttCommCfgPointTblFileEditorDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttCommCfgPointTblFileEditorDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GeneralTab[] = {
    "GeneralTab\0"
};

void GeneralTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GeneralTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneralTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GeneralTab,
      qt_meta_data_GeneralTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralTab))
        return static_cast<void*>(const_cast< GeneralTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int GeneralTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QSttCommCfgPointTblFileEditorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x0a,
      51,   33,   33,   33, 0x0a,
      72,   33,   33,   33, 0x0a,
      91,   33,   33,   33, 0x0a,
     113,   33,   33,   33, 0x0a,
     135,   33,   33,   33, 0x0a,
     161,   33,   33,   33, 0x0a,
     186,   33,   33,   33, 0x0a,
     211,   33,   33,   33, 0x0a,
     246,  235,   33,   33, 0x0a,
     276,   33,   33,   33, 0x0a,
     306,  235,   33,   33, 0x0a,
     340,   33,   33,   33, 0x0a,
     371,   33,   33,   33, 0x0a,
     403,   33,   33,   33, 0x0a,
     455,  436,   33,   33, 0x0a,
     504,  491,   33,   33, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttCommCfgPointTblFileEditorDlg[] = {
    "QSttCommCfgPointTblFileEditorDlg\0\0"
    "slot_OKClicked()\0slot_CancelClicked()\0"
    "slot_SaveClicked()\0slot_Import_Clicked()\0"
    "slot_Export_Clicked()\0slot_DelCurrRow_Clicked()\0"
    "slot_InsertRow_Clicked()\0"
    "slot_AppendRow_Clicked()\0"
    "slot_ApplyAll_Clicked()\0nCurrIndex\0"
    "slot_CrtChangedTabWidget(int)\0"
    "slot_StartAddrEdit_Finished()\0"
    "slot_IntervalSetComboChanged(int)\0"
    "slot_IntervalSetTableChanged()\0"
    "slot_RightParaSetTableChanged()\0"
    "slot_RightTeleMearTableChanged()\0"
    "nRow,nCol,strValue\0"
    "slot_ChangedAdress(int,int,QString)\0"
    "bApplyAllFlg\0slot_ApplyAll(bool)\0"
};

void QSttCommCfgPointTblFileEditorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttCommCfgPointTblFileEditorDlg *_t = static_cast<QSttCommCfgPointTblFileEditorDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_OKClicked(); break;
        case 1: _t->slot_CancelClicked(); break;
        case 2: _t->slot_SaveClicked(); break;
        case 3: _t->slot_Import_Clicked(); break;
        case 4: _t->slot_Export_Clicked(); break;
        case 5: _t->slot_DelCurrRow_Clicked(); break;
        case 6: _t->slot_InsertRow_Clicked(); break;
        case 7: _t->slot_AppendRow_Clicked(); break;
        case 8: _t->slot_ApplyAll_Clicked(); break;
        case 9: _t->slot_CrtChangedTabWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_StartAddrEdit_Finished(); break;
        case 11: _t->slot_IntervalSetComboChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_IntervalSetTableChanged(); break;
        case 13: _t->slot_RightParaSetTableChanged(); break;
        case 14: _t->slot_RightTeleMearTableChanged(); break;
        case 15: _t->slot_ChangedAdress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 16: _t->slot_ApplyAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttCommCfgPointTblFileEditorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttCommCfgPointTblFileEditorDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttCommCfgPointTblFileEditorDlg,
      qt_meta_data_QSttCommCfgPointTblFileEditorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttCommCfgPointTblFileEditorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttCommCfgPointTblFileEditorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttCommCfgPointTblFileEditorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttCommCfgPointTblFileEditorDlg))
        return static_cast<void*>(const_cast< QSttCommCfgPointTblFileEditorDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttCommCfgPointTblFileEditorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
