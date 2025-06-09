#pragma once
#include "afxwin.h"
#include "XKeyDBUiGlobal.h"


// CBaseKeyDlg 对话框

class CXAnalyzeDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXAnalyzeDlg)

public:
	CXAnalyzeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXAnalyzeDlg();
	// 
	// 	// 对话框数据
	// 	enum { IDD = IDD_KEYBASE_DIALOG };

	virtual BOOL OnInitDialog();
	void CreateControls();
	virtual int DoModal();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnSave;
	afx_msg void OnBnClickedBtnBasekeySave();
};


