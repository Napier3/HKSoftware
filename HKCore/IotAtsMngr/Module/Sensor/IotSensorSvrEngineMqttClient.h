#pragma once

#include "../EngineServer/MqttClientToPxEngine.h"

//IotSensorSvrEngine��Ӧ��mqtt�ͻ���

class CIotSensorSvrEngineMqttClient:public CMqttClientToPxEngine
{
public:
	CIotSensorSvrEngineMqttClient();
	virtual ~CIotSensorSvrEngineMqttClient();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	virtual long Send(CExBaseObject *pCmdBase){return 0;}

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//���������ֶΣ�����������SN,������SN
	CString m_strSrcTestAppID;
	CString m_strSensorID;
};