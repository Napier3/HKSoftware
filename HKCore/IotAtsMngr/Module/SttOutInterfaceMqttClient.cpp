#include "stdafx.h"
#include "SttOutInterfaceMqttClient.h"
#include "../../SttStudio/Module/SttRegisterCode.h"
#include "SttMqttClientEngineConfig.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

 //全局唯一的自动测试外部调用的接口，例如：测试仪控制、通信引擎服务等
 CSttOutInterfaceMqttClient *g_theSttOutMqttClient = NULL;

 CSttOutInterfaceMqttClient *CSttOutInterfaceMqttClient::g_pSttOutInterfaceMqttClient = NULL;
 long CSttOutInterfaceMqttClient::g_nSttOutInterfaceMqttClientRef = 0;

CSttOutInterfaceMqttClient::CSttOutInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Create();

	m_strIP = CSttMqttClientEngineConfig::GetMqttServerIP();
	m_nPort = CSttMqttClientEngineConfig::GetMqttServerPort();
	m_strClientID = _T("TestClientID");

	g_theSttOutMqttClient = this;
}

CSttOutInterfaceMqttClient::~CSttOutInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Release();

	g_theSttOutMqttClient = NULL;
}

CSttOutInterfaceMqttClient* CSttOutInterfaceMqttClient::Create()
{
	g_nSttOutInterfaceMqttClientRef ++;

	if (g_nSttOutInterfaceMqttClientRef == 1)
	{
		g_pSttOutInterfaceMqttClient = new CSttOutInterfaceMqttClient();
	}

	return g_pSttOutInterfaceMqttClient;
}

void CSttOutInterfaceMqttClient::Release()
{
	g_nSttOutInterfaceMqttClientRef --;

	if (g_nSttOutInterfaceMqttClientRef == 0)
	{
		delete g_pSttOutInterfaceMqttClient;
		g_pSttOutInterfaceMqttClient = NULL;
	}	
}

void CSttOutInterfaceMqttClient::ReSubcribeMqttTopic()
{
	UnSubcribeMqttTopic();
	SubcribeMqttTopic(0);

	MqttUnSubscribeTopic();
	MqttSubscribeTopic();
}

BOOL CSttOutInterfaceMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
	return m_oMqttClient.SubscribeTopic(pszTopic, nQos);
}

BOOL CSttOutInterfaceMqttClient::UnSubscribeTopic(const char* pszTopic)
{
	return m_oMqttClient.UnSubscribeTopic(pszTopic);
}

void CSttOutInterfaceMqttClient::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{
	MqttMsgProcess(oSttMqttTopicParser);
}




void CSttOutInterfaceMqttClient::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

long CSttOutInterfaceMqttClient::PublicTopic(char *strTopic, char *pBuf, long nLen)
{
	BOOL bRet = m_oMqttClient.PublicTopic(strTopic, pBuf, nLen);

	if (bRet)
	{
		return nLen;
	}

	return -1;
}

long CSttOutInterfaceMqttClient::PublicTopic(CSttMqttTopicCmbn &oTopicCmbn)
{
	BOOL bRet = m_oMqttClient.PublicTopic(oTopicCmbn.CmbnTopic()
		, oTopicCmbn.m_pszBuffer, oTopicCmbn.m_nBufferLength);

	if (bRet)
	{
		return oTopicCmbn.m_nBufferLength;
	}

	return -1;
}


BOOL CSttOutInterfaceMqttClient::Connect()
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}

	if (m_strClientID.GetLength() > 0)
	{
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		m_strClientID.Format(_T("AtsService_%u_%02d%02d%03d")
			,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
	}

	m_oMqttClient.AttachMqttMsgInterface(this);
	BOOL bRet = m_oMqttClient.InitMqttClient(m_strIP, m_nPort, m_strClientID);

	if (bRet)
	{
		//连接成功后，主动订阅主题
		SubcribeMqttTopic(0);
		MqttSubscribeTopic();
	}

	return bRet;
}

void CSttOutInterfaceMqttClient::Disconnect()
{
	UnSubcribeMqttTopic();
	m_oMqttClient.Disconnect();
}



//////////////////////////////////////////////////////////////////////////
CSttParas* CSttOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser)
{
	CSttParas *pParas = new CSttParas();

	stt_pst_get_paras(oParser, *pParas);

	return pParas;
}

void CSttOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttParas.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CSttOutInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttCmdBase &oSttTestCmd, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttTestCmd.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, nXmlRWType);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

//

//////////////////////////////////////////////////////////////////////////
//
void CSttOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oParas.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttParas oParas;
	oParas.Append(pDataGroup);

	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);

	oParas.RemoveAll();
}

void CSttOutInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttCmdBase &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void stt_mqtt_GetParasBuffer(CSttCmdBase *pCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = pCmd->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}