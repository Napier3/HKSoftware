#include "qsttstartinfowidget.h"
#include "ui_qsttstartinfowidget.h"

#include <QDebug>

QSttStartInfoWidget::QSttStartInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttStartInfoWidget)
{
    ui->setupUi(this);

	connect(this,SIGNAL(sig_ShowInfor(QString)),this,SLOT(slot_ShowInfor(QString)));

	QSttStartInfoThread *pThread = new QSttStartInfoThread();
	pThread->m_pWidget = this;
	m_pThread = pThread;
	pThread->start();
}

QSttStartInfoWidget::~QSttStartInfoWidget()
{
    delete ui;
}

void QSttStartInfoWidget::HideWidget()
{
	QSttStartInfoThread *pThread = (QSttStartInfoThread*)m_pThread;
	pThread->m_bExitStart = true;
}

void QSttStartInfoWidget::SetInfor(const QString &strInfor)
{
    emit sig_ShowInfor(strInfor);
}

void QSttStartInfoWidget::slot_ShowInfor(QString strInfor)
{
	if (strInfor.size() <= 5)
	{
		hide();
	}
	else
	{
		show();
		ui->m_lblInfo->setText(strInfor);
		qDebug() << strInfor;
	}
}


QSttStartInfoThread::QSttStartInfoThread()
{
    m_pWidget = NULL;
	m_bExitStart = false;
}

QSttStartInfoThread::~QSttStartInfoThread()
{

}



void QSttStartInfoThread::run()
{
	long nIndex = 0;
	QString strInfor = "³ÌÐòÆô¶¯ÖÐ£¬ÇëÉÔºò";
	m_pWidget->SetInfor(strInfor);

	while (1)
	{
		if (m_bExitStart)
		{
			m_pWidget->SetInfor("");
			break;
		}

		if (nIndex > 10)
		{
			strInfor = "³ÌÐòÆô¶¯ÖÐ£¬ÇëÉÔºò";
			nIndex = 0;
		}
		else
		{
			nIndex++;
			strInfor = strInfor + ">";
		}

		m_pWidget->SetInfor(strInfor);

		usleep(50000);
	}
}
