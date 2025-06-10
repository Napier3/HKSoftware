/********************************************************************************
** Form generated from reading UI file 'GradientSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADIENTSETTINGDLG_H
#define UI_GRADIENTSETTINGDLG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSpacerItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_GradientSetDlg
{
public:

    void setupUi(QDialog *GradientSetDlg)
    {
        if (GradientSetDlg->objectName().isEmpty())
            GradientSetDlg->setObjectName(QString::fromUtf8("GradientSetDlg"));
        GradientSetDlg->resize(600, 400);
        QFont font;
        font.setPointSize(18);
        GradientSetDlg->setFont(font);
        GradientSetDlg->setWindowOpacity(1);
     
		 retranslateUi(GradientSetDlg);

        QMetaObject::connectSlotsByName(GradientSetDlg);
    } // setupUi

    void retranslateUi(QDialog *GradientSetDlg)
    {
        GradientSetDlg->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class GradientSetDlg: public Ui_GradientSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADIENTSETTINGDLG_H
