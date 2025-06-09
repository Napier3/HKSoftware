/****************************************************************************
** Meta object code from reading C++ file 'DiffTimeItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Diff/DiffTimeItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiffTimeItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDiffTimeItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,
      62,   58,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   83,   28,   28, 0x08,
     137,   28,   28,   28, 0x08,
     171,   28,   28,   28, 0x08,
     212,   28,   28,   28, 0x08,
     253,   28,   28,   28, 0x08,
     291,   28,   28,   28, 0x08,
     327,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDiffTimeItemParaEditWidget[] = {
    "QDiffTimeItemParaEditWidget\0\0"
    "sig_UpdateDiffWiringWidget()\0dId\0"
    "sig_UpdateId(double)\0index\0"
    "on_m_cmbTime_FaultType_currentIndexChanged(int)\0"
    "on_m_txtTime_Ir_editingFinished()\0"
    "on_m_txtTime_AbsErrPos_editingFinished()\0"
    "on_m_txtTime_AbsErrNeg_editingFinished()\0"
    "on_m_txtTime_RelErr_editingFinished()\0"
    "on_m_txtTime_Freq_editingFinished()\0"
    "on_m_txtTime_FaultTime_editingFinished()\0"
};

void QDiffTimeItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDiffTimeItemParaEditWidget *_t = static_cast<QDiffTimeItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateDiffWiringWidget(); break;
        case 1: _t->sig_UpdateId((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_m_cmbTime_FaultType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_txtTime_Ir_editingFinished(); break;
        case 4: _t->on_m_txtTime_AbsErrPos_editingFinished(); break;
        case 5: _t->on_m_txtTime_AbsErrNeg_editingFinished(); break;
        case 6: _t->on_m_txtTime_RelErr_editingFinished(); break;
        case 7: _t->on_m_txtTime_Freq_editingFinished(); break;
        case 8: _t->on_m_txtTime_FaultTime_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDiffTimeItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffTimeItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QDiffTimeItemParaEditWidget,
      qt_meta_data_QDiffTimeItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffTimeItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffTimeItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffTimeItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffTimeItemParaEditWidget))
        return static_cast<void*>(const_cast< QDiffTimeItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QDiffTimeItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QDiffTimeItemParaEditWidget::sig_UpdateDiffWiringWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QDiffTimeItemParaEditWidget::sig_UpdateId(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
