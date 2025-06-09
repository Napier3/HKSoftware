/****************************************************************************
** Meta object code from reading C++ file 'SynResultEstimateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/Syn/SynResultEstimateDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SynResultEstimateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSynResultEstimateDlg[] = {

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
      23,   22,   22,   22, 0x08,
      47,   22,   22,   22, 0x08,
      81,   73,   22,   22, 0x08,
     124,   73,   22,   22, 0x08,
     162,   73,   22,   22, 0x08,
     203,  195,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSynResultEstimateDlg[] = {
    "QSynResultEstimateDlg\0\0on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0strText\0"
    "slot_cmbAllowPressureErrorChanged(QString)\0"
    "slot_cmbPressureErrorChanged(QString)\0"
    "slot_cmbFreErrorChanged(QString)\0"
    "row,col\0slot_OnCellChanged(int,int)\0"
};

void QSynResultEstimateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSynResultEstimateDlg *_t = static_cast<QSynResultEstimateDlg *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->slot_cmbAllowPressureErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slot_cmbPressureErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slot_cmbFreErrorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slot_OnCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSynResultEstimateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSynResultEstimateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QSynResultEstimateDlg,
      qt_meta_data_QSynResultEstimateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSynResultEstimateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSynResultEstimateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSynResultEstimateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSynResultEstimateDlg))
        return static_cast<void*>(const_cast< QSynResultEstimateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QSynResultEstimateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
