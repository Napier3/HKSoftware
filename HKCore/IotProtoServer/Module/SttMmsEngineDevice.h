#ifndef CSttMmsEngineDevice_H
#define CSttMmsEngineDevice_H

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS

#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineDeviceBase.h"
#include "../../../61850/Module/PoEngine/PoMmsDevice.h"

class CSttMmsEngineDevice : public CIotPxEngineDeviceBase
{
public:
	CSttMmsEngineDevice();
	virtual ~CSttMmsEngineDevice();

	CPoMmsDevice *m_pMmsDevice;

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

//���ָ��ִ����ϵ���Ϣ������Ϊ��Э��ִ�ж�������ݼ�����ʽ��һ�£����Ժ�������������ʵ��
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);
	virtual void AddDvmEnumToParas(CSttParas *pSttParas);
	virtual void AddRetDatasToParas(CSttParas *pSttParas);	//2023-3-4  lijunqing  ��ʼ��ͨ�Ź��̽������صĲ�������
	virtual void AddSoeReportToParas(CSttParas *pSttParas, unsigned long wPara,unsigned long lPara);	//2023-3-5  lijunqing  ��ӱ������ݵ�

	void OnEngineSystemMessage(CSttIotCmd *pIotCmd, BOOL bFromCloseDevice);
};
#endif//#ifdef IOT_PROTOCOL_SERVER_HAS_MMS

#endif//!CSttMmsEngineDevice_H