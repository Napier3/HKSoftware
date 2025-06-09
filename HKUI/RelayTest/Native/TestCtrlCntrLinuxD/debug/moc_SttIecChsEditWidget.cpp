/****************************************************************************
** Meta object code from reading C++ file 'SttIecChsEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecChsEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecChsEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecChsEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x0a,
      47,   21,   21,   21, 0x0a,
      71,   21,   21,   21, 0x0a,
      97,   21,   21,   21, 0x0a,
     123,   21,   21,   21, 0x0a,
     149,   21,   21,   21, 0x0a,
     170,   21,   21,   21, 0x0a,
     198,   21,   21,   21, 0x0a,
     226,   21,   21,   21, 0x0a,
     253,   21,   21,   21, 0x0a,
     286,  273,   21,   21, 0x0a,
     322,   21,   21,   21, 0x0a,
     352,   21,   21,   21, 0x0a,
     382,   21,   21,   21, 0x0a,
     412,   21,   21,   21, 0x0a,
     458,  442,   21,   21, 0x0a,
     497,  483,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecChsEditWidget[] = {
    "QSttIecChsEditWidget\0\0slot_SetChsTestClicked()\0"
    "slot_SelectAllClicked()\0"
    "slot_UnSelectAllClicked()\0"
    "slot_SelProtCurrClicked()\0"
    "slot_SelMeasCurrClicked()\0"
    "slot_SelVolClicked()\0slot_CurrentMapChanged(int)\0"
    "slot_VoltageMapChanged(int)\0"
    "slot_SetInitValueClicked()\0"
    "slot_DIMapClicked()\0pCurrSelData\0"
    "slot_UpdateCB_ChDatas(CExBaseList*)\0"
    "slot_DcCurrentMapChanged(int)\0"
    "slot_DcVoltageMapChanged(int)\0"
    "slot_AcCurrentMapChanged(int)\0"
    "slot_AcVoltageMapChanged(int)\0"
    "isBinMapEnabled\0slot_BinMapEnabled(bool)\0"
    "bSetInitValue\0slot_SetInitValueEnabled(bool)\0"
};

void QSttIecChsEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecChsEditWidget *_t = static_cast<QSttIecChsEditWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_SetChsTestClicked(); break;
        case 1: _t->slot_SelectAllClicked(); break;
        case 2: _t->slot_UnSelectAllClicked(); break;
        case 3: _t->slot_SelProtCurrClicked(); break;
        case 4: _t->slot_SelMeasCurrClicked(); break;
        case 5: _t->slot_SelVolClicked(); break;
        case 6: _t->slot_CurrentMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_VoltageMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_SetInitValueClicked(); break;
        case 9: _t->slot_DIMapClicked(); break;
        case 10: _t->slot_UpdateCB_ChDatas((*reinterpret_cast< CExBaseList*(*)>(_a[1]))); break;
        case 11: _t->slot_DcCurrentMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_DcVoltageMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_AcCurrentMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slot_AcVoltageMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slot_BinMapEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->slot_SetInitValueEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecChsEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecChsEditWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIecChsEditWidget,
      qt_meta_data_QSttIecChsEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecChsEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecChsEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecChsEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecChsEditWidget))
        return static_cast<void*>(const_cast< QSttIecChsEditWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIecChsEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
