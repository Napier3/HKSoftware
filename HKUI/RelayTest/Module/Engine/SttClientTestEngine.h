#pragma once

#include "SttTestEngineBase.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "SttTestEngineClientData.h"

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


class CSttClientTestEngine : public CSttTestEngineBase, public CSttTestEngineClientData
{
public:
	CSttClientTestEngine();
	virtual ~CSttClientTestEngine();


	virtual CSttCmdOverTimeMsgRcv *GetCmdOverTimeMsgRcv(){	return this;	};
	
	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
//	virtual void CloseSocket(CSttXcmdChInterface *pSocket);
	virtual void OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket = TRUE);

public:
	virtual long OnTestMsg(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen);

	virtual long Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd);

	virtual long Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Adjust(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_IOT(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);
	virtual long Process_SysState_State(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_SearchPointReport(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Packet(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Event(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Update(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Log(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_RtData(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Meas(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Ats_Stop(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

	virtual long Process_Cmd_Comtrade(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_RequestData(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataStartAck(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);

//2020-10-25  lijunqing
public:
	virtual long Process_SysState(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType);

    //2022-2-12  lijunqing
    virtual void AddPkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
	virtual void RemovePkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
	virtual void PrepareFreeClientEngine();
};
