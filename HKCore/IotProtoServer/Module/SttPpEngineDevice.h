#ifndef CSttPpEngineDevice_H
#define CSttPpEngineDevice_H

#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineDeviceBase.h"
#include "../../../Protocol/Module/PxiEngine/PxiDevice.h"

class CSttPpEngineDevice : public CIotPxEngineDeviceBase
{
public:
	CSttPpEngineDevice();
	virtual ~CSttPpEngineDevice();

	CPxiDevice *m_pPxiDevice;
    CPxiDevice *m_pPxiDeviceForDel;

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

	//shaolei 2023-9-11
	//后期改进：在规约模板中，增加定时器，读遥测。同时新增脚本函数，发送RTDATA报文
	virtual long XOnEngineTimer_RTDATA_ReadAin();
	virtual long XOnEngineTimer_RTDATA_ReturnEvent();
// 	void ReturnSysState2(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);
// 	void ReturnConnectFailed(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);

//相关指令执行完毕的消息处理，因为各协议执行对象的数据集管理方式不一致，所以函数在派生类中实现
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);

	//zhouhj 2024.8.10 重载改函数
	//暂时只考虑只有1个客户端连接过来,待解决多线程处理时,对应的客户端已被释放但对应指针还未置为空,导致软件崩溃问题
	virtual long ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttSysState &oSysState);

	virtual void AddRetDatasToParas(CSttParas *pSttParas);

	void OnEngineSystemMessage(CSttIotCmd *pIotCmd, BOOL bFromCloseDevice);
};

#endif//!CSttPpEngineDevice_H