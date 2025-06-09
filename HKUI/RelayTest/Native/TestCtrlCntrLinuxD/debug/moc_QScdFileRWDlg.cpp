/****************************************************************************
** Meta object code from reading C++ file 'QScdFileRWDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../61850/Module/SCL_Qt/QScdFileRWDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QScdFileRWDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CScdFileRWDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   15,   14,   14, 0x05,
      56,   46,   14,   14, 0x05,
      78,   14,   14,   14, 0x05,
      97,   14,   14,   14, 0x05,
     117,  110,   14,   14, 0x05,
     149,  138,   14,   14, 0x05,
     194,  170,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     228,   15,   14,   14, 0x0a,
     251,   46,   14,   14, 0x0a,
     274,   14,   14,   14, 0x0a,
     294,   14,   14,   14, 0x0a,
     308,  110,   14,   14, 0x0a,
     330,  138,   14,   14, 0x0a,
     352,  170,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CScdFileRWDlg[] = {
    "CScdFileRWDlg\0\0strTitle\0sig_SetTitle(CString)\0"
    "nMaxRange\0sig_SetMaxRange(long)\0"
    "sig_ResetProcess()\0sig_StepIt()\0strMsg\0"
    "sig_ShowMsg(CString)\0nTimerLong\0"
    "sig_StartTimer(long)\0nMaxRange,nOneStepCount\0"
    "sig_InitThreadProgress(long,long)\0"
    "slot_SetTitle(CString)\0slot_SetMaxRange(long)\0"
    "slot_ResetProcess()\0slot_StepIt()\0"
    "slot_ShowMsg(CString)\0slot_StartTimer(long)\0"
    "slot_InitThreadProgress(long,long)\0"
};

void CScdFileRWDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CScdFileRWDlg *_t = static_cast<CScdFileRWDlg *>(_o);
        switch (_id) {
        case 0: _t->sig_SetTitle((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 1: _t->sig_SetMaxRange((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 2: _t->sig_ResetProcess(); break;
        case 3: _t->sig_StepIt(); break;
        case 4: _t->sig_ShowMsg((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 5: _t->sig_StartTimer((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 6: _t->sig_InitThreadProgress((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 7: _t->slot_SetTitle((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 8: _t->slot_SetMaxRange((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 9: _t->slot_ResetProcess(); break;
        case 10: _t->slot_StepIt(); break;
        case 11: _t->slot_ShowMsg((*reinterpret_cast< const CString(*)>(_a[1]))); break;
        case 12: _t->slot_StartTimer((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 13: _t->slot_InitThreadProgress((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CScdFileRWDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CScdFileRWDlg::staticMetaObject = {
    { &QProgressDialog::staticMetaObject, qt_meta_stringdata_CScdFileRWDlg,
      qt_meta_data_CScdFileRWDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CScdFileRWDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CScdFileRWDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CScdFileRWDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CScdFileRWDlg))
        return static_cast<void*>(const_cast< CScdFileRWDlg*>(this));
    if (!strcmp(_clname, "CThreadProgressInterface"))
        return static_cast< CThreadProgressInterface*>(const_cast< CScdFileRWDlg*>(this));
    return QProgressDialog::qt_metacast(_clname);
}

int CScdFileRWDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProgressDialog::qt_metacall(_c, _id, _a);
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
void CScdFileRWDlg::sig_SetTitle(const CString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CScdFileRWDlg::sig_SetMaxRange(long _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CScdFileRWDlg::sig_ResetProcess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CScdFileRWDlg::sig_StepIt()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CScdFileRWDlg::sig_ShowMsg(const CString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CScdFileRWDlg::sig_StartTimer(long _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CScdFileRWDlg::sig_InitThreadProgress(long _t1, long _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
