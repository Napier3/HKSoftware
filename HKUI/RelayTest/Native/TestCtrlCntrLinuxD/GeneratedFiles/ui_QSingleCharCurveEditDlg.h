/********************************************************************************
** Form generated from reading UI file 'QSingleCharCurveEditDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSINGLECHARCURVEEDITDLG_H
#define UI_QSINGLECHARCURVEEDITDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSingleCharCurveEditDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *m_pCharElementHLayout;
    QPushButton *m_btnModify;
    QPushButton *m_btnDelete;
    QPushButton *m_btnInsert;
    QCheckBox *m_cbAutoClose;
    QVBoxLayout *m_pEditGridVLayout;
    QHBoxLayout *m_pCharWidgetHLayout;
    QHBoxLayout *m_pCharEditBottom_HLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnOk;
    QPushButton *m_btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *QSingleCharCurveEditDlg)
    {
        if (QSingleCharCurveEditDlg->objectName().isEmpty())
            QSingleCharCurveEditDlg->setObjectName(QString::fromUtf8("QSingleCharCurveEditDlg"));
        QSingleCharCurveEditDlg->resize(735, 503);
        horizontalLayout = new QHBoxLayout(QSingleCharCurveEditDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_pCharElementHLayout = new QHBoxLayout();
        m_pCharElementHLayout->setObjectName(QString::fromUtf8("m_pCharElementHLayout"));
        m_btnModify = new QPushButton(QSingleCharCurveEditDlg);
        m_btnModify->setObjectName(QString::fromUtf8("m_btnModify"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_btnModify->sizePolicy().hasHeightForWidth());
        m_btnModify->setSizePolicy(sizePolicy);

        m_pCharElementHLayout->addWidget(m_btnModify);

        m_btnDelete = new QPushButton(QSingleCharCurveEditDlg);
        m_btnDelete->setObjectName(QString::fromUtf8("m_btnDelete"));
        sizePolicy.setHeightForWidth(m_btnDelete->sizePolicy().hasHeightForWidth());
        m_btnDelete->setSizePolicy(sizePolicy);

        m_pCharElementHLayout->addWidget(m_btnDelete);

        m_btnInsert = new QPushButton(QSingleCharCurveEditDlg);
        m_btnInsert->setObjectName(QString::fromUtf8("m_btnInsert"));
        sizePolicy.setHeightForWidth(m_btnInsert->sizePolicy().hasHeightForWidth());
        m_btnInsert->setSizePolicy(sizePolicy);

        m_pCharElementHLayout->addWidget(m_btnInsert);

        m_cbAutoClose = new QCheckBox(QSingleCharCurveEditDlg);
        m_cbAutoClose->setObjectName(QString::fromUtf8("m_cbAutoClose"));
        sizePolicy.setHeightForWidth(m_cbAutoClose->sizePolicy().hasHeightForWidth());
        m_cbAutoClose->setSizePolicy(sizePolicy);

        m_pCharElementHLayout->addWidget(m_cbAutoClose);


        verticalLayout_2->addLayout(m_pCharElementHLayout);

        m_pEditGridVLayout = new QVBoxLayout();
        m_pEditGridVLayout->setObjectName(QString::fromUtf8("m_pEditGridVLayout"));

        verticalLayout_2->addLayout(m_pEditGridVLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        m_pCharWidgetHLayout = new QHBoxLayout();
        m_pCharWidgetHLayout->setObjectName(QString::fromUtf8("m_pCharWidgetHLayout"));
        m_pCharWidgetHLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_2->addLayout(m_pCharWidgetHLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        m_pCharEditBottom_HLayout = new QHBoxLayout();
        m_pCharEditBottom_HLayout->setObjectName(QString::fromUtf8("m_pCharEditBottom_HLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_pCharEditBottom_HLayout->addItem(horizontalSpacer);

        m_btnOk = new QPushButton(QSingleCharCurveEditDlg);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        sizePolicy.setHeightForWidth(m_btnOk->sizePolicy().hasHeightForWidth());
        m_btnOk->setSizePolicy(sizePolicy);

        m_pCharEditBottom_HLayout->addWidget(m_btnOk);

        m_btnCancel = new QPushButton(QSingleCharCurveEditDlg);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        sizePolicy.setHeightForWidth(m_btnCancel->sizePolicy().hasHeightForWidth());
        m_btnCancel->setSizePolicy(sizePolicy);

        m_pCharEditBottom_HLayout->addWidget(m_btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_pCharEditBottom_HLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(m_pCharEditBottom_HLayout);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QSingleCharCurveEditDlg);

        QMetaObject::connectSlotsByName(QSingleCharCurveEditDlg);
    } // setupUi

    void retranslateUi(QDialog *QSingleCharCurveEditDlg)
    {
        QSingleCharCurveEditDlg->setWindowTitle(QApplication::translate("QSingleCharCurveEditDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        m_btnModify->setText(QApplication::translate("QSingleCharCurveEditDlg", "\344\277\256\346\224\271\345\205\203\347\264\240", 0, QApplication::UnicodeUTF8));
        m_btnDelete->setText(QApplication::translate("QSingleCharCurveEditDlg", "\345\210\240\351\231\244\345\205\203\347\264\240", 0, QApplication::UnicodeUTF8));
        m_btnInsert->setText(QApplication::translate("QSingleCharCurveEditDlg", "\346\217\222\345\205\245\345\205\203\347\264\240", 0, QApplication::UnicodeUTF8));
        m_cbAutoClose->setText(QApplication::translate("QSingleCharCurveEditDlg", "\350\276\271\347\225\214\350\207\252\345\212\250\351\227\255\345\220\210", 0, QApplication::UnicodeUTF8));
        m_btnOk->setText(QApplication::translate("QSingleCharCurveEditDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btnCancel->setText(QApplication::translate("QSingleCharCurveEditDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSingleCharCurveEditDlg: public Ui_QSingleCharCurveEditDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSINGLECHARCURVEEDITDLG_H
