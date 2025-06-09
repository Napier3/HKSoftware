// XscdViewMain.cpp : 实现文件
//

#include "stdafx.h"
#include "XscdViewMain.h"


// CXscdViewMainBase

IMPLEMENT_DYNCREATE(CXscdViewMainBase, CScrollView)

CXscdViewMainBase::CXscdViewMainBase()
{
	m_pXScdDrawView = NULL;
	m_pXScdDataRef = NULL;
	m_bOnMouseDragViewState = FALSE;
}

CXscdViewMainBase::~CXscdViewMainBase()
{
}

void CXscdViewMainBase::ViewToWindow(CPoint &point)
{
	CPoint pt = GetScrollPosition();
	point -= pt;
}

void CXscdViewMainBase::WindowToView(CPoint &point)
{
	CPoint pt = GetScrollPosition();
	point += pt;
}

void CXscdViewMainBase::ViewToWindow(CRect &rect)
{
	CPoint pt = GetScrollPosition();
	rect.OffsetRect(-pt.x, -pt.y);
}

void CXscdViewMainBase::WindowToView(CRect &rect)
{
	CPoint pt = GetScrollPosition();
	rect.OffsetRect(pt.x, pt.y);
}

BOOL  CXscdViewMainBase::OnXScdElementRButtonDown(UINT nFlags, CPoint point)
{
	return FALSE;
}

BEGIN_MESSAGE_MAP(CXscdViewMainBase, CScrollView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
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

	ON_MESSAGE(WM_XSCDDRAW_DATACHANGED, OnXScdDrawChanged)
END_MESSAGE_MAP()


// CXscdViewMainBase 绘图
void CXscdViewMainBase::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}


BOOL CXscdViewMainBase::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CXscdViewMainBase::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CXscdViewMainBase::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CXscdViewMainBase::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	
	if (m_oMemDC->IsSizeChanged())
	{
		CRect rc(0, 0, m_pXScdDrawView->m_nWidth, m_pXScdDrawView->m_nHeight);
		m_oMemDC->Create(pDC, rc);
		CDC *pMemDC = m_oMemDC->GetDC();
		m_oMemDC->FillSolidRect(RGB(255, 255, 255));

		if (m_pXScdDataRef != NULL)
		{
			m_pXScdDrawView->Draw(pMemDC, 1, CPoint(0, 0), 0xFFFFFFFF);
		}
	}
	
	
	m_oMemDC->Draw(pDC);
	ASSERT (m_pXScdDrawView != NULL);

	m_pXScdDrawView->DrawActiveElement(pDC, 1, CPoint(0, 0));
}

BOOL CXscdViewMainBase::OnEraseBkgnd(CDC* pDC)
{
	return CScrollView::OnEraseBkgnd(pDC);
}


// CXscdViewMainBase 诊断

#ifdef _DEBUG
void CXscdViewMainBase::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CXscdViewMainBase::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CXscdViewMainBase 消息处理程序

int CXscdViewMainBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CXscdViewMainBase::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);


}

void CXscdViewMainBase::PostNcDestroy()
{

	CScrollView::PostNcDestroy();
}

void CXscdViewMainBase::OnDestroy()
{
	
	CScrollView::OnDestroy();
}
// 
// void CXscdViewMainBase::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
// {
// 	m_pIecCfgDatasMngr = NULL;
// 	CIecCfgFile *pIecfgFile = (CIecCfgFile*)lHint;
// 
// 	if (pIecfgFile == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pIecCfgDatasMngr = pIecfgFile->m_pIecCfgDatasMngr;
// 	m_pXScdDrawView->XCreateElement(m_pIecCfgDatasMngr, this);
// 	m_pXScdDrawView->AttachViewWindow(this);
// 	
// 	CSize sizeTotal;
// 	
// 	sizeTotal.cx = m_pXScdDrawView->m_nWidth;
// 	sizeTotal.cy = m_pXScdDrawView->m_nHeight;
// 
// 	SetScrollSizes(MM_TEXT, sizeTotal); 
// 	m_oMemDC->SetSizeChanged();
// 	SetFont(g_pGlobalFont11);
// }
// 

