#include "stdafx.h"
#include "SttTestEngineClientData.h"
#include "../SttCmdToolMngr.h"
#include "../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//全局测试端ID
DWORD g_nIDTester = stt_GetMachineCode_U32();
CDataGroup *g_pDeviceAttrs = NULL;  //装置属性  shaolei  20210528

long g_nTimeOut_System = 20000;
long g_nTimeOut_Test = 30000;
long g_nTimeOut_Ats = 5000;
long g_nTimeOut_Debug = 3000;
long g_nTimeOut_Remote = 3000;
long g_nTimeOut_Adjust = 3000;
long g_nTimeOut_Meas = 3000; //2021-9-30  lijunqing

//2022-3-14  lijunqing  生成模板的时候，带调试信息，例如：返回默认报告数据用于调试报告填写等
long g_nAtsGenTemplateForDebug = 0;

//////////////////////////////////////////////////////////////////////////
//
CSttTestEngineClientData::CSttTestEngineClientData()
{
	m_pSttClientSocket = NULL;
	m_pTestEventRcv = NULL;
	m_pSttSvrUserMngrRef = NULL;
	m_bHasLogin = FALSE;
	m_bTestStarted = FALSE;
}

CSttTestEngineClientData::~CSttTestEngineClientData()
{
	if (m_pSttClientSocket != NULL)
	{
		//m_pSttClientSocket->ExitSocketThread();
		delete m_pSttClientSocket;
		m_pSttClientSocket = NULL;
	}

    if (g_pDeviceAttrs != NULL)
	{
        g_pDeviceAttrs->DeleteAll();
        delete g_pDeviceAttrs;
        g_pDeviceAttrs = NULL;
	}
}

void CSttTestEngineClientData::PrepareFreeClientEngine()
{
	DisConnect();

	CTickCount32 oTick;
	while(m_pSttClientSocket != NULL)
	{
		oTick.DoEvents(5);
	}
}

void CSttTestEngineClientData::SetSttSvrUserMngrRef(CSttTestClientUserMngr *pSttSvrUserMngrRef)
{
	m_pSttSvrUserMngrRef = pSttSvrUserMngrRef;	
}

void CSttTestEngineClientData::SetTestEventInterface(CTestEventBaseInterface *pTestEventRcv)
{
	m_pTestEventRcv  = pTestEventRcv;
}

//2022-10-23  lijunqing
void CSttTestEngineClientData::SetSttCmdDataFormat(long nSttCmdDataFormat)
{
	if (m_pSttClientSocket != NULL)
	{
		m_pSttClientSocket->m_nSttCmdDataFormat = nSttCmdDataFormat;
	}
}

//////////////////////////////////////////////////////////////////////////
//
//系统的状态
long CSttTestEngineClientData::GetSysStateVal(const CString &strID, long nDefaultValue)
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, strID, nDefaultValue);
}

//电流过载
BOOL CSttTestEngineClientData::IOverLoad()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_IOverLoad, 0) > 0;
}

//电压过载
BOOL CSttTestEngineClientData::UOverLoad()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_UOverLoad, 0) > 0;
}

//过热
BOOL CSttTestEngineClientData::OverHeat()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_OverHeat, 0) > 0;
}

//电流开路
BOOL CSttTestEngineClientData::IBreak()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_IBreak, 0) > 0;
}

//电压短路
BOOL CSttTestEngineClientData::UShort()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_UShort, 0) > 0;
}

//命令执行状态   0=执行失败   1=执行成功
long CSttTestEngineClientData::ExecStatus()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_ExecStatus, 0);
}

BOOL CSttTestEngineClientData::ExecStatus_Faild()
{
	return 0 == ExecStatus();
}

BOOL CSttTestEngineClientData::ExecStatus_Success()
{
	return 0 < ExecStatus();
}

//通讯状态   0=无连接 1=链接成功  其他=自定义
long CSttTestEngineClientData::ConnectState()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_ConnectState, 0);
}

BOOL CSttTestEngineClientData::ConnectState_Idle()
{
	return 0 == ConnectState();
}

BOOL CSttTestEngineClientData::ConnectState_Testingt()
{
	return 1 == ConnectState();
}

BOOL CSttTestEngineClientData::ConnectState_Finish()
{
	return 2 == ConnectState();
}


//输出状态   0=空闲   1=已开始  2=已完成
long CSttTestEngineClientData::OutputState()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_OutputState, 0);
}

BOOL CSttTestEngineClientData::OutputState_Idle()
{
	return 0 == OutputState();
}

BOOL CSttTestEngineClientData::OutputState_Testing()
{
	return 1 == OutputState();
}

BOOL CSttTestEngineClientData::OutputState_Finish()
{
	return 2 == OutputState();
}


//序列状态   0=空闲 1=状态1已开始  2=状态2已开始  ……
long CSttTestEngineClientData::CurrStateIndex()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_CurrStateIndex, 0);
}

//错误的命令错误命令的ID
BOOL CSttTestEngineClientData::ErrCmd()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_ErrCmd, 0) > 0;
}

//对象不存在不存在的数据，比如文件、项目ID等
BOOL CSttTestEngineClientData::DataNotExist()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_DataNotExist, 0) > 0;
}

//是否成功   0=失败    1=成功
BOOL CSttTestEngineClientData::IsSuccess()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_IsSuccess, 0) > 0;
}

//测试时间总长测试项目预计测试时间长度
long CSttTestEngineClientData::TestTimeLong()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_TestTimeLong, 0);
}

//测试状态   0=空闲  1=已开始 2=已完成（结束）
long CSttTestEngineClientData::TestState()
{
	return stt_GetDataValueByID2(&m_oTestGlobalParas, STT_SYS_STATE_ID_TestState, 0);
}

BOOL CSttTestEngineClientData::TestState_Idle()
{
	return 0 == TestState();
}

BOOL CSttTestEngineClientData::TestState_Testingt()
{
	return 1 == TestState();
}

BOOL CSttTestEngineClientData::TestState_Finish()
{
	return 2 == TestState();
}



//////////////////////////////////////////////////////////////////////////
BOOL CSttTestEngineClientData::IsConnectServerSucc()
{
	if (m_pSttClientSocket == NULL)
	{
		return FALSE;
	}

	if (m_pSttClientSocket->m_hSocket == NULL)
	{
		return FALSE;
	}

// 	if (m_pSttClientSocket->IsSocketClose())
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

void CSttTestEngineClientData::OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket)
{
	m_bTestStarted = FALSE;

	if (m_pSttClientSocket != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s Disconnect"), pSocket->m_strIPRemote.GetString());
//		CSttClientSocket *pCSttClientSocket = (CSttClientSocket*)m_pSttClientSocket;
		OnLogout();
		CSttCmdOverTimeTool::OnSocketClosed(pSocket);
		delete m_pSttClientSocket;
		m_pSttClientSocket = NULL;

		if(m_pTestEventRcv != NULL)
		{
			m_pTestEventRcv->OnDisConnect();
		}	
	}
}

void CSttTestEngineClientData::DisConnect()
{
	if (m_pSttClientSocket != NULL)
	{
		m_pSttClientSocket->CloseSocket();
	}
}

