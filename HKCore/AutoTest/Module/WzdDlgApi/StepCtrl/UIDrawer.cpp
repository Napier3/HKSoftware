#include "stdafx.h"
#include "UIDrawer.h"
#include "../../../iSmartTestWzd/Resource.h"

CUIDrawer::CUIDrawer()
{
	m_Font = NULL;
	m_pData = NULL;
	m_nSize = 0;
	m_nFontIndex = 0;
	m_hFontRes = NULL;

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	m_pFontCollection = new PrivateFontCollection;
	m_pFontFamily = new Gdiplus::FontFamily;
}

CUIDrawer::~CUIDrawer()
{
	if (m_Font != NULL)
	{
		delete m_Font;
		m_Font = NULL;
	}

	if (m_pFontCollection != NULL)
	{
		delete m_pFontCollection;
		m_pFontCollection = NULL;
	}

	if (m_pFontFamily != NULL)
	{
		delete m_pFontFamily;
		m_pFontFamily = NULL;
	}

	if (m_hFontRes != NULL)
	{
		RemoveFontMemResourceEx(m_hFontRes);
		m_hFontRes = NULL;
	}

	if (!m_strFontFile.IsEmpty())
		RemoveFontResourceEx(m_strFontFile, FR_PRIVATE, NULL);

	GdiplusShutdown(gdiplusToken);
}

void CUIDrawer::DrawPng(CDC* pDC, HBITMAP hBitmap, CRect rc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(hBitmap));
	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	pDC->StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	if(pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}
	memDC.DeleteDC();
}

BOOL CUIDrawer::LoadFont(UINT  lpszResource, LPCTSTR lpszType/* = _T("ttf")*/)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hResrc = ::FindResource(hInst, MAKEINTRESOURCE(lpszResource), lpszType);
	if (hResrc == NULL)
		return FALSE;

	m_nSize = SizeofResource(hInst, hResrc);
	m_pData = LoadResource(hInst, hResrc);
	if (m_pData == NULL)
		return FALSE;

	// GDI
	m_nFontIndex = 0;
	m_hFontRes = AddFontMemResourceEx(
		m_pData,			// font resource
		m_nSize,			// number of bytes in font resource 
		NULL,				// Reserved. Must be 0.
		&m_nFontIndex);     // number of fonts installed
	if (m_hFontRes == NULL)
		return FALSE;

	// GDI+
	Gdiplus::Status nResults = m_pFontCollection->AddMemoryFont(m_pData, m_nSize);
	if (nResults != Gdiplus::Ok)
		return FALSE;

	int nNumFound = 0;
	m_pFontCollection->GetFamilies(1, m_pFontFamily, &nNumFound);
	if (nNumFound <= 0)
		return FALSE;

	return TRUE;
}

HFONT CUIDrawer::FontToHFONTA(HWND hWnd)
{
	if (m_Font == NULL || hWnd == NULL)
		return NULL;

	int nNumFound = 0;
	m_pFontCollection->GetFamilies(1, m_pFontFamily, &nNumFound);
	if (nNumFound <= 0)
		return NULL;

	Graphics g(hWnd);
	LOGFONTA logFont;
	m_Font->GetLogFontA(&g, &logFont);
	logFont.lfQuality = CLEARTYPE_QUALITY;
	logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	logFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfPitchAndFamily = DEFAULT_PITCH;
	return ::CreateFontIndirectA(&logFont);
}

// GDI+ -> GDI
HFONT CUIDrawer::FontToHFONTW(HWND hWnd)
{
	if (m_Font == NULL || hWnd == NULL)
		return NULL;

	Graphics g(hWnd);
	LOGFONTW logFont;

	m_Font->GetLogFontW(&g, &logFont);
	logFont.lfQuality = CLEARTYPE_QUALITY;
	logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	logFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfPitchAndFamily = DEFAULT_PITCH;
	return ::CreateFontIndirectW(&logFont);
}

// GDI+ -> GDI
HFONT CUIDrawer::GetSafeHFONT(HWND hWnd)
{
#ifdef _UNICODE
	return FontToHFONTW(hWnd);
#else
	return FontToHFONTA(hWnd);
#endif // _UNICODE
}


