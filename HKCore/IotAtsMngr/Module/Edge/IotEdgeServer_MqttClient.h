#pragma once

#include "EdgeMqttClientBase.h"

//IotEdgeMqttServer��Ӧ��mqtt�ͻ���

class CIotEdgeServer_MqttClient:public CEdgeMqttClientBase
{
public:
	CIotEdgeServer_MqttClient();
	virtual ~CIotEdgeServer_MqttClient();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);

	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);
};