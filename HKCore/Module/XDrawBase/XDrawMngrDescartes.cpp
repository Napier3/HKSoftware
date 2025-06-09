//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawMngrDescartes.cpp  CXDrawMngrDescartes


#include "stdafx.h"
#include "XDrawMngrDescartes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawMngrDescartes::CXDrawMngrDescartes()
{
	//初始化属性
	SetAxisName(_T("X"), _T("Y"), _T("x-y"));
	m_oAxis.SetAxisBackColor(RGB(255, 255, 255));
	m_oAxis.SetWorkAreaBkColor(RGB(255, 255, 255));

	//初始化成员变量
}

CXDrawMngrDescartes::~CXDrawMngrDescartes()
{
}

void CXDrawMngrDescartes::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	m_oAxis.SetXAxisName(strXAxisName);
	m_oAxis.SetYAxisName(strYAxisName);
	m_oAxis.SetAxisTitle(strAxisTitle);
}

void CXDrawMngrDescartes::SetAxisMaxUnitCount(long nXAxisUnitCount, long nYAxisUnitCount)
{
	m_oAxis.SetXAxisMaxUnitCount(nXAxisUnitCount);
	m_oAxis.SetYAxisMaxUnitCount(nYAxisUnitCount);
}

void CXDrawMngrDescartes::SetAxisXYUnitLock(BOOL bUnLock)
{
	m_oAxis.SetAxisXYUnitLock(bUnLock);
}

void CXDrawMngrDescartes::InitAxis()
{
	SetAxisMaxUnitCount(40, 40);
	m_oAxis.SetAxisXYUnitLock(1);
	m_oAxis.SetLeftGap(0);
	m_oAxis.SetTopGap(6);
	m_oAxis.SetRightGap(5);
	m_oAxis.SetBottomGap(0);
	m_oAxis.SetYAxisAreaWidth(45);
	m_oAxis.SetBorder(m_rcBorder);	
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	m_oAxis.ResetAxis();	

// 	m_oAxis.SetAxisBackColor(m_pAxises->m_crAxisBackColor);
// 	m_oAxis.SetAxisCenterColor(m_pAxises->m_crAxisCenter);
// 	m_oAxis.SetAxisXYUnitLock(m_pAxises->m_bAxisUnitLock);
// 	m_oAxis.SetYAxisGridLineColor(m_pAxises->m_crAxisGridColor);
// 	m_oAxis.SetXAxisGridLineColor(m_pAxises->m_crAxisGridColor);
// 	m_oAxis.SetFrameLeftTopColor(m_pAxises->m_crAxisFrame);
// 	m_oAxis.SetFrameRightBottomColor(m_pAxises->m_crAxisFrame);
// 	m_oAxis.SetWorkAreaBkColor(m_pAxises->m_crAxisWorkAreaBk);
// 
// 	m_oAxis.SetYUnitScaleColor(m_pYAxis->m_crScaleColor);
// 	m_oAxis.SetYAxisWorkAreaBackColor(m_pYAxis->m_crBackColorFrom,m_pYAxis->m_crBackColorTo);
// 	m_oAxis.SetYUnitScaleShadowColor(m_pYAxis->m_crShadowColor);
// 	m_oAxis.SetYAxisName(m_pYAxis->m_strName);
// 
// 	//x axis
// 	if (m_pXAxis->m_pFontName)
// 	{
// 		LOGFONT lpFont = m_pXAxis->m_pFontName->GetLogFont();
// 		m_oAxis.SetXAxisNameFont(lpFont);
// 	}
//
// 	if (m_pXAxis->m_pFontScale)
// 	{
// 		LOGFONT lpFont = m_pXAxis->m_pFontScale->GetLogFont();
// 		m_oAxis.SetXAxisNameFont(lpFont);
// 	}
//
// 	m_oAxis.SetXUnitScaleColor(m_pXAxis->m_crScaleColor);
// 	m_oAxis.SetXAxisWorkAreaBackColor(m_pXAxis->m_crBackColorFrom,m_pXAxis->m_crBackColorTo);
// 	m_oAxis.SetXUnitScaleShadowColor(m_pXAxis->m_crShadowColor);
// 	m_oAxis.SetXAxisName(m_pXAxis->m_strName);
// 
// 	///////////////////
// 	//y axis 2
// 	m_pYAxis2 = (CUIBaseAxis*)m_pAxises->GetAt(2);
// 
// 	if (m_pYAxis2 != NULL)
// 	{
// 		m_oAxis.SetUseY2Axis(TRUE);
// 		m_oAxis.SetY2AxisName(m_pYAxis2->m_strName);
// 		m_oAxis.SetXYAxisMinMaxVal(
// 			m_pXAxis->m_dRangeMin,m_pYAxis->m_dRangeMin,
// 			m_pXAxis->m_dRangeMax,m_pYAxis->m_dRangeMax,
// 			m_pYAxis2->m_dRangeMin,m_pYAxis2->m_dRangeMax);
// 	}
// 	else
// 	{
// 		m_oAxis.SetUseY2Axis(FALSE);
// 		m_oAxis.SetMinMaxVal(m_pXAxis->m_dRangeMin,m_pYAxis->m_dRangeMin,
// 			m_pXAxis->m_dRangeMax,m_pYAxis->m_dRangeMax, 0);
// 	}
//
//
// 	CRect rect(m_nLeft,m_nTop,m_nLeft + m_nWidth,m_nTop+m_nHeight);
// 	m_oAxis.SetBorder(rect);
// 	m_oAxis.GetAxisInterface(nXOffSet,nYOffSet,dXCoef,dYCoef);

}

