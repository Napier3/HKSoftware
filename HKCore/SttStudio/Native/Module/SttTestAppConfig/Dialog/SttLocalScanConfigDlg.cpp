// SttLocalScanConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SttLocalScanConfigDlg.h"
#include "../SttTestAppConfigTool.h"
#include "../../API/NetworkInterface.h"
#include "SttTestAppIPConfigDlg.h"


// CSttLocalScanConfigDlg 对话框

//IMPLEMENT_DYNAMIC(CSttLocalScanConfigDlg, CDialog)

CSttLocalScanConfigDlg::CSttLocalScanConfigDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CSttLocalScanConfigDlg::IDD, pParent)
	: CDynDialogEx(pParent)
{
	m_nSvrPort = STT_PORT_TEST_SERVER;

	m_pSttMulticastClientSocket = NULL;
	m_nNextCmdID = 0;

	m_pSttTestAppConfigTool = NULL;
	m_pSttTestAppCfg = NULL;
	m_pGlobalFont11 = font_CreateNew(g_lfGlobalFont11, -11);
}

CSttLocalScanConfigDlg::~CSttLocalScanConfigDlg()
{
	if (m_pGlobalFont11 != NULL)
	{
		delete m_pGlobalFont11;
	}
	OnStopScan();
}

void CSttLocalScanConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_TESTAPP_LOCALSEARCH_GRID, m_grid);
}


BEGIN_MESSAGE_MAP(CSttLocalScanConfigDlg, CDynDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(STT_BTN_SCANLOCAL, &CSttLocalScanConfigDlg::OnBtnClickScan)
	ON_BN_CLICKED(STT_BTN_SELLOCAL, &CSttLocalScanConfigDlg::OnBtnClickSel)
	ON_BN_CLICKED(STT_BTN_CANCEL_1, &CSttLocalScanConfigDlg::OnBtnClickCancel)
	ON_BN_CLICKED(STT_BTN_SET, &CSttLocalScanConfigDlg::OnBtnClickSet)
	ON_BN_CLICKED(STT_BTN_TESTON, &CSttLocalScanConfigDlg::OnBtnClickTestOn)
	ON_BN_CLICKED(STT_BTN_TESTOFF, &CSttLocalScanConfigDlg::OnBtnClickTestOff)
	ON_BN_CLICKED(STT_BTN_TESTLIVEUPDATE, &CSttLocalScanConfigDlg::OnBtnClickTestLiveUpdate)
END_MESSAGE_MAP()

// CSttLocalScanConfigDlg 消息处理程序

void CSttLocalScanConfigDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	BOOL bEnable = (m_grid.GetCurrSelData() != NULL);
	
	m_btnSel.EnableWindow(bEnable);
	m_btnSet.EnableWindow(bEnable);
	m_btnTestOn.EnableWindow(bEnable);
	m_btnTestOff.EnableWindow(bEnable);	
	m_btnTestLiveUpdate.EnableWindow(bEnable);	
}

void CSttLocalScanConfigDlg::OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr)
{

}

BOOL CSttLocalScanConfigDlg::Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec)
{	

	CString strSN = _T(""),strModel = _T("");
	CString strIP = _T(""),strMask = _T("");

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);
	pDatas->FindDataByID(STT_PP_DATAID_IP, strIP, strMask);

	POS pos = m_oGridDatas.GetHeadPosition();
	CDataGroup *pFind = NULL;
	CDataGroup *p= NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)m_oGridDatas.GetNext(pos);

		CString strValue = _T("");
		stt_GetDataValueByID(p, ID_STT_USER_ATTR_SN_TestApp, strValue);
		if (strSN == strValue)
		{
			pFind = p;
			break;
		}
	}

	if (pFind != NULL)
	{
		return TRUE;
	}

	CDataGroup *RecvGroup = new CDataGroup;
	RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
	RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
	CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
	pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, strIP);
	pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, strMask);

	m_oGridDatas.AddTail(RecvGroup);
	m_grid.ShowDatas(&m_oGridDatas);

	return TRUE;
}

