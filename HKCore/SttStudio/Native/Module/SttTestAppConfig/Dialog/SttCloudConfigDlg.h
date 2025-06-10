#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"

#define STT_STC_CLOUDIP				0x000002060
#define STT_EDIT_CLOUDIP			0x000002061
#define STT_STC_CLOUDSVRPORT		0x000002062
#define STT_EDIT_CLOUDSVRPORT		0x000002063
#define STT_BTN_OK					0x000002064
#define STT_BTN_CANCEL				0x000002065

// CSttCloudConfigDlg 对话框

class CSttCloudConfigDlg : public CDynDialogEx
{
//	DECLARE_DYNAMIC(CSttCloudConfigDlg)

public:
	CSttCloudConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttCloudConfigDlg();

// 对话框数据
//	enum { IDD = IDD_TESTAPPCONFIG_LOCALCONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickOK();
	afx_msg void OnBtnClickCancel();

public:
	CStatic m_stcCloudIP;
	CEdit m_edtCloudIP;
	CStatic m_stcCloudSvrPort;
	CEdit m_edtCloudSvrPort;
	CButton m_btnOK;
	CButton m_btnCancel;

	CString m_strIP;
	long m_nSvrPort;
};
