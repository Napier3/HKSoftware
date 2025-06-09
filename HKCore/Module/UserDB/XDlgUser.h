#pragma once
#include "afxwin.h"


// CXDlgUser �Ի���

class CXDlgUser : public CDialog
{
	DECLARE_DYNAMIC(CXDlgUser)

protected:
	void EnableOK();
	void EnableByUser();

public:
	CXDlgUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXDlgUser();
	CXUser *m_pCurrUser;

// �Ի�������
	enum { IDD = IDD_DIALOG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
