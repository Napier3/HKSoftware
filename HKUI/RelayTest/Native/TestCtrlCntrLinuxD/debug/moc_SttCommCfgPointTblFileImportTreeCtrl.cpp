/****************************************************************************
** Meta object code from reading C++ file 'SttCommCfgPointTblFileImportTreeCtrl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommConfigurationDlg/PointTblFile/SttCommCfgPointTblFileImportTreeCtrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttCommCfgPointTblFileImportTreeCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttCommCfgPointTblFileImportTreeCtrl[] = {

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
      39,   38,   38,   38, 0x05,
      73,   38,   38,   38, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QSttCommCfgPointTblFileImportTreeCtrl[] = {
    "QSttCommCfgPointTblFileImportTreeCtrl\0"
    "\0sig_MouseMoveGbTree(QMouseEvent*)\0"
    "sig_focusOutEventGbTree(QFocusEvent*)\0"
};

void QSttCommCfgPointTblFileImportTreeCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttCommCfgPointTblFileImportTreeCtrl *_t = static_cast<QSttCommCfgPointTblFileImportTreeCtrl *>(_o);
        switch (_id) {
        case 0: _t->sig_MouseMoveGbTree((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->sig_focusOutEventGbTree((*reinterpret_cast< QFocusEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttCommCfgPointTblFileImportTreeCtrl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttCommCfgPointTblFileImportTreeCtrl::staticMetaObject = {
    { &CExBaseListTreeCtrl::staticMetaObject, qt_meta_stringdata_QSttCommCfgPointTblFileImportTreeCtrl,
      qt_meta_data_QSttCommCfgPointTblFileImportTreeCtrl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttCommCfgPointTblFileImportTreeCtrl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttCommCfgPointTblFileImportTreeCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttCommCfgPointTblFileImportTreeCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttCommCfgPointTblFileImportTreeCtrl))
        return static_cast<void*>(const_cast< QSttCommCfgPointTblFileImportTreeCtrl*>(this));
    if (!strcmp(_clname, "CScrollCtrlInterface"))
        return static_cast< CScrollCtrlInterface*>(const_cast< QSttCommCfgPointTblFileImportTreeCtrl*>(this));
    return CExBaseListTreeCtrl::qt_metacast(_clname);
}

int QSttCommCfgPointTblFileImportTreeCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CExBaseListTreeCtrl::qt_metacall(_c, _id, _a);
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
void QSttCommCfgPointTblFileImportTreeCtrl::sig_MouseMoveGbTree(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSttCommCfgPointTblFileImportTreeCtrl::sig_focusOutEventGbTree(QFocusEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
