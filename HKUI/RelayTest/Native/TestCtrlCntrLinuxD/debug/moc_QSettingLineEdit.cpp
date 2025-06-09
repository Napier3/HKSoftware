/****************************************************************************
** Meta object code from reading C++ file 'QSettingLineEdit.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/SettingCtrls/QSettingLineEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSettingLineEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSettingLineEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      33,   17,   17,   17, 0x0a,
      52,   46,   17,   17, 0x0a,
      70,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QSettingLineEdit[] = {
    "QSettingLineEdit\0\0slot_Setting()\0"
    "slot_Clear()\0bHide\0slot_Cannel(bool)\0"
    "slot_textChanged(QString)\0"
};

void QSettingLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSettingLineEdit *_t = static_cast<QSettingLineEdit *>(_o);
        switch (_id) {
        case 0: _t->slot_Setting(); break;
        case 1: _t->slot_Clear(); break;
        case 2: _t->slot_Cannel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSettingLineEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSettingLineEdit::staticMetaObject = {
    { &QSttLineEdit::staticMetaObject, qt_meta_stringdata_QSettingLineEdit,
      qt_meta_data_QSettingLineEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSettingLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSettingLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSettingLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSettingLineEdit))
        return static_cast<void*>(const_cast< QSettingLineEdit*>(this));
    if (!strcmp(_clname, "CSettingInterface"))
        return static_cast< CSettingInterface*>(const_cast< QSettingLineEdit*>(this));
    return QSttLineEdit::qt_metacast(_clname);
}

int QSettingLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSttLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
