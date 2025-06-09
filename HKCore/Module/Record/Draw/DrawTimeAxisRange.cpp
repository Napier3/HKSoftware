// DrawTimeAxisRange.cpp: implementation of the CDrawTimeAxisRange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawTimeAxisRange.h"
#include "DrawTimeAxis.h"
#include "../../../Module/API/GloblaDrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawTimeAxisRange::CDrawTimeAxisRange()
{
	TIMEAXIS_RANGESTATEAXIS_HEIGHT = (RANGESTATEAXIS_BLOCK_WIDTH+4);
	m_oRangeState.AttachDrawObject(this);
	m_oRangeState.SetColor(RGB(0,0,255));
	m_pAttachTimeAxis = NULL;
	m_oRangeState.SetLockHead(TRUE);
	m_oRangeState.SetMinLength(10);
	m_nRangeStateAxisLeft = 0;
	m_nRangeStateAxisRight = 0;
	m_dTimeRangeMin = 0;
	m_dTimeRangeMax = 0;
	m_bDrawTimeRange = FALSE;
	m_rcRangeAxis = CRect(0,0,0,0);
}

CDrawTimeAxisRange::~CDrawTimeAxisRange()
{
}

void CDrawTimeAxisRange::AttachTimeAxis(CDrawTimeAxis *pAxis)
{
	m_pAttachTimeAxis = pAxis;
}

void CDrawTimeAxisRange::SetParentWnd(CWnd* pParentWnd)
{
	CXDrawElement::SetParentWnd(pParentWnd);
	m_oRangeState.SetParentWnd(pParentWnd);
}

void CDrawTimeAxisRange::SetBorder(const CRect &rect, BOOL bUseClipRect)
{
	CXDrawElement::SetBorder(rect);

	CRect rcBorder = GetBorder();
	m_rcRangeAxis = rcBorder;
	CRect rcRangeStateAxis = CreateRangeHorzStateAxisBorder(rcBorder.CenterPoint().y+2, rcBorder.left, rcBorder.right);
	m_oRangeState.SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_HORZ);
	rcBorder.InflateRect(RANGESTATEAXIS_BLOCK_HEIGHT1, 0);
	CXDrawElement::SetBorder(rcBorder);
	m_oRangeState.GetBlockHeadPos(m_nRangeStateAxisLeft, m_nRangeStateAxisRight);
	CRect rcClip = rcBorder;
	rcClip.right++;

	if (bUseClipRect)
	{
		m_oRangeState.SetClipRect(rcRangeStateAxis);
	}
}

void CDrawTimeAxisRange::ExpandBorder(long &l, long &t, long &r, long &b)
{
	ASSERT (m_pAttachTimeAxis != NULL);

	if (m_pAttachTimeAxis == NULL)
	{
		return;
	}
	
	long nBegin = 0;
	long nEnd = 0;
	long nWidth = 0;
	double dBegin = 0;
	double dEnd = 0;
	
	nWidth = m_rcRangeAxis.Width()+1;
	m_oRangeState.GetRangeStateAxisRange(nBegin, nEnd);
	dBegin = nBegin - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dEnd = nEnd - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dBegin /= nWidth;
	dEnd /= nWidth;
	m_pAttachTimeAxis->SetAxisRange(dBegin, dEnd);
}

void CDrawTimeAxisRange::Move(long nHor, long nVer )
{
	ASSERT (m_pAttachTimeAxis != NULL);

	if (m_pAttachTimeAxis == NULL)
	{
		return ;
	}

	long nBegin = 0;
	long nEnd = 0;
	long nWidth = 0;
	double dBegin = 0;
	double dEnd = 0;
	
	nWidth = m_rcRangeAxis.Width()+1;
	m_oRangeState.GetRangeStateAxisRange(nBegin, nEnd);
	dBegin = nBegin - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dEnd = nEnd - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dBegin /= nWidth;
	dEnd /= nWidth;
	m_pAttachTimeAxis->SetAxisRange(dBegin, dEnd);
}

void CDrawTimeAxisRange::SetTimeRange(double dMin, double dMax)
{
	m_dTimeRangeMax = dMax;
	m_dTimeRangeMin = dMin;	
}

void CDrawTimeAxisRange::GetAxisRange(double &dCoefLeft, double &dCoefRight)
{
	long nBegin = 0;
	long nEnd = 0;
	long nWidth = 0;

	nWidth = m_rcRangeAxis.Width()+1;
	m_oRangeState.GetRangeStateAxisRange(nBegin, nEnd);
	dCoefLeft = nBegin - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dCoefRight = nEnd - m_nRangeStateAxisLeft;//m_rcRangeAxis.left;
	dCoefLeft /= nWidth;
	dCoefRight /= nWidth;
}

