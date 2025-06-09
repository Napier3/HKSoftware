#include "stdafx.h"
#include "SttAssistWndDynEffExecTool.h"

#include "SttAssistWndFlash.h"
#include "QSttAssistMsgWidget.h"
#include "../../UI/SttStyleSheetGlobalDefine.h"


#include "../SttAssistEngine.h"
#define TimerDynEffct_Long 1000

//测试用样式，实际样式在TestCntrlFrameConfig.xml中定义
// QString g_strFlashStyle1 =  "background-color:rgb(192,192,192); color:rgb(0,0,0); border-radius:1px; border-style:outset;";
// QString g_strFlashStyle2 =  "background-color:rgb(255,192,203); color:rgb(0,0,0); border-radius:10px; border:3px rgb(255,0,0);border-style:outset; ";

CSttAssistWndDynEffExecTool::CSttAssistWndDynEffExecTool()
{
	memset(m_arrAstWndDynEff, 0, sizeof(STTASSITWNDEFFECT_OBJ) * MAX_COUNT_WndDynEffect);
	connect(&m_oTimerDynEffct,   SIGNAL(timeout()),    this,   SLOT(slot_Timer_DynEffect()));
	connect(this, SIGNAL(sig_ShowMsgEx(QString,QString,long)), this, SLOT(slot_ShowMsgEx(QString,QString,long)),Qt::QueuedConnection);
	m_oTimerDynEffct.start(TimerDynEffct_Long);
}

CSttAssistWndDynEffExecTool::~CSttAssistWndDynEffExecTool()
{
	m_oTimerDynEffct.stop();
}

void CSttAssistWndDynEffExecTool::slot_Timer_DynEffect()
{
	int k = 0;
	STTASSITWNDEFFECT_OBJ *p = NULL;

	for (k=0; k<= MAX_COUNT_WndDynEffect; k++)
	{
		p = &m_arrAstWndDynEff[k];

		if (p->nUse != 1)
		{
			continue;
		}

		if (p->pWndDynEffect == NULL)
		{
			p->nUse = 0;
			continue;
		}

		if (p->pWndDynEffect->m_bIsStoped)
		{
			p->pWndDynEffect->ast_Stop();
			delete p->pWndDynEffect;
			p->pWndDynEffect = NULL;
			p->nUse = 0;
		}
		else
		{
			p->pWndDynEffect->ast_Exec(TimerDynEffct_Long);
		}
	}

	CSttAssistWndFlash::AfterExec();
}

//添加动态对象
void CSttAssistWndDynEffExecTool::Add(CSttAssistWndDynEffectBase *pWndDynEffect)
{
	int k = 0;
	STTASSITWNDEFFECT_OBJ *p = NULL;

	for (k=0; k<= MAX_COUNT_WndDynEffect; k++)
	{
		p = &m_arrAstWndDynEff[k];

		if (p->nUse == 0)
		{
			p->pWndDynEffect = pWndDynEffect;
			p->nUse = 1;
			break;
		}
	}
}

//停止动态对象，从工具中清除对象
void CSttAssistWndDynEffExecTool::Stop(const CString  &strWndID)
{
	int k = 0;
	STTASSITWNDEFFECT_OBJ *p = NULL;

	for (k=0; k<= MAX_COUNT_WndDynEffect; k++)
	{
		p = &m_arrAstWndDynEff[k];

		if (p->nUse != 1)
		{
			continue;
		}

		if (p->pWndDynEffect == NULL)
		{
			continue;
		}
		
		if (p->pWndDynEffect->m_strWndID == strWndID)
		{
			p->pWndDynEffect->ast_Stop();
		}
	}
}


//暂时只从g_theTestCntrFrame获取窗口，后续需要根据Engine的窗口层级关系获取
QWidget* assist_find_widget_tool_btn(const CString  &strWndIDPath)
{
	CSttFrame_Button *pBtnAssist = g_theTestCntrFrame->m_pSttFrameConfig->FindBtnByID(strWndIDPath);

	if (pBtnAssist != NULL)
	{
		return (QSttToolButtonBase*)pBtnAssist->m_dwItemData;
	}
	else
	{
		return NULL;
	}
}

QWidget* assist_find_widget(const CString  &strWndIDPath)
{
	QWidget *pFind = assist_find_widget_tool_btn(strWndIDPath);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = g_theAssistEngine->assist_find_widget(strWndIDPath);

	return pFind;
}

bool assist_get_widget_msg_pos(const CString &strWndIdPath, QRect &rcWnd)
{
	QWidget *pFind = assist_find_widget(strWndIdPath);

	if (pFind == NULL)
	{
		//没有找到窗口，则使用状态来顶部的一块区域
		QRect rc = g_theTestCntrFrame->m_pStatusBar->geometry();
		rcWnd.setRight(rc.right());
		rcWnd.setBottom(rc.top());
		rcWnd.setTop(rc.top() - 20);
		rcWnd.setLeft(rc.width() - 50);

		return false;
	}

	QRect rc = pFind->geometry();
	QPoint ptGlobal(pFind->mapToGlobal(QPoint(0,0)));
	rcWnd.setLeft(ptGlobal.x());
	rcWnd.setTop(ptGlobal.y());
	rcWnd.setWidth(rc.width());
	rcWnd.setHeight(rc.height());

	return true;
}

//闪烁子窗口
void CSttAssistWndDynEffExecTool::Flash(const CString  &strWndIDPath, const CString  &strStyle1, const CString  &strStyle2, long nTimeLong)
{
	QWidget *pFind = assist_find_widget(strWndIDPath);

	if (pFind == NULL)
	{
		return;
	}

	CSttAssistWndFlash *pFlash = new CSttAssistWndFlash();
	pFlash->m_strWndID = strWndIDPath;
	pFlash->m_pCurrWnd = pFind;
	pFlash->m_strStyle1 = STT_StyleSheet_AssistFlashStyle1;
	pFlash->m_strStyle2 = STT_StyleSheet_AssistFlashStyle2;
	pFlash->m_strStyleBack = pFind->styleSheet();
	pFlash->m_nTimeLong = nTimeLong;
	Add(pFlash);
}

void CSttAssistWndDynEffExecTool::ShowMsg(const CString &strMsg, long nShowTimeLong)
{
	ShowMsgEx("", strMsg, nShowTimeLong);
}

void CSttAssistWndDynEffExecTool::ShowMsgEx(const CString &strWndID, const CString &strMsg, long nShowTimeLong)
{
	emit sig_ShowMsgEx(strWndID,strMsg,nShowTimeLong);
}

void CSttAssistWndDynEffExecTool::slot_ShowMsgEx(QString strWndID, QString strMsg, long nShowTimeLong)
{
	QSttAssistMsgWidget *pNew = new QSttAssistMsgWidget();
	pNew->ShowMsgEx(strWndID, strMsg, nShowTimeLong);
	pNew->m_strWndID = strWndID;
	Add(pNew);
}