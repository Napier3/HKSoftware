#pragma once

#include "IotVmX_MqttClientBase.h"

//IotEdgeMqttServer对应的mqtt客户端

class CIotVmServer_MqttClient : public CIotVmX_MqttClientBase
{
public:
	CIotVmServer_MqttClient();
	virtual ~CIotVmServer_MqttClient();

public:
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);
	CDataGroup *m_pVmConfig;
};