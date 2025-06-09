/****************************************************************************
** Meta object code from reading C++ file 'QSttMultiMacroParaEditViewBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/QSttMultiMacroParaEditViewBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSttMultiMacroParaEditViewBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x0a,
      58,   31,   31,   31, 0x0a,
      86,   31,   31,   31, 0x0a,
     113,   31,   31,   31, 0x0a,
     136,   31,   31,   31, 0x0a,
     162,   31,   31,   31, 0x0a,
     189,   31,   31,   31, 0x0a,
     218,   31,   31,   31, 0x0a,
     247,   31,   31,   31, 0x0a,
     277,   31,   31,   31, 0x0a,
     318,  307,   31,   31, 0x0a,
     362,  307,   31,   31, 0x0a,
     406,   31,   31,   31, 0x0a,
     428,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewBase[] = {
    "QSttMultiMacroParaEditViewBase\0\0"
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
    "slot_SelectAllItems()\0slot_DeselectAllItems()\0"
};

void QSttMultiMacroParaEditViewBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewBase *_t = static_cast<QSttMultiMacroParaEditViewBase *>(_o);
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
        case 12: _t->slot_SelectAllItems(); break;
        case 13: _t->slot_DeselectAllItems(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewBase::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewBase,
      qt_meta_data_QSttMultiMacroParaEditViewBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewBase))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewBase*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttMultiMacroParaEditViewBase*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
