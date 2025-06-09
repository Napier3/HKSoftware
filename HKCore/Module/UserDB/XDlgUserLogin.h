#pragma once

#include "..\FilterText\FilterTextMngr.h"
#include "..\filtertext\filtertextcombobox.h"
// CXDlgUserLogin 对话框

class CXDlgUserLogin : public CDynDialogEx
{
protected:
	CFilterTextMngr m_oUserLoginHistory;
	void OpenUserLoginHistoryFile();

public:
	CXDlgUserLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDlgUserLogin();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CFilterTextComboBox m_cmbUserFilter;

	CButton m_btnOK;
	CButton m_btnCancel;
	CEdit m_edtUserPsw;
	CStatic m_stcUserName;
	CStatic m_stcUserPsw;

protected:
	virtual void OnOK();
public:
	CString m_strName;
	CString m_strPSW;
};
