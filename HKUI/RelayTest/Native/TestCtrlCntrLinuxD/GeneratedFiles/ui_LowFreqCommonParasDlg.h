/********************************************************************************
** Form generated from reading UI file 'LowFreqCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOWFREQCOMMONPARASDLG_H
#define UI_LOWFREQCOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QLowFreqCommonParasDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *m_labPreFaultTime;
    QLineEdit *m_txt_SteadyTime;
    QLabel *m_labFaultTrig;
    QComboBox *m_cmb_VBlock;
    QRadioButton *m_rBtn_SettingValue;
    QRadioButton *m_rBtn_FreqChange;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnOK;
    QPushButton *m_btnCancel;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *QLowFreqCommonParasDlg)
    {
        if (QLowFreqCommonParasDlg->objectName().isEmpty())
            QLowFreqCommonParasDlg->setObjectName(QString::fromUtf8("QLowFreqCommonParasDlg"));
        QLowFreqCommonParasDlg->resize(304, 296);
        verticalLayout = new QVBoxLayout(QLowFreqCommonParasDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(QLowFreqCommonParasDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_labPreFaultTime = new QLabel(frame);
        m_labPreFaultTime->setObjectName(QString::fromUtf8("m_labPreFaultTime"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labPreFaultTime->sizePolicy().hasHeightForWidth());
        m_labPreFaultTime->setSizePolicy(sizePolicy);
        m_labPreFaultTime->setMinimumSize(QSize(130, 0));
        m_labPreFaultTime->setMaximumSize(QSize(130, 16777215));

        gridLayout->addWidget(m_labPreFaultTime, 0, 0, 1, 1);

        m_txt_SteadyTime = new QLineEdit(frame);
        m_txt_SteadyTime->setObjectName(QString::fromUtf8("m_txt_SteadyTime"));
        sizePolicy.setHeightForWidth(m_txt_SteadyTime->sizePolicy().hasHeightForWidth());
        m_txt_SteadyTime->setSizePolicy(sizePolicy);
        m_txt_SteadyTime->setMinimumSize(QSize(130, 0));
        m_txt_SteadyTime->setMaximumSize(QSize(130, 16777215));

        gridLayout->addWidget(m_txt_SteadyTime, 0, 1, 1, 1);

        m_labFaultTrig = new QLabel(frame);
        m_labFaultTrig->setObjectName(QString::fromUtf8("m_labFaultTrig"));
        sizePolicy.setHeightForWidth(m_labFaultTrig->sizePolicy().hasHeightForWidth());
        m_labFaultTrig->setSizePolicy(sizePolicy);
        m_labFaultTrig->setMinimumSize(QSize(130, 0));
        m_labFaultTrig->setMaximumSize(QSize(130, 16777215));

        gridLayout->addWidget(m_labFaultTrig, 1, 0, 1, 1);

        m_cmb_VBlock = new QComboBox(frame);
        m_cmb_VBlock->setObjectName(QString::fromUtf8("m_cmb_VBlock"));
        sizePolicy.setHeightForWidth(m_cmb_VBlock->sizePolicy().hasHeightForWidth());
        m_cmb_VBlock->setSizePolicy(sizePolicy);
        m_cmb_VBlock->setMinimumSize(QSize(130, 0));
        m_cmb_VBlock->setMaximumSize(QSize(130, 16777215));

        gridLayout->addWidget(m_cmb_VBlock, 1, 1, 1, 1);

        m_rBtn_SettingValue = new QRadioButton(frame);
        buttonGroup = new QButtonGroup(QLowFreqCommonParasDlg);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(m_rBtn_SettingValue);
        m_rBtn_SettingValue->setObjectName(QString::fromUtf8("m_rBtn_SettingValue"));
        m_rBtn_SettingValue->setChecked(true);

        gridLayout->addWidget(m_rBtn_SettingValue, 2, 0, 1, 2);

        m_rBtn_FreqChange = new QRadioButton(frame);
        buttonGroup->addButton(m_rBtn_FreqChange);
        m_rBtn_FreqChange->setObjectName(QString::fromUtf8("m_rBtn_FreqChange"));
        m_rBtn_FreqChange->setChecked(false);

        gridLayout->addWidget(m_rBtn_FreqChange, 3, 0, 1, 2);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnOK = new QPushButton(QLowFreqCommonParasDlg);
        m_btnOK->setObjectName(QString::fromUtf8("m_btnOK"));
        sizePolicy.setHeightForWidth(m_btnOK->sizePolicy().hasHeightForWidth());
        m_btnOK->setSizePolicy(sizePolicy);
        m_btnOK->setMinimumSize(QSize(100, 0));
        m_btnOK->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(m_btnOK);

        m_btnCancel = new QPushButton(QLowFreqCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);
        m_btnCancel->setMinimumSize(QSize(100, 0));
        m_btnCancel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(m_btnCancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);

        retranslateUi(QLowFreqCommonParasDlg);

        QMetaObject::connectSlotsByName(QLowFreqCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QLowFreqCommonParasDlg)
    {
        QLowFreqCommonParasDlg->setWindowTitle(QApplication::translate("QLowFreqCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_labPreFaultTime->setText(QApplication::translate("QLowFreqCommonParasDlg", "\347\250\263\346\200\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labFaultTrig->setText(QApplication::translate("QLowFreqCommonParasDlg", "\351\227\255\351\224\201\347\224\265\345\216\213\351\200\211\346\213\251:", 0, QApplication::UnicodeUTF8));
        m_rBtn_SettingValue->setText(QApplication::translate("QLowFreqCommonParasDlg", "\346\225\264\345\256\232\345\200\274\344\275\234\344\270\272\350\256\241\346\227\266\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        m_rBtn_FreqChange->setText(QApplication::translate("QLowFreqCommonParasDlg", "\351\242\221\347\216\207\345\217\230\345\214\226\344\275\234\344\270\272\350\256\241\346\227\266\350\265\267\347\202\271", 0, QApplication::UnicodeUTF8));
        m_btnOK->setText(QApplication::translate("QLowFreqCommonParasDlg", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QLowFreqCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLowFreqCommonParasDlg: public Ui_QLowFreqCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOWFREQCOMMONPARASDLG_H
