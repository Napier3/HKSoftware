#if !defined(AFX_TITLETIPWND_H__BC14DF4B_618D_4FE0_8260_5B7E23E170B7__INCLUDED_)
#define AFX_TITLETIPWND_H__BC14DF4B_618D_4FE0_8260_5B7E23E170B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AtsTitleTipWnd.h : header file
//

#define TITLETIPWND_CLASSNAME _T("_AtsTitleTipWnd_")
#include "../../Module/api/GloblaDrawFunctions.h"

/////////////////////////////////////////////////////////////////////////////
// CAtsTitleTipWnd window

class CAtsTitleTipWnd : public CWnd
{
// Construction
public:
	CAtsTitleTipWnd();

// Attributes
public:

protected:
	CWnd *m_pParentWnd;
	CRect m_rectTitle;
	LOGFONT m_logFont;
	BOOL	m_bUseParentFont;
	
// Operations
public:
	virtual BOOL Create( CWnd *pParentWnd);
	void Show( CRect rectTitle, LPCTSTR lpszTitleText, int xoffset = 0);
    void Hide();
	void SetLogFont(LOGFONT logFont);
	void CalTipRectAngle(LPCTSTR lpszTitleText,long nMaxWidth,CSize &sizeTip);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAtsTitleTipWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAtsTitleTipWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAtsTitleTipWnd)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLETIPWND_H__BC14DF4B_618D_4FE0_8260_5B7E23E170B7__INCLUDED_)
