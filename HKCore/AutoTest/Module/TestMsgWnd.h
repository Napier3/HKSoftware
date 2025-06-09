// TestMsgWnd.h: interface for the CTestMsgWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMSGWND_H__D1A7CE50_D249_11D7_BE4A_0010DC486B22__INCLUDED_)
#define AFX_TESTMSGWND_H__D1A7CE50_D249_11D7_BE4A_0010DC486B22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Module\MfcCtrlEx\ButtonRgn.h"
#include "..\..\Module\WavePlay\MediaPlay.h"

class CTestMsgWnd : public CWnd  
{
public:
	CTestMsgWnd();
	virtual ~CTestMsgWnd();
	BOOL Create(CWnd *parent);

	void InitSafetyData(const CString &strData);
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
	CMediaPlay m_oMediaPlay;
	long m_nPlayCycle;

public:
	void RepositionAllButtons(CRect rectWnd);
	void SetAllButtonsColor();

protected:
	BOOL GetWindowRegion(CDC *pDC, HRGN* hRegion, CSize* Size = NULL);
	CSize GetWndSizeBySafetyData(CDC* pDC);

protected:
	//{{AFX_MSG(CPWCnlnWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnOk();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnMediaPlayStateChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAtsGbItemStateMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TESTMSGWND_H__D1A7CE50_D249_11D7_BE4A_0010DC486B22__INCLUDED_)