// GDI+
Gdiplus::Font* CUIDrawer::SetFontStyle(Gdiplus::FontStyle fontstyle/* = FontStyleRegular*/, REAL nFontSize/* = 14.0F*/)
{
	int nNumFound = 0;
	m_pFontCollection->GetFamilies(1, m_pFontFamily, &nNumFound);
	if (nNumFound <= 0)
		return NULL;

	if (m_Font != NULL)
	{
		delete m_Font;
		m_Font = NULL;
	}

	m_Font = new Gdiplus::Font(m_pFontFamily, nFontSize, fontstyle, UnitPixel);
	return m_Font;
}

// GDI
Gdiplus::FontFamily* CUIDrawer::FontFamily()
{
	int nNumFound = 0;
	m_pFontCollection->GetFamilies(1, m_pFontFamily, &nNumFound);
	if (nNumFound <= 0)
		return NULL;

	return m_pFontFamily;
}

BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
	CFont* pFont = (CFont*)lParam;
	CWnd* pWnd = CWnd::FromHandle(hwndChild);
	pWnd->SetFont(pFont);
	return TRUE;
}

CFont* CUIDrawer::GetUIFont(HWND hWnd, Gdiplus::FontStyle fontstyle, REAL nFontSize)
{
	LoadFont(IDR_TTF, "ttf");
	SetFontStyle(fontstyle, nFontSize);
	CFont* pFont = CFont::FromHandle(GetSafeHFONT(hWnd));
	return pFont;
}

BEGIN_MESSAGE_MAP(CUIButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUIButton, CButton)
CUIButton::CUIButton()
{
	m_tagState = normal;
}

CUIButton::~CUIButton()
{

}

void CUIButton::InitUI(const CString& strNormalName, const CString& strHoverName)
{
	CString strPath = _P_GetResourcePath();
	strPath += "iSmartTestWzd/test/";
	m_strNormalPic = strPath + strNormalName;
	m_strHoverPic = strPath + strHoverName;
}

BOOL CUIButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

LRESULT CUIButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_tagState = normal;
	Invalidate();
	return 0;
}

LRESULT CUIButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_tagState = hover;
	Invalidate();
	return 0;
}

void CUIButton::OnMouseMove(UINT nFlags, CPoint point)  
{
	if (m_tagState != hover)
	{
		//鼠标移入窗时，请求WM_MOUSEHOVER和WM_MOUSELEAVE 消息
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		_TrackMouseEvent(&tme);
	}

	CWnd::OnMouseMove(nFlags,   point);
}

void CUIButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CUIButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rc = lpDIS->rcItem;

	CImage img;
	switch(m_tagState)
	{
	case normal:
		img.Load(m_strNormalPic); 
		break;	
	case hover:
		img.Load(m_strHoverPic); 
		break;	
	default:
		break;
	}
	DrawPng(pDC, img, rc);
	img.Destroy();

	ReleaseDC(pDC);
}

BEGIN_MESSAGE_MAP(CUITabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUITabCtrl, CTabCtrl)
CUITabCtrl::CUITabCtrl()
{
	m_nCurSel = 0;
	m_fFontPointSize = 10.5;
	m_nTabPadding = 10;
	m_nFontWidth = 6;
}

CUITabCtrl::~CUITabCtrl()
{

}

void CUITabCtrl::InitUI(COLORREF clrBackground, COLORREF clrSelForeground, COLORREF clrUnselForeground)
{
	m_clrBackground = clrBackground;
	m_clrSelForeground = clrSelForeground;
	m_clrUnselForeground = clrUnselForeground;
}

void CUITabCtrl::AddItem(CString strText)
{
	tagTabItem item;
	item.m_strText = strText;
	item.m_ItemWidth = strText.GetLength() * m_nFontWidth + 2 * m_nTabPadding;
	m_mapTabItems.insert(std::pair<long, tagTabItem>(m_mapTabItems.size(), item));
}

int CUITabCtrl::GetCurSel()
{
	return m_nCurSel;
}

int CUITabCtrl::SetCurSel(int nItem)
{
	if(nItem >= m_mapTabItems.size() || nItem < 0)
	{
		m_nCurSel = 0;
	}
	else
	{
		m_nCurSel = nItem;
	}

	CTabCtrl::SetCurSel(nItem);

	return m_nCurSel;
}

BOOL CUITabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CUITabCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//ModifyStyle(0, TCS_OWNERDRAWFIXED);
	CTabCtrl::PreSubclassWindow();
}

