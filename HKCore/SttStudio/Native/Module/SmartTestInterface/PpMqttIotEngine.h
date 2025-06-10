#pragma once

#include "PpXIotEngineBase.h"
#include "../../../IotAtsMngr/Module/MqttCmmInterface.h"

class CPpMqttIotDevice : public CPpSttIotDeviceBase, public CMqttMsgProcessInterface
{
//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface
public:
	//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT消息处理
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
	//订阅相关的主题
	virtual BOOL MqttSubscribeTopic();

	//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
	//T取消订阅相关的主题
	virtual BOOL MqttUnSubscribeTopic();

	CString m_strBentchSN;  //测试台SN

	void MqttAddToClient();
	void MqttRemoveFromClient();

public:
	CPpMqttIotDevice();
	virtual ~CPpMqttIotDevice();

	//事件接口
	virtual void On_SysState_IOT(CSttSysState *pSysState);
	virtual long X_SendIotCmd(CSttIotCmd &oIotCmd);

	virtual BOOL IsConnectIotServerSucc();
	virtual long IsConnectSuccessful();
	virtual BOOL ConnectSttServer();
	virtual void SetSttCmdDataFormat(long nSttCmdForat);
	virtual void DisConnect();
	virtual void DisConnectForClose(BOOL bDelete);  //断开连接
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
