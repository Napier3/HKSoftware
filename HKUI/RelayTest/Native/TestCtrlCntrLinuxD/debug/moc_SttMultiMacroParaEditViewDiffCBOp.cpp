/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewDiffCBOp.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/DiffCBOp/SttMultiMacroParaEditViewDiffCBOp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewDiffCBOp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewDiffCBOp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x0a,
      62,   35,   35,   35, 0x0a,
      89,   35,   35,   35, 0x0a,
     112,   35,   35,   35, 0x0a,
     138,   35,   35,   35, 0x0a,
     165,   35,   35,   35, 0x0a,
     194,   35,   35,   35, 0x0a,
     223,   35,   35,   35, 0x0a,
     253,   35,   35,   35, 0x0a,
     296,  283,   35,   35, 0x0a,
     323,   35,   35,   35, 0x0a,
     353,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewDiffCBOp[] = {
    "QSttMultiMacroParaEditViewDiffCBOp\0\0"
    "slot_AddOneItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0"
    "strImagePath\0slot_strImagePath(QString)\0"
    "slot_ResultEstimateBtnClick()\0"
    "slot_UpdateDiffCBOpWiringWidget()\0"
};

void QSttMultiMacroParaEditViewDiffCBOp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewDiffCBOp *_t = static_cast<QSttMultiMacroParaEditViewDiffCBOp *>(_o);
        switch (_id) {
        case 0: _t->slot_AddOneItemBtnClick(); break;
        case 1: _t->slot_CommonParasBtnClick(); break;
        case 2: _t->slot_BinarysBtnClick(); break;
        case 3: _t->slot_DeleteItemBtnClick(); break;
        case 4: _t->slot_ClearResultBtnClick(); break;
        case 5: _t->slot_DeleteSelItemBtnClick(); break;
        case 6: _t->slot_DeleteAllItemBtnClick(); break;
        case 7: _t->slot_ClearSelResultBtnClick(); break;
        case 8: _t->slot_ClearAllResultBtnClick(); break;
        case 9: _t->slot_strImagePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->slot_ResultEstimateBtnClick(); break;
        case 11: _t->slot_UpdateDiffCBOpWiringWidget(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewDiffCBOp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewDiffCBOp::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewDiffCBOp,
      qt_meta_data_QSttMultiMacroParaEditViewDiffCBOp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewDiffCBOp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewDiffCBOp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewDiffCBOp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewDiffCBOp))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewDiffCBOp*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewDiffCBOp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
