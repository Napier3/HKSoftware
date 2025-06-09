// DrawBase.cpp: implementation of the CDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoint CDrawBase::g_ptOrigin  = CPoint(0,0);
CPoint CDrawBase::g_ptCurrent = CPoint(0,0);
BOOL CDrawBase::g_bLButtonDown = FALSE;


CDrawBase::CDrawBase()
{
	m_rcBorder		= CRect(0,0,0,0);
	m_crColor		= RGB(0,0,0);;
	m_bSelect		= FALSE;
	m_nShow			= 1;
	m_strName		= "";
	m_strID			= "";
	m_pParentWnd	= NULL;	
	m_pParent		= NULL;
	m_nUse			= 0;
	m_nVariableIndex = -1;
}

CDrawBase::~CDrawBase()
{
}

void CDrawBase::Zoom(double dRate) 
{
}

void CDrawBase::Draw(CDC *pDC, ULONG nDrawStyle) 
{
}

void CDrawBase::ExpandBorder(long &l, long &t, long &r, long &b)
{
	m_rcBorder.InflateRect(l, t, r, b);
	
	long nTemp = 0;
	
	if (m_rcBorder.left > m_rcBorder.right)
	{
		nTemp = m_rcBorder.right;
		m_rcBorder.right = m_rcBorder.left;
		m_rcBorder.left = nTemp;
	}
	
	if (m_rcBorder.top > m_rcBorder.bottom)
	{
		nTemp = m_rcBorder.bottom;
		m_rcBorder.bottom = m_rcBorder.top;
		m_rcBorder.top = nTemp;
	}
}

void CDrawBase::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos)
{
}

LONG CDrawBase::MouseMove(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawBase::LButtonDown(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawBase::LButtonUp(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawBase::RButtonDown(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawBase::RButtonUp(UINT nFlags, CPoint &point)
{
	return 0;
}

