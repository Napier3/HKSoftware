// DrawAnalogVariable.cpp: implementation of the CDrawAnalogVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawAnalogVariable.h"
#include "DrawAttrSpy.h"

#include "../../XDrawBase/XDrawGlobal.h"
//

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
	m_dZeroValue = NULL;
	m_dCoefValue = NULL;
	m_dRange = 0;
	m_strUnit	 = "";
	m_strPhaseID = "";
	m_pDrawStruct = NULL;
	//m_pRefRtVariable = NULL;
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
	m_oParas.SetAdjustValue(*dZero, *dCoef);	
#endif
}

void CDrawAnalogVariable::SetUnit(const CString& strUnit)
{
	m_strUnit = strUnit;

#ifdef _SHOW_PARA
	m_oParas.SetUnit(strUnit);	
#endif	
}

// void CDrawAnalogVariable::SetBorder(const CRect &rect, BOOL bSavePos)
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

void CDrawAnalogVariable::SetBorder(const CRect &rect)
{
	CRect rcBorder = rect;

	long nHeight = rcBorder.bottom - rcBorder.top;

	if (nHeight < RECORDDRAW_ANALOG_MINHEIGHT)
	{
		rcBorder.bottom = rcBorder.top + RECORDDRAW_ANALOG_MINHEIGHT;
	}
	else
	{
		long nCount = nHeight / RECORDDRAW_ANALOG_MINHEIGHT;
		long nOffset = nHeight - nCount * RECORDDRAW_ANALOG_MINHEIGHT;

		if (nOffset*2 > RECORDDRAW_ANALOG_MINHEIGHT)
		{
			nCount++;
		}


		nHeight = nCount * RECORDDRAW_ANALOG_MINHEIGHT;
		rcBorder.bottom = rcBorder.top + nHeight;
	}

	CDrawVariable::SetBorder(rcBorder);

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
	m_nYCenter = CenterPoint().y;

	m_rcAxis = GetBorder();//m_rcBorder;
	m_rcAxis.right = nAxisRight;
	long nWidth = m_pRulerAxis->GetRulerHeight();//得到标尺的宽度
	m_rcAxis.left = nAxisRight - nWidth;
	m_pRulerAxis->SetBorder(m_rcAxis);	
	m_rcDraw = GetBorder();//m_rcBorder;
	m_rcDraw.left = nAxisRight;
	double dCoef ;
	m_pRulerAxis->GetAxisInterface(dCoef,m_nYCenter);

	SetNameRect(m_ptTopLeft.x //m_rcBorder.left
		,m_nYCenter - m_nTextHeight
		,nAxisRight/* - nWidth*/,
		m_nYCenter + m_nTextHeight);

	m_rcNameRectOrigin  = m_rcName;
	long nZeroPos = m_nYCenter;
	m_pRulerAxis->LogicPointToDevicePoint(0,&nZeroPos);
	m_bNeedDrawCenter = (m_nYCenter == nZeroPos);
}

void CDrawAnalogVariable::ExpandBorder(long &l, long &t, long &r, long &b)
{
	l = 0;
	r = 0;
	CDrawVariable::ExpandBorder(l, t, r, b);
	InitAxis(MrDraw::g_snNameandAxisRectWidth);

	PostDrawObjectPosChangedMsg();
}

BOOL CDrawAnalogVariable::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

void CDrawAnalogVariable::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
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
		CPen *MyPen = NULL;

		if (g_bInWriteBmpFileState)
		{
			MyPen = new CPen(m_nLineStyle, 1, RGB(0, 0, 0));
		}
		else
		{
			MyPen = new CPen(m_nLineStyle, 1, m_crForeColor);
		}

		CPen* pOldPen = pDC->SelectObject(MyPen);
		ASSERT (m_pptAttachDrawBuffer != NULL);

		if (m_pptAttachDrawBuffer != NULL)
		{
			long nWaveLength = m_pptAttachDrawBuffer->GetCurrUseLength();// -  1;  //2021-2-19  lijunqing 少了一个点

			if (MrDraw::g_dwAnalogDrawMode == ANALOG_DRAW_MODE_LINE)
			{
				pDC->Polyline(m_pptAttachDrawBuffer->GetBuffer(), nWaveLength);
			}
			else
			{
				DWORD dwDrawStyle = MrDraw::g_dwAnalogDrawMode - ANALOG_DRAW_MODE_CROSSA;
				if (dwDrawStyle > 1)
				{
					dwDrawStyle = 1;
				}

				xdraw_DrawPointLine(pDC, m_pptAttachDrawBuffer->GetBuffer(), nWaveLength, dwDrawStyle, m_crForeColor, 3, fZoomRatio, ptOffset);
			}
		}

		pDC->SelectObject(pOldPen);
		MyPen->DeleteObject();
		delete MyPen;
		pOldPen = NULL;
	}
}

