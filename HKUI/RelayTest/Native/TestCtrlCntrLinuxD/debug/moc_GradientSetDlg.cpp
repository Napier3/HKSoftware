/****************************************************************************
** Meta object code from reading C++ file 'GradientSetDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/Gradient/GradientSetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GradientSetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GradientSetDlg[] = {

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
      16,   15,   15,   15, 0x05,
      32,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   15,   15,   15, 0x0a,
      81,   15,   15,   15, 0x0a,
     108,   15,   15,   15, 0x0a,
     131,   15,   15,   15, 0x0a,
     155,   15,   15,   15, 0x0a,
     172,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GradientSetDlg[] = {
    "GradientSetDlg\0\0sig_OkClicked()\0"
    "sig_CancelClicked()\0slot_GradientLinearClicked()\0"
    "slot_GradientStepClicked()\0"
    "slot_StepTimeChanged()\0slot_StepTimeKeyBoard()\0"
    "slot_OKClicked()\0slot_CancelClicked()\0"
};

void GradientSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GradientSetDlg *_t = static_cast<GradientSetDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_OkClicked(); break;
        case 1: _t->sig_CancelClicked(); break;
        case 2: _t->slot_GradientLinearClicked(); break;
        case 3: _t->slot_GradientStepClicked(); break;
        case 4: _t->slot_StepTimeChanged(); break;
        case 5: _t->slot_StepTimeKeyBoard(); break;
        case 6: _t->slot_OKClicked(); break;
        case 7: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GradientSetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GradientSetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GradientSetDlg,
      qt_meta_data_GradientSetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GradientSetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GradientSetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GradientSetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GradientSetDlg))
        return static_cast<void*>(const_cast< GradientSetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int GradientSetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void GradientSetDlg::sig_OkClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GradientSetDlg::sig_CancelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
