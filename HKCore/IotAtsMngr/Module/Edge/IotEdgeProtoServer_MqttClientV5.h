#pragma once

#include "EdgeMqttClientBase.h"

class CIotEdgeProtoServer_MqttClientV5:public CEdgeMqttClientBase
{
public:
	CIotEdgeProtoServer_MqttClientV5();
	virtual ~CIotEdgeProtoServer_MqttClientV5();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);

public:
};