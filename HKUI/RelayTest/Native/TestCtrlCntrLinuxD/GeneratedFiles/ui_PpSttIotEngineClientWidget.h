/********************************************************************************
** Form generated from reading UI file 'PpSttIotEngineClientWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PPSTTIOTENGINECLIENTWIDGET_H
#define UI_PPSTTIOTENGINECLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QPpSttIotEngineClientWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *m_wndVertOptrLayout;
    QGridLayout *m_gridLayOutOptr;
    QPushButton *m_btnStartRpt;
    QPushButton *m_btnReset;
    QPushButton *m_btnReadZone;
    QPushButton *m_btnWriteZone;
    QPushButton *m_btnReadDataset;
    QPushButton *m_btnConnectDevice;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnWriteDataset;
    QPushButton *m_btnCloseDevice;
    QPushButton *m_btnConfigDevice;
    QPushButton *m_btnStopReport;
    QPushButton *m_btnAddDevice;
    QPushButton *m_btnEnumDevice;
    QPushButton *m_btnEnumLDevice;
    QPushButton *m_btnEnumDataset;
    QPushButton *m_btnOpenDvmFile;
    QPushButton *m_btnSaveDvmFile;
    QHBoxLayout *m_wndHorzLayOutArea;

    void setupUi(QDialog *QPpSttIotEngineClientWidget)
    {
        if (QPpSttIotEngineClientWidget->objectName().isEmpty())
            QPpSttIotEngineClientWidget->setObjectName(QString::fromUtf8("QPpSttIotEngineClientWidget"));
        QPpSttIotEngineClientWidget->setWindowModality(Qt::WindowModal);
        QPpSttIotEngineClientWidget->resize(903, 277);
        verticalLayout_2 = new QVBoxLayout(QPpSttIotEngineClientWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_wndVertOptrLayout = new QVBoxLayout();
        m_wndVertOptrLayout->setObjectName(QString::fromUtf8("m_wndVertOptrLayout"));
        m_gridLayOutOptr = new QGridLayout();
        m_gridLayOutOptr->setObjectName(QString::fromUtf8("m_gridLayOutOptr"));
        m_gridLayOutOptr->setContentsMargins(6, 6, 6, 6);
        m_btnStartRpt = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnStartRpt->setObjectName(QString::fromUtf8("m_btnStartRpt"));

        m_gridLayOutOptr->addWidget(m_btnStartRpt, 0, 9, 1, 1);

        m_btnReset = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnReset->setObjectName(QString::fromUtf8("m_btnReset"));

        m_gridLayOutOptr->addWidget(m_btnReset, 0, 8, 1, 1);

        m_btnReadZone = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnReadZone->setObjectName(QString::fromUtf8("m_btnReadZone"));

        m_gridLayOutOptr->addWidget(m_btnReadZone, 0, 6, 1, 1);

        m_btnWriteZone = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnWriteZone->setObjectName(QString::fromUtf8("m_btnWriteZone"));

        m_gridLayOutOptr->addWidget(m_btnWriteZone, 0, 7, 1, 1);

        m_btnReadDataset = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnReadDataset->setObjectName(QString::fromUtf8("m_btnReadDataset"));

        m_gridLayOutOptr->addWidget(m_btnReadDataset, 0, 4, 1, 1);

        m_btnConnectDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnConnectDevice->setObjectName(QString::fromUtf8("m_btnConnectDevice"));

        m_gridLayOutOptr->addWidget(m_btnConnectDevice, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayOutOptr->addItem(horizontalSpacer, 0, 12, 1, 1);

        m_btnWriteDataset = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnWriteDataset->setObjectName(QString::fromUtf8("m_btnWriteDataset"));

        m_gridLayOutOptr->addWidget(m_btnWriteDataset, 0, 5, 1, 1);

        m_btnCloseDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnCloseDevice->setObjectName(QString::fromUtf8("m_btnCloseDevice"));

        m_gridLayOutOptr->addWidget(m_btnCloseDevice, 0, 2, 1, 1);

        m_btnConfigDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnConfigDevice->setObjectName(QString::fromUtf8("m_btnConfigDevice"));

        m_gridLayOutOptr->addWidget(m_btnConfigDevice, 0, 0, 1, 1);

        m_btnStopReport = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnStopReport->setObjectName(QString::fromUtf8("m_btnStopReport"));

        m_gridLayOutOptr->addWidget(m_btnStopReport, 0, 10, 1, 1);

        m_btnAddDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnAddDevice->setObjectName(QString::fromUtf8("m_btnAddDevice"));
        m_btnAddDevice->setEnabled(false);

        m_gridLayOutOptr->addWidget(m_btnAddDevice, 1, 0, 1, 1);

        m_btnEnumDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnEnumDevice->setObjectName(QString::fromUtf8("m_btnEnumDevice"));

        m_gridLayOutOptr->addWidget(m_btnEnumDevice, 0, 3, 1, 1);

        m_btnEnumLDevice = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnEnumLDevice->setObjectName(QString::fromUtf8("m_btnEnumLDevice"));

        m_gridLayOutOptr->addWidget(m_btnEnumLDevice, 1, 1, 1, 1);

        m_btnEnumDataset = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnEnumDataset->setObjectName(QString::fromUtf8("m_btnEnumDataset"));

        m_gridLayOutOptr->addWidget(m_btnEnumDataset, 1, 2, 1, 1);

        m_btnOpenDvmFile = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnOpenDvmFile->setObjectName(QString::fromUtf8("m_btnOpenDvmFile"));

        m_gridLayOutOptr->addWidget(m_btnOpenDvmFile, 1, 3, 1, 1);

        m_btnSaveDvmFile = new QPushButton(QPpSttIotEngineClientWidget);
        m_btnSaveDvmFile->setObjectName(QString::fromUtf8("m_btnSaveDvmFile"));

        m_gridLayOutOptr->addWidget(m_btnSaveDvmFile, 1, 4, 1, 1);


        m_wndVertOptrLayout->addLayout(m_gridLayOutOptr);

        m_wndHorzLayOutArea = new QHBoxLayout();
        m_wndHorzLayOutArea->setObjectName(QString::fromUtf8("m_wndHorzLayOutArea"));

        m_wndVertOptrLayout->addLayout(m_wndHorzLayOutArea);


        verticalLayout_2->addLayout(m_wndVertOptrLayout);


        retranslateUi(QPpSttIotEngineClientWidget);

        QMetaObject::connectSlotsByName(QPpSttIotEngineClientWidget);
    } // setupUi

    void retranslateUi(QDialog *QPpSttIotEngineClientWidget)
    {
        QPpSttIotEngineClientWidget->setWindowTitle(QApplication::translate("QPpSttIotEngineClientWidget", "IotProtcoClient", 0, QApplication::UnicodeUTF8));
        m_btnStartRpt->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\345\220\257\345\212\250\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
        m_btnReset->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\345\244\215\345\275\222", 0, QApplication::UnicodeUTF8));
        m_btnReadZone->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\350\257\273\345\256\232\345\200\274\345\214\272", 0, QApplication::UnicodeUTF8));
        m_btnWriteZone->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\344\277\256\346\224\271\345\256\232\345\200\274\345\214\272", 0, QApplication::UnicodeUTF8));
        m_btnReadDataset->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\350\257\273\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        m_btnConnectDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        m_btnWriteDataset->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\344\277\256\346\224\271\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        m_btnCloseDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\346\226\255\345\274\200", 0, QApplication::UnicodeUTF8));
        m_btnConfigDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnStopReport->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\345\201\234\346\255\242\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
        m_btnAddDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\346\267\273\345\212\240\350\243\205\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnEnumDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\346\236\232\344\270\276\350\243\205\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnEnumLDevice->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\346\236\232\344\270\276\351\200\273\350\276\221\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        m_btnEnumDataset->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\346\236\232\344\270\276\346\225\260\346\215\256\351\233\206", 0, QApplication::UnicodeUTF8));
        m_btnOpenDvmFile->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\345\257\274\345\205\245\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        m_btnSaveDvmFile->setText(QApplication::translate("QPpSttIotEngineClientWidget", "\345\257\274\345\207\272\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QPpSttIotEngineClientWidget: public Ui_QPpSttIotEngineClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PPSTTIOTENGINECLIENTWIDGET_H
