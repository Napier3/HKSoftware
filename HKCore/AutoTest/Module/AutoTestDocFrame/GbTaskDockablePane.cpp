// GbTaskDockablePane.cpp : 实现文件
//

#include "stdafx.h"
#include "GbTaskDockablePane.h"
#include "..\XLanguageResourceAts_AutoTest.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\Module\EpotoInterface\EpotoInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
BOOL CGbTaskToolBar::CreateToolBar(CWnd *pParentWnd)
{
	//Create(pParentWnd, AFX_DEFAULT_TOOLBAR_STYLE, m_nIDR_TESTTASK);
	BOOL bRet = CreateEx(pParentWnd, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC
		,CRect(1,1,1,1), ID_GBTASK_TOOLBAR);

	SetSizes(CSize(18, 18), CSize(16, 16));
	SetWindowText(g_sLangTxt_TestTaskBar);
	EnableDocking(CBRS_ALIGN_ANY);
	
	m_oImgToolBar.SetImageSize(CSize(16, 16));
	CString strPath;
	strPath = _P_GetResourcePath();
	strPath += _T("TestTaskToolBar.bmp");

	if (!m_oImgToolBar.Load(strPath))
	{
		return FALSE;
	}

	SetUserImages(&m_oImgToolBar);

	InsertButton(new CMFCToolBarButton(ID_TASK_OPEN_REPORT, 0,  g_sLangTxt_ToolTip_32781/*_T("打开报告\n打开报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_ADD_PROJECT, 1,  g_sLangTxt_ToolTip_32776/*_T("添加报告\n添加报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_DELETE_PROJECT, 2,  g_sLangTxt_ToolTip_32777/*_T("删除报告\n删除报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_CLEAR_FINISH_STATE, 3,  g_sLangTxt_ToolTip_32783/*_T("恢复到未完成状态\n恢复到未完成状态")*/, TRUE, -1));
	InsertSeparator(-1);
	InsertButton(new CMFCToolBarButton(ID_TASK_MOVEUP_PROJECT, 4,  g_sLangTxt_ToolTip_32778/*_T("上移报告\n上移报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_MOVEDOWN_PROJECT, 5,  g_sLangTxt_ToolTip_32779/*_T("下移报告\n下移报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_VIEW_PROJECT_TEMPLATE, 6,  g_sLangTxt_ToolTip_32784/*_T("显示报告对应的模板\n显示报告对应的模板")*/, TRUE, -1));
	InsertSeparator(-1);
	InsertButton(new CMFCToolBarButton(ID_TASK_EXPORT_REPORT, 7,  g_sLangTxt_ToolTip_32775/*_T("导出任务报告\n导出任务报告")*/, TRUE, -1));
	InsertButton(new CMFCToolBarButton(ID_TASK_STITCH_REPORT, 8,  g_sLangTxt_ToolTip_32789/*_T("拼接任务报告\n拼接任务报告")*/, TRUE, -1));
	InsertSeparator(-1);
	InsertButton(new CMFCToolBarButton(ID_TASK_EXIT, 9,  g_sLangTxt_ToolTip_32782/*_T("关闭任务\n关闭当前任务")*/, TRUE, -1));

	SetPaneStyle(GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	SetPaneStyle(GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	SetOwner(pParentWnd);
	SetRouteCommandsViaFrame(FALSE);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//

BEGIN_MESSAGE_MAP(CGBTaskTreeCtrl, CTreeCtrl)
	ON_COMMAND(WM_TESTPOINT,OnTestPoint)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


CGBTaskTreeCtrl::CGBTaskTreeCtrl()
{
	m_pTestTask = NULL;
}

CGBTaskTreeCtrl::~CGBTaskTreeCtrl()
{

}

void CGBTaskTreeCtrl::ShowTask(CTestTask* pTestTask)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_pTestTask = pTestTask;
	DeleteAllItems();

	if(m_pTestTask != NULL)
	{
		InsertToTreeCtrl(m_pTestTask,TVI_ROOT);
	}
}	

CTestProject* CGBTaskTreeCtrl::GetCurrSelProject()
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hItem);

	if (pSel == NULL)
	{
		return NULL;
	}

	if (pSel->GetClassID() == CLASSID_TESTPROJECT)
	{
		return (CTestProject*)pSel;
	}
	else
	{
		return NULL;
	}
}

