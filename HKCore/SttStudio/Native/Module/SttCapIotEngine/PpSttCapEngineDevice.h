#ifndef CPPSTTCAPENGINEDEVICE_H
#define CPPSTTCAPENGINEDEVICE_H
#include "..\..\Engine\PpEngineServerBase\SttPxPotoEngineBase.h"
#include "..\SmartCap\X61850CapBase.h"



class CPpSttCapEngineDevice: public CSttPxPotoEngineBase
{
public:
	CPpSttCapEngineDevice();
	virtual ~CPpSttCapEngineDevice();
	CX61850CapBase *m_pX61850CapBase;


protected:
	virtual long Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);

	virtual long Process_Cmd_IOT_RunProcedure_ReadAin(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);
	virtual long Process_Cmd_IOT_RunProcedure_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);//����ds6U6I
	virtual long Process_Cmd_IOT_RunProcedure_ReadSV1(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);//��SV1���ݼ�
	virtual long Process_Cmd_IOT_RunProcedure_ReadSVErr(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);//���쳣ģ��dsErr���ݼ�
	virtual long Process_Cmd_IOT_RunProcedure_ReadSVDelay(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);//��SV��ʱdsDelay���ݼ�
	virtual long Process_Cmd_IOT_RunProcedure_SetTestFun(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);//���ò�����(�ڱ���ͳ�ƺ;��Ȳ���֮���л�)

	virtual BOOL IsConnectSuccessful();
};


#endif
