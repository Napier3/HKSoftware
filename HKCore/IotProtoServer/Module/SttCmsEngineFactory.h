#pragma once

#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineFactoryBase.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"

class CSttCmsEngineFactory : public CIotPxEngineFactoryBase
{
public:
	CSttCmsEngineFactory();
	virtual ~CSttCmsEngineFactory();

//////////////////////////////////////////////////////////////////////////
//CIotPxEngineServerInterface
public:
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);

	virtual void CheckHeartbeatOverTime(){};
};


