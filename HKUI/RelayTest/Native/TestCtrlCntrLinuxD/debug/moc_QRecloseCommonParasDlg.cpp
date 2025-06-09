/****************************************************************************
** Meta object code from reading C++ file 'QRecloseCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/RecloseAcc/QRecloseCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QRecloseCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRecloseCommonParasDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   24,   23,   23, 0x0a,
      51,   24,   23,   23, 0x0a,
      78,   24,   23,   23, 0x0a,
     109,   23,   23,   23, 0x0a,
     130,   23,   23,   23, 0x0a,
     155,   23,   23,   23, 0x0a,
     170,   23,   23,   23, 0x0a,
     192,   23,   23,   23, 0x0a,
     212,   23,   23,   23, 0x0a,
     232,   23,   23,   23, 0x0a,
     254,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QRecloseCommonParasDlg[] = {
    "QRecloseCommonParasDlg\0\0nIndex\0"
    "slot_BinSelect(int)\0slot_OutputSwitchMode(int)\0"
    "slot_SimulateBreakerDelay(int)\0"
    "slot_OKCommonParas()\0slot_CancelCommonParas()\0"
    "slot_CurLoad()\0slot_PowerAngleLoad()\0"
    "slot_BrkBreakTime()\0slot_BrkCloseTime()\0"
    "slot_OutputKeepTime()\0slot_OutputDelayTime()\0"
};

void QRecloseCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRecloseCommonParasDlg *_t = static_cast<QRecloseCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_BinSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_OutputSwitchMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_SimulateBreakerDelay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_OKCommonParas(); break;
        case 4: _t->slot_CancelCommonParas(); break;
        case 5: _t->slot_CurLoad(); break;
        case 6: _t->slot_PowerAngleLoad(); break;
        case 7: _t->slot_BrkBreakTime(); break;
        case 8: _t->slot_BrkCloseTime(); break;
        case 9: _t->slot_OutputKeepTime(); break;
        case 10: _t->slot_OutputDelayTime(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QRecloseCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRecloseCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QRecloseCommonParasDlg,
      qt_meta_data_QRecloseCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRecloseCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRecloseCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRecloseCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRecloseCommonParasDlg))
        return static_cast<void*>(const_cast< QRecloseCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QRecloseCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
