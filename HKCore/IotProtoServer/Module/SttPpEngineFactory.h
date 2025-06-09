#pragma once

#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineFactoryBase.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"

class CSttPpEngineFactory : public CIotPxEngineFactoryBase
{
public:
	CSttPpEngineFactory();
	virtual ~CSttPpEngineFactory();

//////////////////////////////////////////////////////////////////////////
//CIotPxEngineServerInterface
public:
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);

	virtual void CheckHeartbeatOverTime(){};
};


