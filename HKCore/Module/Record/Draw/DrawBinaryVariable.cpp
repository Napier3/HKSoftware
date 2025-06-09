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

void CDrawBinaryVariable::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
{	
// 	if ((VARIABLE_DRAW_STYLE_NAME & dwDrawFlag) == VARIABLE_DRAW_STYLE_NAME)
// 	{
// 		CDrawVariable::Draw(pDC, dwDrawFlag);
// 	}
// 
// 	if ((VARIABLE_DRAW_STYLE_CENTER & dwDrawFlag) == VARIABLE_DRAW_STYLE_CENTER)
// 	{
// 		CDrawVariable::Draw(pDC, dwDrawFlag);
// 	}
// 	
// 	if ((VARIABLE_DRAW_STYLE_AXIS & dwDrawFlag) == VARIABLE_DRAW_STYLE_AXIS)
// 	{
// 		pDC->MoveTo(m_rcAxis.right, m_rcBorder.top);
// 		pDC->LineTo(m_rcAxis.right, m_rcBorder.bottom);
// 	}
// 
// 	if ((VARIABLE_DRAW_STYLE_WAVE & dwDrawFlag) == VARIABLE_DRAW_STYLE_WAVE)
// 	{
// 		DrawBinary(pDC);
// 	}


	if ((VARIABLE_DRAW_STYLE_NAME & dwDrawFlag) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}

	if ((VARIABLE_DRAW_STYLE_CENTER & dwDrawFlag) == VARIABLE_DRAW_STYLE_CENTER)
	{
		CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
	
	if ((VARIABLE_DRAW_STYLE_AXIS & dwDrawFlag) == VARIABLE_DRAW_STYLE_AXIS)
	{
		pDC->MoveTo(m_rcAxis.right, m_ptTopLeft.x);//m_rcBorder.top);
		pDC->LineTo(m_rcAxis.right, Bottom());//m_rcBorder.bottom);
	}

	if ((VARIABLE_DRAW_STYLE_WAVE & dwDrawFlag) == VARIABLE_DRAW_STYLE_WAVE)
	{
		DrawBinary(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}

}

void CDrawBinaryVariable::DrawBinary(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	long nPoints = m_pptAttachDrawBuffer->GetCurrUseLength();

	if (m_pptAttachDrawBuffer == NULL || m_pnAttachBuffer == NULL || nPoints <= 0)
	{
		return;
	}
	
	CRect rectBinary;
	long nChanIndex = m_nChanIndex % 16; 
	rectBinary.top = m_nYCenter - RECORDDRAW_BINARY_HIGH;
	rectBinary.bottom = m_nYCenter + RECORDDRAW_BINARY_HIGH + 1;
	rectBinary.left = m_rcAxis.right;
	rectBinary.right = Right();//m_rcBorder.right;
	WORD *pBuffer = m_pnAttachBuffer->GetBuffer();
	WORD *pEnd = NULL;
	WORD *pTemp = NULL;

	if (pBuffer == NULL)
	{
		return;
	}
	
	long nBuf1BeginPos = m_oBufferPos.nBuf1BeginPos;
	long nBuf1EndPos   = m_oBufferPos.nBuf1EndPos;		
	long nBuf2BeginPos = m_oBufferPos.nBuf2BeginPos;
	long nBuf2EndPos   = m_oBufferPos.nBuf2EndPos;
	long nGap		   = m_oBufferPos.nGap;
	CPoint *pPoint = m_pptAttachDrawBuffer->GetBuffer();
	//绘制波形0线，和中心重合，但是可能不一样长
	CPen MyPen(PS_SOLID,1,m_crForeColor);
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
				pDC->FillSolidRect(rectBinary,m_crForeColor);
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
			if ( (( *pTemp >> nChanIndex) & 0x01) > 0)
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
					pDC->FillSolidRect(rectBinary,m_crForeColor);
					bFlag = FALSE;
				}
			}
			
			pPoint++;
			pTemp += nGap;
		}
	}


	if (bFlag)
	{
		pDC->FillSolidRect(rectBinary,m_crForeColor);
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

// void CDrawBinaryVariable::SetBorder(const CRect &rect, BOOL bSavePos)
// {
// 	CDrawBase::SetBorder(rect);
// 	
// 	InitAxis(MrDraw::g_snNameandAxisRectWidth);
// 	
// 	if (bSavePos)
// 	{
// 		SetDrawRectRatio();
// 	}
// }
// 

void CDrawBinaryVariable::SetBorder(const CRect &rect)
{	
	CDrawVariable::SetBorder(rect);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);
}

void CDrawBinaryVariable::InitAxis(long nAxisRight)
{	
	long nWidth = m_pRulerAxis->GetRulerHeight();//得到标尺的宽度
	m_nYCenter = m_ptTopLeft.x + m_nHeight / 2;//(m_rcBorder.top + m_rcBorder.bottom) / 2;
	
	m_rcAxis = GetBorder();//m_rcBorder;
	m_rcAxis.right = nAxisRight;
	m_rcAxis.left  = nAxisRight - nWidth;
	
	SetNameRect(/*m_rcBorder.left*/m_ptTopLeft.x, m_nYCenter - m_nTextHeight / 2, nAxisRight - nWidth, m_nYCenter + m_nTextHeight / 2);

	m_rcNameRectOrigin = m_rcName;
	m_rcDraw = GetBorder();//m_rcBorder;
	m_rcDraw.left = nAxisRight;
}

void CDrawBinaryVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	CDrawVariable::ExpandBorder(l, t, r, b);
}
