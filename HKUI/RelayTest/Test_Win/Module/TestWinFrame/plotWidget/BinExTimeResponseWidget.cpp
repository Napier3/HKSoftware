#include "BinExTimeResponseWidget.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"


QBinExTimeResponseWidget::QBinExTimeResponseWidget(QWidget *parent)
	: QWidget(parent),
	d_timerId(-1)
{
	m_pBinInTimeResponsePlot = NULL;
	m_pBinOutTimeResponsePlot = NULL;
	m_pVLayout = NULL;
}

QBinExTimeResponseWidget::~QBinExTimeResponseWidget()
{
	stop();
	Free();
}

void QBinExTimeResponseWidget::Free()
{
	if (m_pBinInTimeResponsePlot != NULL)
	{
		delete m_pBinInTimeResponsePlot;
		m_pBinInTimeResponsePlot = NULL;
	}

	if (m_pBinOutTimeResponsePlot != NULL)
	{
		delete m_pBinOutTimeResponsePlot;
		m_pBinOutTimeResponsePlot = NULL;
	}

	if (m_pVLayout != NULL)
	{
		delete m_pVLayout;
	}
}

void QBinExTimeResponseWidget::stop()
{
	killTimer(d_timerId);
	d_timerId = -1;
}

void QBinExTimeResponseWidget::start()
{
	if (m_pBinInTimeResponsePlot != NULL)
	{
		m_pBinInTimeResponsePlot->start();
	}

	if (m_pBinOutTimeResponsePlot != NULL)
	{
		m_pBinOutTimeResponsePlot->start();
	}

	d_timerId = startTimer(1000);
}

void QBinExTimeResponseWidget::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == d_timerId )
	{
		if (m_pBinInTimeResponsePlot != NULL)
		{
			m_pBinInTimeResponsePlot->onTimerEvent(event);
		}

		if (m_pBinOutTimeResponsePlot != NULL)
		{
			m_pBinOutTimeResponsePlot->onTimerEvent(event);
		}
	}

	QWidget::timerEvent( event );
}


void QBinExTimeResponseWidget::OnRtDataChanged()
{
	//获取最后一个点时间
	CSttMacroChannels *pChls = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	double fLastTime = 0;
	if (!pChls->m_oHisRealTimesBuf.GetLastMemVal(fLastTime))
	{
//		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("GetLastMemVal==FALSE"));
		return;
	}

	emit sig_SwitchUpdateCurve(fLastTime,FALSE);

	killTimer(d_timerId);
	d_timerId = startTimer(1000);
}

void QBinExTimeResponseWidget::OnRtSwitchChanged(double fLastTime)
{
	emit sig_SwitchUpdateCurve(fLastTime,TRUE);

	killTimer(d_timerId);
	d_timerId = startTimer(1000);
}

void QBinExTimeResponseWidget::initUI(long *pBinInData,long nBinInNum,long *pBinOutData,long nBinOutNum)
{
	Free();

	m_pVLayout = new QVBoxLayout;

	m_pBinInTimeResponsePlot = new CBinTimeResponsePlot(this);
	m_pBinOutTimeResponsePlot = new CBinTimeResponsePlot(this);
	connect(this,SIGNAL(sig_SwitchUpdateCurve(double,BOOL)),m_pBinInTimeResponsePlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_SwitchUpdateCurve(double,BOOL)),m_pBinOutTimeResponsePlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);

	m_pBinInTimeResponsePlot->setBinData(pBinInData,nBinInNum,0);
	m_pBinOutTimeResponsePlot->setBinData(pBinOutData,nBinOutNum,1);
	m_pBinOutTimeResponsePlot->updateXTtile(/*tr("时间(s)")*/g_sLangTxt_Time+"(s)");
	m_pVLayout->addWidget(m_pBinInTimeResponsePlot);
	m_pVLayout->addWidget(m_pBinOutTimeResponsePlot);
	m_pVLayout->setContentsMargins(2,0,0,0);
	m_pVLayout->setSpacing(0);
	this->setLayout(m_pVLayout);
}