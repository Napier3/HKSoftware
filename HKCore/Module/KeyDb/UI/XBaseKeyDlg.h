#pragma once
#include "afxwin.h"
#include "XKeyDBUiGlobal.h"




// CBaseKeyDlg 对话框

class CXBaseKeyDlg : public CXKeyEditDlgBase
{
	DECLARE_DYNAMIC(CXBaseKeyDlg)

public:
	CXBaseKeyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXBaseKeyDlg();

// 
// 	// 对话框数据


	virtual BOOL OnInitDialog();
	void CreateControls();
	virtual int DoModal();
	virtual void OnCancel(){};
	virtual void OnOK(){};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editKeyName;
	CEdit m_editKeyID;
	CString m_strName;
	CString m_strID;
	CStatic m_NameStatic;
	CStatic m_IDStatic;
	CButton m_btnSave;
	CButton m_btnCancle;
	afx_msg void OnBnClickedBtnBasekeySave();
	afx_msg void OnBnClickedBtnBasekeyCancle();
};
