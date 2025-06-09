#include "TimeResponseWidget.h"
#include "..\Module\TestWinFrame\testwinbase.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

#ifdef _GRADIENT_PLOT_
#include "../testwinbase.h"
#endif

#define STT_TimeResponseWidget_OnTime_NotUseTesterTime              200
#define STT_TimeResponseWidget_OnTime_UseTesterTime                1000

QTimeResponseWidget::QTimeResponseWidget(QWidget *parent)
	: QWidget(parent),
	d_timerId(-1)
{
	m_pBinInTimeResponsePlot = NULL;
	m_pBinOutTimeResponsePlot = NULL;
	m_pVLayout = NULL;
	m_tabWidget = NULL;
	m_bInitSync = FALSE;
	m_dLocalTime = 0.0f;
	m_dRealTime = 0.0f; 
	m_bUseTesterTime = FALSE;
#ifdef _GRADIENT_PLOT_
	m_pChlTimePlotEx = NULL;
#endif
}

QTimeResponseWidget::~QTimeResponseWidget()
{
	stop();
	Free();
}

void QTimeResponseWidget::Free()
{
	if (m_pBinInTimeResponsePlot != NULL)
	{
		disconnect(this,SIGNAL(sig_SwitchInUpdateCurve()),m_pBinInTimeResponsePlot,SLOT(slot_UpdateBinCurve()));
		disconnect(this,SIGNAL(sig_RtUpdata()),this,SLOT(slot_RtDataChanged()));
	}

	if (m_pBinOutTimeResponsePlot != NULL)
	{
		disconnect(this,SIGNAL(sig_SwitchOutUpdateCurve()),m_pBinOutTimeResponsePlot,SLOT(slot_UpdateBinCurve()));
	}

	m_oUChls.RemoveAll();
	m_oIChls.RemoveAll();

	if (g_TestWinBase->isCommonMode()||g_TestWinBase->isStateMode())
	{
		int nCnt = m_oChlTimePlotList.size();
		for(int i=0; i<nCnt; i++)
		{
			CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
			delete p;
		}

		m_oChlTimePlotList.clear();
	}
	else if(g_TestWinBase->isGradientMode())
	{
#ifdef _GRADIENT_PLOT_
		if (m_pChlTimePlotEx != NULL)
		{
			delete m_pChlTimePlotEx;
			m_pChlTimePlotEx = NULL;
		}
#endif
	}

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

	if (m_tabWidget != NULL)
	{
		delete m_tabWidget;
	}

	if (m_pVLayout != NULL)
	{
		delete m_pVLayout;
	}
}

void QTimeResponseWidget::stop()
{
	killTimer(d_timerId);

	d_timerId = -1;
	m_dRealTime = 0.0f;
	m_dLocalTime = 0.0f;

	if (m_bUseTesterTime)
	{
		m_pBinInTimeResponsePlot->UpdateCurves();
		m_pBinOutTimeResponsePlot->UpdateCurves();

		m_pBinInTimeResponsePlot->SetInit(true);
		m_pBinOutTimeResponsePlot->SetInit(true);

		for(int i = 0; i < m_oChlTimePlotList.size(); i++)
		{
			m_oChlTimePlotList[i]->AddStopPoint();
			m_oChlTimePlotList[i]->UpdateValueText();
			m_oChlTimePlotList[i]->UpdateCurves();
			m_oChlTimePlotList[i]->SetInit(true);
		}
	}
}

void QTimeResponseWidget::start()
{
	m_bInitSync = false;

	if (g_TestWinBase->isCommonMode()||g_TestWinBase->isStateMode())
	{
		int nCnt = m_oChlTimePlotList.size();
		for(int i=0; i<nCnt; i++)
		{
			CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
			p->start();
		}
	}
	else if (g_TestWinBase->isGradientMode())
	{
#ifdef _GRADIENT_PLOT_
		if(m_pChlTimePlotEx != NULL)
		{
			m_pChlTimePlotEx->start();
		}
#endif
	}

	if (m_pBinInTimeResponsePlot != NULL)
	{
		m_pBinInTimeResponsePlot->start();
	}

	if (m_pBinOutTimeResponsePlot != NULL)
	{
		m_pBinOutTimeResponsePlot->start();
	}

	if (m_bUseTesterTime)
	{
		d_timerId = startTimer(STT_TimeResponseWidget_OnTime_UseTesterTime);
	} 
	else
	{
		d_timerId = startTimer(STT_TimeResponseWidget_OnTime_NotUseTesterTime);
	}
}

