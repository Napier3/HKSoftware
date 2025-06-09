/********************************************************************************
** Form generated from reading UI file 'SynWiringDiagramwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNWIRINGDIAGRAMWIDGET_H
#define UI_SYNWIRINGDIAGRAMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSynWiringDiagramWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *m_pRightPic_Label;

    void setupUi(QWidget *QSynWiringDiagramWidget)
    {
        if (QSynWiringDiagramWidget->objectName().isEmpty())
            QSynWiringDiagramWidget->setObjectName(QString::fromUtf8("QSynWiringDiagramWidget"));
        QSynWiringDiagramWidget->resize(625, 311);
        gridLayout = new QGridLayout(QSynWiringDiagramWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pRightPic_Label = new QLabel(QSynWiringDiagramWidget);
        m_pRightPic_Label->setObjectName(QString::fromUtf8("m_pRightPic_Label"));
        m_pRightPic_Label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(m_pRightPic_Label, 0, 0, 1, 1);


        retranslateUi(QSynWiringDiagramWidget);

        QMetaObject::connectSlotsByName(QSynWiringDiagramWidget);
    } // setupUi

    void retranslateUi(QWidget *QSynWiringDiagramWidget)
    {
        QSynWiringDiagramWidget->setWindowTitle(QApplication::translate("QSynWiringDiagramWidget", "\350\207\252\345\212\250\345\207\206\345\220\214\346\234\237\346\216\245\347\272\277\345\233\276", 0, QApplication::UnicodeUTF8));
        m_pRightPic_Label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QSynWiringDiagramWidget: public Ui_QSynWiringDiagramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNWIRINGDIAGRAMWIDGET_H
