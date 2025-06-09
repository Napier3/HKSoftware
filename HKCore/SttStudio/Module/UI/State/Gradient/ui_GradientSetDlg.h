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
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
