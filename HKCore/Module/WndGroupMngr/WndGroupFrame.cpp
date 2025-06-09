// ..\..\Module\WndGroupMngr\WndGroupFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "WndGroupFrame.h"

// CWndGroupFrame

IMPLEMENT_DYNAMIC(CWndGroupFrame, CStatic)

CWndGroupFrame::CWndGroupFrame()
{
	m_ptLeftTop.x = 0;
	m_ptLeftTop.y = 0;
	/*
	m_rcOrigin;
	m_rcFrame;
	*/

	m_crFrame = RGB(0, 0, 0);
	m_crBack = RGB(128, 0, 128);;
	m_crTitle = RGB(0, 0, 255);
	m_crTitleBack = RGB(0, 128, 128);

	m_rcButton = CRect(EXPAND_CLOSE_BUTTUON_GAP,EXPAND_CLOSE_BUTTUON_GAP
		, EXPAND_CLOSE_BUTTUON_GAP+EXPAND_CLOSE_BUTTUON_WIDTH,EXPAND_CLOSE_BUTTUON_GAP+EXPAND_CLOSE_BUTTUON_WIDTH);
	m_bExpand = TRUE;
	m_nFrameIndex = -1;

}

CWndGroupFrame::~CWndGroupFrame()
{
}


CRect CWndGroupFrame::GetFrameRect()
{
	if (m_bExpand)
	{
		return m_rcOrigin;
	}
	else
	{
		return m_rcFrame;
	}
}

long  CWndGroupFrame::GetFrameGap()
{
	return m_rcOrigin.bottom - m_rcFrame.bottom;
}

void CWndGroupFrame::Move(CRect rcWnd, BOOL bExpand)
{
	m_bExpand = bExpand;

	if (m_bExpand)
	{
		rcWnd.right = rcWnd.left + m_rcOrigin.Width();
		rcWnd.bottom = rcWnd.top + m_rcOrigin.Height();
	}
	else
	{
		rcWnd.right = rcWnd.left + m_rcFrame.Width();
		rcWnd.bottom = rcWnd.top + m_rcFrame.Height();
	}

	m_rcCurr = rcWnd;
	MoveWindow(rcWnd, TRUE);
}

CRect CWndGroupFrame::AdjustWndRect()
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CWnd *pWnd = GetParent();
	pWnd->ScreenToClient(&rcWnd);

	if (m_bExpand)
	{
		rcWnd.right = rcWnd.left + m_rcOrigin.Width();
		rcWnd.bottom = rcWnd.top + m_rcOrigin.Height();
	}
	else
	{
		rcWnd.right = rcWnd.left + m_rcFrame.Width();
		rcWnd.bottom = rcWnd.top + m_rcFrame.Height();
	}

	m_rcCurr = rcWnd;
	MoveWindow(rcWnd, TRUE);
	//Add By hqy
	Invalidate(FALSE);
	return m_rcCurr;
}

void CWndGroupFrame::InitAll()
{
	GetClientRect(&m_rcCurr);
	GetClientRect(&m_rcOrigin);
	GetClientRect(&m_rcFrame);
	m_rcFrame.bottom = m_rcButton.Height() + EXPAND_CLOSE_BUTTUON_GAP*4;

	m_ptFrameExpand[0].x = ROUND_GAP_X;
	m_ptFrameExpand[0].y = 0;

	m_ptFrameExpand[1].x = 0;
	m_ptFrameExpand[1].y = ROUND_GAP_X;

	m_ptFrameExpand[2].x = 0;
	m_ptFrameExpand[2].y = m_rcButton.bottom + EXPAND_CLOSE_BUTTUON_GAP - ROUND_GAP_X;

	m_ptFrameExpand[3].x = ROUND_GAP_X;
	m_ptFrameExpand[3].y = m_ptFrameExpand[2].y + ROUND_GAP_X;

	m_ptFrameExpand[4].x = m_rcButton.right+EXPAND_CLOSE_BUTTUON_GAP - ROUND_GAP_X;
	m_ptFrameExpand[4].y = m_ptFrameExpand[3].y;

	m_ptFrameExpand[5].x = m_rcButton.right+EXPAND_CLOSE_BUTTUON_GAP;
	m_ptFrameExpand[5].y = m_ptFrameExpand[4].y + ROUND_GAP_X;

	m_ptFrameExpand[6].x = m_rcButton.right+EXPAND_CLOSE_BUTTUON_GAP;
	m_ptFrameExpand[6].y = m_rcOrigin.bottom;

	m_ptFrameExpand[7].x = m_rcFrame.right;
	m_ptFrameExpand[7].y = m_rcOrigin.bottom;

	m_ptFrameExpand[8].x = m_rcFrame.right;
	m_ptFrameExpand[8].y = 0;

	m_ptFrameExpand[9] = m_ptFrameExpand[0];

	for (long nIndex = 0; nIndex<EXPAND_CLOSE_FRAME_POINTS; nIndex++)
	{
		m_ptFrameClosed[nIndex] = m_ptFrameExpand[nIndex];
	}

	m_ptFrameClosed[6].y = m_rcFrame.bottom;
	m_ptFrameClosed[7].y = m_rcFrame.bottom;	
}


