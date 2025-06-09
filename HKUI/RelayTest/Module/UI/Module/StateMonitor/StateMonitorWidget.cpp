#include "StateMonitorWidget.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../SttTestCntrFrameAPI.h"

QStateMonitorWidget* g_pStateMonitorWidget = NULL;

QStateMonitorWidget::QStateMonitorWidget(QWidget *parent) : QWidget(parent)
{
	m_nTimerID = -1;
	m_bModeIsSingle = false;
	g_pStateMonitorWidget = this;
	m_pSingle = 0;
	m_pBinBout = 0;
	m_dLocalTime = 0;
	m_dRealTime = 0;
	m_pFrame = 0;
	InitUI();
}

QStateMonitorWidget::~QStateMonitorWidget()
{
	if(m_pBinBout)
	{
		delete m_pBinBout;
		m_pBinBout = NULL;
	}

	if(m_pSingle)
	{
		delete m_pSingle;
		m_pSingle = NULL;
	}

	if (m_pFrame)
	{
		delete m_pFrame;
		m_pFrame = NULL;
	}

	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		delete m_oVoltCurList[i];
	}
	m_oVoltCurList.clear();
}

void QStateMonitorWidget::InitStateMonitor(int nChannel, int nType, bool bStart, QWidget* pConnectWidget)
{
	connect(pConnectWidget, SIGNAL(sig_YRangeChanged(changed_type ,QString ,float ,float )), 
		this, SLOT(slot_YRangeChanged(changed_type,QString ,float ,float )));

	m_pSingle->UpdateSingleChannel(nChannel, nType, bStart);
}

void QStateMonitorWidget::StopStateMonitor()
{
	killTimer(m_nTimerID);
	m_nTimerID = -1;
	m_dLocalTime = 0;
	m_dRealTime = 0;

	m_pBinBout->UpdateCurves();

	if(m_bModeIsSingle)
	{
		m_pSingle->UpdateValueText();
		m_pSingle->UpdateCurves();
	}
	else
	{
		for(int i = 0; i < m_oVoltCurList.size(); i++)
		{
			m_oVoltCurList[i]->AddStopPoint();
			m_oVoltCurList[i]->UpdateValueText();
			m_oVoltCurList[i]->UpdateCurves();
		}
	}

	m_pBinBout->SetInit(true);
	if(m_pSingle)
	{
		m_pSingle->SetInit(true);
	}
	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		m_oVoltCurList[i]->SetInit(true);
	}
}

void QStateMonitorWidget::StartStateMonitor()
{
	ClearStateMonitor();
	m_nTimerID = startTimer(TIMER);//启动1s的更新计时器
}

void QStateMonitorWidget::ClearStateMonitor()
{
	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		m_oVoltCurList[i]->ClearCurves();
	}

	if(m_pSingle)
	{
		m_pSingle->ClearCurves();
	}

	if(m_pBinBout)
	{
		m_pBinBout->ClearCurves();
	}
}

void QStateMonitorWidget::UpdateStateMonitorChs()
{
	UpdateCurve();
}

void QStateMonitorWidget::InitUI()
{
	resize(512, 255);

	setLayout(&m_oLayout);

	//2024-8-9 wuxinyi 修改字体大小统一
// 	QFont font = this->font();
// 	font.setPointSize(18);
// 	setFont(font);

	InitCurve(g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels, 0, g_oLocalSysPara.m_fAC_VolMax, 0, g_oLocalSysPara.m_fAC_CurMax
		, g_theTestCntrFrame->GetCurEventResult()->m_BinIn, g_theTestCntrFrame->GetCurEventResult()->m_BinOut);
}

void QStateMonitorWidget::UpdateCurve()
{
	CSttMacroChannels *pChls = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
	double fUMin = 0;
	double fUMax = g_oLocalSysPara.m_fAC_VolMax;
	double fIMin = 0;
	double fIMax = g_oLocalSysPara.m_fAC_CurMax;
	long *pBinInData = g_theTestCntrFrame->GetCurEventResult()->m_BinIn;
	long *pBinOutData = g_theTestCntrFrame->GetCurEventResult()->m_BinOut;
	//释放原数据
	if(m_pSingle)
	{
		delete m_pSingle;
		m_pSingle = NULL;
	}
	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		delete m_oVoltCurList[i];
	}
	m_oVoltCurList.clear();

	m_tabWidget.clear();

	InitCurve(pChls, fUMin, fUMax, fIMin, fIMax, pBinInData, pBinOutData);
}

