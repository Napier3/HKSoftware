/****************************************************************************
** Meta object code from reading C++ file 'SttIecFT3LineNumberPlanTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/RecordTest/UI/FT3_Test/SttIecFT3LineNumberPlanTextEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SttIecFT3LineNumberPlanTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSttIecFT3LineNumberPlanTextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      48,   34,   33,   33, 0x08,
      79,   33,   33,   33, 0x08,
     104,  102,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSttIecFT3LineNumberPlanTextEdit[] = {
    "QSttIecFT3LineNumberPlanTextEdit\0\0"
    "newBlockCount\0updateLineNumberAreaWidth(int)\0"
    "highlightCurrentLine()\0,\0"
    "updateLineNumberArea(QRect,int)\0"
};

void QSttIecFT3LineNumberPlanTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSttIecFT3LineNumberPlanTextEdit *_t = static_cast<QSttIecFT3LineNumberPlanTextEdit *>(_o);
        switch (_id) {
        case 0: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->highlightCurrentLine(); break;
        case 2: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSttIecFT3LineNumberPlanTextEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSttIecFT3LineNumberPlanTextEdit::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_QSttIecFT3LineNumberPlanTextEdit,
      qt_meta_data_QSttIecFT3LineNumberPlanTextEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSttIecFT3LineNumberPlanTextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSttIecFT3LineNumberPlanTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSttIecFT3LineNumberPlanTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSttIecFT3LineNumberPlanTextEdit))
        return static_cast<void*>(const_cast< QSttIecFT3LineNumberPlanTextEdit*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int QSttIecFT3LineNumberPlanTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
