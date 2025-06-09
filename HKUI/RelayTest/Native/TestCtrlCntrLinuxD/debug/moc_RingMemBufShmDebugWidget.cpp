/****************************************************************************
** Meta object code from reading C++ file 'RingMemBufShmDebugWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/QT/RingMemBufShmDebugWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RingMemBufShmDebugWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRingMemBufShmDebugWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x08,
      61,   26,   26,   26, 0x08,
      92,   26,   26,   26, 0x08,
     120,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QRingMemBufShmDebugWidget[] = {
    "QRingMemBufShmDebugWidget\0\0"
    "on_m_Btn_WriteDetectPkg_clicked()\0"
    "on_m_Btn_WriteRcvPkg_clicked()\0"
    "on_m_btnAutoWrite_clicked()\0"
    "slot_Timer_AutoWrite()\0"
};

void QRingMemBufShmDebugWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRingMemBufShmDebugWidget *_t = static_cast<QRingMemBufShmDebugWidget *>(_o);
        switch (_id) {
        case 0: _t->on_m_Btn_WriteDetectPkg_clicked(); break;
        case 1: _t->on_m_Btn_WriteRcvPkg_clicked(); break;
        case 2: _t->on_m_btnAutoWrite_clicked(); break;
        case 3: _t->slot_Timer_AutoWrite(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QRingMemBufShmDebugWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRingMemBufShmDebugWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QRingMemBufShmDebugWidget,
      qt_meta_data_QRingMemBufShmDebugWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRingMemBufShmDebugWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRingMemBufShmDebugWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRingMemBufShmDebugWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRingMemBufShmDebugWidget))
        return static_cast<void*>(const_cast< QRingMemBufShmDebugWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QRingMemBufShmDebugWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
