#pragma once
#include "..\EngineServer\SttMqttClientBase.h"

//���ڲ�����ͨ�ŵ�Mqtt�ͻ��˻��࣬���պͷ�������Э������

class CIotVmX_MqttClientBase:public CSttMqttClientBase
{
public:
	CIotVmX_MqttClientBase();
	virtual ~CIotVmX_MqttClientBase();

	//ͨ�Žӿ�
public:
	virtual long Send(CExBaseObject *pCmdBase);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:

};