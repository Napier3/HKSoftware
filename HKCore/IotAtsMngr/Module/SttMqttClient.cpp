#include "stdafx.h"
#include "SttMqttClient.h"
#include "SttMqttClientEngineConfig.h"
#include "../../Module/Socket/XPing.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

//��·��������ڹ���·����
// #ifdef PROJ_PATH_TIOATSMNGR
// #pragma comment(lib, "..\\Module\\mqtt\\lib\\paho-mqtt3c.lib")  //���ص�.lib�ļ�
// #else
// #pragma comment(lib, "..\\..\\..\\IotAtsMngr\\Module\\mqtt\\lib\\paho-mqtt3c.lib")  //���ص�.lib�ļ�
// #endif

//project attr ���������� �� ������ �� ���� �� ����Ŀ¼��
//..\..\IotAtsMngr\Module\mqtt\lib
#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
#pragma comment(lib, "paho-mqtt3c.lib")  //���ص�.lib�ļ�
#endif

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
#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
		MQTTClient_destroy(&m_oMqttClient);
#endif
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
#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
#endif
	return 1;
}

void CMqttClient::OnDisconnected(void *context, char *cause)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:Cause[%s]"),cause);

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

BOOL CMqttClient::InitMqttClient(const CString &strServerURI,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
	if (IsConnectSuccessful())
	{
		return TRUE;
	}

	if (m_oMqttClient != 0)
	{
#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
		MQTTClient_destroy(&m_oMqttClient);
#endif
		m_oMqttClient = 0;	
	}

	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
    MQTTClient_create(&m_oMqttClient, strServerURI.GetString(), strClientID.GetString(),MQTTCLIENT_PERSISTENCE_NONE, NULL);
#endif
	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.connectTimeout = 5;

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	MQTTClient_setCallbacks(m_oMqttClient, this, &CMqttClient::OnDisconnected, &CMqttClient::OnMsgArrived, NULL);

	int nRet = MQTTClient_connect(m_oMqttClient, &conn_opts);

	if (nRet != MQTTCLIENT_SUCCESS)
	{
		m_bConnected = FALSE;
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt����[%s][%s]---ʧ��[MQTTClient_connect:%d]"),strServerURI.GetString(),strClientID.GetString(),nRet);
		return FALSE;
	}
#endif

	m_bConnected = TRUE;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt����[%s][%s]---�ɹ�"),strServerURI.GetString(),strClientID.GetString());

	return m_bConnected;
}

BOOL CMqttClient::InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
	if (!xping((char *)strIP.GetString()))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Ping��%s �������Ӳ�ͨ��"),strIP.GetString());
		return FALSE;
	}

	CString strServerURI;
    strServerURI.Format(_T("tcp://%s:%d"),strIP.GetString(),nPort);

	return InitMqttClient(strServerURI,strClientID, _T(""), _T(""));
}

BOOL CMqttClient::Disconnect(unsigned int nTimeout)
{
	if (!IsConnectSuccessful())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("�Ѿ��Ͽ�����"));
		return TRUE;
	}

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	long nRet = MQTTClient_disconnect(m_oMqttClient, nTimeout);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�Ͽ�����ʧ�ܡ�%s��"),nRet);
		return FALSE;
	}
#endif

	m_bConnected = FALSE;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("�Ͽ����ӳɹ�"));
	return TRUE;
}

BOOL CMqttClient::PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos, unsigned int nTimeout)
{
	if (m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
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

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	nRet = MQTTClient_publishMessage(m_oMqttClient, pszTopic, &pubmsg, &token);
#endif
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[MQTTClient_publishMessage:%d]"),pszTopic,nRet);
		return FALSE;
	}

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	nRet = MQTTClient_waitForCompletion(m_oMqttClient, token, nTimeout);
#endif
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[MQTTClient_waitForCompletion:%d]"),pszTopic,nRet);
		return FALSE;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---�ɹ�"),pszTopic);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�����������ݡ�%s��---�ɹ�"),pszData);
	return TRUE;
}

BOOL CMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
	if (m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	int nRet = MQTTClient_subscribe(m_oMqttClient, pszTopic, nQos);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[MQTTClient_subscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��������[%s]---�ɹ�"),pszTopic);
	return TRUE;
}

BOOL CMqttClient::UnSubscribeTopic(const char* pszTopic)
{
	if (m_oMqttClient == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ���������⡾%s��---ʧ��[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

#ifndef _MQTT_NEDD_TO_REMOVE_LIB_
	int nRet = MQTTClient_unsubscribe(m_oMqttClient, pszTopic);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ���������⡾%s��---ʧ��[MQTTClient_unsubscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ����������[%s]---�ɹ�"),pszTopic);
	return TRUE;
}
