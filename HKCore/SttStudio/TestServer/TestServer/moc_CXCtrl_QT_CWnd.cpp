/****************************************************************************
** Meta object code from reading C++ file 'CXCtrl_QT_CWnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Module/OSInterface/QT/CXCtrl_QT_CWnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CXCtrl_QT_CWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CWnd_t {
    QByteArrayData data[7];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWnd_t qt_meta_stringdata_CWnd = {
    {
QT_MOC_LITERAL(0, 0, 4), // "CWnd"
QT_MOC_LITERAL(1, 5, 14), // "sig_AddMessage"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "nMsgID"
QT_MOC_LITERAL(4, 28, 6), // "wParam"
QT_MOC_LITERAL(5, 35, 6), // "lParam"
QT_MOC_LITERAL(6, 42, 16) // "slot_ExecMessage"

    },
    "CWnd\0sig_AddMessage\0\0nMsgID\0wParam\0"
    "lParam\0slot_ExecMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULong, QMetaType::ULong, QMetaType::ULong,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::ULong, QMetaType::ULong, QMetaType::ULong,    3,    4,    5,

       0        // eod
};

void CWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_AddMessage((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        case 1: _t->slot_ExecMessage((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CWnd::*)(unsigned long , unsigned long , unsigned long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWnd::sig_AddMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CWnd::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CWnd.data,
    qt_meta_data_CWnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CWnd.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CXMsgCycleBuffer"))
        return static_cast< CXMsgCycleBuffer*>(this);
    if (!strcmp(_clname, "CXWndInterface"))
        return static_cast< CXWndInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int CWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CWnd::sig_AddMessage(unsigned long _t1, unsigned long _t2, unsigned long _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
