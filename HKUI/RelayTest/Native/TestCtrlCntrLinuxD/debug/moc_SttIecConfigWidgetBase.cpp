/****************************************************************************
** Meta object code from reading C++ file 'SttIecConfigWidgetBase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/IEC61850Config/SttIecConfigWidgetBase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecConfigWidgetBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecConfigWidgetBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   24,   24,   24, 0x09,
      87,   24,   24,   24, 0x09,
     105,   24,   24,   24, 0x09,
     124,   24,   24,   24, 0x09,
     144,   24,   24,   24, 0x09,
     170,   24,   24,   24, 0x09,
     191,   24,   24,   24, 0x09,
     219,   24,   24,   24, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecConfigWidgetBase[] = {
    "QSttIecConfigWidgetBase\0\0pCB_Data\0"
    "sig_UpdateCB_ChDatas(CExBaseList*)\0"
    "slot_AddClicked()\0slot_DelClicked()\0"
    "slot_CopyClicked()\0slot_PasteClicked()\0"
    "slot_ChannelEditClicked()\0"
    "slot_SelAllClicked()\0slot_UnSelectedAllClicked()\0"
    "OnDeleteN_1Clicked()\0"
};

void QSttIecConfigWidgetBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecConfigWidgetBase *_t = static_cast<QSttIecConfigWidgetBase *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateCB_ChDatas((*reinterpret_cast< CExBaseList*(*)>(_a[1]))); break;
        case 1: _t->slot_AddClicked(); break;
        case 2: _t->slot_DelClicked(); break;
        case 3: _t->slot_CopyClicked(); break;
        case 4: _t->slot_PasteClicked(); break;
        case 5: _t->slot_ChannelEditClicked(); break;
        case 6: _t->slot_SelAllClicked(); break;
        case 7: _t->slot_UnSelectedAllClicked(); break;
        case 8: _t->OnDeleteN_1Clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecConfigWidgetBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecConfigWidgetBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSttIecConfigWidgetBase,
      qt_meta_data_QSttIecConfigWidgetBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecConfigWidgetBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecConfigWidgetBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecConfigWidgetBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecConfigWidgetBase))
        return static_cast<void*>(const_cast< QSttIecConfigWidgetBase*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSttIecConfigWidgetBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSttIecConfigWidgetBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QSttIecConfigWidgetBase::sig_UpdateCB_ChDatas(CExBaseList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
