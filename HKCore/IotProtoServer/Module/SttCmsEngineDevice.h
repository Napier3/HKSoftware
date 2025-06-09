#ifndef CSttCmsEngineDevice_H
#define CSttCmsEngineDevice_H

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineDeviceBase.h"
#include "../../../61850/Module/PoCmsEngine/PoCmsDevice.h"

class CSttCmsEngineDevice : public CIotPxEngineDeviceBase
{
public:
	CSttCmsEngineDevice();
	virtual ~CSttCmsEngineDevice();

	CPoCmsDevice *m_pCmsDevice;

public:
	virtual long Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual BOOL IsConnectSuccessful();

protected:
	virtual long Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);

	virtual long IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual CDvmDataset* FindDvmDataset();

	//void ReturnSysState2(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);
	//void ReturnConnectFailed(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);

//相关指令执行完毕的消息处理，因为各协议执行对象的数据集管理方式不一致，所以函数在派生类中实现
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);

	void OnEngineSystemMessage(CSttIotCmd *pIotCmd, BOOL bFromCloseDevice);
};

#endif  //#ifdef IOT_PROTOCOL_SERVER_HAS_CMS

#endif//!CSttCmsEngineDevice_H