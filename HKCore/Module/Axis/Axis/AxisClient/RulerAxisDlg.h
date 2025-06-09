#if !defined(AFX_RULERAXISDLG_H__EFF4F3A0_71CC_4595_BD2D_D052A4780BF6__INCLUDED_)
#define AFX_RULERAXISDLG_H__EFF4F3A0_71CC_4595_BD2D_D052A4780BF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerAxisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRulerAxisDlg dialog

class CRulerAxisDlg : public CDialog
{
// Construction
public:
	CRulerAxisDlg(CWnd* pParent = NULL);   // standard constructor

	IRulerAxisInterface *m_IRulerAxis;
	CRect m_rectHorzAxis;
	CRect m_rectVertAxis;
	float fHorzRulerValue[2];
	float fVertRulerValue[2];

	void InitAxis();
	void ChangeDrawStype(BOOL bSet,long nStyle);


// Dialog Data
	//{{AFX_DATA(CRulerAxisDlg)
	enum { IDD = IDD_DIALOG_RULER };
	CStatic	m_stcVertFrame;
	CStatic	m_stcHorzFrame;
	BOOL	m_bBorder;
	BOOL	m_bHalfScale;
	BOOL	m_bScaleText;
	BOOL	m_bTenthScale;
	BOOL	m_bWorkArea;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerAxisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRulerAxisDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBorder();
	afx_msg void OnWorkarea();
	afx_msg void OnScaleText();
	afx_msg void OnTenthScale();
	afx_msg void OnHalfScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERAXISDLG_H__EFF4F3A0_71CC_4595_BD2D_D052A4780BF6__INCLUDED_)
