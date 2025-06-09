/****************************************************************************
** Meta object code from reading C++ file 'QPowerDirResultEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/QPowerDirResultEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPowerDirResultEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPowerDirResultEstimateDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x08,
      52,   27,   27,   27, 0x08,
      94,   84,   78,   27, 0x08,
     130,   27,   27,   27, 0x08,
     171,   27,   27,   27, 0x08,
     212,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPowerDirResultEstimateDlg[] = {
    "QPowerDirResultEstimateDlg\0\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0float\0"
    "pLineEdit\0on_lineEdit_TextChanged(QLineEdit*)\0"
    "slot_lneAbsoluteErrorEdit1_TextChanged()\0"
    "slot_lneAbsoluteErrorEdit2_TextChanged()\0"
    "slot_lneAbsoluteErrorEdit3_TextChanged()\0"
};

void QPowerDirResultEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPowerDirResultEstimateDlg *_t = static_cast<QPowerDirResultEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: { float _r = _t->on_lineEdit_TextChanged((*reinterpret_cast< QLineEdit*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 3: _t->slot_lneAbsoluteErrorEdit1_TextChanged(); break;
        case 4: _t->slot_lneAbsoluteErrorEdit2_TextChanged(); break;
        case 5: _t->slot_lneAbsoluteErrorEdit3_TextChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPowerDirResultEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPowerDirResultEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QPowerDirResultEstimateDlg,
      qt_meta_data_QPowerDirResultEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPowerDirResultEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPowerDirResultEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPowerDirResultEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPowerDirResultEstimateDlg))
        return static_cast<void*>(const_cast< QPowerDirResultEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QPowerDirResultEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
