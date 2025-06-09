/********************************************************************************
** Form generated from reading UI file 'ActionTimeCommonParasDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONTIMECOMMONPARASDLG_H
#define UI_ACTIONTIMECOMMONPARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QActionTimeCommonParasDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *m_gbNormal;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QLabel *m_labPreFre;
    QLineEdit *m_editPreAngle;
    QLineEdit *m_editIPre;
    QLabel *m_labUPre;
    QLineEdit *m_editUPre;
    QLineEdit *m_editPreFaultTime;
    QLabel *m_labTimePre;
    QLabel *m_labPreAng;
    QLabel *m_labIPre;
    QLineEdit *m_editPreFre;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *m_gbFault;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *m_editFaultTime;
    QLabel *m_labFaultTime;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btnOk;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_10;

    void setupUi(QDialog *QActionTimeCommonParasDlg)
    {
        if (QActionTimeCommonParasDlg->objectName().isEmpty())
            QActionTimeCommonParasDlg->setObjectName(QString::fromUtf8("QActionTimeCommonParasDlg"));
        QActionTimeCommonParasDlg->resize(334, 339);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QActionTimeCommonParasDlg->sizePolicy().hasHeightForWidth());
        QActionTimeCommonParasDlg->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(QActionTimeCommonParasDlg);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_gbNormal = new QGroupBox(QActionTimeCommonParasDlg);
        m_gbNormal->setObjectName(QString::fromUtf8("m_gbNormal"));
        horizontalLayout_3 = new QHBoxLayout(m_gbNormal);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame_2 = new QFrame(m_gbNormal);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        m_labPreFre = new QLabel(frame_2);
        m_labPreFre->setObjectName(QString::fromUtf8("m_labPreFre"));

        gridLayout->addWidget(m_labPreFre, 4, 1, 1, 1);

        m_editPreAngle = new QLineEdit(frame_2);
        m_editPreAngle->setObjectName(QString::fromUtf8("m_editPreAngle"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_editPreAngle->sizePolicy().hasHeightForWidth());
        m_editPreAngle->setSizePolicy(sizePolicy1);
        m_editPreAngle->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_editPreAngle, 3, 3, 1, 1);

        m_editIPre = new QLineEdit(frame_2);
        m_editIPre->setObjectName(QString::fromUtf8("m_editIPre"));
        sizePolicy1.setHeightForWidth(m_editIPre->sizePolicy().hasHeightForWidth());
        m_editIPre->setSizePolicy(sizePolicy1);
        m_editIPre->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_editIPre, 2, 3, 1, 1);

        m_labUPre = new QLabel(frame_2);
        m_labUPre->setObjectName(QString::fromUtf8("m_labUPre"));

        gridLayout->addWidget(m_labUPre, 1, 1, 1, 1);

        m_editUPre = new QLineEdit(frame_2);
        m_editUPre->setObjectName(QString::fromUtf8("m_editUPre"));
        sizePolicy1.setHeightForWidth(m_editUPre->sizePolicy().hasHeightForWidth());
        m_editUPre->setSizePolicy(sizePolicy1);
        m_editUPre->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_editUPre, 1, 3, 1, 1);

        m_editPreFaultTime = new QLineEdit(frame_2);
        m_editPreFaultTime->setObjectName(QString::fromUtf8("m_editPreFaultTime"));
        sizePolicy1.setHeightForWidth(m_editPreFaultTime->sizePolicy().hasHeightForWidth());
        m_editPreFaultTime->setSizePolicy(sizePolicy1);
        m_editPreFaultTime->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_editPreFaultTime, 0, 3, 1, 1);

        m_labTimePre = new QLabel(frame_2);
        m_labTimePre->setObjectName(QString::fromUtf8("m_labTimePre"));

        gridLayout->addWidget(m_labTimePre, 0, 1, 1, 1);

        m_labPreAng = new QLabel(frame_2);
        m_labPreAng->setObjectName(QString::fromUtf8("m_labPreAng"));

        gridLayout->addWidget(m_labPreAng, 3, 1, 1, 1);

        m_labIPre = new QLabel(frame_2);
        m_labIPre->setObjectName(QString::fromUtf8("m_labIPre"));

        gridLayout->addWidget(m_labIPre, 2, 1, 1, 1);

        m_editPreFre = new QLineEdit(frame_2);
        m_editPreFre->setObjectName(QString::fromUtf8("m_editPreFre"));
        sizePolicy1.setHeightForWidth(m_editPreFre->sizePolicy().hasHeightForWidth());
        m_editPreFre->setSizePolicy(sizePolicy1);
        m_editPreFre->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(m_editPreFre, 4, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 4, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);


        horizontalLayout_3->addWidget(frame_2);


        verticalLayout_2->addWidget(m_gbNormal);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_gbFault = new QGroupBox(QActionTimeCommonParasDlg);
        m_gbFault->setObjectName(QString::fromUtf8("m_gbFault"));
        horizontalLayout_5 = new QHBoxLayout(m_gbFault);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame = new QFrame(m_gbFault);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        m_editFaultTime = new QLineEdit(frame);
        m_editFaultTime->setObjectName(QString::fromUtf8("m_editFaultTime"));
        sizePolicy1.setHeightForWidth(m_editFaultTime->sizePolicy().hasHeightForWidth());
        m_editFaultTime->setSizePolicy(sizePolicy1);
        m_editFaultTime->setMinimumSize(QSize(150, 0));

        gridLayout_5->addWidget(m_editFaultTime, 0, 3, 1, 1);

        m_labFaultTime = new QLabel(frame);
        m_labFaultTime->setObjectName(QString::fromUtf8("m_labFaultTime"));

        gridLayout_5->addWidget(m_labFaultTime, 0, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_9, 0, 4, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_5);


        horizontalLayout_5->addWidget(frame);


        verticalLayout_4->addWidget(m_gbFault);


        verticalLayout->addLayout(verticalLayout_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        m_btnOk = new QPushButton(QActionTimeCommonParasDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));

        horizontalLayout->addWidget(m_btnOk);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        m_btnCancel = new QPushButton(QActionTimeCommonParasDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));

        horizontalLayout->addWidget(m_btnCancel);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(QActionTimeCommonParasDlg);

        QMetaObject::connectSlotsByName(QActionTimeCommonParasDlg);
    } // setupUi

    void retranslateUi(QDialog *QActionTimeCommonParasDlg)
    {
        QActionTimeCommonParasDlg->setWindowTitle(QApplication::translate("QActionTimeCommonParasDlg", "\351\200\232\347\224\250\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        m_gbNormal->setTitle(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labPreFre->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201\351\242\221\347\216\207(Hz):", 0, QApplication::UnicodeUTF8));
        m_labUPre->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201\347\224\265\345\216\213(V):", 0, QApplication::UnicodeUTF8));
        m_labTimePre->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201\346\227\266\351\227\264(s):", 0, QApplication::UnicodeUTF8));
        m_labPreAng->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201\347\233\270\344\275\215\345\267\256(\302\260):", 0, QApplication::UnicodeUTF8));
        m_labIPre->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\270\270\346\200\201\347\224\265\346\265\201(A):", 0, QApplication::UnicodeUTF8));
        m_gbFault->setTitle(QApplication::translate("QActionTimeCommonParasDlg", "\346\225\205\351\232\234\346\200\201", 0, QApplication::UnicodeUTF8));
        m_labFaultTime->setText(QApplication::translate("QActionTimeCommonParasDlg", "\346\225\205\351\232\234\346\227\266\351\227\264\350\243\225\345\272\246(s):", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QActionTimeCommonParasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QActionTimeCommonParasDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QActionTimeCommonParasDlg: public Ui_QActionTimeCommonParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONTIMECOMMONPARASDLG_H
