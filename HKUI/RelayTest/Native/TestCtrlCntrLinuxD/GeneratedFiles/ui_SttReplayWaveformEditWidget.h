/********************************************************************************
** Form generated from reading UI file 'SttReplayWaveformEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTREPLAYWAVEFORMEDITWIDGET_H
#define UI_STTREPLAYWAVEFORMEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_SttReplayWaveformEditWidget
{
public:
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_rb_WaveEdit;
    QRadioButton *m_rb_InsertWave;
    QPushButton *m_pb_Replay;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QWidget *widget_2;
    QGroupBox *m_Insert_GroupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *m_Insert_Layout;
    QFloatLineEdit *m_edt_InsertCycNum;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLabel *label_2;
    QFloatLineEdit *m_edt_InsertBegin;
    QLabel *m_lb_InsertBegin;
    QFloatLineEdit *m_edt_InsertEnd;
    QComboBox *m_Cbox_InsertType;
    QLabel *label;
    QGroupBox *m_InsertNomal_GroupBox;
    QWidget *gridLayoutWidget_4;
    QGridLayout *m_Insert_Layout_3;
    QFloatLineEdit *m_edt_InsertNormaloutTime;
    QLabel *label_8;
    QFloatLineEdit *m_edt_InsertNormalCur;
    QSpacerItem *horizontalSpacer_3;
    QFloatLineEdit *m_edt_InsertNormalVal;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_12;
    QComboBox *comboBox;
    QGroupBox *m_DeleteWave_GroupBox;
    QWidget *gridLayoutWidget_3;
    QGridLayout *m_Insert_Layout_2;
    QFloatLineEdit *m_edt_DeleteEnd;
    QLabel *label_4;
    QLabel *label_6;
    QFloatLineEdit *m_edt_DeleteBegin;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pb_delete;
    QPushButton *m_pb_Insert;

    void setupUi(QWidget *SttReplayWaveformEditWidget)
    {
        if (SttReplayWaveformEditWidget->objectName().isEmpty())
            SttReplayWaveformEditWidget->setObjectName(QString::fromUtf8("SttReplayWaveformEditWidget"));
        SttReplayWaveformEditWidget->resize(948, 610);
        SttReplayWaveformEditWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_8 = new QVBoxLayout(SttReplayWaveformEditWidget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        widget = new QWidget(SttReplayWaveformEditWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayoutWidget = new QWidget(widget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 921, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_rb_WaveEdit = new QRadioButton(horizontalLayoutWidget);
        m_rb_WaveEdit->setObjectName(QString::fromUtf8("m_rb_WaveEdit"));

        horizontalLayout->addWidget(m_rb_WaveEdit);

        m_rb_InsertWave = new QRadioButton(horizontalLayoutWidget);
        m_rb_InsertWave->setObjectName(QString::fromUtf8("m_rb_InsertWave"));

        horizontalLayout->addWidget(m_rb_InsertWave);

        m_pb_Replay = new QPushButton(horizontalLayoutWidget);
        m_pb_Replay->setObjectName(QString::fromUtf8("m_pb_Replay"));
        m_pb_Replay->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(m_pb_Replay);

        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 60, 921, 521));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(gridLayoutWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        m_Insert_GroupBox = new QGroupBox(widget_2);
        m_Insert_GroupBox->setObjectName(QString::fromUtf8("m_Insert_GroupBox"));
        m_Insert_GroupBox->setGeometry(QRect(10, 10, 421, 201));
        gridLayoutWidget_2 = new QWidget(m_Insert_GroupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(30, 20, 371, 171));
        m_Insert_Layout = new QGridLayout(gridLayoutWidget_2);
        m_Insert_Layout->setObjectName(QString::fromUtf8("m_Insert_Layout"));
        m_Insert_Layout->setContentsMargins(0, 0, 0, 0);
        m_edt_InsertCycNum = new QFloatLineEdit(gridLayoutWidget_2);
        m_edt_InsertCycNum->setObjectName(QString::fromUtf8("m_edt_InsertCycNum"));

        m_Insert_Layout->addWidget(m_edt_InsertCycNum, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        m_Insert_Layout->addItem(horizontalSpacer, 1, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        m_Insert_Layout->addWidget(label_3, 3, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setContextMenuPolicy(Qt::NoContextMenu);

        m_Insert_Layout->addWidget(label_2, 2, 0, 1, 1);

        m_edt_InsertBegin = new QFloatLineEdit(gridLayoutWidget_2);
        m_edt_InsertBegin->setObjectName(QString::fromUtf8("m_edt_InsertBegin"));

        m_Insert_Layout->addWidget(m_edt_InsertBegin, 1, 2, 1, 1);

        m_lb_InsertBegin = new QLabel(gridLayoutWidget_2);
        m_lb_InsertBegin->setObjectName(QString::fromUtf8("m_lb_InsertBegin"));
        m_lb_InsertBegin->setMinimumSize(QSize(80, 0));

        m_Insert_Layout->addWidget(m_lb_InsertBegin, 1, 0, 1, 1);

        m_edt_InsertEnd = new QFloatLineEdit(gridLayoutWidget_2);
        m_edt_InsertEnd->setObjectName(QString::fromUtf8("m_edt_InsertEnd"));

        m_Insert_Layout->addWidget(m_edt_InsertEnd, 2, 2, 1, 1);

        m_Cbox_InsertType = new QComboBox(gridLayoutWidget_2);
        m_Cbox_InsertType->setObjectName(QString::fromUtf8("m_Cbox_InsertType"));

        m_Insert_Layout->addWidget(m_Cbox_InsertType, 0, 2, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        m_Insert_Layout->addWidget(label, 0, 0, 1, 1);

        m_InsertNomal_GroupBox = new QGroupBox(widget_2);
        m_InsertNomal_GroupBox->setObjectName(QString::fromUtf8("m_InsertNomal_GroupBox"));
        m_InsertNomal_GroupBox->setGeometry(QRect(450, 10, 421, 201));
        gridLayoutWidget_4 = new QWidget(m_InsertNomal_GroupBox);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(30, 20, 361, 171));
        m_Insert_Layout_3 = new QGridLayout(gridLayoutWidget_4);
        m_Insert_Layout_3->setObjectName(QString::fromUtf8("m_Insert_Layout_3"));
        m_Insert_Layout_3->setContentsMargins(0, 0, 0, 0);
        m_edt_InsertNormaloutTime = new QFloatLineEdit(gridLayoutWidget_4);
        m_edt_InsertNormaloutTime->setObjectName(QString::fromUtf8("m_edt_InsertNormaloutTime"));

        m_Insert_Layout_3->addWidget(m_edt_InsertNormaloutTime, 3, 2, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(150, 0));

        m_Insert_Layout_3->addWidget(label_8, 1, 0, 1, 1);

        m_edt_InsertNormalCur = new QFloatLineEdit(gridLayoutWidget_4);
        m_edt_InsertNormalCur->setObjectName(QString::fromUtf8("m_edt_InsertNormalCur"));

        m_Insert_Layout_3->addWidget(m_edt_InsertNormalCur, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        m_Insert_Layout_3->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        m_edt_InsertNormalVal = new QFloatLineEdit(gridLayoutWidget_4);
        m_edt_InsertNormalVal->setObjectName(QString::fromUtf8("m_edt_InsertNormalVal"));

        m_Insert_Layout_3->addWidget(m_edt_InsertNormalVal, 1, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        m_Insert_Layout_3->addWidget(label_5, 2, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        m_Insert_Layout_3->addWidget(label_7, 3, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        m_Insert_Layout_3->addWidget(label_12, 0, 0, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        m_Insert_Layout_3->addWidget(comboBox, 0, 2, 1, 1);

        m_DeleteWave_GroupBox = new QGroupBox(widget_2);
        m_DeleteWave_GroupBox->setObjectName(QString::fromUtf8("m_DeleteWave_GroupBox"));
        m_DeleteWave_GroupBox->setGeometry(QRect(10, 230, 421, 161));
        gridLayoutWidget_3 = new QWidget(m_DeleteWave_GroupBox);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(30, 20, 371, 131));
        m_Insert_Layout_2 = new QGridLayout(gridLayoutWidget_3);
        m_Insert_Layout_2->setObjectName(QString::fromUtf8("m_Insert_Layout_2"));
        m_Insert_Layout_2->setContentsMargins(0, 0, 0, 0);
        m_edt_DeleteEnd = new QFloatLineEdit(gridLayoutWidget_3);
        m_edt_DeleteEnd->setObjectName(QString::fromUtf8("m_edt_DeleteEnd"));

        m_Insert_Layout_2->addWidget(m_edt_DeleteEnd, 1, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        m_Insert_Layout_2->addWidget(label_4, 1, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        m_Insert_Layout_2->addWidget(label_6, 0, 0, 1, 1);

        m_edt_DeleteBegin = new QFloatLineEdit(gridLayoutWidget_3);
        m_edt_DeleteBegin->setObjectName(QString::fromUtf8("m_edt_DeleteBegin"));

        m_Insert_Layout_2->addWidget(m_edt_DeleteBegin, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        m_Insert_Layout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        m_pb_delete = new QPushButton(widget_2);
        m_pb_delete->setObjectName(QString::fromUtf8("m_pb_delete"));
        m_pb_delete->setGeometry(QRect(550, 340, 75, 41));
        m_pb_delete->setMaximumSize(QSize(16777215, 902));
        m_pb_Insert = new QPushButton(widget_2);
        m_pb_Insert->setObjectName(QString::fromUtf8("m_pb_Insert"));
        m_pb_Insert->setGeometry(QRect(680, 340, 75, 41));

        gridLayout_2->addWidget(widget_2, 0, 0, 1, 1);


        verticalLayout_7->addWidget(widget);


        verticalLayout_8->addLayout(verticalLayout_7);


        retranslateUi(SttReplayWaveformEditWidget);

        QMetaObject::connectSlotsByName(SttReplayWaveformEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SttReplayWaveformEditWidget)
    {
        SttReplayWaveformEditWidget->setWindowTitle(QApplication::translate("SttReplayWaveformEditWidget", "Form", 0, QApplication::UnicodeUTF8));
        m_rb_WaveEdit->setText(QApplication::translate("SttReplayWaveformEditWidget", "\345\216\237\346\263\242\345\275\242\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        m_rb_InsertWave->setText(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245\345\270\270\346\200\201\346\263\242\345\275\242", 0, QApplication::UnicodeUTF8));
        m_pb_Replay->setText(QApplication::translate("SttReplayWaveformEditWidget", "\346\263\242\345\275\242\345\244\215\345\275\222", 0, QApplication::UnicodeUTF8));
        m_Insert_GroupBox->setTitle(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245\346\263\242\345\275\242", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SttReplayWaveformEditWidget", "\345\276\252\347\216\257\346\254\241\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SttReplayWaveformEditWidget", "\347\273\210\346\255\242\346\227\266\345\210\273\357\274\210s\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        m_lb_InsertBegin->setText(QApplication::translate("SttReplayWaveformEditWidget", "\350\265\267\345\247\213\346\227\266\345\210\273\357\274\210s\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245\346\263\242\345\275\242\345\217\202\350\200\203\357\274\232", 0, QApplication::UnicodeUTF8));
        m_InsertNomal_GroupBox->setTitle(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245\345\270\270\346\200\201\346\263\242\345\275\242", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SttReplayWaveformEditWidget", "\347\224\265\345\216\213\357\274\210V\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SttReplayWaveformEditWidget", "\347\224\265\346\265\201\357\274\210A\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SttReplayWaveformEditWidget", "\350\276\223\345\207\272\346\227\266\351\227\264\357\274\210s\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245\344\275\215\347\275\256\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SttReplayWaveformEditWidget", "\346\263\242\345\275\242\350\265\267\345\247\213\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SttReplayWaveformEditWidget", "\346\263\242\345\275\242\347\273\223\346\235\237\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8)
        );
        m_DeleteWave_GroupBox->setTitle(QApplication::translate("SttReplayWaveformEditWidget", "\345\210\240\351\231\244\346\263\242\345\275\242", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SttReplayWaveformEditWidget", "\347\273\210\346\255\242\346\227\266\345\210\273\357\274\210s\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SttReplayWaveformEditWidget", "\350\265\267\345\247\213\346\227\266\345\210\273\357\274\210s\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        m_pb_delete->setText(QApplication::translate("SttReplayWaveformEditWidget", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        m_pb_Insert->setText(QApplication::translate("SttReplayWaveformEditWidget", "\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SttReplayWaveformEditWidget: public Ui_SttReplayWaveformEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTREPLAYWAVEFORMEDITWIDGET_H
