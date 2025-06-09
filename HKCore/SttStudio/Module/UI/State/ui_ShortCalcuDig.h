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
