/****************************************************************************
** Meta object code from reading C++ file 'ShortTimeOverGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ShortTimeOver/ShortTimeOverGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShortTimeOverGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QShortTimeOverGrid[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QShortTimeOverGrid[] = {
    "QShortTimeOverGrid\0\0sig_updataParas()\0"
};

void QShortTimeOverGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QShortTimeOverGrid *_t = static_cast<QShortTimeOverGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_updataParas(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QShortTimeOverGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QShortTimeOverGrid::staticMetaObject = {
    { &QSttInfWidgetBase::staticMetaObject, qt_meta_stringdata_QShortTimeOverGrid,
      qt_meta_data_QShortTimeOverGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QShortTimeOverGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QShortTimeOverGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QShortTimeOverGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QShortTimeOverGrid))
        return static_cast<void*>(const_cast< QShortTimeOverGrid*>(this));
    return QSttInfWidgetBase::qt_metacast(_clname);
}

int QShortTimeOverGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttInfWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QShortTimeOverGrid::sig_updataParas()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
