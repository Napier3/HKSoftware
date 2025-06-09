/****************************************************************************
** Meta object code from reading C++ file 'SynActFreqItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynActFreqItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynActFreqItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynActFreqItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   30,   30,   30, 0x08,
      62,   30,   30,   30, 0x08,
      96,   30,   30,   30, 0x08,
     130,   30,   30,   30, 0x08,
     165,   30,   30,   30, 0x08,
     200,   30,   30,   30, 0x08,
     238,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSynActFreqItemParaEditWidget[] = {
    "QSynActFreqItemParaEditWidget\0\0"
    "on_m_lineFzd_editingFinished()\0"
    "on_m_lineAbsErr_editingFinished()\0"
    "on_m_lineRelErr_editingFinished()\0"
    "on_m_lineUgStart_editingFinished()\0"
    "on_m_lineFgStart_editingFinished()\0"
    "on_m_lineUgFreqStep_editingFinished()\0"
    "on_m_lineFt_editingFinished()\0"
};

void QSynActFreqItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynActFreqItemParaEditWidget *_t = static_cast<QSynActFreqItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_lineFzd_editingFinished(); break;
        case 1: _t->on_m_lineAbsErr_editingFinished(); break;
        case 2: _t->on_m_lineRelErr_editingFinished(); break;
        case 3: _t->on_m_lineUgStart_editingFinished(); break;
        case 4: _t->on_m_lineFgStart_editingFinished(); break;
        case 5: _t->on_m_lineUgFreqStep_editingFinished(); break;
        case 6: _t->on_m_lineFt_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSynActFreqItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynActFreqItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QSynActFreqItemParaEditWidget,
      qt_meta_data_QSynActFreqItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynActFreqItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynActFreqItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynActFreqItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynActFreqItemParaEditWidget))
        return static_cast<void*>(const_cast< QSynActFreqItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QSynActFreqItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