void CDrawAnalogVariable::LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) 
{
	if (m_pnAttachBuffer == NULL || m_pptAttachDrawBuffer ==NULL)
	{
		return;
	}

	if (is_mem_buffer_ushort(m_pnAttachBuffer))
	{
		if (m_pnAttachBuffer->GetBuffer() == NULL)
		{
			return;
		}
	}
	else
	{
		if (m_pnAttachBuffer->GetBuffer_long() == NULL
			&& m_pnAttachBuffer->GetBuffer_float() == NULL)
		{
			return;
		}
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
	double dOffset = nOffSet - *m_dZeroValue *  dDrawCoef;
	dOffset += dOffsetY;
	dDrawCoef *= (0-*m_dCoefValue);
	//dDrawCoef *= *m_dCoefValue;

	if (m_pnAttachBuffer != NULL)
	{//2021-10-29  lijunqing
		if (is_mem_buffer_ushort(m_pnAttachBuffer))
		{
			m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,(CMemBuffer_UShort*)m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
				nBuf2BeginPos,nBuf2EndPos,nGap);
		}
		else
		{
			if (m_pnAttachBuffer->GetBuffer_long() != NULL)
			{
				m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,(CMemBuffer_Long*)m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
					nBuf2BeginPos,nBuf2EndPos,nGap);
			}
			else
			{
				m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,(CMemBuffer_Float*)m_pnAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
					nBuf2BeginPos,nBuf2EndPos,nGap);
			}
		}
	}
	else if (m_pfAttachBuffer != NULL)
	{//float 类型的缓冲区   //2021-10-29  lijunqing
		m_pptAttachDrawBuffer->CalValueY(dDrawCoef,dOffset,m_pfAttachBuffer,nBuf1BeginPos,nBuf1EndPos,
			nBuf2BeginPos,nBuf2EndPos,nGap);
	}
}

void CDrawAnalogVariable::DrawAttrs(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag, MrDraw::DRAWMEMBUFFERPOS &oBufPos)
{
	if (!GetShow())
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDrawAttrSpy *pAttrDraw = NULL;
	double dCoefX=1, dCoefY=1;

	while (pos != NULL)
	{
		pAttrDraw = (CDrawAttrSpy*)GetNext(pos);

		pAttrDraw->LogicPointToDevicePoint(dCoefX, dCoefY, oBufPos);
		pAttrDraw->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
}


void CDrawAnalogVariable::Move(long nHor, long nVer) 
{ 
	CDrawVariable::Move(nHor,nVer);
}

void CDrawAnalogVariable::ZoomY(double dRate) 
{
	Zoom(dRate);
}

//放大缩小的算法说明
/*
1，dRate：小于1表示图形缩小，大于1表示图形放大
2，图形缩小时，网格每格代表的数值变大
3，图形放大时，网格每格代表的数值变小
4，网格每格数值为RECORDDRAW_ANALOG_MINHEIGHT(50)
5，绘图对象绘制的最小纵向大小为RECORDDRAW_ANALOG_MINHEIGHT(50)
6，网格每格的数值按照1、2、5、10的标准来计算
7，m_dRange：绘图对象的量程，即坐标的极值；m_dCarryPerGrid：
网格每格的大小，两者之间保持整数倍的关系
8，图形放大缩小的过程中，绘图对象的Range(m_dRange)保持不变，改变m_dCarryPerGrid
从而达到图形的放大缩小的目的
*/
void CDrawAnalogVariable::Zoom(double dRate) 
{
	BOOL bZoomIn = TRUE;

	if (dRate < 1)
	{//缩小时，如果绘图对象的纵向大小小于RECORDDRAW_ANALOG_MINHEIGHT，则返回
		bZoomIn = FALSE;
		if (/*m_rcBorder.Height()*/m_nHeight <= RECORDDRAW_ANALOG_MINHEIGHT)
		{
			return;
		}
	}
	else
	{
		double dZoomCoef = m_dRange / m_dCarryPerGrid;

		if (dZoomCoef >= 1000)
		{
			return;
		}
	}

	//根据放大缩小的倍数计算m_dCarryPerGrid
	double dCarry = m_dCarryPerGrid;
	double dRangeBk = m_dRange;
	dCarry /= dRate;

	//按照1、2、5、10标准化m_dCarryPerGrid
	if (bZoomIn)
	{
		MrDraw::GetIECAxisScaleValueZoomIn(dCarry, m_dCarryPerGrid);
	}
	else
	{
		MrDraw::GetIECAxisScaleValueZoomOut(dCarry, m_dCarryPerGrid);
	}

	//计算实际的放大倍数
	double dZoomRate = m_dRange * 2 / m_dCarryPerGrid;

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->dRange = m_dRange;
		m_pDrawStruct->dRangeGrid = m_dCarryPerGrid;
	}

	//调整绘图对象的位置，即Border
	double dHeight = dZoomRate * RECORDDRAW_ANALOG_MINHEIGHT;
	dHeight /= 2;
	long nHeightNew = (long)dHeight;
	CRect rc = GetBorder();
	rc.top = m_nYCenter - nHeightNew;
	rc.bottom = m_nYCenter + nHeightNew;
	SetBorder(rc);
	m_pRulerAxis->SetMinMaxVal(-m_dRange , m_dRange , 0 );

	//发送绘图对象位置改变消息，重新绘制波形图
	PostDrawObjectPosChangedMsg();
}

