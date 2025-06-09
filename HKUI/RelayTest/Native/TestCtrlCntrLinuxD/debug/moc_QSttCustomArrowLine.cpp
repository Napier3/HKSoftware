/****************************************************************************
** Meta object code from reading C++ file 'QSttCustomArrowLine.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommonCtrl_QT/Draw/QSttCustomArrowLine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttCustomArrowLine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttCustomArrowLine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      36,   20,   20,   20, 0x05,
      53,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QSttCustomArrowLine[] = {
    "QSttCustomArrowLine\0\0itemSelected()\0"
    "itemDeselected()\0arrowClicked()\0"
};

void QSttCustomArrowLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttCustomArrowLine *_t = static_cast<QSttCustomArrowLine *>(_o);
        switch (_id) {
        case 0: _t->itemSelected(); break;
        case 1: _t->itemDeselected(); break;
        case 2: _t->arrowClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttCustomArrowLine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttCustomArrowLine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSttCustomArrowLine,
      qt_meta_data_QSttCustomArrowLine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttCustomArrowLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttCustomArrowLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttCustomArrowLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttCustomArrowLine))
        return static_cast<void*>(const_cast< QSttCustomArrowLine*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< QSttCustomArrowLine*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< QSttCustomArrowLine*>(this));
    return QObject::qt_metacast(_clname);
}

int QSttCustomArrowLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QSttCustomArrowLine::itemSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttCustomArrowLine::itemDeselected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QSttCustomArrowLine::arrowClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
