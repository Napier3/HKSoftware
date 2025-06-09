// DrawAnalogVariable.cpp: implementation of the CDrawAnalogVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawAnalogVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawAnalogVariable::CDrawAnalogVariable()
{
	InitAxisSet();
	m_dZeroValue = NULL;
	m_dCoefValue = NULL;
	m_dRange = 0;
	m_strUnit	 = "";
	m_strPhaseID = "";
	m_pDrawStruct = NULL;
}

CDrawAnalogVariable::~CDrawAnalogVariable()
{
	m_pDrawStruct = NULL;
}

void CDrawAnalogVariable::SetAdjustValue(double *dZero,double *dCoef)
{
	m_dZeroValue = dZero;
	m_dCoefValue = dCoef;
	
#ifdef _SHOW_PARA
	m_oParas.SetAdjustValue(0, *dCoef);	
#endif
}

void CDrawAnalogVariable::SetUnit(const CString& strUnit)
{
	m_strUnit = strUnit;

#ifdef _SHOW_PARA
	m_oParas.SetUnit(strUnit);	
#endif	
}

void CDrawAnalogVariable::SetBorder(const CRect &rect, BOOL bSavePos)
{
	CDrawBase::SetBorder(rect);

	InitAxis(MrDraw::g_snNameandAxisRectWidth);
	
	if (bSavePos)
	{
		SetDrawRectRatio();
	}
}

void CDrawAnalogVariable::SetBorder(const CRect &rect)
{
	CDrawVariable::SetBorder(rect);

	InitAxis(MrDraw::g_snNameandAxisRectWidth);
}

void CDrawAnalogVariable::SetParaRect(CRect rcPara)
{
#ifdef _SHOW_PARA
	m_oParas.SetParaRect(rcPara);
#endif
}

void CDrawAnalogVariable::InitAxis(long nAxisRight)
{	
	CDrawVariable::InitAxis(MrDraw::g_snNameandAxisRectWidth);

	m_rcAxis = m_rcBorder;
	int nYCenter = m_nYCenter;
	m_rcAxis.right = nAxisRight;
	long nWidth = m_oRulerAxis.GetRulerHeight();//得到标尺的宽度
	m_rcAxis.left = nAxisRight - nWidth;
	m_oRulerAxis.SetBorder(m_rcAxis);	
	m_rcDraw = m_rcBorder;
	m_rcDraw.left = nAxisRight;
	double dCoef ;
	m_oRulerAxis.GetAxisInterface(dCoef,nYCenter);
	
	SetNameRect(m_rcBorder.left
		,m_nYCenter - m_nTextHeight / 2
		,nAxisRight - nWidth,
		m_nYCenter + m_nTextHeight / 2);

	m_rcNameRectOrigin  = m_rcName;
	long nZeroPos = 0;
	m_oRulerAxis.LogicPointToDevicePoint(0,&nZeroPos);
	m_bNeedDrawCenter = ( abs(nZeroPos - m_nYCenter) < 3);
}

void CDrawAnalogVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	l = 0;
	r = 0;
	CDrawVariable::ExpandBorder(l, t, r, b);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);

	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{			
			m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
		}
	}
}

// LONG CDrawAnalogVariable::MouseMove(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::MouseMove(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawAnalogVariable::LButtonDown(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::LButtonDown(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawAnalogVariable::LButtonUp(UINT nFlags, CPoint &point)
// {
// 	LONG nState = CDrawVariable::LButtonUp(nFlags,point);
// 	return nState;
// }
// 
// LONG CDrawAnalogVariable::RButtonDown(UINT nFlags, CPoint &point)
// {
// 	return DRAW_NONE_OBJECT_SELECTED;
// }
// 
// LONG CDrawAnalogVariable::RButtonUp(UINT nFlags, CPoint &point)
// {
// 	return DRAW_NONE_OBJECT_SELECTED;
// }

BOOL CDrawAnalogVariable::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawAnalogVariable::Draw(CDC *pDC, ULONG nDrawStyle) 
{	
	if ((VARIABLE_DRAW_STYLE_AXIS & nDrawStyle) == VARIABLE_DRAW_STYLE_AXIS)
	{
		if (m_nSelectedState == DRAW_HAS_OBJECT_SELECTED || m_bSelect)
		{
			m_oRulerAxis.DrawIt(pDC);
		}
	}

	if ((VARIABLE_DRAW_STYLE_NAME & nDrawStyle) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, nDrawStyle);
	}

	if ((VARIABLE_DRAW_STYLE_CENTER & nDrawStyle) == VARIABLE_DRAW_STYLE_CENTER)
	{
		CDrawVariable::Draw(pDC, nDrawStyle);
	}
	
	if ((VARIABLE_DRAW_STYLE_NAME & nDrawStyle) == VARIABLE_DRAW_STYLE_NAME)
	{
		CDrawVariable::Draw(pDC, nDrawStyle);
	}
	
	if ((VARIABLE_DRAW_STYLE_WAVE & nDrawStyle) == VARIABLE_DRAW_STYLE_WAVE)
	{
		CPen MyPen(PS_SOLID,1,m_crColor);
		CPen* pOldPen = pDC->SelectObject(&MyPen);
		ASSERT (m_pptAttachBuffer != NULL);
		
		if (m_pptAttachBuffer != NULL)
		{
			long nWaveLength = m_pptAttachBuffer->GetCurrUseLength();
			pDC->Polyline(m_pptAttachBuffer->GetBuffer(), nWaveLength);
		}
		
		pDC->SelectObject(pOldPen);
		MyPen.DeleteObject();
		pOldPen = NULL;
	}
}

