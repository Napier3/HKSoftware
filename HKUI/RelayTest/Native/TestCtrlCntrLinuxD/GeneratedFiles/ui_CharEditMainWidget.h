/********************************************************************************
** Form generated from reading UI file 'CharEditMainWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAREDITMAINWIDGET_H
#define UI_CHAREDITMAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCharEditMainWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *m_layoutLeft;
    QGridLayout *m_layoutRight;
    QTabWidget *m_wgtCharLib;

    void setupUi(QWidget *QCharEditMainWidget)
    {
        if (QCharEditMainWidget->objectName().isEmpty())
            QCharEditMainWidget->setObjectName(QString::fromUtf8("QCharEditMainWidget"));
        QCharEditMainWidget->resize(731, 365);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        QCharEditMainWidget->setFont(font);
        QCharEditMainWidget->setFocusPolicy(Qt::TabFocus);
        horizontalLayout = new QHBoxLayout(QCharEditMainWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_layoutLeft = new QVBoxLayout();
        m_layoutLeft->setSpacing(6);
        m_layoutLeft->setObjectName(QString::fromUtf8("m_layoutLeft"));

        horizontalLayout->addLayout(m_layoutLeft);

        m_layoutRight = new QGridLayout();
        m_layoutRight->setSpacing(6);
        m_layoutRight->setObjectName(QString::fromUtf8("m_layoutRight"));
        m_wgtCharLib = new QTabWidget(QCharEditMainWidget);
        m_wgtCharLib->setObjectName(QString::fromUtf8("m_wgtCharLib"));

        m_layoutRight->addWidget(m_wgtCharLib, 0, 0, 1, 1);


        horizontalLayout->addLayout(m_layoutRight);

        horizontalLayout->setStretch(0, 6);
        horizontalLayout->setStretch(1, 7);

        retranslateUi(QCharEditMainWidget);

        m_wgtCharLib->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QCharEditMainWidget);
    } // setupUi

    void retranslateUi(QWidget *QCharEditMainWidget)
    {
        QCharEditMainWidget->setWindowTitle(QApplication::translate("QCharEditMainWidget", "ParaSetWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QCharEditMainWidget: public Ui_QCharEditMainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAREDITMAINWIDGET_H
