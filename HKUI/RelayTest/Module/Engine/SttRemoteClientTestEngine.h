#pragma once

#include "SttTestEngineBase.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "SttTestEngineRemoteClientData.h"

//说明1：
//CSttClientTestEngine，作为一台测试仪的测试控制对象，如果是多台测试仪，需要创建多个CSttClientTestEngine对象
//所以CSttClientTestEngine不设计为全局唯一对象
//后续增加

//说明2：
//测试端，对于测试的过程控制，设计为多状态机模式：
//0=没开始测试；
//1=发送了测试命令，还没返回：【界面的“开始”“停止”按钮都不能按】
//2=命令返回，开始测试过程：【界面的“开始”变灰，“停止”按钮使能】
//3=测试结束：【界面的“开始”使能，“停止”按钮变灰】
//4=测试异常：【界面的“开始”使能，“停止”按钮变灰】
//0=关闭设备（CloseDevice），返回初始状态

class CSttRemoteClientTestEngine : public CSttTestEngineBase, public CSttTestEngineRemoteClientData
{
public:
	CSttRemoteClientTestEngine();
	virtual ~CSttRemoteClientTestEngine();

	virtual CSttCmdOverTimeMsgRcv *GetCmdOverTimeMsgRcv(){	return this;	};

	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
	virtual void OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket = TRUE);
	
public:
	virtual long Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd);

	virtual long Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Remote(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

	//要考虑：系统忙、无权限等应答信息

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);

	//shaolei   20210527
	virtual long Process_SysState_Event(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
public:

};
