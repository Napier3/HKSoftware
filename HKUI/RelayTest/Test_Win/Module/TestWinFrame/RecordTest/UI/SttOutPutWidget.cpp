#include "SttOutPutWidget.h"

QSttOutPutWidget::QSttOutPutWidget(QWidget *parent) :
    QWidget(parent)
{
	m_pLayout = new QHBoxLayout(this);
	textEdit = new QTextEdit(this);
	m_pLayout->addWidget(textEdit);
	setLayout(m_pLayout);

    //setupUi(this);
	//this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
	//消息打印
	connect(this, SIGNAL(sig_refreshLog(QString)), this, SLOT(slot_refreshOutput(QString)));

	//2022-10-15  lijunqing  Windows调试，增加行数
#ifdef _PSX_QT_LINUX_
	textEdit->document()->setMaximumBlockCount(1000); 
#else
	textEdit->document()->setMaximumBlockCount(40000);
#endif
}

QSttOutPutWidget::~QSttOutPutWidget()
{
    
}

void QSttOutPutWidget::slot_refreshOutput(QString strLog)
{
	if (textEdit == NULL)
		return;

#ifdef _PSX_QT_LINUX_
   if(textEdit->document()->lineCount() > 990)
#else
	if(textEdit->document()->lineCount() > 39990)
#endif
    {
        textEdit->setText("");
    }

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
	time += "      ";
	time += strLog;

	//yzj 2022-2-18 在非linux基础下编译解决打印的信息在某些电脑上显示乱码的问题
#ifndef _PSX_QT_LINUX_
	//崩溃，临时注释
	//time = QString::fromLocal8Bit(time.toStdString().c_str());
#endif

	textEdit->append(time);

	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);
}

void QSttOutPutWidget::LogString(long nLevel, const QString &strMsg)
{
	emit sig_refreshLog(strMsg);
}

void QSttOutPutWidget::slot_refreshLog(QString strLog)
{
	emit sig_refreshLog(strLog);
}