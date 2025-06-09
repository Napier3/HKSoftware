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

CDrawBase::CDrawBase()
{
	m_nLineStyle = PS_SOLID;

#ifndef _XDRAW_USE_EXTERN_ATTR_
	m_nEnable = 1;
	m_nShow = 1;
	m_nShow = 1;
	m_nEnable = 1;
#endif

}

CDrawBase::~CDrawBase()
{
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

