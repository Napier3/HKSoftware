/****************************************************************************
** Meta object code from reading C++ file 'SttIecRecordCbWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/SttIecRecordCbWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecRecordCbWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecRecordCbWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   57,   22,   22, 0x08,
      95,   57,   22,   22, 0x08,
     129,   57,   22,   22, 0x08,
     165,   22,   22,   22, 0x08,
     188,   22,   22,   22, 0x08,
     213,   22,   22,   22, 0x08,
     239,   22,   22,   22, 0x08,
     266,   22,   22,   22, 0x08,
     293,   22,   22,   22, 0x08,
     320,   22,   22,   22, 0x08,
     347,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecRecordCbWidget[] = {
    "QSttIecRecordCbWidget\0\0"
    "sig_UpdateSVDatasetsPowerVector()\0"
    "index\0slot_CbCurrentIndexChanged(int)\0"
    "slot_FuncCurrentIndexChanged(int)\0"
    "slot_CbHarmDisplayIndexChanged(int)\0"
    "on_m_btnBack_clicked()\0on_m_btnSysSet_clicked()\0"
    "slot_Timer_IecRcdUpdate()\0"
    "on_m_btnPrevPage_clicked()\0"
    "on_m_btnNextPage_clicked()\0"
    "on_m_btnAddToSub_clicked()\0"
    "on_m_btnAddToPub_clicked()\0"
    "slot_UpdateSVDatasetsPowerVector()\0"
};

void QSttIecRecordCbWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecRecordCbWidget *_t = static_cast<QSttIecRecordCbWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateSVDatasetsPowerVector(); break;
        case 1: _t->slot_CbCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_FuncCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_CbHarmDisplayIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_m_btnBack_clicked(); break;
        case 5: _t->on_m_btnSysSet_clicked(); break;
        case 6: _t->slot_Timer_IecRcdUpdate(); break;
        case 7: _t->on_m_btnPrevPage_clicked(); break;
        case 8: _t->on_m_btnNextPage_clicked(); break;
        case 9: _t->on_m_btnAddToSub_clicked(); break;
        case 10: _t->on_m_btnAddToPub_clicked(); break;
        case 11: _t->slot_UpdateSVDatasetsPowerVector(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecRecordCbWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecRecordCbWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttIecRecordCbWidget,
      qt_meta_data_QSttIecRecordCbWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecRecordCbWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecRecordCbWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecRecordCbWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecRecordCbWidget))
        return static_cast<void*>(const_cast< QSttIecRecordCbWidget*>(this));
    if (!strcmp(_clname, "CSttIecRecordCbInterface"))
        return static_cast< CSttIecRecordCbInterface*>(const_cast< QSttIecRecordCbWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttIecRecordCbWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void QSttIecRecordCbWidget::sig_UpdateSVDatasetsPowerVector()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
