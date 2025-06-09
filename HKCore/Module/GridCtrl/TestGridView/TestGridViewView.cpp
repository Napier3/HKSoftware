
// TestGridViewView.cpp : CTestGridViewView 类的实现
//

#include "stdafx.h"
#include "TestGridView.h"

#include "TestGridViewDoc.h"
#include "TestGridViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGridViewView

IMPLEMENT_DYNCREATE(CTestGridViewView, CView)

BEGIN_MESSAGE_MAP(CTestGridViewView, CView)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestGridViewView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CTestGridViewView 构造/析构

CTestGridViewView::CTestGridViewView()
{
	

}

CTestGridViewView::~CTestGridViewView()
{
}

BOOL CTestGridViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestGridViewView 绘制

void CTestGridViewView::OnDraw(CDC* pDC)
{
	CTestGridViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_gridex.IsGridCreated())
	{
		m_gridex.OnDraw(pDC);
	}
}


// CTestGridViewView 打印


LRESULT CTestGridViewView::OnSetFont(WPARAM hFont, LPARAM lParam)
{
	LRESULT result = Default();

	//m_gridex.OnSetFont(hFont, lParam);
	return result;
}

LRESULT CTestGridViewView::OnGetFont(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return 0;//(LRESULT) (HFONT) m_gridex.OnGetFont(0, 0);//m_Font;
}

void CTestGridViewView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTestGridViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestGridViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestGridViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTestGridViewView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestGridViewView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTestGridViewView 诊断

#ifdef _DEBUG
void CTestGridViewView::AssertValid() const
{
	CView::AssertValid();
}

void CTestGridViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestGridViewDoc* CTestGridViewView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestGridViewDoc)));
	return (CTestGridViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestGridViewView 消息处理程序

void CTestGridViewView::CreateGrid()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = 5;
	rcClient.top = 5;
	rcClient.right -= 5;
	rcClient.bottom -= 50;
	m_gridex.Create(this, CPoint(50, 20));
	m_gridex.InitGrid(20);
	//m_gridex.CreateTitleTip();
	m_gridex.InitData();
	m_gridex.SelectRow(4);	

	//m_gridex.SetFont(g_pGlobalFont14);
}


void CTestGridViewView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CreateGrid();
}

//////////////////////////////////////////////////////////////////////////

void CTestGridViewView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);

	m_gridex.OnLButtonUp(nFlags, point);
}

void CTestGridViewView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_gridex.OnLButtonDown(nFlags, point);
}

void CTestGridViewView::OnMouseMove(UINT nFlags, CPoint point)
{
	m_gridex.OnMouseMove(nFlags, point);
}

void CTestGridViewView::OnTimer(UINT nIDEvent)
{
	m_gridex.OnTimer(nIDEvent);
}

void CTestGridViewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_gridex.OnKeyDown(nChar, nRepCnt, nFlags))
	{

	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Instant editing of cells when keys are pressed
void CTestGridViewView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_gridex.OnChar(nChar, nRepCnt, nFlags))
	{
		return;
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CTestGridViewView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	m_gridex.OnLButtonDblClk(nFlags, point);

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CTestGridViewView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	m_gridex.OnRButtonDblClk(nFlags, point);

	CWnd::OnRButtonDblClk(nFlags, point);
}


void CTestGridViewView::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	m_gridex.OnKillFocus(pNewWnd);
}

void CTestGridViewView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_gridex.OnRButtonDown(nFlags, point);

	//CWnd::OnRButtonDown(nFlags, point);
}

