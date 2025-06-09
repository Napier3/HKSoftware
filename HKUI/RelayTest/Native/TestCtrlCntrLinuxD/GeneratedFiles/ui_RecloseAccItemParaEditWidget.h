/********************************************************************************
** Form generated from reading UI file 'RecloseAccItemParaEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECLOSEACCITEMPARAEDITWIDGET_H
#define UI_RECLOSEACCITEMPARAEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../UI/Controls/SettingCtrls/QSettingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_QRecloseAccItemParaEditWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *m_gridLayout;
    QLineEdit *m_editFre;
    QComboBox *m_cbbK0Mode;
    QLabel *m_labFre;
    QLabel *m_labAbsErr1;
    CExBaseListComboBox *m_cbbFaultPermanent;
    QLabel *m_labKlKr;
    QLabel *m_labK0Mode;
    QSettingLineEdit *m_editKlKr;
    QLabel *m_labR;
    QLabel *m_labX;
    QLineEdit *m_editX;
    QLabel *m_labTripTime;
    QLabel *m_labUxInputFre;
    QLabel *m_labUxMode;
    QSettingLineEdit *m_editUxInputFre;
    CExBaseListComboBox *m_cbbUxMode;
    QSettingLineEdit *m_editTripTime;
    QSettingLineEdit *m_editUxInputMag;
    QSettingLineEdit *m_editRecloseTime;
    QLabel *m_labRecloseTime;
    QLabel *m_labUxInputMag;
    QSettingLineEdit *m_editUxInputAng;
    QLabel *m_labFaultPermanent;
    QLabel *m_labUxInputAng;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labFaultType;
    QLineEdit *m_editR;
    QLabel *m_labISet;
    QLabel *m_labZ;
    QLabel *m_labZAngle;
    QLineEdit *m_editISet;
    QSettingLineEdit *m_editZAngle;
    QSettingLineEdit *m_editZ;
    CExBaseListComboBox *m_cbbFaultType;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QLabel *m_labRelErr;
    QLineEdit *m_editRelErr;
    QLabel *m_labAngKx;
    QSettingLineEdit *m_editAngKx;
    QLineEdit *m_editAbsErr1;
    QLabel *m_labAbsErr2;
    QLineEdit *m_editAbsErr2;

    void setupUi(QWidget *QRecloseAccItemParaEditWidget)
    {
        if (QRecloseAccItemParaEditWidget->objectName().isEmpty())
            QRecloseAccItemParaEditWidget->setObjectName(QString::fromUtf8("QRecloseAccItemParaEditWidget"));
        QRecloseAccItemParaEditWidget->resize(827, 366);
        horizontalLayout_2 = new QHBoxLayout(QRecloseAccItemParaEditWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_gridLayout = new QGridLayout();
        m_gridLayout->setSpacing(6);
        m_gridLayout->setObjectName(QString::fromUtf8("m_gridLayout"));
        m_gridLayout->setContentsMargins(-1, -1, 10, -1);
        m_editFre = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editFre->setObjectName(QString::fromUtf8("m_editFre"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_editFre->sizePolicy().hasHeightForWidth());
        m_editFre->setSizePolicy(sizePolicy);
        m_editFre->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editFre, 6, 2, 1, 1);

        m_cbbK0Mode = new QComboBox(QRecloseAccItemParaEditWidget);
        m_cbbK0Mode->setObjectName(QString::fromUtf8("m_cbbK0Mode"));
        sizePolicy.setHeightForWidth(m_cbbK0Mode->sizePolicy().hasHeightForWidth());
        m_cbbK0Mode->setSizePolicy(sizePolicy);
        m_cbbK0Mode->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_cbbK0Mode, 7, 2, 1, 1);

        m_labFre = new QLabel(QRecloseAccItemParaEditWidget);
        m_labFre->setObjectName(QString::fromUtf8("m_labFre"));

        m_gridLayout->addWidget(m_labFre, 6, 1, 1, 1);

        m_labAbsErr1 = new QLabel(QRecloseAccItemParaEditWidget);
        m_labAbsErr1->setObjectName(QString::fromUtf8("m_labAbsErr1"));

        m_gridLayout->addWidget(m_labAbsErr1, 7, 4, 1, 1);

        m_cbbFaultPermanent = new CExBaseListComboBox(QRecloseAccItemParaEditWidget);
        m_cbbFaultPermanent->setObjectName(QString::fromUtf8("m_cbbFaultPermanent"));
        sizePolicy.setHeightForWidth(m_cbbFaultPermanent->sizePolicy().hasHeightForWidth());
        m_cbbFaultPermanent->setSizePolicy(sizePolicy);
        m_cbbFaultPermanent->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_cbbFaultPermanent, 2, 5, 1, 1);

        m_labKlKr = new QLabel(QRecloseAccItemParaEditWidget);
        m_labKlKr->setObjectName(QString::fromUtf8("m_labKlKr"));

        m_gridLayout->addWidget(m_labKlKr, 8, 1, 1, 1);

        m_labK0Mode = new QLabel(QRecloseAccItemParaEditWidget);
        m_labK0Mode->setObjectName(QString::fromUtf8("m_labK0Mode"));

        m_gridLayout->addWidget(m_labK0Mode, 7, 1, 1, 1);

        m_editKlKr = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editKlKr->setObjectName(QString::fromUtf8("m_editKlKr"));
        sizePolicy.setHeightForWidth(m_editKlKr->sizePolicy().hasHeightForWidth());
        m_editKlKr->setSizePolicy(sizePolicy);
        m_editKlKr->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editKlKr, 8, 2, 1, 1);

        m_labR = new QLabel(QRecloseAccItemParaEditWidget);
        m_labR->setObjectName(QString::fromUtf8("m_labR"));

        m_gridLayout->addWidget(m_labR, 3, 1, 1, 1);

        m_labX = new QLabel(QRecloseAccItemParaEditWidget);
        m_labX->setObjectName(QString::fromUtf8("m_labX"));

        m_gridLayout->addWidget(m_labX, 4, 1, 1, 1);

        m_editX = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editX->setObjectName(QString::fromUtf8("m_editX"));
        sizePolicy.setHeightForWidth(m_editX->sizePolicy().hasHeightForWidth());
        m_editX->setSizePolicy(sizePolicy);
        m_editX->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editX, 4, 2, 1, 1);

        m_labTripTime = new QLabel(QRecloseAccItemParaEditWidget);
        m_labTripTime->setObjectName(QString::fromUtf8("m_labTripTime"));

        m_gridLayout->addWidget(m_labTripTime, 0, 4, 1, 1);

        m_labUxInputFre = new QLabel(QRecloseAccItemParaEditWidget);
        m_labUxInputFre->setObjectName(QString::fromUtf8("m_labUxInputFre"));

        m_gridLayout->addWidget(m_labUxInputFre, 4, 4, 1, 1);

        m_labUxMode = new QLabel(QRecloseAccItemParaEditWidget);
        m_labUxMode->setObjectName(QString::fromUtf8("m_labUxMode"));

        m_gridLayout->addWidget(m_labUxMode, 3, 4, 1, 1);

        m_editUxInputFre = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editUxInputFre->setObjectName(QString::fromUtf8("m_editUxInputFre"));
        sizePolicy.setHeightForWidth(m_editUxInputFre->sizePolicy().hasHeightForWidth());
        m_editUxInputFre->setSizePolicy(sizePolicy);
        m_editUxInputFre->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editUxInputFre, 4, 5, 1, 1);

        m_cbbUxMode = new CExBaseListComboBox(QRecloseAccItemParaEditWidget);
        m_cbbUxMode->setObjectName(QString::fromUtf8("m_cbbUxMode"));
        sizePolicy.setHeightForWidth(m_cbbUxMode->sizePolicy().hasHeightForWidth());
        m_cbbUxMode->setSizePolicy(sizePolicy);
        m_cbbUxMode->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_cbbUxMode, 3, 5, 1, 1);

        m_editTripTime = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editTripTime->setObjectName(QString::fromUtf8("m_editTripTime"));
        sizePolicy.setHeightForWidth(m_editTripTime->sizePolicy().hasHeightForWidth());
        m_editTripTime->setSizePolicy(sizePolicy);
        m_editTripTime->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editTripTime, 0, 5, 1, 1);

        m_editUxInputMag = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editUxInputMag->setObjectName(QString::fromUtf8("m_editUxInputMag"));
        sizePolicy.setHeightForWidth(m_editUxInputMag->sizePolicy().hasHeightForWidth());
        m_editUxInputMag->setSizePolicy(sizePolicy);
        m_editUxInputMag->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editUxInputMag, 5, 5, 1, 1);

        m_editRecloseTime = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editRecloseTime->setObjectName(QString::fromUtf8("m_editRecloseTime"));
        sizePolicy.setHeightForWidth(m_editRecloseTime->sizePolicy().hasHeightForWidth());
        m_editRecloseTime->setSizePolicy(sizePolicy);
        m_editRecloseTime->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editRecloseTime, 1, 5, 1, 1);

        m_labRecloseTime = new QLabel(QRecloseAccItemParaEditWidget);
        m_labRecloseTime->setObjectName(QString::fromUtf8("m_labRecloseTime"));

        m_gridLayout->addWidget(m_labRecloseTime, 1, 4, 1, 1);

        m_labUxInputMag = new QLabel(QRecloseAccItemParaEditWidget);
        m_labUxInputMag->setObjectName(QString::fromUtf8("m_labUxInputMag"));

        m_gridLayout->addWidget(m_labUxInputMag, 5, 4, 1, 1);

        m_editUxInputAng = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editUxInputAng->setObjectName(QString::fromUtf8("m_editUxInputAng"));
        sizePolicy.setHeightForWidth(m_editUxInputAng->sizePolicy().hasHeightForWidth());
        m_editUxInputAng->setSizePolicy(sizePolicy);
        m_editUxInputAng->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editUxInputAng, 6, 5, 1, 1);

        m_labFaultPermanent = new QLabel(QRecloseAccItemParaEditWidget);
        m_labFaultPermanent->setObjectName(QString::fromUtf8("m_labFaultPermanent"));

        m_gridLayout->addWidget(m_labFaultPermanent, 2, 4, 1, 1);

        m_labUxInputAng = new QLabel(QRecloseAccItemParaEditWidget);
        m_labUxInputAng->setObjectName(QString::fromUtf8("m_labUxInputAng"));

        m_gridLayout->addWidget(m_labUxInputAng, 6, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        m_labFaultType = new QLabel(QRecloseAccItemParaEditWidget);
        m_labFaultType->setObjectName(QString::fromUtf8("m_labFaultType"));

        m_gridLayout->addWidget(m_labFaultType, 0, 1, 1, 1);

        m_editR = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editR->setObjectName(QString::fromUtf8("m_editR"));
        sizePolicy.setHeightForWidth(m_editR->sizePolicy().hasHeightForWidth());
        m_editR->setSizePolicy(sizePolicy);
        m_editR->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editR, 3, 2, 1, 1);

        m_labISet = new QLabel(QRecloseAccItemParaEditWidget);
        m_labISet->setObjectName(QString::fromUtf8("m_labISet"));

        m_gridLayout->addWidget(m_labISet, 5, 1, 1, 1);

        m_labZ = new QLabel(QRecloseAccItemParaEditWidget);
        m_labZ->setObjectName(QString::fromUtf8("m_labZ"));

        m_gridLayout->addWidget(m_labZ, 1, 1, 1, 1);

        m_labZAngle = new QLabel(QRecloseAccItemParaEditWidget);
        m_labZAngle->setObjectName(QString::fromUtf8("m_labZAngle"));

        m_gridLayout->addWidget(m_labZAngle, 2, 1, 1, 1);

        m_editISet = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editISet->setObjectName(QString::fromUtf8("m_editISet"));
        sizePolicy.setHeightForWidth(m_editISet->sizePolicy().hasHeightForWidth());
        m_editISet->setSizePolicy(sizePolicy);
        m_editISet->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editISet, 5, 2, 1, 1);

        m_editZAngle = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editZAngle->setObjectName(QString::fromUtf8("m_editZAngle"));
        sizePolicy.setHeightForWidth(m_editZAngle->sizePolicy().hasHeightForWidth());
        m_editZAngle->setSizePolicy(sizePolicy);
        m_editZAngle->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editZAngle, 2, 2, 1, 1);

        m_editZ = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editZ->setObjectName(QString::fromUtf8("m_editZ"));
        sizePolicy.setHeightForWidth(m_editZ->sizePolicy().hasHeightForWidth());
        m_editZ->setSizePolicy(sizePolicy);
        m_editZ->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editZ, 1, 2, 1, 1);

        m_cbbFaultType = new CExBaseListComboBox(QRecloseAccItemParaEditWidget);
        m_cbbFaultType->setObjectName(QString::fromUtf8("m_cbbFaultType"));
        sizePolicy.setHeightForWidth(m_cbbFaultType->sizePolicy().hasHeightForWidth());
        m_cbbFaultType->setSizePolicy(sizePolicy);
        m_cbbFaultType->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_cbbFaultType, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        m_labRelErr = new QLabel(QRecloseAccItemParaEditWidget);
        m_labRelErr->setObjectName(QString::fromUtf8("m_labRelErr"));

        m_gridLayout->addWidget(m_labRelErr, 9, 4, 1, 1);

        m_editRelErr = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editRelErr->setObjectName(QString::fromUtf8("m_editRelErr"));
        sizePolicy.setHeightForWidth(m_editRelErr->sizePolicy().hasHeightForWidth());
        m_editRelErr->setSizePolicy(sizePolicy);
        m_editRelErr->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editRelErr, 9, 5, 1, 1);

        m_labAngKx = new QLabel(QRecloseAccItemParaEditWidget);
        m_labAngKx->setObjectName(QString::fromUtf8("m_labAngKx"));

        m_gridLayout->addWidget(m_labAngKx, 9, 1, 1, 1);

        m_editAngKx = new QSettingLineEdit(QRecloseAccItemParaEditWidget);
        m_editAngKx->setObjectName(QString::fromUtf8("m_editAngKx"));
        sizePolicy.setHeightForWidth(m_editAngKx->sizePolicy().hasHeightForWidth());
        m_editAngKx->setSizePolicy(sizePolicy);
        m_editAngKx->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editAngKx, 9, 2, 1, 1);

        m_editAbsErr1 = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editAbsErr1->setObjectName(QString::fromUtf8("m_editAbsErr1"));
        sizePolicy.setHeightForWidth(m_editAbsErr1->sizePolicy().hasHeightForWidth());
        m_editAbsErr1->setSizePolicy(sizePolicy);
        m_editAbsErr1->setMinimumSize(QSize(0, 0));
        m_editAbsErr1->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editAbsErr1, 7, 5, 1, 1);

        m_labAbsErr2 = new QLabel(QRecloseAccItemParaEditWidget);
        m_labAbsErr2->setObjectName(QString::fromUtf8("m_labAbsErr2"));

        m_gridLayout->addWidget(m_labAbsErr2, 8, 4, 1, 1);

        m_editAbsErr2 = new QLineEdit(QRecloseAccItemParaEditWidget);
        m_editAbsErr2->setObjectName(QString::fromUtf8("m_editAbsErr2"));
        sizePolicy.setHeightForWidth(m_editAbsErr2->sizePolicy().hasHeightForWidth());
        m_editAbsErr2->setSizePolicy(sizePolicy);
        m_editAbsErr2->setMaximumSize(QSize(150, 16777215));

        m_gridLayout->addWidget(m_editAbsErr2, 8, 5, 1, 1);


        horizontalLayout_2->addLayout(m_gridLayout);


        retranslateUi(QRecloseAccItemParaEditWidget);

        QMetaObject::connectSlotsByName(QRecloseAccItemParaEditWidget);
    } // setupUi

    void retranslateUi(QWidget *QRecloseAccItemParaEditWidget)
    {
        QRecloseAccItemParaEditWidget->setWindowTitle(QApplication::translate("QRecloseAccItemParaEditWidget", "QRecloseAccItemParaEditWidget", 0, QApplication::UnicodeUTF8));
        m_cbbK0Mode->clear();
        m_cbbK0Mode->insertItems(0, QStringList()
         << QApplication::translate("QRecloseAccItemParaEditWidget", "|K0|,Phi(K0)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QRecloseAccItemParaEditWidget", "RERL,XEXL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QRecloseAccItemParaEditWidget", "|Z0/Z1|,Phi(Z0/Z1)", 0, QApplication::UnicodeUTF8)
        );
        m_labFre->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr1->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)+:", 0, QApplication::UnicodeUTF8));
        m_labKlKr->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "K0:", 0, QApplication::UnicodeUTF8));
        m_labK0Mode->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\351\233\266\345\272\217\350\241\245\345\201\277\347\263\273\346\225\260\350\256\241\347\256\227\346\226\271\345\274\217:", 0, QApplication::UnicodeUTF8));
        m_labR->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "R(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labX->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "X(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labTripTime->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\345\212\250\344\275\234\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labUxInputFre->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\346\212\275\345\217\226\347\224\265\345\216\213\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labUxMode->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\346\212\275\345\217\226\347\224\265\345\216\213\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_labRecloseTime->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\351\207\215\345\220\210\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labUxInputMag->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\350\267\263\351\227\270\345\220\216\346\212\275\345\217\226\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labFaultPermanent->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\346\225\205\351\232\234\346\200\247\350\264\250:", 0, QApplication::UnicodeUTF8));
        m_labUxInputAng->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\350\267\263\351\227\270\345\220\216\346\212\275\345\217\226\347\224\265\345\216\213\347\233\270\344\275\215(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labFaultType->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\346\225\205\351\232\234\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        m_labISet->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\347\237\255\350\267\257\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_labZ->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\351\230\273\346\212\227(\316\251):", 0, QApplication::UnicodeUTF8));
        m_labZAngle->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\351\230\273\346\212\227\350\247\222(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labRelErr->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\347\233\270\345\257\271\350\257\257\345\267\256(\357\274\205):", 0, QApplication::UnicodeUTF8));
        m_labAngKx->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "Phi(K0):", 0, QApplication::UnicodeUTF8));
        m_labAbsErr2->setText(QApplication::translate("QRecloseAccItemParaEditWidget", "\347\273\235\345\257\271\350\257\257\345\267\256(s)-:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QRecloseAccItemParaEditWidget: public Ui_QRecloseAccItemParaEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECLOSEACCITEMPARAEDITWIDGET_H
