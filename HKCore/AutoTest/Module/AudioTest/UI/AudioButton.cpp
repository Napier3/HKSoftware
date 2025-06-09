#include "stdafx.h"
#include "AudioButton.h"

IMPLEMENT_DYNAMIC(CAudioButton, CButton)
CAudioButton::CAudioButton()
{

}

CAudioButton::~CAudioButton()
{

}

void CAudioButton::LoadBitmap(CString strFilePath)
{
	m_strImageFilePath = strFilePath;
}

void CAudioButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	ModifyStyle(WS_CLIPCHILDREN,0);
	ModifyStyle(WS_CLIPSIBLINGS,0);
	CButton::PreSubclassWindow();
}

void CAudioButton::DrawTransparent(HDC hdcDest,int nWidthDest,int nHeightDest,
									HDC hdcSrc,int nWidthSrc,int nHeightSrc,COLORREF crTransparent)
{
	// ��������λͼ
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest); 
	// ������ɫ����λͼ
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);         
	HDC     hImageDC = CreateCompatibleDC(hdcDest);
	HDC     hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// ��ԴDC�е�λͼ��������ʱDC��
	SetBkMode(hImageDC, TRANSPARENT);
	SetStretchBltMode(hImageDC, STRETCH_HALFTONE);
	StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, 0, 0, nWidthSrc, nHeightSrc, SRCCOPY);

	// ����͸��ɫ
	SetBkColor(hImageDC, RGB(255, 255, 255));

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "��"����,��������Ч��
	BitBlt(hdcDest, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP); 
}

void CAudioButton::DrawTransparent(CDC* pDC, HBITMAP hBitmap)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(hBitmap));
 	BITMAP bmp;
 	::GetObject(hBitmap, sizeof(BITMAP), &bmp);
 	COLORREF crTransparent = memDC.GetPixel(0, 0);
	CRect rc;
 	GetClientRect(rc);
 	DrawTransparent(pDC->m_hDC, rc.Width(), rc.Height(), 
 	memDC.m_hDC, bmp.bmWidth, bmp.bmHeight, crTransparent);
	if(pOldBitmap)
	{
	memDC.SelectObject(pOldBitmap);
	}
}

void CAudioButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CRect rc = lpDIS->rcItem;

	if(m_strImageFilePath.GetLength())
	{
		CImage img;
		img.Load(m_strImageFilePath);

		CDC* pDC = GetDC();
		DrawTransparent(pDC, img);
 
		CFont newfont;
		CFont *oldFont;
		newfont.CreateFont(18,6,0,0,0,FALSE,FALSE,0,ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
			DEFAULT_PITCH|FF_SWISS,_T("΢���ź�"));
		oldFont=pDC->SelectObject(&newfont);

		CString strText;
		GetWindowText(strText);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		rc.top = rc.bottom - 18;
		pDC->DrawText(strText, rc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

		ReleaseDC(pDC);
	}
}

BEGIN_MESSAGE_MAP(CAudioButton, CButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CAudioButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}