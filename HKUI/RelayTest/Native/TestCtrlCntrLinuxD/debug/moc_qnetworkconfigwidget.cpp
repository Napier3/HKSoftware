/****************************************************************************
** Meta object code from reading C++ file 'qnetworkconfigwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Module/UI/Controls/NetworkConfig/qnetworkconfigwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qnetworkconfigwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QNetworkConfigWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x0a,
      57,   41,   21,   21, 0x0a,
      84,   41,   21,   21, 0x0a,
     115,   21,   21,   21, 0x0a,
     137,   21,   21,   21, 0x0a,
     162,   21,   21,   21, 0x0a,
     207,  187,   21,   21, 0x0a,
     251,  187,   21,   21, 0x0a,
     292,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QNetworkConfigWidget[] = {
    "QNetworkConfigWidget\0\0slot_ScanClicked()\0"
    "nCurComboxIndex\0slot_changeNetCardSel(int)\0"
    "slot_changeLocalIPAddrSel(int)\0"
    "slot_btnAdd_clicked()\0slot_btnDelete_clicked()\0"
    "slot_btnModify_clicked()\0strIP,strSubNetMask\0"
    "slot_ModifyTesterIPAsMask(QString&,QString)\0"
    "slot_AddTesterIPAsMask(QString&,QString)\0"
    "slot_CancelClicked()\0"
};

void QNetworkConfigWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QNetworkConfigWidget *_t = static_cast<QNetworkConfigWidget *>(_o);
        switch (_id) {
        case 0: _t->slot_ScanClicked(); break;
        case 1: _t->slot_changeNetCardSel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_changeLocalIPAddrSel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_btnAdd_clicked(); break;
        case 4: _t->slot_btnDelete_clicked(); break;
        case 5: _t->slot_btnModify_clicked(); break;
        case 6: _t->slot_ModifyTesterIPAsMask((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->slot_AddTesterIPAsMask((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->slot_CancelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QNetworkConfigWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QNetworkConfigWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QNetworkConfigWidget,
      qt_meta_data_QNetworkConfigWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QNetworkConfigWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QNetworkConfigWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QNetworkConfigWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QNetworkConfigWidget))
        return static_cast<void*>(const_cast< QNetworkConfigWidget*>(this));
    if (!strcmp(_clname, "CSttMulticastMsgViewInterface"))
        return static_cast< CSttMulticastMsgViewInterface*>(const_cast< QNetworkConfigWidget*>(this));
    if (!strcmp(_clname, "CExBaseListGridOptrInterface"))
        return static_cast< CExBaseListGridOptrInterface*>(const_cast< QNetworkConfigWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int QNetworkConfigWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
