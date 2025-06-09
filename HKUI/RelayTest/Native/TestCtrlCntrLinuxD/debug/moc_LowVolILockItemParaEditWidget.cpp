/****************************************************************************
** Meta object code from reading C++ file 'LowVolILockItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowVol/LowVolILockItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowVolILockItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowVolILockItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x08,
      79,   31,   31,   31, 0x08,
     127,  121,   31,   31, 0x08,
     171,   31,   31,   31, 0x08,
     211,   31,   31,   31, 0x08,
     251,   31,   31,   31, 0x08,
     291,   31,   31,   31, 0x08,
     329,   31,   31,   31, 0x08,
     368,   31,   31,   31, 0x08,
     406,   31,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLowVolILockItemParaEditWidget[] = {
    "QLowVolILockItemParaEditWidget\0\0"
    "on_m_txtIBlock_IBlockSetting_editingFinished()\0"
    "on_m_txtIBlock_HoldTime_editingFinished()\0"
    "index\0on_m_cmbIBlock_Var_currentIndexChanged(int)\0"
    "on_m_txtIBlock_RelErr_editingFinished()\0"
    "on_m_txtIBlock_AbsErr_editingFinished()\0"
    "on_m_txtIBlock_IStart_editingFinished()\0"
    "on_m_txtIBlock_IEnd_editingFinished()\0"
    "on_m_txtIBlock_IStep_editingFinished()\0"
    "on_m_txtIBlock_VEnd_editingFinished()\0"
    "on_m_txtIBlock_dVdt_editingFinished()\0"
};

void QLowVolILockItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowVolILockItemParaEditWidget *_t = static_cast<QLowVolILockItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtIBlock_IBlockSetting_editingFinished(); break;
        case 1: _t->on_m_txtIBlock_HoldTime_editingFinished(); break;
        case 2: _t->on_m_cmbIBlock_Var_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_txtIBlock_RelErr_editingFinished(); break;
        case 4: _t->on_m_txtIBlock_AbsErr_editingFinished(); break;
        case 5: _t->on_m_txtIBlock_IStart_editingFinished(); break;
        case 6: _t->on_m_txtIBlock_IEnd_editingFinished(); break;
        case 7: _t->on_m_txtIBlock_IStep_editingFinished(); break;
        case 8: _t->on_m_txtIBlock_VEnd_editingFinished(); break;
        case 9: _t->on_m_txtIBlock_dVdt_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QLowVolILockItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowVolILockItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QLowVolILockItemParaEditWidget,
      qt_meta_data_QLowVolILockItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowVolILockItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowVolILockItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowVolILockItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowVolILockItemParaEditWidget))
        return static_cast<void*>(const_cast< QLowVolILockItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QLowVolILockItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
