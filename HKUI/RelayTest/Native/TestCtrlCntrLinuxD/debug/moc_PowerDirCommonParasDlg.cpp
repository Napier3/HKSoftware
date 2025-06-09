/****************************************************************************
** Meta object code from reading C++ file 'PowerDirCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/PowerDirCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PowerDirCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPowerDirCommonParasDlg[] = {

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
      25,   24,   24,   24, 0x08,
      65,   24,   24,   24, 0x08,
      97,   24,   24,   24, 0x08,
     129,   24,   24,   24, 0x08,
     165,   24,   24,   24, 0x08,
     186,   24,   24,   24, 0x08,
     211,   24,   24,   24, 0x08,
     250,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPowerDirCommonParasDlg[] = {
    "QPowerDirCommonParasDlg\0\0"
    "on_m_editPreFaultTime_editingFinished()\0"
    "on_m_editUPre_editingFinished()\0"
    "on_m_editIPre_editingFinished()\0"
    "on_m_editPreAngle_editingFinished()\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
    "on_m_editPrepareTime_editingFinished()\0"
    "on_m_editAngleMargin_editingFinished()\0"
};

void QPowerDirCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPowerDirCommonParasDlg *_t = static_cast<QPowerDirCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_editPreFaultTime_editingFinished(); break;
        case 1: _t->on_m_editUPre_editingFinished(); break;
        case 2: _t->on_m_editIPre_editingFinished(); break;
        case 3: _t->on_m_editPreAngle_editingFinished(); break;
        case 4: _t->on_m_btnOk_clicked(); break;
        case 5: _t->on_m_btnCancel_clicked(); break;
        case 6: _t->on_m_editPrepareTime_editingFinished(); break;
        case 7: _t->on_m_editAngleMargin_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QPowerDirCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPowerDirCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QPowerDirCommonParasDlg,
      qt_meta_data_QPowerDirCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPowerDirCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPowerDirCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPowerDirCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPowerDirCommonParasDlg))
        return static_cast<void*>(const_cast< QPowerDirCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QPowerDirCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
