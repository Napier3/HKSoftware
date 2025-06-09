#pragma once

#include "IotPxEngineInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "IotPxEngineDeviceWnd.h"
#include "../../../Module/BaseClass/TxArray.h"
#include "../../../Module/BaseClass/TxCycleArray.h"

#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

class CIotPxEngineDeviceWnd;

//m_strID����¼DeviceSN
class CIotPxEngineDeviceBase : public CExBaseList, public CPxiDeviceCommCmdMessage, public CThreadProgressInterface
{
public:
	CIotPxEngineDeviceBase();
	virtual ~CIotPxEngineDeviceBase();

	//ʹ�õ�ͨ��ͨ��������SttSocket��MqttClient��
	//�˴�ֱ�ӷ����Ѿ����ڵĶ������������ӣ��򸲸���Device֮ǰ������
	//��ʱ�����Ƕ����Ӳ���ͳһ�豸�����
	//CIotPxCommChannelInterface *m_pPxCommChannel;

	CDvmDevice *m_pDvmDevice;
	CIotPxEngineDeviceWnd *m_pIotPxEngineDeviceWnd;

	//��ǰִ�еĹ���ID����ص����ݼ�ID
	CString m_strProcedureID;
	CString m_strDatasetID;

	CSttIotCmdDriver m_oSttIotCmdDriver;
	TxCycleArray<CSttIotCmdDriver> m_oArrSttIotCmdDriver;  //�����ͨ�������б����ڶ����Ӷ˵Ĵ���
	TxArray<CIotPxCommChannelInterface> m_oArrCommCh;  //ͨ��ͨ���б����ڶ����Ӷ˵Ĵ���

	//CPxiDeviceCommCmdMessage
public:
	virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam);
	virtual void OnSysMessage(WPARAM wParam, LPARAM lParam);
	virtual void OnEventMessage(WPARAM wParam, LPARAM lParam);

	//2020-11-24  lijunqing LINUX  post msg to ats
	virtual void OnEngineDataDeleted(const CString &strDeviceID);
	virtual void OnReportMessage(WPARAM wParam, LPARAM lParam);

	//shaolei 2023-9-11
	virtual long XOnEngineTimer_RTDATA();
	virtual long XOnEngineTimer_RTDATA_ReadAin();
	virtual long XOnEngineTimer_RTDATA_ReturnEvent();

public:
	unsigned long GetMsgRcvWnd();
	void AddCommCh(CIotPxCommChannelInterface *pCommCh)
	{
		m_oArrCommCh.AddObject(pCommCh);
	}

public:
	virtual long Process_Cmd_IOT(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual BOOL IsConnectSuccessful() = 0;
	virtual BOOL CloseByPxCommChannel(CIotPxCommChannelInterface *pPxCommChn);

protected:
	virtual long Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	virtual long Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);

public:
	//virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, CSttCmdData *pRetData=NULL);
	virtual long ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttCmdBase *pSttCmd, long nCmdExecStatus, CDvmDataset *pDataset=NULL
		,const CString &strAddDataID = _T(""),const CString &strAddDataValue = _T(""));
	virtual long ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttSysState &oSysState);

	void InitSysStateByCurrCmd(CSttSysState &oSysState);

	virtual void ReturnSysState2(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);
	virtual void ReturnConnectFailed(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn);
	
	virtual CDvmDataset* FindDvmDataset();
	virtual long IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);

//���ָ��ִ����ϵ���Ϣ������Ϊ��Э��ִ�ж�������ݼ�����ʽ��һ�£����Ժ�������������ʵ��
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);
	virtual unsigned long OnEngineEventMessage(unsigned long wPara,unsigned long lPara);
	virtual unsigned long OnMmsReportMessage(unsigned long wPara,unsigned long lPara);

	virtual void AddDvmEnumToParas(CSttParas *pSttParas);

	//2023-3-4  lijunqing  ��ʼ��ͨ�Ź��̽������صĲ�������
	virtual void AddRetDatasToParas(CSttParas *pSttParas);

	//2023-3-5  lijunqing  ��ӱ������ݵ�
	virtual void AddSoeReportToParas(CSttParas *pSttParas, unsigned long wPara,unsigned long lPara);

	//////////////////////////////////////////////////////////////////////////
	//CThreadProgressInterface
public:
	virtual void SetTitle(const CString &strTitle);
	virtual void SetMaxRange(long nMaxRange);
	virtual void ResetProcess();
	virtual void StepIt();
	virtual void ShowMsg(const CString &strMsg);
	virtual void StartTimer(long nTimerLong);

	virtual void Finish(DWORD dwParam=0);
	virtual void StepPos(long nPos);
	virtual void Exit();

};

