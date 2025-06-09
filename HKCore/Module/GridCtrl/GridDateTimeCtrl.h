#pragma once

#include "GridDefine.h"

// CGridDateTimeCtrl

class CGridDateTimeCtrl : public CDateTimeCtrl
{
 public:
   CGridDateTimeCtrl(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
	   int nRow, int nColumn, CString sInitText, UINT nFirstChar,
	   CXGridCtrlBase_MsgFunc *pMsgFunc=NULL);

// Attributes
public:

// Operations
public:
     void EndEdit();

public:
	void Init();
	CString GeTimeText();

protected:
	CString m_strDateTimeFormat;
	long m_nLength;
	CXGridCtrlBase_MsgFunc *m_pMsgFunc;

// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CGridEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
public:
	virtual ~CGridDateTimeCtrl();

protected:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
private:
    int     m_nRow;
    int     m_nColumn;
    CString m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
};