void QStateMonitorWidget::InitCurve(CSttMacroChannels *pChls,double fUMin,double fUMax
									,double fIMin,double fIMax,long *pBinInData,long *pBinOutData)
{
	//初始化电压电流状态图
	m_oUChls.AppendClone(pChls->m_oVolChListRef);
	m_oIChls.AppendClone(pChls->m_oCurChListRef);
	//m_oUChls.Append(pChls->m_oVolChListRef);
	//m_oIChls.Append(pChls->m_oCurChListRef);

	long nGroup = 0;
	if (!m_bModeIsSingle)
	{
		long nUChlNum = m_oUChls.GetCount();
		long nIChlNum = m_oIChls.GetCount();
		long nMaxChlNum = qMax(nUChlNum,nIChlNum);
		if (nMaxChlNum <= 4)
		{
			nGroup = 1;
			QStateMonitorVoltCur* pChlPlot = new QStateMonitorVoltCur;
			pChlPlot->InitYTick(fUMin,fUMax,fIMin,fIMax);
			pChlPlot->InitCurve(&m_oUChls, &m_oIChls);	
			m_oVoltCurList.append(pChlPlot);
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
				QStateMonitorVoltCur* pChlPlot = new QStateMonitorVoltCur;
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

				pChlPlot->InitYTick(fUMin,fUMax,fIMin,fIMax);
				pChlPlot->InitCurve(&oUChls, &oIChls);	
				oUChls.RemoveAll();
				oIChls.RemoveAll();
				m_oVoltCurList.append(pChlPlot);
			}
		}
	}
	else
	{
		m_pSingle = new QStateMonitorVoltCur;
		m_pSingle->InitCurve(&m_oUChls , &m_oIChls);
		m_pSingle->setParent(this);
	}

	//分配显示的图像
	if (nGroup > 0 && !m_bModeIsSingle)
	{
		m_tabWidget.setParent(this);
		for (int i=0; i< nGroup; i++)
		{
			CString strGroup;
			xlang_GetLangStrByFile(strGroup, "Native_Group");
			strGroup += QString::number(i + 1);
			m_tabWidget.addTab(m_oVoltCurList[i], strGroup);
		}

		m_oLayout.addWidget(&m_tabWidget, 0, 0);
//		nGroup = 1;
	}
	else
	{
		m_pFrame = new QFrame(this);//add wangtao 20240812 使m_pSingle和m_pBinBout显示上对齐
		m_FrameLayout = new QHBoxLayout(m_pFrame);
		m_pFrame->setFrameShape(QFrame::NoFrame); // 设置边框样式
		m_FrameLayout->addSpacing(9);
		m_FrameLayout->addWidget(m_pSingle);
		//m_FrameLayout->addSpacing(20);
		m_pFrame->setLayout(m_FrameLayout);
		m_oLayout.addWidget(m_pFrame, 0, 0);
	}

	if(!m_pBinBout)
	{
		m_pBinBout = new QStateMonitorBinBout(this);
		m_oLayout.addWidget(m_pBinBout, 1, 0);
	}
	m_pBinBout->setBinBoutData(pBinInData, g_nBinCount, pBinOutData, g_nBoutCount);

	//20241011 huangliang 创建后也需要同步两图的宽度
	UpdateAxisScale();

	m_oUChls.RemoveAll();
	m_oIChls.RemoveAll();
}

void QStateMonitorWidget::timerEvent( QTimerEvent *event)
{
	if (event->timerId() == m_nTimerID)
	{
		//更新开入开出图
		m_pBinBout->UpdateCurves();

		if(m_bModeIsSingle)
		{
			//更新单通道图
			m_pSingle->UpdateValueText();
			m_pSingle->UpdateCurves();
		}
		else
		{
			m_oVoltCurList[m_tabWidget.currentIndex()]->UpdateValueText();
			m_oVoltCurList[m_tabWidget.currentIndex()]->UpdateCurves();
		}
	}

	QWidget::timerEvent(event);
}

void QStateMonitorWidget::UpdateLocalTime(double dLocalTime)
{
	if(m_dRealTime > dLocalTime)
	{
		return;
	}

	m_dLocalTime = dLocalTime;

	if(stt_Frame_IsTestStarted())
	{
		
		if (m_pSingle && m_pSingle->m_dRealTime)
		{
			if (m_pSingle->m_dLastTime < m_dLocalTime - m_pSingle->m_dRealTime)//add wangtao 20240912 防止状态图往回画，下同
		{
			m_pSingle->m_dLastTime = m_dLocalTime - m_pSingle->m_dRealTime;
		}
		}

		if(m_pBinBout->m_dRealTime)
		{
			if (m_pBinBout->m_dLastTime < m_dLocalTime - m_pBinBout->m_dRealTime)
			{
			m_pBinBout->m_dLastTime = m_dLocalTime - m_pBinBout->m_dRealTime;
			}
//			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("m_pBinBout->m_dLastTime=%lf,"),m_pBinBout->m_dLastTime);
		}
		
		for (int i = 0; i < m_oVoltCurList.size(); i++)
		{
			if(m_oVoltCurList[i]->m_dRealTime)
			{
				if (m_oVoltCurList[i]->m_dLastTime<m_dLocalTime - m_oVoltCurList[i]->m_dRealTime)
				{
				m_oVoltCurList[i]->m_dLastTime = m_dLocalTime - m_oVoltCurList[i]->m_dRealTime;
				}
			}	
		}
	}
}