BOOL CSttLocalScanConfigDlg::Process_Multicast_Comm_ACK(BYTE nCmdType,CSttPpDatasDriver vec)
{
	CString strSN = _T(""),strModel = _T("");
	long nErrCode = 0;

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);
	pDatas->FindDataByID(STT_PP_DATAID_RUNSTATE, nErrCode);

	if (nErrCode == 0)
	{
		switch(nCmdType)
		{
		case MULTICAST_CMD_SETIP_ACK:
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("设置测试仪【SN=%s】【Model=%s】IP成功。"),strSN,strModel);
			break;
		case MULTICAST_CMD_PROCESS_ACK:
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("启停测试仪【SN=%s】【Model=%s】进程成功。"),strSN,strModel);
			break;
		default:
			break;
		}
	}
	else
	{
		switch(nCmdType)
		{
		case MULTICAST_CMD_SETIP_ACK:
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("设置测试仪【SN=%s】【Model=%s】IP失败【ErrCode=%d】。"),strSN,strModel,nErrCode);
			break;
		case MULTICAST_CMD_PROCESS_ACK:
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("启停测试仪【SN=%s】【Model=%s】进程失败【ErrCode=%d】。"),strSN,strModel,nErrCode);
			break;
		default:
			break;
		}
	}

	return TRUE;
}

BOOL CSttLocalScanConfigDlg::Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec)
{
	CString strSN = _T(""),strModel = _T("");
	long nErrCode = 0;

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);
	pDatas->FindDataByID(STT_PP_DATAID_RUNSTATE, nErrCode);

	if (nErrCode != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("查询测试仪【SN=%s】【Model=%s】运行进程失败【ErrCode=%d】。"),strSN,strModel,nErrCode);
		return FALSE;
	}

	POS pos = pDatas->GetHeadPosition();
	PSTT_PP_DATA p = NULL;
	CString strValue = _T("");
	CString strInfo;
	strInfo.Format(_T("查询测试仪【SN=%s】【Model=%s】运行进程结果："),strSN,strModel);

	while (pos != NULL)
	{
		p = pDatas->GetNext(pos);

		if (p->id != STT_PP_DATAID_PROCESSID)
		{
			continue;
		}

		stt_pp_data_get_string(p, strValue);
		strInfo.AppendFormat(_T("【%s】;"),strValue);
	}

	CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);

	return TRUE;
}

