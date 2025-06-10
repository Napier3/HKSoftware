#pragma once

#include "PpXIotEngineBase.h"
#include "../../../IotAtsMngr/Module/MqttCmmInterface.h"

class CPpMqttIotDevice : public CPpSttIotDeviceBase, public CMqttMsgProcessInterface
{
//MQTT�¼�����ӿڣ���CMqttMsgInterface�������
//class CMqttMsgProcessInterface
public:
	//�����յ���MQTT�������ƥ�䣬���ƥ��ɹ����򷵻�TRUE�����򷵻�FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT��Ϣ����
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT���ⶩ�Ľӿں�����MQTT Client���ӳɹ��󣬱�����CMqttMsgProcessInterface
	//������ص�����
	virtual BOOL MqttSubscribeTopic();

	//MQTTȡ�����ⶩ�Ľӿں�����MQTT Client�Ͽ����Ӻ󣬱�����CMqttMsgProcessInterface
	//Tȡ��������ص�����
	virtual BOOL MqttUnSubscribeTopic();

	CString m_strBentchSN;  //����̨SN

	void MqttAddToClient();
	void MqttRemoveFromClient();

public:
	CPpMqttIotDevice();
	virtual ~CPpMqttIotDevice();

	//�¼��ӿ�
	virtual void On_SysState_IOT(CSttSysState *pSysState);
	virtual long X_SendIotCmd(CSttIotCmd &oIotCmd);

	virtual BOOL IsConnectIotServerSucc();
	virtual long IsConnectSuccessful();
	virtual BOOL ConnectSttServer();
	virtual void SetSttCmdDataFormat(long nSttCmdForat);
	virtual void DisConnect();
	virtual void DisConnectForClose(BOOL bDelete);  //�Ͽ�����
	virtual void SetDeviceSN(const CString &strDeviceSN);

};

class CPpMqttIotEngine : public CPpXIotEngineBase
{
public:
	CPpMqttIotEngine();
	virtual ~CPpMqttIotEngine(void);

public:
	virtual CPpSttIotDeviceBase* CreateNewDevice();

};