void QTimeResponseWidget::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == d_timerId )
	{
		if(!isSyncInit())
		{
			return;
		}

		if (m_bUseTesterTime)
		{
			if (m_pBinInTimeResponsePlot != NULL)
			{
				m_pBinInTimeResponsePlot->UpdateCurves();
			}

			if (m_pBinOutTimeResponsePlot != NULL)
			{
				m_pBinOutTimeResponsePlot->UpdateCurves();
			}	
		} 

		if (g_TestWinBase->isCommonMode()||g_TestWinBase->isStateMode())
		{
			if (m_bUseTesterTime)
			{
				CChlTimeResponsePlot *p = m_oChlTimePlotList.at(m_tabWidget->currentIndex());
				p->UpdateValueText();
				p->UpdateCurves();
			}
			else
			{
				for(int i=0; i<m_oChlTimePlotList.size(); i++)
				{
					CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
					p->onTimerEvent(event);
				}
			}
		}
#ifdef _GRADIENT_PLOT_
		else if (g_TestWinBase->isGradientMode())
		{
			if(m_pChlTimePlotEx != NULL)
			{
				m_pChlTimePlotEx->onTimerEvent(event);
			}
		}
#endif

		if (!m_bUseTesterTime)
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

	}

	QWidget::timerEvent( event );
}

void QTimeResponseWidget::OnRtDataChanged()
{
	emit sig_RtUpdata();
}

void QTimeResponseWidget::OnRtSwitchChanged(double fLastTime)
{

}

void QTimeResponseWidget::UpdateLocalTime(double dLocalTime)
{
	if (!m_bUseTesterTime)
	{
		return;
	}

	if(m_dRealTime > dLocalTime)
	{
		return;
	}

	m_dLocalTime = dLocalTime;

	if(g_TestWinBase->m_bViewTestStarted)
	{
		if (m_pBinInTimeResponsePlot != NULL)
		{
			if(fabs(m_pBinInTimeResponsePlot->m_dRealTime)>0.00001f)
			{
				m_pBinInTimeResponsePlot->m_dLastTime = m_dLocalTime - m_pBinInTimeResponsePlot->m_dRealTime;
			}
		}

		if (m_pBinOutTimeResponsePlot != NULL)
		{
			if(fabs(m_pBinOutTimeResponsePlot->m_dRealTime)>0.00001f)
			{
				m_pBinOutTimeResponsePlot->m_dLastTime = m_dLocalTime - m_pBinOutTimeResponsePlot->m_dRealTime;
			}
		}

		for (int i = 0; i < m_oChlTimePlotList.size(); i++)
		{
			if(fabs(m_oChlTimePlotList[i]->m_dRealTime)>0.00001f)
			{
				m_oChlTimePlotList[i]->m_dLastTime = m_dLocalTime - m_oChlTimePlotList[i]->m_dRealTime;
			}	
		}
	}
}

#ifdef _GRADIENT_PLOT_
void QTimeResponseWidget::slot_UpdateCurveData()
{
/*
	if (g_TestWinBase->isGradientMode())
	{
		emit sig_ChlUpdateCurveEx();
	}

	emit sig_SwitchInUpdateCurve();
	emit sig_SwitchOutUpdateCurve();
*/
}
#endif

