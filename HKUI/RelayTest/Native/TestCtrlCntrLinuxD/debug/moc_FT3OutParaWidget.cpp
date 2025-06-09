/****************************************************************************
** Meta object code from reading C++ file 'FT3OutParaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/FT3Widget/FT3OutParaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FT3OutParaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QFT3OutParaWidget[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QFT3OutParaWidget[] = {
    "QFT3OutParaWidget\0\0sig_FT3DataChanged()\0"
    "slot_FT3DataChanged()\0"
};

void QFT3OutParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QFT3OutParaWidget *_t = static_cast<QFT3OutParaWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_FT3DataChanged(); break;
        case 1: _t->slot_FT3DataChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QFT3OutParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QFT3OutParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QFT3OutParaWidget,
      qt_meta_data_QFT3OutParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QFT3OutParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QFT3OutParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QFT3OutParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QFT3OutParaWidget))
        return static_cast<void*>(const_cast< QFT3OutParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QFT3OutParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QFT3OutParaWidget::sig_FT3DataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