void Axis_ValidateMinMax(double &dMin, double &dMax)
{
	if (dMin == dMax)
	{
		if (-0.0001 < dMin && dMin < 0.0001)
		{
			dMin = -1;
			dMax = 1;
		}
		else
		{
			dMin = 0.95 * dMin;
			dMax = 1.05 * dMax;
		}
	}
	else
	{
		double dLen = dMax - dMin;

		if (dLen < 0)
		{
			double dTemp = dMax;
			dMax = dMin;
			dMin = dTemp;
			dLen = -dLen;
		}

		dLen *= 0.05;

		dMin -= dLen;
		dMax += dLen;
	}
}

void CDrawAnalogVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	if (m_pnAttachBuffer == NULL || m_pptAttachBuffer ==NULL)
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

	//自动调整Y轴坐标范围
	double dMin = *m_dCoefValue;
	dMin *= *m_pDrawStruct->m_pnMinValue;
	double dMax = *m_dCoefValue;
	dMax *= *m_pDrawStruct->m_pnMaxValue;
	Axis_ValidateMinMax(dMin, dMax);

	double dAxisMax, dAxisMin;
	m_oRulerAxis.GetMinMaxVal(&dAxisMin, &dAxisMax, 0);

	if (dMin != dAxisMin || dMax != dAxisMax)
	{
		m_oRulerAxis.SetMinMaxVal(dMin, dMax, 0);
	}

	m_oRulerAxis.GetAxisInterface(dDrawCoef, nOffSet);
	double dOffset = nOffSet /*- *m_dZeroValue *  dDrawCoef*/;
	dDrawCoef *= 0 - *m_dCoefValue;
	
	m_pptAttachBuffer->CalValueY(dDrawCoef,dOffset,m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
		nBuf2BeginPos,nBuf2EndPos,nGap);
}

void CDrawAnalogVariable::Move(long nHor, long nVer) 
{ 
	CDrawVariable::Move(nHor,nVer);
}

void CDrawAnalogVariable::Zoom(double dRate) 
{
}

void CDrawAnalogVariable::GetVaraibleInterface(double& dCoef,long& nOffSetY)
{
	double dAxisCoef ;
	int nCenter;
	m_oRulerAxis.GetAxisInterface(dAxisCoef,nCenter);
	dCoef = dAxisCoef * *m_dCoefValue;
	nOffSetY = nCenter;
}

void CDrawAnalogVariable::SetRange(double dRange) 
{
	m_dRange = dRange;
	double dMax = dRange;
	double dMin = 0 - dRange;
	m_oRulerAxis.SetMinMaxVal(dMin , dMax , 0 );

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->dRange = dRange;
	}
}

void CDrawAnalogVariable::SetClipRect(const CRect &rcClip)
{
	CDrawVariable::SetClipRect(rcClip);
	
#ifdef _SHOW_PARA
	if(m_pClipRect != NULL)
	{
		m_oParas.SetClipRect(*m_pClipRect);
	}
#endif
}

