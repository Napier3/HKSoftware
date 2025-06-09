// HarmHistogram.cpp: implementation of the CHarmHistogram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HarmHistogram.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\Draw\DrawGlobalDef.h"
#include "..\UI\HarmHistogramConfig.h"
#include "..\recordtest\RtDataAttribute.h"
#include "..\recordtest\RtSingleVariable.h"
#include "..\MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CHarmHistogramConfig *g_pHarmHistogramConfig;
CHarmHistogram::CHarmHistogram()
{
	InitAxisSet();
	
	LOGFONT lf = InitLogFont();
	lf.lfHeight = -10;
	lf.lfWeight = 400;
	strcpy(lf.lfFaceName, "Tahoma");
	m_oHarmFont.CreateFontIndirect(&lf);

	lf.lfHeight = -11;
	lf.lfWeight = 400;
	strcpy(lf.lfFaceName, "Tahoma");
	m_oHarmVariableNameFont.CreateFontIndirect(&lf);

	m_nHarmDrawBeginIndex = 0;
	m_nMaxHarmDrawOnce = 0;
	m_bAxisFixed = FALSE;
}

CHarmHistogram::~CHarmHistogram()
{

}

void CHarmHistogram::CalMaxHarmValues()
{
	ASSERT(g_pHarmHistogramConfig != NULL);
	m_bAxisFixed = g_oMR1200SysAnalyseMngr.oHarmHistogram.bAxisFixed;
	double dMaxValue = 0;
	CRtDataAttribute *pAttr = NULL;
	
	if (!m_bAxisFixed)
	{
		void *pos = g_pHarmHistogramConfig->m_listSelHarmAttr.GetHeadPosition();
		
		while (pos != NULL)
		{
			pAttr = (CRtDataAttribute *)g_pHarmHistogramConfig->m_listSelHarmAttr.GetNext(pos);

			//获取运行、保持时计算的谐波值
			double *pdValue = pAttr->GetCalValue();
			
			if (dMaxValue < *pdValue)
			{
				dMaxValue = *pdValue;
			}
			
			if (dMaxValue < 0.01)
			{
				dMaxValue = 0.01;
			}			
		}

		m_oRulerAxis.SetMinMaxVal(0, dMaxValue, 0);
	}
	else
	{
		dMaxValue = g_oMR1200SysAnalyseMngr.oHarmHistogram.dMaxHarmValue;

		if (dMaxValue < 0.01)
		{
			dMaxValue = 0.01;
		}

		m_oRulerAxis.SetMinMaxVal(0, dMaxValue, 0);
	}
}

void CHarmHistogram::SetAxisMaxValue(double dMax)
{
	m_oRulerAxis.SetMinMaxVal(0, dMax, 0);
}

void CHarmHistogram::SetBorder(const CRect &rc)
{
	m_rcBorder.left = rc.left;
	m_rcBorder.top = rc.top;
	m_rcBorder.bottom = rc.Height();
	m_rcBorder.right = rc.Width();
	
	m_rcVariableName = m_rcBorder;
	m_rcVariableName.bottom = m_rcBorder.top + HARM_ANALYSE_DRAW_BOTTOM_GAP + 1;
	
	InitAxis();
	
	m_rcHarmDraw = m_rcBorder;
	m_rcHarmDraw.top = m_rcVariableName.bottom; 
	m_rcHarmDraw.left = m_rcAxis.right + 2;
	m_rcHarmDraw.bottom -= HARM_ANALYSE_DRAW_BOTTOM_GAP;
	
	long nWidth = m_rcHarmDraw.Width();
	m_nMaxHarmDrawOnce = nWidth / HARM_ANALYSE_DRAW_ONE_HARM_MIN_WIDTH;
}

void CHarmHistogram::Draw(CDC *pDC)
{
	m_oRulerAxis.DrawIt(pDC);
	
	//底线
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(m_rcAxis.right, m_rcHarmDraw.bottom);
	pDC->LineTo(m_rcBorder.right, m_rcHarmDraw.bottom);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
	//谐波
	DrawHarm(pDC);	
}

void CHarmHistogram::InitAxisSet()
{
	m_oRulerAxis.SetRulerHalfScaleShow(1);
	m_oRulerAxis.SetRulerTenthScaleShow(0);
	m_oRulerAxis.SetRulerBoderShow(0);
	m_oRulerAxis.SetFrameRightBottomColor(RGB(0,0,0));
	m_oRulerAxis.SetDrawBack(0);
	m_oRulerAxis.SetMinSawGapWidth(20);
	m_oRulerAxis.SetRulerTypeVert();
	m_oRulerAxis.SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
}