long CSttTestEngineClientData::SendBuffer(BYTE *pBuf,long nLen)
{
    if(m_pSttClientSocket == NULL)
    {
        return 0;
    }

    return m_pSttClientSocket->SendBuffer(pBuf, nLen);
}

long CSttTestEngineClientData::SendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData
										   ,BOOL bDoEvents,BOOL bCompress,BOOL bReset)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	return m_pSttClientSocket->SendCmdSync(pCmd,nTimeOut,pRetData,bDoEvents,bCompress,bReset);
}

long CSttTestEngineClientData::SendCmdAsync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv
											, BOOL bCompress,BOOL bReset)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	return m_pSttClientSocket->SendCmdAsync(pCmd,nTimeOut, pSttCmdOverTimeMsgRcv,bCompress,bReset);
}

long CSttTestEngineClientData::SendCmdOnly(CSttCmdBase *pCmd, BOOL bCompress,BOOL bReset)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	long nRet = m_pSttClientSocket->SendCmd(pCmd,bCompress,bReset);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>> Send cmd %s"), pCmd->m_strID.GetString());

	return nRet;
}

//system command
long CSttTestEngineClientData::System_SetSysConfig(CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_SetSysConfig;
	oSysCmd.AppendParas2(*pParas);

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

long CSttTestEngineClientData::System_GetSysConfig(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_GetSysConfig;

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

//2022-3-23  lijunqing
long CSttTestEngineClientData::System_GetDirs(CDataGroup *pParas, BOOL bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_GetDirs;
	oSysCmd.AppendParas2(*pParas);

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

long CSttTestEngineClientData::System_DownFile(CDataGroup *pParas, BOOL bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_DownFile;
	oSysCmd.AppendParas2(*pParas);

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

long CSttTestEngineClientData::System_Login(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	m_bHasLogin = FALSE;

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Login;
	oSysCmd.m_strTestor = m_oCurrUser.id_soft();
	m_oCurrUser.InitSttSystemCmd(oSysCmd);

	long nRet = SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);

	if (pRetData != NULL)
	{
		CSttParas *pParas = pRetData->GetSttParas();
		CDataGroup *pDevAttrs = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_DeviceAttrs);

		if (pDevAttrs != NULL)
		{
            if(g_pDeviceAttrs != NULL)
            {
                g_pDeviceAttrs->DeleteAll();
                delete g_pDeviceAttrs;
                g_pDeviceAttrs = NULL;
            }
            g_pDeviceAttrs = (CDataGroup *)pDevAttrs->CloneEx(TRUE, TRUE);
		}
	}
	return nRet;
}

long CSttTestEngineClientData::System_Login_Local_Test(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return System_Login_Local(STT_SOFT_ID_TEST,bDoEvents,pRetData);
}

long CSttTestEngineClientData::System_Login_Local_ATS(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return System_Login_Local(STT_SOFT_ID_ATS,bDoEvents,pRetData);
}

long CSttTestEngineClientData::System_Login_Local(const CString &strTestID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
#ifdef  _PSX_QT_LINUX_
    m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_NATIVE);
#else
	m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_LOCAL);
#endif
	m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);

#ifdef STT_TEST_CMD_USE_RandomNum
	//ID_Tester改为随机数 2024-6-4
	srand((unsigned int)time(NULL));
	unsigned int nIDTester = rand();
	m_oCurrUser.ID_Tester(nIDTester/*g_nIDTester*/);
#else
	m_oCurrUser.ID_Tester(g_nIDTester);
#endif
	m_oCurrUser.IP_User(m_pSttClientSocket->m_strIPLocal);
	m_oCurrUser.Name_User(m_pSttClientSocket->m_strIPLocal);
	m_oCurrUser.id_soft(strTestID);

	return System_Login(bDoEvents,pRetData);
}

long CSttTestEngineClientData::System_Logout(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Logout;
	oSysCmd.AddNewParasData(ID_STT_USER_ATTR_ID_Terminal,m_oCurrUser.ID_Terminal());
	oSysCmd.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp,m_oCurrUser.SN_TestApp());
	oSysCmd.AddNewParasData(STT_CMD_PARA_IDTESTER,m_oCurrUser.ID_Tester());

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}


