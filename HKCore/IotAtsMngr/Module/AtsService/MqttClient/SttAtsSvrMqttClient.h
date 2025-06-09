#pragma once

#include "SttMqttClientBase.h"

//IotEngineMqttServer对应的mqtt客户端

class CSttAtsSvrMqttClient:public CSttMqttClientBase
{
public:
	CSttAtsSvrMqttClient();
	virtual ~CSttAtsSvrMqttClient();

public:
	//连接成功后，订阅主题
	virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic,long &nCmdType, char **ppszCmdID, char **ppszRetType);
	
public:
	//特殊主题字段：请求端SN,规约引擎服务ID
	CString m_strSrcID;
	CString m_strCurProtocolSrvID;
};