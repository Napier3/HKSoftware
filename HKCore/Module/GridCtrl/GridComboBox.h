#if !defined(_GRID_COMBOBOX_H__)
#define _GRID_COMBOBOX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GridDefine.h"

#define IDC_COMBOEDIT 1001
#define IPCMBM_FILL  WM_USER + 1001

/////////////////////////////////////////////////////////////////////////////
// CGridComboEdit window

class CGridComboEdit : public CEdit
{
// Construction
public:
	CGridComboEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridComboEdit)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridComboEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGridComboEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};

/////////////////////////////////////////////////////////////////////////////
// CGridComboBox window

class CGridComboBox : public CComboBox
{
    friend class CGridComboEdit;

// Construction
public:
	CGridComboBox(CWnd* pParent,         // parent
                 CRect& rect,           // dimensions & location
                 DWORD dwStyle,         // window/combobox style
                 UINT nID,              // control ID
                 int nRow, int nColumn, // row and column
				 //CStringArray& Items,   // Items in list
                 CString sInitText,     // initial selection
				 UINT nFirstChar,      // first character to pass to control
				 LOGFONT lfFont, CXGridCtrlBase_MsgFunc *pMsgFunc=NULL);
protected:
	int	m_iDeflateVal;
	
    int      m_cxHThumb;     // Size of the drop arrow for the combo box.
    BOOL     m_bLBtnDown;    // TRUE if left mouse button is pressed
    BOOL     m_bPainted;     // used during paint operations
    BOOL     m_bHasFocus;    // TRUE if control has focus
    BOOL     m_bAutoComp;    // Used by Autocompleting.
    BOOL     m_bFlatLook;    // TRUE if the control is flat.
	BOOL     m_bDisableAC;   // TRUE when auto complete is disabled internally.
    COLORREF m_clr3DHilight; // System color for ::GetSysColor(COLOR_3DHILIGHT).
	COLORREF m_clr3DShadow;  // System color for ::GetSysColor(COLOR_3DSHADOW).
	COLORREF m_clr3DFace;    // System color for ::GetSysColor(COLOR_3DFACE).
	CFont *m_pFont;
	CXGridCtrlBase_MsgFunc *m_pMsgFunc;
public:
    void DisableFlatLook(BOOL bDisable);
    virtual void EnableAutoCompletion(BOOL bEnable=TRUE);
    virtual BOOL PointInRect();
	void SetDeflateVal(int iVal);
protected:
    virtual void DrawCombo(CDC* pDC,COLORREF clrTopLeft,COLORREF clrBottomRight);
	void OnNoFlickerPaint(CDC* pDC);
	
// Attributes
public:
   CGridComboEdit m_edit;  // subclassed edit control

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridComboBox)
	protected:
	virtual void PostNcDestroy();
    public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
		//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridComboBox();
protected:
    void EndEdit(BOOL bFromEdit);
	BOOL m_bEndEdit;

// Generated message map functions
protected:
	//{{AFX_MSG(CGridComboBox)
	afx_msg void OnCbnKillfocus();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();
    afx_msg void OnCbnSetFocus();
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int		m_nNumLines;
	CString m_sInitText;
	int		m_nRow;
	int		m_nCol;
 	UINT    m_nLastChar; 
	BOOL	m_bExitOnArrows; 
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnCbnSelchange();
};

/////////////////////////////////////////////////////////////////////////////


AFX_INLINE BOOL CGridComboBox::PointInRect() 
{
    ASSERT(::IsWindow(m_hWnd)); 
	CPoint pt;
	GetCursorPos(&pt); 
	CRect rcItem; 
	GetWindowRect(&rcItem); 
	return rcItem.PtInRect(pt);
}
AFX_INLINE void CGridComboBox::EnableAutoCompletion(BOOL bEnable/*=TRUE*/) 
{
    ASSERT(::IsWindow(m_hWnd)); 
	m_bAutoComp = bEnable;
}
AFX_INLINE void CGridComboBox::DisableFlatLook(BOOL bDisable) 
{
    m_bFlatLook = !bDisable;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_GRID_COMBOBOX_H__)
