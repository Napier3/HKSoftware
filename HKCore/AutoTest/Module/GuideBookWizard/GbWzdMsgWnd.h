// GbWzdMsgWnd.h: interface for the CGbWzdMsgWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GbWzdMsgWnd_h__)
#define _GbWzdMsgWnd_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Module\MfcCtrlEx\ButtonRgn.h"

class CGbWzdMsgWnd : public CWnd  
{
public:
	CGbWzdMsgWnd();
	virtual ~CGbWzdMsgWnd();
	BOOL Create(CWnd *parent);

	void ShowMsgString(const CString &strMsg);
	void InitRight(long nRight);
	void EnableNextButton(BOOL bEnable);

protected:
	void InitMsgString(const CString &strData);
	void Show(CPoint ptOrigin);

private:
	CButtonRgn m_btnOk;
	CEdit	m_editSafety;
	CString m_strMsgText;

	CFont		*m_pFont;										// Tip font
	LOGFONT		m_lfLogFont;										// Tip font
	LPCTSTR		m_szClass;										// Window class
	CPoint m_ptOrigin;

	BOOL	m_bMouseOverWnd;
	BOOL	m_bMouseTracking;
	CPoint	m_ptMouseMove;

	HCURSOR m_hLoadCursor;

public:
	void RepositionAllButtons(CRect rectWnd);
	void SetAllButtonsColor();

protected:
	BOOL GetWindowRegion(CDC *pDC, HRGN* hRegion, CSize* Size = NULL);
	CSize GetWndSizeBySafetyData(CDC* pDC);

protected:
	//{{AFX_MSG(CPWCnlnWnd)
	afx_msg void OnPaint();
	afx_msg void OnBtnOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(_GbWzdMsgWnd_h__)
