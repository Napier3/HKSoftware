#pragma once

#include "SttMqttClientBase.h"

//IotEngineMqttServer对应的mqtt客户端

class CIotEngineServer_MqttClient:public CSttMqttClientBase
{
public:
	CIotEngineServer_MqttClient();
	virtual ~CIotEngineServer_MqttClient();

public:
// 	//连接成功后，订阅主题
// 	virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic , CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//特殊主题字段：请求端SN,规约引擎服务ID
	CString m_strSrcID;
	CString m_strCurProtocolSrvID;
};