long CSttTestEngineClientData::System_Request(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Request;
	oSysCmd.AddNewParasData(strAuthorityID, nAuthorityVal);

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

long CSttTestEngineClientData::System_Authority(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Authority;
	oSysCmd.AddNewParasData(strAuthorityID, nAuthorityVal);

	return SendCmdSync(&oSysCmd,g_nTimeOut_System,pRetData,bDoEvents);
}

//////////////////////////////////////////////////////////////////////////
//remote command
long CSttTestEngineClientData::Remote_Bind(CSttTestRemoteRegister *pRegister,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if ((m_pSttClientSocket == NULL) || (pRegister == NULL))
	{
		return 0;
	}

	CSttRemoteCmd oCmd;
	CString strCode_Register,strSN_TestApp;
	strCode_Register = pRegister->Code_Register();
	strSN_TestApp = pRegister->SN_TestApp();

	oCmd.m_strID = STT_CMD_TYPE_REMOTE_Bind;
	oCmd.AddNewParasData(ID_STT_USER_ATTR_Code_Register,strCode_Register);
	oCmd.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp,strSN_TestApp);
	oCmd.AddNewParasData(STT_CMD_PARA_IDTESTER,g_nIDTester);

	return SendCmdSync(&oCmd,g_nTimeOut_Remote,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Remote_Query(const CString &strCode_Register,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttRemoteCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_REMOTE_Query;
	oCmd.AddNewParasData(ID_STT_USER_ATTR_Code_Register,strCode_Register);

	return SendCmdSync(&oCmd,g_nTimeOut_Remote,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Remote_Register(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttRemoteCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_REMOTE_Register;
	oCmd.AppendClone(m_oCurrUser);

	return SendCmdSync(&oCmd,g_nTimeOut_Remote,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Remote_UnRegister(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttRemoteCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_REMOTE_UnRegister;
	oCmd.AppendClone(m_oCurrUser);

	return SendCmdSync(&oCmd,g_nTimeOut_Remote,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_SetParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_SetParameter;
	oTestCmd.SetParameter(strMacroID, pParas);

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_UpdateParameter;
	oTestCmd.SetParameter(strMacroID, pParas);

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_StartTest(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents
											  ,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	m_bTestStarted = TRUE;

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oTestCmd.SetParameter(strMacroID, pParas);

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Test_StartTest  ++  MacroID = %s"), strMacroID.GetString());

//#ifndef _PSX_QT_LINUX_
// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
// 	CString strTmpPath = _P_GetLibraryPath();
// 	strTmpPath.AppendFormat(_T("Test_StartTest%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
// 		, tm.wHour, tm.wMinute, tm.wSecond);
// 	oTestCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
//#endif

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oTestCmd,g_nTimeOut_Test);
	}
	long nExecStatus = SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		m_bTestStarted = FALSE;
	}
	return nExecStatus;
}

long CSttTestEngineClientData::Test_StopTest(const CString &strMacroID,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++进入函数：CSttTestEngineClientData::Test_StopTest"));
	if (m_pSttClientSocket == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CSttTestEngineClientData::Test_StopTest+++m_pSttClientSocket==NULL"));
		return 0;
	}

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StopTest;
	oTestCmd.SetParameter(strMacroID, NULL);

// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
// 	CString strTmpPath = _P_GetLibraryPath();
// 	strTmpPath.AppendFormat(_T("Test_StopTest%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
// 		, tm.wHour, tm.wMinute, tm.wSecond);
// 	oTestCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oTestCmd,g_nTimeOut_Test);
	}

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_GetReport(const CString &strMacroID,BOOL bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_GetReport;
	oTestCmd.SetParameter(strMacroID, NULL);

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_CloseDevice(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_CloseDevice;

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_GetSystemState(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oTestCmd; //2021-10-6  lijunqing  由TestCmd改为SystemCmd
	oTestCmd.m_strID = STT_CMD_TYPE_SYSTEM_GetSystemState;
	CSttParas *pParas = oTestCmd.GetSttParas();
	pParas->AddDatas(astrTypes);

	return SendCmdSync(&oTestCmd,g_nTimeOut_Test,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Test_SendHeartbeat()
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	BYTE pSendBuf[STT_PKG_HEAD_LEN];
	long nSendBufLen = 0;

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_HEARTBEAT, 0, 
		m_oCurrUser.ID_Tester(), 0, 0);

	return m_pSttClientSocket->SendBuffer(pSendBuf,STT_PKG_HEAD_LEN);
}

//校准命令：adj-cmd
long CSttTestEngineClientData::Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents
											 ,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAdjustCmd oAdjustCmd;
	oAdjustCmd.m_strID = STT_CMD_TYPE_ADJUST_Adjust;
	oAdjustCmd.SetParameter(strMacroID, pParas);

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oAdjustCmd,g_nTimeOut_Adjust);
	}

	return SendCmdSync(&oAdjustCmd,g_nTimeOut_Adjust,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAdjustCmd oAdjustCmd;
	oAdjustCmd.m_strID = STT_CMD_TYPE_ADJUST_ReadDeviceParameter;
	CSttParas *pParas = oAdjustCmd.GetSttParas();
	pParas->AddDatas(astrTypes);

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oAdjustCmd,g_nTimeOut_Adjust);
	}

	return SendCmdSync(&oAdjustCmd,g_nTimeOut_Adjust,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Adjust_WriteFile(BOOL bSendCmdAsync, BOOL bDoEvents)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAdjustCmd oAdjustCmd;
	oAdjustCmd.m_strID = STT_CMD_TYPE_ADJUST_WriteFile;
	oAdjustCmd.SetParameter(_T("WriteFile"), NULL);

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oAdjustCmd,g_nTimeOut_Adjust);
	}

	return SendCmdSync(&oAdjustCmd,g_nTimeOut_Adjust, NULL, bDoEvents);
}

//2021-9-30  lijunqing
long CSttTestEngineClientData::Meas_Read(BOOL bSendCmdAsync, BOOL bDoEvents)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_ReadMeas;

	if (bSendCmdAsync)
	{
		return SendCmdAsync(&oSysCmd,g_nTimeOut_Meas);
	}

	return SendCmdSync(&oSysCmd,g_nTimeOut_Meas, NULL, bDoEvents);
}

//故障回放命令
//上位机给测试仪：手动触发命令、数据发送完成命令
long CSttTestEngineClientData::Test_SendTrigger()
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	BYTE pSendBuf[STT_PKG_HEAD_LEN];
	long nSendBufLen = 0;

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_TRIGGER, 0, 
		m_oCurrUser.ID_Tester(), 0, 0);

	return m_pSttClientSocket->SendBuffer(pSendBuf,STT_PKG_HEAD_LEN);
}

long CSttTestEngineClientData::Comtrade_SendDataStart(long nIndex,long nSendLen)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("回放数据【index=%d,SendLen=%d】准备发送"),nIndex,nSendLen);

	BYTE pSendBuf[STT_PKG_HEAD_LEN+10];
	long nDataLen = 9;
	pSendBuf[STT_PKG_HEAD_LEN] = STT_CMD_TYPE_COMTRADE_SENDDATASTART;
	memcpy(pSendBuf+STT_PKG_HEAD_LEN+1,&nIndex,4);
	memcpy(pSendBuf+STT_PKG_HEAD_LEN+5,&nSendLen,4);

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_COMTRADE, nDataLen, 
		m_oCurrUser.ID_Tester(), 0, 0);

	return m_pSttClientSocket->SendBuffer(pSendBuf,STT_PKG_HEAD_LEN+nDataLen);
}

long CSttTestEngineClientData::Comtrade_SendDataFinish(long nIndex,long nSendLen,BOOL bLast)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("回放数据【index=%d,SendLen=%d】已发送完成"),nIndex,nSendLen);

	if (bLast)
	{
		nIndex |= 0x80000000;
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("回放数据全部发送完成"));
	}
	
	BYTE pSendBuf[STT_PKG_HEAD_LEN+10];
	long nDataLen = 9;
	pSendBuf[STT_PKG_HEAD_LEN] = STT_CMD_TYPE_COMTRADE_SENDDATAFINISH;
	memcpy(pSendBuf+STT_PKG_HEAD_LEN+1,&nIndex,4);
	memcpy(pSendBuf+STT_PKG_HEAD_LEN+5,&nSendLen,4);

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_COMTRADE, nDataLen, 
						   m_oCurrUser.ID_Tester(), 0, 0);

	return m_pSttClientSocket->SendBuffer(pSendBuf,STT_PKG_HEAD_LEN+nDataLen);
}

//////////////////////////////////////////////
//ats cmd
long CSttTestEngineClientData::Ats_CreateTest(CExBaseList *pSttParas, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_CreateTest;
	CSttParas *p = oAtsCmd.GetSttParas();
	p->AppendClone(pSttParas);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
											  ,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas
											  ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_CreateTest;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_Test_ID, strTestID);
	oAtsCmd.AddNewParasData(XPARA_ID_GBXMLFILE, strGbXmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_PPXMLFILE, strPpXmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_DVMFILE, strDvmFile);
	oAtsCmd.AddNewParasData(XPARA_ID_CommCfgFile, strCommCfgFile);

	pCommParas->m_strID = STT_CMD_PARA_CommConfig;
	oAtsCmd.AddNewParas(pCommParas);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas
												 ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ConnectDevice;
	oAtsCmd.AddNewParasData(XPARA_ID_PPXMLFILE, strPpXmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_DVMFILE, strDvmFile);

	pCommParas->m_strID = STT_CMD_PARA_CommConfig;
	oAtsCmd.AddNewParas(pCommParas);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

