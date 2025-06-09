/****************************************************************************
** Meta object code from reading C++ file 'PowerDirItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/PowerDirItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PowerDirItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPowerDirItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   29,   28,   28, 0x05,
      85,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     116,  110,   28,   28, 0x08,
     164,  159,   28,   28, 0x08,
     212,   28,   28,   28, 0x08,
     248,   28,   28,   28, 0x08,
     284,   28,   28,   28, 0x08,
     321,   28,   28,   28, 0x08,
     352,   28,   28,   28, 0x08,
     395,   28,   28,   28, 0x08,
     432,   28,   28,   28, 0x08,
     466,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QPowerDirItemParaEditWidget[] = {
    "QPowerDirItemParaEditWidget\0\0pSttMacroTest\0"
    "sig_UpdateCurrSelGridData(CSttMacroTest*)\0"
    "sig_UpdateVectorWidget()\0index\0"
    "on_m_cbbTestPhase_currentIndexChanged(int)\0"
    "arg1\0on_m_cbbFaultPhase_currentIndexChanged(QString)\0"
    "on_m_editFaultVol_editingFinished()\0"
    "on_m_editFaultCur_editingFinished()\0"
    "on_m_editFaultTime_editingFinished()\0"
    "on_m_editMTA_editingFinished()\0"
    "on_m_editActionAreaRange_editingFinished()\0"
    "on_m_editStepValue_editingFinished()\0"
    "on_m_editAbsErr_editingFinished()\0"
    "on_m_editRelErr_editingFinished()\0"
};

void QPowerDirItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPowerDirItemParaEditWidget *_t = static_cast<QPowerDirItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateCurrSelGridData((*reinterpret_cast< CSttMacroTest*(*)>(_a[1]))); break;
        case 1: _t->sig_UpdateVectorWidget(); break;
        case 2: _t->on_m_cbbTestPhase_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_cbbFaultPhase_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_m_editFaultVol_editingFinished(); break;
        case 5: _t->on_m_editFaultCur_editingFinished(); break;
        case 6: _t->on_m_editFaultTime_editingFinished(); break;
        case 7: _t->on_m_editMTA_editingFinished(); break;
        case 8: _t->on_m_editActionAreaRange_editingFinished(); break;
        case 9: _t->on_m_editStepValue_editingFinished(); break;
        case 10: _t->on_m_editAbsErr_editingFinished(); break;
        case 11: _t->on_m_editRelErr_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPowerDirItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPowerDirItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QPowerDirItemParaEditWidget,
      qt_meta_data_QPowerDirItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPowerDirItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPowerDirItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPowerDirItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPowerDirItemParaEditWidget))
        return static_cast<void*>(const_cast< QPowerDirItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QPowerDirItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QPowerDirItemParaEditWidget::sig_UpdateCurrSelGridData(CSttMacroTest * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QPowerDirItemParaEditWidget::sig_UpdateVectorWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
