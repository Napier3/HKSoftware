/****************************************************************************
** Meta object code from reading C++ file 'SttIntelBoutToGinParaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/GooseParaWidget/SttIntelBoutToGinParaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIntelBoutToGinParaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIntelBoutToGinParaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x05,
      73,   53,   29,   29, 0x05,
     116,   97,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
     143,   29,   29,   29, 0x09,
     167,   53,   29,   29, 0x09,
     213,  192,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIntelBoutToGinParaWidget[] = {
    "QSttIntelBoutToGinParaWidget\0\0"
    "sig_GooseDataChanged()\0nbout,bStateChanged\0"
    "sig_setBinOut(int,bool)\0nRowIndex,fActTime\0"
    "sig_GinRowIndex(int,float)\0"
    "slot_GooseDataChanged()\0"
    "slot_setBinOut(int,bool)\0nRowIndex,m_fActTime\0"
    "slot_GinRowIndex(int,float)\0"
};

void QSttIntelBoutToGinParaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIntelBoutToGinParaWidget *_t = static_cast<QSttIntelBoutToGinParaWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_GooseDataChanged(); break;
        case 1: _t->sig_setBinOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->sig_GinRowIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->slot_GooseDataChanged(); break;
        case 4: _t->slot_setBinOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->slot_GinRowIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIntelBoutToGinParaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIntelBoutToGinParaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIntelBoutToGinParaWidget,
      qt_meta_data_QSttIntelBoutToGinParaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIntelBoutToGinParaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIntelBoutToGinParaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIntelBoutToGinParaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIntelBoutToGinParaWidget))
        return static_cast<void*>(const_cast< QSttIntelBoutToGinParaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIntelBoutToGinParaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QSttIntelBoutToGinParaWidget::sig_GooseDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttIntelBoutToGinParaWidget::sig_setBinOut(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSttIntelBoutToGinParaWidget::sig_GinRowIndex(int _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
