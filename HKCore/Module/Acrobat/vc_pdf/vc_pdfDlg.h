// vc_pdfDlg.h : header file
//

#if !defined(AFX_VC_PDFDLG_H__DEC43529_696A_46F8_8D54_F93B8F9EB8B6__INCLUDED_)
#define AFX_VC_PDFDLG_H__DEC43529_696A_46F8_8D54_F93B8F9EB8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVc_pdfDlg dialog

class CVc_pdfDlg : public CDialog
{
// Construction
public:
	CVc_pdfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVc_pdfDlg)
	enum { IDD = IDD_VC_PDF_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVc_pdfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVc_pdfDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC_PDFDLG_H__DEC43529_696A_46F8_8D54_F93B8F9EB8B6__INCLUDED_)