void atscmd_Init_Paras(CSttParas *pParas, CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup*pCommcmd, CSttContents *pCharacteristic)
{
	CDataGroup *pGroup = NULL;
	
	if (pTestMacroUI != NULL)
	{
		pGroup = pParas->AddNewGroup(STT_CMD_PARA_TestMacroUI, STT_CMD_PARA_TestMacroUI, _T(""));
		pGroup->AppendCloneEx(*pTestMacroUI, TRUE);
	}

	if (pUIParas != NULL)
	{
		pGroup = pParas->AddNewGroup(STT_CMD_PARA_MacroUIParas, STT_CMD_PARA_MacroUIParas, _T(""));
		pGroup->AppendCloneEx(*pUIParas, TRUE);
	}

	//通讯命令生成向导相关的配置
	if (pCommcmd != NULL)
	{
		if (pCommcmd->GetCount() > 0)
		{
			pGroup = pParas->AddNewGroup(STT_CMD_PARA_CommCmd, STT_CMD_PARA_CommCmd, _T(""));
			pGroup->AppendCloneEx(*pCommcmd, TRUE);
		}
	}

	//特性曲线定义
	if (pCharacteristic != NULL)
	{
		CSttContents *pNew = new CSttContents;
		pCharacteristic->CopyOwn(pNew);
		pParas->AddNewChild(pNew);
	}
}

long CSttTestEngineClientData::Ats_StartTest(CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup *pCommCmd
											 , CSttContents *pCharacteristic, BOOL bDoEvents,CSttCmdData *pRetData
											 ,const CString &strDvmFile, const CString &strPpXmlFile,long nTestMode)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	m_bTestStarted = TRUE;

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_StartTest;
	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_DvmFile, strDvmFile/*_T("SttIecRecordDetectDvm.xml")*/);  //20221011 zhouhj 暂时先直接赋值,后期考虑改进传参方式,或增加成员变量方式处理
	pParas->AddNewData(XPARA_ID_PPXMLFILE, strPpXmlFile);
	pParas->AddNewData(STT_CMD_PATA_TestMode, nTestMode);
	atscmd_Init_Paras(pParas, pTestMacroUI, pUIParas, pCommCmd, pCharacteristic);
	long nExecStatus = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Ats_StartTest(%ld)"),nExecStatus);

	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		m_bTestStarted = FALSE;
	}

	return nExecStatus;
}

long CSttTestEngineClientData::Ats_StopTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_StopTest;
	long nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Ats_StopTest(%ld)"),nRet);
	return nRet;
}

long CSttTestEngineClientData::Ats_CloseTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_CloseTest;
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ManuTrigger(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ManuTriger;
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

/*
<ats-cmd name="" id="SetTestPara" testor="ATS">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="SN"/>
		<group name="" id="Paras">
			<data name="参数1" id="Para1" value="0.25" />
			<data name="参数2" id="Para2" value="0.25999999" />
			<data name="参数3" id="Para3" value="0.75" />
			……
		</group>
	</paras>
</ats-cmd>
*/
long CSttTestEngineClientData::Ats_SetTestParas(const CString &strDeviceID, CExBaseList *pTestParas, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetTestPara;
	CSttParas *pSttPatas = oAtsCmd.GetSttParas();
	pSttPatas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pSttPatas->AddNewChild(pTestParas);//此处直接AddNewChild，需要pTestParas是new出来的，且未释放
	long nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	return nRet;
}

long CSttTestEngineClientData::Ats_SetItemState(CExBaseList *pSttParas, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetItemState;
	//shaolei 此处不能直接AddNewParas，若形参是paras则报文结构就不正确了
	//shaolei 20220628
	//oAtsCmd.AddNewParas(pSttParas);
	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AppendCloneEx2(*pSttParas);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable
												,long nShow,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetItemState;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_ItemPath,strItemPath);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_Select,nSelect);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_Enable,nEnable);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_Show,nShow);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_TestItem (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_TestItem;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_ItemPath, strItemPath);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_TestFrom;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_ItemPath, strItemPath);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_TestAllFailedItems(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_TestAllFailedItems;
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath
												 ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GetReportFile;
	oAtsCmd.AddNewParasData(XPARA_ID_GBRPTFILE, nGbrptFile);
	oAtsCmd.AddNewParasData(XPARA_ID_XmlRptFile, nXmlRptFile);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_DestPath, strDestPath);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::GetSystemState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GetSystemState;
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
				,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas
				,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_CreateDevice;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_DeviceID, strDeviceID);
	oAtsCmd.AddNewParasData(XPARA_ID_PPXMLFILE, strPpXmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_DVMFILE, strDvmFile);
	oAtsCmd.AddNewParasData(XPARA_ID_CommCfgFile, strCommCfgFile);

	pCommParas->m_strID = STT_CMD_PARA_CommConfig;
	oAtsCmd.AddNewParas(pCommParas);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ConfigDevice;

	pCommParas->m_strID = STT_CMD_PARA_CommConfig;
	oAtsCmd.AddNewParas(pCommParas);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GetDataset;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_DatasetPath, strDatasetPath);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset
											  ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetDataset;
	oAtsCmd.AddNewParas(pDataset);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset
												,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_RunProcedure;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_DatasetPath, strDatasetPath);

	oAtsCmd.AddNewParas(pData);
	oAtsCmd.AddNewParas(pDataset);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_CloseDevice;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_DeviceID, strDeviceID);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
								 ,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ConfigEngine;
	oAtsCmd.AddNewParasData(STT_CMD_PARA_LogDataBind, nLogDataBind);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_LogPkgDataInfo, nLogPkgDataInfor);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_LogPkg, nLogPkg);
    oAtsCmd.AddNewParasData(STT_CMD_PARA_LogServerDebugInfor, nLogDebugInfor);
	oAtsCmd.AddNewParasData(STT_CMD_PARA_NoChangeWhenSame, nNoChangeWhenSame);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_FinishInputData;
	if (pDatas != NULL)
	{
		oAtsCmd.AppendParas2(*pDatas);
	}
	if (pMsgs != NULL)
	{
		oAtsCmd.AppendMsgs(*pMsgs);
	}
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats);
}

long CSttTestEngineClientData::Ats_QueryAtsFile(long nGetGbxmlFile,long nGetPpxmlFile,long nGetDvmFile,long nGetGbrptFile
												,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_QueryAtsFile;
	oAtsCmd.AddNewParasData(XPARA_ID_GBXMLFILE, nGetGbxmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_PPXMLFILE, nGetPpxmlFile);
	oAtsCmd.AddNewParasData(XPARA_ID_DVMFILE, nGetDvmFile);
	oAtsCmd.AddNewParasData(XPARA_ID_GBRPTFILE, nGetGbrptFile);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Process_Cmd_Ats_InputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
	long nRet = pClientSocket->SendSysState(&oSysState);

	//通知界面弹框
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("通知界面弹框"));
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->Event_OnProcessInputDataCmd(oAtsCmd);
	}
	
    return nRet;
}

//2022-1-8 LINUX脱机以及移动端应用接口指令

