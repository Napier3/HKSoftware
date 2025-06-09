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

// AutoTestBaseLogicView.cpp : CAutoTestBaseLogicView 类的实现
//

#include "stdafx.h"
#include "AutoTestBaseFrame.h"
#include "AutoTestBaseLogicView.h"
#include "../TCtrlCntrDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestBaseLogicView

IMPLEMENT_DYNCREATE(CAutoTestBaseLogicView, CScrollView)

BEGIN_MESSAGE_MAP(CAutoTestBaseLogicView, CScrollView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CAutoTestBaseLogicView 构造/析构
void CAutoTestBaseLogicView::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
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

CAutoTestBaseLogicView::CAutoTestBaseLogicView()
{
	m_pTestControl = NULL;
	m_pVisioRptFill = NULL;
	m_pParentWnd = NULL;
}

CAutoTestBaseLogicView::~CAutoTestBaseLogicView()
{
	if (m_pVisioRptFill != NULL)
	{
		delete m_pVisioRptFill;
		m_pVisioRptFill = NULL;
	}
}

BOOL CAutoTestBaseLogicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CAutoTestBaseLogicView 绘制

void CAutoTestBaseLogicView::OnDraw(CDC* pDC)
{
	CAutoTestBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

// CAutoTestBaseLogicView 诊断

#ifdef _DEBUG
void CAutoTestBaseLogicView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAutoTestBaseLogicView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAutoTestBaseDoc* CAutoTestBaseLogicView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoTestBaseDoc)));
	return (CAutoTestBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoTestBaseLogicView 消息处理程序

void CAutoTestBaseLogicView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(100, 100);
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_pVisioRptFill = new CVisioLogicRptFill();
}

void CAutoTestBaseLogicView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	if(m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->AdjustReportWindowOnSize();
	}
}

void CAutoTestBaseLogicView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CAutoTestBaseLogicView::CreateTestControlView(CTestControl *pTestControl)
{
// 	//设置文档标题
// 	CAutoTestBaseDoc* pDoc = (CAutoTestBaseDoc*)GetDocument();
// 	CString strTitle = pDoc->GetTitle();
// 	strTitle = _T("逻辑图视图：") + strTitle;
// 	pDoc->SetTitle(strTitle);
	CString strFile;

	//此处打开逻辑图文件
	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->SetParentWnd(this);
		strFile = m_pVisioRptFill->GetVisioFilePath();

		if (strFile.GetLength() > 5)
		{
			m_pVisioRptFill->InitVisioRptFill();
			m_pVisioRptFill->OpenVisioFile();
			m_pVisioRptFill->AdjustVisioWindow();
		}
		else
		{
			CMFCTabCtrl *pTab = (CMFCTabCtrl *)m_pParentWnd;
			pTab->ShowTab(1, FALSE);
		}
	}
}

void CAutoTestBaseLogicView::CloseTestControl()
{
	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->CloseFile();
		m_pVisioRptFill->CloseApplication();
	}
}

void CAutoTestBaseLogicView::LocateVisio(CExBaseObject *pItem)
{
	if (m_pVisioRptFill == NULL)
	{
		return;
	}

	m_pVisioRptFill->LocateVisio(pItem);
}

void CAutoTestBaseLogicView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pTestControl = (CTestControl*)lHint;

	if (m_pTestControl == NULL)
	{
		return;
	}

	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->m_pTestControl = m_pTestControl;
	}

	CreateTestControlView(m_pTestControl);
}

BOOL CAutoTestBaseLogicView::OnEraseBkgnd(CDC* pDC)
{
	if (m_pTestControl == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);;
	}

	if (m_pVisioRptFill == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	return TRUE;
}

long CAutoTestBaseLogicView::OnCurrItemStateChanged(CGbItemBase* pItem)
{
	if (m_pVisioRptFill == NULL)
	{
		return 0;
	}

	if (pItem == NULL)
	{
		return 0;
	}

	long nState = pItem->GetState();

	//通过项目状态，判断项目是否测试结束
	if (nState == TEST_STATE_NORMAL || nState == TEST_STATE_TESTING || nState == TEST_STATE_COUNT
		|| nState == TEST_STATE_SKIP)
	{
		return 0;
	}

	//获取最近的CItems的m_strActLogic信息，该信息与逻辑图文件中的某一页面对应；
	CString strActLogic = pItem->GetActLogic_String();

	if (strActLogic.GetLength() <= 0)
	{
		return 0;
	}

	m_pVisioRptFill->OnItemTestFinished(pItem, strActLogic);

	return 0;
}