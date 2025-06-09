// SplitterWndEx.cpp : 实现文件
//

#include "stdafx.h"
//#include "TestDialogSpliter.h"
#include "SplitterWndEx.h"


// CSplitterWndEx

IMPLEMENT_DYNAMIC(CSplitterWnd_Ex, CWnd)

CSplitterWnd_Ex::CSplitterWnd_Ex()
{

}

CSplitterWnd_Ex::~CSplitterWnd_Ex()
{
}

BEGIN_MESSAGE_MAP(CSplitterWnd_Ex, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CSplitterWndEx 消息处理程序

void CSplitterWnd_Ex::setSplitterGap(int nX,int nY)
{
	m_cxSplitterGap = nX;
	m_cySplitterGap = nY;
	/*m_cxSplitterGap = 0;
	m_cySplitterGap = 0;*/

	m_cxSplitter = nX;
	m_cySplitter = nY;
}

void CSplitterWnd_Ex::setBorder(int nX,int nY)
{
	m_cxBorder = nX;
	m_cyBorder = nY;
	m_cxBorderShare = nX;
	m_cyBorderShare = nY;
}

void CSplitterWnd_Ex::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	//CSplitterWnd::OnDrawSplitter(pDC,nType,rect);
	if(pDC == NULL)
	{
		return;
	}

	CRect rc = rect;
	switch(nType)
	{
	case splitBar:
		pDC->FillSolidRect(rc,RGB(242,248,248));
		//pDC->Draw3dRect(rc,RGB(255,0,0),RGB(255,0,0)); 
		break;  
	default:
		break;
	}
}


void CSplitterWnd_Ex::OnPaint()
{
	return CSplitterWnd::OnPaint();
}

BOOL CSplitterWnd_Ex::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return CSplitterWnd::OnSetCursor(pWnd,nHitTest,message);
}

void CSplitterWnd_Ex::OnMouseMove(UINT nFlags, CPoint pt)
{
	return CSplitterWnd::OnMouseMove(nFlags,pt);
}

void CSplitterWnd_Ex::OnLButtonDown(UINT nFlags, CPoint pt)
{
	return CSplitterWnd::OnLButtonDown(nFlags,pt);
}

void CSplitterWnd_Ex::OnLButtonUp(UINT nFlags, CPoint pt)
{
	return CSplitterWnd::OnLButtonUp(nFlags,pt);
}