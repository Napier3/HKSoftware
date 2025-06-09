#pragma once
#include "IotVmX_MqttClientBase.h"

class CIotVmProtoToXImp_MqttClient : public CIotVmX_MqttClientBase
{
public:
	CIotVmProtoToXImp_MqttClient();
	virtual ~CIotVmProtoToXImp_MqttClient();

	//通信接口
public:
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	virtual long Send(CExBaseObject *pCmdBase);
	
	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:

};