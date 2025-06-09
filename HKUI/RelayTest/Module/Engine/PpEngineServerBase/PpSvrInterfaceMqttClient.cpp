#include "stdafx.h"
#include "PpSvrInterfaceMqttClient.h"
#include "../../SttRegisterCode.h"
#include "../../../IotAtsMngr/Module/SttMqttClientEngineConfig.h"
#include "MqttPpServerClient.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

 //全局唯一的自动测试外部调用的接口，例如：测试仪控制、通信引擎服务等
 CPpSvrInterfaceMqttClient *g_thePpSvrMqttClient = NULL;

 CPpSvrInterfaceMqttClient *CPpSvrInterfaceMqttClient::g_pPpSvrInterfaceMqttClient = NULL;
 long CPpSvrInterfaceMqttClient::g_nPpSvrInterfaceMqttClientRef = 0;

CPpSvrInterfaceMqttClient::CPpSvrInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Create();

	m_strIP = CSttMqttClientEngineConfig::GetMqttServerIP();
	m_nPort = CSttMqttClientEngineConfig::GetMqttServerPort();
	m_strClientID = _T("TestClientID");

	g_thePpSvrMqttClient = this;
}

CPpSvrInterfaceMqttClient::~CPpSvrInterfaceMqttClient()
{
	CSttMqttClientEngineConfig::Release();

	g_thePpSvrMqttClient = NULL;
}

CPpSvrInterfaceMqttClient* CPpSvrInterfaceMqttClient::Create()
{
	g_nPpSvrInterfaceMqttClientRef ++;

	if (g_nPpSvrInterfaceMqttClientRef == 1)
	{
		g_pPpSvrInterfaceMqttClient = new CPpSvrInterfaceMqttClient();
		g_pPpSvrInterfaceMqttClient->Connect();
	}

	return g_pPpSvrInterfaceMqttClient;
}

void CPpSvrInterfaceMqttClient::Release()
{
	g_nPpSvrInterfaceMqttClientRef --;

	if (g_nPpSvrInterfaceMqttClientRef == 0)
	{
		delete g_pPpSvrInterfaceMqttClient;
		g_pPpSvrInterfaceMqttClient = NULL;
	}	
}

BOOL CPpSvrInterfaceMqttClient::SubcribeMqttTopic(int nQos)
{
	CString strTopic ;

	strTopic.Format(_T("+/+/%s/#"), MQTT_CMD_ID_IotCmd);
	SubscribeTopic(strTopic, 0);

	strTopic.Format(_T("+/%s/#"), MQTT_CMD_ID_IotCmd);
	SubscribeTopic(strTopic, 0);

	return TRUE;
}

BOOL CPpSvrInterfaceMqttClient::UnSubcribeMqttTopic()
{
	CString strTopic ;

	strTopic.Format(_T("+/+/%s/#"), MQTT_CMD_ID_IotCmd);
	UnSubscribeTopic(strTopic);

	strTopic.Format(_T("+/%s/#"), MQTT_CMD_ID_IotCmd);
	UnSubscribeTopic(strTopic);

	return TRUE;
}

void CPpSvrInterfaceMqttClient::ReSubcribeMqttTopic()
{
	UnSubcribeMqttTopic();
	SubcribeMqttTopic(0);

	MqttUnSubscribeTopic();
	MqttSubscribeTopic();
}

BOOL CPpSvrInterfaceMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
	return m_oMqttClient.SubscribeTopic(pszTopic, nQos);
}

BOOL CPpSvrInterfaceMqttClient::UnSubscribeTopic(const char* pszTopic)
{
	return m_oMqttClient.UnSubscribeTopic(pszTopic);
}

//主题：请求端SN/规约引擎边服务ID/IotCmd/CreateDevice
void CPpSvrInterfaceMqttClient::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{
	long nIndex = oSttMqttTopicParser.FindXCmdType(MQTT_CMD_ID_IotCmd);

	if (nIndex > 0)
	{
		if (nIndex < oSttMqttTopicParser.m_nCount-1)
		{
			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[nIndex+1], STT_CMD_TYPE_IOT_CreateDevice) == 0)
			{
				CMqttPpServerClient *pMqttPpServerClient = new CMqttPpServerClient();
				MqttAdd(pMqttPpServerClient);
				pMqttPpServerClient->IOT_CreateDevice(oSttMqttTopicParser);
				return;
			}

			if (strcmp(oSttMqttTopicParser.m_pszSubTopic[nIndex+1], STT_CMD_TYPE_IOT_CloseDevice) == 0)
			{
				CMqttPpServerClient *pMqttPpServerClient = (CMqttPpServerClient *)MqttMatch(oSttMqttTopicParser);

				if (pMqttPpServerClient != NULL)
				{
					pMqttPpServerClient->IOT_CloseDevice(oSttMqttTopicParser);
					MqttRemove(pMqttPpServerClient);
				}
				
				return;
			}
		}
	}

	MqttMsgProcess(oSttMqttTopicParser);
}