void CXscdViewMainBase::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rc;
	GetClientRect(rc);

	SCROLLINFO scrollInfo; 
	GetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
	switch   (nSBCode) 
	{ 
	case   SB_LINEUP: 
		scrollInfo.nPos -= 1; 
		if   (scrollInfo.nPos   <   scrollInfo.nMin) 
		{ 
			scrollInfo.nPos =   scrollInfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		ScrollWindow(0,   1); 
		break; 
	case   SB_LINEDOWN: 
		scrollInfo.nPos += 1; 
		if   (scrollInfo.nPos + rc.Height()   >   scrollInfo.nMax) 
		{ 
			scrollInfo.nPos =   scrollInfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		ScrollWindow(0,   -1); 
		break; 
	case   SB_TOP   : 
		ScrollWindow((scrollInfo.nPos   -   scrollInfo.nMin),   0); 
		scrollInfo.nPos =   scrollInfo.nMin; 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		break; 
	case   SB_BOTTOM: 
		ScrollWindow(-(scrollInfo.nMax   -   scrollInfo.nPos),   0); 
		scrollInfo.nPos =   scrollInfo.nMax; 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		break; 
	case   SB_PAGEUP: 
		scrollInfo.nPos -= 5; 
		if   (scrollInfo.nPos   <   scrollInfo.nMin) 
		{ 
			scrollInfo.nPos =   scrollInfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollInfo,SIF_ALL); 
		ScrollWindow(0,   5); 
		break; 
	case   SB_PAGEDOWN: 
		scrollInfo.nPos += 5; 
		if   (scrollInfo.nPos   >   scrollInfo.nMax) 
		{ 
			scrollInfo.nPos =   scrollInfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		ScrollWindow(0,   -5); 
		break; 
	case   SB_ENDSCROLL: 
		break; 
	case   SB_THUMBPOSITION: 
		break; 
	case   SB_THUMBTRACK: 
		ScrollWindow(0,   (scrollInfo.nPos   -   nPos)); 
		scrollInfo.nPos =   nPos; 
		SetScrollInfo(SB_VERT,   &scrollInfo,   SIF_ALL); 
		break; 
	} 

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CXscdViewMainBase::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetFont(g_pGlobalFont14);
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void CXscdViewMainBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bOnMouseDragViewState = FALSE;
	CScrollView::OnLButtonUp(nFlags, point);

	CPoint pt = GetScrollPosition();
	point += pt;
	m_pXScdDrawView->UI_OnLButtonUp(nFlags, point);
}

void CXscdViewMainBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bOnMouseDragViewState = FALSE;
	CPoint pt = GetScrollPosition();
	point += pt;

	if (m_pXScdDrawView->UI_OnLButtonDown(nFlags, point))
	{
		Invalidate(FALSE);
	}
}

void CXscdViewMainBase::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt = GetScrollPosition();
	pt += point;

	m_pXScdDrawView->UI_OnMouseMove(nFlags, pt);

	if (m_bOnMouseDragViewState)
	{
		CPoint ptPos = GetScrollPosition();
		ptPos.x += m_pointOrigin.x - point.x;
		ptPos.y += m_pointOrigin.y - point.y;

		CRect rc;
		GetClientRect(&rc);

		if (rc.Height() > m_pXScdDrawView->m_nHeight)
		{
			ptPos.y = 0;
		}
		else
		{
			if (ptPos.y + rc.Height() > m_pXScdDrawView->m_nHeight)
			{
				pt.y = m_pXScdDrawView->m_nHeight - rc.Height();
			}
		}

		m_pointOrigin = point;
		ScrollToPosition(ptPos);
		return;
	}
}

void CXscdViewMainBase::OnTimer(UINT nIDEvent)
{
	m_pXScdDrawView->UI_OnTimer(nIDEvent);
}

void CXscdViewMainBase::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_pXScdDrawView->UI_OnKeyDown(nChar, nRepCnt, nFlags))
	{

	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Instant editing of cells when keys are pressed
void CXscdViewMainBase::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_pXScdDrawView->UI_OnChar(nChar, nRepCnt, nFlags))
	{
		return;
	}

	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}

void CXscdViewMainBase::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CPoint pt = GetScrollPosition();
	point += pt;

	m_pXScdDrawView->UI_OnLButtonDblClk(nFlags, point);

	if (m_pXScdDrawView->m_pActiveElement != NULL)
	{
		OnXScdElementLDblClk(m_pXScdDrawView->m_pActiveElement);
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}


void CXscdViewMainBase::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	CPoint pt = GetScrollPosition();
	point += pt;

	m_pXScdDrawView->UI_OnRButtonDblClk(nFlags, point);

	CScrollView::OnRButtonDblClk(nFlags, point);
}


void CXscdViewMainBase::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);

	m_pXScdDrawView->UI_OnKillFocus(pNewWnd);
}

void CXscdViewMainBase::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (OnXScdElementRButtonDown(nFlags, point))
	{
		return;
	}
	else
	{
		m_pointOrigin = point;
		CPoint pt = GetScrollPosition();
		point += pt;

		m_pXScdDrawView->UI_OnRButtonDown(nFlags, point);
		m_bOnMouseDragViewState = TRUE;
	}

	//CScrollView::OnRButtonDown(nFlags, point);
}

void CXscdViewMainBase::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bOnMouseDragViewState = FALSE;
	CPoint pt = GetScrollPosition();
	point += pt;

	m_pXScdDrawView->UI_OnRButtonUp(nFlags, point);
}


LRESULT CXscdViewMainBase::OnSetFont(WPARAM hFont, LPARAM lParam)
{
	LRESULT result = Default();

	m_pXScdDrawView->UI_OnSetFont(hFont, lParam);
	return result;
}

