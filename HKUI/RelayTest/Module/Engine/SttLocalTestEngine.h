#pragma once

#include "SttClientTestEngine.h"

class CSttLocalTestEngine : public CSttClientTestEngine
{
public:
	CSttLocalTestEngine();
	virtual ~CSttLocalTestEngine();


//connect device
public:
// 	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
	
public:
// 	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
// 	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
// 	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
// 
// 	long Process_SysState_Login(CSttSysState &oSysState);
// 	long Process_SysState_Logout(CSttSysState &oSysState);
// 	long Process_SysState_Request(CSttSysState &oSysState);
// 	long Process_SysState_Query(CSttSysState &oSysState);
// 	long Process_SysState_Bind(CSttSysState &oSysState);
// 	long Process_SysState_UnRegister(CSttSysState &oSysState);
// 	long Process_SysState_Authority(CSttSysState &oSysState);
	
//	BOOL OnUpdate_Users(CSttSysState &oSysState,BOOL &bMatch);

	//要考虑：系统忙、无权限等应答信息
public:
	void OnLogout();

public:
	
};
