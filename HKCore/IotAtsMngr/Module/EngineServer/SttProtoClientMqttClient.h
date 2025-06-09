#pragma once
#include "SttMqttClientBase.h"

//IotEngineProtocolClient��Ӧ��mqtt�ͻ���

class CSttProtoClientMqttClient:public CSttMqttClientBase
{
public:
	CSttProtoClientMqttClient();
	virtual ~CSttProtoClientMqttClient();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual CString GenerateTopic(CSttIotCmd *pIotCmd);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

public:
	//���������ֶΣ������SN,DeviceID
	CString m_strSrcID;
	CString m_strDeviceID;

	void InitTopicSrcInfo(const CString &strFirst,const CString &strSecond);
};