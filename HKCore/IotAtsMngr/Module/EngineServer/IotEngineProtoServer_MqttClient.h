#pragma once

#include "SttMqttClientBase.h"

//IotEngineProtocolServer��Ӧ��mqtt�ͻ���

class CIotEngineProtoServer_MqttClient:public CSttMqttClientBase
{
public:
	CIotEngineProtoServer_MqttClient();
	virtual ~CIotEngineProtoServer_MqttClient();

public:
// 	//���ӳɹ��󣬶�������
// 	virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

};