/****************************************************************************
** Meta object code from reading C++ file 'CharEditWidget_Inverse_Eng.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/InternationalModeUI/CharEditWidget_Inverse_Eng.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CharEditWidget_Inverse_Eng.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharEditWidget_Inverse_Eng[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   29,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   67,   28,   28, 0x09,
     104,   67,   28,   28, 0x09,
     139,   67,   28,   28, 0x09,
     174,   28,   28,   28, 0x09,
     211,   28,   28,   28, 0x09,
     248,   28,   28,   28, 0x09,
     285,   28,   28,   28, 0x09,
     322,   28,   28,   28, 0x09,
     359,   28,   28,   28, 0x09,
     396,   28,   28,   28, 0x09,
     422,   28,   28,   28, 0x09,
     450,  445,   28,   28, 0x09,
     483,   28,   28,   28, 0x09,
     522,  515,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QCharEditWidget_Inverse_Eng[] = {
    "QCharEditWidget_Inverse_Eng\0\0,\0"
    "sig_CharChanged(CExBaseObject*,int)\0"
    "b\0slot_oncheckBox_Set1_toggled(bool)\0"
    "slot_oncheckBox_Set2_toggled(bool)\0"
    "slot_oncheckBox_Set3_toggled(bool)\0"
    "slot_onlineEdit_VSet1_editFinished()\0"
    "slot_onlineEdit_VSet2_editFinished()\0"
    "slot_onlineEdit_VSet3_editFinished()\0"
    "slot_onlineEdit_TSet1_editFinished()\0"
    "slot_onlineEdit_TSet2_editFinished()\0"
    "slot_onlineEdit_TSet3_editFinished()\0"
    "slot_onlineEdit_Changed()\0"
    "on_btnSelect_clicked()\0pObj\0"
    "slot_CIAddChar(CCharacteristic*)\0"
    "slot_ElementData_editFinished()\0bState\0"
    "slot_OnVolModeRadioChanged(bool)\0"
};

void QCharEditWidget_Inverse_Eng::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharEditWidget_Inverse_Eng *_t = static_cast<QCharEditWidget_Inverse_Eng *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged((*reinterpret_cast< CExBaseObject*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_oncheckBox_Set1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_oncheckBox_Set2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_oncheckBox_Set3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_onlineEdit_VSet1_editFinished(); break;
        case 5: _t->slot_onlineEdit_VSet2_editFinished(); break;
        case 6: _t->slot_onlineEdit_VSet3_editFinished(); break;
        case 7: _t->slot_onlineEdit_TSet1_editFinished(); break;
        case 8: _t->slot_onlineEdit_TSet2_editFinished(); break;
        case 9: _t->slot_onlineEdit_TSet3_editFinished(); break;
        case 10: _t->slot_onlineEdit_Changed(); break;
        case 11: _t->on_btnSelect_clicked(); break;
        case 12: _t->slot_CIAddChar((*reinterpret_cast< CCharacteristic*(*)>(_a[1]))); break;
        case 13: _t->slot_ElementData_editFinished(); break;
        case 14: _t->slot_OnVolModeRadioChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharEditWidget_Inverse_Eng::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharEditWidget_Inverse_Eng::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharEditWidget_Inverse_Eng,
      qt_meta_data_QCharEditWidget_Inverse_Eng, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharEditWidget_Inverse_Eng::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharEditWidget_Inverse_Eng::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharEditWidget_Inverse_Eng::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharEditWidget_Inverse_Eng))
        return static_cast<void*>(const_cast< QCharEditWidget_Inverse_Eng*>(this));
    if (!strcmp(_clname, "QCharEditWidgetBase"))
        return static_cast< QCharEditWidgetBase*>(const_cast< QCharEditWidget_Inverse_Eng*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharEditWidget_Inverse_Eng::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void QCharEditWidget_Inverse_Eng::sig_CharChanged(CExBaseObject * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
