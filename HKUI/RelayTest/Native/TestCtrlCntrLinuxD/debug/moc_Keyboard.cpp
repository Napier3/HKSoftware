/****************************************************************************
** Meta object code from reading C++ file 'Keyboard.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/SoftKeyBoard/Keyboard/Keyboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Keyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Keyboard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      39,    9,    9,    9, 0x05,
      68,    9,    9,    9, 0x05,
      97,    9,    9,    9, 0x05,
     126,    9,    9,    9, 0x05,
     152,  143,    9,    9, 0x05,
     179,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     219,  199,    9,    9, 0x08,
     251,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Keyboard[] = {
    "Keyboard\0\0sig_clickFunc1(QPushButton*)\0"
    "sig_clickFunc2(QPushButton*)\0"
    "sig_clickFunc3(QPushButton*)\0"
    "sig_clickFunc4(QPushButton*)\0"
    "sig_clickEnter()\0strValue\0"
    "sig_updateChanged(QString)\0"
    "sig_deleteChanged()\0oldWidget,nowWidget\0"
    "focusChanged(QWidget*,QWidget*)\0"
    "btnClicked()\0"
};

void Keyboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Keyboard *_t = static_cast<Keyboard *>(_o);
        switch (_id) {
        case 0: _t->sig_clickFunc1((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 1: _t->sig_clickFunc2((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 2: _t->sig_clickFunc3((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 3: _t->sig_clickFunc4((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 4: _t->sig_clickEnter(); break;
        case 5: _t->sig_updateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->sig_deleteChanged(); break;
        case 7: _t->focusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 8: _t->btnClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Keyboard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Keyboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Keyboard,
      qt_meta_data_Keyboard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Keyboard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Keyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Keyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Keyboard))
        return static_cast<void*>(const_cast< Keyboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int Keyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Keyboard::sig_clickFunc1(QPushButton * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Keyboard::sig_clickFunc2(QPushButton * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Keyboard::sig_clickFunc3(QPushButton * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Keyboard::sig_clickFunc4(QPushButton * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Keyboard::sig_clickEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Keyboard::sig_updateChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Keyboard::sig_deleteChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
