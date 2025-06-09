#include "stdafx.h"
#include "SttMqttClient.h"
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
// #pragma comment(lib, "paho-mqtt3c.lib")  //加载的.lib文件

/////////////////////////////////////////////

CMqttClient::CMqttClient()
{
	m_bConnected = FALSE;
	m_oMqttClient = NULL;
}

CMqttClient::~CMqttClient()
{
	if (m_oMqttClient != 0)
	{
		MQTTClient_destroy(&m_oMqttClient);
		m_oMqttClient = 0;
	}
}

int CMqttClient::OnMsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	if (context != NULL)
	{
		CMqttClient *pClient = (CMqttClient *)context;
		if (pClient->m_pMqttMsgInterface != NULL)
		{
			pClient->m_pMqttMsgInterface->OnMqttMsgRecieve(topicName,(char *)message->payload,message->payloadlen);
		}
	}

	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}

void CMqttClient::OnDisconnected(void *context, char *cause)
{
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T(" 1 OnDisconnected:Cause[%s]"),cause);

	if (context != NULL)
	{
		CMqttClient *pClient = (CMqttClient *)context;
		pClient->m_bConnected = FALSE;
		if (pClient->m_pMqttMsgInterface != NULL)
		{
			pClient->m_pMqttMsgInterface->OnMqttDisconnected(cause);
		}
	}
}

BOOL CMqttClient::IsConnectSuccessful()
{
	return m_bConnected;
}

BOOL CMqttClient::InitMqttClient(const CString &strServerURI,const CString &strClientID)
{
	if (IsConnectSuccessful())
	{
		return TRUE;
	}

	if (m_oMqttClient != 0)
	{
		MQTTClient_destroy(&m_oMqttClient);
		m_oMqttClient = 0;
	}


	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int nRet = MQTTClient_create(&m_oMqttClient, strServerURI.GetString(), strClientID.GetString(), MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (nRet != MQTTCLIENT_SUCCESS)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("Mqtt [%s][%s]---Failed [MQTTClient_create: %d]"), strServerURI.GetString(), strClientID.GetString(), nRet);
        return FALSE;
    }
	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.connectTimeout = 5;

	MQTTClient_setCallbacks(m_oMqttClient, this, &CMqttClient::OnDisconnected, &CMqttClient::OnMsgArrived, NULL);

    nRet = MQTTClient_connect(m_oMqttClient, &conn_opts);

	if (nRet != MQTTCLIENT_SUCCESS)
	{
		m_bConnected = FALSE;
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt [%s][%s]---Failed [MQTTClient_connect: %d]")
                                   ,strServerURI.GetString(),strClientID.GetString(),nRet);
		return FALSE;
	}

	m_bConnected = TRUE;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt [%s][%s]---OK")
                               ,strServerURI.GetString(),strClientID.GetString());

	return m_bConnected;
}

BOOL CMqttClient::InitMqttClient(const CString &strIP,long nPort,const CString &strClientID)
{
//	if (!xping((char *)strIP.GetString()))
//	{
//        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Ping：%s 网络连接不通！")
//                                   ,strIP.GetString());
//		return FALSE;
//	}

	CString strServerURI;
    strServerURI.Format(_T("tcp://%s:%d"),strIP.GetString(),nPort);

	return InitMqttClient(strServerURI,strClientID);
}

BOOL CMqttClient::Disconnect(unsigned int nTimeout)
{
	if (!IsConnectSuccessful())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("已经断开连接"));
		return TRUE;
	}

	long nRet = MQTTClient_disconnect(m_oMqttClient, nTimeout);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("断开连接失败【%s】"),nRet);
		return FALSE;
	}

	m_bConnected = FALSE;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("断开连接成功"));
	return TRUE;
}

BOOL CMqttClient::PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos, unsigned int nTimeout)
{
	if (m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Publish【%s】---Failed [g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
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

	nRet = MQTTClient_publishMessage(m_oMqttClient, pszTopic, &pubmsg, &token);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Publish【%s】---Failed [MQTTClient_publishMessage:%d]"),pszTopic,nRet);
		return FALSE;
	}

	nRet = MQTTClient_waitForCompletion(m_oMqttClient, token, nTimeout);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Publish【%s】---Failed [MQTTClient_waitForCompletion:%d]"),pszTopic,nRet);
		return FALSE;
	}

//    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Publish: [%s]---OK"),pszTopic); //临时跟踪
//    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Publish: [%s]---OK"),pszData);  //临时跟踪
	return TRUE;
}

BOOL CMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
	if (m_oMqttClient == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Subscribe [%s]---Failed [g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = MQTTClient_subscribe(m_oMqttClient, pszTopic, nQos);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Subscribe [%s]---Failed [MQTTClient_subscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Subscribe[%s]---OK"),pszTopic);
	return TRUE;
}

BOOL CMqttClient::UnSubscribeTopic(const char* pszTopic)
{
	if (m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Unsubscribe【%s】---Failed [g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = MQTTClient_unsubscribe(m_oMqttClient, pszTopic);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Unsubscribe【%s】---Failed [MQTTClient_unsubscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Unsubscribe[%s]---OK"),pszTopic);
	return TRUE;
}
