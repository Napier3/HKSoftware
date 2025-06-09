// DrawTimeAxisRange.cpp: implementation of the CDrawTimeAxisRange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawTimeAxisRange.h"
#include "DrawTimeAxis.h"
#include "..\..\..\..\..\Module\API\GloblaDrawFunctions.h"

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
	CDrawBase::SetParentWnd(pParentWnd);
	m_oRangeState.SetParentWnd(pParentWnd);
}

void CDrawTimeAxisRange::SetBorder(const CRect &rect, BOOL bUseClipRect)
{
	CDrawBase::SetBorder(rect);

	m_rcRangeAxis = m_rcBorder;
	CRect rcRangeStateAxis = CreateRangeHorzStateAxisBorder(m_rcBorder.CenterPoint().y+2, m_rcBorder.left, m_rcBorder.right);
	m_oRangeState.SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_HORZ);
	m_rcBorder.InflateRect(RANGESTATEAXIS_BLOCK_HEIGHT1, 0);
	m_oRangeState.GetBlockHeadPos(m_nRangeStateAxisLeft, m_nRangeStateAxisRight);
	CRect rcClip = m_rcBorder;
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

void CDrawTimeAxisRange::Zoom(double dRate) 
{
}

void CDrawTimeAxisRange::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	DrawRectBorder(pDC, m_rcBorder, RGB(0, 0, 0));
	m_oRangeState.Draw(pDC);

	if (m_bDrawTimeRange)
	{
		CString strTime;
		LOGFONT lf = InitLogFont();
#ifdef _UNICODE
		wcscpy(lf.lfFaceName, _T("Tahoma"));
#else
		strcpy(lf.lfFaceName, "Tahoma");
#endif
		lf.lfHeight = m_rcBorder.Height();
		lf.lfWeight = 400;
		CFont font;
		font.CreateFontIndirect(&lf);
		CFont *pOldFont = pDC->SelectObject(&font);

		CRect rcTime = m_rcBorder;
		rcTime.top++;
		rcTime.bottom--;
		rcTime.left += 3;
		int nMode = pDC->SetBkMode(TRANSPARENT);
		TransSecondsToSystemTime(m_dTimeRangeMin, strTime);
		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
		pDC->DrawText(strTime, rcTime, DT_LEFT);
		
		TransSecondsToSystemTime(m_dTimeRangeMax, strTime);
		pDC->DrawText(strTime, &rcTime, DT_CALCRECT);
		long nWidth = rcTime.Width();
		rcTime = m_rcBorder;
		rcTime.right -= 3;
		rcTime.left = rcTime.right - nWidth;
		pDC->DrawText(strTime, rcTime, DT_LEFT);

		pDC->SetBkMode(nMode);
		pDC->SelectObject(pOldFont);
		font.DeleteObject();
	}
}

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
