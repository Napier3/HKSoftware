/****************************************************************************
** Meta object code from reading C++ file 'LowVolTimeItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowVol/LowVolTimeItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LowVolTimeItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLowVolTimeItemParaEditWidget[] = {

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
      31,   30,   30,   30, 0x08,
      74,   30,   30,   30, 0x08,
     112,   30,   30,   30, 0x08,
     155,   30,   30,   30, 0x08,
     198,   30,   30,   30, 0x08,
     239,   30,   30,   30, 0x08,
     283,   30,   30,   30, 0x08,
     327,   30,   30,   30, 0x08,
     366,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QLowVolTimeItemParaEditWidget[] = {
    "QLowVolTimeItemParaEditWidget\0\0"
    "on_m_txtActTime_TSetting_editingFinished()\0"
    "on_m_txtActTime_Cur_editingFinished()\0"
    "on_m_txtActTime_FSetting_editingFinished()\0"
    "on_m_txtActTime_HoldTime_editingFinished()\0"
    "on_m_txtActTime_RelErr_editingFinished()\0"
    "on_m_txtActTime_AbsErrPos_editingFinished()\0"
    "on_m_txtActTime_AbsErrNeg_editingFinished()\0"
    "on_m_txtActTime_VEnd_editingFinished()\0"
    "on_m_txtActTime_dVdt_editingFinished()\0"
};

void QLowVolTimeItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QLowVolTimeItemParaEditWidget *_t = static_cast<QLowVolTimeItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_txtActTime_TSetting_editingFinished(); break;
        case 1: _t->on_m_txtActTime_Cur_editingFinished(); break;
        case 2: _t->on_m_txtActTime_FSetting_editingFinished(); break;
        case 3: _t->on_m_txtActTime_HoldTime_editingFinished(); break;
        case 4: _t->on_m_txtActTime_RelErr_editingFinished(); break;
        case 5: _t->on_m_txtActTime_AbsErrPos_editingFinished(); break;
        case 6: _t->on_m_txtActTime_AbsErrNeg_editingFinished(); break;
        case 7: _t->on_m_txtActTime_VEnd_editingFinished(); break;
        case 8: _t->on_m_txtActTime_dVdt_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QLowVolTimeItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QLowVolTimeItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QLowVolTimeItemParaEditWidget,
      qt_meta_data_QLowVolTimeItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLowVolTimeItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLowVolTimeItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLowVolTimeItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLowVolTimeItemParaEditWidget))
        return static_cast<void*>(const_cast< QLowVolTimeItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QLowVolTimeItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
