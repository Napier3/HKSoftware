/********************************************************************************
** Form generated from reading UI file 'QBinReverseCfgWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QBINREVERSECFGWIDGET_H
#define UI_QBINREVERSECFGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QBinaryReverseCfgWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *m_GLayout_Center;
    QLabel *m_Label_ReserveThreshold;
    QLabel *m_Label_Bin_Text;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *m_Label_BeEmpty;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_Btn_OK;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_Btn_Cancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QBinaryReverseCfgWidget)
    {
        if (QBinaryReverseCfgWidget->objectName().isEmpty())
            QBinaryReverseCfgWidget->setObjectName(QString::fromUtf8("QBinaryReverseCfgWidget"));
        QBinaryReverseCfgWidget->resize(300, 297);
        QBinaryReverseCfgWidget->setMaximumSize(QSize(300, 450));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        QBinaryReverseCfgWidget->setFont(font);
        verticalLayout = new QVBoxLayout(QBinaryReverseCfgWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_GLayout_Center = new QGridLayout();
        m_GLayout_Center->setSpacing(6);
        m_GLayout_Center->setObjectName(QString::fromUtf8("m_GLayout_Center"));
        m_Label_ReserveThreshold = new QLabel(QBinaryReverseCfgWidget);
        m_Label_ReserveThreshold->setObjectName(QString::fromUtf8("m_Label_ReserveThreshold"));
        m_Label_ReserveThreshold->setMaximumSize(QSize(90, 50));
        m_Label_ReserveThreshold->setFont(font);
        m_Label_ReserveThreshold->setAlignment(Qt::AlignCenter);

        m_GLayout_Center->addWidget(m_Label_ReserveThreshold, 0, 2, 1, 1);

        m_Label_Bin_Text = new QLabel(QBinaryReverseCfgWidget);
        m_Label_Bin_Text->setObjectName(QString::fromUtf8("m_Label_Bin_Text"));
        m_Label_Bin_Text->setMaximumSize(QSize(60, 50));
        m_Label_Bin_Text->setFont(font);
        m_Label_Bin_Text->setAlignment(Qt::AlignCenter);

        m_GLayout_Center->addWidget(m_Label_Bin_Text, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        m_GLayout_Center->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        m_GLayout_Center->addItem(verticalSpacer_2, 1, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        m_GLayout_Center->addItem(verticalSpacer_3, 1, 2, 1, 1);

        m_Label_BeEmpty = new QLabel(QBinaryReverseCfgWidget);
        m_Label_BeEmpty->setObjectName(QString::fromUtf8("m_Label_BeEmpty"));
        m_Label_BeEmpty->setMaximumSize(QSize(60, 50));
        m_Label_BeEmpty->setFont(font);
        m_Label_BeEmpty->setAlignment(Qt::AlignCenter);

        m_GLayout_Center->addWidget(m_Label_BeEmpty, 0, 1, 1, 1);

        m_GLayout_Center->setRowStretch(0, 1);
        m_GLayout_Center->setColumnStretch(0, 2);

        verticalLayout->addLayout(m_GLayout_Center);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_Btn_OK = new QPushButton(QBinaryReverseCfgWidget);
        m_Btn_OK->setObjectName(QString::fromUtf8("m_Btn_OK"));
        m_Btn_OK->setMinimumSize(QSize(60, 25));
        m_Btn_OK->setSizeIncrement(QSize(0, 0));

        horizontalLayout->addWidget(m_Btn_OK);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_Btn_Cancel = new QPushButton(QBinaryReverseCfgWidget);
        m_Btn_Cancel->setObjectName(QString::fromUtf8("m_Btn_Cancel"));
        m_Btn_Cancel->setMinimumSize(QSize(60, 25));
        m_Btn_Cancel->setSizeIncrement(QSize(0, 0));

        horizontalLayout->addWidget(m_Btn_Cancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 9);
        verticalLayout->setStretch(1, 1);

        retranslateUi(QBinaryReverseCfgWidget);

        QMetaObject::connectSlotsByName(QBinaryReverseCfgWidget);
    } // setupUi

    void retranslateUi(QWidget *QBinaryReverseCfgWidget)
    {
        QBinaryReverseCfgWidget->setWindowTitle(QApplication::translate("QBinaryReverseCfgWidget", "\345\274\200\345\205\245\351\207\217\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        m_Label_ReserveThreshold->setText(QApplication::translate("QBinaryReverseCfgWidget", "\347\277\273\350\275\254\351\227\250\346\247\233(V)", 0, QApplication::UnicodeUTF8));
        m_Label_Bin_Text->setText(QApplication::translate("QBinaryReverseCfgWidget", "\345\274\200\345\205\245\351\207\217", 0, QApplication::UnicodeUTF8));
        m_Label_BeEmpty->setText(QApplication::translate("QBinaryReverseCfgWidget", "\347\251\272\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        m_Btn_OK->setText(QApplication::translate("QBinaryReverseCfgWidget", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        m_Btn_Cancel->setText(QApplication::translate("QBinaryReverseCfgWidget", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QBinaryReverseCfgWidget: public Ui_QBinaryReverseCfgWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QBINREVERSECFGWIDGET_H
