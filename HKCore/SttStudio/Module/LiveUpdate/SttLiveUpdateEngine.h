#pragma once

#include "../Engine/SttClientTestEngine.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"

class CSttLiveUpdateEngine : public CSttClientTestEngine
{
public:
	CSttLiveUpdateEngine();
	virtual ~CSttLiveUpdateEngine();
	
public:
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);
};
