#include "stdafx.h"
#include "SttMqttClientTool.h"
#include "SttMqttClientEngineConfig.h"
#include "../../Module/Socket/XPing.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

//该路径是相对于工程路径的
// #ifdef PROJ_PATH_TIOATSMNGR
// #pragma comment(lib, "..\\Module\\mqtt\\lib\\paho-mqtt3c.lib")  //加载的.lib文件
// #else
// #pragma comment(lib, "..\\..\\..\\IotAtsMngr\\Module\\mqtt\\lib\\paho-mqtt3c.lib")  //加载的.lib文件
// #endif

//project attr ：配置属性 ： 连接器 ： 常规 ： 附加目录库
//..\..\IotAtsMngr\Module\mqtt\lib

CSttMqttClientTool *CSttMqttClientTool::g_pSttMqttClientTool = NULL;
long CSttMqttClientTool::g_nSttMqttClientToolRef = 0;

CSttMqttClientTool::CSttMqttClientTool()
{
	m_bConnected = FALSE;
	m_oMqttClient = NULL;
}

CSttMqttClientTool::~CSttMqttClientTool()
{

}

// void CMqttClient::OnDelivered(void *context, MQTTClient_deliveryToken dt)
// {
// 	printf("Message with token value %d delivery confirmed\n", dt);
// //	m_DeliveredToken = dt;
// }

int CSttMqttClientTool::OnMsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMsgArrived:Topic[%s],DataLen[%d]"),topicName,message->payloadlen);

	g_pSttMqttClientTool->m_pSttMqttMsgInterface->OnMqttMsgRecieve(topicName,(char *)message->payload,message->payloadlen);

	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}

void CSttMqttClientTool::OnDisconnected(void *context, char *cause)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:Cause[%s]"),cause);

	if (g_pSttMqttClientTool != NULL)
	{
		g_pSttMqttClientTool->m_bConnected = FALSE;
		if (g_pSttMqttClientTool->m_pSttMqttMsgInterface != NULL)
		{
			g_pSttMqttClientTool->m_pSttMqttMsgInterface->OnMqttDisconnected(cause);
		}
	}	
}

CSttMqttClientTool *CSttMqttClientTool::Create()
{
	g_nSttMqttClientToolRef++;

	if (g_nSttMqttClientToolRef == 1)
	{
		g_pSttMqttClientTool = new CSttMqttClientTool;
	}

	return g_pSttMqttClientTool;
}

void CSttMqttClientTool::Release()
{
	g_nSttMqttClientToolRef--;

	if (g_nSttMqttClientToolRef == 0)
	{
		if (g_pSttMqttClientTool->m_oMqttClient != 0)
		{
			MQTTClient_disconnect(g_pSttMqttClientTool->m_oMqttClient, 2000);
			MQTTClient_destroy(&g_pSttMqttClientTool->m_oMqttClient);
		}

		delete g_pSttMqttClientTool;
		g_pSttMqttClientTool = NULL;
	}
}

BOOL CSttMqttClientTool::IsConnectSuccessful()
{
	if (g_pSttMqttClientTool == NULL)
	{
		return FALSE;
	}

	return g_pSttMqttClientTool->m_bConnected;
}

CString CSttMqttClientTool::GetClientID()
{
	if (g_pSttMqttClientTool == NULL)
	{
		return _T("");
	}

	return g_pSttMqttClientTool->m_strClientID;
}

