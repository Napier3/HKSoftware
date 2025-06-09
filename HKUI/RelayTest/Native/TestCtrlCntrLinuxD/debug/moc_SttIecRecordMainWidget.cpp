/****************************************************************************
** Meta object code from reading C++ file 'SttIecRecordMainWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/SttIecRecordMainWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecRecordMainWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecRecordMainWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      51,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   24,   24,   24, 0x08,
      98,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecRecordMainWidget[] = {
    "QSttIecRecordMainWidget\0\0"
    "sig_ShowIecDetectWindow()\0"
    "sig_ShowIecCbWindow()\0on_ShowIecDetectWindow()\0"
    "on_ShowIecCbWindow()\0"
};

void QSttIecRecordMainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecRecordMainWidget *_t = static_cast<QSttIecRecordMainWidget *>(_o);
        switch (_id) {
        case 0: _t->sig_ShowIecDetectWindow(); break;
        case 1: _t->sig_ShowIecCbWindow(); break;
        case 2: _t->on_ShowIecDetectWindow(); break;
        case 3: _t->on_ShowIecCbWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QSttIecRecordMainWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecRecordMainWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSttIecRecordMainWidget,
      qt_meta_data_QSttIecRecordMainWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecRecordMainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecRecordMainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecRecordMainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecRecordMainWidget))
        return static_cast<void*>(const_cast< QSttIecRecordMainWidget*>(this));
    if (!strcmp(_clname, "CSttWndAssistInterface"))
        return static_cast< CSttWndAssistInterface*>(const_cast< QSttIecRecordMainWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSttIecRecordMainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QSttIecRecordMainWidget::sig_ShowIecDetectWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttIecRecordMainWidget::sig_ShowIecCbWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
