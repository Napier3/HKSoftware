#include "stdafx.h"
#include "SttAssistWzd_ScriptRun.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttTestCntrCmdDefine.h"
#include "../../SttSystemConfig/SttSystemConfig.h"


CSttAssistWzd_ScriptRun::CSttAssistWzd_ScriptRun()
{
	
}


CSttAssistWzd_ScriptRun::~CSttAssistWzd_ScriptRun()
{
	
}

void CSttAssistWzd_ScriptRun::assist_init()
{
	
}

void CSttAssistWzd_ScriptRun::assist_wnd_show(const CString &strWndID, CSttAssistWzd_ScriptRun *pWnd, bool bShow)
{
	
}

void CSttAssistWzd_ScriptRun::assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas)
{
	
}

void CSttAssistWzd_ScriptRun::assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue)
{
	
}

bool CSttAssistWzd_ScriptRun::assist_event(const CString &strEventID, CExBaseObject *pSttParas)
{
	if (strEventID == STT_CNTR_CMD_StartTest)
	{
		return Event_StartTest(pSttParas);
	}
	else if (strEventID == Event_ID_OnTestStarted)
	{
		return Event_OnTestStarted(pSttParas);
	}
	else if (strEventID == Event_ID_OnTestFinished)
	{
		return Event_OnTestFinished(pSttParas);
	}
	
	return true;
}

bool CSttAssistWzd_ScriptRun::Event_StartTest(CExBaseObject *pSttParas)
{
	return true;
}

bool CSttAssistWzd_ScriptRun::Event_OnTestStarted(CExBaseObject *pSttParas)
{
	CSttDevConfig* pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nMultiExpList == 0)
	{
		return true;
	}

	if (g_theTestCntrFrame->IsMultiTestItems())
	{
		if (g_theTestCntrFrame->m_pSttGbTreeView->isHidden())
		{
			g_theTestCntrFrame->SendMenuButtonClick(STT_CNTR_CMD_ItemList);
		}
	}

	return true;
}

bool CSttAssistWzd_ScriptRun::Event_OnTestFinished(CExBaseObject *pSttParas)
{
	CSttDevConfig* pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nMultiExpList == 0)
	{
		return true;
	}

	if (g_theTestCntrFrame->IsMultiTestItems())
	{
		if (!g_theTestCntrFrame->m_pSttGbTreeView->isHidden())
		{
			g_theTestCntrFrame->SendMenuButtonClick(STT_CNTR_CMD_ItemList);
		}
	}

	return true;
}