BOOL CSttLocalScanConfigDlg::Process_Multicast_QuerySystemCfg_ACK(CSttPpDatasDriver vec)
{
	CString strSN = _T(""),strModel = _T("");

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);

	CStringArray arrDefaultRunProc,arrCfgProc,arrCfgDriver;
	POS pos = pDatas->GetHeadPosition();
	PSTT_PP_DATA p = NULL;
	CString strValue = _T("");
	CString strInfo;
	strInfo.Format(_T("查询测试仪【SN=%s】【Model=%s】系统配置结果："),strSN,strModel);
	CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);

	while (pos != NULL)
	{
		p = pDatas->GetNext(pos);

		if (p->id == STT_PP_DATAID_DEFAULT_RUNPROC)
		{
			stt_pp_data_get_string(p, strValue);
			arrDefaultRunProc.Add(strValue);
		}
		else if (p->id == STT_PP_DATAID_CFG_PROC)
		{
			stt_pp_data_get_string(p, strValue);
			arrCfgProc.Add(strValue);
		}
		else if (p->id == STT_PP_DATAID_CFG_DRIVER)
		{
			stt_pp_data_get_string(p, strValue);
			arrCfgDriver.Add(strValue);
		}
	}

	CString strList1 = _T("默认启动进程列表：");
	for(int i=0; i<arrDefaultRunProc.GetCount(); i++)
	{
		strList1.AppendFormat(_T("%s;"),arrDefaultRunProc[i]);
	}
	CLogPrint::LogString(XLOGLEVEL_INFOR,strList1);

	CString strList2 = _T("配置进程列表：");
	for(int i=0; i<arrCfgProc.GetCount(); i++)
	{
		strList2.AppendFormat(_T("%s;"),arrCfgProc[i]);
	}
	CLogPrint::LogString(XLOGLEVEL_INFOR,strList2);

	CString strList3 = _T("配置驱动列表：");
	for(int i=0; i<arrCfgDriver.GetCount(); i++)
	{
		strList3.AppendFormat(_T("%s;"),arrCfgDriver[i]);
	}
	CLogPrint::LogString(XLOGLEVEL_INFOR,strList3);

	if (m_nNextCmdID != 0)
	{
		if ((strSN == m_strCmdSN) && (strModel == m_strCmdModel))
		{//需要发送启动关闭命令
			long nNextCmdID = m_nNextCmdID;
			m_nNextCmdID = 0;//清除标记

			int nCnt = arrCfgProc.GetCount();
			CStringArray astrProcRun;
			switch(nNextCmdID)
			{
			case 1:
				{
					CString strPUDAID = _T("");
					for (int i=0; i<nCnt; i++)
					{
						if (arrCfgProc[i] == STT_PROCESS_PUDA)
						{
							strPUDAID = STT_PROCESS_PUDA;
							break;
						}
					}

					if (strPUDAID.IsEmpty())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进程【%s】不存在"),STT_PROCESS_PUDA);
						return FALSE;
					}
					astrProcRun.Add(STT_PROCESS_PUDA);
					break;
				}
			case 2:
				{
					//查找关键字匹配TestServer进程
					CString strTemp = STT_PROCESS_TESTSERVER;
					CString strTestServerID = _T("");
					CString strTestMainCoreID = _T("");
					
					for (int i=0; i<nCnt; i++)
					{
						if ((arrCfgProc[i].Find(strTemp) >= 0) 
							&& (arrCfgProc[i].GetLength() > strTestServerID.GetLength()))
						{
							strTestServerID = arrCfgProc[i];
						}
						else if (arrCfgProc[i].Find(STT_PROCESS_TESTMAINCORE) >= 0) 
						{
							strTestMainCoreID = arrCfgProc[i];
						}
					}

					if (strTestServerID.IsEmpty())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进程【%s】不存在"),STT_PROCESS_TESTSERVER);
						return FALSE;
					}
					if (strTestMainCoreID.IsEmpty())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进程【%s】不存在"),STT_PROCESS_TESTMAINCORE);
						return FALSE;
					}

					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TestServerID:%s;TestMainCoreID:%s"),strTestServerID,strTestMainCoreID);
					astrProcRun.Add(strTestServerID);
					astrProcRun.Add(strTestMainCoreID);
					break;
				}
			case 3:
				{
					CString strLiveUpdateID = _T("");
					for (int i=0; i<nCnt; i++)
					{
						if (arrCfgProc[i] == STT_PROCESS_LIVEUPDATE)
						{
							strLiveUpdateID = STT_PROCESS_LIVEUPDATE;
							break;
						}
					}
					if (strLiveUpdateID.IsEmpty())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("进程【%s】不存在"),STT_PROCESS_LIVEUPDATE);
						return FALSE;
					}

					astrProcRun.Add(STT_PROCESS_LIVEUPDATE);
					break;
				}
			default:
				break;
			}

			m_pSttMulticastClientSocket->Multicast_Process(strSN,strModel,astrProcRun,arrCfgProc);
		}
	}

	return TRUE;
}

void CSttLocalScanConfigDlg::OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec)
{
	switch (nCmdType)
	{
	case MULTICAST_CMD_QUERYIPS_ACK:
		{
			Process_Multicast_QueryIP_ACK(vec);
			break;
		}
	case MULTICAST_CMD_SETIP_ACK:
	case MULTICAST_CMD_PROCESS_ACK:
		{
			Process_Multicast_Comm_ACK(nCmdType,vec);
			break;
		}
	case MULTICAST_CMD_QUERYSERVERSTATE_ACK:
		{
			Process_Multicast_QueryServerState_ACK(vec);
			break;
		}
	case MULTICAST_CMD_QUERYSYSTEMCFG_ACK:
		{
			Process_Multicast_QuerySystemCfg_ACK(vec);
			break;
		}
	default:
		break;	
	}
}

void CSttLocalScanConfigDlg::OnStopMulticastMsg()
{
	OnStopScan();
}

