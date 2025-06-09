/****************************************************************************
** Meta object code from reading C++ file 'IecCfgFT3OutGrid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/FT3Widget/IecCfgFT3OutGrid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IecCfgFT3OutGrid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QIecCfgFT3OutComBoxDelegBase[] = {

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

static const char qt_meta_stringdata_QIecCfgFT3OutComBoxDelegBase[] = {
    "QIecCfgFT3OutComBoxDelegBase\0"
};

void QIecCfgFT3OutComBoxDelegBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QIecCfgFT3OutComBoxDelegBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QIecCfgFT3OutComBoxDelegBase::staticMetaObject = {
    { &QExBaseListComBoxDelegBase::staticMetaObject, qt_meta_stringdata_QIecCfgFT3OutComBoxDelegBase,
      qt_meta_data_QIecCfgFT3OutComBoxDelegBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QIecCfgFT3OutComBoxDelegBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QIecCfgFT3OutComBoxDelegBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QIecCfgFT3OutComBoxDelegBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QIecCfgFT3OutComBoxDelegBase))
        return static_cast<void*>(const_cast< QIecCfgFT3OutComBoxDelegBase*>(this));
    return QExBaseListComBoxDelegBase::qt_metacast(_clname);
}

int QIecCfgFT3OutComBoxDelegBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListComBoxDelegBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_IecCfgFT3OutGrid[] = {

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
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   41,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IecCfgFT3OutGrid[] = {
    "IecCfgFT3OutGrid\0\0sig_Ft3Value_Changed()\0"
    "nRow,nCol\0Slot_Setting_Clicked(int,int)\0"
};

void IecCfgFT3OutGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IecCfgFT3OutGrid *_t = static_cast<IecCfgFT3OutGrid *>(_o);
        switch (_id) {
        case 0: _t->sig_Ft3Value_Changed(); break;
        case 1: _t->Slot_Setting_Clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IecCfgFT3OutGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IecCfgFT3OutGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_IecCfgFT3OutGrid,
      qt_meta_data_IecCfgFT3OutGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IecCfgFT3OutGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IecCfgFT3OutGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IecCfgFT3OutGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IecCfgFT3OutGrid))
        return static_cast<void*>(const_cast< IecCfgFT3OutGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int IecCfgFT3OutGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
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
void IecCfgFT3OutGrid::sig_Ft3Value_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