long CSttTestEngineClientData::Ats_GenerateTemplate(CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup*pCommcmd
													, CSttContents *pCharacteristic, const CString &strRetMode, long nHasDigital
													, bool bDoEvents, CSttCmdData *pRetData,const CString &strDvmFile,const CString &strPpXmlFile)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_TtRetMode, strRetMode);
	pParas->AddNewData(STT_CMD_PARA_HasDigital, nHasDigital);  //2022-2-26 lijunqing
	pParas->AddNewData(STT_CMD_PARA_DvmFile, strDvmFile/*_T("SttIecRecordDetectDvm.xml")*/);  //20221011 zhouhj 暂时先直接赋值,后期考虑改进传参方式,或增加成员变量方式处理
	pParas->AddNewData(XPARA_ID_PPXMLFILE, strPpXmlFile);  

	
	if (g_nAtsGenTemplateForDebug == 1)
	{
		pParas->AddNewData(STT_CMD_PARA_GenForDebug, g_nAtsGenTemplateForDebug);  //2022-3-14 lijunqing
	}
	
	if (pTestMacroUI != NULL && pUIParas != NULL)
	{
		atscmd_Init_Paras(pParas, pTestMacroUI, pUIParas, pCommcmd, pCharacteristic);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_GenerateTemplate(CDataGroup *pGenParas, const CString &strRetMode
													, long nHasDigital, bool bDoEvents, CSttCmdData *pRetData,const CString &strDvmFile,const CString &strPpXmlFile)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_TtRetMode, strRetMode);
	pParas->AddNewData(STT_CMD_PARA_HasDigital, nHasDigital);  //2022-2-26 lijunqing
	pParas->AddNewData(STT_CMD_PARA_DvmFile, strDvmFile/*_T("SttIecRecordDetectDvm.xml")*/);  
	pParas->AddNewData(XPARA_ID_PPXMLFILE, strPpXmlFile);  

	if (g_nAtsGenTemplateForDebug == 1)
	{
		pParas->AddNewData(STT_CMD_PARA_GenForDebug, g_nAtsGenTemplateForDebug);  //2022-3-14 lijunqing
	}

	pParas->AppendCloneEx(*pGenParas, TRUE);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
												, CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup *pCommCmd, CSttContents *pCharacteristic
												, const CString &strDvmFile, const CString strTestClass, const CString &strRetMode, long nHasDigital
												, long nRepeatTimes, long nRptTitle, long nTitleLevel, long nSynMode, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateItems;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_TtRetMode, strRetMode);
	pParas->AddNewData(STT_CMD_PARA_HasDigital, nHasDigital);  //2022-2-26 lijunqing
	pParas->AddNewData(STT_CMD_PARA_generate_items_ItemsName, strItemsName); 
	pParas->AddNewData(STT_CMD_PARA_generate_items_ItemsID, strItemsID); 
	pParas->AddNewData(STT_CMD_PARA_generate_items_RepeatTimes, nRepeatTimes);
	pParas->AddNewData(STT_CMD_PARA_generate_items_RptTitle, nRptTitle); 
	pParas->AddNewData(STT_CMD_PARA_generate_items_TitleLevel, nTitleLevel);

	if (!strDvmFile.IsEmpty())
	{	
		pParas->AddNewData(STT_CMD_PARA_DvmFile, strDvmFile); 
	}

	if (!strTestClass.IsEmpty())
	{	
		pParas->AddNewData(STT_CMD_PARA_TestClass, strTestClass); 
	}

	if (g_nAtsGenTemplateForDebug == 1)
	{
		pParas->AddNewData(STT_CMD_PARA_GenForDebug, g_nAtsGenTemplateForDebug);  //2022-3-14 lijunqing
	}

	pParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strItemParentPath);
	
	atscmd_Init_Paras(pParas, pTestMacroUI, pUIParas, pCommCmd, pCharacteristic);


	if(nSynMode == STT_CMD_Send_Async)
	{
		return SendCmdAsync(&oAtsCmd,g_nTimeOut_Ats);
	}
	else
	{
		return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	}

	//return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID, CDataGroup *pItemParas
											   , bool bDoEvents, CSttCmdData *pRetData, const CString &strContents
											   , const CString &strRsltExpr)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetItemPara;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);

	if (!strMacroID.IsEmpty())
	{
		pParas->AddNewData(STT_CMD_PARA_MacroID, strMacroID);
	}
	
	if (pItemParas != NULL)
	{
		CDataGroup *pGroup = pParas->AddNewGroup(STT_CMD_PARA_ItemParas, STT_CMD_PARA_ItemParas, _T(""));
		pGroup->AppendCloneEx(*pItemParas, TRUE);
	}
	
	if (! strContents.IsEmpty())
	{
		pParas->AddContents(STT_CMD_PARA_ContentsParas, strContents); 
	}

	if (! strRsltExpr.IsEmpty())
	{
		pParas->AddContents(STT_CMD_PARA_RsltEpxr, strRsltExpr);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString& strMacroID, const CString &strItemParas,bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateItems;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	CDataGroup *pGenParas = pParas->AddNewGroup(STT_CMD_PARA_generate_items, STT_CMD_PARA_generate_items, _T(""));
	pGenParas->m_strValue = STT_CMD_PARA_generate_items_macro_add;

	pGenParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
	pGenParas->AddNewData(STT_CMD_PARA_MacroID, strMacroID);
	pGenParas->AddNewData(STT_CMD_PARA_ItemName, strItemName); 
	pGenParas->AddNewData(STT_CMD_PARA_ItemID, strItemID); 
	pParas->AddContents(STT_CMD_PARA_ItemParas, strItemParas); 

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_SaveTemplate(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI
												, CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData, long nSynMode)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SaveTemplate;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(XPARA_ID_Path, strPath);
	pParas->AddNewData(STT_CMD_PARA_FILE_NAME, strFileName);
	atscmd_Init_Paras(pParas, pMacroTestUI, pUIParas, NULL, NULL);
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("CSttTestEngineClientData::Ats_SaveTemplate[strPath=%s][strFileName=%s].")
// 		,strPath.GetString(),strFileName.GetString());

	long nRet = 0;
	if(nSynMode == STT_CMD_Send_Async)
	{
		nRet = SendCmdAsync(&oAtsCmd,g_nTimeOut_Ats);
	}
	else
	{
		nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	}

	return nRet;
	//return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_SaveTest(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI
											, CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData, long nSynMode)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SaveTest;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(XPARA_ID_Path, strPath);
	pParas->AddNewData(STT_CMD_PARA_FILE_NAME, strFileName);
	atscmd_Init_Paras(pParas, pMacroTestUI, pUIParas, NULL, NULL);

	long nRet = 0;
	if(nSynMode == STT_CMD_Send_Async)
	{
		nRet = SendCmdAsync(&oAtsCmd,g_nTimeOut_Ats);
	}
	else
	{
		nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	}

	return nRet;

	//return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ExportWordRpt(const CString &strPath, const CString& strFileName, CDataGroup *pParas, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ExportWordRpt;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pSttParas = oAtsCmd.GetSttParas();
	pSttParas->AddNewData(XPARA_ID_Path, strPath);
	pSttParas->AddNewData(STT_CMD_PARA_FILE_NAME, strFileName);
	
	if (pParas != NULL)
	{
		pSttParas->AppendCloneEx(*pParas, TRUE);
	}

	oAtsCmd.Set_Xml_Pkg_With_Name(TRUE);
	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_OpenTemplate;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(XPARA_ID_Path, strFileWithPath);

	if (strDvmFile.GetLength() > 0)
	{
		pParas->AddNewData(XPARA_ID_DVMFILE, strDvmFile);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_GenerateItems_Items(CDataGroup *pGenItemsParas , CSttContents *pContents, bool bDoEvents,CSttCmdData *pRetData, long nSynMode)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateItems;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewChild(pGenItemsParas);

	if (pContents != NULL)
	{
		pParas->AddNewChild(pContents);
	}

	long nRet = 0;
	if(nSynMode == STT_CMD_Send_Async)
	{
		 nRet = SendCmdAsync(&oAtsCmd,g_nTimeOut_Ats);
	}
	else
	{
		 nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	}

	return nRet;
}

