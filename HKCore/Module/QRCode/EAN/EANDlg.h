// EANDlg.h : header file
//

#if !defined(AFX_EANDLG_H__97443067_8DEE_468B_975D_7D4FD2D0C194__INCLUDED_)
#define AFX_EANDLG_H__97443067_8DEE_468B_975D_7D4FD2D0C194__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEANDlg dialog

class CEANDlg : public CDialog
{
// Construction
public:
	CEANDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEANDlg)
	enum { IDD = IDD_EAN_DIALOG };
	CComboBox	m_cbRatio;
	CEdit	m_editCheckDigit;
	CEdit	m_editProduct;
	CEdit	m_editManufacturer;
	CEdit	m_editHeight;
	CEdit	m_editGuardbarHeight;
	CEdit	m_editCountryCode;
	CComboBox	m_cbSymbology;
	CStatic	m_staticBitmapBarcode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEANDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEANDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonDraw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EANDLG_H__97443067_8DEE_468B_975D_7D4FD2D0C194__INCLUDED_)
