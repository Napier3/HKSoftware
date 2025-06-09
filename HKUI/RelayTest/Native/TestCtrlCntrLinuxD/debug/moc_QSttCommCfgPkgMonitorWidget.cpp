/****************************************************************************
** Meta object code from reading C++ file 'QSttCommCfgPkgMonitorWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CommConfigurationDlg/PkgMonitor/QSttCommCfgPkgMonitorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttCommCfgPkgMonitorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttCommCfgPkgMonitorWidget[] = {

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
      29,   28,   28,   28, 0x0a,
      56,   28,   28,   28, 0x0a,
      82,   28,   28,   28, 0x0a,
     107,   28,   28,   28, 0x0a,
     128,   28,   28,   28, 0x0a,
     149,  144,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttCommCfgPkgMonitorWidget[] = {
    "QSttCommCfgPkgMonitorWidget\0\0"
    "slot_StartMonitorClicked()\0"
    "slot_StopMonitorClicked()\0"
    "slot_ClearListrClicked()\0slot_ExportClicked()\0"
    "slot_TimerOut()\0item\0"
    "slot_TabSelectRowChange(QTableWidgetItem*)\0"
};

void QSttCommCfgPkgMonitorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttCommCfgPkgMonitorWidget *_t = static_cast<QSttCommCfgPkgMonitorWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_StartMonitorClicked(); break;
        case 1: _t->slot_StopMonitorClicked(); break;
        case 2: _t->slot_ClearListrClicked(); break;
        case 3: _t->slot_ExportClicked(); break;
        case 4: _t->slot_TimerOut(); break;
        case 5: _t->slot_TabSelectRowChange((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttCommCfgPkgMonitorWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttCommCfgPkgMonitorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttCommCfgPkgMonitorWidget,
      qt_meta_data_QSttCommCfgPkgMonitorWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttCommCfgPkgMonitorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttCommCfgPkgMonitorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttCommCfgPkgMonitorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttCommCfgPkgMonitorWidget))
        return static_cast<void*>(const_cast< QSttCommCfgPkgMonitorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttCommCfgPkgMonitorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
