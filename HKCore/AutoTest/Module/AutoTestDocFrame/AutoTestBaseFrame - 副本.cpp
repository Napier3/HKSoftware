// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoTestBaseFrame.h"

#include "AutoTestBaseTreeView.h"
#include "AutoTestBaseReportView.h"
#include "..\..\..\Module\DocFrameMngr\DocFrameMngr.h"

#include "..\UITestItem\ParaEdit\ItemParaEditDlg.h"
#include "..\UITestItem\ParaEdit\CommCmdParaEditDlg.h"
#include "..\SmartTestRpcEventApi.h"

#include "..\TestControl/AtsNewTestTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CAutoTestBaseFrame, CMDIChildWndEx)

CAutoTestBaseFrame::CAutoTestBaseFrame()
{
	m_pTestControl = NULL;
	m_pTreeView = NULL;
	m_pReportView = NULL;
	m_pMacroCharTestPaneRef = NULL;
	m_bTestControlRef = FALSE;
	m_pLogicView = NULL;
	m_wndSplitter = NULL;
}

CAutoTestBaseFrame::~CAutoTestBaseFrame()
{
	if (m_wndSplitter != NULL)
	{
		delete m_wndSplitter;
	}

	m_pTestControl = NULL;
}

CWnd* ats_CreateView(CRuntimeClass* pViewClass,CView* pOldView, UINT nViewID, CWnd *pParent, CSize sizeInit, CCreateContext* pContext)
{
	ASSERT(pViewClass != NULL);
	ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	ASSERT(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));

	BOOL bSendInitialUpdate = FALSE;

	CCreateContext contextT;
	
	if (pContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		if (pOldView != NULL && pOldView->IsKindOf(RUNTIME_CLASS(CView)))
		{
			// set info about last pane
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL)
				contextT.m_pNewDocTemplate =
				contextT.m_pCurrentDoc->GetDocTemplate();
		}
		pContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	CWnd* pWnd;
	
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE(traceAppMsg, 0, "Out of memory creating a splitter pane.\n");
		// Note: DELETE_EXCEPTION(e) not required
		return NULL;
	}
	END_CATCH_ALL

	ASSERT_KINDOF(CWnd, pWnd);
	ASSERT(pWnd->m_hWnd == NULL);       // not yet created

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW & ~WS_BORDER;

	// Create with the right size (wrong position)
	CRect rect(CPoint(0,0), sizeInit);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, pParent, nViewID, pContext))
	{
		TRACE(traceAppMsg, 0, "Warning: couldn't create client pane for splitter.\n");
		// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}

	// send initial notification message
	if (bSendInitialUpdate)
		pWnd->SendMessage(WM_INITIALUPDATE);

	return pWnd;
}

void CAutoTestBaseFrame::CreateClient(CTestControl *pTestControl, CDocTemplate* pNewDocTemplate, CDocument* pCurrentDoc, CRuntimeClass* pNewViewClass)
{
	if (!pTestControl->m_pGuideBook->HasLogic())
	{
		pCurrentDoc->UpdateAllViews(NULL, (LPARAM)pTestControl, NULL);
		return;
	}

	CCreateContext oContext;

	if (pNewViewClass != NULL)
	{
		oContext.m_pNewViewClass = pNewViewClass;
	}
	else
	{
		oContext.m_pNewViewClass = RUNTIME_CLASS(CAutoTestBaseTreeView);
	}

	oContext.m_pCurrentDoc = pCurrentDoc;
	oContext.m_pNewDocTemplate = pNewDocTemplate;
	
	CreateClient(&oContext);
	pCurrentDoc->UpdateAllViews(NULL, (LPARAM)pTestControl, NULL);
	RecalcLayout(TRUE);
}