void CGBTaskTreeCtrl::UpdateProject(CTestProject *pProject)
{
	UINT nBmpID = GetProjectBmpID(pProject);
	HTREEITEM hProject = (HTREEITEM)pProject->m_dwItemData;
	SetItemText(hProject, pProject->m_strName);
	SetItemImage(hProject, nBmpID, nBmpID);
}


BOOL CGBTaskTreeCtrl::ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2)
{
	if (p1 == NULL || p2 == NULL)
	{
		return FALSE;
	}

	if( p1->GetClassID() != CLASSID_TESTPROJECT || p2->GetClassID() != CLASSID_TESTPROJECT)
	{
		return FALSE;
	}

	CExBaseList* pParent = (CExBaseList*)p1->GetParent();
	HTREEITEM hItem = NULL;

	POS pos1 = pParent->Find(p1);
	POS pos2 = pParent->Find(p2);
	int nIndex1 = -1;
	int nIndex2 = -1;

	if(pos1 == NULL || pos2 == NULL)
	{
		return FALSE;
	}
	
	nIndex1 = pParent->FindIndex(pos1);
	nIndex2 = pParent->FindIndex(pos2);

	if(nIndex1 < 0 || nIndex2 < 0)
	{
		return FALSE;
	}

	if(nIndex1 > nIndex2)
	{
		this->DeleteItem((HTREEITEM)p2->m_dwItemData);
		InsertToTreeCtrl((CTestProject*)p2, TVI_ROOT, (HTREEITEM)p1->m_dwItemData);
	}
	else
	{
		this->DeleteItem((HTREEITEM)p1->m_dwItemData);
		InsertToTreeCtrl((CTestProject*)p1, TVI_ROOT, (HTREEITEM)p2->m_dwItemData);
	}

	return TRUE;
}

void CGBTaskTreeCtrl::AddErrTestItem(CExBaseObject *pItem)
{
	if (pItem == NULL)
	{
		return;
	}

	CTestProject *pProject = (CTestProject*)pItem->GetParent();
	InsertItem(pItem->m_strName, 4, 4, (HTREEITEM)pProject->m_dwItemData);
}

void CGBTaskTreeCtrl::RemoveErrTestItem(DWORD dwItem)
{
	DeleteItem((HTREEITEM)dwItem);
}

void CGBTaskTreeCtrl::AddProject(CTestProject *pProject)
{
	InsertToTreeCtrl(pProject, TVI_ROOT);
}

void CGBTaskTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	HTREEITEM hItem = HitTest(point);
	CTreeCtrl::OnRButtonDown(nFlags, point);

	if (hItem != NULL)
	{
		SelectItem(hItem);
		OnContextMenu(this, point);
	}
	//IDR_POPUP_TASK
}

