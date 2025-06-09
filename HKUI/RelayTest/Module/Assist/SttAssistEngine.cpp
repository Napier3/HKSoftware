#include "stdafx.h"
#include "SttAssistEngine.h"

#include "MU/SttAssistWzd_MuTest.h"
#include "DynEffect/SttAssistWndDynEffExecTool.h"
#include "QObjectGlobalApi.h"
#include "Script/SttAssistWzd_ScriptRun.h"
#include "../XLangResource_Native.h"

CSttAssistWndDynEffExecTool *g_theAssistWndDynEffExecTool = NULL;
CSttAssistEngine *g_theAssistEngine = NULL;

CSttAssistEngine* CSttAssistEngine::g_pSttAssistEngine = NULL;
long CSttAssistEngine::g_nSttAssistEngine = 0;

#include "QSttAssistMenuWidget.h"
QSttAssistMenuWidget *g_pAssistMenu = NULL;

void CSttAssistEngine::Create()
{
	g_nSttAssistEngine++;

	if (g_nSttAssistEngine == 1)
	{
		g_pSttAssistEngine = new CSttAssistEngine();
	}
}

void CSttAssistEngine::Release()
{
	g_nSttAssistEngine--;

	if (g_nSttAssistEngine == 0)
	{
		delete g_pSttAssistEngine;
		g_pSttAssistEngine = NULL;
	}
}

CSttAssistEngine::CSttAssistEngine()
{
	g_theAssistWndDynEffExecTool = new CSttAssistWndDynEffExecTool();
	g_theAssistEngine  =this;
	m_pCurrAssist = NULL;
	m_pEntryWnd = NULL;

	memset(m_arrWidgetShow, 0, sizeof(m_arrWidgetShow));
}


CSttAssistEngine::~CSttAssistEngine()
{
	delete g_theAssistWndDynEffExecTool;
	g_theAssistEngine = NULL;

	if (m_pCurrAssist != NULL)
	{
		delete m_pCurrAssist;
		m_pCurrAssist = NULL;
	}

	if (g_pAssistMenu != NULL)
	{
		delete g_pAssistMenu;
		g_pAssistMenu = NULL;
	}
}

//智能助手
void CSttAssistEngine::assist_show_menu()
{
	if (g_pAssistMenu == NULL)
	{
#ifdef _PSX_QT_LINUX_
        g_pAssistMenu = new QSttAssistMenuWidget(g_theTestCntrFrame);
#else
		 g_pAssistMenu = new QSttAssistMenuWidget();
#endif
	}

	g_pAssistMenu->ShowMenu();
}

void CSttAssistEngine::assist_set_entry_wnd(void *pEntryWnd)
{
	m_pEntryWnd = (QWidget*)pEntryWnd;
	show_start_tip();
}

void CSttAssistEngine::assist_set_main_wnd(CSttWndAssistInterface *pSttMainWnd)
{
	
}

void CSttAssistEngine::assist_set_app(CSttAppAssistInterface *pApp)
{
	
}

bool CSttAssistEngine::assist_run_script(const CString &strScriptFile)
{
	if (m_pCurrAssist != NULL)
	{
		delete m_pCurrAssist;
		m_pCurrAssist = NULL;
	}

	//d第一个阶段，先实现mutest，后面根据迭代过程的需要，实现流程化配置实现。
	if ((strScriptFile == STT_AssistID_MUTEST/*"mutest"*/)||(strScriptFile == STT_AssistID_ADMUTEST))
	{
		m_pCurrAssist = new CSttAssistWzd_MuTest();
	}
	else
	{
		if (strScriptFile == "ieccaptest")
		{
			g_theTestCntrFrame->InitIecCapTest(true, true,false);
		}

		if (strScriptFile == "remotectrltest")
		{
			g_theTestCntrFrame->InitRemoteCtrlTest(true, true,false);
		}

		m_pCurrAssist = new CSttAssistWzd_ScriptRun();
	}

	if (m_pCurrAssist != NULL)
	{
		m_pCurrAssist->assist_init();
	}

	return true;
}

bool CSttAssistEngine::assist_close_script(const CString &strScriptFile)
{
	return true;
}


//事件相关函数
void CSttAssistEngine::assist_wnd_show(const CString &strWndID, CSttWndAssistInterface *pWnd, bool bShow)
{
	
}

