#include "stdafx.h"
#include "WzdDlgProgressCtrl.h"

IMPLEMENT_DYNAMIC(CWzdDlgProgressCtrl, CProgressCtrl)
CWzdDlgProgressCtrl::CWzdDlgProgressCtrl()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
	strIcon += "progress.png";
	m_imgProgress.Load(strIcon);
}

CWzdDlgProgressCtrl::~CWzdDlgProgressCtrl()
{

}

void CWzdDlgProgressCtrl::DrawTransparent(CDC* pDC, CRect rc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(m_imgProgress));
	BITMAP bm;
	::GetObject(m_imgProgress, sizeof(BITMAP), &bm);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	pDC->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	if(pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}
	memDC.DeleteDC();
}

BEGIN_MESSAGE_MAP(CWzdDlgProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CWzdDlgProgressCtrl::OnPaint()
{
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);

	CRect rc;
	GetClientRect(rc);
	CRect rcClient = rc;

	long nPos = GetPos();
	long nWidth = rc.Width();

	int nStart = 0;
	int nStop = 0;
	GetRange(nStart, nStop);

	double dPercent = double(nPos - nStart) / double(nStop - nStart);
	rc.right = rc.left + dPercent * rc.Width();

	dc.FillSolidRect(rcClient, RGB(128, 128, 128));
	DrawTransparent(&dc, rc);

	CString strText;
	dc.SetTextColor(RGB(255, 255, 255));
	strText.Format("%d", long(dPercent * 100));
	strText += "%";
	dc.DrawText(strText, rcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

BOOL CWzdDlgProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}