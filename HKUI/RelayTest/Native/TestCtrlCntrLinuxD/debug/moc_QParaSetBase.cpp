/****************************************************************************
** Meta object code from reading C++ file 'QParaSetBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/ChannelParaSet/QParaSetBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QParaSetBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QParaSetBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      56,   14,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QParaSetBase[] = {
    "QParaSetBase\0\0moudleType,channelNum,valueFlag,datavalue\0"
    "slot_ChannelValueChanged(MOUDLEType,int,int,float)\0"
};

void QParaSetBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QParaSetBase *_t = static_cast<QParaSetBase *>(_o);
        switch (_id) {
        case 0: _t->slot_ChannelValueChanged((*reinterpret_cast< MOUDLEType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QParaSetBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QParaSetBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QParaSetBase,
      qt_meta_data_QParaSetBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QParaSetBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QParaSetBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QParaSetBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QParaSetBase))
        return static_cast<void*>(const_cast< QParaSetBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int QParaSetBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
