#include "stdafx.h"
#include "SttMqttClient_QT.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CMqttMsgInterface* CMqttClient::g_pMqttMsgInterface = NULL;
/////////////////////////////////////////////
char pszRcvTopic[1024];
BOOL bDataIsSending = FALSE;

static UINT MqttClient_RCV_Thread(LPVOID pParam)
{
    CMqttClient *pThead = (CMqttClient*)pParam;

    pThead->RCV_Thread();

    return 0;
}


CMqttClient::CMqttClient()
{
	m_bConnected = FALSE;
	m_pMqttClient = new MQTT::Client<IPStack, Countdown>(m_ipstack);
    m_pThread = NULL;
}

CMqttClient::~CMqttClient()
{
	if (m_pMqttClient != NULL)
	{
		m_pMqttClient->disconnect();
		delete m_pMqttClient;
		m_pMqttClient = NULL;
	}
	if(m_pThread != NULL)
	{
		delete m_pThread;
		m_pThread = NULL;
	}
    m_ipstack.disconnect();	
}

void CMqttClient::RCV_Thread()
{
    Countdown tmOut(10000);
    Countdown tmOut2(100);

    while (m_bConnected)
    {
        tmOut2.countdown_ms(100);
        m_pMqttClient->cycle(tmOut2);
//        m_pMqttClient->yield(50);

        if(m_pTopic != NULL && tmOut.expired())
        {
            tmOut.countdown_ms(10000);
            if(!bDataIsSending)
            m_pMqttClient->publish(m_pTopic, m_oMqttSendBuff);
        }

		if(!m_pMqttClient->isConnected())
		{
			OnDisconnected(this,"Server Close");
		}
    }
}

void CMqttClient::Create_MqttClient_RCV_Thread()
{
	if(m_pThread == NULL)
	{
    m_pThread = new CWinThread(MqttClient_RCV_Thread, this);
		m_pThread->m_bAutoDelete = FALSE;
	}

    m_pThread->ResumeThread();
}

void CMqttClient::OnMsgArrived(MQTT::MessageData &messageData)
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMsgArrived:Topic[%s],DataLen[%d]"),messageData.topicName.cstring,messageData.message.payloadlen);

    if (g_pMqttMsgInterface != NULL && messageData.topicName.lenstring.data != NULL)
	{
//        char *pTopic = (char*)malloc(messageData.topicName.lenstring.len+1);
        memset(pszRcvTopic,0,1024);
        memcpy(pszRcvTopic,messageData.topicName.lenstring.data,messageData.topicName.lenstring.len);
        *(pszRcvTopic+messageData.topicName.lenstring.len) = '\0';
        g_pMqttMsgInterface->OnMqttMsgRecieve(pszRcvTopic,(char *)messageData.message.payload,messageData.message.payloadlen);
//        free(pTopic);
	}
}

