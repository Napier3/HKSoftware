/********************************************************************************
** Form generated from reading UI file 'QttMacroParaEditViewShortTimOver.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTMACROPARAEDITVIEWSHORTTIMOVER_H
#define UI_QTTMACROPARAEDITVIEWSHORTTIMOVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_QttMacroParaEditViewShortTimOver
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *m_pVBoxLayout;
    QGroupBox *m_boxGroupChoose;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_btnVolSTOver;
    QRadioButton *m_btnCurSTOver;
    QGroupBox *m_boxGroup;
    QGridLayout *gridLayout;
    QSttLineEdit *m_edtOnceInflictTime;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labOnceInflictTime;
    QLabel *m_labFloadID;
    QSttLineEdit *m_edtTotalTime;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_labTotalTime;
    QSttLineEdit *m_edtInflictFload;
    QLabel *m_labInflictFload;
    QLabel *m_labInflictCount;
    QLabel *m_labIntervalTime;
    QLabel *m_labFloadID_3;
    QLabel *m_labFloadID_4;
    QSpacerItem *horizontalSpacer_3;
    QScrollComboBox *m_cmbInflictCount;
    QSttLineEdit *m_edtIntervalTime;
    QLabel *m_labFloadID_2;

    void setupUi(QWidget *QttMacroParaEditViewShortTimOver)
    {
        if (QttMacroParaEditViewShortTimOver->objectName().isEmpty())
            QttMacroParaEditViewShortTimOver->setObjectName(QString::fromUtf8("QttMacroParaEditViewShortTimOver"));
        QttMacroParaEditViewShortTimOver->resize(1041, 773);
        QttMacroParaEditViewShortTimOver->setFocusPolicy(Qt::StrongFocus);
        verticalLayout = new QVBoxLayout(QttMacroParaEditViewShortTimOver);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pVBoxLayout = new QVBoxLayout();
        m_pVBoxLayout->setObjectName(QString::fromUtf8("m_pVBoxLayout"));

        verticalLayout->addLayout(m_pVBoxLayout);

        m_boxGroupChoose = new QGroupBox(QttMacroParaEditViewShortTimOver);
        m_boxGroupChoose->setObjectName(QString::fromUtf8("m_boxGroupChoose"));
        horizontalLayout = new QHBoxLayout(m_boxGroupChoose);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btnVolSTOver = new QRadioButton(m_boxGroupChoose);
        m_btnVolSTOver->setObjectName(QString::fromUtf8("m_btnVolSTOver"));
        m_btnVolSTOver->setAutoExclusive(true);

        horizontalLayout->addWidget(m_btnVolSTOver);

        m_btnCurSTOver = new QRadioButton(m_boxGroupChoose);
        m_btnCurSTOver->setObjectName(QString::fromUtf8("m_btnCurSTOver"));
        m_btnCurSTOver->setAutoExclusive(true);

        horizontalLayout->addWidget(m_btnCurSTOver);


        verticalLayout->addWidget(m_boxGroupChoose);

        m_boxGroup = new QGroupBox(QttMacroParaEditViewShortTimOver);
        m_boxGroup->setObjectName(QString::fromUtf8("m_boxGroup"));
        gridLayout = new QGridLayout(m_boxGroup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_edtOnceInflictTime = new QSttLineEdit(m_boxGroup);
        m_edtOnceInflictTime->setObjectName(QString::fromUtf8("m_edtOnceInflictTime"));

        gridLayout->addWidget(m_edtOnceInflictTime, 0, 12, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 14, 1, 1);

        m_labOnceInflictTime = new QLabel(m_boxGroup);
        m_labOnceInflictTime->setObjectName(QString::fromUtf8("m_labOnceInflictTime"));

        gridLayout->addWidget(m_labOnceInflictTime, 0, 10, 1, 2);

        m_labFloadID = new QLabel(m_boxGroup);
        m_labFloadID->setObjectName(QString::fromUtf8("m_labFloadID"));

        gridLayout->addWidget(m_labFloadID, 0, 3, 1, 1);

        m_edtTotalTime = new QSttLineEdit(m_boxGroup);
        m_edtTotalTime->setObjectName(QString::fromUtf8("m_edtTotalTime"));

        gridLayout->addWidget(m_edtTotalTime, 1, 11, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(19, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 14, 1, 1);

        m_labTotalTime = new QLabel(m_boxGroup);
        m_labTotalTime->setObjectName(QString::fromUtf8("m_labTotalTime"));

        gridLayout->addWidget(m_labTotalTime, 1, 10, 1, 1);

        m_edtInflictFload = new QSttLineEdit(m_boxGroup);
        m_edtInflictFload->setObjectName(QString::fromUtf8("m_edtInflictFload"));

        gridLayout->addWidget(m_edtInflictFload, 0, 1, 1, 2);

        m_labInflictFload = new QLabel(m_boxGroup);
        m_labInflictFload->setObjectName(QString::fromUtf8("m_labInflictFload"));

        gridLayout->addWidget(m_labInflictFload, 0, 0, 1, 1);

        m_labInflictCount = new QLabel(m_boxGroup);
        m_labInflictCount->setObjectName(QString::fromUtf8("m_labInflictCount"));

        gridLayout->addWidget(m_labInflictCount, 0, 5, 1, 1);

        m_labIntervalTime = new QLabel(m_boxGroup);
        m_labIntervalTime->setObjectName(QString::fromUtf8("m_labIntervalTime"));

        gridLayout->addWidget(m_labIntervalTime, 1, 0, 1, 2);

        m_labFloadID_3 = new QLabel(m_boxGroup);
        m_labFloadID_3->setObjectName(QString::fromUtf8("m_labFloadID_3"));

        gridLayout->addWidget(m_labFloadID_3, 1, 13, 1, 1);

        m_labFloadID_4 = new QLabel(m_boxGroup);
        m_labFloadID_4->setObjectName(QString::fromUtf8("m_labFloadID_4"));

        gridLayout->addWidget(m_labFloadID_4, 0, 13, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 9, 1, 1);

        m_cmbInflictCount = new QScrollComboBox(m_boxGroup);
        m_cmbInflictCount->setObjectName(QString::fromUtf8("m_cmbInflictCount"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cmbInflictCount->sizePolicy().hasHeightForWidth());
        m_cmbInflictCount->setSizePolicy(sizePolicy);
        m_cmbInflictCount->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(m_cmbInflictCount, 0, 6, 1, 4);

        m_edtIntervalTime = new QSttLineEdit(m_boxGroup);
        m_edtIntervalTime->setObjectName(QString::fromUtf8("m_edtIntervalTime"));

        gridLayout->addWidget(m_edtIntervalTime, 1, 2, 1, 3);

        m_labFloadID_2 = new QLabel(m_boxGroup);
        m_labFloadID_2->setObjectName(QString::fromUtf8("m_labFloadID_2"));

        gridLayout->addWidget(m_labFloadID_2, 1, 5, 1, 1);


        verticalLayout->addWidget(m_boxGroup);


        retranslateUi(QttMacroParaEditViewShortTimOver);

        QMetaObject::connectSlotsByName(QttMacroParaEditViewShortTimOver);
    } // setupUi

    void retranslateUi(QWidget *QttMacroParaEditViewShortTimOver)
    {
        QttMacroParaEditViewShortTimOver->setWindowTitle(QApplication::translate("QttMacroParaEditViewShortTimOver", "QttMacroParaEditViewShortTimOver", 0, QApplication::UnicodeUTF8));
        m_boxGroupChoose->setTitle(QApplication::translate("QttMacroParaEditViewShortTimOver", "\346\265\213\350\257\225\351\241\271\347\233\256\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        m_btnVolSTOver->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\347\224\265\345\216\213\347\237\255\346\227\266\350\277\207\351\207\217", 0, QApplication::UnicodeUTF8));
        m_btnCurSTOver->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\347\224\265\346\265\201\347\237\255\346\227\266\350\277\207\351\207\217", 0, QApplication::UnicodeUTF8));
        m_boxGroup->setTitle(QApplication::translate("QttMacroParaEditViewShortTimOver", "\346\265\213\350\257\225\346\226\271\346\241\210", 0, QApplication::UnicodeUTF8));
        m_labOnceInflictTime->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\345\215\225\346\254\241\346\226\275\345\212\240\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_labFloadID->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "TextLabel", 0, QApplication::UnicodeUTF8));
        m_labTotalTime->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\350\257\225\351\252\214\346\200\273\346\227\266\351\225\277", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_edtInflictFload->setWhatsThis(QApplication::translate("QttMacroParaEditViewShortTimOver", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        m_labInflictFload->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\346\226\275\345\212\240\345\200\215\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labInflictCount->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\346\226\275\345\212\240\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        m_labIntervalTime->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "\347\233\270\351\202\273\346\226\275\345\212\240\351\227\264\351\232\224\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        m_labFloadID_3->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "s", 0, QApplication::UnicodeUTF8));
        m_labFloadID_4->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "s", 0, QApplication::UnicodeUTF8));
        m_cmbInflictCount->clear();
        m_cmbInflictCount->insertItems(0, QStringList()
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QttMacroParaEditViewShortTimOver", "10", 0, QApplication::UnicodeUTF8)
        );
        m_labFloadID_2->setText(QApplication::translate("QttMacroParaEditViewShortTimOver", "s", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QttMacroParaEditViewShortTimOver: public Ui_QttMacroParaEditViewShortTimOver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTMACROPARAEDITVIEWSHORTTIMOVER_H