//弹出菜单：测试菜单、查看报告菜单根据不同情况弹出
//李俊庆
void CGBTaskTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(m_pTestTask == NULL)
	{
		return;
	}

	HTREEITEM hItem = GetSelectedItem();
	CBaseObject *pObj = (CBaseObject*)GetItemData(hItem);

	if ( pObj == NULL)
	{
		return;
	}

	UINT nClassID = pObj->GetClassID();

	if (nClassID != CLASSID_TESTPROJECT)
	{
		return;
	}

	CMenu menu;		
	menu.CreatePopupMenu();

	// 添加菜单项
	xlang_AppendMenu(menu, ID_TASK_OPEN_REPORT,  g_sLangTxt_ToolTip_32781/*_T("打开报告\n打开报告")*/);
	xlang_AppendMenu(menu, ID_TASK_ADD_PROJECT,  g_sLangTxt_ToolTip_32776/*_T("添加报告\n添加报告")*/);
	xlang_AppendMenu(menu, ID_TASK_DELETE_PROJECT,  g_sLangTxt_ToolTip_32777/*_T("删除报告\n删除报告")*/);
	xlang_AppendMenu(menu, ID_TASK_CLEAR_FINISH_STATE,  g_sLangTxt_ToolTip_32783/*_T("恢复到未完成状态\n恢复到未完成状态")*/);
	menu.AppendMenu(MF_SEPARATOR);
	xlang_AppendMenu(menu, ID_TASK_MOVEUP_PROJECT,  g_sLangTxt_ToolTip_32778/*_T("上移报告\n上移报告")*/);
	xlang_AppendMenu(menu, ID_TASK_MOVEDOWN_PROJECT,  g_sLangTxt_ToolTip_32779/*_T("下移报告\n下移报告")*/);
	xlang_AppendMenu(menu, ID_TASK_VIEW_PROJECT_TEMPLATE,  g_sLangTxt_ToolTip_32784/*_T("显示报告对应的模板\n显示报告对应的模板")*/);
	menu.AppendMenu(MF_SEPARATOR);
	xlang_AppendMenu(menu, ID_TASK_EXPORT_REPORT,  g_sLangTxt_ToolTip_32775/*_T("导出任务报告\n导出任务报告")*/);
	xlang_AppendMenu(menu, ID_TASK_STITCH_REPORT,  g_sLangTxt_ToolTip_32789/*_T("拼接任务报告\n拼接任务报告")*/);
	menu.AppendMenu(MF_SEPARATOR);
	xlang_AppendMenu(menu, ID_TASK_EXIT,  g_sLangTxt_ToolTip_32782/*_T("关闭任务\n关闭当前任务")*/);

	//确定弹出式菜单的位置
	CWnd *pParent = GetParent();
	ClientToScreen(&point);
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pParent);			
	HMENU hmenu=menu.Detach();			
	menu.DestroyMenu();	
}

void CGBTaskTreeCtrl::InsertToTreeCtrl(CTestTask *pTask,HTREEITEM htiParent)
{
	m_pTestTask = pTask;
	ASSERT(m_pTestTask != NULL);

	POS pos = m_pTestTask->GetHeadPosition();
	CTestProject *pProject = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_pTestTask->GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			pProject = (CTestProject *)p;
			InsertToTreeCtrl(pProject, TVI_ROOT);
		}
	}
}

UINT CGBTaskTreeCtrl::GetProjectBmpID(CTestProject *pProject)
{
	UINT nBmpID = 0;

	if (pProject->IsTestState_Normal())
	{
		if (ATS_IsGuideBookReportFile(pProject->m_strName))
		{
			nBmpID = 1;
		}
		else
		{
			nBmpID = 0;
		}
	}
	else if (pProject->IsTestState_Finish())
	{
		nBmpID = 3;
	}
	else if (pProject->IsTestState_Testting())
	{
		nBmpID = 2;
	}

	return nBmpID;
}

void CGBTaskTreeCtrl::InsertToTreeCtrl(CTestProject *pProject,HTREEITEM htiParent, HTREEITEM hAfter)
{
	UINT nBmpID = GetProjectBmpID(pProject);
	HTREEITEM hProject = InsertItem(pProject->m_strName, nBmpID, nBmpID, htiParent, hAfter);
	POS pos = pProject->GetHeadPosition();
	CErrTestItemRef *pRef = NULL;
	SetItemData(hProject, (DWORD)pProject);
	pProject->m_dwItemData = (DWORD)hProject;

	while (pos != NULL)
	{
		pRef = (CErrTestItemRef *)pProject->GetNext(pos);
		InsertItem(pRef->m_strName, 4, 4, hProject);
	}

	Expand(hProject, TVE_EXPAND);
}

void CGBTaskTreeCtrl::OnTestPoint()
{
	
}

int CGBTaskTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CGBTaskTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point,&uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if(hItem != hItemSelected)
	{
		this->SelectItem(hItem);
	}

	CTreeCtrl::OnLButtonDblClk(nFlags, point);


}

//////////////////////////////////////////////////////////////////////////
// CGbTaskDockablePane

