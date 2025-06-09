#pragma once
#include "..\EngineServer\SttMqttClientBase.h"

//用于测试仪通信的Mqtt客户端基类，接收和发送物联协议命令

class CIotVmX_MqttClientBase:public CSttMqttClientBase
{
public:
	CIotVmX_MqttClientBase();
	virtual ~CIotVmX_MqttClientBase();

	//通信接口
public:
	virtual long Send(CExBaseObject *pCmdBase);

	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:

};