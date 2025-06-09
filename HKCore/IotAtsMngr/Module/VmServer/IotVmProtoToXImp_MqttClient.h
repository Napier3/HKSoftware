#pragma once
#include "IotVmX_MqttClientBase.h"

class CIotVmProtoToXImp_MqttClient : public CIotVmX_MqttClientBase
{
public:
	CIotVmProtoToXImp_MqttClient();
	virtual ~CIotVmProtoToXImp_MqttClient();

	//ͨ�Žӿ�
public:
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	virtual long Send(CExBaseObject *pCmdBase);
	
	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:

};