LRESULT CXscdViewMainBase::OnGetFont(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return (LRESULT) (HFONT) m_pXScdDrawView->UI_OnGetFont(0, 0);//m_Font;
}

LRESULT CXscdViewMainBase::OnXScdDrawChanged(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	if (m_pXScdDataRef != NULL)
	{
		CDC *pMemDC = m_oMemDC->GetDC();
		m_oMemDC->FillSolidRect(RGB(255, 255, 255));
		m_pXScdDrawView->Draw(pMemDC, 1, CPoint(0, 0), 0xFFFFFFFF);
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//CXscdViewCfgMain
IMPLEMENT_DYNCREATE(CXscdViewCfgMain, CXscdViewMainBase)

CXscdViewCfgMain::CXscdViewCfgMain()
{
	m_pIecCfgDatasMngr = NULL;
	m_pXScdDrawView = &m_oXScdDrawViewCfg;
}

CXscdViewCfgMain::~CXscdViewCfgMain()
{
	m_pIecCfgDatasMngr = NULL;

}


void CXscdViewCfgMain::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pIecCfgDatasMngr = NULL;
	CIecCfgFile *pIecfgFile = (CIecCfgFile*)lHint;

	if (pIecfgFile == NULL)
	{
		return;
	}

	m_pIecCfgDatasMngr = pIecfgFile->m_pIecCfgDatasMngr;
		m_oXScdDrawViewCfg.XCreateElement(m_pIecCfgDatasMngr, this);
	m_pXScdDataRef = m_pIecCfgDatasMngr;
	m_oXScdDrawViewCfg.AttachViewWindow(this);

	CSize sizeTotal;

	sizeTotal.cx = m_oXScdDrawViewCfg.m_nWidth;
	sizeTotal.cy = m_oXScdDrawViewCfg.m_nHeight;

	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	SetFont(g_pGlobalFont11);
}


//////////////////////////////////////////////////////////////////////////
//CXscdViewThumbMain
IMPLEMENT_DYNCREATE(CXscdViewStationThumbMain, CXscdViewMainBase)

CXscdViewStationThumbMain::CXscdViewStationThumbMain()
{
	m_pXScdDrawView = &m_oXScdDrawViewThumbnail;
	m_pSclStation = NULL;
}

CXscdViewStationThumbMain::~CXscdViewStationThumbMain()
{
	
}

void CXscdViewStationThumbMain::CreateXscdViewThumbMain(CSclStation *pSclStation)
{
	m_pSclStation = pSclStation;
	m_pXScdDataRef = pSclStation;
	m_oXScdDrawViewThumbnail.XCreateElement(pSclStation,this);
}


//////////////////////////////////////////////////////////////////////////
//CXscdViewIedThumbMain
IMPLEMENT_DYNCREATE(CXscdViewIedThumbMain, CXscdViewMainBase)

CXscdViewIedThumbMain::CXscdViewIedThumbMain()
{
	m_pXScdDrawView = &m_oXScdDrawViewThumbnail;
	m_pXScdDrawIedThumb = NULL;
}

CXscdViewIedThumbMain::~CXscdViewIedThumbMain()
{
	
}

void CXscdViewIedThumbMain::CreateXscdViewThumbMain(CXScdDrawIedThumbnail *pXScdDrawIedThumb)
{
	m_pXScdDrawIedThumb = pXScdDrawIedThumb;
	m_pXScdDataRef = m_pXScdDrawIedThumb;
	m_oXScdDrawViewThumbnail.XCreateElement(pXScdDrawIedThumb,this);
}


//////////////////////////////////////////////////////////////////////////
//CXscdViewIedDetailMain
IMPLEMENT_DYNCREATE(CXscdViewIedDetailMain, CXscdViewMainBase)

CXscdViewIedDetailMain::CXscdViewIedDetailMain()
{
	m_pXScdDrawView = &m_oXScdDrawViewIedDetail;
	//m_pXScdDrawIedThumb = NULL;
}

CXscdViewIedDetailMain::~CXscdViewIedDetailMain()
{
	
}

void CXscdViewIedDetailMain::CreateXscdViewIedDetailMain(CXScdDrawLine_Ctrls *pXScdDrawLine_Ctrls)
{
	m_pXScdDataRef = pXScdDrawLine_Ctrls;
	m_oXScdDrawViewIedDetail.XCreateElement(pXScdDrawLine_Ctrls, this);
}
// 
// void CXscdViewIedDetailMain::CreateXscdViewThumbMain(CXScdDrawIedThumbnail *pXScdDrawIedThumb)
// {
// 	m_pXScdDrawIedThumb = pXScdDrawIedThumb;
// 	m_pXScdDataRef = m_pXScdDrawIedThumb;
// 	m_oXScdDrawViewThumbnail.XCreateElement(pXScdDrawIedThumb,this);
// }
// 
