#include "stdafx.h"
#include "IotTestCtrlBase.h"
#include "SttMqttClientEngineConfig.h"
#include "../../SttStudio/Module/SttRegisterCode.h"
#include "../../Module/System/StringTokenizer.h"


//命令执行状态	ExecStatus	0=未处理  1=ACK 2=执行失败，3=执行成功
#define STT_CMD_ExecStatus_NULL		0
#define STT_CMD_ExecStatus_ACK		1
#define STT_CMD_ExecStatus_FAILURE	2
#define STT_CMD_ExecStatus_SUCCESS	3
#define STT_CMD_ExecStatus_TIMEOUT	4
#define STT_CMD_ExecStatus_SocketClose	5

BOOL Stt_Is_ExecStatus_NULL(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_NULL);
}

BOOL Stt_Is_ExecStatus_Ack(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_ACK);
}

BOOL Stt_Is_ExecStatus_Failure(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_FAILURE);
}

BOOL Stt_Is_ExecStatus_Success(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_SUCCESS);
}

BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_TIMEOUT);
}

CIotTestCtrlBase::CIotTestCtrlBase()
{
	m_bIsConnect = FALSE;
	m_nDeviceType = 0;
	m_nRemotePort = 8998;
	m_pTestMacros = NULL;
	m_pTestMacro = NULL;
	m_pMacroUpdateMsgRcvWnd = NULL;

	m_strFormat = MQTT_DATA_FORMAT_JSON;
	m_nTestState = IOT_TEST_STATE_IDLE;

	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(1048576); //1M

	m_oBinaryBuffer.SetBufferLength(4194304);   //4M
	m_oBinaryBuffer.AllocBuffer(0);

	//2021-8-15  lijunqing CreateXTimer Wnd Object
	CreateXTimer();
}

CIotTestCtrlBase::~CIotTestCtrlBase()
{
	ClearTestState();
	FreeTestMacros();

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}
}

void CIotTestCtrlBase::FreeTestMacros()
{
	m_pTestMacros = NULL;

	if (m_pTestMacro != NULL)
	{
		delete m_pTestMacro;
		m_pTestMacro = NULL;
	}
}

void CIotTestCtrlBase::SetXmlBufferLen(long nLen)
{
	if (nLen <= m_nXmlBufferLen)
	{
		return;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}

	m_pszXmlBuffer = new char [nLen+10];
	m_nXmlBufferLen = nLen;
}

void CIotTestCtrlBase::PostTestWndMsg(WPARAM wParam, LPARAM lParam)
{
	if (::IsWindow(m_hTestMsgRcvWnd))
	{
		::PostMessage(m_hTestMsgRcvWnd, m_nMessage, wParam, lParam);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("PostTestWndMsg error......."));
	}
}

void CIotTestCtrlBase::PostUpdateMacroMsg(long nMsgType)
{
	if (m_pMacroUpdateMsgRcvWnd != NULL)
	{
		m_pMacroUpdateMsgRcvWnd->PostMessage(WM_FLUSH_MACRO, 0, nMsgType);
	}
}

void CIotTestCtrlBase::ClearTestState()
{
	m_nTestState = IOT_TEST_STATE_IDLE;
	m_strCurrCmd = _T("");
}

void CIotTestCtrlBase::PraseBufToCmd(CSttCmdBase *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	if (strFormat == MQTT_DATA_FORMAT_JSON)
	{
		pCmdBase->PraseCmdBuf(pBuf,nLen,NULL,MQTT_DATA_FORMAT_JSON);
	}
	else
	{//XML
		SetXmlBufferLen(nLen * 2);
		pCmdBase->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,MQTT_DATA_FORMAT_XML);
	}
}