void CUITabCtrl::OnPaint()
{
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);

	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, m_clrBackground);

	CFont* pAlbbFont = GetUIFont(m_hWnd, FontStyleBold, m_fFontPointSize);
	CFont* pOldFont = dc.SelectObject(pAlbbFont);

	long nLeftPos = 0;
	std::map<long, tagTabItem>::iterator iter = m_mapTabItems.begin();
	for (;iter != m_mapTabItems.end(); iter++)
	{
		tagTabItem item = iter->second;
		CRect rcTab(nLeftPos, rc.top, nLeftPos + item.m_ItemWidth, rc.bottom);

		dc.SetTextColor(m_clrUnselForeground);
		if(m_nCurSel == iter->first)
		{
			dc.SetTextColor(m_clrSelForeground);
		}

		dc.DrawText(item.m_strText, rcTab, DT_VCENTER | DT_CENTER);
		nLeftPos += item.m_ItemWidth;
	}

	dc.SelectObject(pOldFont);
	//font.DeleteObject();
}

void CUITabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	long nX = point.x;
	std::map<long, tagTabItem>::iterator iter = m_mapTabItems.begin();
	for (;iter != m_mapTabItems.end(); iter++)
	{
		tagTabItem item = iter->second;
		nX -= item.m_ItemWidth;
		if(nX < 0)
		{
			m_nCurSel = iter->first;
			break;
		}
	}

	CTabCtrl::OnLButtonDown(nFlags, point);
}

BEGIN_MESSAGE_MAP(CUIComboBox, CComboBox)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUIComboBox, CComboBox)

CUIComboBox::CUIComboBox()
{

}

CUIComboBox::~CUIComboBox()
{

}

void CUIComboBox::InitUI(COLORREF clrBorder, COLORREF clrArrowBackground)
{
	m_clrBorder = clrBorder;
	m_clrArrowBackground = clrArrowBackground;
}

BOOL CUIComboBox::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

int CUIComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	int nComp = 0;
	ASSERT(lpCompareItemStruct->CtlType == ODT_COMBOBOX);
	LPCTSTR lpszText1 = (LPCTSTR) lpCompareItemStruct->itemData1;
	ASSERT(lpszText1 != NULL);
	LPCTSTR lpszText2 = (LPCTSTR) lpCompareItemStruct->itemData2;
	ASSERT(lpszText2 != NULL);

	if (NULL != lpszText1 && NULL != lpszText2)
	{
		nComp = _tcscmp(lpszText2, lpszText1);    
	}

	return nComp;
}

void CUIComboBox::OnPaint()
{
	CPaintDC dc(this);
	CDC* pDC = &dc;
	//绘制客户区
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());

	CBitmap mNewBmp;
	CRect rc;
	GetClientRect(&rc);

	//画整个客户区域
	mNewBmp.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
	CBitmap* pOldBmp = dMemDC.SelectObject(&mNewBmp);
	CPen pen(PS_SOLID,1,m_clrBorder);
	CPen *pOldPen = dMemDC.SelectObject(&pen);
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(m_clrBorder);
	dMemDC.SelectObject(&bkBrush);
	dMemDC.Rectangle(rc);

	//画右边的三角形按钮
	CRect rcEnd(rc);
	rcEnd.left = rc.right - 20;
	CBrush bkBrushRect;
	bkBrushRect.CreateSolidBrush(m_clrArrowBackground);
	dMemDC.SelectObject(&bkBrushRect);
	dMemDC.Rectangle(rcEnd);
	//画三角形
	CRgn rgn;
	CPoint ptAngle[3];
	int angleSideWidth = 8;//三角形边长
	//第一个点的坐标
	ptAngle[0].x = rcEnd.left+rcEnd.Width()/2-angleSideWidth/2;
	ptAngle[0].y = rcEnd.top+rcEnd.Height()/2-2;
	//第二个点的坐标
	ptAngle[1].x = ptAngle[0].x + angleSideWidth;
	ptAngle[1].y = ptAngle[0].y;
	//第三个点的坐标
	ptAngle[2].x = rcEnd.left+rcEnd.Width()/2;
	ptAngle[2].y = ptAngle[0].y + 5;
	CBrush brushAngle;
	rgn.CreatePolygonRgn(ptAngle, 3, ALTERNATE); //创建区域  
	brushAngle.CreateSolidBrush(m_clrBorder); //创建画刷
	dMemDC.FillRgn(&rgn, &brushAngle); //填充区域
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,
		rc.left ,rc.top, SRCCOPY);

	//画选择时Label中的字符串
	CString strText;
	GetWindowText(strText);
	CRect rcText(rc);
	rcText.right = rc.right - 21;
	rcText.top += 1;
	rcText.bottom -= 1;
	rcText.left += 1;
	CFont* pFont = GetParent()->GetFont();
	pDC->SelectObject(pFont);
	pDC->FillSolidRect(rcText, RGB(255,255,255));
	rcText.top += 1;
	rcText.left += 1;
	pDC->DrawText(strText, rcText, DT_VCENTER | DT_LEFT);

	//恢复
	dMemDC.SelectObject(pOldBmp);
	dMemDC.SelectObject(pOldPen);
	pOldPen->DeleteObject();
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
	bkBrush.DeleteObject();
	bkBrushRect.DeleteObject();
	brushAngle.DeleteObject();
}

