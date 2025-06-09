#if !defined(AFX_DESCARTESAXISDLG_H__CD73631B_E3B3_4F98_AA53_51563455674C__INCLUDED_)
#define AFX_DESCARTESAXISDLG_H__CD73631B_E3B3_4F98_AA53_51563455674C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DescartesAxisDlg.h : header file
//
#include "MyColorBotton.h"

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxisDlg dialog

class CDescartesAxisDlg : public CDialog
{
// Construction
public:
	CDescartesAxisDlg(CWnd* pParent = NULL);   // standard constructor

	IDescartesAxisInterface *m_IDescartesAxis;
	CRect m_rectDescartesAxis;
	
	void InitAxis();
	void ChangeDrawStype(BOOL bSet,long nStyle);
	void SetFont();
	void SetColor();
// Dialog Data
	//{{AFX_DATA(CDescartesAxisDlg)
	enum { IDD = IDD_DIALOG_DESCARTES };
	CButton	m_btnZoomOut;
	CButton	m_btnZoomIn;
	CComboBox	m_cmbCenterLineStyle;
	CMyColorBotton	m_crCenterLine;
	CMyColorBotton	m_crXUnitScaleShadow;
	CMyColorBotton	m_crXUnitScale;
	CMyColorBotton	m_crYScaleTenth;
	CMyColorBotton	m_crXScaleTenth;
	CComboBox	m_cmbYGridStyle;
	CComboBox	m_cmbXGridStyle;
	CMyColorBotton	m_crYGrid;
	CMyColorBotton	m_crXGrid;
	CMyColorBotton	m_crYScaleFont;
	CMyColorBotton	m_crXScaleFont;
	CMyColorBotton	m_crYAxisName;
	CMyColorBotton	m_crXAxisName;
	CButton	m_lfYScale;
	CButton	m_lfXScale;
	CButton	m_lfXAxisName;
	CButton	m_lfYAxisName;
	CMyColorBotton	m_crYUnitScaleShadow;
	CMyColorBotton	m_crYUnitScale;
	CComboBox	m_cmbFrameShadow;
	CMyColorBotton	m_crRightBottomFrame;
	CMyColorBotton	m_crLeftTopFrame;
	CComboBox	m_cmbBorderShadow;
	CMyColorBotton	m_crRightBottomBorder;
	CMyColorBotton	m_crLeftTopBorder;
	CMyColorBotton	m_crAxisBack;
	CButton	m_fontDesAxisTitle;
	CMyColorBotton	m_crAxisTitle;
	CMyColorBotton	m_crWorkArea;
	CStatic	m_stcFrame;
	BOOL	m_bDrawFrame;
	BOOL	m_bAxisTitle;
	BOOL	m_bXAxisTitle;
	BOOL	m_bYAxisTitle;
	BOOL	m_bXAxisTenth;
	BOOL	m_bXAxisScaleText;
	BOOL	m_bYAxisTenth;
	BOOL	m_bAxisCenter;
	BOOL	m_bXAxisHalfUnitScale;
	BOOL	m_bYAxisHalfUnitScale;
	BOOL	m_bYAxisScaleText;
	CString	m_strAxisTitle;
	CString	m_strXAxisName;
	CString	m_strYAxisName;
	CString	m_strXAxisWidth;
	CString	m_strYAxisWidth;
	CString	m_strXHalfScaleLen;
	CString	m_strXTenthScaleLen;
	CString	m_strXUnitScaleLen;
	CString	m_strYHalfScaleLen;
	CString	m_strYTenthScaleLen;
	CString	m_strYUnitScaleLen;
	CString	m_strCenterLineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDescartesAxisDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDescartesAxisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnDrawborder();
	afx_msg void OnAxistitle();
	afx_msg void OnXaxistitle();
	afx_msg void OnYaxistitle();
	afx_msg void OnXaxistenith();
	afx_msg void OnXaxisscaletext();
	afx_msg void OnYaxistenith();
	afx_msg void OnAxiscenter();
	afx_msg void OnXaxishalfunitscale();
	afx_msg void OnYaxishalfunitscale();
	afx_msg void OnYaxisscaletext();
	afx_msg void OnBtnColorworkarea();
	afx_msg void OnBtnColorAxistitle();
	afx_msg void OnBtnColorDesaxistitle();
	afx_msg void OnBtnFontDesaxistitle();
	afx_msg void OnBtnColorDesaxisback();
	afx_msg void OnBtnColorDeslefttopborder();
	afx_msg void OnBtnColorDesrightbottomborder();
	afx_msg void OnBtnColorDesframelefttop();
	afx_msg void OnBtnColorDesframerightbottom();
	afx_msg void OnBtnColorDesyunitscale();
	afx_msg void OnBtnColorDesyunitscaleshadow();
	afx_msg void OnBtnFontDesyaxisname();
	afx_msg void OnBtnFontDesxaxisname();
	afx_msg void OnBtnFontDesyscale();
	afx_msg void OnBtnFontDesxscale();
	afx_msg void OnBtnColorDesyaxisname();
	afx_msg void OnBtnColorDesxaxisname();
	afx_msg void OnBtnColorDesyscalefont();
	afx_msg void OnBtnColorDesxscalefont();
	afx_msg void OnBtnColorDesygrid();
	afx_msg void OnBtnColorDesxgrid();
	virtual void OnOK();
	afx_msg void OnBtnColorDesytenth();
	afx_msg void OnBtnColorDesxtenth();
	afx_msg void OnSelchangeComboDesbordershadow();
	afx_msg void OnSelchangeComboDesframeshadow();
	afx_msg void OnSelchangeComboDesygirdstyle();
	afx_msg void OnSelchangeComboDesxgridstyle();
	afx_msg void OnBtnColorDesxunitscale();
	afx_msg void OnBtnColorDesxunitscaleshadow();
	afx_msg void OnSelchangeComboDescenterlinestyle();
	afx_msg void OnBtnColorCenterline();
	afx_msg void OnBtnZoomin();
	afx_msg void OnBtnZoomout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESCARTESAXISDLG_H__CD73631B_E3B3_4F98_AA53_51563455674C__INCLUDED_)
