#pragma once

#include "SttClientTestEngine.h"

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

class CSttNativeClientTestEngine : public CSttClientTestEngine
{
public:
	CSttNativeClientTestEngine();
	virtual ~CSttNativeClientTestEngine();
	
public:
    virtual BOOL OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet);

    virtual long Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
    virtual long Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    long Process_Debug_GetSocketConnect(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);

	//只有具有单机测试权限的测试端定时发送心跳
	virtual void OnSendHeartbeatTimer();

public:
	void SetExternEngineRef(CSttTestEngineBase *pExternEngineRef)	{	m_pExternEngineRef = pExternEngineRef;	}

protected:
	CSttTestEngineBase *m_pExternEngineRef;

};