BEGIN_MESSAGE_MAP(CUIEdit, CEdit)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUIEdit, CEdit)

CUIEdit::CUIEdit()
{

}
CUIEdit::~CUIEdit()
{

}

void CUIEdit::InitUI(COLORREF clrBorder)
{
	m_clrBorder = clrBorder;
}

BOOL CUIEdit::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CUIEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	CRect rc;
	GetClientRect(rc);
	CBrush brush(m_clrBorder);
	pDC->FrameRect(rc, &brush);
	return NULL;
}

BEGIN_MESSAGE_MAP(CUITreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CUITreeCtrl::OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CExBaseListTreeCtrl::OnNMDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CExBaseListTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUITreeCtrl, CTreeCtrl)

CUITreeCtrl::CUITreeCtrl()
{

}
CUITreeCtrl::~CUITreeCtrl()
{

}

void CUITreeCtrl::InitUI(const CString& strFoldName, const CString& strDisFoldName,
						 const CString& strExpandName, const CString& strDisExpandName)
{
	CString strPath = _P_GetResourcePath();
	strPath += "iSmartTestWzd/test/";
	m_strFoldPic = strPath + strFoldName;
	m_strDisFoldPic = strPath + strDisFoldName;
	m_strExpandPic = strPath + strExpandName;
	m_strDisExpandPic = strPath + strDisExpandName;
}

void CUITreeCtrl::DrawCustom(NMTVCUSTOMDRAW* pCustomDraw)
{
	int nHPos = GetScrollPos(SB_HORZ);
	int nVPos = GetScrollPos(SB_VERT);

	HTREEITEM hItem = (HTREEITEM)pCustomDraw->nmcd.dwItemSpec;
	CRect rc = pCustomDraw->nmcd.rc;

	BOOL bItemState = GetItemState(hItem, TVIS_EXPANDED);

	long nWidth = rc.Height();
	if(ItemHasChildren(hItem))
	{
		CRect rcImg = CRect(rc.left + nWidth * pCustomDraw->iLevel,
			rc.top, rc.left + nWidth * (pCustomDraw->iLevel + 1), rc.bottom);

		rcImg.left -= nHPos;
		rcImg.right -= nHPos; 
		rcImg.top -= nVPos;
		rcImg.bottom -= nVPos;

		CDC* pDC = GetDC();

		if(TVIS_EXPANDED & bItemState)
		{
			//注释掉的原因是Item好像没有专门去设置过这个标记,获取的值都是不对的
// 			BOOL bItemDisable = GetItemState(hItem, TVIS_DISABLED);
// 			if(bItemDisable & TVIS_DISABLED)
// 			{
// 				CImage img;
// 				img.Load(m_strDisFoldPic);
// 				DrawPng(pDC, img, rcImg);
// 				img.Destroy();
// 			}
// 			else
// 			{
				CImage img;
				img.Load(m_strFoldPic);
				DrawPng(pDC, img, rcImg);
				img.Destroy();
//			}
		}
		else
		{
// 			BOOL bItemDisable = GetItemState(hItem, TVIS_DISABLED);
// 			if(bItemDisable & TVIS_DISABLED)
// 			{
// 				CImage img;
// 				img.Load(m_strDisExpandPic);
// 				DrawPng(pDC, img, rcImg);	
// 				img.Destroy();
// 			}
// 			else
// 			{
				CImage img;
				img.Load(m_strExpandPic);
				DrawPng(pDC, img, rcImg);	
				img.Destroy();
//			}
		}
	}

	CString strText = GetItemText(hItem);
	rc.left += nWidth * (pCustomDraw->iLevel + 1) + 10;
	rc.right += 10;
	rc.left -= nHPos;
	rc.top -= nVPos;
	rc.bottom -= nVPos;
	DrawText(pCustomDraw->nmcd.hdc, strText, -1, &rc, DT_SINGLELINE | DT_VCENTER);
}

