#pragma once

#include "SttMqttEngineBase.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "XCommSvrWnd.h"

#define IOT_TEST_STATE_IDLE			0
#define IOT_TEST_STATE_TESTING		1
#define IOT_TEST_STATE_WAITRESULT	2

class CIotEngineProtocolClient:public CSttMqttEngineBase,public CXCommSvrWndInterface
{
public:
	CIotEngineProtocolClient();
	virtual ~CIotEngineProtocolClient();

	CXCommSvrWnd m_oXCommSvrWnd;//用于定时器窗口
	virtual void OnXTimer(UINT nIDEvent);

	//外部消息定义
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long  m_hSysMsgWnd;
	unsigned long  m_nSysMsg;

	CString m_strDvmFile;
	CString m_strPpxmlFile;
	CString m_strDeviceID;
	CString m_strIP;
	long m_nPort;

	CDvmDevice m_oDvmDevice;			//数据设备模型
public:
	virtual void OnClose(char *pszErr);
	BOOL Init(const char *pszIP,long nPort);
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface,const CString &strFromSN,  char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);	

	BOOL IsConnectSuccessful();
	BOOL ConnectDevice();
	void AttachSystemWndMsg(long hWnd, long nMsgID);
	void RegisterProcedureWndMsg(const CString &strProcedureID, long hWnd, long nMsgID);
	void UnRegisterProcedureWndMsg(const CString &strProcedureID, long hWnd, long nMsgID);
	long CreateDevice(const CString &strCmmConfig);
	long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath
		,CExBaseList &listDataInterface,const CString &strRecordMode);
	long GetDataset(const CString &strDatasetPath);
	long ConfigDevice(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile);
	long CloseDevice();

	long SendCmd(CSttCmdBase *pCmd);
	long GetCmdTimeOverLong();
	BOOL IsTesting(){return (m_nTestState != IOT_TEST_STATE_IDLE);}
	void InitTestState();

	CDvmDataset *GetDeviceAttrs();
	CDvmDataset *FindDataset(const CString &strDsID);

	BOOL NeedClearDataset(const CString& strDatasetID);

public:
	void PostDeviceSysMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam);

public:
	BOOL InitParas(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile);

	long Process_SysState_Reply(CSttSysState &oSysState);
	long Process_SysState_Event_CommFinish(CSttSysState &oSysState);
	long Process_SysState_Event_CommError(CSttSysState &oSysState);
	long Process_SysState_Event_DeviceClosed(CSttSysState &oSysState);
	long Process_SysState_Event_CommOverTime(CSttSysState &oSysState);

	long Process_SysState_UpdateDataset(CSttSysState &oSysState);

	long Process_SysState_CreateDevice(CSttSysState &oSysState);
	long Process_SysState_RunProcedure(CSttSysState &oSysState);
	long Process_SysState_CloseDevice(CSttSysState &oSysState);

private:		
	long m_nTestState;					//测试状态：0空闲，1：正在测试；2：等待结果
	CString m_strCurCmd;				//当前命令：RunProcedure\GetDataset\CreateDevice等
	CString m_strCurItemPath;			//当前测试项
	CDvmDataset *m_pCurDataset;		//当前命令数据集
//	CDvmDevice m_oDvmDevice;			//数据设备模型
};

//////////////////////////////////