void CMqttClient::OnDisconnected(void *context, char *cause)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:Cause[%s]"),cause);

	if (context != NULL)
	{
		CMqttClient *pClient = (CMqttClient *)context;
		pClient->m_bConnected = FALSE;
		if (pClient->g_pMqttMsgInterface != NULL)
		{
			pClient->g_pMqttMsgInterface->OnMqttDisconnected(cause);
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

	MQTTPacket_connectData conn_data = MQTTPacket_connectData_initializer;

    conn_data.cleansession = 1;
    conn_data.MQTTVersion = 3;
    conn_data.clientID.cstring = (char *)strClientID.GetString();

	if(bAuthority)
	{
		conn_data.username.cstring = (char *)strUser.GetString();
		conn_data.password.cstring = (char *)strPwd.GetString();
	}

	int nRet = m_pMqttClient->connect(conn_data);

	if (nRet != MQTT::SUCCESS)
	{
		m_bConnected = FALSE;
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt联机[%s][%s]---失败[MQTTClient_connect:%d]"),strServerURI.GetString(),strClientID.GetString(),nRet);
		return FALSE;
	}

	m_bConnected = TRUE;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Mqtt联机[%s][%s]---成功"),strServerURI.GetString(),strClientID.GetString());

    m_pMqttClient->setDefaultMessageHandler(CMqttClient::OnMsgArrived);
    Create_MqttClient_RCV_Thread();

	return m_bConnected;
}

BOOL CMqttClient::InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{	
	int nRet = m_ipstack.connect(strIP.GetString(),nPort);
	if(nRet < 0)
	{
		return FALSE;
	}

	CString strServerURI;
    strServerURI.Format(_T("tcp://%s:%d"),strIP.GetString(),nPort);

	return InitMqttClient(strServerURI,strClientID,strUser,strPwd,bAuthority);
}

BOOL CMqttClient::Disconnect(unsigned int nTimeout)
{
	if (!IsConnectSuccessful())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("已经断开连接"));
		return TRUE;
	}

	long nRet = m_pMqttClient->disconnect();
	if (MQTT::SUCCESS != nRet)
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
    if (m_pMqttClient == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[g_pSttMqttClientTool->m_oMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = 0;
	MQTT::Message pubmsg;

	if (nQos < 0 || nQos > 2) 
	{ 
		nQos = 0; 
	}

	MQTT::QoS qos = MQTT::QOS0;
	if (nQos == 1)
	{
		qos = MQTT::QOS1;
	}
	else if (nQos == 2)
	{
		qos = MQTT::QOS2;
	}

	pubmsg.payload = (void *)pszData;
	pubmsg.payloadlen = nDataLen;

	pubmsg.qos = qos;
	pubmsg.retained = 0;

    bDataIsSending = TRUE;
	nRet = m_pMqttClient->publish(pszTopic,pubmsg);
    bDataIsSending = FALSE;
	if (MQTT::SUCCESS != nRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---失败[MQTTClient_publishMessage:%d]"),pszTopic,nRet);
		return FALSE;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题【%s】---成功"),pszTopic);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("发布主题数据【%s】---成功"),pszData);
	return TRUE;
}

BOOL CMqttClient::SubscribeTopic(const char* pszTopic,int nQos)
{
    if (m_pMqttClient == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题【%s】---失败[g_pSttMqttClientTool->m_pMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	MQTT::QoS qos = MQTT::QOS0;
	if (nQos == 1)
	{
		qos = MQTT::QOS1;
	}
	else if (nQos == 2)
	{
		qos = MQTT::QOS2;
	}

    int nRet = m_pMqttClient->subscribe(pszTopic,qos,CMqttClient::OnMsgArrived);
	if (nRet != MQTT::SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题【%s】---失败[MQTTClient_subscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("订阅主题[%s]---成功"),pszTopic);
	return TRUE;
}

BOOL CMqttClient::UnSubscribeTopic(const char* pszTopic)
{
    if (m_pMqttClient == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题【%s】---失败[g_pSttMqttClientTool->m_pMqttClient == 0]"),pszTopic);
		return FALSE;
	}

	int nRet = m_pMqttClient->unsubscribe(pszTopic);
	if (nRet != MQTT::SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题【%s】---失败[MQTTClient_unsubscribe:%d]"),pszTopic,nRet);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("取消订阅主题[%s]---成功"),pszTopic);
	return TRUE;
}

/*

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    IPStack ipstack = IPStack();
    float version = 0.3;
    const char* topic = "mbed-sample";

    printf("Version is %f\n", version);

    MQTT::Client<IPStack, Countdown> client = MQTT::Client<IPStack, Countdown>(ipstack);

    const char* strRemote = "127.0.0.1";
    int port = 1883;
    printf("Connecting to %s:%d\n", strRemote, port);
    int rc = ipstack.connect(strRemote, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\n", rc);

    printf("MQTT connecting\n");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = (char*)"mbed-icraggs";
    rc = client.connect(data);
    if (rc != 0)
        printf("rc from MQTT connect is %d\n", rc);
    printf("MQTT connected\n");

    rc = client.subscribe("+", MQTT::QOS2, messageArrived);
    if (rc != 0)
        printf("rc from MQTT subscribe is %d\n", rc);

    MQTT::Message message;

    // QoS 0
    char buf[100];
    sprintf(buf, "Hello World!  QoS 0 message from app version %f", version);
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    while (arrivedcount == 0)
        client.yield(100);

    // QoS 1
    printf("Now QoS 1\n");
    sprintf(buf, "Hello World!  QoS 1 message from app version %f", version);
    message.qos = MQTT::QOS1;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    while (arrivedcount == 1)
        client.yield(100);

    // QoS 2
    sprintf(buf, "Hello World!  QoS 2 message from app version %f", version);
    message.qos = MQTT::QOS2;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    while (arrivedcount == 2)
        client.yield(100);

    rc = client.unsubscribe(topic);
    if (rc != 0)
        printf("rc from unsubscribe was %d\n", rc);

    rc = client.disconnect();
    if (rc != 0)
        printf("rc from disconnect was %d\n", rc);

    ipstack.disconnect();

    printf("Finishing with %d messages received\n", arrivedcount);

    return a.exec();
}

 * */
