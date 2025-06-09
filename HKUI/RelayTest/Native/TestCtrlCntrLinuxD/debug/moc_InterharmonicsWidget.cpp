/****************************************************************************
** Meta object code from reading C++ file 'InterharmonicsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Harm/InterharmonicsWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterharmonicsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QInterharmonicsChannelTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   29,   28,   28, 0x09,
      69,   65,   28,   28, 0x09,
     102,   96,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QInterharmonicsChannelTable[] = {
    "QInterharmonicsChannelTable\0\0row,col\0"
    "slot_OnCellChanged(int,int)\0pos\0"
    "slot_TableShowMent(QPoint)\0pItem\0"
    "slot_OnItemDoubleClicked(QTableWidgetItem*)\0"
};

void QInterharmonicsChannelTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QInterharmonicsChannelTable *_t = static_cast<QInterharmonicsChannelTable *>(_o);
        switch (_id) {
        case 0: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_TableShowMent((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->slot_OnItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QInterharmonicsChannelTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QInterharmonicsChannelTable::staticMetaObject = {
    { &QChannelTable::staticMetaObject, qt_meta_stringdata_QInterharmonicsChannelTable,
      qt_meta_data_QInterharmonicsChannelTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QInterharmonicsChannelTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QInterharmonicsChannelTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QInterharmonicsChannelTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QInterharmonicsChannelTable))
        return static_cast<void*>(const_cast< QInterharmonicsChannelTable*>(this));
    return QChannelTable::qt_metacast(_clname);
}

int QInterharmonicsChannelTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChannelTable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_QInterharmonicsImp[] = {

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

static const char qt_meta_stringdata_QInterharmonicsImp[] = {
    "QInterharmonicsImp\0"
};

void QInterharmonicsImp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QInterharmonicsImp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QInterharmonicsImp::staticMetaObject = {
    { &QBasicTestParaSetImp::staticMetaObject, qt_meta_stringdata_QInterharmonicsImp,
      qt_meta_data_QInterharmonicsImp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QInterharmonicsImp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QInterharmonicsImp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QInterharmonicsImp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QInterharmonicsImp))
        return static_cast<void*>(const_cast< QInterharmonicsImp*>(this));
    return QBasicTestParaSetImp::qt_metacast(_clname);
}

int QInterharmonicsImp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBasicTestParaSetImp::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QInterharmonicsWidget[] = {

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

static const char qt_meta_stringdata_QInterharmonicsWidget[] = {
    "QInterharmonicsWidget\0"
};

void QInterharmonicsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QInterharmonicsWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QInterharmonicsWidget::staticMetaObject = {
    { &QBasicTestParaSet::staticMetaObject, qt_meta_stringdata_QInterharmonicsWidget,
      qt_meta_data_QInterharmonicsWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QInterharmonicsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QInterharmonicsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QInterharmonicsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QInterharmonicsWidget))
        return static_cast<void*>(const_cast< QInterharmonicsWidget*>(this));
    return QBasicTestParaSet::qt_metacast(_clname);
}

int QInterharmonicsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBasicTestParaSet::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