BOOL CUITreeCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, COLOR_WHITE);
	return TRUE;
}

void CUITreeCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMTVCUSTOMDRAW* pCustomDraw = (NMTVCUSTOMDRAW*)pNMHDR;

	switch(pCustomDraw->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		{
			// 双缓冲绘制
			DrawCustom(pCustomDraw);
			*pResult = CDRF_SKIPDEFAULT;
			break;
		}
	default:
		break;
	}
}

void CUITreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags;
	HTREEITEM hItem = HitTest(point, &uFlags);

	if(hItem != NULL && (uFlags & (TVHT_ONITEM | TVHT_ONITEMRIGHT)))
	{
		long nState = GetItemState(hItem, TVIS_EXPANDED);
		if(nState & TVIS_EXPANDED)
		{
			Expand(hItem, TVE_COLLAPSE);
		}
		else
		{
			Expand(hItem, TVE_EXPAND);
		}

		Invalidate();
	}

	CExBaseListTreeCtrl::OnLButtonDown(nFlags, point);
}

void CUITreeCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CExBaseListTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}

void CUITreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CExBaseListTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}

BEGIN_MESSAGE_MAP(CUIGrid, CGridCtrl)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUIGrid, CGridCtrl)

CUIGrid::CUIGrid()
{

}

CUIGrid::~CUIGrid()
{

}

void CUIGrid::InitUI(COLORREF clrHeaderBk, COLORREF clrBorder, COLORREF clrForeground, COLORREF clrBackground)
{
	m_crBkColor = clrBackground;
	m_crTextColor = clrForeground;
	m_crTitleTextBkColor = clrHeaderBk;
	m_crGridColour = clrBorder;
}

BEGIN_MESSAGE_MAP(CUIDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CUIDialog, CDialog)

CUIDialog::CUIDialog(UINT nIDTemplate, CWnd* pParent)
	: CDialog(nIDTemplate, pParent)
{
	m_clrBackground = RGB(255, 255, 255);
	m_clrForeground = RGB(0, 0, 0);
}

CUIDialog::~CUIDialog()
{

}

void CUIDialog::InitUI(COLORREF clrBackground, COLORREF clrForeground)
{
	m_clrBackground = clrBackground;
	m_clrForeground = clrForeground;
}

void CUIDialog::SetWindowTitle(const CString& strTitle)
{
	LONG_PTR style = ::GetWindowLongPtr(m_hWnd, GWL_STYLE);  
	style = style & ~WS_BORDER;
	::SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	CRect rc;
	GetClientRect(rc);

	m_txtTitle.Create(strTitle, WS_CHILD | WS_VISIBLE, CRect(5, 0, rc.Width() - 20, 20), this, 99998);
	CFont* pAlbbFont = GetUIFont(m_txtTitle.m_hWnd, FontStyleBold);
	m_txtTitle.SetFont(pAlbbFont);

	//m_btnCloseDlg.Create(NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(rc.Width() - 20, 0, rc.Width(), 20), this, 99999);
	//m_btnCloseDlg.InitUI("normal关闭.png", "hover关闭.png");
}

void CUIDialog::MoveChildWindow(CWnd* pWnd)
{
	if(pWnd)
	{
		CRect rc;
		pWnd->GetWindowRect(rc);
		ScreenToClient(rc);

		pWnd->SetWindowPos(NULL, rc.left, rc.top + 20, 0, 0, SWP_NOSIZE);
	}
}

BOOL CUIDialog::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, m_clrBackground);
	return TRUE;
}

HBRUSH CUIDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH brush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetTextColor(m_clrForeground);
		pDC->SetBkColor(m_clrBackground);
		brush = ::CreateSolidBrush(m_clrBackground);
		return brush;
	default:
		break;
	}
	return brush;
}

LRESULT CUIDialog::OnNcHitTest(CPoint point)
{
	// 取得鼠标所在的窗口区域
	LRESULT nHitTest = CDialog::OnNcHitTest(point);

	// 如果鼠标在窗口客户区，则返回标题条代号给Windows
	// 使Windows按鼠标在标题条上类进行处理，即可单击移动窗口
	return (nHitTest==HTCLIENT) ? HTCAPTION : nHitTest;
}