IMPLEMENT_DYNAMIC(CGbTaskDockablePane, CDockablePane)

CGbTaskDockablePane::CGbTaskDockablePane()
{
	m_pTestTask = NULL;
}

CGbTaskDockablePane::~CGbTaskDockablePane()
{
}


BEGIN_MESSAGE_MAP(CGbTaskDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TASK_EXPORT_REPORT, OnExportReport)
	ON_UPDATE_COMMAND_UI(ID_TASK_EXPORT_REPORT, OnUpdateExportReport)
	ON_COMMAND(ID_TASK_STITCH_REPORT, OnStitchReport)
	ON_UPDATE_COMMAND_UI(ID_TASK_STITCH_REPORT, OnUpdateStitchReport)
	ON_COMMAND(ID_TASK_OPEN_REPORT, OnOpenReport)
	ON_UPDATE_COMMAND_UI(ID_TASK_OPEN_REPORT, OnUpdateOpenReport)
	ON_COMMAND(ID_TASK_ADD_PROJECT, OnAddProject)
	ON_UPDATE_COMMAND_UI(ID_TASK_ADD_PROJECT, OnUpdateAddProject)
	ON_COMMAND(ID_TASK_DELETE_PROJECT, OnDeleteProject)
	ON_UPDATE_COMMAND_UI(ID_TASK_DELETE_PROJECT, OnUpdateDeleteProject)
	ON_COMMAND(ID_TASK_MOVEDOWN_PROJECT, OnMoveDownProject)
	ON_UPDATE_COMMAND_UI(ID_TASK_MOVEDOWN_PROJECT, OnUpdateMoveDownProject)
	ON_COMMAND(ID_TASK_MOVEUP_PROJECT, OnMoveUpProject)
	ON_UPDATE_COMMAND_UI(ID_TASK_MOVEUP_PROJECT, OnUpdateMoveUpProject)
	ON_COMMAND(ID_TASK_EXIT, OnExitTask)
	ON_UPDATE_COMMAND_UI(ID_TASK_EXIT, OnUpdateExitTask)
	ON_COMMAND(ID_TASK_CLEAR_FINISH_STATE, OnClearFinishState)
	ON_UPDATE_COMMAND_UI(ID_TASK_CLEAR_FINISH_STATE, OnUpdateClearFinishState)
	ON_COMMAND(ID_TASK_VIEW_PROJECT_TEMPLATE, OnViewProjectTemplate)
	ON_UPDATE_COMMAND_UI(ID_TASK_VIEW_PROJECT_TEMPLATE, OnUpdateViewProjectTemplate)
END_MESSAGE_MAP()



// CGbTaskDockablePane 消息处理程序
int CGbTaskDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	if (!m_GBTaskTree.Create(dwViewStyle, rectDummy, this, ID_GBTASK_TREECTRL))
	{
		TRACE0("未能创建XFile视图\n");
		return -1;      // 未能创建
	}
	
	m_GBTaskTree.SetFont(g_pGlobalFont12);

	{
		CString strFile;
		strFile = _P_GetResourcePath();
		strFile += _T("TestTaskTree.bmp");

		m_oImageList.LoadBmpFile(strFile, 5, RGB(255, 255, 255));
		m_GBTaskTree.SetImageList(&m_oImageList, TVSIL_NORMAL);
	}

	// 加载图像:
	ASSERT (AFX_DEFAULT_TOOLBAR_STYLE != 0);
	CreateToolBar();

	AdjustLayout();

	return 0;
}

void CGbTaskDockablePane::CreateToolBar()
{
	m_wndToolBar.CreateToolBar(this);

}

void CGbTaskDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
	//st_PostAdjustCfgMsg();
}

void CGbTaskDockablePane::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_GBTaskTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CGbTaskDockablePane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_GBTaskTree.SetFocus();
}

void CGbTaskDockablePane::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (m_GBTaskTree.GetSafeHwnd() == NULL)
	{
		return;
	}

	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_GBTaskTree.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);

}

void CGbTaskDockablePane::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{

}

