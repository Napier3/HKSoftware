// DrawSysTime.cpp: implementation of the CDrawSysTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawSysTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawSysTime::CDrawSysTime()
{
	m_crColor = RGB(0,0,0);
	m_nDrawWidth = 120;
	m_pParentWnd =NULL;
	CTime oTime =CTime::GetCurrentTime();
	m_oTime.wYear = oTime.GetYear();
	m_oTime.wMonth = oTime.GetMonth();
	m_oTime.wDay  = oTime.GetDay();
	m_oTime.wHour = oTime.GetHour();
	m_oTime.wMinute = oTime.GetMinute();
	m_oTime.wSecond = oTime.GetSecond();
	m_oTime.wMicroseconds = 0;
	m_oTime.wMilliseconds = 0;
	m_rcTime = CRect(0,0,0,0);
}

CDrawSysTime::~CDrawSysTime()
{
}

void CDrawSysTime::GetSysTime(RTTIME& oTime)
{
	m_oTime = oTime;
	m_pParentWnd->InvalidateRect(m_rcTime,FALSE);
}

void CDrawSysTime::Draw(CDC* pDC)
{
	CFont font;
	font.CreateFontIndirect(&MrDraw::g_lfDrawVariableName);
	CFont *pOldFont = pDC->SelectObject(&font);

	int nMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF cr = pDC->SetTextColor(m_crColor); 
	CString str;
	str.Format(_T("%d-%02d-%02d %02d:%02d:%02d"),m_oTime.wYear,m_oTime.wMonth,
		m_oTime.wDay,m_oTime.wHour,m_oTime.wMinute,m_oTime.wSecond);
	pDC->DrawText(str,m_rcTime,DT_CENTER | DT_VCENTER);
	pDC->SetBkMode(nMode);
	pDC->SetTextColor(cr);
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
	pOldFont = NULL;
}
