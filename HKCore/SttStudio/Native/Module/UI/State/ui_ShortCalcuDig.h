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

class Ui_ShortCalcuDig
{
public:

    void setupUi(QDialog *ShortCalcuDig)
    {
        if (ShortCalcuDig->objectName().isEmpty())
            ShortCalcuDig->setObjectName(QString::fromUtf8("ShortCalcuDig"));
        ShortCalcuDig->resize(600, 400);
        QFont font;
        font.setPointSize(20);
        ShortCalcuDig->setFont(font);
        ShortCalcuDig->setWindowOpacity(1);
     
		 retranslateUi(ShortCalcuDig);

        QMetaObject::connectSlotsByName(ShortCalcuDig);
    } // setupUi

    void retranslateUi(QDialog *ShortCalcuDig)
    {
        ShortCalcuDig->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class ShortCalcuDig: public Ui_ShortCalcuDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADIENTSETTINGDLG_H
