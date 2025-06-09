/****************************************************************************
** Meta object code from reading C++ file 'DistanceSearchItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/DistanceSearch/DistanceSearchItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceSearchItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceSearchItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      41,   35,   34,   34, 0x08,
      84,   34,   34,   34, 0x08,
     116,   35,   34,   34, 0x08,
     160,   34,   34,   34, 0x08,
     195,   34,   34,   34, 0x08,
     231,   34,   34,   34, 0x08,
     266,   34,   34,   34, 0x08,
     305,   34,   34,   34, 0x08,
     341,   34,   34,   34, 0x08,
     375,   34,   34,   34, 0x08,
     409,   34,   34,   34, 0x08,
     446,   34,   34,   34, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceSearchItemParaEditWidget[] = {
    "QDistanceSearchItemParaEditWidget\0\0"
    "index\0on_m_cbbFaultType_currentIndexChanged(int)\0"
    "on_m_editStep_editingFinished()\0"
    "slot_m_cbbZoneType_currentIndexChanged(int)\0"
    "on_m_editFaultIf_editingFinished()\0"
    "on_m_editBeginVal_editingFinished()\0"
    "on_m_editFaultVf_editingFinished()\0"
    "on_m_editBeginValAng_editingFinished()\0"
    "on_m_editTSetting_editingFinished()\0"
    "on_m_editEndVal_editingFinished()\0"
    "on_m_editAbsErr_editingFinished()\0"
    "on_m_editEndValAng_editingFinished()\0"
    "on_m_editRelErr_editingFinished()\0"
};

void QDistanceSearchItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceSearchItemParaEditWidget *_t = static_cast<QDistanceSearchItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_cbbFaultType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_m_editStep_editingFinished(); break;
        case 2: _t->slot_m_cbbZoneType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_editFaultIf_editingFinished(); break;
        case 4: _t->on_m_editBeginVal_editingFinished(); break;
        case 5: _t->on_m_editFaultVf_editingFinished(); break;
        case 6: _t->on_m_editBeginValAng_editingFinished(); break;
        case 7: _t->on_m_editTSetting_editingFinished(); break;
        case 8: _t->on_m_editEndVal_editingFinished(); break;
        case 9: _t->on_m_editAbsErr_editingFinished(); break;
        case 10: _t->on_m_editEndValAng_editingFinished(); break;
        case 11: _t->on_m_editRelErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDistanceSearchItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceSearchItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QDistanceSearchItemParaEditWidget,
      qt_meta_data_QDistanceSearchItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceSearchItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceSearchItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceSearchItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceSearchItemParaEditWidget))
        return static_cast<void*>(const_cast< QDistanceSearchItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QDistanceSearchItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
