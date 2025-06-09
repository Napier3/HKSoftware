#include "StateMonitor.h"
#include "../../../SttTestCtrl/SttTestAppBase.h"
#include "../../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../SttTestCntrFrameBase.h"

QStateMonitor* g_pStateMonitor = NULL;

QStateMonitor::QStateMonitor(bool bIsEx, QWidget *parent)
	: QWidget(parent)
{
	m_bIsPlotEx = bIsEx;
	m_bIsGradient = true;
	m_pLay = NULL;
	m_pTimeResponseWidget = NULL;
	g_pStateMonitor = this;
	initUI();
}

QStateMonitor::~QStateMonitor()
{

}

void QStateMonitor::initUI()
{
	setObjectName(QString::fromUtf8("MonitorTab"));
	resize(1024, 510);

	QFont font;
	font.setPointSize(18);
	setFont(font);

	m_pLay = new QGridLayout(this);
	m_pLay->setSpacing(0);
	m_pLay->setContentsMargins(0, 0, 0, 0);
	m_pLay->setObjectName(QString::fromUtf8("gridLayout"));

	m_pTimeResponseWidget = new QTimeResponseWidget(this);
	m_pTimeResponseWidget->setObjectName(QString::fromUtf8("QTimeResponseWidget"));

	m_pLay->addWidget(m_pTimeResponseWidget, 0, 0, 1, 1);

	m_pTimeResponseWidget->initUI(g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels, 0, g_oLocalSysPara.m_fAC_VolMax, 0, g_oLocalSysPara.m_fAC_CurMax
		, g_theTestCntrFrame->GetCurEventResult()->m_BinIn, g_theTestCntrFrame->GetCurEventResult()->m_BinOut);
	
	QMetaObject::connectSlotsByName(this);
}

void QStateMonitor::UpdateStateMonitorChs()
{
	disconnect(parent(), SIGNAL(sig_YRangeChanged(changed_type ,QString ,float ,float )), this, SLOT(slot_YChanged(changed_type,QString ,float ,float )));
	m_pTimeResponseWidget->UpdateUI(g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels, 0, g_oLocalSysPara.m_fAC_VolMax, 0, g_oLocalSysPara.m_fAC_CurMax
		, g_theTestCntrFrame->GetCurEventResult()->m_BinIn, g_theTestCntrFrame->GetCurEventResult()->m_BinOut);
	connect(parent(), SIGNAL(sig_YRangeChanged(changed_type ,QString ,float ,float )), this, SLOT(slot_YChanged(changed_type,QString ,float ,float )));
}

void QStateMonitor::InitConnection(QWidget* parent)
{
	if(parent)
	{
		connect(parent, SIGNAL(sig_YRangeChanged(changed_type ,QString ,float ,float )), this, SLOT(slot_YChanged(changed_type,QString ,float ,float )));
	}
}

void QStateMonitor::UpdateCurveData(CChlTimeResponsePlotEx* pChlTimePlotEx, double dLastTime)
{
	CSttMacroChannel *pMacroCh = NULL;
	tmt_rtdata_ch tmpRtData;
	tmt_rtdata_ch* pRtData = NULL;
	if (!pChlTimePlotEx->m_bInited)
	{
		lock.unlock();
		return;
	}

	if (pChlTimePlotEx->m_rtDataList.size()==0)
	{
		lock.unlock();
		return;
	}

	int nIndex = 0;
	pChlTimePlotEx->m_dLastTime = dLastTime;
	m_pTimeResponseWidget->m_pBinBoutInTimeResponsePlot->m_dLastTime = dLastTime;

	CChlTimeSignal* pNewSignal = pChlTimePlotEx->NewSignal();
	POS pos = pChlTimePlotEx->m_oMacroChannels.GetHeadPosition();
	while(pos)
	{
		pMacroCh = (CSttMacroChannel*)pChlTimePlotEx->m_oMacroChannels.GetNext(pos);
		pRtData = pChlTimePlotEx->m_rtDataList.at(nIndex);

		if (pRtData && pMacroCh->m_oHisDataBuf.GetLastMemVal(tmpRtData))
		{
			pRtData->m_fMag = tmpRtData.m_fMag;
			pRtData->m_fAng = tmpRtData.m_fAng;
			pRtData->m_fFreq = tmpRtData.m_fFreq;

			pChlTimePlotEx->AppendSignalData(pNewSignal,dLastTime,&tmpRtData);
		}

		nIndex++;

	pChlTimePlotEx->AppenSignalInfo(pNewSignal);
	m_pTimeResponseWidget->m_pBinBoutInTimeResponsePlot->AppendSignalData(dLastTime);	
	}
}

void QStateMonitor::UpdateCurChannal(int nChannel, int type, bool bStart)
{
	if(m_pTimeResponseWidget && m_pTimeResponseWidget->m_pChlTimePlotEx)
	{
		m_pTimeResponseWidget->m_pChlTimePlotEx->setData(nChannel, type, bStart);
	}
}

void QStateMonitor::SetModeGradient(bool bIsGradient)
{
	m_bIsGradient = bIsGradient;
}

void QStateMonitor::UpdateCurveData()
{
	if(m_pTimeResponseWidget)
	{
		lock.lockForWrite();
		CSttGlobalRtDataMngr *pRtDataMngr = &g_oSttTestResourceMngr.m_oRtDataMngr;
		CSttMacroChannels *pMacroChs = pRtDataMngr->m_pMacroChannels;	
		double dLastTime = 0;

		if (!pMacroChs->m_oHisRealTimesBuf.GetLastMemVal(dLastTime))
		{
			lock.unlock();
			return;
		}

		//不是递变模式则不用按照LastTime刷新
		if(!m_bIsGradient && pMacroChs->m_oHisRealTimesBuf.GetDataLength() != 1)
		{
			lock.unlock();
			return;
		}

		if(m_bIsPlotEx)
		{
			UpdateCurveData(m_pTimeResponseWidget->m_pChlTimePlotEx, dLastTime);		
		}
		else
		{
			for (int i = 0; i < m_pTimeResponseWidget->m_oChlTimePlotList.size(); i++)
			{
				CChlTimeResponsePlotEx* pChlTimePlotEx = m_pTimeResponseWidget->m_oChlTimePlotList[i];
				UpdateCurveData(pChlTimePlotEx, dLastTime);
			}
		}

//		emit sig_UpdateCurveData();
		lock.unlock();
	}
}

void QStateMonitor::slot_YChanged(changed_type type, QString str,float down,float up)
{
	if (m_pTimeResponseWidget->m_pChlTimePlotEx != NULL)
	{
		m_pTimeResponseWidget->m_pChlTimePlotEx->updateYScale(type,str,down,up);
	}
}

void QStateMonitor::UpdateStateMonitor(bool bIsPlotEx)
{
	m_bIsPlotEx = bIsPlotEx;
	m_pTimeResponseWidget->UpdateUI(g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels, 0, g_oLocalSysPara.m_fAC_VolMax,0,g_oLocalSysPara.m_fAC_CurMax
		,g_theTestCntrFrame->GetCurEventResult()->m_BinIn, g_theTestCntrFrame->GetCurEventResult()->m_BinOut);
}