#pragma once

#include "../SttTestEngineServerBase.h"
#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineFactoryBase.h"
/*
STT协议的通信引擎服务基类，此基类初始化时，创建CSttPpServerSocket
接受连接时，创建CSttPpServerClientSocket，实现IOT个性化的处理

相比于测试仪的Engine：
    ----SttPpEngineServer只是作为管理方，处理CreateDevice和CloseDevice指令，创建对象和关闭对象
	----CSttPpServerClientSocket做报文的基础处理
	----CIotPxEngineDeviceBase实现具体的协议实现，是真正的协议对象
	----CSttPpServerClientSocket与CIotPxEngineDeviceBase是一对，相互引用
*/

class CSttPpEngineServer : public  CSttTestEngineServerBase//, public CIotPxEngineFactoryBase
{
private:
	CSttPpEngineServer();
	virtual ~CSttPpEngineServer();

	static CSttPpEngineServer *g_pSttPpEngineServer;
	static long g_nSttPpEngineServerRef;

public:
	static CSttPpEngineServer* Create();
	static CSttPpEngineServer* Create(char *pszIP, int nPort);
	static void Release();

public:
    virtual void InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort = 0);
	virtual void ExitSttServerEngine();
	virtual void OnTimer();

	virtual void CheckHeartbeatOverTime(){};
};

