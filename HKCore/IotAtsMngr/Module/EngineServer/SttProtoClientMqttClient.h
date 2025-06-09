#pragma once
#include "SttMqttClientBase.h"

//IotEngineProtocolClient对应的mqtt客户端

class CSttProtoClientMqttClient:public CSttMqttClientBase
{
public:
	CSttProtoClientMqttClient();
	virtual ~CSttProtoClientMqttClient();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual CString GenerateTopic(CSttIotCmd *pIotCmd);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

public:
	//特殊主题字段：请求端SN,DeviceID
	CString m_strSrcID;
	CString m_strDeviceID;

	void InitTopicSrcInfo(const CString &strFirst,const CString &strSecond);
};