/****************************************************************************
** Meta object code from reading C++ file 'SynAdjVolItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynAdjVolItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynAdjVolItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynAdjVolItemParaEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x08,
      60,   29,   29,   29, 0x08,
      92,   29,   29,   29, 0x08,
     125,   29,   29,   29, 0x08,
     159,   29,   29,   29, 0x08,
     194,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSynAdjVolItemParaEditWidget[] = {
    "QSynAdjVolItemParaEditWidget\0\0"
    "on_m_lineUt_editingFinished()\0"
    "on_m_linePlus_editingFinished()\0"
    "on_m_lineMinus_editingFinished()\0"
    "on_m_lineRelErr_editingFinished()\0"
    "on_m_lineUgStart_editingFinished()\0"
    "on_m_lineFgStart_editingFinished()\0"
};

void QSynAdjVolItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynAdjVolItemParaEditWidget *_t = static_cast<QSynAdjVolItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_lineUt_editingFinished(); break;
        case 1: _t->on_m_linePlus_editingFinished(); break;
        case 2: _t->on_m_lineMinus_editingFinished(); break;
        case 3: _t->on_m_lineRelErr_editingFinished(); break;
        case 4: _t->on_m_lineUgStart_editingFinished(); break;
        case 5: _t->on_m_lineFgStart_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSynAdjVolItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynAdjVolItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QSynAdjVolItemParaEditWidget,
      qt_meta_data_QSynAdjVolItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynAdjVolItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynAdjVolItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynAdjVolItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynAdjVolItemParaEditWidget))
        return static_cast<void*>(const_cast< QSynAdjVolItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QSynAdjVolItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemParaEditWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
