#pragma once

#include "MqttEngineBase_Stt.h"
#include "IotEngineProtocolServer.h"
#include "XCommSvrWnd.h"

/**********************************
CIotEngineServer_Mqtt模块：参考visio模块图
1、Mqtt客户端；
2、订阅CreateDevice主题；
针对传感器测试：
3、收到CreateDevice主题后，创建并初始化IotEngineProtocolServer模块、IotEngineToSensor模块、RTDeviceCtrl模块
针对边设备TTU测试：
3、收到CreateDevice主题后，创建并初始化IotEngineProtocolServer模块、CIotEngineToEdgeV4|V5模块、CIotEdgeProtoServerV4|V5模块
**********************************/
//2021-8-22  lijunqing  CIotEngineMqttServer命名很容易被认为是MQTT的服务端，因此改名为CIotEngineServer_Mqtt
//表示为EngineServer，即规约引擎的服务端，只不过是MQTT模式下的“规约引擎的服务端”，更加容易理解
class CIotEngineServer_Mqtt:public CMqttEngineBase_Stt,public CXCommSvrWndInterface
{//子对象为IotEngineProtocolServer
public:
	CIotEngineServer_Mqtt();
	virtual ~CIotEngineServer_Mqtt();

public:
	//用于发消息创建IotEngineProtocolServer模块
	CXCommSvrWnd *m_pXCommSvrWnd;
	void OnXCommMsg(WPARAM wParam, LPARAM lParam);

public:
	//断链事件触发接口
	virtual void OnClose(char *pszErr);
	//初始化Mqtt客户端及订阅主题
	BOOL Init(const char *pszIP,long nPort);
	//收到消息处理接口
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	virtual long Process_Cmd_Iot(CSttIotCmd &oIotCmd);
	virtual long Process_Cmd_Iot_CreateDevice(CSttIotCmd &oIotCmd);

	//收到CloseDevice主题处理逻辑
	virtual long OnCloseDevice(CIotEngineProtocolServer *pIotEngineProtocolServer);

//初始化mqtt客户端，尽量不要在接收处理函数中，如果必须在处理函数中，也需要在处理函数结尾，通过消息或线程的方式
private:
	BOOL CreateIotEngineProtocolServer(CSttIotCmd &oIotCmd);
	void PostMsg_CreateIotEngineProtoSvr(CSttIotCmd &oIotCmd);
};