/****************************************************************************
** Meta object code from reading C++ file 'SttReportViewHtml.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Webkit/SttReportViewHtml.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttReportViewHtml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttReportViewHtml[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      72,   20,   19,   19, 0x05,
     127,   20,   19,   19, 0x05,
     212,  182,   19,   19, 0x05,
     287,  249,   19,   19, 0x05,
     384,  336,   19,   19, 0x05,
     482,  440,   19,   19, 0x05,
     568,  528,   19,   19, 0x05,
     642,  618,   19,   19, 0x05,
     681,   19,   19,   19, 0x05,
     718,  707,   19,   19, 0x05,
     772,  748,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     826,  811,   19,   19, 0x0a,
     854,   20,   19,   19, 0x0a,
     910,   20,   19,   19, 0x0a,
     962,   20,   19,   19, 0x0a,
    1019,  182,   19,   19, 0x0a,
    1055,  249,   19,   19, 0x0a,
    1150, 1102,   19,   19, 0x0a,
    1201,  440,   19,   19, 0x0a,
    1285, 1245,   19,   19, 0x0a,
    1337,  618,   19,   19, 0x0a,
    1379,   19,   19,   19, 0x0a,
    1406,  707,   19,   19, 0x0a,
    1460, 1436,   19,   19, 0x0a,
    1501,  748,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSttReportViewHtml[] = {
    "QSttReportViewHtml\0\0"
    "strParentItemsPath,strItemsID,strRptHtml,strGbDatas\0"
    "msg_InsertRptHtml(QVariant,QVariant,QVariant,QVariant)\0"
    "msg_UpdateRptHtml(QVariant,QVariant,QVariant,QVariant)\0"
    "strParentItemsPath,strItemsID\0"
    "msg_DeleteRptHtml(QVariant,QVariant)\0"
    "strParentItemsPath,strItemID,strState\0"
    "msg_ItemStateChanged(QVariant,QVariant,QVariant)\0"
    "strParentItemsPath,strItemID,strState,strReport\0"
    "msg_FillReportData(QVariant,QVariant,QVariant,QVariant)\0"
    "strParentItemsPath,strItemID,strImgBase64\0"
    "msg_FillReportImg(QVariant,QVariant,QVariant)\0"
    "strParentItemsPath,strItemID,strDataset\0"
    "msg_FillReportDataset(QVariant,QVariant,QVariant)\0"
    "pszRptMapDatas,strState\0"
    "msg_FillRptMapDatas(QVariant,QVariant)\0"
    "msg_QueryReportFillMode()\0strItemsID\0"
    "msg_ClearRptResults(QVariant)\0"
    "strItemsID,strGroupData\0"
    "msg_FillReportTitle(QVariant,QVariant)\0"
    "strRptFillMode\0SetReportFillMode(QVariant)\0"
    "slot_InsertRptHtml(CString,CString,CString,const char*)\0"
    "slot_UpdateRptHtml(CString,CString,CString,CString)\0"
    "slot_UpdateRptHtml2(CString,CString,CString,const char*)\0"
    "slot_DeleteRptHtml(CString,CString)\0"
    "slot_ItemStateChanged(CString,CString,CString)\0"
    "strParentItemsPath,strItemID,strState,pszReport\0"
    "slot_FillReportData(CString,CString,CString,char*)\0"
    "slot_FillReportImg(CString,CString,CString)\0"
    "strParentItemsPath,strItemID,pszDataset\0"
    "slot_FillReportDataset(CString,CString,const char*)\0"
    "slot_FillRptMapDatas(const char*,CString)\0"
    "slot_QueryReportFillMode()\0"
    "slot_ClearRptResults(CString)\0"
    "strItemsID,pszGroupData\0"
    "stt_FillReportTitle(CString,const char*)\0"
    "stt_FillReportTitle(CString,CString)\0"
};

void QSttReportViewHtml::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttReportViewHtml *_t = static_cast<QSttReportViewHtml *>(_o);
        switch (_id) {
        case 0: _t->msg_InsertRptHtml((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4]))); break;
        case 1: _t->msg_UpdateRptHtml((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4]))); break;
        case 2: _t->msg_DeleteRptHtml((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 3: _t->msg_ItemStateChanged((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 4: _t->msg_FillReportData((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4]))); break;
        case 5: _t->msg_FillReportImg((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 6: _t->msg_FillReportDataset((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 7: _t->msg_FillRptMapDatas((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 8: _t->msg_QueryReportFillMode(); break;
        case 9: _t->msg_ClearRptResults((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 10: _t->msg_FillReportTitle((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 11: _t->SetReportFillMode((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 12: _t->slot_InsertRptHtml((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4]))); break;
        case 13: _t->slot_UpdateRptHtml((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3])),(*reinterpret_cast< const CString(*)>(_a[4]))); break;
        case 14: _t->slot_UpdateRptHtml2((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4]))); break;
        case 15: _t->slot_DeleteRptHtml((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2]))); break;
        case 16: _t->slot_ItemStateChanged((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3]))); break;
        case 17: _t->slot_FillReportData((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3])),(*reinterpret_cast< char*(*)>(_a[4]))); break;
        case 18: _t->slot_FillReportImg((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const CString(*)>(_a[3]))); break;
        case 19: _t->slot_FillReportDataset((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3]))); break;
        case 20: _t->slot_FillRptMapDatas((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2]))); break;
        case 21: _t->slot_QueryReportFillMode(); break;
        case 22: _t->slot_ClearRptResults((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 23: _t->stt_FillReportTitle((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 24: _t->stt_FillReportTitle((*reinterpret_cast< const CString(*)>(_a[1])),(*reinterpret_cast< const CString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttReportViewHtml::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttReportViewHtml::staticMetaObject = {
    { &QSttWebViewBase::staticMetaObject, qt_meta_stringdata_QSttReportViewHtml,
      qt_meta_data_QSttReportViewHtml, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttReportViewHtml::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttReportViewHtml::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttReportViewHtml::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttReportViewHtml))
        return static_cast<void*>(const_cast< QSttReportViewHtml*>(this));
    if (!strcmp(_clname, "CSttHtmlReportVIewInterface"))
        return static_cast< CSttHtmlReportVIewInterface*>(const_cast< QSttReportViewHtml*>(this));
    return QSttWebViewBase::qt_metacast(_clname);
}

int QSttReportViewHtml::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttWebViewBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void QSttReportViewHtml::msg_InsertRptHtml(QVariant _t1, QVariant _t2, QVariant _t3, QVariant _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSttReportViewHtml::msg_UpdateRptHtml(QVariant _t1, QVariant _t2, QVariant _t3, QVariant _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSttReportViewHtml::msg_DeleteRptHtml(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSttReportViewHtml::msg_ItemStateChanged(QVariant _t1, QVariant _t2, QVariant _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QSttReportViewHtml::msg_FillReportData(QVariant _t1, QVariant _t2, QVariant _t3, QVariant _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QSttReportViewHtml::msg_FillReportImg(QVariant _t1, QVariant _t2, QVariant _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QSttReportViewHtml::msg_FillReportDataset(QVariant _t1, QVariant _t2, QVariant _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QSttReportViewHtml::msg_FillRptMapDatas(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QSttReportViewHtml::msg_QueryReportFillMode()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void QSttReportViewHtml::msg_ClearRptResults(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QSttReportViewHtml::msg_FillReportTitle(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
