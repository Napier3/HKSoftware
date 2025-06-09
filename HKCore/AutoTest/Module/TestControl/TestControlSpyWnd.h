#if !defined(AFX_TTTCTRLTESTSPYWND_H__AFB718D0_9990_43E4_A25A_E72D14359199__INCLUDED_)
#define AFX_TTTCTRLTESTSPYWND_H__AFB718D0_9990_43E4_A25A_E72D14359199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tttctrltestspywnd.h : header file
//

#include "TestItemTestContainer.h"
#include "..\MFCCtrlEx\TitleTipWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTttCtrlTestSpyWnd window

class CTttCtrlTestSpyWnd : public CButton
{
// Construction
public:
	CTttCtrlTestSpyWnd();

// Attributes
public:
	CTestItemTestContainer m_TestItemTestContainer;
	CTitleTipWnd	m_TitleTip;             // Title tips
	CRect			m_rectTitleTip;
	long			m_nOldItemIndexShowTip;
	CTestItemBaseClass *m_pCurrItem;
	long	m_nTimerIDEvent;
	
	CBitmap	*m_pBitmap;
	CBitmap	*m_pOldBitmap;
	CDC		*m_pMemDC;

	long	m_nTopGap;	//第一行元素与顶部的间隔
	
// Operations
public:
	void SetTestProject(CTestProject *pProject);
	void UpdateTestProjectSpy();
	void AddTestItemToContainer(CTestItemBaseClass *pItem);

	void _OnLButtonDblClk(UINT nFlags, CPoint point);
	void _OnMouseMove(UINT nFlags, CPoint point);
	void _OnClicked();
	void _OnDoubleclicked();
	void _OnLButtonDown(UINT nFlags, CPoint point);
	void _OnLButtonUp(UINT nFlags, CPoint point);
	void _OnSize();
	
	long GetTestItemIndexAtPoint(CPoint point);
	CTestItemBaseClass* GetTestItemAtPoint(CPoint point);

	void CreateTitleTip();

protected:
	void GetTestItemTipString(CString &strTip,CTestItemBaseClass *pItem);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTttCtrlTestSpyWnd)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTttCtrlTestSpyWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTttCtrlTestSpyWnd)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	afx_msg void OnDoubleclicked();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTTCTRLTESTSPYWND_H__AFB718D0_9990_43E4_A25A_E72D14359199__INCLUDED_)