long CSttTestEngineClientData::Ats_OpenGbrptFile(const CString &strGbrptFile, const CString &strDvmFile, const CString &strSmartTestRunMode, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_OpenGbrptFile;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(XPARA_ID_GBRPTFILE, strGbrptFile);
	pParas->AddNewData(XPARA_ID_SmartTestRunMode, strSmartTestRunMode);

	if (strDvmFile.GetLength() > 0)
	{
		pParas->AddNewData(XPARA_ID_DVMFILE, strDvmFile);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_AdjustMainWnd(LONG hMainParent, LONG hLogParent, bool bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_AdjustMainWnd;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(XPARA_ID_MainWnd, hMainParent);
	pParas->AddNewData(XPARA_ID_LogWnd, hLogParent);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ExportRpt(const CString &strDeviceID, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ExportReport;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_DeviceID, strDeviceID);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_UpdateItem(const CString &strItemPath, CDataGroup *pItemParas, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_UpdateItem;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);

	if (pItemParas != NULL)
	{
		CString strParas;

		++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
		strParas = pItemParas->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);
		--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

		pParas->AddContents(STT_CMD_PARA_ItemParas, strParas);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	if (strItemParas.GetLength() < 10)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_UpdateItem;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);

	if (strItemType.GetLength() > 0)
	{
		pParas->AddNewData(STT_CMD_PARA_ItemType, strItemType);
	}

	pParas->AddContents(STT_CMD_PARA_ItemParas, strItemParas);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_QueryItem(const CString &strItemPath, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_QueryItem;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_AdjustReport(const CString &strDeviceSN, long nShowWnd, bool bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_AdjustReport;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pParas = oAtsCmd.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pParas->AddNewData(XPARA_ID_ADJUSTREPORT_ShowWnd, nShowWnd);

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Ats_ClearReportsRslts(CDataGroup *pParas, bool bDoEvents, CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_ClearReportsRslts;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pSttParas = oAtsCmd.GetSttParas();
	
	if (pParas != NULL)
	{
		pSttParas->AppendCloneEx(*pParas, TRUE);
	}

	return SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
}

/*
<ats-cmd name="" id="GenerateItems" mid="0" time="2023-07-19 09:24:56" testor="ATS">
	<paras name="" id="">
		<group id="generate-items" data-type="generate-items" value="safety-add">
			<data id="ParentItemsPath" data-type="string" value=""/>
			<data id="ItemName" data-type="string" value="">
			<data id="ItemID" data-type="string" value="">
			<group id="safety-datas" data-type="" value="">
				<data name="额定电压" id="Un" value="220"/>
				<data name="额定电流" id="In" value="5"/>
				<data name="额定电频率" id="Fre" value="50"/>
				……
			</group>
		</group>
	</paras>
	<msgs>
		<msg type="" id="" time="" level=""><![CDATA[提示信息]]></msg>
		<msg type="" id="" time="" level=""><![CDATA[提示信息]]></msg>
	</msgs>
</ats-cmd>
*/
long CSttTestEngineClientData::Ats_AddSafety(CDataGroup *pParas, CExBaseList *pDatas, CExBaseList *pMsgs, bool bDoEvents, CSttCmdData *pRetData, long nSynMode)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttAtsCmd oAtsCmd;
	oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateItems;
	oAtsCmd.m_strTestor = STT_SOFT_ID_ATS;

	CSttParas *pSttParas = oAtsCmd.GetSttParas();
	CDataGroup *pGenItemsParas = new CDataGroup();
	pSttParas->AddNewChild(pGenItemsParas);
	pGenItemsParas->m_strName = STT_CMD_PARA_generate_items;
	pGenItemsParas->m_strID = STT_CMD_PARA_generate_items;
	pGenItemsParas->m_strDataType = STT_CMD_PARA_generate_items;
	pGenItemsParas->m_strValue = STT_CMD_PARA_generate_items_safety_add;

	if (pParas != NULL)
	{
		pGenItemsParas->AppendCloneEx(*pParas, TRUE);
	}

	if (pDatas != NULL)
	{
		CDataGroup *pSafetyDatas = new CDataGroup();
		pSafetyDatas->m_strID = STT_CMD_PARA_SafetyDatas;
		pGenItemsParas->AddNewChild(pSafetyDatas);
		pSafetyDatas->AppendCloneEx(*pDatas, TRUE);
	}	

	if (pMsgs != NULL)
	{
		CSttMsgs *pSttMsgs = oAtsCmd.GetSttMsgs();
		pSttMsgs->AppendCloneEx(*pMsgs, TRUE);
	}

	long nRet = 0;
	if(nSynMode == STT_CMD_Send_Async)
	{
		nRet = SendCmdAsync(&oAtsCmd,g_nTimeOut_Ats);
	}
	else
	{
		nRet = SendCmdSync(&oAtsCmd,g_nTimeOut_Ats,pRetData,bDoEvents);
	}

	return nRet;
}
//////////////////////////////////////////////////////////////////////////
//
//debug command
long CSttTestEngineClientData::Debug_Command(const CString &strCmdID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttDebugCmd oCmd;
	oCmd.m_strID = strCmdID;
	return SendCmdSync(&oCmd,g_nTimeOut_Debug,pRetData,bDoEvents);
}

long CSttTestEngineClientData::Debug_GetProcessState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetProcessState,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetMemState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetMemState,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetTestParas(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetTestParas,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetTestReports(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetTestReports,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetBasicTestParas(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetBasicTestParas,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetBasicReportData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetBasicReportData,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetDrvTestData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetDrvTestData,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetDrvReportData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetDrvReportData,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetFpgaData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetFpgaData,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_GetSocketConnect(BOOL bDoEvents,CSttCmdData *pRetData)
{
	return Debug_Command(STT_CMD_TYPE_DEBUG_GetSocketConnect,bDoEvents,pRetData);
}

long CSttTestEngineClientData::Debug_ConfigDebug(CDataGroup *pGroup,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttDebugCmd oCmd;
	oCmd.m_strID = STT_CMD_TYPE_DEBUG_ConfigDebug;
	oCmd.Append(pGroup);

	long nRet = SendCmdSync(&oCmd,g_nTimeOut_Debug,pRetData,bDoEvents);
	oCmd.RemoveAll();
	return nRet;
}

long CSttTestEngineClientData::Debug_ConfigDebug(CSttDebugCmd *pCmd,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	pCmd->m_strID = STT_CMD_TYPE_DEBUG_ConfigDebug;
	long nRet = SendCmdSync(pCmd,g_nTimeOut_Debug,pRetData,bDoEvents);
	pCmd->RemoveAll();
	return nRet;
}

long CSttTestEngineClientData::Debug_ConfigDebug(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
												,long nLogDebugInfor,long nNoChangeWhenSame, long nSpyCmd)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttDebugCmd oDebugCmd;
	oDebugCmd.m_strID = STT_CMD_TYPE_DEBUG_ConfigDebug;
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogDataBind, nLogDataBind);
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogPkgDataInfo, nLogPkgDataInfor);
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogPkg, nLogPkg);
    oDebugCmd.AddNewParasData(STT_CMD_PARA_LogServerDebugInfor, nLogDebugInfor);
	oDebugCmd.AddNewParasData(STT_CMD_PARA_NoChangeWhenSame, nNoChangeWhenSame);
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogServerSpyAllCmd, nSpyCmd);

	return SendCmdOnly(&oDebugCmd);
}

 //2020-12-04  lijunqing add spy-cmd
long CSttTestEngineClientData::Debug_ConfigDebug(const CString &strDebugParaID, long nValue)
{
	if (m_pSttClientSocket == NULL)
	{
		return 0;
	}

	CSttDebugCmd oDebugCmd;
	oDebugCmd.m_strID = STT_CMD_TYPE_DEBUG_ConfigDebug;
	oDebugCmd.AddNewParasData(strDebugParaID, nValue);

	return SendCmdOnly(&oDebugCmd);
}

//////////////////////////////////////////////////////////////////////////
//测试部分
long CSttTestEngineClientData::On_SysState_Test(CSttSysState &oSysState)
{
	//外部需要根据应答，进行成功或失败处理，故放在最开头
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->On_SysState_Test(&oSysState);
	}

	long nCmdExecState = oSysState.Get_ExecStatus();

	if (!Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);
		return nCmdExecState;
	}

	On_SysState_Test_UpdateTestGlobalParas(oSysState);
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_SetParameter)
	{
		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_UpdateParameter)
	{
		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_StartTest)
	{

		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_StopTest)
	{

		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_CloseDevice)
	{

		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_TEST_GetReport)
	{

		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_GetSystemState)
	{

		return 1;
	}

	return nCmdExecState;
}

