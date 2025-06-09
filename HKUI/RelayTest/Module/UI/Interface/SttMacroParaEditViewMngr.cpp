#include "SttMacroParaEditViewMngr.h"

#include "../Webkit/SttMacroParaEditViewHtml.h"
#include "SttMacroParaEditViewOriginal.h"

/*
#include "../Manual/SttMacroParaEditViewManual.h"
#include "../SequenceManu/SttMacroParaEditViewSequenceManu.h"
#include "../State/SttMacroParaEditViewState.h"
#include "../Harm/SttMacroParaEditViewHarm.h"
#include "../Gradient/SttMacroParaEditViewGradient.h"
#include "../TransPlay/SttMacroParaEditViewTransPlay.h"
#include "../State/GooseAbnormal/SttMacroParaEditViewGooseAbnormal.h"
#include "../SOE/SttMacroParaEditViewSoe.h"
#include "../SequenceGradient/SttMacroParaEditViewSequenceGradient.h"
#include "../LineVolGradient/SttMacroParaEditViewLineVolGradient.h"
#include "../LineVoltManu/SttMacroParaEditViewLineVoltManu.h"
#include "../MUAutoTest/SttMacroParaEditViewMuAutoTest.h"
#include "../RemoteMeas/SttMacroParaEditViewRemoteMeas.h"
#include "../RemoteCtrl/SttMacroParaEditViewRemoteCtrl.h"
#include "../TerminalAutoTest/SttMacroParaEditViewTerminalAutoTest.h"
#include "../IntelligentTerminal/SttMacroParaEditViewIntelligentTerminal.h"
#include "../SttTestCntrCmdDefine.h"
#include "../ShortTimeOver/QttMacroParaEditViewShortTimOver.h"
#include "../VoltageTimeTypeSectorMode/QSttMacroParaEditViewVolTimeTypeSec.h"
#include "../FaultGradient/SttMacroParaEditViewFaultGradient.h"
#include "../AntiShakeTime/QSttMacroParaEditViewAntiShakeTime.h"
#include "../ADMUAccurAutoTest/SttMacroParaEditViewADMUAccurAutoTest.h"
#include "../PowerManu/SttMacroParaEditViewPowerManu.h"
#include "../ImpedanceManu/SttMacroParaEditViewImpedanceManu.h"
#include "../CBOperate/QSttMacroParaEditViewCBOperate.h"
#include "../../TestUI/Distance/SttMultiMacroParaEditViewDistance.h"
#include "../../TestUI/LowFreq/SttMultiMacroParaEditViewLowFreq.h"
#include "../../TestUI/LowVol/SttMultiMacroParaEditViewLowVol.h"
#include "../Swing/SttMacroParaEditViewSwing.h"
#include "../../TestUI/ActTime/SttMultiMacroParaEditViewActionTime.h"
#include "../../TestUI/CurrInverseTime/SttMultiMacroParaEditViewCurrInverseTime.h"
#include "../../TestUI/DistanceSearch/SttMultiMacroParaEditViewDistanceSearch.h"
#include "../../TestUI/RecloseAcc/SttMultiMacroParaEditViewRecloseAcc.h"
#include "../../TestUI/PowerDirection/SttMultiMacroParaEditViewPowerDir.h"
#include "../../TestUI/VolInverseTime/SttMultiMacroParaEditViewVolInverseTime.h"
*/

//2024-7-12 lijunqing 全局工厂
#include "SttMacroParaEditFactory.h"
CSttMacroParaEditFactory *g_theMacroParaEditFactory = 0;

extern long g_nLogDebugInfor;

long CSttMacroParaEditViewMngr::g_nSttMacroParaEditRef = 0;
CSttMacroParaEditViewMngr* CSttMacroParaEditViewMngr::g_pSttMacroParaEditViewMngr = NULL;


CSttMacroParaEditViewMngr::CSttMacroParaEditViewMngr()
{
	m_pMacroParaView = NULL;
	m_pSttMacroParaEditViewHtml = NULL;
	m_pSttMacroParaEditViewHtmlForDelete = NULL;
}

CSttMacroParaEditViewMngr::~CSttMacroParaEditViewMngr()
{

}

CSttMacroParaEditViewMngr* CSttMacroParaEditViewMngr::Create()
{
	g_nSttMacroParaEditRef++;

	if (g_nSttMacroParaEditRef == 1)
	{
		g_pSttMacroParaEditViewMngr = new CSttMacroParaEditViewMngr();
	}

	return g_pSttMacroParaEditViewMngr;
}