long CXDrawMngrDescartes::GetDrawsCount()
{
	CXDrawList *p = NULL;
	long nDrawCount = 0;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXDrawList*)GetNext(pos);
		nDrawCount += p->GetCount();
	}

	return nDrawCount;
}

void CXDrawMngrDescartes::AdjustAxis(BOOL bUseMngrAxisRange)
{
	if (GetDrawsCount()/*GetCount()*/ == 0)//zhouhj 20210203 当子链表为空时,会出错
	{
		m_fXMin = -10;
		m_fXMax = 10;
		m_fYMin = -10;
		m_fYMax = 10;

		m_oAxis.SetBorder(m_rcBorder);
		ResetAxis();
		LogicPointToDevicePoint();
		return;
	}

	CXDrawList *p = NULL;
	POS pos = GetHeadPosition();
	double fMinX = 999999,fMaxX =-999999,fMinY = 999999, fMaxY = -999999;
	BOOL bAdjust = FALSE;

	while (pos != NULL)
	{
		p = (CXDrawList*)GetNext(pos);
		p->GetLogicBorder(fMinX, fMinY, fMaxX, fMaxY);
	}

	if (!math_IsEqual(fMinX, 999999))
	{
		double dLenY = fMaxY - fMinY;
		double dLenX = fMaxX - fMinX;
		dLenX *= 0.1;
		dLenY *= 0.1;

		if (bUseMngrAxisRange)
		{
			if (!m_bXMin)
				m_fXMin = min(m_fXMin, fMinX - dLenX);

			if (!m_bXMax)
				m_fXMax = max(m_fXMax, fMaxX + dLenX);

			if (!m_bYMin)
				m_fYMin = min(m_fYMin, fMinY - dLenY);

			if (!m_bYMax)
				m_fYMax = max(m_fYMax, fMaxY + dLenY);
		}
		else
		{
			m_fXMin = fMinX - dLenX;
			m_fXMax = fMaxX + dLenX;
			m_fYMin = fMinY - dLenY;
			m_fYMax = fMaxY + dLenY;
		}
	}

	m_oAxis.SetBorder(m_rcBorder);
	ResetAxis();

	LogicPointToDevicePoint();
}

void CXDrawMngrDescartes::ResetAxis()
{
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	m_oAxis.ResetAxis();
}

void CXDrawMngrDescartes::SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	
}

void CXDrawMngrDescartes::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	*ppAxisInterface = &m_oAxis;
}


void CXDrawMngrDescartes::DrawAxis(CDC *pDC)
{
	m_oAxis.DrawAxis(pDC, 1, 0, 0);
}

