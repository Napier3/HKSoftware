// GridCtrlClientDlg.h : header file
//

#if !defined(AFX_GRIDCTRLCLIENTDLG_H__AE9BCA90_8DA7_4E6B_ACC5_03875A2DD687__INCLUDED_)
#define AFX_GRIDCTRLCLIENTDLG_H__AE9BCA90_8DA7_4E6B_ACC5_03875A2DD687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyGridctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CGridCtrlClientDlg dialog

class CGridCtrlClientDlg : public CDialog
{
public:
//	CMyGridctrl m_grid;
	CMyGridctrl m_gridex;
	void CreateGrid();

// Construction
public:
	CGridCtrlClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGridCtrlClientDlg)
	enum { IDD = IDD_GRIDCTRLCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGridCtrlClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnMerge();
	afx_msg void OnButtonCreate();
	afx_msg void OnButtonDestroy();
	//}}AFX_MSG
	LRESULT OnGridDoubleClick(WPARAM , LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLCLIENTDLG_H__AE9BCA90_8DA7_4E6B_ACC5_03875A2DD687__INCLUDED_)