void CSttMacroParaEditViewMngr::Release()
{
	g_nSttMacroParaEditRef--;

	if (g_nSttMacroParaEditRef == 0)
	{
		delete g_pSttMacroParaEditViewMngr;
		g_pSttMacroParaEditViewMngr = NULL;
	}
}

void CSttMacroParaEditViewMngr::Clear(void *pView)
{
	if (pView == (void*)m_pSttMacroParaEditViewHtml)
	{
		return;
	}

	if (pView != NULL)
	{
		delete pView;
	}
}	

void CSttMacroParaEditViewMngr::DeletePrev()
{

}	

void CSttMacroParaEditViewMngr::DeleteSttMacroParaEditViewHtml()
{
	QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
	QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtmlDelete = NULL;
	pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;

	if (pSttMacroParaEditViewHtml != NULL)
	{
		g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = pSttMacroParaEditViewHtml;
		pSttMacroParaEditViewHtml->OpenHtmlFile("");
		pSttMacroParaEditViewHtml->hide();
		pSttMacroParaEditViewHtml->deleteLater();
	}

	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = NULL;
	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml = NULL;
}

//#include "../SttTestCntrThread.h"
CSttMacroParaEditInterface* CSttMacroParaEditViewMngr::CreateSttMacroParaEditView(const CString &strMacroID, const CString &strGridFile,BOOL bUseExist)
{
	if (bUseExist)
	{//2022-3-10  lijunqing  如果是返回存在的功能视图
		if(g_pSttMacroParaEditViewMngr->m_strMacroID == strMacroID 
			&& g_pSttMacroParaEditViewMngr->m_pMacroParaView != NULL)
		{
			return g_pSttMacroParaEditViewMngr->m_pMacroParaView;
		}
	}

	g_pSttMacroParaEditViewMngr->Clear(NULL);
	g_pSttMacroParaEditViewMngr->m_strMacroID = strMacroID;
	CSttMacroParaEditInterface *pNew = NULL;
	BOOL bWeb = FALSE;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin CreateSttMacroParaEditView -  >>");	}

    pNew = g_theMacroParaEditFactory->CreateSttMacroParaEditView(strMacroID, strGridFile, bUseExist);


    if (pNew != 0)
    {
        pNew->InitUI(strGridFile);
    }

	if (g_pSttMacroParaEditViewMngr->m_pMacroParaView != NULL)
	{
		if (!g_pSttMacroParaEditViewMngr->m_pMacroParaView->IsHtmlView())
		{
			CSttMacroParaEditViewOriginal *pView = (CSttMacroParaEditViewOriginal*)g_pSttMacroParaEditViewMngr->m_pMacroParaView;
			pView->deleteLater();
		}
	}

	if (!bWeb)
	{
		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
		pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;

		if (pSttMacroParaEditViewHtml != NULL)
		{
			pSttMacroParaEditViewHtml->hide();
			pSttMacroParaEditViewHtml->deleteLater();
			g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml = NULL;
		}
	}


	g_pSttMacroParaEditViewMngr->m_pMacroParaView = pNew;

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end CreateSttMacroParaEditView -  >>");	}

	return pNew;
}

long g_nCreateNewViewEveryTime = 1;

CSttMacroParaEditInterface* CSttMacroParaEditViewMngr::GetSttMacroParaEditViewHtml()
{
	QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
	QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtmlDelete = NULL;
	pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;
	//		pSttMacroParaEditViewHtml = NULL;

	if (pSttMacroParaEditViewHtml != NULL)
	{
		//pSttMacroParaEditViewHtml->back();
		g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = pSttMacroParaEditViewHtml;
		pSttMacroParaEditViewHtml->OpenHtmlFile("");
		pSttMacroParaEditViewHtml->stop();
		pSttMacroParaEditViewHtml->close();

		if (g_nCreateNewViewEveryTime == 1)
		{
			pSttMacroParaEditViewHtml->hide();
			pSttMacroParaEditViewHtmlDelete = pSttMacroParaEditViewHtml;
			pSttMacroParaEditViewHtml = new QSttMacroParaEditViewHtml();
		}
	}
	else
	{
		pSttMacroParaEditViewHtml = new QSttMacroParaEditViewHtml();
	}

	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml = pSttMacroParaEditViewHtml;

	if (g_nCreateNewViewEveryTime == 1)
	{
		if (pSttMacroParaEditViewHtmlDelete != NULL)
		{
			pSttMacroParaEditViewHtmlDelete->deleteLater();
		}
	}
	
	return pSttMacroParaEditViewHtml;
}
