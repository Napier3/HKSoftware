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
	//���ڸĽ����ڹ�Լģ���У����Ӷ�ʱ������ң�⡣ͬʱ�����ű�����������RTDATA����
	virtual long XOnEngineTimer_RTDATA_ReadAin();
	virtual long XOnEngineTimer_RTDATA_ReturnEvent();
// 	void ReturnSysState2(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);
// 	void ReturnConnectFailed(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);

//���ָ��ִ����ϵ���Ϣ������Ϊ��Э��ִ�ж�������ݼ�����ʽ��һ�£����Ժ�������������ʵ��
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);

	//zhouhj 2024.8.10 ���ظĺ���
	//��ʱֻ����ֻ��1���ͻ������ӹ���,��������̴߳���ʱ,��Ӧ�Ŀͻ����ѱ��ͷŵ���Ӧָ�뻹δ��Ϊ��,���������������
	virtual long ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttSysState &oSysState);

	virtual void AddRetDatasToParas(CSttParas *pSttParas);

	void OnEngineSystemMessage(CSttIotCmd *pIotCmd, BOOL bFromCloseDevice);
};

#endif//!CSttPpEngineDevice_H