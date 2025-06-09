#include "stdafx.h"
#include "AtsOutInterfaceMqttClient.h"
#include "../SttRegisterCode.h"
#include "../../../IotAtsMngr/Module/SttMqttClientEngineConfig.h"
#include "../../../Module/System/XNumberRand.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

 CSttXDevice * g_pTheOwnIotDevice = NULL;

 //全局唯一的自动测试外部调用的接口，例如：测试仪控制、通信引擎服务等
 CAtsOutInterfaceMqttClient *g_theAtsOutMqttClient = NULL;

 CAtsOutInterfaceMqttClient *CAtsOutInterfaceMqttClient::g_pAtsOutInterfaceMqttClient = NULL;
 long CAtsOutInterfaceMqttClient::g_nAtsOutInterfaceMqttClientRef = 0;

CAtsOutInterfaceMqttClient::CAtsOutInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Create();

	m_strIP = CSttMqttClientEngineConfig::GetMqttServerIP();
	m_nPort = CSttMqttClientEngineConfig::GetMqttServerPort();
	m_strClientID = _T("TestClientID");

	g_pTheOwnIotDevice = &m_oAtsIotDevice;
	g_theAtsOutMqttClient = this;
}

CAtsOutInterfaceMqttClient::~CAtsOutInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Release();

	g_theAtsOutMqttClient = NULL;
	g_pTheOwnIotDevice = NULL;
}

CAtsOutInterfaceMqttClient* CAtsOutInterfaceMqttClient::Create(const CString &strSN)
{
	g_nAtsOutInterfaceMqttClientRef ++;

	if (g_nAtsOutInterfaceMqttClientRef == 1)
	{
		g_pAtsOutInterfaceMqttClient = new CAtsOutInterfaceMqttClient();
		g_pAtsOutInterfaceMqttClient->Connect(strSN);
	}

	return g_pAtsOutInterfaceMqttClient;
}

void CAtsOutInterfaceMqttClient::Release()
{
	g_nAtsOutInterfaceMqttClientRef --;

	if (g_nAtsOutInterfaceMqttClientRef == 0)
	{
		delete g_pAtsOutInterfaceMqttClient;
		g_pAtsOutInterfaceMqttClient = NULL;
	}	
}

void CAtsOutInterfaceMqttClient::ReSubcribeMqttTopic()
{
	UnSubcribeMqttTopic();
	SubcribeMqttTopic(0);

	MqttUnSubscribeTopic();
	MqttSubscribeTopic();
}

BOOL CAtsOutInterfaceMqttClient::SubscribeTopic(const CString &strTopic,int nQos)
{
	char *pszTopic = NULL;
	CString_to_char(strTopic, &pszTopic);
	BOOL bRet = SubscribeTopic(pszTopic, nQos);
	delete pszTopic;
	return bRet;
}

BOOL CAtsOutInterfaceMqttClient::UnSubscribeTopic(const CString &strTopic)
{
	char *pszTopic = NULL;
	CString_to_char(strTopic, &pszTopic);
	BOOL bRet = UnSubscribeTopic(pszTopic);
	delete pszTopic;
	return bRet;
}

BOOL CAtsOutInterfaceMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
	return m_oMqttClient.SubscribeTopic(pszTopic, nQos);
}

BOOL CAtsOutInterfaceMqttClient::UnSubscribeTopic(const char* pszTopic)
{
	return m_oMqttClient.UnSubscribeTopic(pszTopic);
}

void CAtsOutInterfaceMqttClient::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{
	MqttMsgProcess(oSttMqttTopicParser);
}




void CAtsOutInterfaceMqttClient::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

long CAtsOutInterfaceMqttClient::PublicTopic(char *strTopic, char *pBuf, long nLen)
{
	BOOL bRet = m_oMqttClient.PublicTopic(strTopic, pBuf, nLen);

	if (bRet)
	{
		return nLen;
	}

	return -1;
}

long CAtsOutInterfaceMqttClient::PublicTopic(CSttMqttTopicCmbn &oTopicCmbn)
{
	BOOL bRet = m_oMqttClient.PublicTopic(oTopicCmbn.CmbnTopic()
		, oTopicCmbn.m_pszBuffer, oTopicCmbn.m_nBufferLength);

	if (bRet)
	{
		return oTopicCmbn.m_nBufferLength;
	}

	return -1;
}


BOOL CAtsOutInterfaceMqttClient::Connect(const CString &strSN)
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}


		SYSTEMTIME tm;
		GetLocalTime(&tm);
	m_strClientID.Format(_T("Ats_%s_%u_%d_%d_%d"), strSN.GetString()
		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond, tm.wMilliseconds);

	CLogPrint::LogString(XLOGLEVEL_TRACE, m_strClientID);
	m_oMqttClient.AttachMqttMsgInterface(this);
    BOOL bRet = m_oMqttClient.InitMqttClient(m_strIP, m_nPort, m_strClientID, "", "");

	if (bRet)
	{
		//连接成功后，主动订阅主题
		SubcribeMqttTopic(0);
		MqttSubscribeTopic();
	}

	return bRet;
}

void CAtsOutInterfaceMqttClient::Disconnect()
{
	UnSubcribeMqttTopic();
	m_oMqttClient.Disconnect();
}



//////////////////////////////////////////////////////////////////////////
CSttParas* CAtsOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser)
{
	CSttParas *pParas = new CSttParas();

	stt_pst_get_paras(oParser, *pParas);

	return pParas;
}

void CAtsOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttParas.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CAtsOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttTestCmd &oSttTestCmd, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttTestCmd.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, nXmlRWType);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

//

//////////////////////////////////////////////////////////////////////////
//
void CAtsOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oParas.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CAtsOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttParas oParas;
	oParas.Append(pDataGroup);

	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);

	oParas.RemoveAll();
}

void CAtsOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttTestCmd &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CAtsOutInterfaceMqttClient::stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, CSttXDevice *pDestDevice)
{
	oTopicCmbn.AddSubTopic(g_pTheOwnIotDevice->GetSN());

	if (pDestDevice != NULL)
	{
		oTopicCmbn.AddSubTopic(pDestDevice->GetSN());
	}
}

void CAtsOutInterfaceMqttClient::stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const char *pszSttCmdID, const char *pszSttCmdID2, CSttXDevice *pDestDevice)
{
	oTopicCmbn.ResetSubTopics();
	stt_mqtt_InitTopicCmbn(oTopicCmbn, pDestDevice);
	oTopicCmbn.AddSubTopic(pszSttCmdID);

	if (pszSttCmdID2 != NULL)
	{
		oTopicCmbn.AddSubTopic(pszSttCmdID2);
	}
}


void stt_mqtt_GetParasBuffer(CSttCmdBase *pCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = pCmd->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}
