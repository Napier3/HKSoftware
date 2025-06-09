/********************************************************************************
** Form generated from reading UI file 'QCharInverseSet.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCHARINVERSESET_H
#define UI_QCHARINVERSESET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCharInverseSet
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *_2;
    QLabel *label_26;
    QLineEdit *lineEdit_VSet1;
    QLabel *label_34;
    QLabel *label_35;
    QLineEdit *lineEdit_TSet2;
    QLabel *label_30;
    QCheckBox *checkBox_Set3;
    QLineEdit *lineEdit_TSet3;
    QCheckBox *checkBox_Set2;
    QLabel *label_27;
    QLabel *label_31;
    QLineEdit *lineEdit_VSet3;
    QLineEdit *lineEdit_VSet2;
    QLabel *label_38;
    QLabel *label_39;
    QLineEdit *lineEdit_TSet1;
    QCheckBox *checkBox_Set1;
    QGridLayout *GroupGrid;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_CANCEL;

    void setupUi(QWidget *QCharInverseSet)
    {
        if (QCharInverseSet->objectName().isEmpty())
            QCharInverseSet->setObjectName(QString::fromUtf8("QCharInverseSet"));
        QCharInverseSet->resize(510, 367);
        verticalLayout = new QVBoxLayout(QCharInverseSet);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(QCharInverseSet);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        _2 = new QGridLayout(groupBox_3);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QString::fromUtf8("_2"));
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(10);
        label_26->setFont(font);
        label_26->setAlignment(Qt::AlignCenter);

        _2->addWidget(label_26, 0, 1, 1, 1);

        lineEdit_VSet1 = new QLineEdit(groupBox_3);
        lineEdit_VSet1->setObjectName(QString::fromUtf8("lineEdit_VSet1"));
        lineEdit_VSet1->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        lineEdit_VSet1->setFont(font1);

        _2->addWidget(lineEdit_VSet1, 2, 1, 1, 1);

        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy1);
        label_34->setFont(font);

        _2->addWidget(label_34, 3, 2, 1, 1);

        label_35 = new QLabel(groupBox_3);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy1.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy1);
        label_35->setFont(font);

        _2->addWidget(label_35, 3, 4, 1, 1);

        lineEdit_TSet2 = new QLineEdit(groupBox_3);
        lineEdit_TSet2->setObjectName(QString::fromUtf8("lineEdit_TSet2"));
        lineEdit_TSet2->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet2->setFont(font1);

        _2->addWidget(lineEdit_TSet2, 3, 3, 1, 1);

        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font);

        _2->addWidget(label_30, 2, 2, 1, 1);

        checkBox_Set3 = new QCheckBox(groupBox_3);
        checkBox_Set3->setObjectName(QString::fromUtf8("checkBox_Set3"));
        checkBox_Set3->setFont(font);

        _2->addWidget(checkBox_Set3, 4, 0, 1, 1);

        lineEdit_TSet3 = new QLineEdit(groupBox_3);
        lineEdit_TSet3->setObjectName(QString::fromUtf8("lineEdit_TSet3"));
        lineEdit_TSet3->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet3->setFont(font1);

        _2->addWidget(lineEdit_TSet3, 4, 3, 1, 1);

        checkBox_Set2 = new QCheckBox(groupBox_3);
        checkBox_Set2->setObjectName(QString::fromUtf8("checkBox_Set2"));
        checkBox_Set2->setFont(font);

        _2->addWidget(checkBox_Set2, 3, 0, 1, 1);

        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font);
        label_27->setAlignment(Qt::AlignCenter);

        _2->addWidget(label_27, 0, 3, 1, 1);

        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font);

        _2->addWidget(label_31, 2, 4, 1, 1);

        lineEdit_VSet3 = new QLineEdit(groupBox_3);
        lineEdit_VSet3->setObjectName(QString::fromUtf8("lineEdit_VSet3"));
        lineEdit_VSet3->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_VSet3->setFont(font1);

        _2->addWidget(lineEdit_VSet3, 4, 1, 1, 1);

        lineEdit_VSet2 = new QLineEdit(groupBox_3);
        lineEdit_VSet2->setObjectName(QString::fromUtf8("lineEdit_VSet2"));
        lineEdit_VSet2->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_VSet2->setFont(font1);

        _2->addWidget(lineEdit_VSet2, 3, 1, 1, 1);

        label_38 = new QLabel(groupBox_3);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        sizePolicy1.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy1);
        label_38->setFont(font);

        _2->addWidget(label_38, 4, 2, 1, 1);

        label_39 = new QLabel(groupBox_3);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy1.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy1);
        label_39->setFont(font);

        _2->addWidget(label_39, 4, 4, 1, 1);

        lineEdit_TSet1 = new QLineEdit(groupBox_3);
        lineEdit_TSet1->setObjectName(QString::fromUtf8("lineEdit_TSet1"));
        lineEdit_TSet1->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_TSet1->setFont(font1);

        _2->addWidget(lineEdit_TSet1, 2, 3, 1, 1);

        checkBox_Set1 = new QCheckBox(groupBox_3);
        checkBox_Set1->setObjectName(QString::fromUtf8("checkBox_Set1"));
        checkBox_Set1->setFont(font);

        _2->addWidget(checkBox_Set1, 2, 0, 1, 1);

        label_27->raise();
        label_30->raise();
        checkBox_Set1->raise();
        label_31->raise();
        lineEdit_VSet1->raise();
        lineEdit_TSet1->raise();
        lineEdit_TSet2->raise();
        label_34->raise();
        checkBox_Set2->raise();
        lineEdit_VSet2->raise();
        lineEdit_VSet3->raise();
        checkBox_Set3->raise();
        label_38->raise();
        lineEdit_TSet3->raise();
        label_35->raise();
        label_39->raise();
        label_26->raise();

        verticalLayout->addWidget(groupBox_3);

        GroupGrid = new QGridLayout();
        GroupGrid->setSpacing(6);
        GroupGrid->setObjectName(QString::fromUtf8("GroupGrid"));
        groupBox = new QGroupBox(QCharInverseSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox_3->raise();

        GroupGrid->addWidget(groupBox, 0, 0, 1, 1);


        verticalLayout->addLayout(GroupGrid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_OK = new QPushButton(QCharInverseSet);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));

        horizontalLayout->addWidget(pushButton_OK);

        pushButton_CANCEL = new QPushButton(QCharInverseSet);
        pushButton_CANCEL->setObjectName(QString::fromUtf8("pushButton_CANCEL"));

        horizontalLayout->addWidget(pushButton_CANCEL);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QCharInverseSet);

        QMetaObject::connectSlotsByName(QCharInverseSet);
    } // setupUi

    void retranslateUi(QWidget *QCharInverseSet)
    {
        QCharInverseSet->setWindowTitle(QApplication::translate("QCharInverseSet", "QCharInverseSet", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        label_26->setText(QApplication::translate("QCharInverseSet", "\345\212\250\344\275\234\345\256\232\345\200\274", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("QCharInverseSet", "A", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("QCharInverseSet", "s", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("QCharInverseSet", "A", 0, QApplication::UnicodeUTF8));
        checkBox_Set3->setText(QApplication::translate("QCharInverseSet", "3\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        checkBox_Set2->setText(QApplication::translate("QCharInverseSet", "2\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("QCharInverseSet", "\345\212\250\344\275\234\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("QCharInverseSet", "s", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("QCharInverseSet", "A", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("QCharInverseSet", "s", 0, QApplication::UnicodeUTF8));
        checkBox_Set1->setText(QApplication::translate("QCharInverseSet", "1\346\256\265\345\256\232\346\227\266\351\231\220", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushButton_OK->setText(QApplication::translate("QCharInverseSet", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_CANCEL->setText(QApplication::translate("QCharInverseSet", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharInverseSet: public Ui_QCharInverseSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCHARINVERSESET_H
