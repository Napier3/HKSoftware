#pragma once

#include "../../EngineServer/SttMqttClientBase.h"

/************************************************************************/
/*
�Զ����Կ��Ʒ����Ӧ��mqtt�ͻ���
ʵ�֣�
	�����Զ����Կ���ָ�CreateTest��StartTest��FinishInputData��
	�����Զ�����ϵͳ״ָ̬��
*/
/*
��Ӧ���Զ����Է�����ÿͻ���Ϊ��CSttSartTestClientMqttClient��Ŀǰ�Զ����Կͻ���Ϊ��վ�ˣ���ʱ������
*/
/************************************************************************/

class CSttProtoAtsServiceMqttClient:public CSttMqttClientBase
{
public:
	CSttProtoAtsServiceMqttClient(const CString &strMqttTopic);
	CSttProtoAtsServiceMqttClient();
	virtual ~CSttProtoAtsServiceMqttClient();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);

	//�����뱨�����ͻ�ת�ӿ�
	//shaolei 20210805
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//���ĵ����⣬CSttProtoAtsServiceMqttClient������ģʽ�����Է���ģʽ�Ͳ���̨ģʽ
	//���Է���ģʽ��TestServiceֻ���ܴ�������ָ��������Կ�����CAtsSvrTestFlow
	//����̨ģʽ��CAtsTestBench��CAtsSvrTestFlow���ܲ��Կ���ָ�ִ���Զ�����
	CString m_strAtsMqttTopic;

	CString m_strSN;  //����̨SN���߲��Է����SN�����󴴽���ʱ������
	//void Init(const CString &strIP,long nPort,const CString &strClientID);
};

/************************************************************************/
/*
�Զ�����ģ������Ӧ��mqtt�ͻ���
ʵ�֣�
	�����Զ�����ģ�������ص�ָ�UploadTemplate��ImportTaskInfo��ImportSampleInfo��ExportReport��
*/
/*
��Ӧ���Զ����Է�����ÿͻ���Ϊ��CSttSartTestClientMqttClient��Ŀǰ�Զ����Կͻ���Ϊ��վ�ˣ���ʱ������
*/
/************************************************************************/

class CSttProtoAtsService_Template_MqttClient:public CSttProtoAtsServiceMqttClient
{
public:
	CSttProtoAtsService_Template_MqttClient(const CString &strMqttTopic);
	CSttProtoAtsService_Template_MqttClient();
	virtual ~CSttProtoAtsService_Template_MqttClient();

public:
	//���ӳɹ��󣬶�������
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
};