void QTimeResponseWidget::initUI(CSttMacroChannels *pChls,double fUMin,double fUMax
						,double fIMin,double fIMax
						,long *pBinInData,long nBinInNum
						,long *pBinOutData,long nBinOutNum,int type)
{
	Free();

	m_pVLayout = new QVBoxLayout;

	long nGroup = 0;
	if (pChls != NULL)
	{
		m_oUChls.Append(pChls->m_oVolChListRef);
		m_oIChls.Append(pChls->m_oCurChListRef);

		if (g_TestWinBase->isCommonMode()||g_TestWinBase->isStateMode())
		{
			long nUChlNum = m_oUChls.GetCount();
			long nIChlNum = m_oIChls.GetCount();
			long nMaxChlNum = max(nUChlNum,nIChlNum);
			if (nMaxChlNum <= 4)
			{
				nGroup = 1;

				CChlTimeResponsePlot *pChlPlot = new CChlTimeResponsePlot;
				pChlPlot->m_bUseTesterTime = m_bUseTesterTime;
				pChlPlot->setChlData(m_oUChls,m_oIChls,fUMin,fUMax,fIMin,fIMax,type);//20210908 sf 兼容幅值相位频率
				m_oChlTimePlotList.append(pChlPlot);

				connect(this,SIGNAL(sig_ChlUpdateCurve()),pChlPlot,SLOT(slot_UpdateCurve()),Qt::UniqueConnection);
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
					pChlPlot->m_bUseTesterTime = m_bUseTesterTime;
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

					pChlPlot->setChlData(oUChls,oIChls,fUMin,fUMax,fIMin,fIMax,type);//20210908 sf 兼容幅值相位频率
					oUChls.RemoveAll();
					oIChls.RemoveAll();
					m_oChlTimePlotList.append(pChlPlot);
					connect(this,SIGNAL(sig_ChlUpdateCurve()),pChlPlot,SLOT(slot_UpdateCurve()),Qt::UniqueConnection);
				}
			}
		}
		else if (g_TestWinBase->isGradientMode())
		{
#ifdef _GRADIENT_PLOT_
			m_pChlTimePlotEx = new CChlTimeResponsePlotEx;
			m_pChlTimePlotEx->setChlData(m_oUChls,m_oIChls);

			connect(this,SIGNAL(sig_ChlUpdateCurveEx()),m_pChlTimePlotEx,SLOT(slot_UpdateCurveEx()),Qt::UniqueConnection);
#endif
		}
	}

	if (nGroup > 0 && (g_TestWinBase->isCommonMode() || g_TestWinBase->isStateMode()))
	{
		m_tabWidget = new QTabWidget(this);
		for (int i=0; i< nGroup; i++)
		{
			m_tabWidget->addTab(m_oChlTimePlotList[i],QString(/*tr("第%1组")*/g_sLangTxt_Native_groupNumber).arg(i+1));
		}
		
		m_pVLayout->addWidget(m_tabWidget);

		nGroup = 1;
	}
	else if (g_TestWinBase->isGradientMode())
	{
#ifdef _GRADIENT_PLOT_
		m_pVLayout->addWidget(m_pChlTimePlotEx);
#endif
	}

	m_pBinInTimeResponsePlot = new CBinTimeResponsePlot(this);
	m_pBinInTimeResponsePlot->m_bUseTesterTime = m_bUseTesterTime;
	m_pBinOutTimeResponsePlot = new CBinTimeResponsePlot(this);
	m_pBinOutTimeResponsePlot->m_bUseTesterTime = m_bUseTesterTime;
	connect(this,SIGNAL(sig_SwitchInUpdateCurve()),m_pBinInTimeResponsePlot,SLOT(slot_UpdateBinCurve()),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_SwitchOutUpdateCurve()),m_pBinOutTimeResponsePlot,SLOT(slot_UpdateBinCurve()),Qt::UniqueConnection);

	connect(this,SIGNAL(sig_RtUpdata()),this,SLOT(slot_RtDataChanged()),Qt::UniqueConnection);

	m_pBinInTimeResponsePlot->setBinData(pBinInData,nBinInNum,0);
	m_pBinOutTimeResponsePlot->setBinData(pBinOutData,nBinOutNum,1);
	m_pBinOutTimeResponsePlot->updateXTtile(/*tr("时间(s)")*/g_sLangTxt_Time+"(s)");
	m_pVLayout->addWidget(m_pBinInTimeResponsePlot);
	m_pVLayout->addWidget(m_pBinOutTimeResponsePlot);
	m_pVLayout->setContentsMargins(nGroup + 2,0,0,0);

	m_pVLayout->setSpacing(0);
	this->setLayout(m_pVLayout);
}

