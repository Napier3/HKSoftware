/****************************************************************************
** Meta object code from reading C++ file 'QDeviceModelGrid_Eng.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Module/DeviceModelUI_Eng/QDeviceModelGrid_Eng.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QDeviceModelGrid_Eng.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDeviceModelGrid_Eng_CheckBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   31,   30,   30, 0x05,
      80,   70,   30,   30, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QDeviceModelGrid_Eng_CheckBox[] = {
    "QDeviceModelGrid_Eng_CheckBox\0\0"
    "bStateValue\0CheckBoxStateChanged(BOOL)\0"
    "nRow,nCol\0CheckBox_LeftClicked(int&,int&)\0"
};

void QDeviceModelGrid_Eng_CheckBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDeviceModelGrid_Eng_CheckBox *_t = static_cast<QDeviceModelGrid_Eng_CheckBox *>(_o);
        switch (_id) {
        case 0: _t->CheckBoxStateChanged((*reinterpret_cast< BOOL(*)>(_a[1]))); break;
        case 1: _t->CheckBox_LeftClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDeviceModelGrid_Eng_CheckBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDeviceModelGrid_Eng_CheckBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QDeviceModelGrid_Eng_CheckBox,
      qt_meta_data_QDeviceModelGrid_Eng_CheckBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeviceModelGrid_Eng_CheckBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeviceModelGrid_Eng_CheckBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeviceModelGrid_Eng_CheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeviceModelGrid_Eng_CheckBox))
        return static_cast<void*>(const_cast< QDeviceModelGrid_Eng_CheckBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int QDeviceModelGrid_Eng_CheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QDeviceModelGrid_Eng_CheckBox::CheckBoxStateChanged(BOOL _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QDeviceModelGrid_Eng_CheckBox::CheckBox_LeftClicked(int & _t1, int & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QDeviceModelGrid_Eng[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      43,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   68,   21,   21, 0x0a,
     115,  104,   21,   21, 0x0a,
     157,  147,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDeviceModelGrid_Eng[] = {
    "QDeviceModelGrid_Eng\0\0sig_ScrollFinished()\0"
    "sig_EndEditCellSuccess()\0nrow,ncol\0"
    "slot_CellChanged(int,int)\0row,column\0"
    "slot_cellDoubleClicked(int,int)\0"
    "nRow,nCol\0slot_CheckBox_LeftClicked(int&,int&)\0"
};

void QDeviceModelGrid_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDeviceModelGrid_Eng *_t = static_cast<QDeviceModelGrid_Eng *>(_o);
        switch (_id) {
        case 0: _t->sig_ScrollFinished(); break;
        case 1: _t->sig_EndEditCellSuccess(); break;
        case 2: _t->slot_CellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_CheckBox_LeftClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDeviceModelGrid_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDeviceModelGrid_Eng::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_QDeviceModelGrid_Eng,
      qt_meta_data_QDeviceModelGrid_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeviceModelGrid_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeviceModelGrid_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeviceModelGrid_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeviceModelGrid_Eng))
        return static_cast<void*>(const_cast< QDeviceModelGrid_Eng*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int QDeviceModelGrid_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QDeviceModelGrid_Eng::sig_ScrollFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QDeviceModelGrid_Eng::sig_EndEditCellSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
