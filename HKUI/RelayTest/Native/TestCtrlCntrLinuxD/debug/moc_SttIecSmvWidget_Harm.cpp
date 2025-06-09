/****************************************************************************
** Meta object code from reading C++ file 'SttIecSmvWidget_Harm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/SttIecSmvWidget_Harm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecSmvWidget_Harm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSttIecSmvWidget_Harm[] = {

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

static const char qt_meta_stringdata_CSttIecSmvWidget_Harm[] = {
    "CSttIecSmvWidget_Harm\0"
};

void CSttIecSmvWidget_Harm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CSttIecSmvWidget_Harm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSttIecSmvWidget_Harm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSttIecSmvWidget_Harm,
      qt_meta_data_CSttIecSmvWidget_Harm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSttIecSmvWidget_Harm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSttIecSmvWidget_Harm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSttIecSmvWidget_Harm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSttIecSmvWidget_Harm))
        return static_cast<void*>(const_cast< CSttIecSmvWidget_Harm*>(this));
    if (!strcmp(_clname, "CSttIecRcdFuncInterface"))
        return static_cast< CSttIecRcdFuncInterface*>(const_cast< CSttIecSmvWidget_Harm*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSttIecSmvWidget_Harm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