void CAutoTestBaseFrame::CreateClient(CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);
	long nLeft = rect.Width()/3;

	if (nLeft > 350)
		nLeft = 350;

	long nRight = rect.Width() - nLeft;

	pContext->m_pCurrentDoc->DisconnectViews();

	m_wndSplitter->DestroyWindow();
	delete m_wndSplitter;
	m_wndSplitter = new CSplitterWnd();
	
	m_wndSplitter->CreateStatic(this,1,2);
	m_wndSplitter->CreateView(0,0,RUNTIME_CLASS(CAutoTestBaseTreeView),CSize(nLeft,rect.Height()),pContext);
	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CMFCTabCtrl),CSize(nRight, rect.Height()),pContext);

	m_pTreeView = (CAutoTestBaseTreeView*)m_wndSplitter->GetPane(0, 0);
	CMFCTabCtrl *pTab = (CMFCTabCtrl*)m_wndSplitter->GetPane(0, 1);

	CSize sz(nRight, rect.Height());

	m_pReportView = (CAutoTestBaseReportView*)ats_CreateView(RUNTIME_CLASS(CAutoTestBaseReportView)
		, m_pTreeView, 21046,pTab, sz, pContext);
	m_pLogicView = (CAutoTestBaseLogicView*)ats_CreateView(RUNTIME_CLASS(CAutoTestBaseLogicView)
		, m_pTreeView, 21047,pTab, sz, pContext);

	m_pReportView->SetParent(pTab);
	m_pLogicView->SetParentWnd(pTab);
	pTab->AddTab(m_pReportView, _T("报告视图"));
	pTab->AddTab(m_pLogicView, _T("逻辑视图"));

	m_pReportView->m_pTreeView = m_pTreeView;
	m_pTreeView->m_pReportView = m_pReportView;
	m_pTreeView->m_pLogicView = m_pLogicView;

	m_pTreeView->SendMessage(WM_INITIALUPDATE);
	m_pReportView->SendMessage(WM_INITIALUPDATE);
	m_pLogicView->SendMessage(WM_INITIALUPDATE);
}


BOOL CAutoTestBaseFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	//DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE;
	CRect rect;
	GetClientRect(&rect);
	long nLeft = rect.Width()/3;

	if (nLeft > 350)
		nLeft = 350;

	long nRight = rect.Width() - nLeft;

	m_wndSplitter = new CSplitterWnd();
	m_wndSplitter->CreateStatic(this,1,2);
	m_wndSplitter->CreateView(0,0,RUNTIME_CLASS(CAutoTestBaseTreeView),CSize(nLeft,rect.Height()),pContext);
	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CAutoTestBaseReportView),CSize(nRight, rect.Height()),pContext);

	m_pTreeView = NULL;
	m_pReportView = NULL;
	m_pTreeView = (CAutoTestBaseTreeView*)m_wndSplitter->GetPane(0, 0);
	m_pReportView = (CAutoTestBaseReportView*)m_wndSplitter->GetPane(0, 1);
	m_pTreeView->m_pReportView = m_pReportView;
	m_pReportView->m_pTreeView = m_pTreeView;

	return TRUE;
}

void CAutoTestBaseFrame::CreateView_Logic(CCreateContext* pContext, CRect rect, long nRight)
{
// 	m_wndSplitter->DeleteColumn(1);
// 	CSize szMin(0, 0);
// 	m_wndSplitter->CreateCommon(this, szMin,  WS_CHILD | WS_VISIBLE, 21045);
// 
// 	m_wndSplitter->CreateStatic(this,1,2);
// 	m_wndSplitter->CreateView(0,0,RUNTIME_CLASS(CAutoTestBaseTreeView),CSize(nLeft,rect.Height()),pContext);
// 	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CMFCTabCtrl),CSize(nRight, rect.Height()),pContext);
// 
// 	CMFCTabCtrl *pTab = (CMFCTabCtrl*)m_wndSplitter->GetPane(0, 1);
// 	m_pTreeView = (CAutoTestBaseTreeView*)m_wndSplitter->GetPane(0, 0);
// 
// 	CSize sz(nRight, rect.Height());
// 
// 	m_pReportView = (CAutoTestBaseReportView*)ats_CreateView(RUNTIME_CLASS(CAutoTestBaseReportView)
// 		, m_pTreeView, 21046,pTab, sz, pContext);
// 	m_pLogicView = (CAutoTestBaseLogicView*)ats_CreateView(RUNTIME_CLASS(CAutoTestBaseLogicView)
// 		, m_pTreeView, 21047,pTab, sz, pContext);
// 
// 	m_pReportView->SetParent(pTab);
// 	m_pLogicView->SetParentWnd(pTab);
// 	pTab->AddTab(m_pReportView, _T("报告视图"));
// 	pTab->AddTab(m_pLogicView, _T("逻辑视图"));
// 
// 	m_pReportView->m_pTreeView = m_pTreeView;
// 	m_pTreeView->m_pReportView = m_pReportView;
// 	m_pTreeView->m_pLogicView = m_pLogicView;
}

