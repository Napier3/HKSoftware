// DrawAnalogVariableCmp.cpp: implementation of the CDrawAnalogVariableCmp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawAnalogVariableCmp.h"
#include "DrawAttrSpy.h"
//

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawAnalogVariableCmp::CDrawAnalogVariableCmp()
{

}

CDrawAnalogVariableCmp::~CDrawAnalogVariableCmp()
{

}


void CDrawAnalogVariableCmp::SetShow(long nShow)
{
	CDrawBase::SetShow(nShow);

	m_oCmpAnalogDraw.SetShow(nShow);

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->nShow = nShow;
	}
}

void CDrawAnalogVariableCmp::Draw_Cmp(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
{	
	if ((VARIABLE_DRAW_STYLE_AXIS & dwDrawFlag) == VARIABLE_DRAW_STYLE_AXIS)
	{
		if (m_nSelectedState == DRAW_HAS_OBJECT_SELECTED || m_bSelect)
		{
			if (m_nShow)
			{
				m_pRulerAxis->DrawIt(pDC);
			}
		}
	}

	if ((VARIABLE_DRAW_STYLE_NAME & dwDrawFlag) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}

	if (((VARIABLE_DRAW_STYLE_CENTER & dwDrawFlag) == VARIABLE_DRAW_STYLE_CENTER) && m_nShow)
	{
		CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
	
	if ((VARIABLE_DRAW_STYLE_NAME & dwDrawFlag) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
	
	if (!GetShow())
	{
		return;
	}

	if ((VARIABLE_DRAW_STYLE_WAVE & dwDrawFlag) == VARIABLE_DRAW_STYLE_WAVE)
	{
		CPen MyPen(PS_SOLID,1,m_crForeColor);
		CPen* pOldPen = pDC->SelectObject(&MyPen);
		ASSERT (m_pptAttachDrawBuffer != NULL);
		
		if (m_pptAttachDrawBuffer != NULL)
		{
			long nWaveLength = m_pptAttachDrawBuffer->GetCurrUseLength();
			pDC->Polyline(m_pptAttachDrawBuffer->GetBuffer(), nWaveLength);
		}
		
		pDC->SelectObject(pOldPen);
		MyPen.DeleteObject();
		pOldPen = NULL;
	}
}

void CDrawAnalogVariableCmp::LogicPointToDevicePoint_Cmp(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	if (m_pnAttachBuffer == NULL || m_pptAttachDrawBuffer ==NULL)
	{
		return;
	}
	
	if (m_pnAttachBuffer->GetBuffer() == NULL)
	{
		return;
	}
	
	m_oBufferPos = oBufPos;
	long nBuf1BeginPos = oBufPos.nBuf1BeginPos;
	long nBuf1EndPos   = oBufPos.nBuf1EndPos;
	long nBuf2BeginPos = oBufPos.nBuf2BeginPos;
	long nBuf2EndPos   = oBufPos.nBuf2EndPos;
	long nGap = oBufPos.nGap;
	double dDrawCoef;
	int nOffSet;	
	m_pRulerAxis->GetAxisInterface(dDrawCoef, nOffSet);
	nOffSet += 10;
	double dOffset = nOffSet - *m_dZeroValue *  dDrawCoef;
	dDrawCoef *= (0-*m_dCoefValue);
	//dDrawCoef *= *m_dCoefValue;
	
	if (is_mem_buffer_ushort(m_pnAttachBuffer))
	{
		m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,(CMemBuffer_UShort*)m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
			nBuf2BeginPos,nBuf2EndPos,nGap);
	}
	else
	{
		m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,(CMemBuffer_Long*)m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
			nBuf2BeginPos,nBuf2EndPos,nGap);
	}

}
