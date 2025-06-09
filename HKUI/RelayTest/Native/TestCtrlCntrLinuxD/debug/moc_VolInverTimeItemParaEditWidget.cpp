/****************************************************************************
** Meta object code from reading C++ file 'VolInverTimeItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/VolInverseTime/VolInverTimeItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolInverTimeItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QVolInverTimeItemParaEditWidget[] = {

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
      39,   33,   32,   32, 0x08,
      83,   32,   32,   32, 0x08,
     115,   32,   32,   32, 0x08,
     155,   32,   32,   32, 0x08,
     186,   32,   32,   32, 0x08,
     216,   32,   32,   32, 0x08,
     252,   32,   32,   32, 0x08,
     285,   32,   32,   32, 0x08,
     319,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QVolInverTimeItemParaEditWidget[] = {
    "QVolInverTimeItemParaEditWidget\0\0index\0"
    "slot_cmb_ErrorType_currentIndexChanged(int)\0"
    "slot_lne_Volt_editingFinished()\0"
    "slot_lne_FaultCurrent_editingFinished()\0"
    "slot_lne_Ang_editingFinished()\0"
    "slot_lne_Hz_editingFinished()\0"
    "slot_lne_TSetting_editingFinished()\0"
    "slot_m_txtPlus_editingFinished()\0"
    "slot_m_txtMinus_editingFinished()\0"
    "slot_lne_RelErr_editingFinished()\0"
};

void QVolInverTimeItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QVolInverTimeItemParaEditWidget *_t = static_cast<QVolInverTimeItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_cmb_ErrorType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_lne_Volt_editingFinished(); break;
        case 2: _t->slot_lne_FaultCurrent_editingFinished(); break;
        case 3: _t->slot_lne_Ang_editingFinished(); break;
        case 4: _t->slot_lne_Hz_editingFinished(); break;
        case 5: _t->slot_lne_TSetting_editingFinished(); break;
        case 6: _t->slot_m_txtPlus_editingFinished(); break;
        case 7: _t->slot_m_txtMinus_editingFinished(); break;
        case 8: _t->slot_lne_RelErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QVolInverTimeItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QVolInverTimeItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QVolInverTimeItemParaEditWidget,
      qt_meta_data_QVolInverTimeItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QVolInverTimeItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QVolInverTimeItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QVolInverTimeItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QVolInverTimeItemParaEditWidget))
        return static_cast<void*>(const_cast< QVolInverTimeItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QVolInverTimeItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
