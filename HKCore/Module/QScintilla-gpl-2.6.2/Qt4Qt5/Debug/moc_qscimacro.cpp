/****************************************************************************
** Meta object code from reading C++ file 'qscimacro.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qsci/qscimacro.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscimacro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciMacro[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      18,   10,   10,   10, 0x0a,
      35,   10,   10,   10, 0x0a,
      68,   50,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QsciMacro[] = {
    "QsciMacro\0\0play()\0startRecording()\0"
    "endRecording()\0msg,wParam,lParam\0"
    "record(uint,ulong,void*)\0"
};

void QsciMacro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QsciMacro *_t = static_cast<QsciMacro *>(_o);
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->startRecording(); break;
        case 2: _t->endRecording(); break;
        case 3: _t->record((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QsciMacro::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QsciMacro::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QsciMacro,
      qt_meta_data_QsciMacro, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciMacro::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciMacro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciMacro::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciMacro))
        return static_cast<void*>(const_cast< QsciMacro*>(this));
    return QObject::qt_metacast(_clname);
}

int QsciMacro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
