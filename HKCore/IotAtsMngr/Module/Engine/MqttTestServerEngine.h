#pragma once

#include "../../../SttStudio/Module/Engine/SttTestEngineServerBase.h"
#include "../SttMqttClientTool.h"
#include "../SttEngineMqttCmdExec.h"

class CMqttTestServerEngine : public  CSttTestEngineServerBase, public CSttMqttMsgInterface
{
public:
	static CMqttTestServerEngine* Create(char *pszIP, int nPort);
	static void Release();

public:
	static long m_nSttTestServerEngineRef;
	static CMqttTestServerEngine *g_pSttTestServerEngine;

protected:
	CMqttTestServerEngine();
	virtual ~CMqttTestServerEngine();

	CExBaseList m_oEngineMqttCmdExecMngr;
	CSttEngineMqttCmdExec *FindMqttCmdExecByRefSocket(CSttSocketDataBase *pRefSocket);
	void DeleteMqttCmdExecByRefSocket(CSttSocketDataBase *pRefSocket);

	//mqtt接口
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);
	BOOL ConnectMqttServer();
public:
	virtual void InitSttServerEngine(const char *pszIP, int nPort);
	virtual void ExitSttServerEngine();

	virtual void OnSocketClose(CSttSocketDataBase *pSocket);

	//只检测具有单机测试权限的测试端心跳超时
	virtual void CheckHeartbeatOverTime(){};

protected:
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);

	virtual CSttTestClientUser* User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
};