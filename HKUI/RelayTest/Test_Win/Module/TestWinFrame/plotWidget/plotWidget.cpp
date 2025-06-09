#include "plotwidget.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"
PlotWidget::PlotWidget(QWidget *parent)
	: QWidget(parent),
	d_timerId(-1)
{
	m_pBinInTimeResponsePlot = NULL;
	m_pBinOutTimeResponsePlot = NULL;
	m_pVLayout = NULL;
}

PlotWidget::~PlotWidget()
{
	stop();
	Free();
}

void PlotWidget::Free()
{
	m_oUChls.RemoveAll();
	m_oIChls.RemoveAll();

	int nCnt = m_oChlTimePlotList.size();
	for(int i=0; i<nCnt; i++)
	{
		CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
		delete p;
	}
	m_oChlTimePlotList.clear();

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

void PlotWidget::stop()
{
	killTimer(d_timerId);
	d_timerId = -1;
}

void PlotWidget::start()
{
	int nCnt = m_oChlTimePlotList.size();
	for(int i=0; i<nCnt; i++)
	{
		CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
		p->start();
	}

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

void PlotWidget::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == d_timerId )
	{
		int nCnt = m_oChlTimePlotList.size();
		for(int i=0; i<nCnt; i++)
		{
			CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
			p->onTimerEvent(event);
		}

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


void PlotWidget::OnRtDataChanged()
{
	//获取最后一个点时间
	CSttMacroChannels *pChls = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	double fLastTime = 0;
	if (!pChls->m_oHisRealTimesBuf.GetLastMemVal(fLastTime))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("GetLastMemVal==FALSE"));
		return;
	}

	emit sig_ChlUpdateCurve(fLastTime,TRUE);
	emit sig_SwitchUpdateCurve(fLastTime,FALSE);

	killTimer(d_timerId);
	d_timerId = startTimer(1000);
}

void PlotWidget::OnRtSwitchChanged(double fLastTime)
{
	emit sig_ChlUpdateCurve(fLastTime,FALSE);
	emit sig_SwitchUpdateCurve(fLastTime,TRUE);

	killTimer(d_timerId);
	d_timerId = startTimer(1000);
}

void PlotWidget::initUI(CSttMacroChannels *pChls,double fUMin,double fUMax
						,double fIMin,double fIMax
						,long *pBinInData,long nBinInNum
						,long *pBinOutData,long nBinOutNum)
{
	Free();

	m_pVLayout = new QVBoxLayout;

	long nGroup = 0;
//	CSttMacroChannels *pChls = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	if (pChls != NULL)
	{
		m_oUChls.Append(pChls->m_oVolChListRef);
		m_oIChls.Append(pChls->m_oCurChListRef);

		//test
// 		POS pos1 = m_oUChls.GetHeadPosition();
// 		CSttMacroChannel *pTemp = NULL;
// 		long nIndexTemp = 0;
// 		while(pos1 != NULL)
// 		{
// 			pTemp = (CSttMacroChannel *)m_oUChls.GetNext(pos1);
// 
// 			float fVal = 10*nIndexTemp + 10;
// 			pTemp->m_oHisMagBuf.AppendBuffer(&fVal,1);
// 			
// 			nIndexTemp++;
// 		}
// 
// 		pos1 = m_oIChls.GetHeadPosition();
// 		nIndexTemp = 0;
// 		while(pos1 != NULL)
// 		{
// 			pTemp = (CSttMacroChannel *)m_oIChls.GetNext(pos1);
// 
// 			float fVal = 2*nIndexTemp + 5;
// 			pTemp->m_oHisMagBuf.AppendBuffer(&fVal,1);
// 
// 			nIndexTemp++;
// 		}

		long nUChlNum = m_oUChls.GetCount();
		long nIChlNum = m_oIChls.GetCount();
		long nMaxChlNum = max(nUChlNum,nIChlNum);
		if (nMaxChlNum <= 4)
		{
			nGroup = 1;

			CChlTimeResponsePlot *pChlPlot = new CChlTimeResponsePlot;
			pChlPlot->setChlData(m_oUChls,m_oIChls,fUMin,fUMax,fIMin,fIMax);
			m_pVLayout->addWidget(pChlPlot);
			m_oChlTimePlotList.append(pChlPlot);

			connect(this,SIGNAL(sig_ChlUpdateCurve(double,BOOL)),pChlPlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);
		}
		else
		{
			nGroup = nMaxChlNum / 3;
			if (nMaxChlNum % 3 != 0)
			{
				nGroup++;
			}

			for (int i=0; i<nGroup; i++)
			{
				CChlTimeResponsePlot *pChlPlot = new CChlTimeResponsePlot;
				CExBaseList oUChls,oIChls;

				for (int j=0; j<3; j++)
				{
					CExBaseObject *pUHead = m_oUChls.GetHead();
					if (pUHead != NULL)
					{
						oUChls.AddTail(pUHead);
						m_oUChls.RemoveHead();
					}

					CExBaseObject *pIHead = m_oIChls.GetHead();
					if (pIHead != NULL)
					{
						oIChls.AddTail(pIHead);
						m_oIChls.RemoveHead();
					}
				}
				
				pChlPlot->setChlData(oUChls,oIChls,fUMin,fUMax,fIMin,fIMax);
				oUChls.RemoveAll();
				oIChls.RemoveAll();
				m_pVLayout->addWidget(pChlPlot);
				m_oChlTimePlotList.append(pChlPlot);
				connect(this,SIGNAL(sig_ChlUpdateCurve(double,BOOL)),pChlPlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);
			}
		}
	}
	
	m_pBinInTimeResponsePlot = new CBinTimeResponsePlot(this);
	m_pBinOutTimeResponsePlot = new CBinTimeResponsePlot(this);
	connect(this,SIGNAL(sig_SwitchUpdateCurve(double,BOOL)),m_pBinInTimeResponsePlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_SwitchUpdateCurve(double,BOOL)),m_pBinOutTimeResponsePlot,SLOT(slot_UpdateCurve(double,BOOL)),Qt::UniqueConnection);

	m_pBinInTimeResponsePlot->setBinData(pBinInData,nBinInNum,0);
	m_pBinOutTimeResponsePlot->setBinData(pBinOutData,nBinOutNum,1);
	m_pBinOutTimeResponsePlot->updateXTtile(/*tr("时间(s)")*/g_sLangTxt_Time+"(s)");
	m_pVLayout->addWidget(m_pBinInTimeResponsePlot);
	m_pVLayout->addWidget(m_pBinOutTimeResponsePlot);
	m_pVLayout->setContentsMargins(nGroup + 2,0,0,0);
	m_pVLayout->setSpacing(0);
	this->setLayout(m_pVLayout);

	//test
//	start();
}