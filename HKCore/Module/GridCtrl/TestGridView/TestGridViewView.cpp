
// TestGridViewView.cpp : CTestGridViewView ���ʵ��
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
	// ��׼��ӡ����
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

// CTestGridViewView ����/����

CTestGridViewView::CTestGridViewView()
{
	

}

CTestGridViewView::~CTestGridViewView()
{
}

BOOL CTestGridViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestGridViewView ����

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


// CTestGridViewView ��ӡ


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
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestGridViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestGridViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CTestGridViewView ���

#ifdef _DEBUG
void CTestGridViewView::AssertValid() const
{
	CView::AssertValid();
}

void CTestGridViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestGridViewDoc* CTestGridViewView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestGridViewDoc)));
	return (CTestGridViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestGridViewView ��Ϣ�������

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

