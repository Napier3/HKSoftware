/****************************************************************************
** Meta object code from reading C++ file 'QSingleCharCurveEditDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/CharLibWidget/InternationalModeUI/QSingleCharCurveEditDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSingleCharCurveEditDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSingleCharCurveEditDlg[] = {

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
      25,   24,   24,   24, 0x08,
      50,   24,   24,   24, 0x08,
      75,   24,   24,   24, 0x08,
     105,  100,   24,   24, 0x08,
     140,   24,   24,   24, 0x08,
     161,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QSingleCharCurveEditDlg[] = {
    "QSingleCharCurveEditDlg\0\0"
    "on_m_btnModify_clicked()\0"
    "on_m_btnDelete_clicked()\0"
    "on_m_btnInsert_clicked()\0arg1\0"
    "on_m_cbAutoClose_stateChanged(int)\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
};

void QSingleCharCurveEditDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSingleCharCurveEditDlg *_t = static_cast<QSingleCharCurveEditDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnModify_clicked(); break;
        case 1: _t->on_m_btnDelete_clicked(); break;
        case 2: _t->on_m_btnInsert_clicked(); break;
        case 3: _t->on_m_cbAutoClose_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_m_btnOk_clicked(); break;
        case 5: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSingleCharCurveEditDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSingleCharCurveEditDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSingleCharCurveEditDlg,
      qt_meta_data_QSingleCharCurveEditDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSingleCharCurveEditDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSingleCharCurveEditDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSingleCharCurveEditDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSingleCharCurveEditDlg))
        return static_cast<void*>(const_cast< QSingleCharCurveEditDlg*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QSingleCharCurveEditDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSingleCharCurveEditDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
