#pragma once

/*******************************
CSttMqttClient��Mqtt�ͻ�����Ϊȫ��Ψһ������
CMqttClient��Mqtt�ͻ�����Ϊ�ֲ�������
*******************************/

#include "mqtt/include/MQTTClient.h"               //����mqtt��ͷ�ļ�
#include "mqtt/include/MQTTClientPersistence.h"    //����mqtt��ͷ�ļ�
#include "mqtt/include/MQTTProperties.h"           //����mqtt��ͷ�ļ�
#include "MqttCmmInterface.h"

class CMqttClient
{
public:
	CMqttClient();
	virtual ~CMqttClient();

private:
	MQTTClient m_oMqttClient;					//����mqtt�ͻ��˶���
	CMqttMsgInterface *m_pMqttMsgInterface;		//mqtt�¼��ӿ�
	BOOL m_bConnected;

public:
	void AttachMqttMsgInterface(CMqttMsgInterface *pInterface){m_pMqttMsgInterface = pInterface;}
	BOOL IsConnectSuccessful();

	//mqtt�¼�ȫ�ֻص��ӿ�
	static int OnMsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
	static void OnDisconnected(void *context, char *cause);

	//mqtt�ͻ��˳�ʼ�����Ӷ����ӿ�
	BOOL InitMqttClient(const CString &strServerURI,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	BOOL Disconnect(unsigned int nTimeout = 2000);

	//mqtt�ͻ��˶��ġ�������ȡ����������ӿ�
	BOOL PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos=MQTT_QOS_DEFAULT, unsigned int nTimeout=MQTT_TIMEOUT_DEFAULT);
	BOOL SubscribeTopic(const char* pszTopic,int nQos);
	BOOL UnSubscribeTopic(const char* pszTopic);
};
