/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewLowVol.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/LowVol/SttMultiMacroParaEditViewLowVol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewLowVol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewLowVol[] = {

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
      34,   33,   33,   33, 0x0a,
      62,   33,   33,   33, 0x0a,
      89,   33,   33,   33, 0x0a,
     112,   33,   33,   33, 0x0a,
     138,   33,   33,   33, 0x0a,
     165,   33,   33,   33, 0x0a,
     204,   33,   33,   33, 0x0a,
     233,   33,   33,   33, 0x0a,
     262,   33,   33,   33, 0x0a,
     292,   33,   33,   33, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewLowVol[] = {
    "QSttMultiMacroParaEditViewLowVol\0\0"
    "slot_AddMultiItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_CurrMacroParaEditGridChanged(int)\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0"
};

void QSttMultiMacroParaEditViewLowVol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewLowVol *_t = static_cast<QSttMultiMacroParaEditViewLowVol *>(_o);
        switch (_id) {
        case 0: _t->slot_AddMultiItemBtnClick(); break;
        case 1: _t->slot_CommonParasBtnClick(); break;
        case 2: _t->slot_BinarysBtnClick(); break;
        case 3: _t->slot_DeleteItemBtnClick(); break;
        case 4: _t->slot_ClearResultBtnClick(); break;
        case 5: _t->slot_CurrMacroParaEditGridChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_DeleteSelItemBtnClick(); break;
        case 7: _t->slot_DeleteAllItemBtnClick(); break;
        case 8: _t->slot_ClearSelResultBtnClick(); break;
        case 9: _t->slot_ClearAllResultBtnClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewLowVol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewLowVol::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewLowVol,
      qt_meta_data_QSttMultiMacroParaEditViewLowVol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewLowVol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewLowVol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewLowVol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewLowVol))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewLowVol*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewLowVol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
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
