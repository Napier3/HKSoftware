// DrawBinaryVariable.cpp: implementation of the CDrawBinaryVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawBinaryVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawBinaryVariable::CDrawBinaryVariable()
{
	InitAxisSet();
	m_nChanIndex = 0;
	m_pDrawStruct = NULL;
}

CDrawBinaryVariable::~CDrawBinaryVariable()
{
	m_pDrawStruct = NULL;
}

// LONG CDrawBinaryVariable::MouseMove(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::MouseMove(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawBinaryVariable::LButtonDown(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::LButtonDown(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawBinaryVariable::LButtonUp(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::LButtonUp(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawBinaryVariable::RButtonDown(UINT nFlags, CPoint &point)
// {
// 	return DRAW_NONE_OBJECT_SELECTED;
// }
// 
// LONG CDrawBinaryVariable::RButtonUp(UINT nFlags, CPoint &point)
// {
// 	return DRAW_NONE_OBJECT_SELECTED;
// }

BOOL CDrawBinaryVariable::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawBinaryVariable::Draw(CDC *pDC, ULONG nDrawStyle) 
{	
	if ((VARIABLE_DRAW_STYLE_NAME & nDrawStyle) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, nDrawStyle);
	}

	if ((VARIABLE_DRAW_STYLE_CENTER & nDrawStyle) == VARIABLE_DRAW_STYLE_CENTER)
	{
		CDrawVariable::Draw(pDC, nDrawStyle);
	}
	
	if ((VARIABLE_DRAW_STYLE_AXIS & nDrawStyle) == VARIABLE_DRAW_STYLE_AXIS)
	{
		pDC->MoveTo(m_rcAxis.right, m_rcBorder.top);
		pDC->LineTo(m_rcAxis.right, m_rcBorder.bottom);
	}

	if ((VARIABLE_DRAW_STYLE_AXIS & nDrawStyle) == VARIABLE_DRAW_STYLE_AXIS)
	{
		DrawBinary(pDC);
	}
}

void CDrawBinaryVariable::DrawBinary(CDC *pDC)
{
	long nPoints = m_pptAttachBuffer->GetCurrUseLength();

	if (m_pptAttachBuffer == NULL || m_pnAttachBuffer == NULL || nPoints <= 0)
	{
		return;
	}
	
	CRect rectBinary;
	long nChanIndex = m_nChanIndex % 16; 
	rectBinary.top = m_nYCenter - BINARY_HIGH_HEIGHT;
	rectBinary.bottom = m_nYCenter + BINARY_HIGH_HEIGHT + 1;
	rectBinary.left = m_rcAxis.right;
	rectBinary.right = m_rcBorder.right;
	long *pBuffer = m_pnAttachBuffer->GetBuffer();
	long *pEnd = NULL;
	long *pTemp = NULL;
	
	long nBuf1BeginPos = m_oBufferPos.nBuf1BeginPos;
	long nBuf1EndPos   = m_oBufferPos.nBuf1EndPos;		
	long nBuf2BeginPos = m_oBufferPos.nBuf2BeginPos;
	long nBuf2EndPos   = m_oBufferPos.nBuf2EndPos;
	long nGap		   = m_oBufferPos.nGap;
	CPoint *pPoint = m_pptAttachBuffer->GetBuffer();
	//绘制波形0线，和中心重合，但是可能不一样长
	CPen MyPen(PS_SOLID,1,m_crColor);
	CPen* pOldPen = pDC->SelectObject(&MyPen);
	long nLeft = pPoint->x;
	
	CPoint ptRight = *(pPoint + nPoints - 1);
	long nRight = ptRight.x;
	pDC->MoveTo(nLeft , m_nYCenter);
	pDC->LineTo(nRight , m_nYCenter);
	pDC->SelectObject(pOldPen);
	pOldPen = NULL;
	MyPen.DeleteObject();
	/////////////////////////////

	if (nBuf1BeginPos >= nBuf1EndPos || nBuf1BeginPos < 0)//没有数据时使用
	{		
		return;
	}
	
	pTemp = pBuffer + nBuf1BeginPos;
	pEnd  = pBuffer + nBuf1EndPos;
	BOOL bFlag = FALSE;
	
	while (pTemp <= pEnd)
	{
		if ( (( *pTemp >> nChanIndex) & 0x01) > 0)
		{
			if (bFlag)
			{		
				long nRight = pPoint->x;

				if (rectBinary.right <= nRight)
				{
					rectBinary.right = nRight;
				}
			}
			else
			{
				rectBinary.left = pPoint->x;
				rectBinary.right = pPoint->x;
				bFlag = TRUE;
			}
		}
		else
		{
			if (bFlag)
			{
				pDC->FillSolidRect(rectBinary,m_crColor);
				bFlag = FALSE;
			}
		}

		pPoint++;
		pTemp += nGap;
	}

	if (nBuf2BeginPos >= 0)
	{		
		long nOffset = 0;

		if (nGap == 1)
		{
			nOffset = 0;
		}
		else
		{
			nOffset = nGap - (nBuf1EndPos - nBuf1BeginPos + 1) % nGap ; // -1 
		}

		pTemp = pBuffer + nBuf2BeginPos + nOffset;
		pEnd  = pBuffer + nBuf2EndPos;
		
		while (pTemp <= pEnd)
		{
			if ((( *pTemp >> nChanIndex) & 0x01) > 0)
			{
				if (bFlag)
				{
				//	rectBinary.right = pPoint->x;

					long nRight = pPoint->x;
					
					if (rectBinary.right <= nRight)
					{
						rectBinary.right = nRight;
					}
				}
				else
				{
					rectBinary.left = pPoint->x;
					bFlag = TRUE;
				}
			}
			else
			{
				if (bFlag)
				{
					pDC->FillSolidRect(rectBinary,m_crColor);
					bFlag = FALSE;
				}
			}
			
			pPoint++;
			pTemp += nGap;
		}
	}


	if (bFlag)
	{
		pDC->FillSolidRect(rectBinary,m_crColor);
		bFlag = FALSE;
	}
}

void CDrawBinaryVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	m_oBufferPos = oBufPos;
}

void CDrawBinaryVariable::Move(long nHor, long nVer) 
{
	CDrawVariable::Move(nHor,nVer);	
}

void CDrawBinaryVariable::SetBorder(const CRect &rect, BOOL bSavePos)
{
	CDrawBase::SetBorder(rect);
	
	InitAxis(MrDraw::g_snNameandAxisRectWidth);
	
	if (bSavePos)
	{
		SetDrawRectRatio();
	}
}

void CDrawBinaryVariable::SetBorder(const CRect &rect)
{	
	CDrawVariable::SetBorder(rect);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);
}

void CDrawBinaryVariable::InitAxis(long nAxisRight)
{	
	CDrawVariable::InitAxis(MrDraw::g_snNameandAxisRectWidth);

	long nWidth = m_oRulerAxis.GetRulerHeight();//得到标尺的宽度
	
	m_rcAxis = m_rcBorder;
	m_rcAxis.right = nAxisRight;
	m_rcAxis.left  = nAxisRight - nWidth;
	
	SetNameRect(m_rcBorder.left, m_nYCenter - m_nTextHeight / 2, nAxisRight /*- nWidth*/, m_nYCenter + m_nTextHeight / 2);

	m_rcNameRectOrigin = m_rcName;
	m_rcDraw = m_rcBorder;
	m_rcDraw.left = nAxisRight;
}

void CDrawBinaryVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	CDrawVariable::ExpandBorder(l, t, r, b);
}