BOOL CWndGroupFrame::UICreate(CRect rcBorder, CWnd *pParent, UINT nID)
{
	BOOL bState = FALSE;
	bState = Create(NULL,
		WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_BLACKFRAME,
		rcBorder,
		pParent,
		nID);

	if (!bState)
	{
		return FALSE;
	}

	ShowWindow(SW_SHOW);
	InitAll();

	return TRUE;
}


BEGIN_MESSAGE_MAP(CWndGroupFrame, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CWndGroupFrame 消息处理程序
extern void WINAPI DrawGradient(HDC pDC,const RECT& rect,COLORREF begin, COLORREF end, const int &width);

void CWndGroupFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//Modified by hqy 2010.7.8

	CDC Dc;
	CBitmap bmp;
	CRect rect;
	GetClientRect(rect);
	COLORREF bkColor = GetSysColor( COLOR_3DFACE ); 

	Dc.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	Dc.SelectObject(&bmp);
	GradientFill(&Dc,rect,RGB(255,255,255),bkColor/*RGB(192,193,200)*/,0);


	CPen pen(PS_SOLID, 1, RGB(192,192,192));
	CPen *pOldPen = dc.SelectObject(&pen);
	CBrush *pBrush = NULL;

	if (m_bExpand)
	{
		CBrush brushBk(m_crBack);
		pBrush = Dc.SelectObject(&brushBk);
		//dc.Polyline(m_ptFrameExpand, 10);
		Dc.SelectObject(pBrush);
		brushBk.DeleteObject();
	}

	CBrush brushTitleBk(m_crTitleBack);
	pBrush = Dc.SelectObject(&brushTitleBk);
	Dc.Polygon(m_ptFrameClosed, 10);

	Dc.SelectObject(pBrush);
	brushTitleBk.DeleteObject();

	{
		long nMode = Dc.SetBkMode(TRANSPARENT);
		COLORREF crText = Dc.SetTextColor(m_crTitle);
		CRect rc;
		rc.left = m_ptFrameClosed[6].x + EXPAND_CLOSE_BUTTUON_GAP;
		rc.top = EXPAND_CLOSE_BUTTUON_GAP;
		rc.right = m_ptFrameClosed[7].x - EXPAND_CLOSE_BUTTUON_GAP;
		rc.bottom = m_ptFrameClosed[7].y;

		LOGFONT  lf = InitLogFont();
		lf.lfHeight = 14;
		lf.lfWeight = 400;
		CFont font;
		font.CreateFontIndirect(&lf);
		CFont *pOldFont = Dc.SelectObject(&font);
		Dc.DrawText(m_strTitle, rc, DT_LEFT | DT_VCENTER);

		Dc.SetBkMode(nMode);
		Dc.SelectObject(pOldFont);
		font.DeleteObject();
		Dc.SetTextColor(crText);
		//dc.Rectangle(m_rcFrame);
	}

	Dc.SelectObject(pOldPen);
	pen.DeleteObject();

	long nGap1 = 1;
	long nGap2 = 3;
	Dc.Rectangle(m_rcButton);
	CPoint pt = m_rcButton.CenterPoint();
	Dc.MoveTo(pt.x - nGap2, pt.y);
	Dc.LineTo(pt.x + nGap2, pt.y);
	Dc.MoveTo(pt.x - nGap2, pt.y-nGap1);
	Dc.LineTo(pt.x + nGap2, pt.y-nGap1);

	if (!m_bExpand)
	{
		Dc.MoveTo(pt.x, pt.y - nGap2);
		Dc.LineTo(pt.x, pt.y + nGap2);
		Dc.MoveTo(pt.x-nGap1, pt.y-nGap2);
		Dc.LineTo(pt.x-nGap1, pt.y+nGap2);
	}

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&Dc,0,0,SRCCOPY);
	bmp.DeleteObject();
	Dc.DeleteDC();
}

void CWndGroupFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	AfxGetMainWnd()->ShowOwnedPopups(FALSE);

	if (m_rcButton.PtInRect(point))
	{
		m_bExpand = !m_bExpand;
		CWnd *pParent = GetParent();
		if (m_bExpand)
		{
			pParent->PostMessage(WM_FRAME_EXPAND, m_nFrameIndex, m_nFrameIndex);
		}
		else
		{
			pParent->PostMessage(WM_FRAME_CLOSED, m_nFrameIndex, m_nFrameIndex);
		}
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CWndGroupFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_bExpand = !m_bExpand;

	CWnd *pParent = GetParent();

	if (m_bExpand)
	{
		pParent->PostMessage(WM_FRAME_EXPAND, m_nFrameIndex, m_nFrameIndex);
	}
	else
	{
		pParent->PostMessage(WM_FRAME_CLOSED, m_nFrameIndex, m_nFrameIndex);
	}

	CStatic::OnLButtonDblClk(nFlags, point);
}

void CWndGroupFrame::Resize(CRect rect)
{
	MoveWindow(rect);
	InitAll();
}