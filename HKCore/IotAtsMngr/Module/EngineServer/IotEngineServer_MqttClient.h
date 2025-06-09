#pragma once

#include "SttMqttClientBase.h"

//IotEngineMqttServer��Ӧ��mqtt�ͻ���

class CIotEngineServer_MqttClient:public CSttMqttClientBase
{
public:
	CIotEngineServer_MqttClient();
	virtual ~CIotEngineServer_MqttClient();

public:
// 	//���ӳɹ��󣬶�������
// 	virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic , CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//���������ֶΣ������SN,��Լ�������ID
	CString m_strSrcID;
	CString m_strCurProtocolSrvID;
};