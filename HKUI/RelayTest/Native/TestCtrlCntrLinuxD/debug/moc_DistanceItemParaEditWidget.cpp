/****************************************************************************
** Meta object code from reading C++ file 'DistanceItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Distance/DistanceItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDistanceItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   29,   28,   28, 0x08,
      75,   29,   28,   28, 0x08,
     119,   29,   28,   28, 0x08,
     163,   29,   28,   28, 0x08,
     209,   29,   28,   28, 0x08,
     247,   28,   28,   28, 0x08,
     282,   28,   28,   28, 0x08,
     313,   28,   28,   28, 0x08,
     341,   28,   28,   28, 0x08,
     369,   28,   28,   28, 0x08,
     400,   28,   28,   28, 0x08,
     431,   28,   28,   28, 0x08,
     463,   28,   28,   28, 0x08,
     502,   28,   28,   28, 0x08,
     537,   28,   28,   28, 0x08,
     568,   28,   28,   28, 0x08,
     600,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDistanceItemParaEditWidget[] = {
    "QDistanceItemParaEditWidget\0\0index\0"
    "on_m_cmbK0Mode_currentIndexChanged(int)\0"
    "on_m_cmb_ErrorType_currentIndexChanged(int)\0"
    "on_m_cmb_ErrorDirc_currentIndexChanged(int)\0"
    "on_m_cmb_ErrorNature_currentIndexChanged(int)\0"
    "slot_ZoneTypeCurrentIndexChanged(int)\0"
    "on_m_txtZSetting_editingFinished()\0"
    "on_m_txtZAng_editingFinished()\0"
    "on_m_txtR_editingFinished()\0"
    "on_m_txtX_editingFinished()\0"
    "on_m_txtRate_editingFinished()\0"
    "on_m_txtKlKr_editingFinished()\0"
    "on_m_txtAngKx_editingFinished()\0"
    "on_m_txtFaultCurrent_editingFinished()\0"
    "on_m_txtTSetting_editingFinished()\0"
    "on_m_txtPlus_editingFinished()\0"
    "on_m_txtMinus_editingFinished()\0"
    "on_m_txtRelErr_editingFinished()\0"
};

void QDistanceItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDistanceItemParaEditWidget *_t = static_cast<QDistanceItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_cmbK0Mode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_m_cmb_ErrorType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_m_cmb_ErrorDirc_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_cmb_ErrorNature_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_ZoneTypeCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_m_txtZSetting_editingFinished(); break;
        case 6: _t->on_m_txtZAng_editingFinished(); break;
        case 7: _t->on_m_txtR_editingFinished(); break;
        case 8: _t->on_m_txtX_editingFinished(); break;
        case 9: _t->on_m_txtRate_editingFinished(); break;
        case 10: _t->on_m_txtKlKr_editingFinished(); break;
        case 11: _t->on_m_txtAngKx_editingFinished(); break;
        case 12: _t->on_m_txtFaultCurrent_editingFinished(); break;
        case 13: _t->on_m_txtTSetting_editingFinished(); break;
        case 14: _t->on_m_txtPlus_editingFinished(); break;
        case 15: _t->on_m_txtMinus_editingFinished(); break;
        case 16: _t->on_m_txtRelErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDistanceItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDistanceItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QDistanceItemParaEditWidget,
      qt_meta_data_QDistanceItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDistanceItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDistanceItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDistanceItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDistanceItemParaEditWidget))
        return static_cast<void*>(const_cast< QDistanceItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QDistanceItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
