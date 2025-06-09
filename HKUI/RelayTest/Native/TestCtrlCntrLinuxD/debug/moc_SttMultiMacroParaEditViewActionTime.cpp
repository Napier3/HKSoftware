/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewActionTime.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/ActTime/SttMultiMacroParaEditViewActionTime.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewActionTime.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewActionTime[] = {

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
      38,   37,   37,   37, 0x0a,
      64,   37,   37,   37, 0x0a,
      92,   37,   37,   37, 0x0a,
     119,   37,   37,   37, 0x0a,
     142,   37,   37,   37, 0x0a,
     168,   37,   37,   37, 0x0a,
     197,   37,   37,   37, 0x0a,
     226,   37,   37,   37, 0x0a,
     253,   37,   37,   37, 0x0a,
     283,   37,   37,   37, 0x0a,
     324,  313,   37,   37, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewActionTime[] = {
    "QSttMultiMacroParaEditViewActionTime\0"
    "\0slot_AddOneItemBtnClick()\0"
    "slot_AddMultiItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0pMacroTest\0"
    "slot_ParaEditWidget_To_Grid(CSttMacroTest*)\0"
};

void QSttMultiMacroParaEditViewActionTime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewActionTime *_t = static_cast<QSttMultiMacroParaEditViewActionTime *>(_o);
        switch (_id) {
        case 0: _t->slot_AddOneItemBtnClick(); break;
        case 1: _t->slot_AddMultiItemBtnClick(); break;
        case 2: _t->slot_CommonParasBtnClick(); break;
        case 3: _t->slot_BinarysBtnClick(); break;
        case 4: _t->slot_DeleteItemBtnClick(); break;
        case 5: _t->slot_DeleteSelItemBtnClick(); break;
        case 6: _t->slot_DeleteAllItemBtnClick(); break;
        case 7: _t->slot_ClearResultBtnClick(); break;
        case 8: _t->slot_ClearSelResultBtnClick(); break;
        case 9: _t->slot_ClearAllResultBtnClick(); break;
        case 10: _t->slot_ParaEditWidget_To_Grid((*reinterpret_cast< CSttMacroTest*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewActionTime::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewActionTime::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewActionTime,
      qt_meta_data_QSttMultiMacroParaEditViewActionTime, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewActionTime::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewActionTime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewActionTime::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewActionTime))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewActionTime*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewActionTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
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