void QStateMonitorWidget::OnRtDataChanged()
{
	CSttGlobalRtDataMngr *pRtDataMngr = &g_oSttTestResourceMngr.m_oRtDataMngr;
	CSttMacroChannels *pMacroChs = pRtDataMngr->m_pMacroChannels;	
	double dTime = 0;

	if (!pMacroChs->m_oHisTimesBuf.GetLastMemVal(dTime))
	{
		return;
	}

	if(m_bModeIsSingle)
	{
		if(!m_pSingle->m_dRealTime)
		{
			m_pSingle->m_dRealTime = dTime;
		}
		else
		{
			m_pSingle->m_dLastTime = dTime - m_pSingle->m_dRealTime;
		}

		m_pSingle->AddPoint(pMacroChs);
	}
	else
	{
		for (int i = 0; i < m_oVoltCurList.size(); i++)
		{
			QStateMonitorVoltCur* pVoltCur = m_oVoltCurList[i];
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
	}

	if(!m_pBinBout->m_dRealTime)
	{
		m_pBinBout->m_dRealTime = dTime;
		m_pBinBout->InitBinBoutPoint(0);
	}

	if(!m_dRealTime)
	{
		m_dRealTime = dTime;
	}
}

void QStateMonitorWidget::AddBinBoutPoint(long nIndex, double x, double y)
{
	m_pBinBout->AddBinBoutPoint(nIndex, x, y);
}

void QStateMonitorWidget::SetSingle(bool bSingle)
{
	if(bSingle == m_bModeIsSingle)
	{
		return;
	}

	m_bModeIsSingle = bSingle;
	UpdateCurve();
}

void QStateMonitorWidget::slot_YRangeChanged(changed_type tagType, QString strText, float fDown, float fUp)
{
	//单通道变更的响应函数
	if(m_pSingle)
	{
		m_pSingle->SetSingleTitle(strText);
		m_pSingle->UpdateYLeftRightScale(tagType, fDown, fUp);
		m_pSingle->replot();
	}
}

void QStateMonitorWidget::ChangeListType( int type,double fUMin,double fUMax,double fIMin,double fIMax )
{
	for(int i=0; i<m_oVoltCurList.size(); i++)
	{
		QStateMonitorVoltCur *p = m_oVoltCurList.at(i);
		p->ChangeType(type);
		p->InitYTick(fUMin,fUMax,fIMin,fIMax);
	}
}

void QStateMonitorWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		QStateMonitorVoltCur* pChlPlot = (QStateMonitorVoltCur*)m_oVoltCurList[i];
		//pChlPlot->resize(event->size());
		QWidget* currentTab = m_tabWidget.currentWidget();
		if (currentTab)
		{
			pChlPlot->resize(currentTab->size());
		}
		//2024-10-18 wuxinyi 修改切组后大小不一致
		pChlPlot->setStyleSheet("padding: 0px; margin: 0px;");
	}
}

void QStateMonitorWidget::UpdateAxisScale()	//20240913 huangliang 
{
	if (m_pBinBout == NULL)
		return;
	m_pBinBout->setAxisScaleDraw(QwtPlot::yLeft, new BinBoutYScaleDraw(true));
	m_pBinBout->setAxisScaleDraw(QwtPlot::yRight, new BinBoutYScaleDraw(false));

	//20241014 huangliang m_oVoltCurList和m_pSingle，谁存在则刷新谁
	if (m_oVoltCurList.count() > 0)	//20241012 huangliang 
	{
	for (int i = 0; i < m_oVoltCurList.size(); i++)
	{
		m_oVoltCurList[i]->setAxisScaleDraw(QwtPlot::yLeft, new UIYScaleDraw(true));
		m_oVoltCurList[i]->setAxisScaleDraw(QwtPlot::yRight, new UIYScaleDraw(false));
	}
	}	

	if (m_pSingle != NULL)	
	{
		m_pSingle->setAxisScaleDraw(QwtPlot::yLeft, new BinBoutYScaleDraw(true));
		m_pSingle->setAxisScaleDraw(QwtPlot::yRight, new BinBoutYScaleDraw(false));
	}	
}