void CSttAssistEngine::assist_widget_show(const CString &strWndID, QWidget *pWidget, bool bShow)
{
	//首先移去已经隐藏的
	WidgetRemove();

	if (bShow)
	{
		WidgetAdd(strWndID, pWidget);
	}
	else
	{
		WidgetRemove(pWidget);
	}
}

void CSttAssistEngine::assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas)
{
	
}

void CSttAssistEngine::assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue)
{
	
}

bool CSttAssistEngine::assist_event(const CString &strEventID, CExBaseObject *pSttParas)
{
	bool bRet = TRUE;

	if (m_pCurrAssist != NULL)
	{
		bRet = m_pCurrAssist->assist_event(strEventID, pSttParas);
	}

	return bRet;
}


//消息显示相关
void CSttAssistEngine::assist_show_msg(const CString &strMsg, long nShowTimeLong)
{

}

void CSttAssistEngine::assist_show_msg_ex(const CString &strWndID, const CString &strMsg, long nShowTimeLong)
{
	
}


void CSttAssistEngine::assist_show_result(CDataGroup *pDatas) //保留
{

}


void CSttAssistEngine::show_start_tip()
{
	//g_theAssistWndDynEffExecTool->ShowMsgEx("Assist", "测试助手，点击我获取测试帮助", 5000);
	g_theAssistWndDynEffExecTool->ShowMsgEx("Assist", g_sLangTxt_TestHelp.GetString(), 5000);
	//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttAssistEngine::show_start_tip : not implemented"));
}

void CSttAssistEngine::WidgetAdd(const CString &strWndID, QWidget *pWidget)
{
	int k = 0;
	STT_ASSISTWIGETSHOW_OBJ *p = NULL;

	for (k=0; k< STT_ASSISTWIGETSHOW_OBJ_COUNT; k++)
	{
		p = &m_arrWidgetShow[k];

		if (p->nUse == 0)
		{
			p->pWidget = pWidget;
			CString_to_char(strWndID, p->pszWndID);
			p->nUse = 1;
			break;
		}
	}
}

void CSttAssistEngine::WidgetRemove(const CString &strWndID)
{
	int k = 0;
	STT_ASSISTWIGETSHOW_OBJ *p = NULL;

	for (k=0; k< STT_ASSISTWIGETSHOW_OBJ_COUNT; k++)
	{
		p = &m_arrWidgetShow[k];

		if (p->nUse == 0)
		{
			continue;
		}

		if (strWndID == p->pszWndID)
		{
			p->nUse = 0;
		}
	}
}

void CSttAssistEngine::WidgetRemove(QWidget *pWidget)
{
	int k = 0;
	STT_ASSISTWIGETSHOW_OBJ *p = NULL;

	for (k=0; k< STT_ASSISTWIGETSHOW_OBJ_COUNT; k++)
	{
		p = &m_arrWidgetShow[k];

		if (p->nUse == 0)
		{
			continue;
		}

		if (p->pWidget == pWidget)
		{
			p->nUse = 0;
		}
	}
}

void CSttAssistEngine::WidgetRemove()
{
	int k = 0;
	STT_ASSISTWIGETSHOW_OBJ *p = NULL;

	for (k=0; k< STT_ASSISTWIGETSHOW_OBJ_COUNT; k++)//20221229 zhouhj 去除等于
	{
		p = &m_arrWidgetShow[k];

		if (p->nUse == 0)
		{
			continue;
		}

		if (! p->pWidget->isVisible())
		{//已经隐藏
			p->nUse = 0;
		}
	}
}

QWidget* CSttAssistEngine::assist_find_widget(const CString  &strWndIDPath)
{
	QObject *pFind = NULL;

	int k = 0;
	STT_ASSISTWIGETSHOW_OBJ *p = NULL;

	for (k=0; k< STT_ASSISTWIGETSHOW_OBJ_COUNT; k++)
	{
		p = &m_arrWidgetShow[k];

		if (p->nUse == 0)
		{
			continue;
		}

		pFind = qobj_findChild(p->pWidget, "QWidget", strWndIDPath);

		if (pFind != NULL)
		{
			return qobject_cast <QWidget*> (pFind);
		}
	}

	return NULL;
}

