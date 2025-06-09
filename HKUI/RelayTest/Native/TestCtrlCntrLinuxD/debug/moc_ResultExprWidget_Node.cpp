/****************************************************************************
** Meta object code from reading C++ file 'ResultExprWidget_Node.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ResultExpr/ResultExprWidget_Node.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultExprWidget_Node.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QResultExprWidget_Node[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      39,   23,   23,   23, 0x08,
      54,   23,   23,   23, 0x08,
      65,   23,   23,   23, 0x08,
      94,   87,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QResultExprWidget_Node[] = {
    "QResultExprWidget_Node\0\0OnSelectExpr()\0"
    "OnDelectExpr()\0OnExpand()\0"
    "on_m_btnAdd_clicked()\0bCheck\0"
    "slot_Add(bool)\0"
};

void QResultExprWidget_Node::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QResultExprWidget_Node *_t = static_cast<QResultExprWidget_Node *>(_o);
        switch (_id) {
        case 0: _t->OnSelectExpr(); break;
        case 1: _t->OnDelectExpr(); break;
        case 2: _t->OnExpand(); break;
        case 3: _t->on_m_btnAdd_clicked(); break;
        case 4: _t->slot_Add((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QResultExprWidget_Node::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QResultExprWidget_Node::staticMetaObject = {
    { &QResultExprWidget::staticMetaObject, qt_meta_stringdata_QResultExprWidget_Node,
      qt_meta_data_QResultExprWidget_Node, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QResultExprWidget_Node::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QResultExprWidget_Node::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QResultExprWidget_Node::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QResultExprWidget_Node))
        return static_cast<void*>(const_cast< QResultExprWidget_Node*>(this));
    return QResultExprWidget::qt_metacast(_clname);
}

int QResultExprWidget_Node::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QResultExprWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
