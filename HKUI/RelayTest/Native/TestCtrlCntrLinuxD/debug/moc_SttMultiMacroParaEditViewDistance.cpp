/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewDistance.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Distance/SttMultiMacroParaEditViewDistance.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewDistance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewDistance[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x0a,
      62,   35,   35,   35, 0x0a,
      90,   35,   35,   35, 0x0a,
     117,   35,   35,   35, 0x0a,
     140,   35,   35,   35, 0x0a,
     166,   35,   35,   35, 0x0a,
     193,   35,   35,   35, 0x0a,
     222,   35,   35,   35, 0x0a,
     251,   35,   35,   35, 0x0a,
     281,   35,   35,   35, 0x0a,
     322,  311,   35,   35, 0x0a,
     366,  311,   35,   35, 0x0a,
     410,   35,   35,   35, 0x08,
     434,   35,   35,   35, 0x08,
     458,   35,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewDistance[] = {
    "QSttMultiMacroParaEditViewDistance\0\0"
    "slot_AddOneItemBtnClick()\0"
    "slot_AddMultiItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0pMacroTest\0"
    "slot_Grid_To_ParaEditWidget(CSttMacroTest*)\0"
    "slot_ParaEditWidget_To_Grid(CSttMacroTest*)\0"
    "slot_AddOneLNBtnClick()\0slot_AddOneLLBtnClick()\0"
    "slot_AddMultBtnClick()\0"
};

void QSttMultiMacroParaEditViewDistance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewDistance *_t = static_cast<QSttMultiMacroParaEditViewDistance *>(_o);
        switch (_id) {
        case 0: _t->slot_AddOneItemBtnClick(); break;
        case 1: _t->slot_AddMultiItemBtnClick(); break;
        case 2: _t->slot_CommonParasBtnClick(); break;
        case 3: _t->slot_BinarysBtnClick(); break;
        case 4: _t->slot_DeleteItemBtnClick(); break;
        case 5: _t->slot_ClearResultBtnClick(); break;
        case 6: _t->slot_DeleteSelItemBtnClick(); break;
        case 7: _t->slot_DeleteAllItemBtnClick(); break;
        case 8: _t->slot_ClearSelResultBtnClick(); break;
        case 9: _t->slot_ClearAllResultBtnClick(); break;
        case 10: _t->slot_Grid_To_ParaEditWidget((*reinterpret_cast< CSttMacroTest*(*)>(_a[1]))); break;
        case 11: _t->slot_ParaEditWidget_To_Grid((*reinterpret_cast< CSttMacroTest*(*)>(_a[1]))); break;
        case 12: _t->slot_AddOneLNBtnClick(); break;
        case 13: _t->slot_AddOneLLBtnClick(); break;
        case 14: _t->slot_AddMultBtnClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewDistance::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewDistance::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewDistance,
      qt_meta_data_QSttMultiMacroParaEditViewDistance, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewDistance::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewDistance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewDistance::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewDistance))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewDistance*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewDistance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
