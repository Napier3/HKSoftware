#ifndef UIDRAWER_H
#define UIDRAWER_H

#include <map>
#include <GdiPlus.h>
using namespace Gdiplus;

//以下是ExBase体系的控件,自绘能力有限,最好替换成原版MFC控件
#include "../../../../Module/BaseClass/ExBaseListTreeCtrl.h"
#include "../../../../Module/GridBase/ExBaseListGrid.h"

#define COLOR_DEEPGREEN			RGB(0,146,159)
#define COLOR_GREEN				RGB(202,235,231)
#define COLOR_LIGHTGREEN		RGB(242,249,249)
#define COLOR_RED				RGB(244,92,88)
#define COLOR_YELLOW			RGB(255,208,0)
#define COLOR_DEEPBLUE			RGB(6,21,45)
#define COLOR_GRAY				RGB(102,106,126)
#define COLOR_LIGHTGRAY			RGB(156,160,183)
#define COLOR_WHITE				RGB(255,255,255)

class CUIDrawer
{
private:
	ULONG_PTR				gdiplusToken;

	void* m_pData;
	int                     m_nSize;
	DWORD					m_nFontIndex;

	// GDI+
	PrivateFontCollection* m_pFontCollection;
	Gdiplus::FontFamily* m_pFontFamily;
	Gdiplus::Font* m_Font;

	// GDI
	CString					m_strFontFile;
	HANDLE                  m_hFontRes;

public:
	CUIDrawer();
	virtual ~CUIDrawer();

	BOOL LoadFont(UINT lpszResource, LPCTSTR lpszType = _T("ttf"));
	Gdiplus::Font* SetFontStyle(Gdiplus::FontStyle fontstyle = FontStyleRegular, REAL nFontSize = 14.0F);
	Gdiplus::FontFamily* FontFamily();
	HFONT FontToHFONTA(HWND hWnd);
	HFONT FontToHFONTW(HWND hWnd);
	HFONT GetSafeHFONT(HWND hWnd);

	CFont* GetUIFont(HWND hWnd, Gdiplus::FontStyle fontstyle = FontStyleRegular, REAL nFontSize = 14.0F);

protected:
	void DrawPng(CDC* pDC, HBITMAP hBitmap, CRect rc);
	
};

class CUIButton : public CBitmapButton, public CUIDrawer
{
	DECLARE_DYNAMIC(CUIButton)
private:
	enum stateMachine
	{
		normal,
		hover
	}m_tagState;

	CString m_strNormalPic;
	CString m_strHoverPic;

public:
	CUIButton();
	virtual ~CUIButton();

	void InitUI(const CString& strNormalName, const CString& strHoverName);

protected:
	BOOL OnEraseBkgnd(CDC* pDC); 
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

	DECLARE_MESSAGE_MAP()
};

class CUITabCtrl : public CTabCtrl, public CUIDrawer
{
	DECLARE_DYNAMIC(CUITabCtrl)
private:
	struct tagTabItem{
		CString m_strText;
		long m_ItemWidth;
	};

	COLORREF m_clrBackground;
	COLORREF m_clrSelForeground;
	COLORREF m_clrUnselForeground;

	float m_fFontPointSize;
	long m_nFontWidth;
	long m_nTabPadding;
	std::map<long, tagTabItem> m_mapTabItems;
	long m_nCurSel;

public:
	CUITabCtrl();
	virtual ~CUITabCtrl();

	void InitUI(COLORREF clrBackground, COLORREF clrSelForeground, COLORREF clrUnselForeground);
	void AddItem(CString strText);
	int GetCurSel();
	int SetCurSel(int nItem);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

class CUIComboBox : public CComboBox, public CUIDrawer
{
	DECLARE_DYNAMIC(CUIComboBox)
private:
	COLORREF m_clrBorder;
	COLORREF m_clrArrowBackground;

public:
	CUIComboBox();
	virtual ~CUIComboBox();

	void InitUI(COLORREF clrBorder, COLORREF clrArrowBackground);

protected:
	BOOL OnEraseBkgnd(CDC* pDC); 
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){}
	virtual void OnPaint();

	DECLARE_MESSAGE_MAP()
};

class CUIEdit : public CEdit, public CUIDrawer
{
	DECLARE_DYNAMIC(CUIEdit)

private:
	COLORREF m_clrBorder;

public:
	CUIEdit();
	virtual ~CUIEdit();

	void InitUI(COLORREF clrBorder);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

class CUITreeCtrl : public CExBaseListTreeCtrl, public CUIDrawer
{
	DECLARE_DYNAMIC(CUITreeCtrl)
private:
	CString m_strFoldPic;
	CString m_strExpandPic;
	CString m_strDisFoldPic;
	CString m_strDisExpandPic;
	
	void DrawCustom(NMTVCUSTOMDRAW* pCustomDraw);

public:
	CUITreeCtrl();
	virtual ~CUITreeCtrl();

	void InitUI(const CString& strFoldName, const CString& strDisFoldName,
		const CString& strExpandName, const CString& strDisExpandName);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
};

class CUIGrid : public CExBaseListGrid, public CUIDrawer
{
	DECLARE_DYNCREATE(CUIGrid)
public:
	CUIGrid();
	virtual ~CUIGrid();

	virtual void InitGrid(){}
	virtual void InitGridTitle(){}
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE){}

	void InitUI(COLORREF clrHeaderBk, COLORREF clrBorder, COLORREF clrForeground, COLORREF clrBackground);

protected:

	DECLARE_MESSAGE_MAP()
};

class CUIDialog : public CDialog, public CUIDrawer
{
	DECLARE_DYNAMIC(CUIDialog)
private:
	COLORREF m_clrBackground;
	COLORREF m_clrForeground;
	CStatic m_txtTitle;
	CUIButton m_btnCloseDlg;

public:
	CUIDialog(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CUIDialog();

	void InitUI(COLORREF clrBackground, COLORREF clrForeground);
	void SetWindowTitle(const CString& strTitle);
	void MoveChildWindow(CWnd* pWnd);

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif