#pragma once

#include "SttTestEngineBase.h"
#include "../TestClient/SttMacroTestInterface.h"

#ifdef VM_MACROTEST_IN_LOCAL
#include "SttTestEngineRemoteClientData.h"
#else
#include "SttTestEngineClientData.h"
#endif

#ifdef VM_MACROTEST_IN_LOCAL
class CSttVmMacroTest : public CSttTestEngineRemoteClientData
#else
class CSttVmMacroTest : public CSttTestEngineClientData
#endif
{
public:
	CSttVmMacroTest();
	virtual ~CSttVmMacroTest();

	void SetMsgWnd(CMacroTestEventInterface *pMacroTestEventRcv)	{	m_pMacroTestEventRcv = pMacroTestEventRcv;	}

protected:
	CMacroTestEventInterface *m_pMacroTestEventRcv; //测试事件接收对象

//connect device
public:
	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
	
public:
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	long Process_SysState_Login(CSttSysState &oSysState);
	long Process_SysState_Logout(CSttSysState &oSysState);
	long Process_SysState_Request(CSttSysState &oSysState);
	long Process_SysState_Query(CSttSysState &oSysState);
	long Process_SysState_Bind(CSttSysState &oSysState);
	long Process_SysState_UnRegister(CSttSysState &oSysState);
	long Process_SysState_Authority(CSttSysState &oSysState);
	
};