void CGbTaskDockablePane::ShowTask(CTestTask *pTestTask, CXFolder *pFolder)
{
	m_GBTaskTree.ShowTask(pTestTask);

	m_pTestTask = pTestTask;
	m_pXFolder = pFolder;
}

void CGbTaskDockablePane::UpdateProject(CTestProject *pProject)
{
	m_GBTaskTree.UpdateProject(pProject);
}

void CGbTaskDockablePane::OnExportReport()
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	//m_pTestTask->ExportWordReport(pApp->GetWordApp());
	CRptFillWordApp *pWordApp = (CRptFillWordApp*)g_theRptFillApp;
	m_pTestTask->ExportWordReport(pWordApp->GetWordApp());
}

void CGbTaskDockablePane::OnUpdateExportReport(CCmdUI* pCmdUI)
{
	OnUpdateAddProject(pCmdUI);
}

void CGbTaskDockablePane::OnStitchReport()
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
/*	MSWord::_Application oWordApp = pApp->GetWordApp();
	m_pTestTask->StitchWordReport(NULL, oWordApp);
	pApp->CloseWordApplication();
*/
	if (g_theRptFillApp != NULL)
	{
//		m_pTestTask->StitchWordReport(NULL, oWordApp);	//待调yyj
		g_theRptFillApp->CloseApplication();
	}

	AfxMessageBox(g_sLangTxt_StitchRptFinish);
}

void CGbTaskDockablePane::OnUpdateStitchReport(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL bEnable = TRUE;

	//进行测试项目的测试
	if (m_pGbTaskOptrInerface == NULL)
	{
		bEnable = FALSE;
	}
	else
	{
		if (m_pGbTaskOptrInerface->IsTesting())
		{
			bEnable = FALSE;
		}
	}

	pCmdUI->Enable(bEnable);
}

void CGbTaskDockablePane::OnOpenReport()
{
	if (m_pTestTask == NULL)
	{
		return;
	}

	CXFolder *pFolder = m_pXFolder;
	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (m_pGbTaskOptrInerface->OpenReport(pProject, pFolder))
	{
		m_GBTaskTree.UpdateProject(pProject);
	}
}

void CGbTaskDockablePane::OnUpdateOpenReport(CCmdUI* pCmdUI)
{
	OnUpdateAddProject(pCmdUI);
}

void CGbTaskDockablePane::OnAddProject()
{
	if (m_pGbTaskOptrInerface == NULL)
	{
		return;
	}

	CString strTemplateFile;
	strTemplateFile = m_pGbTaskOptrInerface->AddProject();

	if (strTemplateFile.GetLength() <= 3)
	{
		return;
	}

	CTestProject *pProject = m_pTestTask->AddProject(strTemplateFile);

	if (pProject != NULL)
	{
		m_GBTaskTree.AddProject(pProject);
		m_pTestTask->Save(TRUE);
	}
}

void CGbTaskDockablePane::OnUpdateAddProject(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	
	BOOL bEnable = TRUE;

	if (m_pGbTaskOptrInerface == NULL)
	{
		bEnable = FALSE;
	}
	else
	{
		if (m_pGbTaskOptrInerface->IsTesting())
		{
			bEnable = FALSE;
		}
	}
	
	pCmdUI->Enable(bEnable);
}

void CGbTaskDockablePane::OnDeleteProject()
{
	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	CString strMsg;
	strMsg.Format(g_sLangTxt_SureToDele/*_T("你确实要删除【%s】吗？")*/, pProject->m_strName);

	if (MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}
	
	BOOL bTrue = FALSE;

	if (ATS_IsGuideBookReportFile(pProject->m_strName))
	{
		CXFile *pFile = (CXFile*)m_pXFolder->FindByName(pProject->m_strName);

		if (pFile != NULL && m_pGbTaskOptrInerface != NULL)
		{
			bTrue = m_pGbTaskOptrInerface->DeleteProject(pFile);
		}
	}

	if (bTrue)
	{
		m_GBTaskTree.DeleteItem((HTREEITEM)pProject->m_dwItemData);
		m_pTestTask->Delete(pProject);
		m_pTestTask->Save(TRUE);
	}
}

