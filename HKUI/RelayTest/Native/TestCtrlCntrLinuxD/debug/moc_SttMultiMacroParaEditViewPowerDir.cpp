/****************************************************************************
** Meta object code from reading C++ file 'SttMultiMacroParaEditViewPowerDir.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/PowerDirection/SttMultiMacroParaEditViewPowerDir.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMultiMacroParaEditViewPowerDir.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMultiMacroParaEditViewPowerDir[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   36,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   35,   35,   35, 0x0a,
     106,   35,   35,   35, 0x0a,
     134,   35,   35,   35, 0x0a,
     161,   35,   35,   35, 0x0a,
     184,   35,   35,   35, 0x0a,
     210,   35,   35,   35, 0x0a,
     239,   35,   35,   35, 0x0a,
     268,   35,   35,   35, 0x0a,
     295,   35,   35,   35, 0x0a,
     325,   35,   35,   35, 0x0a,
     366,  355,   35,   35, 0x0a,
     410,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMultiMacroParaEditViewPowerDir[] = {
    "QSttMultiMacroParaEditViewPowerDir\0\0"
    "pDatas\0sig_UpdateVectorWidget(CExBaseList*)\0"
    "slot_AddOneItemBtnClick()\0"
    "slot_AddMultiItemBtnClick()\0"
    "slot_CommonParasBtnClick()\0"
    "slot_BinarysBtnClick()\0slot_DeleteItemBtnClick()\0"
    "slot_DeleteSelItemBtnClick()\0"
    "slot_DeleteAllItemBtnClick()\0"
    "slot_ClearResultBtnClick()\0"
    "slot_ClearSelResultBtnClick()\0"
    "slot_ClearAllResultBtnClick()\0pMacroTest\0"
    "slot_ParaEditWidget_To_Grid(CSttMacroTest*)\0"
    "slot_UpdateVetorWidget()\0"
};

void QSttMultiMacroParaEditViewPowerDir::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMultiMacroParaEditViewPowerDir *_t = static_cast<QSttMultiMacroParaEditViewPowerDir *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateVectorWidget((*reinterpret_cast< CExBaseList*(*)>(_a[1]))); break;
        case 1: _t->slot_AddOneItemBtnClick(); break;
        case 2: _t->slot_AddMultiItemBtnClick(); break;
        case 3: _t->slot_CommonParasBtnClick(); break;
        case 4: _t->slot_BinarysBtnClick(); break;
        case 5: _t->slot_DeleteItemBtnClick(); break;
        case 6: _t->slot_DeleteSelItemBtnClick(); break;
        case 7: _t->slot_DeleteAllItemBtnClick(); break;
        case 8: _t->slot_ClearResultBtnClick(); break;
        case 9: _t->slot_ClearSelResultBtnClick(); break;
        case 10: _t->slot_ClearAllResultBtnClick(); break;
        case 11: _t->slot_ParaEditWidget_To_Grid((*reinterpret_cast< CSttMacroTest*(*)>(_a[1]))); break;
        case 12: _t->slot_UpdateVetorWidget(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMultiMacroParaEditViewPowerDir::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMultiMacroParaEditViewPowerDir::staticMetaObject = {
    { &QSttMultiMacroParaEditViewBase::staticMetaObject, qt_meta_stringdata_QSttMultiMacroParaEditViewPowerDir,
      qt_meta_data_QSttMultiMacroParaEditViewPowerDir, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMultiMacroParaEditViewPowerDir::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMultiMacroParaEditViewPowerDir::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMultiMacroParaEditViewPowerDir::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMultiMacroParaEditViewPowerDir))
        return static_cast<void*>(const_cast< QSttMultiMacroParaEditViewPowerDir*>(this));
    return QSttMultiMacroParaEditViewBase::qt_metacast(_clname);
}

int QSttMultiMacroParaEditViewPowerDir::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttMultiMacroParaEditViewBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QSttMultiMacroParaEditViewPowerDir::sig_UpdateVectorWidget(CExBaseList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
