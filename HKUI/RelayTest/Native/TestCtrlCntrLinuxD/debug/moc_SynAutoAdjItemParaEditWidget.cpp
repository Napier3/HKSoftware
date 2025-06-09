/****************************************************************************
** Meta object code from reading C++ file 'SynAutoAdjItemParaEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynAutoAdjItemParaEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynAutoAdjItemParaEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynAutoAdjItemParaEditWidget[] = {

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
      31,   30,   30,   30, 0x08,
      65,   30,   30,   30, 0x08,
      98,   30,   30,   30, 0x08,
     128,   30,   30,   30, 0x08,
     158,   30,   30,   30, 0x08,
     192,   30,   30,   30, 0x08,
     226,   30,   30,   30, 0x08,
     261,   30,   30,   30, 0x08,
     296,   30,   30,   30, 0x08,
     328,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSynAutoAdjItemParaEditWidget[] = {
    "QSynAutoAdjItemParaEditWidget\0\0"
    "on_m_lineLAngle_editingFinished()\0"
    "on_m_lineLTime_editingFinished()\0"
    "on_m_lineUt_editingFinished()\0"
    "on_m_lineFt_editingFinished()\0"
    "on_m_lineAbsErr_editingFinished()\0"
    "on_m_lineRelErr_editingFinished()\0"
    "on_m_lineUgStart_editingFinished()\0"
    "on_m_lineFgStart_editingFinished()\0"
    "on_m_lineDfDt_editingFinished()\0"
    "on_m_lineDvDt_editingFinished()\0"
};

void QSynAutoAdjItemParaEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynAutoAdjItemParaEditWidget *_t = static_cast<QSynAutoAdjItemParaEditWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_lineLAngle_editingFinished(); break;
        case 1: _t->on_m_lineLTime_editingFinished(); break;
        case 2: _t->on_m_lineUt_editingFinished(); break;
        case 3: _t->on_m_lineFt_editingFinished(); break;
        case 4: _t->on_m_lineAbsErr_editingFinished(); break;
        case 5: _t->on_m_lineRelErr_editingFinished(); break;
        case 6: _t->on_m_lineUgStart_editingFinished(); break;
        case 7: _t->on_m_lineFgStart_editingFinished(); break;
        case 8: _t->on_m_lineDfDt_editingFinished(); break;
        case 9: _t->on_m_lineDvDt_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSynAutoAdjItemParaEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynAutoAdjItemParaEditWidget::staticMetaObject = {
    { &QItemParaEditWidgetBase::staticMetaObject, qt_meta_stringdata_QSynAutoAdjItemParaEditWidget,
      qt_meta_data_QSynAutoAdjItemParaEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynAutoAdjItemParaEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynAutoAdjItemParaEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynAutoAdjItemParaEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynAutoAdjItemParaEditWidget))
        return static_cast<void*>(const_cast< QSynAutoAdjItemParaEditWidget*>(this));
    return QItemParaEditWidgetBase::qt_metacast(_clname);
}

int QSynAutoAdjItemParaEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
