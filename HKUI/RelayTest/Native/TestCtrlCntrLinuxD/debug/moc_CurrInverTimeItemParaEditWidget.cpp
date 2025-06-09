/****************************************************************************
** Meta object code from reading C++ file 'CurrInverTimeItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/CurrInverseTime/CurrInverTimeItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CurrInverTimeItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCurrInverTimeItemParaEditWidget[] = {

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
      40,   34,   33,   33, 0x08,
      72,   34,   33,   33, 0x08,
     116,   33,   33,   33, 0x08,
     153,   33,   33,   33, 0x08,
     188,   33,   33,   33, 0x08,
     219,   33,   33,   33, 0x08,
     249,   33,   33,   33, 0x08,
     285,   33,   33,   33, 0x08,
     318,   33,   33,   33, 0x08,
     352,   33,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QCurrInverTimeItemParaEditWidget[] = {
    "QCurrInverTimeItemParaEditWidget\0\0"
    "index\0slot_cmb_FaultVolt_Changed(int)\0"
    "slot_cmb_ErrorType_currentIndexChanged(int)\0"
    "slot_lne_FaultVolt_editingFinished()\0"
    "slot_lne_Current_editingFinished()\0"
    "slot_lne_Ang_editingFinished()\0"
    "slot_lne_Hz_editingFinished()\0"
    "slot_lne_TSetting_editingFinished()\0"
    "slot_m_txtPlus_editingFinished()\0"
    "slot_m_txtMinus_editingFinished()\0"
    "slot_lne_RelErr_editingFinished()\0"
};

void QCurrInverTimeItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCurrInverTimeItemParaEditWidget *_t = static_cast<QCurrInverTimeItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_cmb_FaultVolt_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_cmb_ErrorType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_lne_FaultVolt_editingFinished(); break;
        case 3: _t->slot_lne_Current_editingFinished(); break;
        case 4: _t->slot_lne_Ang_editingFinished(); break;
        case 5: _t->slot_lne_Hz_editingFinished(); break;
        case 6: _t->slot_lne_TSetting_editingFinished(); break;
        case 7: _t->slot_m_txtPlus_editingFinished(); break;
        case 8: _t->slot_m_txtMinus_editingFinished(); break;
        case 9: _t->slot_lne_RelErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCurrInverTimeItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCurrInverTimeItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QCurrInverTimeItemParaEditWidget,
      qt_meta_data_QCurrInverTimeItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCurrInverTimeItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCurrInverTimeItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCurrInverTimeItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCurrInverTimeItemParaEditWidget))
        return static_cast<void*>(const_cast< QCurrInverTimeItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QCurrInverTimeItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
