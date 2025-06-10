#pragma once

#include "../Engine/SttClientTestEngine.h"

class CSttLiveUpdateEngine : public CSttClientTestEngine
{
public:
	CSttLiveUpdateEngine();
	virtual ~CSttLiveUpdateEngine();
	
public:
	virtual void OnSocketClose(CSttSocketDataBase *pSocket);
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);
};
