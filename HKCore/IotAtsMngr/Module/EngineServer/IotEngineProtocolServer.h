#pragma once

#include "MqttEngineBase_Stt.h"
#include "IotEngineProtoSvrImpInterface.h"
#include "..\ProtocolBase\PxProtocolBase.h"

/**********************************
CIotEngineProtocolServer模块：参考visio模块图
1、Mqtt客户端；
2、订阅RunProcedure\CloseDevice等主题；
针对传感器测试：
3、收到RunProcedure等主题后，通过IotEngineToSensor模块最终调用RTDeviceCtrl模块的RunProcedure接口；
RunProcedure过程结束，通过IotEngineToSensor模块，最终调用CIotEngineProtocolServer模块的OnPrcdrFinished接口返回过程事件结果
针对边设备TTU测试：
3、收到RunProcedure等主题后，通过CIotEngineToEdgeV4|V5模块最终调用CIotEdgeProtoServerV4|V5模块的RunProcedure接口；
RunProcedure过程结束，通过CIotEngineToEdgeV4|V5模块，最终调用CIotEngineProtocolServer模块的OnPrcdrFinished接口返回过程事件结果
**********************************/

class CIotEngineServer_Mqtt;

class CIotEngineProtocolServer:public CMqttEngineBase_Stt, public CPxProtocolBase
{
public:
	CIotEngineProtocolServer();
	virtual ~CIotEngineProtocolServer();

public:
	//断链事件触发接口
	virtual void OnClose(char *pszErr);
	//初始化Mqtt客户端及订阅主题
	BOOL Init(const char *pszIP,long nPort, const char *pszDeviceSN);
	//收到消息处理接口
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	virtual long Process_Cmd_Iot(CSttIotCmd &oIotCmd);
	virtual long Process_Cmd_Iot_PkgParse(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_PkgProduce(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_RunProcedure(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_GetDataset(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_ConfigDevice(CSttIotCmd &oIotCmd);	
	virtual long Process_Cmd_Iot_CloseDevice(CSttIotCmd &oIotCmd);

	//协议转换模块过程结束事件返回
	virtual long OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
	virtual void OnDeviceClosed(long nDeviceIndex);

	//重新订阅主题:主要解决IotEngine断链后，规约引擎服务不知道，同一个装置再试收到CreateDevice主题，
	//需要取消订阅之前的主题，重新订阅新的主题
	void ReSubcribeMqttTopic();

	//创建协议转换模块和协议服务模块
	BOOL CreateProtocol(CSttIotCmd &oIotCmd);
	void SetIotEngineMqttServer(CIotEngineServer_Mqtt *pIotEngineMqttServer){m_pIotEngineMqttServer=pIotEngineMqttServer;}
private:
	//协议转换接口指针
	CIotEngineProtoSvrImpInterface *m_pEngineProtoSvrImpInterface;
	//CIotEngineMqttServer指针
	CIotEngineServer_Mqtt *m_pIotEngineMqttServer;
};