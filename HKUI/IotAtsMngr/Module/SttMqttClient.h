#pragma once

/*******************************
CSttMqttClient：Mqtt客户端作为全局唯一对象类
CMqttClient：Mqtt客户端作为局部对象类
*******************************/

#include "mqtt/include/MQTTClient.h"               //引用mqtt的头文件
#include "mqtt/include/MQTTClientPersistence.h"    //引用mqtt的头文件
#include "mqtt/include/MQTTProperties.h"           //引用mqtt的头文件
#include "MqttCmmInterface.h"

class CMqttClient
{
public:
	CMqttClient();
	virtual ~CMqttClient();

private:
	MQTTClient m_oMqttClient;					//具体mqtt客户端对象
	CMqttMsgInterface *m_pMqttMsgInterface;		//mqtt事件接口
	BOOL m_bConnected;

public:
	void AttachMqttMsgInterface(CMqttMsgInterface *pInterface){m_pMqttMsgInterface = pInterface;}
	BOOL IsConnectSuccessful();

	//mqtt事件全局回调接口
	static int OnMsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
	static void OnDisconnected(void *context, char *cause);

	//mqtt客户端初始化连接断链接口
	BOOL InitMqttClient(const CString &strServerURI,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL Disconnect(unsigned int nTimeout = 2000);

	//mqtt客户端订阅、发布和取消订阅主题接口
	BOOL PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos=MQTT_QOS_DEFAULT, unsigned int nTimeout=MQTT_TIMEOUT_DEFAULT);
	BOOL SubscribeTopic(const char* pszTopic,int nQos);
	BOOL UnSubscribeTopic(const char* pszTopic);
};
