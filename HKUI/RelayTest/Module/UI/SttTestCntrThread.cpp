#include "SttTestCntrThread.h"
#include "SttTestCntrFrameBase.h"


QSttTestCntrThread *g_theSttTestCntrThread = NULL;

void CreateSttTestCntrThread()
{
	g_theSttTestCntrThread = new QSttTestCntrThread();
	g_theSttTestCntrThread->ResumeThread();
}

void ReleaseSttTestCntrThread()
{
	g_theSttTestCntrThread->WaitThreadExit();
}


QSttTestCntrThread::QSttTestCntrThread()
{
	g_theSttTestCntrThread = this;
	m_pParentItems = NULL;
}

QSttTestCntrThread::~QSttTestCntrThread()
{
	
}

#include "Manual/SttMacroParaEditViewManual.h"
#include "State/SttMacroParaEditViewState.h"
#include "Harm/SttMacroParaEditViewHarm.h"
#include "Gradient/SttMacroParaEditViewGradient.h"
#include "TransPlay/SttMacroParaEditViewTransPlay.h"
#include "Webkit/SttMacroParaEditViewHtml.h"
#include "State/GooseAbnormal/SttMacroParaEditViewGooseAbnormal.h"

void QSttTestCntrThread::OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	if (nMsgID == 1)
	{
 		QSttWebViewBase *pWebView = (QSttWebViewBase*)wParam;
 		pWebView->OnHtmlLoadFinish(true);
	}
	else if (nMsgID == 2)
	{
		QSttMacroParaEditViewState *pSttMacroParaEditViewState = (QSttMacroParaEditViewState*)wParam;
		pSttMacroParaEditViewState->initUI_Paras(false);
	}
	else if (nMsgID == 3)
	{
		QSttMacroParaEditViewState *pSttMacroParaEditViewState = (QSttMacroParaEditViewState*)wParam;
		pSttMacroParaEditViewState->initUI_Paras(true);
	}
	else if (nMsgID == 4)
	{
		QSttMacroParaEditViewGooseAbnormal *pSttMacroParaEditViewGooseAbnormal = (QSttMacroParaEditViewGooseAbnormal*)wParam;
		pSttMacroParaEditViewGooseAbnormal->initUI_Paras(false,false);
	}
	else if (nMsgID == 9)
	{
		g_theTestCntrFrame->OpenMacroTestUI(g_pTheSttTestApp->m_pTestMacroUI, "", "");
	}
	else if (nMsgID == 10)
	{
		g_theTestCntrFrame->GenerateTemplate(m_pParentItems, m_strItemsName, m_strItemsID);
	}
	else if (nMsgID == 11)
	{
		CSttMacroParaEditInterface *pMacroEditView = (CSttMacroParaEditInterface*)wParam;//g_theTestCntrFrame->GetMacroEditView();
		pMacroEditView->InitSpyToolWidget();
	}
	else if (nMsgID == 12)
	{
		g_theTestCntrFrame->UpdateRptHtml();
	}
}
