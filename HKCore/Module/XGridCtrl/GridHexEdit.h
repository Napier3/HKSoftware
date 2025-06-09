#pragma once

#include "GridDefine.h"

// CGridHexEdit

class CGridHexEdit : public CMFCMaskedEdit
{
public:
    CGridHexEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar, int nMaxLen);

// Attributes
public:

// Operations
public:
     void EndEdit();

public:
	void Init(long nLength);
	void InitEx(long nLength);
	void SetValue(DWORD dwValue);
	void GetValue(DWORD &dwValue);
	void SetValue(WORD wValue);
	void GetValue(WORD &wValue);
	void SetValue(BYTE byteValue);
	void GetValue(BYTE &byteValue);

	CString GetHexText()
	{
		CString strText;
		GetWindowText(strText);
		return strText;
	}
protected:
	long m_nLength;

// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CGridEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

public:
	virtual ~CGridHexEdit();

protected:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
private:
    int     m_nRow;
    int     m_nColumn;
    CString m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


