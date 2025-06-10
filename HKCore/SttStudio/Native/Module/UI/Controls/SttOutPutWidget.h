#ifndef STTOUTPUTWIDGET_H
#define STTOUTPUTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QBoxLayout>

#include "../Module/ScrollCtrl/ScrollTextEdit.h"

class QSttOutPutWidget : public QWidget
{
	Q_OBJECT

public:
    explicit QSttOutPutWidget(QWidget *parent = 0);
    ~QSttOutPutWidget();

	virtual void LogString(long nLevel, const QString &strMsg);
	
	QScrollTextEdit *textEdit;
	QHBoxLayout *m_pLayout;
	QTextCharFormat m_oErrorFormat;
	QTextCharFormat m_oNormalFormat;

signals:
	void sig_refreshLog(long nLevel,QString strLog);

public slots:
	void slot_refreshOutput(long nLevel,QString strLog);
	void slot_refreshLog(QString strLog);
};

#endif // STTOUTPUTWIDGET_H
