/****************************************************************************
** Meta object code from reading C++ file 'FT3OutWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/FT3Widget/FT3OutWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FT3OutWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FT3OutWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FT3OutWidget[] = {
    "FT3OutWidget\0\0sig_FT3DataChanged()\0"
    "slot_dataChanged()\0"
};

void FT3OutWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FT3OutWidget *_t = static_cast<FT3OutWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_FT3DataChanged(); break;
        case 1: _t->slot_dataChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FT3OutWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FT3OutWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FT3OutWidget,
      qt_meta_data_FT3OutWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FT3OutWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FT3OutWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FT3OutWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FT3OutWidget))
        return static_cast<void*>(const_cast< FT3OutWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FT3OutWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FT3OutWidget::sig_FT3DataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
