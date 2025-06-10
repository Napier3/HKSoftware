#include "SttMacroParaEditViewMngr.h"

#include "../Manual/SttMacroParaEditViewManual.h"
#include "../SequenceManu/SttMacroParaEditViewSequenceManu.h"
#include "../State/SttMacroParaEditViewState.h"
#include "../Harm/SttMacroParaEditViewHarm.h"
#include "../Gradient/SttMacroParaEditViewGradient.h"
#include "../TransPlay/SttMacroParaEditViewTransPlay.h"
//#include "../Webkit/SttMacroParaEditViewHtml.h"
#include "../State/GooseAbnormal/SttMacroParaEditViewGooseAbnormal.h"
#include "../SOE/SttMacroParaEditViewSoeWidget.h"
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
    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtmlDelete = NULL;
    //pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;

    //if (pSttMacroParaEditViewHtml != NULL)
    //{
    //	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = pSttMacroParaEditViewHtml;
    //	pSttMacroParaEditViewHtml->OpenHtmlFile("");
    //	pSttMacroParaEditViewHtml->hide();
    //	pSttMacroParaEditViewHtml->deleteLater();
    //}

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

 	if((strMacroID == STT_ORG_MACRO_ManualTest)||(strMacroID == STT_ORG_MACRO_MUAccuracyTest)||(strMacroID == STT_ORG_MACRO_MUFirstCycleTest)||
		(strMacroID == STT_ORG_MACRO_MUTimingAccurTest)||(strMacroID == STT_ORG_MACRO_MUPunctAccurTest))
 	{
 		pNew = new QSttMacroParaEditViewManual;  
 	}
 	else if(strMacroID == STT_ORG_MACRO_StateTest)
 	{
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin new QSttMacroParaEditViewState -  >>");	}
		QSttMacroParaEditViewState *pSttMacroParaEditViewState = new QSttMacroParaEditViewState(false);
		pNew = pSttMacroParaEditViewState;
		if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end new QSttMacroParaEditViewState -  >>");	}

#ifndef SttTestCntrThread_H
		pSttMacroParaEditViewState->initUI_Paras(false);
#else
		g_theSttTestCntrThread->PostThreadMessage(2, (unsigned long)pNew, (unsigned long)pNew);
#endif
 	}
	else if(strMacroID == STT_ORG_MACRO_SmvAbnTest)
	{
		QSttMacroParaEditViewState *pSttMacroParaEditViewState = new QSttMacroParaEditViewState(false);
		pNew = pSttMacroParaEditViewState;
#ifndef SttTestCntrThread_H
		pSttMacroParaEditViewState->initUI_Paras(true);
#else
		g_theSttTestCntrThread->PostThreadMessage(3, (unsigned long)pNew, (unsigned long)pNew);
#endif
	}
	else if(strMacroID == STT_ORG_MACRO_GseAbnTest)
	{
        QSttMacroParaEditViewGooseAbnormal *pSttMacroParaEditViewGooseAbnormal = new QSttMacroParaEditViewGooseAbnormal(false);
		pNew = pSttMacroParaEditViewGooseAbnormal;
#ifndef SttTestCntrThread_H
		pSttMacroParaEditViewGooseAbnormal->initUI_Paras(false,false);
#else
		g_theSttTestCntrThread->PostThreadMessage(4, (unsigned long)pNew, (unsigned long)pNew);
#endif
 	}
	else if(strMacroID == STT_ORG_MACRO_GradientTest)
	{
		pNew = new QSttMacroParaEditViewGradient;     
	}
	else if(strMacroID == STT_ORG_MACRO_HarmTest)
	{
		pNew = new QSttMacroParaEditViewHarm;  
	}
	else if(strMacroID == STT_ORG_MACRO_ReplayTest)
	{
		pNew = new QSttMacroParaEditViewTransPlay;  
	}
	else if(strMacroID == STT_ORG_MACRO_SequenceManuTest)//增加用于通用序分量  20230208 zhouhj
	{
		pNew = new QSttMacroParaEditViewSequenceManu;  
	}
	else if(strMacroID == STT_ORG_MACRO_LineVolManuTest)//增加用于通用线电压  20230803 gyp
	{
		pNew = new QSttMacroParaEditViewLineVoltManu;  
	}
	else if(strMacroID == STT_ORG_MACRO_SoeTest)//增加用于SOE  20230408 suyang
	{
		pNew = new QSttMacroParaEditViewSoeWidget;  
	}
	else if(strMacroID == STT_ORG_MACRO_SequenceGradientTest)//序分量递变 20230815 dxy
	{
		pNew = new QSttMacroParaEditViewSequenceGradient;  
	}
	else if(strMacroID == STT_MACRO_ID_FaultGradientTest)//故障递变 2023-12-28 yuanting
	{
		pNew = new QSttMacroParaEditViewFaultGradient;  
	}
	else if(strMacroID == STT_ORG_MACRO_LineVolGradientTest)//线电压递变 20230825 zyy
	{
		pNew = new QSttMacroParaEditViewLineVolGradient;  
	}
	else if(strMacroID == STT_ORG_MACRO_MUAutoTest) // 2023-10-24 lcq
	{
        pNew = new QSttMacroParaEditViewMuAutoTest;
	}
	else if(strMacroID == STT_ORG_MACRO_RemoteMeasTest)//遥测 20231120 zhangyq
	{
		pNew = new QSttMacroParaEditViewRemoteMeas;  
	}
	//else if(strMacroID == STT_ORG_MACRO_RemoteCtrlTest)//遥控
	//{
	//	pNew = new QSttMacroParaEditViewRemoteCtrl;  
	//}
	else if (strMacroID == STT_ORG_MACRO_TerminalAutoTest)//chenling
	{
		pNew = new QSttMacroParaEditViewTerminalAutoTest;
	}
        else if(strMacroID == STT_ORG_MACRO_IntelligentTest)//增加用于智能终端测试  20231107 gongyiping
	{
		pNew = new QSttMacroParaEditViewIntelligentTerminal;  
	}
	else if(strMacroID == STT_ORG_MACRO_ShortTimeOverTest)//2023/11/30 wangjunsheng 短时过量输入模块
	{
		pNew = new QttMacroParaEditViewShortTimOver;  
	}
	else if(strMacroID == STT_ORG_MACRO_VolTimeTypeSecTest)//20240112 xueyangfan 电压时间型分段模式
	{
		pNew = new QSttMacroParaEditViewVolTimeTypeSec;
	}
    else if(strMacroID == STT_ORG_MACRO_AntiShakeTimeTest)//20240305 xueyangfan 防抖时间测试
    {
    	pNew = new QSttMacroParaEditViewAntiShakeTime;
    }
	else if(strMacroID == STT_ORG_MACRO_MUAccurAutoTest)//2024.5.28 ADMU自动测试
	{
		if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
		{
			pNew = new QSttMacroParaEditViewAdmuAccurAutoTest;
		}
		else
		{
			bWeb = TRUE;
			pNew = GetSttMacroParaEditViewHtml();
		}

	}
	else if(strMacroID == STT_ORG_MACRO_PowerManuTest)//
	{
		pNew = new QSttMacroParaEditViewPowerManu;
	}
	else if(strMacroID == STT_ORG_MACRO_ImpedanceManuTest)//20240611 zhangyq 通用试验（阻抗）
	{
		pNew = new QSttMacroParaEditViewImpedanceManu;
	}
	else if(strMacroID == STT_ORG_MACRO_CBOperateTest)//20240612 xueyangfan 整组传动
	{
		pNew = new QSttMacroParaEditViewCBOperate;
	}
	else if(strMacroID == STT_ORG_MACRO_DistanceTest_I)//20240620 zhouhj 国际版-距离保护
	{
		pNew = new QSttMultiMacroParaEditViewDistance(strGridFile);
		((QSttMultiMacroParaEditViewDistance*)pNew)->InitUI_OneMacro();
	}
	else if (strMacroID == STT_ORG_MACRO_Iec61850Config
		|| strMacroID == STT_ORG_MACRO_SystemConfig
		|| strMacroID == STT_ORG_MACRO_ChMapsConfig)
	{
		return NULL;
	}
	else
	{
		bWeb = TRUE;
		pNew = GetSttMacroParaEditViewHtml();
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
        //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
        //pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;

        //if (pSttMacroParaEditViewHtml != NULL)
		{
            //pSttMacroParaEditViewHtml->hide();
            //pSttMacroParaEditViewHtml->deleteLater();
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
    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = NULL;
    //QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtmlDelete = NULL;
    //pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml;
	//		pSttMacroParaEditViewHtml = NULL;

    //if (pSttMacroParaEditViewHtml != NULL)
    //{
    //	//pSttMacroParaEditViewHtml->back();
    //	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = pSttMacroParaEditViewHtml;
    //	pSttMacroParaEditViewHtml->OpenHtmlFile("");
    //	pSttMacroParaEditViewHtml->stop();
    //	pSttMacroParaEditViewHtml->close();
    //
    //	if (g_nCreateNewViewEveryTime == 1)
    //	{
    //		pSttMacroParaEditViewHtml->hide();
    //		pSttMacroParaEditViewHtmlDelete = pSttMacroParaEditViewHtml;
    //		pSttMacroParaEditViewHtml = new QSttMacroParaEditViewHtml();
    //	}
    //}
    //else
    //{
    //	pSttMacroParaEditViewHtml = new QSttMacroParaEditViewHtml();
    //}

    //g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtml = pSttMacroParaEditViewHtml;
    //
    //if (g_nCreateNewViewEveryTime == 1)
    //{
    //	if (pSttMacroParaEditViewHtmlDelete != NULL)
    //	{
    //		pSttMacroParaEditViewHtmlDelete->deleteLater();
    //	}
    //}
    //
    //return pSttMacroParaEditViewHtml;
}
