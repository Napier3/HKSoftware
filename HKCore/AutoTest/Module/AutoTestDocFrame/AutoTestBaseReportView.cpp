// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// AutoTestBaseReportView.cpp : CAutoTestBaseReportView 类的实现
//

#include "stdafx.h"

#include "AutoTestBaseFrame.h"

#include "AutoTestBaseReportView.h"
#include "AutoTestBaseTreeView.h"

#include "../TCtrlCntrDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestBaseReportView

IMPLEMENT_DYNCREATE(CAutoTestBaseReportView, CScrollView)

BEGIN_MESSAGE_MAP(CAutoTestBaseReportView, CScrollView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CREATE_NEW_TEST_PROJECT,&CAutoTestBaseReportView::OnCreateNewTestProject)
	ON_MESSAGE(WM_ADJUSTVIEWSIZE,&CAutoTestBaseReportView::OnAdjustViewSize)
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CAutoTestBaseReportView 构造/析构
void CAutoTestBaseReportView::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMaxSize.x = 2000;  // 设置窗口最大化时的宽度
	lpMMI->ptMaxSize.y = 0x00FFFFFF;  // 设置窗口最大化时的高度
// 	lpMMI->ptMaxPosition.x = 100; // 设置窗口最大化时x坐标
// 	lpMMI->ptMaxPosition.y = 100; // 设置窗口最大化时y坐标
// 	lpMMI->ptMinTrackSize.x = 400; // 设置窗口最小宽度
// 	lpMMI->ptMinTrackSize.y = 400; // 设置窗口最小高度
// 	lpMMI->ptMaxTrackSize.x = 600; // 设置窗口最大宽度
// 	lpMMI->ptMaxTrackSize.y = 500; // 设置窗口最大高度

	CScrollView::OnGetMinMaxInfo(lpMMI);
}

CAutoTestBaseReportView::CAutoTestBaseReportView()
{
	m_nTestControlMode = TESTCONTROLMODE_NORMAL;
	m_pTestControl = NULL;
	m_pTreeView = NULL;
}

CAutoTestBaseReportView::~CAutoTestBaseReportView()
{
}

BOOL CAutoTestBaseReportView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CAutoTestBaseReportView 绘制

void CAutoTestBaseReportView::OnDraw(CDC* pDC)
{
	CAutoTestBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CAutoTestBaseReportView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAutoTestBaseReportView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CAutoTestBaseReportView 诊断

#ifdef _DEBUG
void CAutoTestBaseReportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAutoTestBaseReportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAutoTestBaseDoc* CAutoTestBaseReportView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoTestBaseDoc)));
	return (CAutoTestBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoTestBaseReportView 消息处理程序

void CAutoTestBaseReportView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(100, 100);
	SetScrollSizes(MM_TEXT, sizeTotal); 
	//OpenReportView();
}

void CAutoTestBaseReportView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	CRptFillInterface *pRptFillInterface = GetRptFillInterface();

	if(pRptFillInterface != NULL)
	{
		pRptFillInterface->AdjustReportWindowOnSize();
	}
}

void CAutoTestBaseReportView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

CRptFillInterface* CAutoTestBaseReportView::GetRptFillInterface()
{
	if (m_pTestControl != NULL)
	{
		return m_pTestControl->m_pReportFill;
	}
	else
	{
		return NULL;
	}
}

long CAutoTestBaseReportView::OpenReportView()
{
	if (m_pTestControl == NULL)
	{
		return 0;
	}

	if(!m_pTestControl->HasProject())
	{
		return 0;
	}

	//pFrame->m_bIsFirstFrame = TRUE;
	//pFrame->TraverseAllTestProjects();

	return 0;
}

LRESULT CAutoTestBaseReportView::OnCreateNewTestProject(WPARAM wParam,LPARAM lParam)
{
	CTestControl* pTestControl = (CTestControl*)wParam;

	if (pTestControl == NULL)
	{
		CloseTestControl();
		return 0;
	}
	
	m_nTestControlMode = pTestControl->GetTestControlMode();
	CreateTestControlView(pTestControl);

	return 0;
}

LRESULT CAutoTestBaseReportView::OnAdjustViewSize(WPARAM wParam,LPARAM lParam)
{
	CSystemRptFill *pSysRptFill = (CSystemRptFill*)wParam;
	CSize sizeTotal;
	sizeTotal.cx = pSysRptFill->GetWidth();
	sizeTotal.cy = pSysRptFill->GetHeight();

	if (lParam != 0)
	{
		SetScrollSizes(MM_TEXT, sizeTotal); 
		//SetScrollRange(SB_VERT, 0, sizeTotal.cx, TRUE);
		//SetScrollRange(SB_HORZ, 0, sizeTotal.cy, TRUE);
	}

	long nPos = pSysRptFill->GetCurrPos();
	CRect rcClient;
	GetClientRect(&rcClient);
	long nHeight = rcClient.Height();

	if (nHeight > sizeTotal.cy)
	{
		nPos = 0;
	}
	else
	{
		if (nPos + nHeight > sizeTotal.cy)
		{
			nPos = sizeTotal.cy - nHeight;
		}
	}

	ScrollToPosition(CPoint(0, nPos));

	return 0;
}

void CAutoTestBaseReportView::CreateTestControlView(CTestControl *pTestControl)
{
	//设置文档标题
	CAutoTestBaseDoc* pDoc = (CAutoTestBaseDoc*)GetDocument();

#if 0
	if(pDoc != NULL)
	{
		//ats_SetCocumentTitle(pTestControl->GetProjectName(), pDoc);//pDoc->SetTitle(pTestControl->GetProjectName());
	
		if (m_nTestControlMode == TESTCONTROLMODE_MDGBRPT
			|| m_nTestControlMode == TESTCONTROLMODE_SDVMPP)
		{
			CString strTitle = pDoc->GetTitle();
			strTitle = g_sLangTxt_MainView2/*_T("主视图:")*/ + strTitle;
			pDoc->SetTitle(strTitle);
		}
		else
		{

		}
	}
#endif

	CRptFillInterface *pRptFillInterface = GetRptFillInterface();

	if (pRptFillInterface != NULL)
	{
		pRptFillInterface->SetParentWnd(this);
	}

	pTestControl->OpenReportFile(this, TRUE);
	pTestControl->OpenAllBinaryTempFiles();
}


void CAutoTestBaseReportView::CloseTestControl()
{
	
}

void CAutoTestBaseReportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pTestControl = (CTestControl*)lHint;

	if (m_pTestControl == NULL)
	{
		return;
	}

	CreateTestControlView(m_pTestControl);
}

BOOL CAutoTestBaseReportView::OnEraseBkgnd(CDC* pDC)
{
	if (m_pTestControl == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);;
	}

	if (m_pTestControl->m_pReportFill == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	if (m_pTestControl->m_pReportFill->GetReportFillClassID() == REPORTFILL_PROGID_SYSTEM)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	return TRUE;//CScrollView::OnEraseBkgnd(pDC);
}
