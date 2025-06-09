/****************************************************************************
** Meta object code from reading C++ file 'QttMacroParaEditViewShortTimOver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/ShortTimeOver/QttMacroParaEditViewShortTimOver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QttMacroParaEditViewShortTimOver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QttMacroParaEditViewShortTimOver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x0a,
      64,   33,   33,   33, 0x0a,
      99,   93,   33,   33, 0x0a,
     145,   33,   33,   33, 0x0a,
     178,   33,   33,   33, 0x0a,
     208,   33,   33,   33, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QttMacroParaEditViewShortTimOver[] = {
    "QttMacroParaEditViewShortTimOver\0\0"
    "on_m_edtInflictFloadChanged()\0"
    "om_m_btnSTOverStateChanged()\0index\0"
    "on_m_cmbInflictCount_currentIndexChanged(int)\0"
    "on_m_edtOnceInflictTimeChanged()\0"
    "on_m_edtIntervalTimeChanged()\0"
    "slot_updateParas()\0"
};

void QttMacroParaEditViewShortTimOver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QttMacroParaEditViewShortTimOver *_t = static_cast<QttMacroParaEditViewShortTimOver *>(_o);
        switch (_id) {
        case 0: _t->on_m_edtInflictFloadChanged(); break;
        case 1: _t->om_m_btnSTOverStateChanged(); break;
        case 2: _t->on_m_cmbInflictCount_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_m_edtOnceInflictTimeChanged(); break;
        case 4: _t->on_m_edtIntervalTimeChanged(); break;
        case 5: _t->slot_updateParas(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QttMacroParaEditViewShortTimOver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QttMacroParaEditViewShortTimOver::staticMetaObject = {
    { &CSttMacroParaEditViewOriginal::staticMetaObject, qt_meta_stringdata_QttMacroParaEditViewShortTimOver,
      qt_meta_data_QttMacroParaEditViewShortTimOver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QttMacroParaEditViewShortTimOver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QttMacroParaEditViewShortTimOver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QttMacroParaEditViewShortTimOver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QttMacroParaEditViewShortTimOver))
        return static_cast<void*>(const_cast< QttMacroParaEditViewShortTimOver*>(this));
    return CSttMacroParaEditViewOriginal::qt_metacast(_clname);
}

int QttMacroParaEditViewShortTimOver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CSttMacroParaEditViewOriginal::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
