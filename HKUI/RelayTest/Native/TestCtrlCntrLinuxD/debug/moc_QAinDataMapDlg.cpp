/****************************************************************************
** Meta object code from reading C++ file 'QAinDataMapDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Module/AinDataMap/QAinDataMapDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QAinDataMapDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QAinDataMapDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      38,   15,   15,   15, 0x08,
      63,   15,   15,   15, 0x08,
      93,   15,   15,   15, 0x08,
     127,   15,   15,   15, 0x08,
     148,   15,   15,   15, 0x08,
     179,  173,   15,   15, 0x08,
     220,  173,   15,   15, 0x08,
     266,  261,   15,   15, 0x08,
     305,  261,   15,   15, 0x08,
     346,  261,   15,   15, 0x08,
     385,  261,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QAinDataMapDlg[] = {
    "QAinDataMapDlg\0\0on_m_btnAdd_clicked()\0"
    "on_m_btnDelete_clicked()\0"
    "on_m_btnClearAllMap_clicked()\0"
    "on_m_btnClearClickedMap_clicked()\0"
    "on_m_btnOK_clicked()\0on_m_btnCancel_clicked()\0"
    "index\0on_m_cmbDataSet_currentIndexChanged(int)\0"
    "on_m_cmbDevMeas_currentIndexChanged(int)\0"
    "arg1\0on_m_edtPtPrimary_textChanged(QString)\0"
    "on_m_edtPtSecondary_textChanged(QString)\0"
    "on_m_edtCtPrimary_textChanged(QString)\0"
    "on_m_edtCtSecondary_textChanged(QString)\0"
};

void QAinDataMapDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QAinDataMapDlg *_t = static_cast<QAinDataMapDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_btnAdd_clicked(); break;
        case 1: _t->on_m_btnDelete_clicked(); break;
        case 2: _t->on_m_btnClearAllMap_clicked(); break;
        case 3: _t->on_m_btnClearClickedMap_clicked(); break;
        case 4: _t->on_m_btnOK_clicked(); break;
        case 5: _t->on_m_btnCancel_clicked(); break;
        case 6: _t->on_m_cmbDataSet_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_m_cmbDevMeas_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_m_edtPtPrimary_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_m_edtPtSecondary_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_m_edtCtPrimary_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_m_edtCtSecondary_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QAinDataMapDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QAinDataMapDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QAinDataMapDlg,
      qt_meta_data_QAinDataMapDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QAinDataMapDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QAinDataMapDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QAinDataMapDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QAinDataMapDlg))
        return static_cast<void*>(const_cast< QAinDataMapDlg*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QAinDataMapDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QAinDataMapDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
