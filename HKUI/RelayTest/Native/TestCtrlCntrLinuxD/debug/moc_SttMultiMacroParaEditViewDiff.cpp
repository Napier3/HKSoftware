/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewDiff.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Diff/SttMultiMacroParaEditViewDiff.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewDiff.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewDiff[] = {

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
      60,   31,   31,   31, 0x0a,
      87,   31,   31,   31, 0x0a,
     110,   31,   31,   31, 0x0a,
     136,   31,   31,   31, 0x0a,
     163,   31,   31,   31, 0x0a,
     202,   31,   31,   31, 0x0a,
     231,   31,   31,   31, 0x0a,
     260,   31,   31,   31, 0x0a,
     290,   31,   31,   31, 0x0a,
     320,   31,   31,   31, 0x0a,
     349,   31,   31,   31, 0x0a,
     377,   31,   31,   31, 0x0a,
     411,  407,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewDiff[] = {
    "QSttMultiMacroParaEditViewDiff\0\0"
    "slot_AddMultiItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_CurrMacroParaEditGridChanged(int)\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0"
    "slot_AddSearchLineBtnClick()\0"
    "slot_AddBatchItemBtnClick()\0"
    "slot_UpdateDiffWiringWidget()\0dIr\0"
    "slot_CalculateId(double)\0"
};

void QSttMultiMacroParaEditViewDiff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewDiff *_t = static_cast<QSttMultiMacroParaEditViewDiff *>(_o);
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
        case 10: _t->slot_AddSearchLineBtnClick(); break;
        case 11: _t->slot_AddBatchItemBtnClick(); break;
        case 12: _t->slot_UpdateDiffWiringWidget(); break;
        case 13: _t->slot_CalculateId((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewDiff::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewDiff::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewDiff,
      qt_meta_data_QSttMultiMacroParaEditViewDiff, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewDiff::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewDiff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewDiff::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewDiff))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewDiff*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewDiff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
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