BOOL CSttLocalScanConfigDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_grid.Create(CRect(5,5,630,205), this, STT_GRID_LOCALTESTAPP);
	m_grid.SetFont(g_pGlobalFont11);
	m_grid.InitGrid();
	m_grid.AttachDataViewOptrInterface(this);

	CreateButton(m_btnScan,_T("扫描"), CRect(5,215,85,240), STT_BTN_SCANLOCAL, this);
	CreateButton(m_btnSet,_T("设置"), CRect(95,215,175,240), STT_BTN_SET, this);
	CreateButton(m_btnTestLiveUpdate,_T("启升级"), CRect(220,215,290,240), STT_BTN_TESTLIVEUPDATE, this);
	CreateButton(m_btnTestOn,_T("启PUDA"), CRect(300,215,370,240), STT_BTN_TESTON, this);
	CreateButton(m_btnTestOff,_T("启TestSvr"), CRect(380,215,450,240), STT_BTN_TESTOFF, this);
	CreateButton(m_btnCancel,_T("取消"), CRect(460,215,540,240), STT_BTN_CANCEL_1, this);
	CreateButton(m_btnSel,_T("确定"), CRect(550,215,630,240), STT_BTN_SELLOCAL, this);

	m_btnSet.SetFont(m_pGlobalFont11);
	m_btnScan.SetFont(m_pGlobalFont11);
	m_btnCancel.SetFont(m_pGlobalFont11);
	m_btnTestOff.SetFont(m_pGlobalFont11);
	m_btnTestOn.SetFont(m_pGlobalFont11);
	m_btnTestLiveUpdate.SetFont(m_pGlobalFont11);
	m_btnSel.SetFont(m_pGlobalFont11);

	m_btnSel.EnableWindow(FALSE);
	m_btnSet.EnableWindow(FALSE);
	m_btnTestOff.EnableWindow(FALSE);
	m_btnTestOn.EnableWindow(FALSE);
	m_btnTestLiveUpdate.EnableWindow(FALSE);

// 	m_btnTestOff.ShowWindow(FALSE);
// 	m_btnTestOn.ShowWindow(FALSE);
// 	m_btnTestLiveUpdate.ShowWindow(FALSE);
	MoveWindow(CRect( 0, 0, 650, 250), TRUE);

	return TRUE;
}

void CSttLocalScanConfigDlg::OnBtnClickScan()
{
	if(m_pSttMulticastClientSocket == NULL)
	{
		m_pSttMulticastClientSocket = new CSttMulticastClientSocket;
	
		if(!m_pSttMulticastClientSocket->Create(m_pSttTestAppCfg->GetMulticastIP()
			,m_pSttTestAppCfg->GetMulticastPort()
			,m_pSttTestAppCfg->GetLocalIP()
			,m_pSttTestAppCfg->GetMulticastPort()))
		{
			return;
		}

		m_oGridDatas.DeleteAll();
		m_grid.ShowDatas(&m_oGridDatas);
		m_btnScan.SetWindowText(_T("停止扫描"));

		m_nNextCmdID = 0;//清除标记
		m_pSttMulticastClientSocket->AttatchSttMulticastMsgViewInterface(this);
		SetTimer(1,2000,NULL);
	}
	else
	{
		OnStopScan();
	}
}

void CSttLocalScanConfigDlg::OnBtnClickSel()
{
	CDataGroup *pGroup = (CDataGroup *)m_grid.GetCurrSelData();
	CDataGroup *pFindGroup = (CDataGroup *)pGroup->FindByDataType(STT_SYS_DATA_ID_DeviceIP);
	if (pFindGroup == NULL)
	{
		return;
	}

	//停止扫描
	OnStopScan();	

	CString strIP = _T("");
	stt_GetDataValueByID(pFindGroup, STT_SYS_DATA_ID_IP, strIP);
	BOOL bRet = m_pSttTestAppConfigTool->Local_ConnectServer(m_pSttTestAppCfg, strIP,m_nSvrPort,m_pSttTestAppConfigTool->m_strSoftID);

	if(!bRet)
	{
		MessageBox(_T("连接测试仪失败"),_T("提示"),MB_OK);
		return;
	}

	m_pSttTestAppCfg->SetTestAppIP(strIP);

	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDOK,STT_LOCALSCANCONFIG_DLG_INDEX);	
}

