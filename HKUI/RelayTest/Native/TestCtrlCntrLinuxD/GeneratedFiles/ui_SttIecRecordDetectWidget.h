/********************************************************************************
** Form generated from reading UI file 'SttIecRecordDetectWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTIECRECORDDETECTWIDGET_H
#define UI_STTIECRECORDDETECTWIDGET_H

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
#include "../../UI/Controls/SttCheckBox.h"

QT_BEGIN_NAMESPACE

class Ui_QSttIecRecordDetectWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutNameID;
    QHBoxLayout *m_layButtons;
    QPushButton *m_btnImportIecfg;
    QPushButton *m_btnDetect;
    QPushButton *m_btnDetectStop;
    QPushButton *m_btnClear;
    QPushButton *m_btnBeginRecord;
    QSttCheckBox *m_chkUseSmv;
    QSttCheckBox *m_chkUseGoose;
    QSttCheckBox *m_chkUseFT3;
    QSpacerItem *horizontalSpacer;
    QSttCheckBox *m_chkSmvFirstIsTime;

    void setupUi(QDialog *QSttIecRecordDetectWidget)
    {
        if (QSttIecRecordDetectWidget->objectName().isEmpty())
            QSttIecRecordDetectWidget->setObjectName(QString::fromUtf8("QSttIecRecordDetectWidget"));
        QSttIecRecordDetectWidget->resize(1415, 366);
        verticalLayout_2 = new QVBoxLayout(QSttIecRecordDetectWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayoutNameID = new QGridLayout();
        gridLayoutNameID->setObjectName(QString::fromUtf8("gridLayoutNameID"));

        verticalLayout->addLayout(gridLayoutNameID);

        m_layButtons = new QHBoxLayout();
        m_layButtons->setSpacing(6);
        m_layButtons->setObjectName(QString::fromUtf8("m_layButtons"));
        m_layButtons->setSizeConstraint(QLayout::SetDefaultConstraint);
        m_btnImportIecfg = new QPushButton(QSttIecRecordDetectWidget);
        m_btnImportIecfg->setObjectName(QString::fromUtf8("m_btnImportIecfg"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(18);
        m_btnImportIecfg->setFont(font);

        m_layButtons->addWidget(m_btnImportIecfg);

        m_btnDetect = new QPushButton(QSttIecRecordDetectWidget);
        m_btnDetect->setObjectName(QString::fromUtf8("m_btnDetect"));
        m_btnDetect->setFont(font);

        m_layButtons->addWidget(m_btnDetect);

        m_btnDetectStop = new QPushButton(QSttIecRecordDetectWidget);
        m_btnDetectStop->setObjectName(QString::fromUtf8("m_btnDetectStop"));
        m_btnDetectStop->setFont(font);

        m_layButtons->addWidget(m_btnDetectStop);

        m_btnClear = new QPushButton(QSttIecRecordDetectWidget);
        m_btnClear->setObjectName(QString::fromUtf8("m_btnClear"));
        m_btnClear->setFont(font);

        m_layButtons->addWidget(m_btnClear);

        m_btnBeginRecord = new QPushButton(QSttIecRecordDetectWidget);
        m_btnBeginRecord->setObjectName(QString::fromUtf8("m_btnBeginRecord"));
        m_btnBeginRecord->setFont(font);

        m_layButtons->addWidget(m_btnBeginRecord);

        m_chkUseSmv = new QSttCheckBox(QSttIecRecordDetectWidget);
        m_chkUseSmv->setObjectName(QString::fromUtf8("m_chkUseSmv"));
        m_chkUseSmv->setFont(font);

        m_layButtons->addWidget(m_chkUseSmv);

        m_chkUseGoose = new QSttCheckBox(QSttIecRecordDetectWidget);
        m_chkUseGoose->setObjectName(QString::fromUtf8("m_chkUseGoose"));
        m_chkUseGoose->setFont(font);

        m_layButtons->addWidget(m_chkUseGoose);

        m_chkUseFT3 = new QSttCheckBox(QSttIecRecordDetectWidget);
        m_chkUseFT3->setObjectName(QString::fromUtf8("m_chkUseFT3"));
        m_chkUseFT3->setFont(font);

        m_layButtons->addWidget(m_chkUseFT3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_layButtons->addItem(horizontalSpacer);

        m_chkSmvFirstIsTime = new QSttCheckBox(QSttIecRecordDetectWidget);
        m_chkSmvFirstIsTime->setObjectName(QString::fromUtf8("m_chkSmvFirstIsTime"));
        m_chkSmvFirstIsTime->setFont(font);

        m_layButtons->addWidget(m_chkSmvFirstIsTime);


        verticalLayout->addLayout(m_layButtons);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttIecRecordDetectWidget);

        QMetaObject::connectSlotsByName(QSttIecRecordDetectWidget);
    } // setupUi

    void retranslateUi(QDialog *QSttIecRecordDetectWidget)
    {
        QSttIecRecordDetectWidget->setWindowTitle(QString());
        m_btnImportIecfg->setText(QApplication::translate("QSttIecRecordDetectWidget", "\345\257\274\345\205\245\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        m_btnDetect->setText(QApplication::translate("QSttIecRecordDetectWidget", "\345\274\200\345\247\213\346\216\242\346\265\213", 0, QApplication::UnicodeUTF8));
        m_btnDetectStop->setText(QApplication::translate("QSttIecRecordDetectWidget", " \345\201\234\346\255\242\346\216\242\346\265\213", 0, QApplication::UnicodeUTF8));
        m_btnClear->setText(QApplication::translate("QSttIecRecordDetectWidget", "\346\270\205\347\251\272\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        m_btnBeginRecord->setText(QApplication::translate("QSttIecRecordDetectWidget", "\350\277\233\345\205\245\347\233\221\350\247\206", 0, QApplication::UnicodeUTF8));
        m_chkUseSmv->setText(QApplication::translate("QSttIecRecordDetectWidget", "9-2", 0, QApplication::UnicodeUTF8));
        m_chkUseGoose->setText(QApplication::translate("QSttIecRecordDetectWidget", "GOOSE", 0, QApplication::UnicodeUTF8));
        m_chkUseFT3->setText(QApplication::translate("QSttIecRecordDetectWidget", "FT3", 0, QApplication::UnicodeUTF8));
        m_chkSmvFirstIsTime->setText(QApplication::translate("QSttIecRecordDetectWidget", "SMV\347\254\2541\351\200\232\351\201\223\344\270\272\345\273\266\346\227\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttIecRecordDetectWidget: public Ui_QSttIecRecordDetectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTIECRECORDDETECTWIDGET_H
