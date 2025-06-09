#include "SttOutPutWidget.h"
#include "../../../../Module/OSInterface/OSInterface.h"

QSttOutPutWidget::QSttOutPutWidget(QWidget *parent) :
    QWidget(parent)
{
	m_pLayout = new QHBoxLayout(this);
	textEdit = new QScrollTextEdit(this);
	m_pLayout->addWidget(textEdit);
	setLayout(m_pLayout);

    //setupUi(this);
	//this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
	//��Ϣ��ӡ
	connect(this, SIGNAL(sig_refreshLog(long,QString)), this, SLOT(slot_refreshOutput(long,QString)));

	//2022-10-15  lijunqing  Windows���ԣ���������
#ifdef _PSX_QT_LINUX_
	textEdit->document()->setMaximumBlockCount(1000); 
#else
	textEdit->document()->setMaximumBlockCount(40000);
#endif
	m_oErrorFormat.setForeground(QBrush(QColor(255,0,0)));
	m_oNormalFormat.setForeground(QBrush(QColor(0,0,0)));
}

QSttOutPutWidget::~QSttOutPutWidget()
{
    
}

void QSttOutPutWidget::slot_refreshOutput(long nLevel,QString strLog)
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

	//�Ƿ�ʹ���Զ����ʱ�����
#ifdef USE_Custom_CDateTime
	QString time;
	CString strTimeText;
	CDateTime::GetDateTime_HHMMSSZZZ(strTimeText);
	time = strTimeText;
 #else
     QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
 #endif
	time += "      ";
	time += strLog;

	//yzj 2022-2-18 �ڷ�linux�����±�������ӡ����Ϣ��ĳЩ��������ʾ���������
#ifndef _PSX_QT_LINUX_
	//��������ʱע��
	//time = QString::fromLocal8Bit(time.toStdString().c_str());
#endif
	QTextCursor cursor = textEdit->textCursor();

 	if (nLevel == XLOGLEVEL_ERROR)
 	{
 		cursor.mergeCharFormat(m_oErrorFormat);
 		textEdit->mergeCurrentCharFormat(m_oErrorFormat);
 	}

	textEdit->append(time);
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);

 	if (nLevel == XLOGLEVEL_ERROR)
 	{
 		cursor.mergeCharFormat(m_oNormalFormat);
 		textEdit->mergeCurrentCharFormat(m_oNormalFormat);
 	}
}

void QSttOutPutWidget::LogString(long nLevel, const QString &strMsg)
{
	emit sig_refreshLog(nLevel,strMsg);
}

void QSttOutPutWidget::slot_refreshLog(QString strLog)
{
	emit sig_refreshLog(XLOGLEVEL_INFOR, strLog);
}