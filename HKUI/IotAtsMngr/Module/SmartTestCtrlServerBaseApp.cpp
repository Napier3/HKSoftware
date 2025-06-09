#include "stdafx.h"
#include "SmartTestCtrlServerBaseApp.h"
#include "../../SttStudio/Module/SttRegisterCode.h"
#include "SttMqttClientEngineConfig.h"


CSmartTestCtrlServerBaseApp::CSmartTestCtrlServerBaseApp()
{

}

CSmartTestCtrlServerBaseApp::~CSmartTestCtrlServerBaseApp()
{

}


/************************
自动测试主题：
"测试台SN/XML/AtsCmd/+";
"测试台SN/被测装置SN/XML/AtsCmd/FinishInputData";
"测试台SN/被测装置SN/XML/AtsState/InputData/Reply"
**************************/
void CSmartTestCtrlServerBaseApp::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	//根据主题
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (IsAtsTopic(oToken))
	{//自动测试命令处理
		m_oIotSmartTestCtrlMngr.OnMqttMsgRecieve(strTopic,pBuf,nLen);
	}
	else if (IsTestTopic(oToken))
	{//测试仪命令处理
	}
}

void CSmartTestCtrlServerBaseApp::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

BOOL CSmartTestCtrlServerBaseApp::ConnectMqttServer()
{
	CString strIP,strClientID;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	strClientID.Format(_T("SmartTestCtrlServer_%d"),stt_GetMachineCode_U32());

	return CSttMqttClientTool::InitMqttClient(strIP,nPort,strClientID);
}

void CSmartTestCtrlServerBaseApp::InitSmartTestCtrlServerBaseApp()
{
	CCfgDataMngrConstGlobal::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();

	CString strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
	CSttMqttClientEngineConfig::Create(strFile);

	CSttMqttClientTool::Create();
	CSttMqttClientTool::g_pSttMqttClientTool->AttachSttMqttMsgInterface(this);

	if (ConnectMqttServer())
	{
		long nQos = 0;
		CSttMqttClientEngineConfig::GetMqttDefualtQos(nQos);
		//订阅所有主题
		SubcribeMqttTopic(nQos);
	}
}

void CSmartTestCtrlServerBaseApp::ExitSmartTestCtrlServerBaseApp()
{
	CSttMqttClientTool::Release();
	CSttMqttClientEngineConfig::Release();

	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
}

//启动后需要订阅的主题
BOOL CSmartTestCtrlServerBaseApp::SubcribeMqttTopic(int nQos)
{
	//订阅自动测试命令主题
	m_oIotSmartTestCtrlMngr.SubcribeMqttAtsTopic(nQos);

	//订阅测试仪命令主题

	return TRUE;
}

/////////////////////////////////////////////

BOOL HasSubString(CStringTokenizer &oToken,const CString &strSub)
{
	ASSERT(!strSub.IsEmpty());
	CString str;

	while(TRUE)
	{
		str = oToken.NextToken();

		if (strSub == str)
		{
			return TRUE;
		}

		if (str.IsEmpty())
		{
			break;
		}
	}

	return FALSE;
}

BOOL IsAtsTopic(CStringTokenizer &oTopicToken)
{
	if (HasSubString(oTopicToken,_T("AtsCmd")))
	{
		return TRUE;
	}
	if (HasSubString(oTopicToken,_T("AtsState")))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsTestTopic(CStringTokenizer &oTopicToken)
{
	if (HasSubString(oTopicToken,_T("TestCmd")))
	{
		return TRUE;
	}
	if (HasSubString(oTopicToken,_T("TestState")))
	{
		return TRUE;
	}

	return FALSE;
}