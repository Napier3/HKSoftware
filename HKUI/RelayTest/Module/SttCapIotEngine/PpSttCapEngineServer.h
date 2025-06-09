#ifndef CPPSTTCAPENGINESERVER_H
#define CPPSTTCAPENGINESERVER_H
#include "..\..\IotAtsMngr\Module\PxEngineServer\IotPxEngineFactoryBase.h"

class CPpSttCapEngineServer: public CIotPxEngineFactoryBase
{
public:
	CPpSttCapEngineServer();
	virtual ~CPpSttCapEngineServer();


	//////////////////////////////////////////////////////////////////////////
	//CIotPxEngineServerInterface
public:
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);


	virtual void CheckHeartbeatOverTime(){};
};
#endif