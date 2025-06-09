/****************************************************************************
** Meta object code from reading C++ file 'LowFreqULockItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowFreq/LowFreqULockItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowFreqULockItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowFreqULockItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   32,   32,   32, 0x08,
      80,   32,   32,   32, 0x08,
     117,   32,   32,   32, 0x08,
     165,  159,   32,   32, 0x08,
     209,   32,   32,   32, 0x08,
     249,   32,   32,   32, 0x08,
     289,   32,   32,   32, 0x08,
     329,   32,   32,   32, 0x08,
     367,   32,   32,   32, 0x08,
     406,   32,   32,   32, 0x08,
     444,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLowFreqULockItemParaEditWidget[] = {
    "QLowFreqULockItemParaEditWidget\0\0"
    "on_m_txtVBlock_VBlockSetting_editingFinished()\0"
    "on_m_txtVBlock_Cur_editingFinished()\0"
    "on_m_txtVBlock_HoldTime_editingFinished()\0"
    "index\0on_m_cmbVBlock_Var_currentIndexChanged(int)\0"
    "on_m_txtVBlock_RelErr_editingFinished()\0"
    "on_m_txtVBlock_AbsErr_editingFinished()\0"
    "on_m_txtVBlock_VStart_editingFinished()\0"
    "on_m_txtVBlock_VEnd_editingFinished()\0"
    "on_m_txtVBlock_VStep_editingFinished()\0"
    "on_m_txtVBlock_dfdt_editingFinished()\0"
    "on_m_txtVBlock_FreqEnd_editingFinished()\0"
};

void QLowFreqULockItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowFreqULockItemParaEditWidget *_t = static_cast<QLowFreqULockItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtVBlock_VBlockSetting_editingFinished(); break;
        case 1: _t->on_m_txtVBlock_Cur_editingFinished(); break;
        case 2: _t->on_m_txtVBlock_HoldTime_editingFinished(); break;
        case 3: _t->on_m_cmbVBlock_Var_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_m_txtVBlock_RelErr_editingFinished(); break;
        case 5: _t->on_m_txtVBlock_AbsErr_editingFinished(); break;
        case 6: _t->on_m_txtVBlock_VStart_editingFinished(); break;
        case 7: _t->on_m_txtVBlock_VEnd_editingFinished(); break;
        case 8: _t->on_m_txtVBlock_VStep_editingFinished(); break;
        case 9: _t->on_m_txtVBlock_dfdt_editingFinished(); break;
        case 10: _t->on_m_txtVBlock_FreqEnd_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QLowFreqULockItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowFreqULockItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QLowFreqULockItemParaEditWidget,
      qt_meta_data_QLowFreqULockItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowFreqULockItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowFreqULockItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowFreqULockItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowFreqULockItemParaEditWidget))
        return static_cast<void*>(const_cast< QLowFreqULockItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QLowFreqULockItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