BEGIN_MESSAGE_MAP(CAutoTestBaseFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序

void CAutoTestBaseFrame::OnClose()
{
	if (!OnCloseAtsFrame())
	{
		return;
	}

// 	CString strMsg;
// 
// 	if (m_pTestControl == NULL)
// 	{
// 		strMsg.Format(_T("系统配置，不能关闭【%s】"), m_pTestControl->m_strName);
// 		MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONWARNING);
// 		return;
// 	}
// 
// 	strMsg.Format(_T("你确实要关闭【%s】吗？"), m_pTestControl->m_strName);
// 
// 	UINT nRet = MessageBox(strMsg, _T("提示"), MB_YESNO | MB_ICONQUESTION);
// 
// 	if (nRet == IDNO)
// 	{
// 		return;
// 	}

	CMDIChildWndEx::OnClose();
}

BOOL CAutoTestBaseFrame::CanCloseAtsFrame()
{
	if (m_pTestControl != NULL)
	{
		if(m_pTestControl->IsNowTesting())
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAts_AutoTest::g_sLangTxt_TestingClose/*L"正在测试中，不能关闭..."*/);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CAutoTestBaseFrame::OnCloseAtsFrame()
{
	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nUseSttAtsSvr == 1)
	{
		return FALSE;
	}

	if (!CanCloseAtsFrame())
	{
		return FALSE;
	}

	//引用，通过外部来关闭
	if (m_bTestControlRef)
	{
		AfxGetMainWnd()->PostMessage(WM_CLOSE_TEST_PROJECT, (WPARAM)m_pTestControl, 1);
		return FALSE;
	}

	m_pTreeView->CloseTestControl();

	if (m_pReportView != NULL)
	{
		m_pReportView->CloseTestControl();
	}

	if (m_pLogicView != NULL)
	{
		m_pLogicView->CloseTestControl();
	}

	CDocFrameMngr::CloseFrame(this);
	CloseAtsFrame();
	AfxGetMainWnd()->PostMessage(WM_CLOSE_TEST_PROJECT, 0, 1);

	//delete m_pTestControl;
	m_pTestControl = NULL;

	return TRUE;
}

BOOL CAutoTestBaseFrame::CloseAtsFrame()
{
	ASSERT (m_pTestControl != NULL);

	if (m_pTestControl->HasProject())
	{
		//保存系统测试报告，删除临时文件
		m_pTestControl->SaveBinaryFile();
		m_pTestControl->DeleteTempDirectorys();

		CTCtrlCntrWorkSpace::s_SetLastTestState(g_strNormal);
		CTCtrlCntrWorkSpace::s_SetCurrTestItemIndex(m_pTestControl->m_nCurrTestItemIndex);
		CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

		if (m_pTestControl->m_pReportFill != NULL)
		{
			m_pTestControl->m_pReportFill->Close(1);
		}
	}

	POS pos = CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.Find(m_pTestControl);

	if (pos != NULL)
	{
		CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.RemoveAt(pos);
	}

	m_pTreeView->CloseTestControl();

	if (m_pReportView != NULL)
	{
		m_pReportView->CloseTestControl();
	}
	

	return TRUE;
}

BOOL CAutoTestBaseFrame::CloseAtsFrameEx()
{
	CloseAtsFrame();
	CMDIChildWndEx::OnClose();

	return TRUE;
}

void CAutoTestBaseFrame::SelectTestItem(CExBaseObject *pItem)
{
	if (m_pTreeView != NULL)
	{
		m_pTreeView->SelectTestItem(pItem);
	}
}

//////////////////////////////////////////////////////////////////////////

//界面交互
long CAutoTestBaseFrame::OnException(long nError,const CString &strError)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, strError);

	return 0;
}

long CAutoTestBaseFrame::OnConnectSuccess()
{
	// 	if(m_pHarmToolDlg != NULL && m_pHarmToolDlg->IsWindowVisible())
	// 	{
	// 		m_pHarmToolDlg->m_ctrBtnStart.EnableWindow(TRUE);
	// 	}
	return 0;
}


