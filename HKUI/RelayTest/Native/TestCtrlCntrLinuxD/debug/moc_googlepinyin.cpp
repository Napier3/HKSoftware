/****************************************************************************
** Meta object code from reading C++ file 'googlepinyin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/SoftKeyBoard/Keyboard/googlepinyin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googlepinyin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GooglePinYin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   19,   14,   13, 0x0a,
      40,   13,   13,   13, 0x0a,
      48,   13,   13,   13, 0x0a,
      56,   13,   13,   13, 0x0a,
      75,   68,   64,   13, 0x0a,
     105,   99,   91,   13, 0x0a,
     125,  121,   64,   13, 0x0a,
     143,   13,   64,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GooglePinYin[] = {
    "GooglePinYin\0\0bool\0dbPath\0open(QString)\0"
    "close()\0flush()\0reset()\0int\0pinyin\0"
    "select(QString)\0QString\0index\0"
    "getChinese(int)\0pos\0deleteSelect(int)\0"
    "getPosition()\0"
};

void GooglePinYin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GooglePinYin *_t = static_cast<GooglePinYin *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->close(); break;
        case 2: _t->flush(); break;
        case 3: _t->reset(); break;
        case 4: { int _r = _t->select((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->getChinese((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->deleteSelect((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = _t->getPosition();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GooglePinYin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GooglePinYin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GooglePinYin,
      qt_meta_data_GooglePinYin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GooglePinYin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GooglePinYin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GooglePinYin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GooglePinYin))
        return static_cast<void*>(const_cast< GooglePinYin*>(this));
    return QObject::qt_metacast(_clname);
}

int GooglePinYin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
