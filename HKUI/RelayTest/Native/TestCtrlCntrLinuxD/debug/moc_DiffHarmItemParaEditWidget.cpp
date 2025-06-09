/****************************************************************************
** Meta object code from reading C++ file 'DiffHarmItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Diff/DiffHarmItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiffHarmItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDiffHarmItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   58,   28,   28, 0x08,
     112,   58,   28,   28, 0x08,
     160,   28,   28,   28, 0x08,
     194,   28,   28,   28, 0x08,
     234,   28,   28,   28, 0x08,
     272,   28,   28,   28, 0x08,
     308,   58,   28,   28, 0x08,
     354,   28,   28,   28, 0x08,
     395,   28,   28,   28, 0x08,
     436,   28,   28,   28, 0x08,
     477,   28,   28,   28, 0x08,
     515,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDiffHarmItemParaEditWidget[] = {
    "QDiffHarmItemParaEditWidget\0\0"
    "sig_UpdateDiffWiringWidget()\0index\0"
    "on_m_cmbHarm_FaultType_currentIndexChanged(int)\0"
    "on_m_cmbHarm_HarmIndex_currentIndexChanged(int)\0"
    "on_m_txtHarm_Id_editingFinished()\0"
    "on_m_txtHarm_BeginVal_editingFinished()\0"
    "on_m_txtHarm_EndVal_editingFinished()\0"
    "on_m_txtHarm_Step_editingFinished()\0"
    "on_m_cmbHarm_OutSide_currentIndexChanged(int)\0"
    "on_m_txtHarm_FaultTime_editingFinished()\0"
    "on_m_txtHarm_AbsErrPos_editingFinished()\0"
    "on_m_txtHarm_AbsErrNeg_editingFinished()\0"
    "on_m_txtHarm_RelErr_editingFinished()\0"
    "on_m_txtHarm_CustomHarmIndex_editingFinished()\0"
};

void QDiffHarmItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDiffHarmItemParaEditWidget *_t = static_cast<QDiffHarmItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateDiffWiringWidget(); break;
        case 1: _t->on_m_cmbHarm_FaultType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_m_cmbHarm_HarmIndex_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_txtHarm_Id_editingFinished(); break;
        case 4: _t->on_m_txtHarm_BeginVal_editingFinished(); break;
        case 5: _t->on_m_txtHarm_EndVal_editingFinished(); break;
        case 6: _t->on_m_txtHarm_Step_editingFinished(); break;
        case 7: _t->on_m_cmbHarm_OutSide_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_txtHarm_FaultTime_editingFinished(); break;
        case 9: _t->on_m_txtHarm_AbsErrPos_editingFinished(); break;
        case 10: _t->on_m_txtHarm_AbsErrNeg_editingFinished(); break;
        case 11: _t->on_m_txtHarm_RelErr_editingFinished(); break;
        case 12: _t->on_m_txtHarm_CustomHarmIndex_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDiffHarmItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDiffHarmItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QDiffHarmItemParaEditWidget,
      qt_meta_data_QDiffHarmItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDiffHarmItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDiffHarmItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDiffHarmItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDiffHarmItemParaEditWidget))
        return static_cast<void*>(const_cast< QDiffHarmItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QDiffHarmItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QDiffHarmItemParaEditWidget::sig_UpdateDiffWiringWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