void CAutoTestBaseFrame::ShowMacroCharTestPane(CGbItemBase *pGbItem)
{
	if (m_pMacroCharTestPaneRef == NULL)
	{
		return;
	}

	if (pGbItem == NULL)
	{
		m_pMacroCharTestPaneRef->ShowMacroCharTest(FALSE);
		return;
	}

	UINT nClassID = pGbItem->GetClassID();
	BOOL bCanShow = FALSE;

	if (nClassID == GBCLASSID_MACROTEST)
	{
		if (pGbItem->GetParent()->GetClassID() == GBCLASSID_MACROCHARITEMS)
		{
			bCanShow = TRUE;
		}
	}
	else if (nClassID == GBCLASSID_MACROCHARITEMS)
	{
		bCanShow = TRUE;
	}

	if (!bCanShow)
	{
		m_pMacroCharTestPaneRef->ShowMacroCharTest(FALSE);

		return;
	}

	m_pMacroCharTestPaneRef->ShowMacroCharTest(TRUE);

	if (nClassID == GBCLASSID_MACROCHARITEMS)
	{
		m_pMacroCharTestPaneRef->ShowMacroCharTest((CMacroCharItems*)pGbItem);
	}
	else
	{
		m_pMacroCharTestPaneRef->UpdateMacroCharTest((CMacroTest*)pGbItem);
	}
}


long CAutoTestBaseFrame::OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop)
{
	//特性曲线
	ShowMacroCharTestPane(pItem);

	m_pTreeView->OnCurrItemStateChanged(pItem, bBringToTop);

	if (m_pLogicView != NULL)
	{
		m_pLogicView->OnCurrItemStateChanged(pItem);
	}

	//shaolie  20210514
	//只有选中的项目，状态发生改变，才告知第三方程序
	if (pItem == NULL)
	{
		return 0;
	}

	if (pItem->m_nSelect)
	{
		atsrpc_OnTestItemStateChanged(pItem);
	}
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CAutoTestBaseFrame::OnCurrItemStateChanged>>>>%s>>>>%d"), pItem->m_strName, pItem->GetState());

	//shaolei 修改为状态为合格或者不合格，则更计算测试进度更准确  20210823
// 	if (nState == TEST_STATE_ELIGIBLE || nState == TEST_STATE_INLEGIBLE
	// 		|| nState == TEST_STATE_SKIP || nState == TEST_STATE_ELIGIBLEEX)

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strItemsCountMode == SMARTTEST_ITEM_COUNT_MODE_ALLITEMS)
	{
		if (pItem->GetClassID() == GBCLASSID_ITEMS)
		{
			return 0;
		}

		long nState = pItem->GetState();

	 		if (nState == TEST_STATE_ELIGIBLE || nState == TEST_STATE_INLEGIBLE
	 			|| nState == TEST_STATE_SKIP || nState == TEST_STATE_ELIGIBLEEX)
		{
			atsrpc_OnTestProcess(m_pTestControl);
		}
	}
	else
	{
// 		if (pItem->GetClassID() != GBCLASSID_ITEMS)
// 		{
// 			return 0;
// 		}
		//进入到此处的，都是测试小项
		CItems *pParentItems = Gb_GetFirstParentItems(pItem,TRUE);

		if (pParentItems == NULL)
		{
			//直接在CDevice下的测试小项，会返回为空
			return 0;
		}

		//CItems *p = (CItems *)pItem;

		if (!pParentItems->IsTypeRootNode())
		{
			return 0;
		}

		if (!Gb_IsItemsTestFinished(pParentItems))
		{
			return 0;
		}

		//略过子项目：子项目结束时，父项目已经结束，会导致发两次TestProcess
		if (pItem->m_bIsSubItem)
		{
			return 0;
		}

		long nState = pItem->GetState();

		if (nState == TEST_STATE_ELIGIBLE || nState == TEST_STATE_INLEGIBLE
			|| nState == TEST_STATE_SKIP || nState == TEST_STATE_ELIGIBLEEX)
		{
			//电气量项目需要考虑重复次数，全部测试完成，算测试结束
			if (pItem->GetClassID() == GBCLASSID_MACROTEST)
			{
				CMacroTest *pMacroTest = (CMacroTest *)pItem;

				if (!m_pTestControl->IsRepeatTimesFinished(pMacroTest))
				{
					return 0;
				}
			}
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++atsrpc_OnTestProcess++++++【%s】"), pParentItems->m_strName);
			atsrpc_OnTestItemStateChanged(pParentItems);
			atsrpc_OnTestProcess(m_pTestControl);
		}
	}

	return 0;
}

