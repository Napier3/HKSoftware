//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawMngrLogarithm.cpp  CXDrawMngrLogarithm


#include "stdafx.h"
#include "XDrawMngrLogarithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

float g_fLogarithmMinXCoef = 0.5f;
float g_fLogarithmMaxXCoef = 1.1f;
float g_fLogarithmMinYCoef = 0.5f;
float g_fLogarithmMaxYCoef = 1.1f;

CXDrawMngrLogarithm::CXDrawMngrLogarithm()
{
	//初始化属性
	SetAxisName(_T("X"), _T("Y"), _T("x-y"));
	m_fXMax = 4;
	m_fYMax = 4;
	m_fXMin = -2;
	m_fYMin = -2;

	//初始化成员变量
	InitAxis();
}

CXDrawMngrLogarithm::~CXDrawMngrLogarithm()
{
}

void CXDrawMngrLogarithm::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	m_oAxis.SetXAxisName(strXAxisName);
	m_oAxis.SetYAxisName(strYAxisName);
	m_oAxis.SetAxisTitle(strAxisTitle);
}

void CXDrawMngrLogarithm::SetAxisMaxUnitCount(long nXAxisUnitCount, long nYAxisUnitCount)
{
	m_oAxis.SetXAxisMaxUnitCount(nXAxisUnitCount);
	m_oAxis.SetYAxisMaxUnitCount(nYAxisUnitCount);
}

void CXDrawMngrLogarithm::InitAxis()
{
	SetAxisMaxUnitCount(40, 40);
	m_oAxis.SetAxisXYUnitLock(1);
// 	m_oAxis.SetLeftGap(0);
// 	m_oAxis.SetTopGap(6);
// 	m_oAxis.SetRightGap(5);
// 	m_oAxis.SetBottomGap(0);
	m_oAxis.SetYAxisAreaWidth(45);
	m_oAxis.SetBorder(m_rcBorder);	
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	//m_oAxis.ResetAxis();
}

void CXDrawMngrLogarithm::AdjustAxis(BOOL bUseMngrAxisRange)
{
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
		m_fXMin = fMinX*g_fLogarithmMinXCoef/*0.5*/;//zhouhj 2023.7.13  改为参数可配方式,便于调整系数显示刻度值
		m_fXMax = fMaxX*g_fLogarithmMaxXCoef/*1.1*/;
		m_fYMin = fMinY*g_fLogarithmMinYCoef/*0.5*/;
		m_fYMax = fMaxY*g_fLogarithmMaxYCoef/*1.1*/;

		//转换成逻辑坐标的值
		if (m_fXMin <= 0)
		{
			m_fXMin = 0.001;
		}
		if (m_fYMin <= 0)
		{
			m_fYMin = 0.001;
		}

		m_fXMin = log10(m_fXMin);
		m_fXMax = log10(m_fXMax);
		m_fYMin = log10(m_fYMin);
		m_fYMax = log10(m_fYMax);

// 		m_fXMax = ceil(m_fXMax);
// 		m_fYMax = ceil(m_fYMax);
	}

	m_oAxis.SetBorder(m_rcBorder);
	ResetAxis();

	LogicPointToDevicePoint();
}

void CXDrawMngrLogarithm::ResetAxis()
{
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	m_oAxis.ResetAxis();
}

void CXDrawMngrLogarithm::SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	
}

void CXDrawMngrLogarithm::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	*ppAxisInterface = &m_oAxis;
}


void CXDrawMngrLogarithm::DrawAxis(CDC *pDC)
{
	m_oAxis.DrawAxis(pDC, 1, 0, 0);
}

void CXDrawMngrLogarithm::SetAxisXYUnitLock(BOOL bUnLock)
{
	m_oAxis.SetAxisXYUnitLock(bUnLock);
}
