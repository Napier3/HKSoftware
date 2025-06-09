#pragma once

#include "SttMqttClientBase.h"

//IotEngineProtocolServer对应的mqtt客户端

class CIotEngineProtoServer_MqttClient:public CSttMqttClientBase
{
public:
	CIotEngineProtoServer_MqttClient();
	virtual ~CIotEngineProtoServer_MqttClient();

public:
// 	//连接成功后，订阅主题
// 	virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

};