void CGbTaskDockablePane::OnUpdateDeleteProject(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
	}

	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (pProject == NULL)
	{
		pCmdUI->Enable(FALSE);
	}
	
	OnUpdateAddProject(pCmdUI);
}

void CGbTaskDockablePane::OnMoveDownProject()
{
	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();
	CTestProject *p2 = NULL;
	POS pos = m_pTestTask->Find(pProject);
	ASSERT (pos != NULL);
	m_pTestTask->GetNext(pos);
	p2 = (CTestProject*)m_pTestTask->GetAt(pos);
	ASSERT( p2 != NULL);

	m_GBTaskTree.ChangeTreePosition(p2, pProject);
	m_pTestTask->ChangePosition(p2, pProject);
	m_pTestTask->Save();
	m_GBTaskTree.SelectItem((HTREEITEM)pProject->m_dwItemData);
}

void CGbTaskDockablePane::OnUpdateMoveDownProject(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (pProject == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	POS pos = m_pTestTask->Find(pProject);

	if (pos == m_pTestTask->GetTailPosition())
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	
	OnUpdateAddProject(pCmdUI);
}

void CGbTaskDockablePane::OnMoveUpProject()
{
	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();
	CTestProject *p2 = NULL;
	POS pos = m_pTestTask->Find(pProject);
	ASSERT (pos != NULL);
	m_pTestTask->GetPrev(pos);
	p2 = (CTestProject*)m_pTestTask->GetAt(pos);
	ASSERT( p2 != NULL);

	m_GBTaskTree.ChangeTreePosition(p2, pProject);
	m_pTestTask->ChangePosition(p2, pProject);
	m_pTestTask->Save();
	m_GBTaskTree.SelectItem((HTREEITEM)pProject->m_dwItemData);
}

void CGbTaskDockablePane::OnUpdateMoveUpProject(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (pProject == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	POS pos = m_pTestTask->Find(pProject);

	if (pos == m_pTestTask->GetHeadPosition())
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	
	OnUpdateAddProject(pCmdUI);
}


void CGbTaskDockablePane::OnExitTask()
{
	m_GBTaskTree.ShowTask(NULL);
	m_pTestTask = NULL;
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	pApp->CloseTestTask();
	
	if (m_pGbTaskOptrInerface != NULL)
	{
		m_pGbTaskOptrInerface->ExitTask();
	}
}

void CGbTaskDockablePane::OnUpdateExitTask(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL bEnable = TRUE;

	//进行测试项目的测试
	if (m_pGbTaskOptrInerface == NULL)
	{
		bEnable = FALSE;
	}
	else
	{
		if (m_pGbTaskOptrInerface->IsTesting())
		{
			bEnable = FALSE;
		}
	}

	pCmdUI->Enable(bEnable);
}


void CGbTaskDockablePane::OnClearFinishState()
{
	CTestProject *pProject = NULL;
	POS pos = m_pTestTask->GetHeadPosition();

	while (pos != NULL)
	{
		pProject = (CTestProject *)m_pTestTask->GetNext(pos);
		pProject->SetTestState_Normal();
		m_GBTaskTree.UpdateProject(pProject);
	}

	m_pTestTask->Save(TRUE);
}

void CGbTaskDockablePane::OnUpdateClearFinishState(CCmdUI* pCmdUI)
{
	OnUpdateAddProject(pCmdUI);
}

void CGbTaskDockablePane::OnViewProjectTemplate()
{
	if (m_pTestTask == NULL)
	{
		return;
	}

	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (pProject == NULL)
	{
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ReportTestTempt/*_T("报告【%s】对应的测试模板:【%s】")*/
		, pProject->m_strName, pProject->tsk_GetPpxmlFile());
}

void CGbTaskDockablePane::OnUpdateViewProjectTemplate(CCmdUI* pCmdUI)
{
	if (m_pTestTask == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CTestProject *pProject = m_GBTaskTree.GetCurrSelProject();

	if (pProject == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	OnUpdateAddProject(pCmdUI);
}
