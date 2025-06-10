#pragma once

#include "../Engine/VC/SttTestServerEngine.h"

class CSttLiveUpdateServerEngine : protected CSttTestServerBase
{
public:
	static CSttLiveUpdateServerEngine* Create(char *pszIP, int nPort);
	static void Release();

private:
	CSttLiveUpdateServerEngine();
	virtual ~CSttLiveUpdateServerEngine();
	
public:
	void SendRetState(CSttSocketDataBase *pClientSocket, BOOL bRet);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket);
	virtual long Process_Cmd_System_LiveUpdate(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
};
