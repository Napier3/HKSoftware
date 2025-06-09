#if !defined(_GRID_EDIT_H__)
#define _GRID_EDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GridEdit.h : header file

#include "GridDefine.h"

/////////////////////////////////////////////////////////////////////////////
// CGridEdit window
 
class CGridEdit : public CEdit
{
// Construction
public:
    CGridEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar, 
				 GRIDEDIT_FORMAT nFormat=GEFM_NONE, CXGridCtrlBase_MsgFunc *pMsgFunc=NULL);

// Attributes
public:
	GRIDEDIT_FORMAT m_nFormat;
 
// Operations
public:
     void EndEdit();
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CGridEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
 
// Implementation
public:
     virtual ~CGridEdit();
 
// Generated message map functions
protected:
    //{{AFX_MSG(CGridEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    int     m_nRow;
    int     m_nColumn;
    CString m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
	CXGridCtrlBase_MsgFunc *m_pMsgFunc;

private:
	void ArrowUp();
	void ArrowDown();
	void ArrowRight();
	void ArrowLeft();
	void UpdateText(CString& strText,int nStart,int nEnd);

public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
 
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_GRID_EDIT_H__)
