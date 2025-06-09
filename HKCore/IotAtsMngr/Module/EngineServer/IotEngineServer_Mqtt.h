#pragma once

#include "MqttEngineBase_Stt.h"
#include "IotEngineProtocolServer.h"
#include "XCommSvrWnd.h"

/**********************************
CIotEngineServer_Mqttģ�飺�ο�visioģ��ͼ
1��Mqtt�ͻ��ˣ�
2������CreateDevice���⣻
��Դ��������ԣ�
3���յ�CreateDevice����󣬴�������ʼ��IotEngineProtocolServerģ�顢IotEngineToSensorģ�顢RTDeviceCtrlģ��
��Ա��豸TTU���ԣ�
3���յ�CreateDevice����󣬴�������ʼ��IotEngineProtocolServerģ�顢CIotEngineToEdgeV4|V5ģ�顢CIotEdgeProtoServerV4|V5ģ��
**********************************/
//2021-8-22  lijunqing  CIotEngineMqttServer���������ױ���Ϊ��MQTT�ķ���ˣ���˸���ΪCIotEngineServer_Mqtt
//��ʾΪEngineServer������Լ����ķ���ˣ�ֻ������MQTTģʽ�µġ���Լ����ķ���ˡ��������������
class CIotEngineServer_Mqtt:public CMqttEngineBase_Stt,public CXCommSvrWndInterface
{//�Ӷ���ΪIotEngineProtocolServer
public:
	CIotEngineServer_Mqtt();
	virtual ~CIotEngineServer_Mqtt();

public:
	//���ڷ���Ϣ����IotEngineProtocolServerģ��
	CXCommSvrWnd *m_pXCommSvrWnd;
	void OnXCommMsg(WPARAM wParam, LPARAM lParam);

public:
	//�����¼������ӿ�
	virtual void OnClose(char *pszErr);
	//��ʼ��Mqtt�ͻ��˼���������
	BOOL Init(const char *pszIP,long nPort);
	//�յ���Ϣ����ӿ�
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	virtual long Process_Cmd_Iot(CSttIotCmd &oIotCmd);
	virtual long Process_Cmd_Iot_CreateDevice(CSttIotCmd &oIotCmd);

	//�յ�CloseDevice���⴦���߼�
	virtual long OnCloseDevice(CIotEngineProtocolServer *pIotEngineProtocolServer);

//��ʼ��mqtt�ͻ��ˣ�������Ҫ�ڽ��մ������У���������ڴ������У�Ҳ��Ҫ�ڴ�������β��ͨ����Ϣ���̵߳ķ�ʽ
private:
	BOOL CreateIotEngineProtocolServer(CSttIotCmd &oIotCmd);
	void PostMsg_CreateIotEngineProtoSvr(CSttIotCmd &oIotCmd);
};