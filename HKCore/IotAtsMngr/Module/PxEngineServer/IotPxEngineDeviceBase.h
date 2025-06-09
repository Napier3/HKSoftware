#pragma once

#include "IotPxEngineInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "IotPxEngineDeviceWnd.h"
#include "../../../Module/BaseClass/TxArray.h"
#include "../../../Module/BaseClass/TxCycleArray.h"

#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

class CIotPxEngineDeviceWnd;

//m_strID，记录DeviceSN
class CIotPxEngineDeviceBase : public CExBaseList, public CPxiDeviceCommCmdMessage, public CThreadProgressInterface
{
public:
	CIotPxEngineDeviceBase();
	virtual ~CIotPxEngineDeviceBase();

	//使用的通信通道，例如SttSocket、MqttClient等
	//此处直接返回已经存在的对象，如果多个连接，则覆盖了Device之前的连接
	//暂时不考虑多连接操作统一设备的情况
	//CIotPxCommChannelInterface *m_pPxCommChannel;

	CDvmDevice *m_pDvmDevice;
	CIotPxEngineDeviceWnd *m_pIotPxEngineDeviceWnd;

	//当前执行的过程ID和相关的数据集ID
	CString m_strProcedureID;
	CString m_strDatasetID;

	CSttIotCmdDriver m_oSttIotCmdDriver;
	TxCycleArray<CSttIotCmdDriver> m_oArrSttIotCmdDriver;  //缓存的通信命令列表，用于多连接端的处理
	TxArray<CIotPxCommChannelInterface> m_oArrCommCh;  //通信通道列表，用于多连接端的处理

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

//相关指令执行完毕的消息处理，因为各协议执行对象的数据集管理方式不一致，所以函数在派生类中实现
public:
	virtual unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	virtual unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);
	virtual unsigned long OnEngineEventMessage(unsigned long wPara,unsigned long lPara);
	virtual unsigned long OnMmsReportMessage(unsigned long wPara,unsigned long lPara);

	virtual void AddDvmEnumToParas(CSttParas *pSttParas);

	//2023-3-4  lijunqing  初始化通信过程结束返回的参数数据
	virtual void AddRetDatasToParas(CSttParas *pSttParas);

	//2023-3-5  lijunqing  添加报告数据到
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

