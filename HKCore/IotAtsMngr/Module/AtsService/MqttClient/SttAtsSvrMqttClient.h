#pragma once

#include "SttMqttClientBase.h"

//IotEngineMqttServer��Ӧ��mqtt�ͻ���

class CSttAtsSvrMqttClient:public CSttMqttClientBase
{
public:
	CSttAtsSvrMqttClient();
	virtual ~CSttAtsSvrMqttClient();

public:
	//���ӳɹ��󣬶�������
	virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic,long &nCmdType, char **ppszCmdID, char **ppszRetType);
	
public:
	//���������ֶΣ������SN,��Լ�������ID
	CString m_strSrcID;
	CString m_strCurProtocolSrvID;
};