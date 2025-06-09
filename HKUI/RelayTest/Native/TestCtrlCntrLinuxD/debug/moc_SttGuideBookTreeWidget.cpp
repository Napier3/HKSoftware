/****************************************************************************
** Meta object code from reading C++ file 'SttGuideBookTreeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SttGuideBookTreeWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttGuideBookTreeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttGuideBookTreeWidget[] = {

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
      38,   25,   24,   24, 0x0a,
      90,   76,   24,   24, 0x0a,
     119,   24,   24,   24, 0x0a,
     140,   24,   24,   24, 0x0a,
     163,  161,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttGuideBookTreeWidget[] = {
    "QSttGuideBookTreeWidget\0\0pCurTestItem\0"
    "slot_ItemStateChanged(CExBaseObject*)\0"
    "pCurTestItems\0slot_ShowItems(CExBaseList*)\0"
    "slot_OnBtnTestFrom()\0slot_OnBtnTestThis()\0"
    "e\0slot_SttfocusOutEventGbTree(QFocusEvent*)\0"
};

void QSttGuideBookTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttGuideBookTreeWidget *_t = static_cast<QSttGuideBookTreeWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_ItemStateChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1]))); break;
        case 1: _t->slot_ShowItems((*reinterpret_cast< CExBaseList*(*)>(_a[1]))); break;
        case 2: _t->slot_OnBtnTestFrom(); break;
        case 3: _t->slot_OnBtnTestThis(); break;
        case 4: _t->slot_SttfocusOutEventGbTree((*reinterpret_cast< QFocusEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttGuideBookTreeWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttGuideBookTreeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttGuideBookTreeWidget,
      qt_meta_data_QSttGuideBookTreeWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttGuideBookTreeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttGuideBookTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttGuideBookTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttGuideBookTreeWidget))
        return static_cast<void*>(const_cast< QSttGuideBookTreeWidget*>(this));
    if (!strcmp(_clname, "CExBaseListTreeOptrInterface"))
        return static_cast< CExBaseListTreeOptrInterface*>(const_cast< QSttGuideBookTreeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttGuideBookTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
