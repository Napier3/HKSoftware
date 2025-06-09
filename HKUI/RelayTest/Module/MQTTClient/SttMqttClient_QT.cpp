#include "stdafx.h"
#include "SttMqttClient_QT.h"

#ifdef _DEBUG
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

/////////////////////////////////////////////
char pszRcvTopic[1024];
BOOL bConnected = FALSE;
BOOL bInited = FALSE;
long nTimeOut = 0;
CMqttMsgInterface *g_pMqttMsgInterface = NULL;

#define not_MQTTAsync

CMqttClient::CMqttClient()
{
	m_nPublicToken = 0;
	m_nSubToken = 0;
	m_nUnSubToken = 0;
}

CMqttClient::~CMqttClient()
{
	if(bInited)
	{
#ifndef not_MQTTAsync
		MQTTAsync_destroy(&m_oMQTTclient);
#endif
        bInited = FALSE;
	}
}

void ConnectLost(void *context, char *cause)
{
#ifndef not_MQTTAsync
    if (g_pMqttMsgInterface != NULL)
	{
		g_pMqttMsgInterface->OnMqttDisconnected(cause);
	}

	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("MQTT Reconnecting"));
	conn_opts.keepAliveInterval = MQTT_TIMEOUT_DEFAULT;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("���� ---ʧ��[%d]"),rc);
		bConnected = FALSE;
	}
#endif
}

//! ��Ϣ���ĵĻص�����
#ifndef not_MQTTAsync
int OnMsgArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
    if (g_pMqttMsgInterface != NULL && topicName != NULL)
	{
		memset(pszRcvTopic,0,1024);
		memcpy(pszRcvTopic,topicName,topicLen);
		*(pszRcvTopic+topicLen) = '\0';
		g_pMqttMsgInterface->OnMqttMsgRecieve(pszRcvTopic,(char *)message->payload,message->payloadlen);
	}

	MQTTAsync_free(topicName);
	MQTTAsync_free(message);

	return 1;
}
#endif

BOOL CMqttClient::IsConnectSuccessful()
{
	return bConnected;
}

#ifndef not_MQTTAsync
//! ���� mqtt �������ɹ��ص�����
void OnConnect(void *context, MQTTAsync_successData* response)
{
	nTimeOut = 0;
	bConnected = TRUE;
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Mqtt�����ɹ�"));
	if (g_pMqttMsgInterface != NULL)
	{
		g_pMqttMsgInterface->OnMqttConnected();
	}
}

//! �Ͽ��� mqtt ���������ӻص�����
void OnConnectFailure(void *context, MQTTAsync_failureData* response)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Mqtt����ʧ��"));
}
#endif

void CMqttClient::InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
#ifndef not_MQTTAsync
    if(bInited)
	{
		MQTTAsync_destroy(&m_oMQTTclient);
		bInited = FALSE;
	}

	bConnected = FALSE;
	CString strServerURI;
    strServerURI.Format(_T("tcp://%s:%d"),strIP.GetString(),nPort);

	int ret;
	MQTTAsync_connectOptions conn_opt = MQTTAsync_connectOptions_initializer;	//!< ��ʼ������ѡ��

	ret = MQTTAsync_create(&m_oMQTTclient, strServerURI.GetString(), strClientID.GetString(), MQTTCLIENT_PERSISTENCE_NONE, NULL);
	if(ret != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Cannot Create MQTT Client"));
		return;
	}

	bInited = TRUE;
	ret = MQTTAsync_setCallbacks(m_oMQTTclient, NULL, ConnectLost, OnMsgArrived, NULL); 		//!< ��ʼ��������Ϣ�ص�;
	if(ret != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Cannot Set MQTT OnMsgArrived"));
		MQTTAsync_destroy(&m_oMQTTclient);
		bInited = FALSE;
		return;
	}

	conn_opt.keepAliveInterval = MQTT_TIMEOUT_DEFAULT;
	conn_opt.cleansession = 1;
	conn_opt.onSuccess = OnConnect;
	conn_opt.onFailure = OnConnectFailure;
	conn_opt.automaticReconnect = 1;
	conn_opt.context = m_oMQTTclient;

	if(bAuthority)
	{
		conn_opt.username = strUser.GetString();
		conn_opt.password = strPwd.GetString();
	}

	ret = MQTTAsync_connect(m_oMQTTclient, &conn_opt);

	//��Ϊ���첽�ģ���MQTTAsync_connect���ص�ʱ��ֻ�Ǵ���ײ����Բ��������˼��
	//����ȷ����ʱ����ʾ�ײ��������˸�connect��������
	if(ret != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt����[%s][%s]---ʧ��[MQTTClient_connect:%d]"),strServerURI.GetString(),strClientID.GetString(),ret);
		MQTTAsync_destroy(&m_oMQTTclient);
		bInited = FALSE;
	}
