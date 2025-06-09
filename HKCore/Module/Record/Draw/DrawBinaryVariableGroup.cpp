// DrawBinaryVariableGroup.cpp: implementation of the CDrawBinaryVariableGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawBinaryVariableGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawBinaryVariableGroup::CDrawBinaryVariableGroup()
{
	m_nYCenter = 0;
}

CDrawBinaryVariableGroup::~CDrawBinaryVariableGroup()
{
}

//继承的方法
LONG CDrawBinaryVariableGroup::MouseMove(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawBinaryVariableGroup::LButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawBinaryVariableGroup::LButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawBinaryVariableGroup::RButtonDown(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawBinaryVariableGroup::RButtonUp(UINT nFlags, CPoint &point)
{
	return DRAW_NONE_OBJECT_SELECTED;
}

BOOL CDrawBinaryVariableGroup::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawBinaryVariableGroup::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	CDrawVariable *pDraw = NULL;
	void *pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	//绘制通道
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->Draw(pDC);
	}
}

void CDrawBinaryVariableGroup::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	CDrawVariable *pDraw = NULL;
	void *pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	//获得位置索引
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->LogicPointToDevicePoint(dCoef,dOffset,oBufPos);
	}
}

void CDrawBinaryVariableGroup::Move(long nHor , long nVer ) 
{
}

void CDrawBinaryVariableGroup::SetBorder(const CRect &rect)
{
	CDrawBase::SetBorder(rect);
	CDrawBinaryVariable *pBinary = NULL;
	void *pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	CRect rcBorder = rect;
	m_nYCenter = (rect.bottom + rect.top) /2;
	//获得位置索引
	while (pos != NULL)
	{
		pBinary = (CDrawBinaryVariable*)GetNext(pos);
		UINT nChanIndex = pBinary->m_nChanIndex;
		rcBorder.bottom = rect.bottom - nChanIndex * (RECORDDRAW_BINARY_HEIGHT + 1);
		rcBorder.top    = rcBorder.bottom - RECORDDRAW_BINARY_HEIGHT ;
		pBinary->SetBorder(rcBorder);
	}
}
