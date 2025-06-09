/****************************************************************************
** Meta object code from reading C++ file 'SttPanelBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SttPanelBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttPanelBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttPanelBase[] = {

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

static const char qt_meta_stringdata_QSttPanelBase[] = {
    "QSttPanelBase\0"
};

void QSttPanelBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttPanelBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttPanelBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttPanelBase,
      qt_meta_data_QSttPanelBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttPanelBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttPanelBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttPanelBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttPanelBase))
        return static_cast<void*>(const_cast< QSttPanelBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttPanelBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QSttFloatPanelBase[] = {

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

static const char qt_meta_stringdata_QSttFloatPanelBase[] = {
    "QSttFloatPanelBase\0"
};

void QSttFloatPanelBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttFloatPanelBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFloatPanelBase::staticMetaObject = {
    { &QSttPanelBase::staticMetaObject, qt_meta_stringdata_QSttFloatPanelBase,
      qt_meta_data_QSttFloatPanelBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFloatPanelBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFloatPanelBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFloatPanelBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFloatPanelBase))
        return static_cast<void*>(const_cast< QSttFloatPanelBase*>(this));
    return QSttPanelBase::qt_metacast(_clname);
}

int QSttFloatPanelBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttPanelBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QSttFloatPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      37,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttFloatPanel[] = {
    "QSttFloatPanel\0\0slot_FloatLeftMove()\0"
    "slot_FloatRightMove()\0"
};

void QSttFloatPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttFloatPanel *_t = static_cast<QSttFloatPanel *>(_o);
        switch (_id) {
        case 0: _t->slot_FloatLeftMove(); break;
        case 1: _t->slot_FloatRightMove(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttFloatPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttFloatPanel::staticMetaObject = {
    { &QSttFloatPanelBase::staticMetaObject, qt_meta_stringdata_QSttFloatPanel,
      qt_meta_data_QSttFloatPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttFloatPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttFloatPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttFloatPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttFloatPanel))
        return static_cast<void*>(const_cast< QSttFloatPanel*>(this));
    return QSttFloatPanelBase::qt_metacast(_clname);
}

int QSttFloatPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttFloatPanelBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_QSttResultPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   17,   16,   16, 0x05,
      60,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   17,   16,   16, 0x0a,
     108,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttResultPanel[] = {
    "QSttResultPanel\0\0nLevel,strLog\0"
    "sig_refreshLog(long,QString)\0"
    "sig_ClearAll()\0slot_refreshOutput(long,QString)\0"
    "slot_ClearAll()\0"
};

void QSttResultPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttResultPanel *_t = static_cast<QSttResultPanel *>(_o);
        switch (_id) {
        case 0: _t->sig_refreshLog((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sig_ClearAll(); break;
        case 2: _t->slot_refreshOutput((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->slot_ClearAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttResultPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttResultPanel::staticMetaObject = {
    { &QSttPanelBase::staticMetaObject, qt_meta_stringdata_QSttResultPanel,
      qt_meta_data_QSttResultPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttResultPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttResultPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttResultPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttResultPanel))
        return static_cast<void*>(const_cast< QSttResultPanel*>(this));
    if (!strcmp(_clname, "CTestEventBaseInterface"))
        return static_cast< CTestEventBaseInterface*>(const_cast< QSttResultPanel*>(this));
    return QSttPanelBase::qt_metacast(_clname);
}

int QSttResultPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttPanelBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QSttResultPanel::sig_refreshLog(long _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSttResultPanel::sig_ClearAll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_QSttBarBase[] = {

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
      22,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttBarBase[] = {
    "QSttBarBase\0\0strState\0"
    "on_UpdateEnableState(CString)\0"
};

void QSttBarBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttBarBase *_t = static_cast<QSttBarBase *>(_o);
        switch (_id) {
        case 0: _t->on_UpdateEnableState((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttBarBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttBarBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttBarBase,
      qt_meta_data_QSttBarBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttBarBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttBarBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttBarBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttBarBase))
        return static_cast<void*>(const_cast< QSttBarBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttBarBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
