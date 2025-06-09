#pragma once

/*******************************
CSttMqttClientTool：Mqtt客户端作为全局唯一对象类
CMqttClient：Mqtt客户端作为局部对象类
*******************************/

#include "SttMqttClient.h"

class CSttMqttClientTool
{
public:
	CSttMqttClientTool();
	virtual ~CSttMqttClientTool();

	static CSttMqttClientTool *g_pSttMqttClientTool;
	static long g_nSttMqttClientToolRef;

private:
	MQTTClient m_oMqttClient;					//具体mqtt客户端对象
	CMqttMsgInterface *m_pSttMqttMsgInterface;	//mqtt事件接口

	BOOL m_bConnected;
	CString m_strClientID;
	
public:
	void AttachSttMqttMsgInterface(CMqttMsgInterface *pInterface){m_pSttMqttMsgInterface = pInterface;}
	static CSttMqttClientTool *Create();
	static void Release();

	static BOOL IsConnectSuccessful();
	static CString GetClientID();

	//mqtt事件全局回调接口
	static int OnMsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
	static void OnDisconnected(void *context, char *cause);

	static BOOL InitMqttClient(const CString &strServerURI,const CString &strClientID);
	static BOOL InitMqttClient(const CString &strIP,long nPort,const CString &strClientID);
	static BOOL Disconnect(unsigned int nTimeout = 2000);

	static BOOL PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos=MQTT_QOS_DEFAULT, unsigned int nTimeout=MQTT_TIMEOUT_DEFAULT);
	static BOOL SubscribeTopic(const char* pszTopic,int nQos);
	static BOOL UnSubscribeTopic(const char* pszTopic);
};