void CPpSvrInterfaceMqttClient::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

long CPpSvrInterfaceMqttClient::PublicTopic(char *strTopic, char *pBuf, long nLen)
{
	BOOL bRet = m_oMqttClient.PublicTopic(strTopic, pBuf, nLen);

	if (bRet)
	{
		return nLen;
	}

	return -1;
}

long CPpSvrInterfaceMqttClient::PublicTopic(CSttMqttTopicCmbn &oTopicCmbn)
{
	BOOL bRet = m_oMqttClient.PublicTopic(oTopicCmbn.CmbnTopic()
		, oTopicCmbn.m_pszBuffer, oTopicCmbn.m_nBufferLength);

	if (bRet)
	{
		return oTopicCmbn.m_nBufferLength;
	}

	return -1;
}

long CPpSvrInterfaceMqttClient::PxSendSysState(CSttSysState *pSysState, const CString &strFromSN, const CString &strDeviceSN, long nFormatType)
{
	if (pSysState->m_strRetType == SYS_STATE_RETTYPE_RTDATA)
	{
		return PxSendSysState_RTDATA(pSysState, strFromSN, strDeviceSN, nFormatType);
	}

	//其它的暂不处理
	return -1;
}

long CPpSvrInterfaceMqttClient::PxSendSysState_RTDATA(CSttSysState *pSysState, const CString &strFromSN, const CString &strDeviceSN, long nFormatType)
{
	CSttMqttTopicCmbn oCmbn;
	oCmbn.ResetSubTopics();
	oCmbn.AddSubTopic(strFromSN);
	oCmbn.AddSubTopic(strDeviceSN);
	oCmbn.AddSubTopic(MQTT_CMD_ID_IotState);
	oCmbn.AddSubTopic(SYS_STATE_RETTYPE_RTDATA);

	//CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oCmbn.m_nBufferLength = pSysState->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, &oCmbn.m_pszBuffer, 0, nFormatType);
	//CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	g_thePpSvrMqttClient->PublicTopic(oCmbn);

	return 0;
}

CMqttPpServerClient* CPpSvrInterfaceMqttClient::FindByDeviceSN(const CString &strDeviceSN)
{
	POS pos = m_listMqttMsgProcess.GetHeadPosition();
	
	while (pos != NULL)
	{
		CMqttPpServerClient* pClient = (CMqttPpServerClient *)m_listMqttMsgProcess.GetNext(pos);

		if (pClient->GetDeviceSN() == strDeviceSN)
		{
			return pClient;
		}
	}

	return NULL;
}

BOOL CPpSvrInterfaceMqttClient::Connect()
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}


	if (m_strClientID.GetLength() > 0)
	{
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		m_strClientID.Format(_T("IotProtoSvr_%u_%02d%02d%03d")
			,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
	}

	m_oMqttClient.AttachMqttMsgInterface(this);
	BOOL bRet = m_oMqttClient.InitMqttClient(m_strIP, m_nPort, m_strClientID,_T(""), _T(""), false);

	if (bRet)
	{
		//连接成功后，主动订阅主题
		SubcribeMqttTopic(0);
		MqttSubscribeTopic();
	}

	return bRet;
}

void CPpSvrInterfaceMqttClient::Disconnect()
{
	UnSubcribeMqttTopic();
	m_oMqttClient.Disconnect();
}



//////////////////////////////////////////////////////////////////////////
CSttParas* CPpSvrInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser)
{
	CSttParas *pParas = new CSttParas();

	stt_pst_get_paras(oParser, *pParas);

	return pParas;
}

void CPpSvrInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttParas.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CPpSvrInterfaceMqttClient::stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttTestCmd &oSttTestCmd, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oSttTestCmd.SetXml_UTF8(oParser.m_pMqttPkgBuffer, oParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, nXmlRWType);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

//

//////////////////////////////////////////////////////////////////////////
//
void CPpSvrInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oParas.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CPpSvrInterfaceMqttClient::stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn)
{
	CSttParas oParas;
	oParas.Append(pDataGroup);

	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);

	oParas.RemoveAll();
}

void CPpSvrInterfaceMqttClient::stt_mqtt_GetParasBuffer(CSttTestCmd &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType)
{
	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oTopicCmbn.m_nBufferLength = oCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &oTopicCmbn.m_pszBuffer, 0, nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CPpSvrInterfaceMqttClient::stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, CSttXDevice *pDestDevice)
{
	ASSERT (FALSE);
}

void CPpSvrInterfaceMqttClient::stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const char *pszSttCmdID, const char *pszSttCmdID2, CSttXDevice *pDestDevice)
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