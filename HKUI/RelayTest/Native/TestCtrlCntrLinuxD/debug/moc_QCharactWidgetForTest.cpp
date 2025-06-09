/****************************************************************************
** Meta object code from reading C++ file 'QCharactWidgetForTest.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/QCharactWidgetForTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCharactWidgetForTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCharactWidgetForTest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      49,   23,   22,   22, 0x05,
     104,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     118,   23,   22,   22, 0x0a,
     174,   22,   22,   22, 0x0a,
     202,   22,   22,   22, 0x0a,
     224,   22,   22,   22, 0x0a,
     247,   22,   22,   22, 0x0a,
     268,   22,   22,   22, 0x0a,
     296,   22,   22,   22, 0x0a,
     318,   22,   22,   22, 0x0a,
     342,   22,   22,   22, 0x0a,
     366,   22,   22,   22, 0x0a,
     391,   22,   22,   22, 0x0a,
     414,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QCharactWidgetForTest[] = {
    "QCharactWidgetForTest\0\0strCharaID,strIndex,dX,dY\0"
    "sig_UpdateCurrTestPoint(QString,QString,double,double)\0"
    "sizeChanged()\0"
    "slot_UpdateCurrTestPoint(QString,QString,double,double)\0"
    "slot_UpdateDrawCharacters()\0"
    "slotDrawOptr_ZoomIn()\0slotDrawOptr_ZoomOut()\0"
    "slotDrawOptr_Reset()\0slot_ActionTestAddClicked()\0"
    "slotDrawOptr_MoveUp()\0slotDrawOptr_MoveDown()\0"
    "slotDrawOptr_MoveLeft()\0"
    "slotDrawOptr_MoveRight()\0"
    "updateButtonPosition()\0slotDrawOptr_SynReset()\0"
};

void QCharactWidgetForTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCharactWidgetForTest *_t = static_cast<QCharactWidgetForTest *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateCurrTestPoint((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 1: _t->sizeChanged(); break;
        case 2: _t->slot_UpdateCurrTestPoint((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 3: _t->slot_UpdateDrawCharacters(); break;
        case 4: _t->slotDrawOptr_ZoomIn(); break;
        case 5: _t->slotDrawOptr_ZoomOut(); break;
        case 6: _t->slotDrawOptr_Reset(); break;
        case 7: _t->slot_ActionTestAddClicked(); break;
        case 8: _t->slotDrawOptr_MoveUp(); break;
        case 9: _t->slotDrawOptr_MoveDown(); break;
        case 10: _t->slotDrawOptr_MoveLeft(); break;
        case 11: _t->slotDrawOptr_MoveRight(); break;
        case 12: _t->updateButtonPosition(); break;
        case 13: _t->slotDrawOptr_SynReset(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCharactWidgetForTest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCharactWidgetForTest::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCharactWidgetForTest,
      qt_meta_data_QCharactWidgetForTest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCharactWidgetForTest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCharactWidgetForTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCharactWidgetForTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCharactWidgetForTest))
        return static_cast<void*>(const_cast< QCharactWidgetForTest*>(this));
    if (!strcmp(_clname, "CInternationalCharactInterface"))
        return static_cast< CInternationalCharactInterface*>(const_cast< QCharactWidgetForTest*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCharactWidgetForTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QCharactWidgetForTest::sig_UpdateCurrTestPoint(QString _t1, QString _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCharactWidgetForTest::sizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
