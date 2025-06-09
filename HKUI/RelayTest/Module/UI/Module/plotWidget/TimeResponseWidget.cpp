#include "TimeResponseWidget.h"
#include "StateMonitor.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QTimeResponseWidget::QTimeResponseWidget(QWidget *parent)
	: QWidget(parent),
	d_timerId(-1)
{
	m_pLayout = NULL;
	m_tabWidget = NULL;
	m_bInitSync = FALSE;
	m_pChlTimePlotEx = NULL;
	m_pBinBoutInTimeResponsePlot = NULL;
}

QTimeResponseWidget::~QTimeResponseWidget()
{
	stop();
	Free();
}

void QTimeResponseWidget::Free()
{
	m_oUChls.RemoveAll();
	m_oIChls.RemoveAll();

	if (!g_pStateMonitor->m_bIsPlotEx)
	{
		int nCnt = m_oChlTimePlotList.size();
		for(int i=0; i<nCnt; i++)
		{
			CChlTimeResponsePlotEx *p = m_oChlTimePlotList.at(i);
			delete p;
		}

		m_oChlTimePlotList.clear();
	}
	else if(m_pChlTimePlotEx != NULL)
	{
		delete m_pChlTimePlotEx;
		m_pChlTimePlotEx = NULL;
	}

	if(m_pBinBoutInTimeResponsePlot != NULL)
	{
		delete m_pBinBoutInTimeResponsePlot;
		m_pBinBoutInTimeResponsePlot = NULL;
	}

	if (m_tabWidget != NULL)
	{
		delete m_tabWidget;
	}

	if (m_pLayout != NULL)
	{
		delete m_pLayout;
		m_pLayout = NULL;
	}
}

void QTimeResponseWidget::stop()
{
	return;

	killTimer(d_timerId);
	d_timerId = -1;
}

void QTimeResponseWidget::start()
{
	return;

	m_bInitSync = false;

	if (!g_pStateMonitor->m_bIsPlotEx)
	{
		int nCnt = m_oChlTimePlotList.size();
		for(int i=0; i<nCnt; i++)
		{
			CChlTimeResponsePlotEx *p = m_oChlTimePlotList.at(i);
			p->start();
		}
	}
	else if (m_pChlTimePlotEx != NULL)
	{
		m_pChlTimePlotEx->start();
	}

	if (m_pBinBoutInTimeResponsePlot != NULL)
	{
		m_pBinBoutInTimeResponsePlot->start();
	}

	d_timerId = startTimer(200);
}

void QTimeResponseWidget::timerEvent( QTimerEvent *event )
{
	return;

	if ( event->timerId() == d_timerId )
	{
		if(!isSyncInit())
		{
			return;
		}

		if (!g_pStateMonitor->m_bIsPlotEx)
		{
			QWidget::timerEvent( event );//zhouhj 20220415 等待李工优化,避免滑差递变时,软件卡死,暂时先直接返回
			return;

			for(int i=0; i<m_oChlTimePlotList.size(); i++)
			{
				CChlTimeResponsePlotEx *p = m_oChlTimePlotList.at(i);
				p->onTimerEvent(event);
			}
		}
		else if (m_pChlTimePlotEx != NULL)
		{
			m_pChlTimePlotEx->onTimerEvent(event);
		}

		if (m_pBinBoutInTimeResponsePlot != NULL)
		{
			m_pBinBoutInTimeResponsePlot->onTimerEvent(event);
		}
	}

	QWidget::timerEvent( event );
}

void QTimeResponseWidget::OnRtDataChanged()
{
	return;

	if(!isSyncInit())
	{
		m_bInitSync = true;
	}

	
	g_pStateMonitor->UpdateCurveData();
}

