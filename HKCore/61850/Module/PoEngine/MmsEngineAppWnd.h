// MmsEngineAppWnd.h 
//

#pragma once

#include "../MmsApi.h"
#include "../MmsGlobal.h"
#include "../../../Module/DataMngr/DvmDataset.h"

#define CALLFUNC_MAX_RETRY_TIMES    3


#define WM_INIT_BY_RPC_MNGR  (WM_USER + 158)
#define WM_CONNECT_ALL_DEVICE  (WM_USER + 159)
#define WM_DISCONNECT_ALL_DEVICE  (WM_USER + 160)
#define WM_READ_RCDFILE_ALL  (WM_USER + 161)
#define WM_UPDATEWIND_MSG   WM_USER+3201
#define WM_UPDATEWIND_RPT   WM_USER+3202
#define WM_OPER_ALL_DEVS_REPORT WM_USER+3203
#define WM_UPDATE_DEVICE_IP_DESC  (WM_USER+1014)

class CMmsEngineAppWnd : public CWnd
{
	
public: // 仅从序列化创建
	CMmsEngineAppWnd();
	virtual ~CMmsEngineAppWnd();
	
	virtual BOOL CreateWnd()	{	return TRUE;	}

private:
	typedef struct struct_StartTripInforRpt
	{
		CFuncParamEx *pFuncParaEx;
		long nMstmSlnDvIndex;
		long nCnlnIndex;
		CString strSleDsPath;
		CString strLDType;
		CWinThread *pThread;
		CMmsEngineAppWnd *pMainFrame;
		UINT nRetSucc;
		CDvmValue *pCnln;
		int nLinkCounts;
	}STRUCT_START_RPT, *PSTRUCT_START_RPT;

	static UINT StartTripInforRpt_Thread(LPVOID pParam);
	static UINT StopTripInforRpt_Thread(LPVOID pParam);
	static UINT LinkDevAll_OneDevice_Thread(LPVOID pParam);
	BOOL StartTripInforRpt(CFuncParamEx *pFuncParaEx,const CString &strSleDsPath,const CString &strLDType);
	BOOL StopTripInforRpt(CFuncParamEx *pFuncParaEx,const CString &strSleDsPath,const CString &strLDType);

	long m_nOnCloseDevAll_Curr_Index;
	long m_nReadDirDevAll_Curr_Index;
	long m_nReadDirFailTimes;
	void OnCloseDevAll_CloseCurr();
	void OnCloseDevAll_CloseNext();
	void OnReadDirDevAll_DirCurr();
	void OnReadDirDevAll_DirNext();
	
// 属性
public:

	void PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceSysMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceEventMessage(WPARAM wParam, LPARAM lParam);
	void UpdateAfterReadFile(long nDeviceIndex);
	void ShowEncrypptInfor();


	void OnImportDevModelFile(const CString &strModelFilePath,long nDevIndex);//zhouhj

	//2020-12-22  lijunqing  外部调用配置接口，配置IP
	void OnLinkDev(long nDeviceIndex, BOOL bIsConfig);

protected:
	CString GetRptDescInfo(int dsIndex);

	LRESULT OnMmsCmdFinish_View(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsCmdAllFinish_AutoTest(LONG nFuncID, WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsCmdFinish_Error(WPARAM wParam,LPARAM lParam);
	void OnMmsCmdAllFinish_FuncID_XLink(CFuncParamEx *pFuncParaEx);

	long m_nCallFuncRetryTimes;

protected:  // 控件条嵌入成员
	BOOL m_bOperateAllDevReport;//zhouhj20181013  在启动所有装置同一数据集报告时使用
	static UINT OnStartAllDevsRpt_Thread(LPVOID pParam);
	static UINT OnStopAllDevsRpt_Thread(LPVOID pParam);
	static UINT LinkDevAll_Thread(LPVOID pParam);
	void StartAllDevsRpt_Func();
	void StopAllDevsRpt_Func();
	void LinkDevAll_ThreadFunc();
	ST_INT m_nStartAllDevsRpt_DeviceIndex;
	ST_INT m_nStartAllDevsRpt_LDIndex;
	CString m_strOperAllRpt_LDName;
	CString m_strOperAllRpt_DsName;

	CWinThread *m_pOnOperAllDevsRpt_Thread;
	CWinThread *m_pLinkDevice_Thread;

//////////////////////////////////////////////////////////////////////////
	CWinThread *m_pReadAllDeviceRcdDir;
	void Create_ReadAllDeviceRcdDir_Thread();
	static UINT ReadAllDeviceRcdDir_Thread(LPVOID pParam);
	void ReadAllDeviceRcdDir_Thread_Func();

	void ResetWriteFailErrorCode();//zhouhj 20201117复归写操作失败，上送的原因码值；

	void OnOperAllDevRpt(ST_INT nOperType);
// 生成的消息映射函数
protected:
	LRESULT OnOperAllDevsRpt(WPARAM wParam,LPARAM lParam);
	LRESULT OnDisConnAllDev(WPARAM wParam,LPARAM lParam);
	LRESULT OnReadRcdAllDev(WPARAM wParam,LPARAM lParam);
	LRESULT SaveAllMmsDevicesRcdFiles(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsCmdFinish(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsReport(WPARAM wParam,LPARAM lParam);
	LRESULT OnReset(WPARAM wParam,LPARAM lParam);
	LRESULT OnConnectAllDevice(WPARAM wParam,LPARAM lParam);

};


