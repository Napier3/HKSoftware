#ifndef STTOUTPUTWIDGET_H
#define STTOUTPUTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QBoxLayout>
#include <QTextEdit>

/*#include "../Module/ScrollCtrl/ScrollTextEdit.h"*/

class QSttOutPutWidget : public QWidget
{
	Q_OBJECT

public:
    explicit QSttOutPutWidget(QWidget *parent = 0);
    ~QSttOutPutWidget();

	virtual void LogString(long nLevel, const QString &strMsg);
	
	/*QScrollTextEdit *textEdit;*/
	QTextEdit *textEdit;
	QHBoxLayout *m_pLayout;

signals:
	void sig_refreshLog(QString strLog);

public slots:
	void slot_refreshOutput(QString strLog);
	void slot_refreshLog(QString strLog);
};

#endif // STTOUTPUTWIDGET_H
