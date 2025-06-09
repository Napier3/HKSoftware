#pragma once

#include "SttTestEngineBase.h"
#include "SttTestEngineServerData.h"
#include "../SttSocket/SttServerSocketDataBase.h"

class CSttTestEngineServerBase : public CSttTestEngineBase, public CSttTestEngineServerData
{
public:
	CSttTestEngineServerBase();
	virtual ~CSttTestEngineServerBase();

    virtual void InitSttServerEngine(const char *pszIP, int nTestPort,int nReplayPort = 0) = 0;
	virtual void ExitSttServerEngine() = 0;

public:
	virtual void OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket = TRUE);

	virtual long Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
};

//extern CSttServerTestCtrlCntr  *g_pTestCtrlEngine;