long CAutoTestBaseFrame::OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj)
{
	if (m_pMacroCharTestPaneRef == NULL)
	{
		return 0;
	}

	UINT nClassID = pItem->GetClassID();
	BOOL bCanShow = FALSE;
	CMacroCharItems *pMacroCharItems = NULL;
	CExBaseObject *pParent = NULL;

	if (nClassID == GBCLASSID_MACROTEST)
	{
		pParent = (CExBaseObject*)pItem->GetParent();

		if (pParent->GetClassID() == GBCLASSID_MACROCHARITEMS)
		{
			pMacroCharItems = (CMacroCharItems *)pParent;
		}
	}

	if (pMacroCharItems == NULL)
	{
		return 0;
	}

	CCharElementTestLine *pTestLine = NULL;

	if (pObj->GetClassID() == GBCLASSID_REPORT)
	{
		m_pMacroCharTestPaneRef->UpdateMacroTest((CMacroTest*)pItem,(CReport*)pObj);
	}
	else if (pObj->GetClassID() == DTMCLASSID_CVALUES)
	{
		m_pMacroCharTestPaneRef->UpdateMacroTest((CMacroTest*)pItem,(CValues*)pObj);
	}

	return 0;
}

long CAutoTestBaseFrame::OnStopTest(long nType)
{
	m_pTreeView->OnCurrItemStateChanged(NULL, FALSE);
	//AfxGetMainWnd()->PostMessage(WM_TEST_STOP, nType, nType);   //shaolei 2019.08.13
	AfxGetMainWnd()->SendMessage(WM_TEST_STOP, nType, nType);

	if (nType == 1)
	{
		atsrpc_OnTestFinished(m_pTestControl, nType);
	}
	else
	{
		atsrpc_OnTestError(m_pTestControl);
	}

	return 0;
}

long CAutoTestBaseFrame::OnUpdateMeasure(long nData)
{

	return 0;
}

BOOL CAutoTestBaseFrame::IsRunning(long nType)
{
	return FALSE;
}

long CAutoTestBaseFrame::HideAllTestItemUI(long nData)
{

	return 0;
}

HWND CAutoTestBaseFrame::GetFrameHwnd()
{
	return this->GetSafeHwnd();
}


void CAutoTestBaseFrame::ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate, BOOL bShow)
{
	LPARAM lParam = (bCreate << 16) + bShow;
	AfxGetMainWnd()->PostMessage(WM_TEST_SHOW_ITEM_REPORT, (WPARAM)pGbItem, lParam);
}

void CAutoTestBaseFrame::ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow)
{
	if (m_pMacroCharTestPaneRef == NULL)
	{
		return;
	}

	if (!bShow)
	{
		m_pMacroCharTestPaneRef->ShowMacroCharTest(FALSE);
		return;
	}

	m_pMacroCharTestPaneRef->ShowMacroCharTest(TRUE);
	m_pMacroCharTestPaneRef->ShowMacroCharTest((CMacroCharItems*)pGbItem);
}

void CAutoTestBaseFrame::LocateItemReport(CExBaseObject *pGbItem)
{
	m_pTestControl->LocateReport((CGbItemBase*)pGbItem, 0);
}



void CAutoTestBaseFrame::EditItemPara(CExBaseObject *pGbItem)
{
	UINT nClassID = pGbItem->GetClassID();

	if (nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmdParaEditDlg dlg;
		dlg.m_pCommCmd = (CCommCmd *)pGbItem;
		dlg.DoModal();
	}
	else if (nClassID == GBCLASSID_MACROTEST)
	{
		CItemParaEditDlg dlg;
		dlg.m_pItem = (CGbItemBase *)pGbItem;
		dlg.DoModal();
	}

}

long CAutoTestBaseFrame::OnTestBegin()
{
	//2021-8-6  lijunqing  立即调用
	atsrpc_OnTestStarted(m_pTestControl, _T(""));
	CWnd *pFrame = AfxGetMainWnd();
	pFrame->PostMessage(WM_TEST_BEGIN, 0, 0);

	return 0;
}

//shaolei 20220622 SV接收压板一致性测试，需要动态生成项目，需要删除或插入
void CAutoTestBaseFrame::InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if (m_pTreeView == NULL)
	{
		return;
	}

	m_pTreeView->InsertItem(pParentItem, pSubItem);
}

void CAutoTestBaseFrame::DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if (m_pTreeView == NULL)
	{
		return;
	}

	m_pTreeView->DeleteItem(pParentItem, pSubItem);
}