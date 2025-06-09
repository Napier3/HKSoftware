/****************************************************************************
** Meta object code from reading C++ file 'SttWebViewBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Webkit/SttWebViewBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttWebViewBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttWebViewBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      52,   50,   16,   16, 0x0a,
      85,   76,   16,   16, 0x0a,
     121,  103,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttWebViewBase[] = {
    "QSttWebViewBase\0\0populateJavaScriptWindowObject()\0"
    "b\0slot_loadFinished(bool)\0strParas\0"
    "ShowMsg(QVariant)\0strLevel,strParas\0"
    "ShowMsgEx(QVariant,QVariant)\0"
};

void QSttWebViewBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttWebViewBase *_t = static_cast<QSttWebViewBase *>(_o);
        switch (_id) {
        case 0: _t->populateJavaScriptWindowObject(); break;
        case 1: _t->slot_loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ShowMsg((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->ShowMsgEx((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttWebViewBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttWebViewBase::staticMetaObject = {
    { &QScrollWebView::staticMetaObject, qt_meta_stringdata_QSttWebViewBase,
      qt_meta_data_QSttWebViewBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttWebViewBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttWebViewBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttWebViewBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttWebViewBase))
        return static_cast<void*>(const_cast< QSttWebViewBase*>(this));
    return QScrollWebView::qt_metacast(_clname);
}

int QSttWebViewBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