void CDrawAnalogVariable::GetVaraibleInterface(double& dCoef,long& nOffSetY)
{
	double dAxisCoef ;
	int nCenter;
	m_pRulerAxis->GetAxisInterface(dAxisCoef,nCenter);
	dCoef = dAxisCoef * (0 - *m_dCoefValue);
	nOffSetY = nCenter - (*m_dZeroValue) *  dAxisCoef;
}

void CDrawAnalogVariable::SetRange(double dRange) 
{
	if (dRange <= 0.0001)
	{
		dRange = 0.01; //2022-6-12  lijunqing
	}

	dRange *= 1.1;
	dRange *= 2;
	double dCarry = dRange;
	//	MrDraw::GetIECAxisScaleValue(dRange, m_dCarryPerGrid);
	MrDraw::GetIECAxisScaleValueZoomOut(dRange, m_dCarryPerGrid);
	m_dRange = m_dCarryPerGrid / 2;
	MrDraw::GetIECAxisScaleValueZoomIn(m_dRange, m_dRange);

	double dMax = m_dRange;
	double dMin = 0 - m_dRange;
	m_pRulerAxis->SetMinMaxVal(dMin , dMax , 0 );

	if (m_pDrawStruct != NULL)
	{
		m_pDrawStruct->dRange = m_dRange;
		m_pDrawStruct->dRangeGrid = m_dCarryPerGrid;
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

void CDrawAnalogVariable::GetTimeCursorPos(long nCursorPos, long MR1200_DFT_CAL_LEN)
{
#ifdef _SHOW_PARA
	long nWidth = m_rcDraw.Width();
	long nPoints = m_pptAttachDrawBuffer->GetCurrUseLength();
	long nLeft = (nCursorPos - m_rcDraw.left) * nPoints / nWidth;
	long nGap = m_oBufferPos.nGap;
	long nBeginPos1 = m_oBufferPos.nBuf1BeginPos;
	long nBeginPos2 = m_oBufferPos.nBuf2BeginPos;
	long nEndPos1   = m_oBufferPos.nBuf1EndPos;
	long nEndPos2   = m_oBufferPos.nBuf2EndPos;
	long nCalBegin  = nBeginPos1 + nLeft * nGap;
	long nCalEnd    = nCalBegin + MR1200_DFT_CAL_LEN;
	m_oParas.m_oCalPara.pnBuffer = m_pnAttachBuffer->GetBuffer();
	m_oParas.m_oCalPara.pnBuffer_long = m_pnAttachBuffer->GetBuffer_long();
	m_oParas.m_oCalPara.pfBuffer = m_pnAttachBuffer->GetBuffer_float();
	long nBufferLen = m_pnAttachBuffer->GetBufferLength();
	long nDataFillBegin = m_pnAttachBuffer->GetDataFillBeginPosition();
	long nDataLen	= m_pnAttachBuffer->GetDataLength();

	if(nDataLen < nBufferLen)//数据不循环
	{
		if(nCalBegin < 0 || nCalEnd > nDataFillBegin)//没有足够的数据
		{
		}
		else
		{
			m_oParas.m_oCalPara.nDataLength = MR1200_DFT_CAL_LEN;
			m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
			m_oParas.m_oCalPara.nBuffer1Len = MR1200_DFT_CAL_LEN;
			m_oParas.m_oCalPara.nBuffer2Pos = -1;
			m_oParas.m_oCalPara.nBuffer2Len = -1;

			m_oParas.m_oCalPara.nDftBuffer1Len = MR1200_DFT_CAL_LEN;
			m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
			m_oParas.m_oCalPara.nDftBuffer2Len = -1;
			m_oParas.m_oCalPara.nDftBuffer2Pos = -1;

			m_oParas.CalParaRect(nCursorPos,m_nYCenter);
		}
	}
	else
	{
		if(nCalBegin >= nBufferLen)//计算的数据在新的一端
		{
			nCalBegin -= nBufferLen;
			nCalEnd   -= nBufferLen;

			if(nCalEnd > nDataFillBegin)//数据不足
			{
			}
			else
			{
				m_oParas.m_oCalPara.nDataLength = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
				m_oParas.m_oCalPara.nBuffer1Len = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nBuffer2Pos = -1;
				m_oParas.m_oCalPara.nBuffer2Len = -1;

				m_oParas.m_oCalPara.nDftBuffer1Len = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
				m_oParas.m_oCalPara.nDftBuffer2Len = -1;
				m_oParas.m_oCalPara.nDftBuffer2Pos = -1;

				m_oParas.CalParaRect(nCursorPos,m_nYCenter);
			}
		}
		else
		{
			if(nCalEnd <= nBufferLen)//都在数据旧的一端
			{
				m_oParas.m_oCalPara.nDataLength = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
				m_oParas.m_oCalPara.nBuffer1Len = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nBuffer2Pos = -1;
				m_oParas.m_oCalPara.nBuffer2Len = -1;

				m_oParas.m_oCalPara.nDftBuffer1Len = MR1200_DFT_CAL_LEN;
				m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
				m_oParas.m_oCalPara.nDftBuffer2Len = -1;
				m_oParas.m_oCalPara.nDftBuffer2Pos = -1;

				m_oParas.CalParaRect(nCursorPos,m_nYCenter);			
			}
			else
			{
				long nLen1 = nBufferLen - nCalBegin;
				long nLen2 = MR1200_DFT_CAL_LEN - nLen1;

				if(nLen2 > nDataFillBegin)//没有足够数据
				{
				}
				else
				{
					m_oParas.m_oCalPara.nDataLength = MR1200_DFT_CAL_LEN;
					m_oParas.m_oCalPara.nBuffer1Pos = nCalBegin;
					m_oParas.m_oCalPara.nBuffer1Len = nLen1;
					m_oParas.m_oCalPara.nBuffer2Pos = 0;
					m_oParas.m_oCalPara.nBuffer2Len = nLen2;

					m_oParas.m_oCalPara.nDftBuffer1Len = nLen1;
					m_oParas.m_oCalPara.nDftBuffer1Pos = nCalBegin;
					m_oParas.m_oCalPara.nDftBuffer2Len = nLen2;
					m_oParas.m_oCalPara.nDftBuffer2Pos = 0;

					m_oParas.CalParaRect(nCursorPos,m_nYCenter);
				}
			}
		}
	}
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
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s%s->AddPara(%d)"), m_strUnit.GetString(), m_strPhaseID.GetString(), nID);
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

void CDrawAnalogVariable::SetAttachStruct(PRECORDDRAWOBJECTCONTROL pDrawStruct)
{	
	CDrawVariable::SetAttachStruct(pDrawStruct);
	m_dRange = pDrawStruct->dRange;
	m_dCarryPerGrid = pDrawStruct->dRangeGrid;
	double dMax = m_dRange;
	double dMin = 0 - m_dRange;
	m_pRulerAxis->SetMinMaxVal(dMin , dMax , 0 );
	// 	if (pDrawStruct != NULL)
	// 	{
	// 		SetRange(pDrawStruct->dRange);
	// 	}
}


void CDrawAnalogVariable::DrawChanName(CDC* pDC, BOOL bDrawCarryGrid)
{
	int nMode = pDC->SetBkMode(TRANSPARENT);
	long nSrcBegin = 0;
	long nSrcLen = 0;
	CFont *pOldFont = NULL;

	if (GetSelect())
	{
		pOldFont = pDC->SelectObject(&m_oSelectNameFont);
	}
	else
	{
		pOldFont = pDC->SelectObject(&m_oNameFont);//
	}

	COLORREF crOld ;

	if (g_bInWriteBmpFileState)
	{
		crOld = pDC->SetTextColor(RGB(0, 0, 0));	
	}
	else
	{
		crOld = pDC->SetTextColor(m_crForeColor);	
	}

	CRect rcName = m_rcName;
	CRect rcScale = m_rcName;

	if (bDrawCarryGrid)
	{
		rcName.bottom -= m_nTextHeight;
		rcScale.top += m_nTextHeight;
	}

#ifdef _DEBUG
	CString strName;
	BOOL bBufferIsNull = FALSE;
	if (m_pnAttachBuffer == NULL)
	{
		bBufferIsNull = TRUE;
	}
	else 
	{
		if (m_pnAttachBuffer->GetBuffer() == NULL)
		{
			if (m_pnAttachBuffer->GetBuffer_float() == NULL)
			{
				if (m_pnAttachBuffer->GetBuffer_long() == NULL)
				{
					bBufferIsNull = TRUE;
				}
			}
		}
	}

	if (bBufferIsNull)
	{
		strName.Format("%s null", m_strName);
	}
	else
	{
		strName = m_strName;
	}

	pDC->DrawText(strName, rcName,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

#else
	pDC->DrawText(m_strName, rcName,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

#endif

	if (bDrawCarryGrid)
	{
		CString strCarry;
		strCarry.Format("%.4f", m_dCarryPerGrid);
		_ChopFloatString(strCarry);
		CString strScale;
		strScale = strCarry;
		pDC->DrawText(strScale, rcScale,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(crOld);
	pDC->SetBkMode(nMode);
	pOldFont = NULL;
}

COLORREF MR_ChangeColor(COLORREF cr, long nIndex)
{
	long nChange = nIndex * 20;
	long br = cr & 0xFF;
	long bg = (cr >> 8) & 0xFF;
	long bb = (cr >> 16) & 0xFF;
	// 	BYTE br = cr & 0xFF;
	// 	BYTE bg = (cr >> 8) & 0xFF;
	// 	BYTE bb = (cr >> 16) & 0xFF;

	br -= nChange;
	bg -= nChange;
	bb -= nChange;

	// 	br -= nChange;
	// 	bg -= nChange;
	// 	bb -= nChange;
	//
	if (br < 0)
	{
		br = 0;
	}

	if (bg < 0)
	{
		bg = 0;
	}

	if (bb < 0)
	{
		bb = 0;
	}

	return br + (bg << 8) + (bb << 16);
}

//////////////////////////////////////////////////////////////////////////
//综合属性绘图
void CDrawAnalogVariable::AddAttrsDraw(CRtVariable *pRtVariable)
{
	ASSERT (pRtVariable == m_pXDrawDataRef);
	CRtDataAttributes *pAttrs = pRtVariable->m_pDataAttrs;
	POS pos = pAttrs->GetHeadPosition();
	CRtDataAttribute *pAttr = NULL;
	CDrawAttrSpy *pAttrDraw = NULL;
	static UINT g_nAttrLineStyle[4] = {PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT};
	int nAttrLineStyleIndex = 0;

	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute *)pAttrs->GetNext(pos);
		pAttrDraw = (CDrawAttrSpy*)FindByID(pAttr->m_strID);

		if (//pAttr->m_nAttributeID != SingleVariableAttrID_Frequancy && 
			pAttr->m_nAttributeID != SingleVariableAttrID_EffecValue && 
			pAttr->m_nAttributeID != SingleVariableAttrID_FundValue &&
			pAttr->m_nAttributeID != SingleVariableAttrID_DeltaEffecValue && 
			pAttr->m_nAttributeID != SingleVariableAttrID_DeltaFundValue 
			)
		{
			continue;
		}

		if (pAttrDraw == NULL && pAttr->GetUse())
		{
			pAttrDraw = new CDrawAttrSpy(m_pRulerAxis);
			pAttrDraw->m_pfAttachBuffer = pAttr->m_pAttrBuffer;
			pAttrDraw->m_nAttrDataIndex = pAttr->m_nAttributeID;
			pAttrDraw->m_strName = pAttr->m_strID;
			pAttrDraw->m_strID = pAttr->m_strID;
			AddNewChild(pAttrDraw);
			pAttrDraw->m_pptAttachDrawBuffer = m_pptAttachDrawBuffer;
			pAttrDraw->m_nLineStyle = g_nAttrLineStyle[nAttrLineStyleIndex % 4];
			nAttrLineStyleIndex++;
			pAttrDraw->m_crForeColor = MR_ChangeColor(m_crForeColor, nAttrLineStyleIndex);//RGB(255, 255, 255);
		}
	}
}
