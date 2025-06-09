#pragma once

/*******************************
CSttMqttClient��Mqtt�ͻ�����Ϊȫ��Ψһ������
CMqttClient��Mqtt�ͻ�����Ϊ�ֲ�������
*******************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>


//#include "MQTTAsync.h"
#include "../../../IotAtsMngr/Module/MqttCmmInterface.h"
#include "QMutex"

extern CMqttMsgInterface *g_pMqttMsgInterface;		//mqtt�¼��ӿ�

class CMqttClient
{
public:
	CMqttClient();
	virtual ~CMqttClient();
	char *m_pTopicHeart;
	long m_nPublicToken;
	long m_nSubToken;
	long m_nUnSubToken;
private:			
    //MQTTAsync m_oMQTTclient;//����mqtt�ͻ��˶���
	QMutex m_oMutex;

public:
    void AttachMqttMsgInterface(CMqttMsgInterface *pInterface){g_pMqttMsgInterface = pInterface;}
	BOOL IsConnectSuccessful();

	//mqtt�ͻ��˳�ʼ�����Ӷ����ӿ�
	void InitMqttClient(const CString &strIP,long nPort,const CString &strClientID,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
	void Disconnect();
	//mqtt�ͻ��˶��ġ�������ȡ����������ӿ�
	void PublicTopic(const char* pszTopic, char* pszData,int nDataLen, int nQos=MQTT_QOS_DEFAULT, unsigned int nTimeout=MQTT_TIMEOUT_DEFAULT);
	void SubscribeTopic(const char* pszTopic,int nQos);
	void UnSubscribeTopic(const char* pszTopic);
	void SendHeart();
};
