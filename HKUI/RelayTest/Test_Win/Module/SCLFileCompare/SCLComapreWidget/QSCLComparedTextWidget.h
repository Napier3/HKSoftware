#ifndef QSCLCOMPAREDTEXTWIDGET_H
#define QSCLCOMPAREDTEXTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QLabel>
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "QLineNumberEdit.h"


class QSCLComparedTextWidget: public QWidget
{
	Q_OBJECT

public:
	QSCLComparedTextWidget(QWidget *parent = 0);
	~QSCLComparedTextWidget();

	void InitUI();
	void CompareAndMarkDifference();

public slots:
	void ShowText(CString& strSourText, CString& strCompText);

private:
	QLineNumberTextEdit  *m_pSourTextEdit;
	QLineNumberTextEdit  *m_pCompTextEdit;

	QLabel *m_pSourLabel;
	QLabel *m_pCompLabel;
	QSplitter *m_pTextComparedSplitter;
};

#endif