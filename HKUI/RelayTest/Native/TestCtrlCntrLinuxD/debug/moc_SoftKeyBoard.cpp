/****************************************************************************
** Meta object code from reading C++ file 'SoftKeyBoard.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/SoftKeyBoard/SoftKeyBoard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SoftKeyBoard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSoftKeyBoard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      39,   14,   14,   14, 0x05,
      63,   14,   14,   14, 0x05,
      87,   14,   14,   14, 0x05,
     111,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   14,   14,   14, 0x08,
     158,   14,   14,   14, 0x08,
     188,   14,   14,   14, 0x08,
     218,   14,   14,   14, 0x08,
     248,   14,   14,   14, 0x08,
     266,   14,   14,   14, 0x0a,
     285,  276,   14,   14, 0x0a,
     308,   14,   14,   14, 0x0a,
     324,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSoftKeyBoard[] = {
    "QSoftKeyBoard\0\0sig_clickFunc1(QString)\0"
    "sig_clickFunc2(QString)\0sig_clickFunc3(QString)\0"
    "sig_clickFunc4(QString)\0sig_clickEnter()\0"
    "slot_clickFunc1(QPushButton*)\0"
    "slot_clickFunc2(QPushButton*)\0"
    "slot_clickFunc3(QPushButton*)\0"
    "slot_clickFunc4(QPushButton*)\0"
    "slot_clickEnter()\0OnTimer()\0strValue\0"
    "updateChanged(QString)\0deleteChanged()\0"
    "microFocusChanged()\0"
};

void QSoftKeyBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSoftKeyBoard *_t = static_cast<QSoftKeyBoard *>(_o);
        switch (_id) {
        case 0: _t->sig_clickFunc1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_clickFunc2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_clickFunc3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sig_clickFunc4((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sig_clickEnter(); break;
        case 5: _t->slot_clickFunc1((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 6: _t->slot_clickFunc2((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 7: _t->slot_clickFunc3((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 8: _t->slot_clickFunc4((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 9: _t->slot_clickEnter(); break;
        case 10: _t->OnTimer(); break;
        case 11: _t->updateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->deleteChanged(); break;
        case 13: _t->microFocusChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSoftKeyBoard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSoftKeyBoard::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSoftKeyBoard,
      qt_meta_data_QSoftKeyBoard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSoftKeyBoard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSoftKeyBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSoftKeyBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSoftKeyBoard))
        return static_cast<void*>(const_cast< QSoftKeyBoard*>(this));
    return QObject::qt_metacast(_clname);
}

int QSoftKeyBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QSoftKeyBoard::sig_clickFunc1(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSoftKeyBoard::sig_clickFunc2(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSoftKeyBoard::sig_clickFunc3(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSoftKeyBoard::sig_clickFunc4(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QSoftKeyBoard::sig_clickEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