void CHarmHistogram::InitAxis()
{	
	m_rcAxis = m_rcBorder;
	m_rcAxis.top = m_rcVariableName.bottom;
	m_rcAxis.left = 15;
	long nWidth = m_oRulerAxis.GetRulerHeight();
	m_rcAxis.right = m_rcAxis.left + nWidth;
	m_rcAxis.bottom -= HARM_ANALYSE_DRAW_BOTTOM_GAP;
	m_oRulerAxis.SetBorder(m_rcAxis);	
}

void CHarmHistogram::DrawHarm(CDC *pDC)
{
	int nMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF crOld ;	
	crOld = pDC->SetTextColor(RGB(0,0,0));	
	CFont *pOldFont = NULL;
	
	//绘制通道名称
	CString str;
	CRtSingleVariable *pSingle = (CRtSingleVariable *)g_pHarmHistogramConfig->m_listUseVariables.GetAt(g_oMR1200SysAnalyseMngr.oHarmHistogram.nChIndex);
	
	if (pSingle != NULL)
	{
		pOldFont = pDC->SelectObject(&m_oHarmVariableNameFont);
		str.Format("%s%s", pSingle->m_strName, GetLanguageStringByID(gs_strLanguage_msHarmAnalyseHistogram));
		pDC->DrawText(str, m_rcVariableName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
	}

	//绘制谐波柱状图
	long nCount = GetHarmDrawCount();
	
	long nEndIndex = m_nHarmDrawBeginIndex + m_nMaxHarmDrawOnce;
	long nBeginIndex = m_nHarmDrawBeginIndex;
	
	if (nCount <= m_nMaxHarmDrawOnce)
	{
		nBeginIndex = 0;
		nEndIndex = nCount;
	}
	else
	{
		if (nEndIndex >= nCount)
		{
			nBeginIndex = nCount - m_nMaxHarmDrawOnce;
			nEndIndex = nBeginIndex + m_nMaxHarmDrawOnce;
		}
	}
	
	long xPos = 0;
	double dGap = m_rcHarmDraw.Width();
	dGap /= (nEndIndex - nBeginIndex);
	xPos = m_rcHarmDraw.left;
	pOldFont = pDC->SelectObject(&m_oHarmFont);

	long nSrcBegin = 0;
	long nSrcLen = 0;
	
	for (long nIndex = nBeginIndex; nIndex < nEndIndex; nIndex++)
	{
		xPos = m_rcHarmDraw.left + (long)(dGap * (nIndex - nBeginIndex));
		DrawHarm(pDC, nIndex, nBeginIndex, xPos);
	}
	
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(crOld);
	pDC->SetBkMode(nMode);
}

void CHarmHistogram::DrawHarm(CDC *pDC, long nIndex, long nBeginIndex, long xPos)
{
	ASSERT (nIndex >=0 && nIndex <= MAX_HARM_INDEX);
	if ( !(nIndex >=0 && nIndex <= MAX_HARM_INDEX) )
	{
		return;
	}

	double dValue = 0;
	ASSERT(g_pHarmHistogramConfig != NULL);
	CRtDataAttribute *pAttr = (CRtDataAttribute *)g_pHarmHistogramConfig->m_listSelHarmAttr.GetAt(nIndex - nBeginIndex);
	ASSERT(pAttr != NULL);
				
	//获取运行、保持时计算的谐波值
	dValue = *pAttr->GetCalValue();

	//次数
	CRect rcHarm;
	rcHarm.left = xPos;
	rcHarm.right = xPos + HARM_ANALYSE_DRAW_ONE_HARM_MIN_WIDTH;
	rcHarm.top = m_rcHarmDraw.bottom;
	rcHarm.bottom = m_rcBorder.bottom;
	CString strName;
	strName.Format("%d", nIndex);
	pDC->DrawText(pAttr->GetHarmNumID(), rcHarm, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	//柱状图
	long nGap = (HARM_ANALYSE_DRAW_ONE_HARM_MIN_WIDTH - HARM_ANALYSE_DRAW_HARM_RECT_WIDTH) / 2;
	rcHarm.left += nGap;
	rcHarm.right -= nGap;
	rcHarm.bottom = m_rcHarmDraw.bottom;
	m_oRulerAxis.LogicPointToDevicePoint(dValue, &rcHarm.top);

	if (rcHarm.top < m_rcHarmDraw.top)
	{
		rcHarm.top = m_rcHarmDraw.top;
	}

	pDC->FillSolidRect(&rcHarm, RGB(0,0,255));
}

long CHarmHistogram::GetHarmDrawCount()
{
	ASSERT(g_pHarmHistogramConfig != NULL);
	long nCount = 0;
	nCount = g_pHarmHistogramConfig->m_listSelHarmAttr.GetCount();
	return nCount;
}
