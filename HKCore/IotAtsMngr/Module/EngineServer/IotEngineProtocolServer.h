#pragma once

#include "MqttEngineBase_Stt.h"
#include "IotEngineProtoSvrImpInterface.h"
#include "..\ProtocolBase\PxProtocolBase.h"

/**********************************
CIotEngineProtocolServerģ�飺�ο�visioģ��ͼ
1��Mqtt�ͻ��ˣ�
2������RunProcedure\CloseDevice�����⣻
��Դ��������ԣ�
3���յ�RunProcedure�������ͨ��IotEngineToSensorģ�����յ���RTDeviceCtrlģ���RunProcedure�ӿڣ�
RunProcedure���̽�����ͨ��IotEngineToSensorģ�飬���յ���CIotEngineProtocolServerģ���OnPrcdrFinished�ӿڷ��ع����¼����
��Ա��豸TTU���ԣ�
3���յ�RunProcedure�������ͨ��CIotEngineToEdgeV4|V5ģ�����յ���CIotEdgeProtoServerV4|V5ģ���RunProcedure�ӿڣ�
RunProcedure���̽�����ͨ��CIotEngineToEdgeV4|V5ģ�飬���յ���CIotEngineProtocolServerģ���OnPrcdrFinished�ӿڷ��ع����¼����
**********************************/

class CIotEngineServer_Mqtt;

class CIotEngineProtocolServer:public CMqttEngineBase_Stt, public CPxProtocolBase
{
public:
	CIotEngineProtocolServer();
	virtual ~CIotEngineProtocolServer();

public:
	//�����¼������ӿ�
	virtual void OnClose(char *pszErr);
	//��ʼ��Mqtt�ͻ��˼���������
	BOOL Init(const char *pszIP,long nPort, const char *pszDeviceSN);
	//�յ���Ϣ����ӿ�
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	virtual long Process_Cmd_Iot(CSttIotCmd &oIotCmd);
	virtual long Process_Cmd_Iot_PkgParse(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_PkgProduce(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_RunProcedure(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_GetDataset(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_ConfigDevice(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_CloseDevice(CSttIotCmd &oIotCmd);

	//Э��ת��ģ����̽����¼�����
	virtual long OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
	virtual void OnDeviceClosed(long nDeviceIndex);

	//���¶�������:��Ҫ���IotEngine�����󣬹�Լ�������֪����ͬһ��װ�������յ�CreateDevice���⣬
	//��Ҫȡ������֮ǰ�����⣬���¶����µ�����
	void ReSubcribeMqttTopic();

	//����Э��ת��ģ���Э�����ģ��
	BOOL CreateProtocol(CSttIotCmd &oIotCmd);
	void SetIotEngineMqttServer(CIotEngineServer_Mqtt *pIotEngineMqttServer){m_pIotEngineMqttServer=pIotEngineMqttServer;}
private:
	//Э��ת���ӿ�ָ��
	CIotEngineProtoSvrImpInterface *m_pEngineProtoSvrImpInterface;
	//CIotEngineMqttServerָ��
	CIotEngineServer_Mqtt *m_pIotEngineMqttServer;
};