long CSttTestEngineClientData::On_SysState_Ats(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	if (Stt_Is_ExecStatus_Ack(nCmdExecState))
	{
		return nCmdExecState;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_ATS_GenerateTemplate)
	{
		m_pTestEventRcv->On_Ats_Generate(oSysState.m_strID, oSysState.GetSttParas());
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_GenerateItems)
	{
		m_pTestEventRcv->On_Ats_Generate(oSysState.m_strID, oSysState.GetSttParas());
	}
	if (oSysState.m_strID == STT_CMD_TYPE_ATS_SaveTemplate)
	{
		m_pTestEventRcv->On_Ats_SaveTemplate(&oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_SaveTest)
	{
		m_pTestEventRcv->On_Ats_SaveTest(&oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_ExportWordRpt)
	{
		m_pTestEventRcv->On_Ats_ExportWordRpt(&oSysState);
	}	
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_CreateTest)
	{
		m_pTestEventRcv->On_Ats_CreateTest(&oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_AdjustMainWnd)
	{
		m_pTestEventRcv->On_Ats_AdjustMainWnd(&oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_ATS_QueryItem)
	{
		m_pTestEventRcv->On_Ats_QueryItem(&oSysState);
	}

	return nCmdExecState;
}

long CSttTestEngineClientData::On_SysState_Adjust(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	if (!Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		return nCmdExecState;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_ADJUST_Adjust)
	{
		return 1;
	}

	if (oSysState.m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		if (m_pTestEventRcv != NULL)
		{
			m_pTestEventRcv->OnRecvSttDebugData(oSysState);
		}

		return 1;
	}

	return nCmdExecState;
}

long CSttTestEngineClientData::On_SysState_IOT(CSttSysState &oSysState)
{
	//外部需要根据应答，进行成功或失败处理，故放在最开头
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->On_SysState_IOT(&oSysState);
	}

	long nCmdExecState = oSysState.Get_ExecStatus();

	if (nCmdExecState == 0)
	{
		return nCmdExecState;
	}

	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

//2020-10-09 文件处理  lijunqing
//读文件 strRealFilePath，目标文件相对路径，例如："Config/DeviceSystemParas.xml"  strDestFilePath,本地绝对路径
long CSttTestEngineClientData::ReadFile(const CString &strSrcFileRealPath, const CString &strDestFilePath,CSttSocketFileTransferProgress *pProgress)
{
	return m_pSttClientSocket->SttDownloadFile(strSrcFileRealPath,strDestFilePath,0,pProgress);
}

//写文件：strSrcFilePath，本地绝对路径；strSrcFileRealPath目标文件相对路径
long CSttTestEngineClientData::Write(const CString &strSrcFilePath, const CString &strDestFileRealPath,CSttSocketFileTransferProgress *pProgress)
{
	return m_pSttClientSocket->SttSendFile(strSrcFilePath,strDestFileRealPath,0,pProgress);
}


void CSttTestEngineClientData::On_SysState_Test_UpdateTestGlobalParas(CSttSysState &oSysState)
{
	CSttParas *pParas = oSysState.GetSttParas();
	POS pos = pParas->GetHeadPosition();
	CDvmData *pSrcPara = NULL, *pFind = NULL;
	CExBaseObject *p = NULL;
	
	while (pos != NULL)
	{
		p = (CExBaseObject *)pParas->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pSrcPara = (CDvmData *)p;
		pFind = (CDvmData *)m_oTestGlobalParas.FindByID(pSrcPara->m_strID);

		if (pFind == NULL)
		{
			m_oTestGlobalParas.AddNewChild((CExBaseObject*)pSrcPara->Clone());
		}
		else
		{
			pFind->m_strValue = pSrcPara->m_strValue;
		}
	}
}

/////////////////////////////////
long CSttTestEngineClientData::Process_SysState_System_Login(CSttSysState &oSysState)
{//登录命令是点对点应答，然后广播
	long nCmdExecState = oSysState.Get_ExecStatus();

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		long nIDTest = 0;
		oSysState.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTest);
		m_oCurrUser.SetIDTest(nIDTest);

		m_bHasLogin = TRUE;
	}

	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

long CSttTestEngineClientData::Process_SysState_System_Logout(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		OnLogout();
	}

	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

/*
<sys-state name="" id="query" mater-host="">
	<paras name="" id="">	
		<data id="IsSuccess" value="1" />  【登录是否成功】
		<data id="Test" value="1" />  【返回是否可以控制测试仪进行测试】
		…………………………………………..
	</paras>
<sys-state>
*/
long CSttTestEngineClientData::Process_SysState_System_Request(CSttSysState &oSysState)
{//请求授权命令是点对点应答，然后广播
	long nCmdExecState = oSysState.Get_ExecStatus();

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		CExBaseList *pParas = oSysState.GetSttParas();
		m_oCurrUser.SetAuthoritys(pParas);
		m_pSttSvrUserMngrRef->ClearOtherAuthoritys(pParas, &m_oCurrUser);
	}

	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

long CSttTestEngineClientData::Process_SysState_System_Authority(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

long CSttTestEngineClientData::Process_SysState_BroadcastUserMngr(CSttSysState &oSysState)
{
	if(m_pSttSvrUserMngrRef)
	{
		m_pSttSvrUserMngrRef->UpdateUserList(oSysState);
	
		BOOL bRet = m_pSttSvrUserMngrRef->UpdateCurrUser(m_oCurrUser);

		if (!bRet)
		{	//用户列表中没找到自身
			OnLogout();
		}
	}

	return 1;
}

long CSttTestEngineClientData::Process_SysState_System_SetSysConfig(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

long CSttTestEngineClientData::Process_SysState_System_GetSysConfig(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{
		//如果需要，更新系统参数
	}

	//CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nCmdExecState;
}

//2021-10-2  lijunqing
long CSttTestEngineClientData::Process_SysState_System_ReadMeas(CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineClientData::Process_SysState_System_LiveUpdate(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->OnRecvLiveUpdate(oSysState);
	}

	return nCmdExecState;
}

void CSttTestEngineClientData::OnLogout()
{
	m_bHasLogin = FALSE;
	m_oCurrUser.OnLogout();
	if(m_pSttSvrUserMngrRef)
	{
		m_pSttSvrUserMngrRef->DeleteAll();
	}
}

void CSttTestEngineClientData::On_SysState_Debug(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->OnRecvSttDebugData(oSysState);
	}
}

long CSttTestEngineClientData::Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	On_SysState_Test_UpdateTestGlobalParas(oSysState);//20220913 zhouhj 增加更新系统参数等
	m_pTestEventRcv->OnException(pParas);
	return 1;
}

long CSttTestEngineClientData::Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	//2022-1-15  lijunqing
	CSttParas *pParas = oSysState.GetSttParas();

	CString strTestID = _T(""),strItemID = _T("");
	long nDeviceIndex = 0,nReportIndex = 0,nItemIndex = 0,nState = 0;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemIndex,nItemIndex);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemID,strItemID);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_State,nState);

	pParas->m_strID = oSysState.m_strID;
	pParas->m_strDataType = oSysState.m_strRetType;
	pParas->m_strValue = oSysState.m_strRetSttCmd;

	m_pTestEventRcv->OnReport(strTestID,nDeviceIndex,nReportIndex,nItemIndex,strItemID,nState,pParas);

	return 1;
}

