/****************************************************************************
** Meta object code from reading C++ file 'StateEditDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/State/StateEditDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateEditDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QStateEditGrid[] = {

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

static const char qt_meta_stringdata_QStateEditGrid[] = {
    "QStateEditGrid\0"
};

void QStateEditGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QStateEditGrid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QStateEditGrid::staticMetaObject = {
    { &QExBaseListGridBase::staticMetaObject, qt_meta_stringdata_QStateEditGrid,
      qt_meta_data_QStateEditGrid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QStateEditGrid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QStateEditGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QStateEditGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QStateEditGrid))
        return static_cast<void*>(const_cast< QStateEditGrid*>(this));
    return QExBaseListGridBase::qt_metacast(_clname);
}

int QStateEditGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExBaseListGridBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QStateEditDlg[] = {

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
      15,   14,   14,   14, 0x08,
      34,   14,   14,   14, 0x08,
      55,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QStateEditDlg[] = {
    "QStateEditDlg\0\0slot_SelectedAll()\0"
    "slot_UnSelectedAll()\0slot_ReverseSelect()\0"
};

void QStateEditDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QStateEditDlg *_t = static_cast<QStateEditDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_SelectedAll(); break;
        case 1: _t->slot_UnSelectedAll(); break;
        case 2: _t->slot_ReverseSelect(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QStateEditDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QStateEditDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QStateEditDlg,
      qt_meta_data_QStateEditDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QStateEditDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QStateEditDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QStateEditDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QStateEditDlg))
        return static_cast<void*>(const_cast< QStateEditDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QStateEditDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