void QTimeResponseWidget::ChangeListType( int type,double fUMin,double fUMax,double fIMin,double fIMax )
{
	for(int i=0; i<m_oChlTimePlotList.size(); i++)
	{
		CChlTimeResponsePlot *p = m_oChlTimePlotList.at(i);
		p->ChangeType(type);
		p->InitYTick(fUMin,fUMax,fIMin,fIMax);
	}
	//wangtao 20240430 使三幅图大小一致

	int nUDigits = 0;
    int nUMax = fUMax;

	if (type == amplitude_type)
	{
		nUMax += 20;	
	}
	//获取最大值的位数nDigits，根据位数将三幅图大小统一缩放
	while (nUMax != 0)
	{
		nUMax = nUMax / 10;
		nUDigits++;
	}
 
    int nIDigits = 0;
    int nIMax = fIMax;

	if (type == amplitude_type)
	{
		nIMax += 10;	
	}
	while (nIMax != 0)
	{
		nIMax = nIMax / 10;
		nIDigits++;
	}

	if (m_pBinInTimeResponsePlot != NULL)//其他功能存在没有这两幅图的情况
	{
		m_pBinInTimeResponsePlot->setAxisScaleDraw(QwtPlot::yLeft,new BinCharYScaleDraw(nUDigits,false));//false：文字在左边Y轴；true：右边Y轴
        m_pBinInTimeResponsePlot->setAxisScaleDraw(QwtPlot::yRight,new BinCharYScaleDraw(nIDigits+1,true));
	}
	if (m_pBinOutTimeResponsePlot != NULL)
	{
	    m_pBinOutTimeResponsePlot->setAxisScaleDraw(QwtPlot::yLeft,new BinNumYScaleDraw(nUDigits,false));
	    m_pBinOutTimeResponsePlot->setAxisScaleDraw(QwtPlot::yRight,new BinNumYScaleDraw(nIDigits+1,true));
	}
}

void QTimeResponseWidget::AddBinPoint(long nIndex, double x, double y)
{
	if (m_bUseTesterTime && m_pBinInTimeResponsePlot)
	{
		m_pBinInTimeResponsePlot->AddBinBoutPoint(nIndex, x, y);
	}
}

void QTimeResponseWidget::AddBoutPoint(long nIndex, double x, double y)
{
	if (m_bUseTesterTime && m_pBinOutTimeResponsePlot)
	{
		m_pBinOutTimeResponsePlot->AddBinBoutPoint(nIndex, x, y);
	}
}

void QTimeResponseWidget::slot_RtDataChanged()
{
	if(!isSyncInit())
	{
		m_bInitSync = true;
	}

#ifdef _GRADIENT_PLOT_
	g_TestWinBase->UpdateCurveData();
#else

	if (m_bUseTesterTime)
	{
		CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
		double dTime = 0;

		if (!pMacroChs->m_oHisTimesBuf.GetLastMemVal(dTime))
		{
			return;
		}

		for (int i = 0; i < m_oChlTimePlotList.size(); i++)
		{
			CChlTimeResponsePlot* pVoltCur = m_oChlTimePlotList[i];
			if(!pVoltCur->m_dRealTime)
			{
				pVoltCur->m_dRealTime = dTime;
			}
			else
			{
				pVoltCur->m_dLastTime = dTime - pVoltCur->m_dRealTime;	
			}

			pVoltCur->AddPoint(pMacroChs);
		}

		if(fabs(m_pBinInTimeResponsePlot->m_dRealTime)<0.00001)
		{
			m_pBinInTimeResponsePlot->m_dRealTime = dTime;
			m_pBinInTimeResponsePlot->InitBinBoutPoint(0);
		}

		if(fabs(m_pBinOutTimeResponsePlot->m_dRealTime)<0.00001)
		{
			m_pBinOutTimeResponsePlot->m_dRealTime = dTime;
			m_pBinOutTimeResponsePlot->InitBinBoutPoint(0);
		}

		if(fabs(m_dRealTime)<0.00001)
		{
			m_dRealTime = dTime;
		}
	}
#endif

}