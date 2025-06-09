#if !defined(AFX_POLARAXISDLG_H__A5983FA0_3596_4079_811D_2D0B496DC5A5__INCLUDED_)
#define AFX_POLARAXISDLG_H__A5983FA0_3596_4079_811D_2D0B496DC5A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolarAxisDlg.h : header file
#include "MyColorBotton.h"

/////////////////////////////////////////////////////////////////////////////
// CPolarAxisDlg dialog

class CPolarAxisDlg : public CDialog
{
// Construction
public:
	CPolarAxisDlg(CWnd* pParent = NULL);   // standard constructor

	IPolarAxisInterface *m_IPolarAxis;
	CRect m_rectPolarAxis;
	int iCount;

	void InitPolarAxis();
	void ChangeDrawStype(BOOL bSet,long nStyle);
	void SetFont();
	void SetColor();

// Dialog Data
	//{{AFX_DATA(CPolarAxisDlg)
	enum { IDD = IDD_DIALOG_POLAR };
	CButton	m_btnZoomOut;
	CButton	m_btnZoomIn;
	CMyColorBotton	m_crAngleFont;
	CButton	m_fontAngleLine;
	CButton	m_btnFont;
	CMyColorBotton	m_crCircleLine;
	CMyColorBotton	m_crAngleLine;
	CComboBox	m_cmbCircleLine;
	CComboBox	m_cmbAngleLine;
	CComboBox	m_cmbFrameShadow;
	CMyColorBotton	m_crRightBottomFrame;
	CMyColorBotton	m_crLeftTopFrame;
	CMyColorBotton	m_crAxisBack;
	CMyColorBotton	m_crAxisTitle;
	CMyColorBotton	m_crWorkArea;
	CStatic	m_stcPolarFrame;
	BOOL	m_bAngleUnitLine;
	BOOL	m_bAxisBorder;
	BOOL	m_bAxisCenter;
	BOOL	m_bCircleUnit;
	BOOL	m_bWorkArea;
	BOOL	m_bWorkAreaFrame;
	BOOL	m_bAxisTitle;
	CString	m_strAngleLineWidth;
	CString	m_strCircleLineWidth;
	CString	m_strTitle;
	CString	m_strAngleUnit;
	CString	m_strCircleUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolarAxisDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPolarAxisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnWorkarea();
	afx_msg void OnWorkareaframe();
	afx_msg void OnAxiscenter();
	afx_msg void OnAxisborder();
	afx_msg void OnAngleunitline();
	afx_msg void OnCircleunit();
	afx_msg void OnBtnColorWorkarea();
	afx_msg void OnAxistitle();
	afx_msg void OnBtnColorAxistitle();
	afx_msg void OnBtnColorAxisback();
	afx_msg void OnBtnColorLefttopframe();
	afx_msg void OnBtnColorRightbottomframe();
	afx_msg void OnEditchangeFrameshadow();
	afx_msg void OnSelchangeComboFrameshadow();
	afx_msg void OnSelchangeComboAngleline();
	afx_msg void OnSelchangeComboCircleline();
	afx_msg void OnBtnColorAngleline();
	afx_msg void OnBtnColorCircleline();
	virtual void OnOK();
	afx_msg void OnBtnFont();
	afx_msg void OnBtnFontangleline();
	afx_msg void OnBtnColorAnglefont();
	afx_msg void OnBtnZoomin();
	afx_msg void OnBtnZoomout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLARAXISDLG_H__A5983FA0_3596_4079_811D_2D0B496DC5A5__INCLUDED_)
