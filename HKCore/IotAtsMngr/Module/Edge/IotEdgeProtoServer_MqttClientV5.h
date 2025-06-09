#pragma once

#include "EdgeMqttClientBase.h"

class CIotEdgeProtoServer_MqttClientV5:public CEdgeMqttClientBase
{
public:
	CIotEdgeProtoServer_MqttClientV5();
	virtual ~CIotEdgeProtoServer_MqttClientV5();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

public:
};