#include "stdafx.h"
#include "WzdDlgButton.h"

IMPLEMENT_DYNAMIC(CWzdDlgButton, CButton)
CWzdDlgButton::CWzdDlgButton()
{
	m_bIsHover = FALSE;
	m_bEnabled = TRUE;
	m_bChecked = FALSE;
	m_bPressed = FALSE;
	m_bIsHold = FALSE;
	m_bVisible = TRUE;
	m_bReadOnly = FALSE;
	m_bDrawTrans = FALSE;
	m_pData = NULL;

	m_bIsImgMode = FALSE;
	m_nTextMode = DT_VCENTER | DT_SINGLELINE | DT_CENTER;
	m_txtColor = RGB(0, 0, 0);
	m_backColor = RGB(255, 255, 255);
}

CWzdDlgButton::~CWzdDlgButton()
{
// 	if(!m_imgNor.IsNull())
// 	{
// 		m_imgNor.Destroy();
// 	}	
// 	if(!m_imgSel.IsNull())
// 	{
// 		m_imgSel.Destroy();
// 	}	
// 	if(!m_imgHot.IsNull())
// 	{
// 		m_imgHot.Destroy();
// 	}	
// 	if(!m_imgDis.IsNull())
// 	{
// 		m_imgDis.Destroy();
// 	}	
}

void CWzdDlgButton::LoadImage(CString strNor, CString strSel, CString strHot, CString strDis)
{
	m_imgNor = strNor;
	m_imgSel = strSel;
	m_imgHot = strHot;
	m_imgDis = strDis;
	
//	m_imgNor.Load(strNor);
// 	if (strSel.GetLength())
// 	{
// 		m_imgSel.Load(strSel);
// 	}
// 	if (strHot.GetLength())
// 	{
// 		m_imgHot.Load(strHot);
// 	}
// 	if (strDis.GetLength())
// 	{
// 		m_imgDis.Load(strDis);
// 	}
}

void CWzdDlgButton::SetEnabled(BOOL bEnable)
{
	if(!bEnable)
	{
		m_bEnabled = FALSE;
		m_bIsHold = FALSE;
		EnableWindow(FALSE);
	}
	else
	{
		m_bEnabled = TRUE;
		EnableWindow(TRUE);
	}
}

void CWzdDlgButton::SetVisible(BOOL bVisible)
{
	 m_bVisible = bVisible;
	 ShowWindow(bVisible);
}

BEGIN_MESSAGE_MAP(CWzdDlgButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

BOOL CWzdDlgButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

LRESULT CWzdDlgButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bIsHover = FALSE;
	Invalidate();
	return 0;
}

LRESULT CWzdDlgButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_bIsHover = TRUE;
	Invalidate();
	return 0;
}

void CWzdDlgButton::OnMouseMove(UINT nFlags, CPoint point)  
{
	if (!m_bIsHover)
	{
		//������봰ʱ������WM_MOUSEHOVER��WM_MOUSELEAVE ��Ϣ
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bIsHover = _TrackMouseEvent(&tme);
	}

	CWnd::OnMouseMove(nFlags,   point);
}

void CWzdDlgButton::LButtonUp(UINT nFlags, CPoint point)
{
	m_bPressed = FALSE;
	Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}

void CWzdDlgButton::LButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bReadOnly)
	{
		m_bPressed = TRUE;
	}
	Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}

void CWzdDlgButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	LButtonUp(nFlags, point);
}

void CWzdDlgButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	LButtonDown(nFlags, point);
}

void CWzdDlgButton::PreSubclassWindow() 
{
	if(GetButtonStyle() & BS_CHECKBOX)
	{
		m_bChecked = TRUE;
	}
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CWzdDlgButton::DrawTransparent(HDC hdcDest,int nWidthDest,int nHeightDest,
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

void CWzdDlgButton::DrawPng(CDC* pDC, HBITMAP hBitmap, CRect rc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(hBitmap));
	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	pDC->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	if(pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}
	memDC.DeleteDC();
}

void CWzdDlgButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rc = lpDIS->rcItem;

	if(m_bIsImgMode)
	{
		CImage img;
		if(m_bIsHold)
		{
			//����Ǳ��ְ��µ�ģʽ��ֻ��Clickʱ��ͼƬ
			img.Load(m_imgSel);
			DrawPng(pDC, img, rc);
			
		}
		else if (m_bChecked)
		{
			//�����ѡ��
		}
		else
		{
			//��������ͼƬ
			//����ͼƬ
			if (!m_bEnabled || !IsWindowEnabled())
			{
				m_bEnabled = IsWindowEnabled();
				//���������
				//�������ͼ���Ѿ�������
				img.Load(m_imgDis);
				DrawPng(pDC, img, rc);
			}
			else
			{
				if(m_bPressed)
				{
					img.Load(m_imgSel);
					DrawPng(pDC, img, rc);
				}
				else
				{
					if(m_bIsHover)
					{
						img.Load(m_imgHot);
						DrawPng(pDC, img, rc);
					}
					else
					{
// 						if(m_bDrawTrans)
// 						{
// 							pDC->FillSolidRect(rc, m_backColor);
// 							DrawTransparent(pDC->GetSafeHdc(), rc.Width(), rc.Height(), 
// 									m_imgNor.GetDC(), m_imgNor.GetWidth(), m_imgNor.GetHeight(), RGB(255,255,255));
// 						}
// 						else
// 						{
							img.Load(m_imgNor);
							DrawPng(pDC, img, rc);
//						}
					}
				}
			}
		}
		img.Destroy();
	}

	CString strText;
	GetWindowText(strText);
	pDC->SetTextColor(m_txtColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(strText, rc, m_nTextMode);

	ReleaseDC(pDC);
}