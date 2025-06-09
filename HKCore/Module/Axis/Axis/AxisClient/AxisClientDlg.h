// AxisClientDlg.h : header file
//

#if !defined(AFX_AXISCLIENTDLG_H__1A9E24F8_4147_49EF_9377_1B466A0EC9A6__INCLUDED_)
#define AFX_AXISCLIENTDLG_H__1A9E24F8_4147_49EF_9377_1B466A0EC9A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAxisClientDlg dialog

class CAxisClientDlg : public CDialog
{
// Construction
public:
	CAxisClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAxisClientDlg)
	enum { IDD = IDD_AXISCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxisClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAxisClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDescartesaxis();
	afx_msg void OnPolaraxis();
	afx_msg void OnLogarithmaxis();
	afx_msg void OnRuleraxis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISCLIENTDLG_H__1A9E24F8_4147_49EF_9377_1B466A0EC9A6__INCLUDED_)
