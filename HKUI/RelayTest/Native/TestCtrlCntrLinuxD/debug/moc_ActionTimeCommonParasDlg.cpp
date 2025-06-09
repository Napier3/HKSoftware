/****************************************************************************
** Meta object code from reading C++ file 'ActionTimeCommonParasDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/TestUI/ActTime/ActionTimeCommonParasDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActionTimeCommonParasDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QActionTimeCommonParasDlg[] = {

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
      27,   26,   26,   26, 0x08,
      67,   26,   26,   26, 0x08,
      99,   26,   26,   26, 0x08,
     131,   26,   26,   26, 0x08,
     167,   26,   26,   26, 0x08,
     201,   26,   26,   26, 0x08,
     238,   26,   26,   26, 0x08,
     259,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QActionTimeCommonParasDlg[] = {
    "QActionTimeCommonParasDlg\0\0"
    "on_m_editPreFaultTime_editingFinished()\0"
    "on_m_editUPre_editingFinished()\0"
    "on_m_editIPre_editingFinished()\0"
    "on_m_editPreAngle_editingFinished()\0"
    "on_m_editPreFre_editingFinished()\0"
    "on_m_editFaultTime_editingFinished()\0"
    "on_m_btnOk_clicked()\0on_m_btnCancel_clicked()\0"
};

void QActionTimeCommonParasDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QActionTimeCommonParasDlg *_t = static_cast<QActionTimeCommonParasDlg *>(_o);
        switch (_id) {
        case 0: _t->on_m_editPreFaultTime_editingFinished(); break;
        case 1: _t->on_m_editUPre_editingFinished(); break;
        case 2: _t->on_m_editIPre_editingFinished(); break;
        case 3: _t->on_m_editPreAngle_editingFinished(); break;
        case 4: _t->on_m_editPreFre_editingFinished(); break;
        case 5: _t->on_m_editFaultTime_editingFinished(); break;
        case 6: _t->on_m_btnOk_clicked(); break;
        case 7: _t->on_m_btnCancel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QActionTimeCommonParasDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QActionTimeCommonParasDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QActionTimeCommonParasDlg,
      qt_meta_data_QActionTimeCommonParasDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QActionTimeCommonParasDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QActionTimeCommonParasDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QActionTimeCommonParasDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QActionTimeCommonParasDlg))
        return static_cast<void*>(const_cast< QActionTimeCommonParasDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QActionTimeCommonParasDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
