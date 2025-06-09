#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\..\..\..\Module\DataMngr\DataGroup.h"
#include "../SttTestAppConfigTool.h"


// CSttTestAppIPConfigDlg �Ի���

class CSttTestAppIPConfigDlg : public CDynDialogEx
{
//	DECLARE_DYNAMIC(CSttTestAppIPConfigDlg)

public:
	CSttTestAppIPConfigDlg(CDataGroup *pDvGroup,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSttTestAppIPConfigDlg();

	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CFont *m_pGlobalFont11;

// �Ի�������
//	enum { IDD = IDD_TESTAPPCONFIG_LOCALCONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickOK();
	afx_msg void OnBtnClickCancel();

public:
	CStatic m_stcDeviceIP;
	CIPAddressCtrl m_ctrlDeviceIP;
	CStatic m_stcDeviceMask;
	CIPAddressCtrl m_ctrlDeviceMask;


	CButton m_btnOK;
	CButton m_btnCancel;

	CDataGroup *m_pDvGroup;
	CString m_strDeviceIP;
	CString m_strDeviceMask;
};
