/********************************************************************************
** Form generated from reading UI file 'SttExportWordReport.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STTEXPORTWORDREPORT_H
#define UI_STTEXPORTWORDREPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSttExportWordReport
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_tree;
    QVBoxLayout *verticalLayout_grid;
    QHBoxLayout *horizontalLayout_prev_next;
    QPushButton *m_btnPrev;
    QPushButton *m_btnNext;
    QHBoxLayout *horizontalLayout_btn;
    QLabel *label_FilePath;
    QLineEdit *m_editFilePath;
    QPushButton *m_btnSelPath;
    QPushButton *m_btnExport;

    void setupUi(QDialog *QSttExportWordReport)
    {
        if (QSttExportWordReport->objectName().isEmpty())
            QSttExportWordReport->setObjectName(QString::fromUtf8("QSttExportWordReport"));
        QSttExportWordReport->resize(1117, 502);
        verticalLayout_2 = new QVBoxLayout(QSttExportWordReport);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(15, -1, 15, 15);
        verticalLayout_tree = new QVBoxLayout();
        verticalLayout_tree->setObjectName(QString::fromUtf8("verticalLayout_tree"));

        horizontalLayout->addLayout(verticalLayout_tree);

        verticalLayout_grid = new QVBoxLayout();
        verticalLayout_grid->setObjectName(QString::fromUtf8("verticalLayout_grid"));
        horizontalLayout_prev_next = new QHBoxLayout();
        horizontalLayout_prev_next->setObjectName(QString::fromUtf8("horizontalLayout_prev_next"));
        m_btnPrev = new QPushButton(QSttExportWordReport);
        m_btnPrev->setObjectName(QString::fromUtf8("m_btnPrev"));

        horizontalLayout_prev_next->addWidget(m_btnPrev);

        m_btnNext = new QPushButton(QSttExportWordReport);
        m_btnNext->setObjectName(QString::fromUtf8("m_btnNext"));

        horizontalLayout_prev_next->addWidget(m_btnNext);


        verticalLayout_grid->addLayout(horizontalLayout_prev_next);


        horizontalLayout->addLayout(verticalLayout_grid);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 7);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_btn = new QHBoxLayout();
        horizontalLayout_btn->setSpacing(7);
        horizontalLayout_btn->setObjectName(QString::fromUtf8("horizontalLayout_btn"));
        horizontalLayout_btn->setContentsMargins(15, 0, 15, 15);
        label_FilePath = new QLabel(QSttExportWordReport);
        label_FilePath->setObjectName(QString::fromUtf8("label_FilePath"));

        horizontalLayout_btn->addWidget(label_FilePath);

        m_editFilePath = new QLineEdit(QSttExportWordReport);
        m_editFilePath->setObjectName(QString::fromUtf8("m_editFilePath"));
        m_editFilePath->setReadOnly(true);

        horizontalLayout_btn->addWidget(m_editFilePath);

        m_btnSelPath = new QPushButton(QSttExportWordReport);
        m_btnSelPath->setObjectName(QString::fromUtf8("m_btnSelPath"));

        horizontalLayout_btn->addWidget(m_btnSelPath);

        m_btnExport = new QPushButton(QSttExportWordReport);
        m_btnExport->setObjectName(QString::fromUtf8("m_btnExport"));

        horizontalLayout_btn->addWidget(m_btnExport);


        verticalLayout->addLayout(horizontalLayout_btn);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(QSttExportWordReport);

        QMetaObject::connectSlotsByName(QSttExportWordReport);
    } // setupUi

    void retranslateUi(QDialog *QSttExportWordReport)
    {
        QSttExportWordReport->setWindowTitle(QString());
        m_btnPrev->setText(QApplication::translate("QSttExportWordReport", "\344\270\212\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
        m_btnNext->setText(QApplication::translate("QSttExportWordReport", "\344\270\213\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
        label_FilePath->setText(QApplication::translate("QSttExportWordReport", "\345\257\274\345\207\272\350\267\257\345\276\204\357\274\232", 0, QApplication::UnicodeUTF8));
        m_editFilePath->setInputMask(QString());
        m_editFilePath->setText(QString());
        m_btnSelPath->setText(QApplication::translate("QSttExportWordReport", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        m_btnExport->setText(QApplication::translate("QSttExportWordReport", "\345\257\274\345\207\272\346\212\245\345\221\212", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QSttExportWordReport: public Ui_QSttExportWordReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STTEXPORTWORDREPORT_H
