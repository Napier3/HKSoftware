/****************************************************************************
** Meta object code from reading C++ file 'qscilexerpostscript.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Qsci/qscilexerpostscript.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qscilexerpostscript.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QsciLexerPostScript[] = {

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
      30,   21,   20,   20, 0x0a,
      54,   48,   20,   20, 0x0a,
      73,   68,   20,   20, 0x0a,
      94,   68,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QsciLexerPostScript[] = {
    "QsciLexerPostScript\0\0tokenize\0"
    "setTokenize(bool)\0level\0setLevel(int)\0"
    "fold\0setFoldCompact(bool)\0setFoldAtElse(bool)\0"
};

void QsciLexerPostScript::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QsciLexerPostScript *_t = static_cast<QsciLexerPostScript *>(_o);
        switch (_id) {
        case 0: _t->setTokenize((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setFoldCompact((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setFoldAtElse((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QsciLexerPostScript::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QsciLexerPostScript::staticMetaObject = {
    { &QsciLexer::staticMetaObject, qt_meta_stringdata_QsciLexerPostScript,
      qt_meta_data_QsciLexerPostScript, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QsciLexerPostScript::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QsciLexerPostScript::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QsciLexerPostScript::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsciLexerPostScript))
        return static_cast<void*>(const_cast< QsciLexerPostScript*>(this));
    return QsciLexer::qt_metacast(_clname);
}

int QsciLexerPostScript::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QsciLexer::qt_metacall(_c, _id, _a);
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