void CDrawAnalogVariable::GetTimeCursorPos(long nCursorPos)
{
#ifdef _SHOW_PARA
	m_oParas.CalParaRect(nCursorPos,m_nYCenter);
// 
// 	long nWidth = m_rcDraw.Width();
// 	long nPoints = m_pptAttachBuffer->GetCurrUseLength();
// 	long nLeft = (nCursorPos - m_rcDraw.left) * nPoints / nWidth;
// 	long nGap = m_oBufferPos.nGap;
// 	long nBeginPos1 = m_oBufferPos.nBuf1BeginPos;
// 	long nBeginPos2 = m_oBufferPos.nBuf2BeginPos;
// 	long nEndPos1   = m_oBufferPos.nBuf1EndPos;
// 	long nEndPos2   = m_oBufferPos.nBuf2EndPos;
// 	long nCalBegin  = nBeginPos1 + nLeft * nGap;
// 	long nCalEnd    = nCalBegin + STRECORD_DFT_CAL_LEN;
// 	m_oParas.m_oCalPara.pnBuffer = m_pnAttachBuffer->GetBuffer();
// 	long nBufferLen = m_pnAttachBuffer->GetBufferLength();
// 	long nDataFillBegin = m_pnAttachBuffer->GetDataFillBeginPosition();
// 	long nDataLen	= m_pnAttachBuffer->GetDataLength();
// 	
// 	if(nDataLen < nBufferLen)//数据不循环
// 	{
// 		if(nCalBegin < 0 || nCalEnd > nDataFillBegin)//没有足够的数据
// 		{
// 		}
// 		else
// 		{
// 			m_oParas.m_oCalPara.nDataLength = STRECORD_DFT_CAL_LEN;
// 			m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
// 			m_oParas.m_oCalPara.nBuffer1Len = STRECORD_DFT_CAL_LEN;
// 			m_oParas.m_oCalPara.nBuffer2Pos = -1;
// 			m_oParas.m_oCalPara.nBuffer2Len = -1;
// 			
// 			m_oParas.m_oCalPara.nDftBuffer1Len = STRECORD_DFT_CAL_LEN;
// 			m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
// 			m_oParas.m_oCalPara.nDftBuffer2Len = -1;
// 			m_oParas.m_oCalPara.nDftBuffer2Pos = -1;
// 			
// 			m_oParas.CalParaRect(nCursorPos,m_nYCenter);
// 		}
// 	}
// 	else
// 	{
// 		if(nCalBegin >= nBufferLen)//计算的数据在新的一端
// 		{
// 			nCalBegin -= nBufferLen;
// 			nCalEnd   -= nBufferLen;
// 			
// 			if(nCalEnd > nDataFillBegin)//数据不足
// 			{
// 			}
// 			else
// 			{
// 				m_oParas.m_oCalPara.nDataLength = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
// 				m_oParas.m_oCalPara.nBuffer1Len = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nBuffer2Pos = -1;
// 				m_oParas.m_oCalPara.nBuffer2Len = -1;
// 				
// 				m_oParas.m_oCalPara.nDftBuffer1Len = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
// 				m_oParas.m_oCalPara.nDftBuffer2Len = -1;
// 				m_oParas.m_oCalPara.nDftBuffer2Pos = -1;
// 				
// 				m_oParas.CalParaRect(nCursorPos,m_nYCenter);
// 			}
// 		}
// 		else
// 		{
// 			if(nCalEnd <= nBufferLen)//都在数据旧的一端
// 			{
// 				m_oParas.m_oCalPara.nDataLength = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
// 				m_oParas.m_oCalPara.nBuffer1Len = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nBuffer2Pos = -1;
// 				m_oParas.m_oCalPara.nBuffer2Len = -1;
// 				
// 				m_oParas.m_oCalPara.nDftBuffer1Len = STRECORD_DFT_CAL_LEN;
// 				m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
// 				m_oParas.m_oCalPara.nDftBuffer2Len = -1;
// 				m_oParas.m_oCalPara.nDftBuffer2Pos = -1;
// 				
// 				m_oParas.CalParaRect(nCursorPos,m_nYCenter);			
// 			}
// 			else
// 			{
// 				long nLen1 = nBufferLen - nCalBegin;
// 				long nLen2 = STRECORD_DFT_CAL_LEN - nLen1;
// 				
// 				if(nLen2 > nDataFillBegin)//没有足够数据
// 				{
// 				}
// 				else
// 				{
// 					m_oParas.m_oCalPara.nDataLength = STRECORD_DFT_CAL_LEN;
// 					m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
// 					m_oParas.m_oCalPara.nBuffer1Len = nLen1;
// 					m_oParas.m_oCalPara.nBuffer2Pos = 0;
// 					m_oParas.m_oCalPara.nBuffer2Len = nLen2;
// 					
// 					m_oParas.m_oCalPara.nDftBuffer1Len = nLen1;
// 					m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
// 					m_oParas.m_oCalPara.nDftBuffer2Len = nLen2;
// 					m_oParas.m_oCalPara.nDftBuffer2Pos = 0;
// 					
// 					m_oParas.CalParaRect(nCursorPos,m_nYCenter);
// 				}
// 			}
// 		}
// 	}
#endif
}

void CDrawAnalogVariable::SetParentWnd(CWnd* pParentWnd)
{
	CDrawVariable::SetParentWnd(pParentWnd);
	
#ifdef _SHOW_PARA
	m_oParas.SetParentWnd(pParentWnd);
#endif
}

void CDrawAnalogVariable::AddPara(UINT nID)
{
#ifdef _SHOW_PARA
	m_oParas.AddPara(nID);
#endif
}

void CDrawAnalogVariable::DeletePara(UINT nID)
{
#ifdef _SHOW_PARA
	m_oParas.DeletePara(nID);
#endif
}

void CDrawAnalogVariable::DeleteAllPara()
{
#ifdef _SHOW_PARA
	m_oParas.DeleteAllPara();
#endif
}

void CDrawAnalogVariable::SetAttachStruct(PDRAWVAR pDrawStruct)
{	
	CDrawVariable::SetAttachStruct(pDrawStruct);

	if (pDrawStruct != NULL)
	{
		SetRange(pDrawStruct->dRange);
	}
}