#endif
}

#ifndef not_MQTTAsync
void onSendSuccess(void* context, MQTTAsync_successData* response)
{
	nTimeOut = 0;
}

void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��������[token %d] ---����ʧ��[error code %d]"),response->token, response->code);
}
#endif

void CMqttClient::PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos, unsigned int nTimeout)
{
#ifndef not_MQTTAsync
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---[token %d]"),pszTopic,m_nPublicToken);
	if(!bConnected)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[bConnected = FALSE]"),pszTopic);
		return;
	}

	if(m_oMutex.tryLock(nTimeout))
	{
		MQTTAsync_message message = MQTTAsync_message_initializer;
		MQTTAsync_responseOptions res_option = MQTTAsync_responseOptions_initializer;
		res_option.onSuccess = onSendSuccess;
		res_option.onFailure = onSendFailure;
		res_option.context = m_oMQTTclient;
		res_option.token = m_nPublicToken++;
		message.payload = pszData;
		message.payloadlen = nDataLen;
		message.qos = nQos;

		int rc;
		if ((rc = MQTTAsync_sendMessage(m_oMQTTclient, pszTopic, &message, &res_option)) != MQTTASYNC_SUCCESS)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[%d]"),pszTopic,rc);
		}
		m_oMutex.unlock();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[trylock fail]"),pszTopic);
	}
#endif
}

#ifndef not_MQTTAsync
void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("��������[token %d] ---����ʧ��[error code %d]"),response->token,response->code);
}
#endif

void CMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
#ifndef not_MQTTAsync
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---[token %d]"),pszTopic,m_nSubToken);
	if(!bConnected)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[bConnected = FALSE]"),pszTopic);
		return;
	}

	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	int rc;
	opts.onFailure = onSubscribeFailure;
	opts.context = m_oMQTTclient;
	opts.token = m_nSubToken++;
	if ((rc = MQTTAsync_subscribe(m_oMQTTclient, pszTopic, nQos, &opts)) != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������⡾%s��---ʧ��[%d]"),pszTopic,rc);
	}
#endif
}

#ifndef not_MQTTAsync
void onUnSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ����������[token %d] ---����ʧ��[error code %d]"),response->token,response->code);
}
#endif

void CMqttClient::UnSubscribeTopic(const char* pszTopic)
{
#ifndef not_MQTTAsync
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ���������⡾%s��---[token %d]"),pszTopic,m_nUnSubToken);
	if(!bConnected)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ���������⡾%s��---ʧ��[bConnected = FALSE]"),pszTopic);
		return;
	}

	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	int rc;
	opts.onFailure = onUnSubscribeFailure;
	opts.context = m_oMQTTclient;
	opts.token = m_nUnSubToken++;
	if ((rc = MQTTAsync_unsubscribe(m_oMQTTclient, pszTopic, &opts)) != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ȡ���������⡾%s��---ʧ��[%d]"),pszTopic,rc);
	}
#endif
}

void CMqttClient::SendHeart()
{
	if(bConnected)
	{
		if(nTimeOut > MQTT_TIMEOUT_DEFAULT)
		{
			PublicTopic(m_pTopicHeart,NULL,0);
		}
		else
		{
			nTimeOut++;
		}
	}
}

void CMqttClient::Disconnect()
{
#ifndef not_MQTTAsync
    bConnected = FALSE;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;
	if ((rc = MQTTAsync_disconnect(m_oMQTTclient, &opts)) != MQTTASYNC_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�Ͽ����� ---ʧ��[%d]"),rc);
	}

	MQTTAsync_destroy(&m_oMQTTclient);
	bInited = FALSE;
#endif
}