long CIotTestCtrlBase::Process_SysState_Reply(CSttSysState &oSysState,const CString &strCmd)
{
	if (strCmd != m_strCurrCmd)
	{//不是期待的命令
		return 0;
	}

	if (strCmd == STT_CMD_TYPE_TEST_QueryDeviceState)
	{
		Process_SysState_Reply_QueryDeviceState(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_SendSensorModel)
	{
		Process_SysState_Reply_SendSensorModel(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_GetTestMacros)
	{
		Process_SysState_Reply_GetTestMacros(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_GetTopo)
	{
		Process_SysState_Reply_GetTopo(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_StartTest)
	{
		Process_SysState_Reply_StartTest(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_StopTest)
	{
		Process_SysState_Reply_StopTest(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_SetParameter)
	{
		Process_SysState_Reply_SetParameter(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_UpdateParameter)
	{
		Process_SysState_Reply_UpdateParameter(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_GetReport)
	{
		Process_SysState_Reply_GetReport(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_CloseDevice)
	{
		Process_SysState_Reply_CloseDevice(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_SYSTEM_GetSystemState)
	{
		Process_SysState_Reply_GetSystemState(oSysState);
	}
	else if (strCmd == STT_CMD_TYPE_TEST_CreateDevice)
	{
		//在VmEngineServer中，创建完设备后，会进行联机。会给联机成功与否的REPLY
		Process_SysState_Reply_CreateDevice(oSysState);
	}

	return 1;
}

long CIotTestCtrlBase::Process_SysState_Event(CSttSysState &oSysState,const CString &strEvent)
{
	if (strEvent == SYS_STATE_EVENT_OnTestStarted)
	{
		Process_SysState_Event_OnTestStarted(oSysState);
	}
	else if (strEvent == SYS_STATE_EVENT_OnTestStoped)
	{
		Process_SysState_Event_OnTestStoped(oSysState);
	}
	else if (strEvent == SYS_STATE_EVENT_OnTestFinished)
	{
		Process_SysState_Event_OnTestFinished(oSysState);
	}
	else if (strEvent == SYS_STATE_EVENT_OnSearchPointReport)
	{
		Process_SysState_Event_OnSearchPointReport(oSysState);
	}

	return 1;
}

long CIotTestCtrlBase::Process_SysState_Report(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Exception(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_QueryDeviceState(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_SendSensorModel(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_GetTestMacros(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_GetTopo(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_StartTest(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	if (Stt_Is_ExecStatus_Ack(nCmdExecState))
	{//ACK
		return nCmdExecState;
	}

	KillXTimer(1);

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{//执行成功,等待Finish事件
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----StartTest执行成功，等待结果……"));
		m_nTestState = IOT_TEST_STATE_WAITRESULT;
		return nCmdExecState;
	}
	else
	{//失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----StartTest执行失败[%d]"),nCmdExecState);
		ClearTestState();

		PostTestWndMsg(MTMSG_CommError,0);
	}

	return nCmdExecState;
}

long CIotTestCtrlBase::Process_SysState_Reply_StopTest(CSttSysState &oSysState)
{
	long nCmdExecState = oSysState.Get_ExecStatus();
	if (Stt_Is_ExecStatus_Ack(nCmdExecState))
	{//ACK
		return nCmdExecState;
	}

	if (Stt_Is_ExecStatus_Success(nCmdExecState))
	{//执行成功
		ClearTestState();
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----StopTest执行成功"));
	}
	else
	{//失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----StopTest执行失败[%d]"),nCmdExecState);

		//停止测试不发送通讯错误消息，会导致自动测试再下发StopTest指令，会导致StopTest循环
		//若需要停止测试仪输出，则应用其它的功能ID进行测试，例如：StopOutput
		//PostTestWndMsg(MTMSG_CommError,0);
	}

	return nCmdExecState;
}

long CIotTestCtrlBase::Process_SysState_Reply_SetParameter(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_UpdateParameter(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_GetReport(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_CloseDevice(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_GetSystemState(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_TriggerTest(CSttSysState &oSysState)
{
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Reply_CreateDevice(CSttSysState &oSysState)
{
	long nRet = STT_CMD_ExecStatus_FAILURE;
	oSysState.GetParasDataValueByID(STT_SYS_STATE_ID_ExecStatus, nRet);
	KillXTimer(TIMER_ID_CreateDevice);

	if (STT_CMD_ExecStatus_FAILURE == nRet)
	{
		m_bIsConnect = FALSE;
		PostTestWndMsg(MTMSG_ConnectFaild,0);
	}
	else if (STT_CMD_ExecStatus_SUCCESS == nRet)
	{
		m_bIsConnect = TRUE;
		PostTestWndMsg(MTMSG_ConnectSuccess,0);
		//第一次联机成功后，开始测试
		return Test_StartTest();
	}
	
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Event_OnTestStarted(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestStarted"));
	PostTestWndMsg(MTMSG_TestBegin,0);
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Event_OnTestStoped(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestStoped"));
	return 1;
}

long CIotTestCtrlBase::Process_SysState_Event_OnTestFinished(CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished"));
	if (m_pTestMacro == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished,m_pTestMacro==NULL"));
		return 0;
	}

	CSttMacro *pMacro = oSysState.GetSttMacro();
	CSttMsgs *pMsgs = oSysState.GetSttMsgs();

	if (pMacro->m_strID != m_pTestMacro->m_strID)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Event_OnTestFinished,m_pTestMacro[%s]!=pMacro[%s]")
			,m_pTestMacro->m_strID,pMacro->m_strID);
		return 0;
	}

	//SttResult更新TestMacro节点
	UpdateMacroResultBySttMacroResult(m_pTestMacro,pMacro);

	ClearTestState();

	//发消息刷新界面
	PostUpdateMacroMsg(IOTVM_MACRO_MSG_TYPE_MACRO);

	//发消息给com窗口
	PostTestWndMsg(MTMSG_TestFinished,0);

	return 1;
}

long CIotTestCtrlBase::Process_SysState_Event_OnSearchPointReport(CSttSysState &oSysState)
{
	return 1;
}

void CIotTestCtrlBase::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{	
	OnMqttMsgRecieve(oSttMqttTopicParser.m_strTopic, oSttMqttTopicParser.m_pMqttPkgBuffer, oSttMqttTopicParser.m_nMqttPkgBufferLen);
}
/************************
测试仪主题：
测试仪SN/JSON/TestCmd/QueryDeviceState;
测试仪SN/JSON/TestCmd/SendSensorModel 
测试仪SN/JSON/TestCmd/GetTestMacros
测试仪SN/JSON/TestCmd/StartTest
测试仪SN/JSON/TestCmd/StopTest
测试仪SN/JSON/TestCmd/GetTopo
测试仪SN/JSON/TestState/QueryDeviceState/Reply
测试仪SN/JSON/TestState/SendSensorModel/Reply
测试仪SN/JSON/TestState/GetTestMacros/Reply
测试仪SN/JSON/TestState/StartTest/Reply
测试仪SN/JSON/TestState/StopTest/Reply
测试仪SN/JSON/TestState/GetTopo/Reply
测试仪SN/JSON/TestState/EVENT/TestFinished
测试仪SN/JSON/TestState/EVENT/TestStoped

测试仪SN/TestState/+/REPLY
测试仪SN/TestState/EVENT/+
测试仪SN/TestState/REPORT
测试仪SN/TestState/EXCEPTION
**************************/
void CIotTestCtrlBase::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	CString strLastTopic,strCmd,strEvent,strFormat;
	long nPathCnt = oToken.GetStringsCount();
	strFormat = MQTT_DATA_FORMAT_XML;
	strLastTopic = oToken.GetToken(nPathCnt-1);

	CSttSysState oSysState;
	PraseBufToCmd(&oSysState,pBuf,nLen,strFormat);

	if (strLastTopic == MQTT_SYSSTATE_TYPE_REPLY)
	{
		strCmd = oToken.GetToken(nPathCnt-2);
		Process_SysState_Reply(oSysState,strCmd);
	}
	else if (strLastTopic == MQTT_SYSSTATE_TYPE_REPORT)
	{
		Process_SysState_Report(oSysState);
	}
	else if (strLastTopic == MQTT_SYSSTATE_TYPE_EXCEPTION)
	{
		Process_SysState_Exception(oSysState);
	}
	else 
	{
		strEvent = oToken.GetToken(nPathCnt-2);

		if (strEvent == MQTT_SYSSTATE_TYPE_EVENT)
		{//EVENT
			if (strLastTopic == SYS_STATE_EVENT_OnTestStarted)
			{
				Process_SysState_Event_OnTestStarted(oSysState);
			}
			else if (strLastTopic == SYS_STATE_EVENT_OnTestStoped)
			{
				Process_SysState_Event_OnTestStoped(oSysState);
			}
			else if (strLastTopic == SYS_STATE_EVENT_OnTestFinished)
			{
				Process_SysState_Event_OnTestFinished(oSysState);
			}
			else if (strLastTopic == SYS_STATE_EVENT_OnSearchPointReport)
			{
				Process_SysState_Event_OnSearchPointReport(oSysState);
			}
		}
	}
}

void CIotTestCtrlBase::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

void CIotTestCtrlBase::OnProcessOverTime()
{
	ClearTestState();
	PostTestWndMsg(MTMSG_TestOverTime,0);
}

void CIotTestCtrlBase::OnXTimer(DWORD dwTimerID)
{//命令超时处理逻辑
	KillXTimer(dwTimerID);

	if (dwTimerID == TIMER_ID_CreateDevice)
	{
		PostTestWndMsg(MTMSG_ConnectFaild,0);
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("----测试仪联机超时失败"));
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("----%s执行超时失败"), m_strCurrCmd.GetString());
	OnProcessOverTime();
}

BOOL CIotTestCtrlBase::ConnectMqttServer()
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}

	m_oMqttClient.AttachMqttMsgInterface(this);

	CString strIP;
	long nPort = 0;
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	m_strClientSN.Format(_T("%s_%u_%02d%02d%03d"), _T("IotVm")
		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);

	BOOL bConnect = m_oMqttClient.InitMqttClient(strIP,nPort,m_strClientSN);

	if (!bConnect)
	{
		return FALSE;
	}

	return TRUE;
}

CTestMacro *CIotTestCtrlBase::SetCurrTestMacro(CTestMacro *pTestMacro)
{
	if (m_pTestMacro != NULL)
	{
		if (m_pTestMacro->m_strID != pTestMacro->m_strID)
		{
			delete m_pTestMacro;
			m_pTestMacro = (CTestMacro *)pTestMacro->Clone();
		}
		else
		{
			m_pTestMacro->ResetDatas();
		}
	}
	else
	{
		m_pTestMacro = (CTestMacro *)pTestMacro->Clone();
	}

	return m_pTestMacro;
}

CTestMacro *CIotTestCtrlBase::SetCurrTestMacro(const CString &strMacroID)
{
	CTestMacro *pFind = (CTestMacro *)m_pTestMacros->FindByID(strMacroID);
	if (pFind == NULL)
	{
		return NULL;
	}

	return SetCurrTestMacro(pFind);
}

/************************
测试仪主题：
测试仪SN/TestState/+/Reply
测试仪SN/TestState/EVENT/+
测试仪SN/TestState/+
**************************/
BOOL CIotTestCtrlBase::SubcribeMqttTopic(int nQos)
{
	if (!ConnectMqttServer())
	{
		return FALSE;
	}

	CString strTopic1,strTopic2,strTopic3;
	strTopic1.Format(_T("%s/TestState/+/REPLY"),m_strID);
	strTopic2.Format(_T("%s/TestState/EVENT/+"),m_strID);
	strTopic3.Format(_T("%s/TestState/+"),m_strID);

	m_oMqttClient.SubscribeTopic(strTopic1,nQos);
	m_oMqttClient.SubscribeTopic(strTopic2,nQos);
	m_oMqttClient.SubscribeTopic(strTopic3,nQos);
	return TRUE;
}

//主题：测试仪SN/TestCmd/CreateTest
//主题：测试仪SN/TestCmd/StartTest
//返回值：非0，表示成功
long CIotTestCtrlBase::PublicCmdEx(CSttCmdBase *pSttCmd,long nTimeOut)
{
	m_strCurrCmd = pSttCmd->m_strID;
	CString strTopic;
	strTopic.Format("%s/TestCmd/%s",m_strID,pSttCmd->m_strID);

	long nRet = PublicCmd(strTopic,pSttCmd);

	if (nRet > 0)
	{
		if (pSttCmd->m_strID != STT_CMD_TYPE_TEST_CreateDevice && pSttCmd->m_strID != STT_CMD_TYPE_TEST_StopTest)
		{
			//停止测试不用设置超时，否则会进入停止测试的死循环
			//CreateDevice命令单独设置了超时
			m_nTestState = IOT_TEST_STATE_TESTING;
			SetXTimer(1,nTimeOut);
		}
	}
	else
	{
		m_strCurrCmd.Empty();
	}

	return nRet;
}

long CIotTestCtrlBase::PublicCmd(const CString &strTopic,CSttCmdBase *pSttCmd)
{
	ASSERT(pSttCmd != NULL);

	if (!ConnectMqttServer())
	{
		return 0;
	}

	char *pszBuf = NULL;
	long nLen = 0;
	nLen = pSttCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);

	if (pszBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("PublicCmd::pszBuf==NULL"));
		return 0;
	}

	BOOL bRet = m_oMqttClient.PublicTopic(strTopic,pszBuf,nLen);
	delete pszBuf;
	return bRet;
}

//返回值：非0表示成功
BOOL CIotTestCtrlBase::CreateDevice()
{
	/*
<test-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<group id="test-app">
			<data id="DeviceSN" value="123456789"/>
			<data id="EngineProgID" value="IotVm"/>
			<data id="dvm-file" value="MacroTest.xml"/>
			<data id="remote-ip" value="127.0.0.1"/>
			<data id="remote-port" value="9988"/>
		</group>
	</paras>
</test-cmd>
*/

	//需要增加：联机成功后，发送CreateDevice
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_CreateDevice;
	oTestCmd.m_strFromSN = m_strClientSN;
	oTestCmd.AddNewParasData(STT_CMD_PARA_DeviceSN,m_strID);
	CSttParas *pParas = oTestCmd.GetSttParas();
	CDataGroup *pTestApp = pParas->AddNewGroup(XPARA_ID_test_app, XPARA_ID_test_app, _T(""));
	pTestApp->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	pTestApp->AddNewData(STT_CMD_PARA_MacroFile, m_strMacroFile);
	pTestApp->AddNewData(STT_CMD_PARA_ProtocolID, m_strProtocolID);
	pTestApp->AddNewData(STT_CMD_PARA_EngineProgID, m_strEngineProgID);
	pTestApp->AddNewData(XPARA_ID_Remote_ip, m_strRemoteIP);
	pTestApp->AddNewData(XPARA_ID_Remote_port, m_nRemotePort);

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrlBase::Test_StartTest()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;

	CSttMacro *pSttMacro = GenerateSttMacroParas(m_pTestMacro);
	oTestCmd.AddNewChild(pSttMacro);

	return PublicCmdEx(&oTestCmd);
}

long CIotTestCtrlBase::Test_StopTest()
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_StopTest;

	CSttMacro *pSttMacro = oTestCmd.GetSttMacro();
	pSttMacro->m_strID = m_pTestMacro->m_strID;

	return PublicCmdEx(&oTestCmd);
}

LONG CIotTestCtrlBase::SetWndMsg(ULONG hMainWnd, ULONG nMsgID)
{
	m_hTestMsgRcvWnd = (HWND)hMainWnd; 
	m_nMessage= nMsgID;	
	return 0;
}

//返回0，表示测试成功
LONG CIotTestCtrlBase::Test(const CString &strMacroID, const CString &strParameter)
{
	if (IsTesting())
	{//正在测试
		PostTestWndMsg(MTMSG_AppError,0);
		return COMM_SetError(COMMERROR_DEVICE_INTESTTING);
	}

	CTestMacro *pTestMacro = SetCurrTestMacro(strMacroID);
	if (pTestMacro == NULL)
	{//不支持当前功能
		PostTestWndMsg(MTMSG_Not_Surport,0);
		return COMM_SetError(COMMERROR_MACRO_NOT_SUPPORT);
	}

	if (!ConnectMqttServer())
	{//服务端断链
		PostTestWndMsg(MTMSG_CommError,0);
		return COMM_SetError(COMMERROR_CONNECT_FAILED);
	}

	m_oEquation.DeleteAll();
	m_oEquation.InitBuffer(strParameter);

	UpdateDatasByParas(&m_oEquation,pTestMacro->GetFaultParas());
	UpdateDatasByParas(&m_oEquation,pTestMacro->GetSysParas());
	UpdateGroupByParas(&m_oEquation,pTestMacro->GetFaultParasEx());

	if (m_bIsConnect)
	{
		//如果已经联机成功，则直接下发开始测试命令，否则在CreateDevice的REPLY事件中下发开始测试
		return Test_StartTest();
	}

	//CreateDevice，在VmEngineServer中，与实际测试仪进行联机
	BOOL bRet = CreateDevice();
	//bRet = TURE，表示CreateDevice的报文发送成功
	//此处，不管是否报文发送成功，都起定时器，没发送成功也进入超时
	SetXTimer(TIMER_ID_CreateDevice, TIMER_LONG_CreateDevice);

	//此处直接返回0，表示命令执行成功。
	//由于CreateDevice超时， 或者CreateDevice的REPLY中判定执行失败，会向自动测试发送ConnectFailed消息，也能停止测试。
	//故此处直接返回0，不影响自动测试逻辑
	return 0;
}

LONG CIotTestCtrlBase::StopTest()
{
	return Test_StopTest();
}

BSTR CIotTestCtrlBase::GetConfig(void)
{
	return NULL;
}

LONG CIotTestCtrlBase::SetConfig(const CString & bstrConfig)
{
	return 0;
}

LONG CIotTestCtrlBase::CloseDevice(void)
{
	CSttTestCmd oTestCmd;
	oTestCmd.m_strID = STT_CMD_TYPE_TEST_CloseDevice;

// 	CSttMacro *pSttMacro = oTestCmd.GetSttMacro();
// 	pSttMacro->m_strID = m_pTestMacro->m_strID;
// 	CSttIotDevices *pDevices = oTestCmd.GetSttIotDevices();
// 	pDevices->AppendClone(m_oSttIotDevices);

	return PublicCmdEx(&oTestCmd);
}

BSTR CIotTestCtrlBase::GetReport(void)
{
	if (m_pTestMacro == NULL)
	{
		return NULL;
	}

	CString strReport;

	m_oBinaryBuffer.ResetBufferPointer();
	GetDatasReportEx(m_oBinaryBuffer,m_pTestMacro->GetFaultParas());
	GetDatasReportEx(m_oBinaryBuffer,m_pTestMacro->GetSysParas());
	GetDatasReportEx(m_oBinaryBuffer,m_pTestMacro->GetResults());
	GetGroupReportEx(m_oBinaryBuffer,m_pTestMacro->GetFaultParasEx());
	GetGroupReportEx(m_oBinaryBuffer,m_pTestMacro->GetResultsEx());
	m_oBinaryBuffer.StringEnd();

	m_oBinaryBuffer >> strReport;

	return strReport.AllocSysString();
}

BSTR CIotTestCtrlBase::GetSearchReport(void)
{
	return NULL;
}

DWORD CIotTestCtrlBase::FinishTest(DWORD dwState)
{
	return 0;
}


///////////////////////

CString GetParaIDPath(CShortData *pData)
{
	CString strPath = _T("");
	CExBaseObject *pParent = pData;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->m_strID.GetLength() == 0)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strID);
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			break;
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}

	return strPath;
}

void GetDatasReportEx(CStringSerializeBuffer &oBinaryBuffer,CShortDatas *pDatas)
{
	CShortData* pData = NULL;
	POS pos = pDatas->GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);

		oBinaryBuffer << pData->m_strID;
		oBinaryBuffer << _T("=");
		oBinaryBuffer << pData->m_strValue;
		oBinaryBuffer << _T(";");
	}
}

void GetGroupReportEx(CStringSerializeBuffer &oBinaryBuffer,CDataGroup *pGroup)
{
	CExBaseObject* pObject = NULL;

	//yzj 2021-9-26 pGroup可能为空即是没有report
	if(pGroup)
	{
		POS pos = pGroup->GetHeadPosition();
		CString strValue;

		while (pos != NULL)
		{
			pObject = pGroup->GetNext(pos);

			if (pObject->GetClassID() == DTMCLASSID_CDATAGROUP)
			{
				GetGroupReportEx(oBinaryBuffer,(CDataGroup*)pObject);
			}
			else if(pObject->GetClassID() == DTMCLASSID_CSHORTDATA)
			{
				CShortData *pData = (CShortData *)pObject;
				CString strPath = GetParaIDPath(pData);

				oBinaryBuffer << strPath;
				oBinaryBuffer << _T("=");
				oBinaryBuffer << pData->m_strValue;
				oBinaryBuffer << _T(";");
			}
		}
	}
}

//解析更新参数
void UpdateDatasByParas(CEquationBuffer *pEquation,CShortDatas *pDatas)
{
	if ((pDatas == NULL) || (pEquation == NULL))
	{
		return;
	}

	CShortData* pData = NULL;
	POS pos = pDatas->GetHeadPosition();
	CString strValue;

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);

		strValue = _T("");
		pEquation->ParseString(pData->m_strID, strValue);

		if(strValue.GetLength() > 0)
		{
			pData->m_strValue = strValue;
		}
	}
}

void UpdateGroupByParas(CEquationBuffer *pEquation,CDataGroup *pGroup)
{
	if ((pGroup == NULL) || (pEquation == NULL))
	{
		return;
	}

	CString strPath,strValue;
	UINT nClassID = 0;
	CShortData* pData = NULL;
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			UpdateGroupByParas(pEquation,(CDataGroup *)p);
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			pData = (CShortData*)p;
			strValue = _T("");

			strPath = GetParaIDPath(pData);
			pEquation->ParseString(strPath, strValue);

			if(strValue.GetLength() > 0)
			{
				pData->m_strValue = strValue;
			}
		}
	}
}

//根据macro节点生成SttMacro节点
void Stt_AppendDatasParas(CDataGroup *pDstParas,CShortDatas *pSrcDatas)
{
	ASSERT(pDstParas != NULL);
	if (pSrcDatas == NULL)
	{
		return;
	}

	POS pos = pSrcDatas->GetHeadPosition();
	CShortData *pShortData = NULL;

	while(pos != NULL)
	{
		pShortData = (CShortData *)pSrcDatas->GetNext(pos);
		pDstParas->AddNewData(pShortData->m_strName,pShortData->m_strID
			,pShortData->m_strDataTypeID,pShortData->m_strValue,pShortData->m_strUnit);
	}
}

void Stt_AppendGroupParas(CDataGroup *pDstParas,CDataGroup *pSrcGroup)
{
	ASSERT(pDstParas != NULL);
	if (pSrcGroup == NULL)
	{
		return;
	}

	POS pos = pSrcGroup->GetHeadPosition();
	CShortData *pTempData = NULL;
	CDataGroup *pTempGroup = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while(pos != NULL)
	{
		p = pSrcGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pTempGroup = (CDataGroup *)p;
			CDataGroup *pNewGroup = pDstParas->AddNewGroup(pTempGroup->m_strName
				,pTempGroup->m_strID,pTempGroup->m_strDataType);
			Stt_AppendGroupParas(pNewGroup,pTempGroup);
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			pTempData = (CShortData *)p;
			pDstParas->AddNewData(pTempData->m_strName,pTempData->m_strID
				,pTempData->m_strDataTypeID,pTempData->m_strValue,pTempData->m_strUnit);
		}
	}
}

void Stt_UpdateDatasParas(CDataGroup *pSrcParas,CShortDatas *pDstDatas)
{
	if ((pDstDatas == NULL) || (pSrcParas == NULL))
	{
		return;
	}

	POS pos = pSrcParas->GetHeadPosition();
	CExBaseObject *p = NULL;
	CShortData *pShortData = NULL;

	while(pos != NULL)
	{
		p = pSrcParas->GetNext(pos);
		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pShortData = (CShortData *)pDstDatas->FindByID(p->m_strID);
		if (pShortData != NULL)
		{
			pShortData->m_strValue = ((CDvmData *)p)->m_strValue;
		}
	}
}

CSttMacro *GenerateSttMacroParas(CTestMacro *pTestMacro)
{
	ASSERT(pTestMacro != NULL);
	CSttMacro *pSttMacro = new CSttMacro;
	pSttMacro->m_strName = pTestMacro->m_strName;
	pSttMacro->m_strID = pTestMacro->m_strID;
	pSttMacro->m_strType = pTestMacro->m_strType;

	CSttParas* pParas = pSttMacro->GetParas();

	Stt_AppendDatasParas(pParas,pTestMacro->GetFaultParas());
	Stt_AppendDatasParas(pParas,pTestMacro->GetSysParas());
	Stt_AppendGroupParas(pParas,pTestMacro->GetFaultParasEx());

	return pSttMacro;
}

//根据SttMacro节点生成macro节点
void Stt_AppendDatasParas2(CShortDatas *pDstDatas,CDataGroup *pSrcGroup)
{
	ASSERT(pDstDatas != NULL);
	if (pSrcGroup == NULL)
	{
		return;
	}

	POS pos = pSrcGroup->GetHeadPosition();
	CDvmData *pData = NULL;

	while(pos != NULL)
	{
		pData = (CDvmData *)pSrcGroup->GetNext(pos);
		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		CShortData *pShortData = new CShortData;
		pShortData->PutID(pData->m_strID);
		pShortData->PutName(pData->m_strName);
		pShortData->PutValue(pData->m_strValue);
		pShortData->PutUnit(pData->m_strUnit);
		pShortData->PutDataTypeID(pData->m_strDataType);
		pShortData->PutFormat(pData->m_strFormat);
		pShortData->PutDefaultValue(pData->m_strValue);
		pDstDatas->AddNewChild(pShortData);
	}
}

CTestMacro *GenerateMacroParas(CSttMacro *pSttMacro)
{
	ASSERT(pSttMacro != NULL);

	CTestMacro *pTestMacro = new CTestMacro;
	pTestMacro->InitAfterRead();
	pTestMacro->m_strName = pSttMacro->m_strName;
	pTestMacro->m_strID = pSttMacro->m_strID;
	pTestMacro->m_strType = pSttMacro->m_strType;

	CSttParas* pParas = pSttMacro->GetParas();
	CSttResults *pResults = pSttMacro->GetResults();

	Stt_AppendDatasParas2(pTestMacro->GetFaultParas(),pParas);
	Stt_AppendDatasParas2(pTestMacro->GetResults(),pResults);

	return pTestMacro;
}

void UpdateMacroResultBySttMacroResult(CTestMacro *pDstTestMacro,CSttMacro *pSrcSttMacro)
{
	ASSERT(pDstTestMacro != NULL);
	ASSERT(pSrcSttMacro != NULL);
	CSttResults *pResult = pSrcSttMacro->GetResults();

	Stt_UpdateDatasParas(pResult,pDstTestMacro->GetResults());
}