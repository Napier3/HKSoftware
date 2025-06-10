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
//	virtual void CloseSocket(CSttSocketDataBase *pSocket);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);

public:
	virtual long OnTestMsg(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen);

	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	virtual long Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Adjust(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_IOT(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);
	virtual long Process_SysState_State(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_SearchPointReport(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Meas(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	virtual long Process_Cmd_Comtrade(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_RequestData(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataStartAck(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);

//2020-10-25  lijunqing
public:
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType);

    //2022-2-12  lijunqing
    virtual void AddPkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
	virtual void RemovePkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
};
