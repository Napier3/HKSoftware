#pragma once

#include "EdgeMqttClientBase.h"

//IotEdgeMqttServer对应的mqtt客户端

class CIotEdgeServer_MqttClient:public CEdgeMqttClientBase
{
public:
	CIotEdgeServer_MqttClient();
	virtual ~CIotEdgeServer_MqttClient();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);

	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);
};