void CDrawTimeAxisRange::SetAxisRange(double dCoefLeft, double dCoefRight)
{
	m_oRangeState.AdjustRangeStateAxisByCoef(dCoefLeft, dCoefRight);
}

void CDrawTimeAxisRange::Zoom(double dRate) 
{

}

void CDrawTimeAxisRange::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rcBorder = GetBorder();
	DrawRectBorder(pDC, rcBorder, RGB(0, 0, 0));
	m_oRangeState.Draw(pDC, fZoomRatio, ptOffset);

	if (m_bDrawTimeRange)
	{
		CString strTime;
		LOGFONT lf = InitLogFont();

		//2021-9-19  lijunqing  ģ�黯�����λ������ͼ��VS2008���� QT ���������´��󣬻���ģʽ
		//error C2664: ��strcpy��: ���ܽ����� 1 �ӡ�WCHAR [32]��ת��Ϊ��char *��
		//strcpy(lf.lfFaceName, "Tahoma");

		lf.lfHeight = m_nHeight;
		lf.lfWeight = 400;
		CFont font;
		font.CreateFontIndirect(&lf);
		CFont *pOldFont = pDC->SelectObject(&font);

		CRect rcTime = rcBorder;
		rcTime.top++;
		rcTime.bottom--;
		rcTime.left += 3;
		int nMode = pDC->SetBkMode(TRANSPARENT);
		TransSecondsToSystemTime(m_dTimeRangeMin, strTime, TRUE);
		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
		pDC->DrawText(strTime, rcTime, DT_LEFT);

		TransSecondsToSystemTime(m_dTimeRangeMax, strTime, TRUE);
		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
		long nWidth = rcTime.Width();
		rcTime = rcBorder;
		rcTime.right -= 5;
		rcTime.left = rcTime.right - nWidth - 5;
		pDC->DrawText(strTime, rcTime, DT_LEFT);

		pDC->SetBkMode(nMode);
		pDC->SelectObject(pOldFont);
		font.DeleteObject();
	}
}

// 
// void CDrawTimeAxisRange::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) 
// {
// 	DrawRectBorder(pDC, m_rcBorder, RGB(0, 0, 0));
// 	m_oRangeState.Draw(pDC);
// 
// 	if (m_bDrawTimeRange)
// 	{
// 		CString strTime;
// 		LOGFONT lf = InitLogFont();
// 		strcpy(lf.lfFaceName, "Tahoma");
// 		lf.lfHeight = m_rcBorder.Height();
// 		lf.lfWeight = 400;
// 		CFont font;
// 		font.CreateFontIndirect(&lf);
// 		CFont *pOldFont = pDC->SelectObject(&font);
// 
// 		CRect rcTime = m_rcBorder;
// 		rcTime.top++;
// 		rcTime.bottom--;
// 		rcTime.left += 3;
// 		int nMode = pDC->SetBkMode(TRANSPARENT);
// 		TransSecondsToSystemTime(m_dTimeRangeMin, strTime);
// 		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
// 		pDC->DrawText(strTime, rcTime, DT_LEFT);
// 		
// 		TransSecondsToSystemTime(m_dTimeRangeMax, strTime);
// 		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
// 		long nWidth = rcTime.Width();
// 		rcTime = m_rcBorder;
// 		rcTime.right -= 3;
// 		rcTime.left = rcTime.right - nWidth;
// 		pDC->DrawText(strTime, rcTime, DT_LEFT);
// 
// 		pDC->SetBkMode(nMode);
// 		pDC->SelectObject(pOldFont);
// 		font.DeleteObject();
// 	}
// }

LONG CDrawTimeAxisRange::MouseMove(UINT nFlags, CPoint &point)
{
	return m_oRangeState.MouseMove(nFlags, point);
}

LONG CDrawTimeAxisRange::LButtonDown(UINT nFlags, CPoint &point)
{
	return m_oRangeState.LButtonDown(nFlags, point);
}

LONG CDrawTimeAxisRange::LButtonUp(UINT nFlags, CPoint &point)
{
	return m_oRangeState.LButtonUp(nFlags, point);
}

LONG CDrawTimeAxisRange::RButtonDown(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawTimeAxisRange::RButtonUp(UINT nFlags, CPoint &point)
{
	return 0;
}

BOOL CDrawTimeAxisRange::PointInRgn(CPoint &pt)
{
	return TRUE;
}
