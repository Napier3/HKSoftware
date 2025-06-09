#pragma once

class CWzdDlgButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CWzdDlgButton)

private:
	CString m_imgNor;
	CString	m_imgSel;
	CString	m_imgHot;
	CString	m_imgDis;

	BOOL m_bIsHover;
	BOOL m_bEnabled;
	BOOL m_bChecked;
	BOOL m_bPressed;
	BOOL m_bVisible;
	BOOL m_bReadOnly;
	BOOL m_bIsHold;
	BOOL m_bDrawTrans;
	BOOL m_bIsImgMode;
	UINT m_nTextMode;

	void* m_pData;

	COLORREF m_txtColor;
	COLORREF m_backColor;

public:
	CString m_strID;

	CWzdDlgButton();
	virtual ~CWzdDlgButton();

private:
	void DrawPng(CDC* pDC, HBITMAP hBitmap, CRect rc);
	void DrawTransparent(HDC hdcDest,int nWidthDest,int nHeightDest,
		HDC hdcSrc,int nWidthSrc,int nHeightSrc,COLORREF crTransparent);

public:
	void LoadImage(CString strNor, CString strSel = "", CString strHot = "", CString strDis = "");
	void SetItemData(void* pData) { m_pData = pData; }
	void* GetItemData() { return m_pData; }
	void SetImgMode(BOOL bImg) { m_bIsImgMode = bImg; }
	void SetHold(bool bHold) { m_bIsHold = bHold; Invalidate(); }
	BOOL IsHold() { return m_bIsHold; }
	void SetEnabled(BOOL bEnable);
	BOOL IsEnabled() { return m_bEnabled; }
	void SetVisible(BOOL bVisible);
	BOOL IsVisible() { return m_bVisible; }
	void SetReadOnly(BOOL bReadOnly) { m_bReadOnly = bReadOnly; }
	BOOL IsReadOnly() { return m_bReadOnly; }

	void SetTxtColor(COLORREF rgb) { m_txtColor = rgb; }
	void SetBackColor(COLORREF rgb) { m_backColor = rgb; }
	void SetDrawMode(BOOL bDrawTrans) { m_bDrawTrans = bDrawTrans; }
	
	virtual void LButtonUp(UINT nFlags, CPoint point);
	virtual void LButtonDown(UINT nFlags, CPoint point);

protected:
	BOOL OnEraseBkgnd(CDC* pDC); 
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	
DECLARE_MESSAGE_MAP()
};

class CWzdDlgNormalBtn : public CWzdDlgButton
{
public:
	CWzdDlgNormalBtn()
	{
		CString strIcon = _P_GetResourcePath();
		strIcon += "iSmartTestWzd/";
		LoadImage(strIcon + "btn_n.png", 
			strIcon + "btn_y.png", 
			strIcon + "btn_h.png",
			strIcon + "btn_d.png");
		SetImgMode(TRUE);
	}
};