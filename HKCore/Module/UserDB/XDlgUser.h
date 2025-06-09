#pragma once
#include "afxwin.h"


// CXDlgUser 对话框

class CXDlgUser : public CDialog
{
	DECLARE_DYNAMIC(CXDlgUser)

protected:
	void EnableOK();
	void EnableByUser();

public:
	CXDlgUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDlgUser();
	CXUser *m_pCurrUser;

// 对话框数据
	enum { IDD = IDD_DIALOG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_edtName;
	CEdit m_edtID;
	CEdit m_edtPSW;
	CString m_strName;
	CString m_strID;
	CString m_strPSW;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditId();
	afx_msg void OnEnChangeEditPsw();
	CButton m_btnOK;
};