void QTimeResponseWidget::initUI(CSttMacroChannels *pChls,double fUMin,double fUMax
	,double fIMin,double fIMax,long *pBinInData,long *pBinOutData,int type)
{
	return;

	Free();

	m_pLayout = new QGridLayout;

	long nGroup = 0;
	if (pChls != NULL)
	{
		m_oUChls.Append(pChls->m_oVolChListRef);
		m_oIChls.Append(pChls->m_oCurChListRef);

		if (!g_pStateMonitor->m_bIsPlotEx)
		{
			long nUChlNum = m_oUChls.GetCount();
			long nIChlNum = m_oIChls.GetCount();
			long nMaxChlNum = max(nUChlNum,nIChlNum);
			if (nMaxChlNum <= 4)
			{
				nGroup = 1;

				CChlTimeResponsePlotEx *pChlPlot = new CChlTimeResponsePlotEx;
				pChlPlot->setChlData(m_oUChls, m_oIChls, fUMin, fUMax, fIMin, fIMax);//20210908 sf 兼容幅值相位频率
				m_oChlTimePlotList.append(pChlPlot);

				connect(this,SIGNAL(sig_ChlUpdateCurveEx()),pChlPlot,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
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
					CChlTimeResponsePlotEx *pChlPlot = new CChlTimeResponsePlotEx;
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

					pChlPlot->setChlData(oUChls,oIChls, fUMin, fUMax, fIMin, fIMax);//20210908 sf 兼容幅值相位频率
					oUChls.RemoveAll();
					oIChls.RemoveAll();
					m_oChlTimePlotList.append(pChlPlot);
					connect(this,SIGNAL(sig_ChlUpdateCurveEx()),pChlPlot,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
				}
			}
		}
		else
		{
			m_pChlTimePlotEx = new CChlTimeResponsePlotEx;
			//m_pChlTimePlotEx->setChlData(m_oUChls,m_oIChls);
			connect(this,SIGNAL(sig_ChlUpdateCurveEx()),m_pChlTimePlotEx,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
		}
	}

	if (nGroup > 0 && !g_pStateMonitor->m_bIsPlotEx)
	{
		m_tabWidget = new QTabWidget(this);
		for (int i=0; i< nGroup; i++)
		{
			CString strGroup;
			xlang_GetLangStrByFile(strGroup, "Native_Group");
			strGroup += QString::number(i + 1);
			m_tabWidget->addTab(m_oChlTimePlotList[i], strGroup);
		}
		
		m_pLayout->addWidget(m_tabWidget, 0, 0);

		nGroup = 1;
	}
	else
	{
		m_pLayout->addWidget(m_pChlTimePlotEx, 0, 0);
	}

	m_pBinBoutInTimeResponsePlot = new CBinBoutTimeResponsePlot(this);
	m_pBinBoutInTimeResponsePlot->setBinBoutData(pBinInData, g_nBinCount, pBinOutData, g_nBoutCount);
	m_pLayout->addWidget(m_pBinBoutInTimeResponsePlot, 1, 0);

	m_pLayout->setSpacing(0);
	this->setLayout(m_pLayout);
}

void QTimeResponseWidget::UpdateUI(CSttMacroChannels *pChls,double fUMin,double fUMax
	,double fIMin,double fIMax,long *pBinInData,long *pBinOutData,int type)
{
	return;
	long nGroup = 0;
	if (pChls != NULL)
	{
		//删除旧的资源
		m_oIChls.RemoveAll();
		m_oUChls.RemoveAll();
		foreach(CChlTimeResponsePlotEx *p,m_oChlTimePlotList)
		{
			if(p)
			{
				m_oChlTimePlotList.removeOne(p);
				delete p;
				p = NULL;
			}
		}
		m_oChlTimePlotList.clear();

		if(m_tabWidget)
		{
			delete m_tabWidget;
			m_tabWidget = NULL;	
		}

		if(m_pChlTimePlotEx)
		{
			m_pLayout->removeWidget(m_pChlTimePlotEx);
			delete m_pChlTimePlotEx;
			m_pChlTimePlotEx = NULL;
		}

		m_oUChls.Append(pChls->m_oVolChListRef);
		m_oIChls.Append(pChls->m_oCurChListRef);

		if (!g_pStateMonitor->m_bIsPlotEx)
		{
			long nUChlNum = m_oUChls.GetCount();
			long nIChlNum = m_oIChls.GetCount();
			long nMaxChlNum = max(nUChlNum,nIChlNum);
			if (nMaxChlNum <= 4)
			{
				nGroup = 1;

				CChlTimeResponsePlotEx *pChlPlot = new CChlTimeResponsePlotEx;
				pChlPlot->setChlData(m_oUChls, m_oIChls, fUMin, fUMax, fIMin, fIMax);//20210908 sf 兼容幅值相位频率
				m_oChlTimePlotList.append(pChlPlot);

				connect(this,SIGNAL(sig_ChlUpdateCurveEx()),pChlPlot,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
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
					CChlTimeResponsePlotEx *pChlPlot = new CChlTimeResponsePlotEx;
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

					pChlPlot->setChlData(oUChls,oIChls, fUMin, fUMax, fIMin, fIMax);//20210908 sf 兼容幅值相位频率
					oUChls.RemoveAll();
					oIChls.RemoveAll();
					m_oChlTimePlotList.append(pChlPlot);
					connect(this,SIGNAL(sig_ChlUpdateCurveEx()),pChlPlot,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
				}
			}
		}
		else
		{
			m_pChlTimePlotEx = new CChlTimeResponsePlotEx;
			//m_pChlTimePlotEx->setChlData(m_oUChls,m_oIChls);
			connect(this,SIGNAL(sig_ChlUpdateCurveEx()),m_pChlTimePlotEx,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
		}
	}

	if (nGroup > 0 && !g_pStateMonitor->m_bIsPlotEx)
	{
		m_tabWidget = new QTabWidget(this);
		for (int i=0; i< nGroup; i++)
		{
			CString strGroup;
			xlang_GetLangStrByFile(strGroup, "Native_Group");
			strGroup += QString::number(i + 1);
			m_tabWidget->addTab(m_oChlTimePlotList[i], strGroup);
		}

		m_pLayout->addWidget(m_tabWidget, 0, 0);

		nGroup = 1;
	}
	else
	{
		m_pLayout->addWidget(m_pChlTimePlotEx, 0, 0);
	}

	if(m_pBinBoutInTimeResponsePlot)
	{
		m_pLayout->removeWidget(m_pBinBoutInTimeResponsePlot);
		delete m_pBinBoutInTimeResponsePlot;
		m_pBinBoutInTimeResponsePlot = NULL;
	}

	m_pBinBoutInTimeResponsePlot = new CBinBoutTimeResponsePlot(this);
	m_pBinBoutInTimeResponsePlot->setBinBoutData(pBinInData, g_nBinCount, pBinOutData, g_nBoutCount);
	m_pLayout->addWidget(m_pBinBoutInTimeResponsePlot, 1, 0);
}