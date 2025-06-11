#pragma once

#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineDeviceBase.h"

class CSttPxPotoEngineBase : public  CIotPxEngineDeviceBase
{
public:
	CSttPxPotoEngineBase();
	virtual ~CSttPxPotoEngineBase();

protected:
	virtual long Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);

};
