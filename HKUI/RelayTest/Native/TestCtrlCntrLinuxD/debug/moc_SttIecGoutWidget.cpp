/****************************************************************************
** Meta object code from reading C++ file 'SttIecGoutWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecGoutWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecGoutWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecGoutWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x09,
      44,   18,   18,   18, 0x09,
      69,   18,   18,   18, 0x09,
     103,   18,   18,   18, 0x09,
     136,   18,   18,   18, 0x09,
     170,   18,   18,   18, 0x09,
     204,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecGoutWidget[] = {
    "QSttIecGoutWidget\0\0slot_lne_T1EditClicked()\0"
    "slot_lne_T0EditClicked()\0"
    "slot_lne_TimeQualityEditClicked()\0"
    "slot_lne_GroupDelayEditClicked()\0"
    "slot_lne_T1Edit_editingFinished()\0"
    "slot_lne_T0Edit_editingFinished()\0"
    "slot_lne_GroupDelayEdit_editingFinished()\0"
};

void QSttIecGoutWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecGoutWidget *_t = static_cast<QSttIecGoutWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_lne_T1EditClicked(); break;
        case 1: _t->slot_lne_T0EditClicked(); break;
        case 2: _t->slot_lne_TimeQualityEditClicked(); break;
        case 3: _t->slot_lne_GroupDelayEditClicked(); break;
        case 4: _t->slot_lne_T1Edit_editingFinished(); break;
        case 5: _t->slot_lne_T0Edit_editingFinished(); break;
        case 6: _t->slot_lne_GroupDelayEdit_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttIecGoutWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecGoutWidget::staticMetaObject = {
    { &QSttIecConfigWidgetBase::staticMetaObject, qt_meta_stringdata_QSttIecGoutWidget,
      qt_meta_data_QSttIecGoutWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecGoutWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecGoutWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecGoutWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecGoutWidget))
        return static_cast<void*>(const_cast< QSttIecGoutWidget*>(this));
    if (!strcmp(_clname, "CIecConfigInterface"))
        return static_cast< CIecConfigInterface*>(const_cast< QSttIecGoutWidget*>(this));
    return QSttIecConfigWidgetBase::qt_metacast(_clname);
}

int QSttIecGoutWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttIecConfigWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
