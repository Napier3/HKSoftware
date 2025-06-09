/****************************************************************************
** Meta object code from reading C++ file 'DiagramWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/VectorWidget/DiagramWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiagramWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Diagram[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      31,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,    8,    8,    8, 0x08,
      75,    8,    8,    8, 0x08,
      98,    8,    8,    8, 0x08,
     120,    8,    8,    8, 0x08,
     142,    8,    8,    8, 0x08,
     165,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Diagram[] = {
    "Diagram\0\0sig_Pbn_NextClicked()\0"
    "sig_Pbn_PreClicked()\0slot_UZoomOutClicked()\0"
    "slot_IZoomOutClicked()\0slot_UZoomInClicked()\0"
    "slot_IZoomInClicked()\0slot_Pbn_NextClicked()\0"
    "slot_Pbn_PreClicked()\0"
};

void Diagram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Diagram *_t = static_cast<Diagram *>(_o);
        switch (_id) {
        case 0: _t->sig_Pbn_NextClicked(); break;
        case 1: _t->sig_Pbn_PreClicked(); break;
        case 2: _t->slot_UZoomOutClicked(); break;
        case 3: _t->slot_IZoomOutClicked(); break;
        case 4: _t->slot_UZoomInClicked(); break;
        case 5: _t->slot_IZoomInClicked(); break;
        case 6: _t->slot_Pbn_NextClicked(); break;
        case 7: _t->slot_Pbn_PreClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Diagram::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Diagram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Diagram,
      qt_meta_data_Diagram, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Diagram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Diagram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Diagram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Diagram))
        return static_cast<void*>(const_cast< Diagram*>(this));
    return QWidget::qt_metacast(_clname);
}

int Diagram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Diagram::sig_Pbn_NextClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Diagram::sig_Pbn_PreClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
