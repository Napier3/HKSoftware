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
�Զ��������⣺
"����̨SN/XML/AtsCmd/+";
"����̨SN/����װ��SN/XML/AtsCmd/FinishInputData";
"����̨SN/����װ��SN/XML/AtsState/InputData/Reply"
**************************/
void CSmartTestCtrlServerBaseApp::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	//��������
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (IsAtsTopic(oToken))
	{//�Զ����������
		m_oIotSmartTestCtrlMngr.OnMqttMsgRecieve(strTopic,pBuf,nLen);
	}
	else if (IsTestTopic(oToken))
	{//�����������
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
		//������������
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

//��������Ҫ���ĵ�����
BOOL CSmartTestCtrlServerBaseApp::SubcribeMqttTopic(int nQos)
{
	//�����Զ�������������
	m_oIotSmartTestCtrlMngr.SubcribeMqttAtsTopic(nQos);

	//���Ĳ�������������

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