void CSttLocalScanConfigDlg::OnBtnClickSet()
{//设置后，清除列表，重新扫描
	CDataGroup *pGroup = (CDataGroup *)m_grid.GetCurrSelData();
	CSttTestAppIPConfigDlg oDlg(pGroup);
	if (oDlg.DoModal() != IDOK)
	{
		return;
	}
	CString strIP=_T(""),strMask=_T("");
	strIP = oDlg.m_strDeviceIP;
	strMask = oDlg.m_strDeviceMask;

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(pGroup, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(pGroup, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	//设置后清除列表
	m_oGridDatas.DeleteAll();
	m_grid.ShowDatas(&m_oGridDatas);
	m_btnSet.EnableWindow(FALSE);

	if(m_pSttMulticastClientSocket == NULL)
	{
		OnBtnClickScan();
	}

	m_pSttMulticastClientSocket->Multicast_SetIPV4s(strSN,strModel,strIP,strMask);
}

void CSttLocalScanConfigDlg::OnBtnClickTestOn()
{//启PUDA、杀TestServer
	CDataGroup *pGroup = (CDataGroup *)m_grid.GetCurrSelData();

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(pGroup, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(pGroup, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

// 	CStringArray astrProcRun, astrProcClose;
// 	astrProcRun.Add(STT_PROCESS_PUDA);
// 	astrProcClose.Add(STT_PROCESS_TESTSERVER);

	if(m_pSttMulticastClientSocket == NULL)
	{
		OnBtnClickScan();
	}

	m_nNextCmdID = 1;
	m_strCmdSN = strSN;
	m_strCmdModel = strModel;
	m_pSttMulticastClientSocket->Multicast_QuerySystemCfg(strSN,strModel);

// 	m_pSttMulticastClientSocket->Multicast_Process(strSN,strModel,astrProcRun,astrProcClose);
// 	astrProcRun.RemoveAll();
// 	astrProcClose.RemoveAll();
}

void CSttLocalScanConfigDlg::OnBtnClickTestOff()
{//启TestServer，杀PUDA
	CDataGroup *pGroup = (CDataGroup *)m_grid.GetCurrSelData();

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(pGroup, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(pGroup, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

// 	CStringArray astrProcRun, astrProcClose;
// 	astrProcRun.Add(STT_PROCESS_TESTSERVER);
// 	astrProcClose.Add(STT_PROCESS_PUDA);

	if(m_pSttMulticastClientSocket == NULL)
	{
		OnBtnClickScan();
	}

	m_nNextCmdID = 2;
	m_strCmdSN = strSN;
	m_strCmdModel = strModel;
	m_pSttMulticastClientSocket->Multicast_QuerySystemCfg(strSN,strModel);

// 	m_pSttMulticastClientSocket->Multicast_Process(strSN,strModel,astrProcRun,astrProcClose);
// 	astrProcRun.RemoveAll();
// 	astrProcClose.RemoveAll();
}

void CSttLocalScanConfigDlg::OnBtnClickTestLiveUpdate()
{//启LiveUpdate，杀PUDA,TestServer
	CDataGroup *pGroup = (CDataGroup *)m_grid.GetCurrSelData();

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(pGroup, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(pGroup, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

// 	CStringArray astrProcRun, astrProcClose;
// 	astrProcRun.Add(STT_PROCESS_LIVEUPDATE);
// 	astrProcClose.Add(STT_PROCESS_PUDA);
// 	astrProcClose.Add(STT_PROCESS_TESTSERVER);
// 	astrProcClose.Add(STT_PROCESS_TESTMAINCORE);

	if(m_pSttMulticastClientSocket == NULL)
	{
		OnBtnClickScan();
	}

	m_nNextCmdID = 3;
	m_strCmdSN = strSN;
	m_strCmdModel = strModel;
	m_pSttMulticastClientSocket->Multicast_QuerySystemCfg(strSN,strModel);

// 	m_pSttMulticastClientSocket->Multicast_Process(strSN,strModel,astrProcRun,astrProcClose);
// 	astrProcRun.RemoveAll();
// 	astrProcClose.RemoveAll();
}

void CSttLocalScanConfigDlg::OnStopScan()
{
	m_nNextCmdID = 0;//清除标记

	if(m_pSttMulticastClientSocket != NULL)
	{
		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
		if(::IsWindow(m_hWnd))
		{
			KillTimer(1);
		}
	}

	if (::IsWindow(m_btnScan.m_hWnd))
	{
		m_btnScan.SetWindowText(_T("扫描"));
	}
}

void CSttLocalScanConfigDlg::OnBtnClickCancel()
{
	CWnd *pParentWnd = this->GetParentOwner();
	pParentWnd->PostMessage(TESTAPPCONFIG_OK_MSG,IDCANCEL,0);
}

void CSttLocalScanConfigDlg::OnTimer(UINT nIDEvent)
{
	if (m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->Multicast_QueryIP();
	}
}