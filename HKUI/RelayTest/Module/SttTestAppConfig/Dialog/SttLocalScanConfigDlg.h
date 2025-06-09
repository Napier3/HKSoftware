#pragma once
#include "..\..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\Grid\LocalScan_TestAppGrid.h"

#include "..\..\..\Module\SttSocket\Multicast\SttMulticastClientSocket.h"
#include "../SttTestAppConfigTool.h"

#define STT_GRID_LOCALTESTAPP			0x000002020
#define STT_BTN_SCANLOCAL				0x000002021
#define STT_BTN_SELLOCAL				0x000002022
#define STT_BTN_CANCEL_1				0x000002023
#define STT_BTN_SET						0x000002024
#define STT_BTN_TESTON					0x000002025
#define STT_BTN_TESTOFF					0x000002026
#define STT_BTN_TESTLIVEUPDATE			0x000002027

// CSttLocalScanConfigDlg 对话框

class CSttLocalScanConfigDlg : public CDynDialogEx,public CSttMulticastMsgViewInterface, public CExBaseListGridOptrInterface
{
	//	DECLARE_DYNAMIC(CSttLocalScanConfigDlg)

public:
	CSttLocalScanConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSttLocalScanConfigDlg();

	CSttTestAppConfigTool *m_pSttTestAppConfigTool;
	CSttTestAppCfg *m_pSttTestAppCfg;
	CFont *m_pGlobalFont11;

public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar){return TRUE;}
public:
	virtual void OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr);
	virtual void OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec);
	virtual void OnStopMulticastMsg();

	BOOL Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec);
	BOOL Process_Multicast_Comm_ACK(BYTE nCmdType,CSttPpDatasDriver vec);
	BOOL Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec);
	BOOL Process_Multicast_QuerySystemCfg_ACK(CSttPpDatasDriver vec);


	// 对话框数据
	//	enum { IDD = IDD_TESTAPPCONFIG_LOCALSEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickScan();
	afx_msg void OnBtnClickSel();
	afx_msg void OnBtnClickCancel();
	afx_msg void OnBtnClickSet();
	afx_msg void OnBtnClickTestOn();
	afx_msg void OnBtnClickTestOff();
	afx_msg void OnBtnClickTestLiveUpdate();
	afx_msg void OnTimer(UINT nIDEvent);

public:
	CLocalScan_TestAppGrid m_grid;
	CButton m_btnScan;
	CButton m_btnSel;
	CButton m_btnCancel;
	CButton m_btnSet;
	CButton m_btnTestOn;
	CButton m_btnTestOff;
	CButton m_btnTestLiveUpdate;

	long m_nSvrPort;
public:
	CSttMulticastClientSocket *m_pSttMulticastClientSocket;
	CExBaseList m_oGridDatas;
	void OnStopScan();

public:
	long m_nNextCmdID;
	CString m_strCmdSN;
	CString m_strCmdModel;
};