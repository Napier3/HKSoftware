/****************************************************************************
** Meta object code from reading C++ file 'TestMacroToolDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/TestMacroTool/TestMacroToolDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestMacroToolDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTestMacroToolDlg[] = {

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
      28,   19,   18,   18, 0x08,
      49,   19,   18,   18, 0x08,
      71,   19,   18,   18, 0x08,
      93,   19,   18,   18, 0x08,
     115,   19,   18,   18, 0x08,
     140,   19,   18,   18, 0x08,
     166,   19,   18,   18, 0x08,
     191,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QTestMacroToolDlg[] = {
    "QTestMacroToolDlg\0\0bChecked\0"
    "OnTreeBtnClick(bool)\0OnTreeBtnExpand(bool)\0"
    "OnTableBtnClick(bool)\0OnBtnCloseClick(bool)\0"
    "OnBtnAddAfterClick(bool)\0"
    "OnBtnAddBeforeClick(bool)\0"
    "OnBtnAddChildClick(bool)\0"
    "on_m_chkRptTitle_clicked()\0"
};

void QTestMacroToolDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QTestMacroToolDlg *_t = static_cast<QTestMacroToolDlg *>(_o);
        switch (_id) {
        case 0: _t->OnTreeBtnClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->OnTreeBtnExpand((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->OnTableBtnClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->OnBtnCloseClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->OnBtnAddAfterClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->OnBtnAddBeforeClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->OnBtnAddChildClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_m_chkRptTitle_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QTestMacroToolDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QTestMacroToolDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QTestMacroToolDlg,
      qt_meta_data_QTestMacroToolDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTestMacroToolDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTestMacroToolDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTestMacroToolDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTestMacroToolDlg))
        return static_cast<void*>(const_cast< QTestMacroToolDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QTestMacroToolDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