BOOL CSttMqttClientTool::InitMqttClient(const CString &strServerURI,const CString &strClientID)
{
	if (IsConnectSuccessful())
	{
		return TRUE;
	}

	if (g_pSttMqttClientTool->m_oMqttClient != 0)
	{
		MQTTClient_destroy(&g_pSttMqttClientTool->m_oMqttClient);
		g_pSttMqttClientTool->m_oMqttClient = 0;	
	}

	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

	MQTTClient_create(&g_pSttMqttClientTool->m_oMqttClient, strServerURI.GetString(), strClientID.GetString(), MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.connectTimeout = 5;

	MQTTClient_setCallbacks(g_pSttMqttClientTool->m_oMqttClient, NULL, &CSttMqttClientTool::OnDisconnected, &CSttMqttClientTool::OnMsgArrived, NULL);
	
	int nRet = MQTTClient_connect(g_pSttMqttClientTool->m_oMqttClient, &conn_opts);

	if (nRet != MQTTCLIENT_SUCCESS)
	{
		g_pSttMqttClientTool->m_bConnected = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt联机[%s][%s]---失败[MQTTClient_connect:%d]"),strServerURI,strClientID,nRet);
		return FALSE;
	}

	g_pSttMqttClientTool->m_strClientID = strClientID;
	g_pSttMqttClientTool->m_bConnected = TRUE;
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt联机[%s][%s]---成功"),strServerURI,strClientID);

	return g_pSttMqttClientTool->m_bConnected;
}

BOOL CSttMqttClientTool::InitMqttClient(const CString &strIP,long nPort,const CString &strClientID)
{
	if (!xping((char *)strIP.GetString()))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Ping：%s 网络连接不通！"),strIP);
		return FALSE;
	}

	CString strServerURI;
	strServerURI.Format(_T("tcp://%s:%d"),strIP,nPort);

	return CSttMqttClientTool::InitMqttClient(strServerURI,strClientID);
}

BOOL CSttMqttClientTool::Disconnect(unsigned int nTimeout)
{
	if (!IsConnectSuccessful())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("已经断开连接"));
		return TRUE;
	}

	long nRet = MQTTClient_disconnect(g_pSttMqttClientTool->m_oMqttClient, nTimeout);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("断开连接失败【%s】"),nRet);
		return FALSE;
	}

	g_pSttMqttClientTool->m_bConnected = FALSE;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("断开连接成功"));
	return TRUE;
}

BOOL CSttMqttClientTool::PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos, unsigned int nTimeout)
{
	if (g_pSttMqttClientTool == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[g_pSttMqttClientTool == NULL]"),pszTopic);
		return FALSE;
	}
	if (g_pSttMqttClientTool->m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = 0;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token = 0;

	if (nQos < 0 || nQos > 2) 
	{ 
		nQos = 0; 
	}

	pubmsg.payload = (void *)pszData;
	pubmsg.payloadlen = nDataLen;

	pubmsg.qos = nQos;
	pubmsg.retained = 0;

	nRet = MQTTClient_publishMessage(g_pSttMqttClientTool->m_oMqttClient, pszTopic, &pubmsg, &token);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[MQTTClient_publishMessage:%d]"),pszTopic,nRet);
		return FALSE;
	}

	nRet = MQTTClient_waitForCompletion(g_pSttMqttClientTool->m_oMqttClient, token, nTimeout);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[MQTTClient_waitForCompletion:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---成功"),pszTopic);
	return TRUE;
}

BOOL CSttMqttClientTool::SubscribeTopic(const char* pszTopic,int nQos)
{
	if (g_pSttMqttClientTool == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题[%s]---失败[g_pSttMqttClientTool == NULL]"),pszTopic);
		return FALSE;
	}
	if (g_pSttMqttClientTool->m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题【%s】---失败[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = MQTTClient_subscribe(g_pSttMqttClientTool->m_oMqttClient, pszTopic, nQos);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题【%s】---失败[MQTTClient_subscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题[%s]---成功"),pszTopic);
	return TRUE;
}

BOOL CSttMqttClientTool::UnSubscribeTopic(const char* pszTopic)
{
	if (g_pSttMqttClientTool == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题[%s]---失败[g_pSttMqttClientTool == NULL]"),pszTopic);
		return FALSE;
	}
	if (g_pSttMqttClientTool->m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题【%s】---失败[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = MQTTClient_unsubscribe(g_pSttMqttClientTool->m_oMqttClient, pszTopic);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题【%s】---失败[MQTTClient_unsubscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题[%s]---成功"),pszTopic);
	return TRUE;
}
