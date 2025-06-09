#include "stdafx.h"
#include "MqttTestServerEngine.h"
#include "../../../SttStudio/Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#include "../SttMqttClientEngineConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CMqttTestServerEngine::m_nSttTestServerEngineRef = 0;
CMqttTestServerEngine* CMqttTestServerEngine::g_pSttTestServerEngine = NULL;

CMqttTestServerEngine::CMqttTestServerEngine()
{

}

CMqttTestServerEngine::~CMqttTestServerEngine()
{

}

CMqttTestServerEngine* CMqttTestServerEngine::Create(char *pszIP, int nPort)
{
	m_nSttTestServerEngineRef++;

	if (m_nSttTestServerEngineRef == 1)
	{
		g_pSttTestServerEngine = new CMqttTestServerEngine();
		g_pSttTestServerEngine->InitSttServerEngine(pszIP, nPort);
	}

	return (CMqttTestServerEngine*)g_pSttTestServerEngine;
}

void CMqttTestServerEngine::Release()
{
	m_nSttTestServerEngineRef--;

	if (m_nSttTestServerEngineRef == 0)
	{
		g_pSttTestServerEngine->ExitSttServerEngine();
		delete g_pSttTestServerEngine;
		g_pSttTestServerEngine = NULL;
	}
}

BOOL CMqttTestServerEngine::ConnectMqttServer()
{
	if (CSttMqttClientTool::IsConnectSuccessful())
	{
		return TRUE;
	}

	CString strIP,strClientID,strServerURI;
	long nPort = 0,nQos = 0;
	CSttMqttClientEngineConfig::GetMqttDefualtQos(nQos);
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	CSttMqttClientEngineConfig::GetMqttClientID(strClientID);
	strServerURI.Format(_T("tcp://%s:%d"),strIP,nPort);

	BOOL bRet = CSttMqttClientTool::InitMqttClient(strServerURI,strClientID+_T("_Vm"));

	if (bRet)
	{
		//订阅所有主题
		CSttMqttClientTool::SubscribeTopic(MQTT_TOPIC_TestCmd_Ack,(int)nQos);
		CSttMqttClientTool::SubscribeTopic(MQTT_TOPIC_TestCmd_Report,(int)nQos);
	}

	return bRet;
}

CSttEngineMqttCmdExec *CMqttTestServerEngine::FindMqttCmdExecByRefSocket(CSttSocketDataBase *pRefSocket)
{
	POS pos = m_oEngineMqttCmdExecMngr.GetHeadPosition();
	CSttEngineMqttCmdExec *p = NULL;

	while(pos != NULL)
	{
		p = (CSttEngineMqttCmdExec *)m_oEngineMqttCmdExecMngr.GetNext(pos);

		if (p->m_pRefSocket == pRefSocket)
		{
			return p;
		}
	}

	return NULL;
}

void CMqttTestServerEngine::DeleteMqttCmdExecByRefSocket(CSttSocketDataBase *pRefSocket)
{
	POS pos = m_oEngineMqttCmdExecMngr.GetHeadPosition();
	POS prePos = NULL;
	CSttEngineMqttCmdExec *p = NULL;

	while(pos != NULL)
	{
		prePos = pos;
		p = (CSttEngineMqttCmdExec *)m_oEngineMqttCmdExecMngr.GetNext(pos);

		if (p->m_pRefSocket == pRefSocket)
		{
			m_oEngineMqttCmdExecMngr.DeleteAt(prePos);
			break;
		}
	}
}

void CMqttTestServerEngine::InitSttServerEngine(const char *pszIP, int nPort)
{
	SetServerSocketDataBase(new CSttTestServerSocket);
	m_pServerSocket->m_nMaxClientCount=5;
	m_pServerSocket->CreateServer(pszIP,nPort);
	m_pServerSocket->AttachCmdOverTimeMsgRcv(this);
	m_pServerSocket->SetTestEngine(this);

	CSttMqttClientTool::Create();
	CSttMqttClientTool::g_pSttMqttClientTool->AttachSttMqttMsgInterface(this);
	ConnectMqttServer();
}

//2020-4-6  lijq
//如果没有这部分，Server的Accept线程无法退出
void CMqttTestServerEngine::ExitSttServerEngine()
{
	if (m_pServerSocket != NULL)
	{
		m_pServerSocket->CloseSttServer();
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}	
}

void CMqttTestServerEngine::OnSocketClose(CSttSocketDataBase *pSocket)
{
	m_pSttTestClientUserMngr->DeleteUserByRefSocket(pSocket);
	DeleteMqttCmdExecByRefSocket(pSocket);
	m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket);
}

void CMqttTestServerEngine::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	if (strTopic != MQTT_TOPIC_TestCmd_Report)
	{
		return;
	}

	CSttSysState oSysState;
	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	oSysState.SetXml_UTF8(pBuf,nLen,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	CSttParas *pParas = oSysState.GetSttParas();
	CString strDeviceID = _T("");
	pParas->GetDataValue(_T("Device"), strDeviceID);

	CSttEngineMqttCmdExec *pCmdExec = (CSttEngineMqttCmdExec *)m_oEngineMqttCmdExecMngr.FindByID(strDeviceID);
	if (pCmdExec != NULL)
	{
		pCmdExec->OnMqttMsgRecieve(oSysState);
	}
}

void CMqttTestServerEngine::OnMqttDisconnected(char *pszErr)
{

}

long CMqttTestServerEngine::Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd)
{
	CSttEngineMqttCmdExec *pFind = FindMqttCmdExecByRefSocket(pClientSocket);

	if (pFind == NULL)
	{
		return 0;
	}

	return pFind->Process_Cmd_Test(oTestCmd);
}

//登录
CSttTestClientUser* CMqttTestServerEngine::User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{//脱机软件或测试服务程序登录
	CSttTestClientUser *pUser = NULL;
	CString strIDTerminal;
	DWORD nIDTester = 0;
	oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);

	CSttSocketDataBase *pPrevSocket = NULL;
	pUser = m_pSttTestClientUserMngr->FindUser(pClientSocket, 0);

	if (pUser == NULL)
	{
		pUser = new CSttTestClientUser();
		m_pSttTestClientUserMngr->AddNewChild(pUser);
	}

	//重复登录不改变用户的权限
	pUser->AnalysisLoginUser(oSysCmd);
	pClientSocket->m_nIDTester = nIDTester;
	pUser->m_pRefSttSckt = pClientSocket;
	pUser->m_pRefSttSckt->SetUser(pUser);
	pClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);

	return pUser;
}

long CMqttTestServerEngine::Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
	CSttTestClientUser *pUser = User_Login(pClientSocket, oSysCmd);

	//生成应答命令返回
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oSysCmd);

	if(pUser != NULL)
	{
		//登录成功创建控制对象
		CSttEngineMqttCmdExec *pCmdExec = new CSttEngineMqttCmdExec(pClientSocket);
		m_oEngineMqttCmdExecMngr.AddNewChild(pCmdExec);

		oSysState.Set_ExecStatus_Success();
		oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, pUser->GetIDTest());
	}
	else
	{
		oSysState.Set_ExecStatus_Failure();
	}

	pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

	return 1;
}

long CMqttTestServerEngine::Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
	//更新用户链表，删除关联的用户和命令控制模块
	DWORD nIDTester = 0;
	oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
	m_pSttTestClientUserMngr->DeleteUserByRefSocket(pClientSocket);
	DeleteMqttCmdExecByRefSocket(pClientSocket);

	//生成应答命令返回
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oSysCmd);
	oSysState.Set_ExecStatus_Success();
	oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, nIDTester);
	pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

	return 1;
}