long CSttTestEngineClientData::Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	
	if (oSysState.m_strID == SYS_STATE_EVENT_OnItemStateChanged)
	{
		return m_pTestEventRcv->Event_OnItemStateChanged(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestFinished)
	{
		//2024.1.8 yzj 判断test-cmd是错误的，需要判断ats-cmd
		//m_bTestStarted = FALSE;
		return m_pTestEventRcv->Event_OnTestFinished(oSysState, m_bTestStarted);
		//return m_pTestEventRcv->Event_OnTestFinished(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestStarted)
	{
		//m_bTestStarted = TRUE;
		return m_pTestEventRcv->Event_OnTestStarted(oSysState, m_bTestStarted);
		//return m_pTestEventRcv->Event_OnTestStarted(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestStoped)
	{
		//m_bTestStarted = FALSE;
		return m_pTestEventRcv->Event_OnTestStoped(oSysState, m_bTestStarted);
		//return m_pTestEventRcv->Event_OnTestStoped(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnExportRptFinished)
	{
		return m_pTestEventRcv->Event_OnExportRptFinished(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestAppEvent)
	{
		return m_pTestEventRcv->Event_OnTestAppEvent(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestCreated)
	{
		return m_pTestEventRcv->Event_OnTestCreated(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnOpenGbrptFileFailed)
	{
		return m_pTestEventRcv->Event_OnOpenGbrptFileFailed(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnEngineEvent)
	{
		return m_pTestEventRcv->Event_OnEngineEvent(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnEngineReport)
	{
		return m_pTestEventRcv->Event_OnEngineReport(pParas);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnSearchPointReport)
	{
		return m_pTestEventRcv->Event_OnSearchPointReport(oSysState);//zhouhj 20210925  新增用于返回测试点报告
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_ExportReport)
	{
		return m_pTestEventRcv->Event_OnExportRpt(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnTestProcess)
	{
		return m_pTestEventRcv->Event_OnTestProcess(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_OnReTestFinished)
	{
		m_bTestStarted = FALSE;
		return m_pTestEventRcv->Event_OnReTestFinished(oSysState);
	}
	else if (oSysState.m_strID == SYS_STATE_EVENT_PkgSpy)//zhouhj 2024.1.23 增加用于报文监视
	{
		return m_pTestEventRcv->Event_OnPkgSpy(oSysState);
	}
	else
	{
		return m_pTestEventRcv->Event_OnTestState(oSysState);
	}

	return 1;
}

long CSttTestEngineClientData::Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	return m_pTestEventRcv->OnRtData(pParas);
}

long CSttTestEngineClientData::Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	return m_pTestEventRcv->OnViewPackage(pParas);
}

long CSttTestEngineClientData::Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	return m_pTestEventRcv->OnUpdate(pParas);
}

long CSttTestEngineClientData::Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
/*
	CSttParas *pParas = oSysState.GetSttParas();
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strLog;

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);

		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		strLog = _T("*********************");
		strLog += pData->m_strValue;
		CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
	}
*/

	//zhouhj 2023.11.17 增加此接口,方便单机软件派生后使用底层上送的打印信息
	if (m_pTestEventRcv != NULL)
	{
		return m_pTestEventRcv->Process_SysState_Log(oSysState);
	}

	CSttMsgs *pMsgs = oSysState.GetSttMsgs();
	POS pos = pMsgs->GetHeadPosition();
	CSttMsg *pData = NULL;
	CString strLog;

	while (pos != NULL)
	{
		pData = (CSttMsg *)pMsgs->GetNext(pos);
		strLog = _T("*********************");
		strLog += pData->m_strMsg;
		CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
	}

	return 0;
}

long CSttTestEngineClientData::Process_SysState_Meas(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
    if (m_pTestEventRcv == NULL)
    {
        return 0;
    }

    CSttParas *pParas = oSysState.GetSttParas();
    return m_pTestEventRcv->OnMeas(pParas);
}

long CSttTestEngineClientData::Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	if (m_pTestEventRcv == NULL)
	{
		return 0;
	}

	CSttParas *pParas = oSysState.GetSttParas();
	return m_pTestEventRcv->OnAts_Stop(pParas);
}

//只有具有单机测试权限的测试端定时发送心跳
void CSttTestEngineClientData::OnSendHeartbeatTimer()
{
	if((g_nSendHeartbeatTimeGap <= 0)
		|| (!m_bHasLogin)
		|| (m_pSttClientSocket == NULL))
	{
		return;
	}

	if (!m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test))
	{
		return;
	}
	
	OnSendHeartbeatTimer_NotCheakAuthority();
}

void CSttTestEngineClientData::OnSendHeartbeatTimer_NotCheakAuthority()
{
	if((g_nSendHeartbeatTimeGap <= 0)
		|| (!m_bHasLogin)
		|| (m_pSttClientSocket == NULL))
	{
		return;
	}

	if (m_oCurrUser.id_soft() != STT_SOFT_ID_TEST)
	{
		return;
	}

	if (m_pSttClientSocket->m_oSendHeartbeatTick.GetTickCountLong(FALSE) >= g_nSendHeartbeatTimeGap)
	{
		m_pSttClientSocket->SendHeartbeatCmd();
		//		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("发送心跳...."));
	}
}


