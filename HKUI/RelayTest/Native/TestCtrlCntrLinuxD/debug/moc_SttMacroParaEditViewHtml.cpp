/****************************************************************************
** Meta object code from reading C++ file 'SttMacroParaEditViewHtml.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Webkit/SttMacroParaEditViewHtml.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttMacroParaEditViewHtml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttMacroParaEditViewHtml[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x05,
      46,   39,   26,   26, 0x05,
      70,   39,   26,   26, 0x05,
      93,   39,   26,   26, 0x05,
     116,   39,   26,   26, 0x05,
     160,  138,   26,   26, 0x05,
     196,  138,   26,   26, 0x05,
     241,  229,   26,   26, 0x05,
     283,  268,   26,   26, 0x05,
     324,  313,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     349,   26,   26,   26, 0x0a,
     373,  362,   26,   26, 0x0a,
     414,  401,   26,   26, 0x0a,
     447,  438,   26,   26, 0x0a,
     482,  475,   26,   26, 0x0a,
     520,  509,   26,   26, 0x0a,
     543,  438,   26,   26, 0x0a,
     571,  438,   26,   26, 0x0a,
     606,  598,   26,   26, 0x0a,
     637,  628,   26,   26, 0x0a,
     659,  628,   26,   26, 0x0a,
     700,  684,   26,   26, 0x0a,
     766,  730,   26,   26, 0x0a,
     822,  806,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttMacroParaEditViewHtml[] = {
    "QSttMacroParaEditViewHtml\0\0msg_Debug()\0"
    "object\0msg_SysConfig(QVariant)\0"
    "msg_SetDatas(QVariant)\0msg_GetDatas(QVariant)\0"
    "msg_SetHtml(QVariant)\0strSysParas,strChMaps\0"
    "msg_SetSysConfig(QVariant,QVariant)\0"
    "msg_SetChMaps(QVariant,QVariant)\0"
    "strSysParas\0msg_SetPowerGear(QVariant)\0"
    "strDeviceModel\0msg_SetVersionInfor(QVariant)\0"
    "strLdevice\0msg_SetDevComm(QVariant)\0"
    "slot_Debug()\0pSysConfig\0"
    "slot_SysConfig(CDataGroup*)\0strSysConfig\0"
    "slot_SysConfig(CString)\0pDataset\0"
    "slot_SetDatas(CDvmDataset*)\0pParas\0"
    "slot_SetDatas(CDataGroup*)\0strDataset\0"
    "slot_SetDatas(CString)\0"
    "slot_GetDatas(CDvmDataset*)\0"
    "slot_GetDatas(CDataGroup*)\0strFile\0"
    "slot_SetHtml(CString)\0strParas\0"
    "UpdateDatas(QVariant)\0OnItemsChanged(QVariant)\0"
    "strCmd,strParas\0UI_ExecCmd(QVariant,QVariant)\0"
    "strHtmlFileName,strParas1,strParas2\0"
    "UI_OK_Click(QVariant,QVariant,QVariant)\0"
    "strHtmlFileName\0UI_Cancel_Click(QVariant)\0"
};

void QSttMacroParaEditViewHtml::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttMacroParaEditViewHtml *_t = static_cast<QSttMacroParaEditViewHtml *>(_o);
        switch (_id) {
        case 0: _t->msg_Debug(); break;
        case 1: _t->msg_SysConfig((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->msg_SetDatas((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->msg_GetDatas((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: _t->msg_SetHtml((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->msg_SetSysConfig((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 6: _t->msg_SetChMaps((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 7: _t->msg_SetPowerGear((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 8: _t->msg_SetVersionInfor((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 9: _t->msg_SetDevComm((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 10: _t->slot_Debug(); break;
        case 11: _t->slot_SysConfig((*reinterpret_cast< CDataGroup*(*)>(_a[1]))); break;
        case 12: _t->slot_SysConfig((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 13: _t->slot_SetDatas((*reinterpret_cast< CDvmDataset*(*)>(_a[1]))); break;
        case 14: _t->slot_SetDatas((*reinterpret_cast< CDataGroup*(*)>(_a[1]))); break;
        case 15: _t->slot_SetDatas((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 16: _t->slot_GetDatas((*reinterpret_cast< CDvmDataset*(*)>(_a[1]))); break;
        case 17: _t->slot_GetDatas((*reinterpret_cast< CDataGroup*(*)>(_a[1]))); break;
        case 18: _t->slot_SetHtml((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 19: _t->UpdateDatas((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 20: _t->OnItemsChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 21: _t->UI_ExecCmd((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 22: _t->UI_OK_Click((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 23: _t->UI_Cancel_Click((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttMacroParaEditViewHtml::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttMacroParaEditViewHtml::staticMetaObject = {
    { &QSttWebViewBase::staticMetaObject, qt_meta_stringdata_QSttMacroParaEditViewHtml,
      qt_meta_data_QSttMacroParaEditViewHtml, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttMacroParaEditViewHtml::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttMacroParaEditViewHtml::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttMacroParaEditViewHtml::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttMacroParaEditViewHtml))
        return static_cast<void*>(const_cast< QSttMacroParaEditViewHtml*>(this));
    if (!strcmp(_clname, "CSttMacroParaEditInterface"))
        return static_cast< CSttMacroParaEditInterface*>(const_cast< QSttMacroParaEditViewHtml*>(this));
    return QSttWebViewBase::qt_metacast(_clname);
}

int QSttMacroParaEditViewHtml::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttWebViewBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void QSttMacroParaEditViewHtml::msg_Debug()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSttMacroParaEditViewHtml::msg_SysConfig(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSttMacroParaEditViewHtml::msg_SetDatas(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSttMacroParaEditViewHtml::msg_GetDatas(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QSttMacroParaEditViewHtml::msg_SetHtml(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QSttMacroParaEditViewHtml::msg_SetSysConfig(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QSttMacroParaEditViewHtml::msg_SetChMaps(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QSttMacroParaEditViewHtml::msg_SetPowerGear(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QSttMacroParaEditViewHtml::msg_SetVersionInfor(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QSttMacroParaEditViewHtml::msg_SetDevComm(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
