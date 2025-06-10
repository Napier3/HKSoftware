#include "stdafx.h"
#include "SttAssistGlobalApi.h"

#ifndef NOT_USE_ASSIST
#include "SttAssistEngine.h"
#endif

//总的接口函数
//调用全局对象CSttAssistEngine进行初始化和释放
bool assist_create(const CString &strAssistID)
{
#ifndef NOT_USE_ASSIST
	CSttAssistEngine::Create();
	g_theAssistEngine->assist_run_script(strAssistID);
#endif

	return true;
}

bool assist_release()
{
#ifndef NOT_USE_ASSIST
	CSttAssistEngine::Release();
#endif

	return true;
}


//智能助手
void assist_show_menu()
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_show_menu();
#endif
}

void assist_set_entry_wnd(void *pEntryWnd)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_set_entry_wnd(pEntryWnd);
#endif
}

void assist_set_main_wnd(CSttWndAssistInterface *pSttMainWnd)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_set_main_wnd(pSttMainWnd);
#endif
}

void assist_set_app(CSttAppAssistInterface *pApp)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_set_app(pApp);
#endif
}

bool assist_run_script(const CString &strScriptFile)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return true;
	}

	g_theAssistEngine->assist_run_script(strScriptFile);
#endif

	return true;
}

bool assist_close_script(const CString &strScriptFile)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return true;
	}

	g_theAssistEngine->assist_close_script(strScriptFile);
#endif

	return true;
}


//事件相关函数
void assist_wnd_show(const CString &strWndID, CSttWndAssistInterface *pWnd, bool bShow)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_wnd_show(strWndID, pWnd, bShow);
#endif
}

void assist_widget_show(const CString &strWndID, QWidget *pWidget, bool bShow)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_widget_show(strWndID, pWidget, bShow);
#endif
}


void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_ui_msg(strUiMsgID, pDatas);
#endif
}

void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_data_change(strWndID, strDataID, strValue);
#endif
}

bool assist_event(const CString &strEventID, CExBaseObject *pSttParas)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return true;
	}

	return g_theAssistEngine->assist_event(strEventID, pSttParas);
#endif

	return true;
}


//消息显示相关
void assist_show_msg(const CString &strMsg, long nShowTimeLong)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_show_msg(strMsg, nShowTimeLong);
#endif
}

void assist_show_msg_ex(const CString &strWndID, const CString &strMsg, long nShowTimeLong)
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_show_msg_ex(strWndID, strMsg, nShowTimeLong);
#endif
}

void assist_show_result(CDataGroup *pDatas) //保留
{
#ifndef NOT_USE_ASSIST
	if (g_theAssistEngine == NULL)
	{
		return;
	}

	g_theAssistEngine->assist_show_result(pDatas);
#endif
}

