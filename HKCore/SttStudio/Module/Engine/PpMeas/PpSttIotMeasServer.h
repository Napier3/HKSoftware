#pragma once

#include "../PpEngineServerBase/SttPpEngineServer.h"

class CPpSttIotMeasServer : public CIotPxEngineFactoryBase
{
public:
	CPpSttIotMeasServer();
	virtual ~CPpSttIotMeasServer();


//////////////////////////////////////////////////////////////////////////
//CIotPxEngineServerInterface
public:
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);


	virtual void CheckHeartbeatOverTime(){};
};


