#pragma once

#include "../EngineServer/MqttClientToPxEngine.h"

//IotSensorSvrEngine对应的mqtt客户端

class CIotSensorSvrEngineMqttClient:public CMqttClientToPxEngine
{
public:
	CIotSensorSvrEngineMqttClient();
	virtual ~CIotSensorSvrEngineMqttClient();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	virtual long Send(CExBaseObject *pCmdBase){return 0;}

	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//特殊主题字段：物联测试仪SN,传感器SN
	CString m_strSrcTestAppID;
	CString m_strSensorID;
};