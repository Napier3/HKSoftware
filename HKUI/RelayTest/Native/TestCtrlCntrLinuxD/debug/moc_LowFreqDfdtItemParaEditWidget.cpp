/****************************************************************************
** Meta object code from reading C++ file 'LowFreqDfdtItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowFreq/LowFreqDfdtItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowFreqDfdtItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowFreqDfdtItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x08,
      79,   31,   31,   31, 0x08,
     118,   31,   31,   31, 0x08,
     162,   31,   31,   31, 0x08,
     204,   31,   31,   31, 0x08,
     246,   31,   31,   31, 0x08,
     289,   31,   31,   31, 0x08,
     334,   31,   31,   31, 0x08,
     377,   31,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLowFreqDfdtItemParaEditWidget[] = {
    "QLowFreqDfdtItemParaEditWidget\0\0"
    "on_m_txtSlipTrip_dfdtSetting_editingFinished()\0"
    "on_m_txtSlipTrip_Cur_editingFinished()\0"
    "on_m_txtSlipTrip_HoldTime_editingFinished()\0"
    "on_m_txtSlipTrip_RelErr_editingFinished()\0"
    "on_m_txtSlipTrip_AbsErr_editingFinished()\0"
    "on_m_txtSlipTrip_FreqEnd_editingFinished()\0"
    "on_m_txtSlipTrip_dfdtStart_editingFinished()\0"
    "on_m_txtSlipTrip_dfdtEnd_editingFinished()\0"
    "on_m_txtSlipTrip_dfdtStep_editingFinished()\0"
};

void QLowFreqDfdtItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowFreqDfdtItemParaEditWidget *_t = static_cast<QLowFreqDfdtItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtSlipTrip_dfdtSetting_editingFinished(); break;
        case 1: _t->on_m_txtSlipTrip_Cur_editingFinished(); break;
        case 2: _t->on_m_txtSlipTrip_HoldTime_editingFinished(); break;
        case 3: _t->on_m_txtSlipTrip_RelErr_editingFinished(); break;
        case 4: _t->on_m_txtSlipTrip_AbsErr_editingFinished(); break;
        case 5: _t->on_m_txtSlipTrip_FreqEnd_editingFinished(); break;
        case 6: _t->on_m_txtSlipTrip_dfdtStart_editingFinished(); break;
        case 7: _t->on_m_txtSlipTrip_dfdtEnd_editingFinished(); break;
        case 8: _t->on_m_txtSlipTrip_dfdtStep_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QLowFreqDfdtItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowFreqDfdtItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QLowFreqDfdtItemParaEditWidget,
      qt_meta_data_QLowFreqDfdtItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowFreqDfdtItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowFreqDfdtItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowFreqDfdtItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowFreqDfdtItemParaEditWidget))
        return static_cast<void*>(const_cast< QLowFreqDfdtItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QLowFreqDfdtItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
