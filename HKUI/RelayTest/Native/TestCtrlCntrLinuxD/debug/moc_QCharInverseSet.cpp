/****************************************************************************
** Meta object code from reading C++ file 'QCharInverseSet.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/QCharInverseSet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCharInverseSet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharInverseSet[] = {

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
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   35,   16,   16, 0x09,
      72,   35,   16,   16, 0x09,
     107,   35,   16,   16, 0x09,
     142,   16,   16,   16, 0x09,
     179,   16,   16,   16, 0x09,
     216,   16,   16,   16, 0x09,
     253,   16,   16,   16, 0x09,
     290,   16,   16,   16, 0x09,
     327,   16,   16,   16, 0x09,
     364,   16,   16,   16, 0x09,
     396,   16,   16,   16, 0x09,
     416,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QCharInverseSet[] = {
    "QCharInverseSet\0\0sig_CharChanged()\0b\0"
    "slot_oncheckBox_Set1_toggled(bool)\0"
    "slot_oncheckBox_Set2_toggled(bool)\0"
    "slot_oncheckBox_Set3_toggled(bool)\0"
    "slot_onlineEdit_VSet1_editFinished()\0"
    "slot_onlineEdit_VSet2_editFinished()\0"
    "slot_onlineEdit_VSet3_editFinished()\0"
    "slot_onlineEdit_TSet1_editFinished()\0"
    "slot_onlineEdit_TSet2_editFinished()\0"
    "slot_onlineEdit_TSet3_editFinished()\0"
    "slot_ElementData_editFinished()\0"
    "slot_PbnOkClicked()\0slot_PbnCancelClicked()\0"
};

void QCharInverseSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharInverseSet *_t = static_cast<QCharInverseSet *>(_o);
        switch (_id) {
        case 0: _t->sig_CharChanged(); break;
        case 1: _t->slot_oncheckBox_Set1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_oncheckBox_Set2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_oncheckBox_Set3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_onlineEdit_VSet1_editFinished(); break;
        case 5: _t->slot_onlineEdit_VSet2_editFinished(); break;
        case 6: _t->slot_onlineEdit_VSet3_editFinished(); break;
        case 7: _t->slot_onlineEdit_TSet1_editFinished(); break;
        case 8: _t->slot_onlineEdit_TSet2_editFinished(); break;
        case 9: _t->slot_onlineEdit_TSet3_editFinished(); break;
        case 10: _t->slot_ElementData_editFinished(); break;
        case 11: _t->slot_PbnOkClicked(); break;
        case 12: _t->slot_PbnCancelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharInverseSet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharInverseSet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharInverseSet,
      qt_meta_data_QCharInverseSet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharInverseSet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharInverseSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharInverseSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharInverseSet))
        return static_cast<void*>(const_cast< QCharInverseSet*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharInverseSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void QCharInverseSet::sig_CharChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
