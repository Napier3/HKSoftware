// CmsEngineAppWnd.h 
//

#pragma once

#include "DltEngineAppBase.h"
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

class CCmsEngineAppWnd : public CWnd
{
	
public: // 仅从序列化创建
	CCmsEngineAppWnd();
	virtual ~CCmsEngineAppWnd();
	
	virtual BOOL CreateWnd()	{	return TRUE;	}

// 属性
public:
	void PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceSysMessage(WPARAM wParam, LPARAM lParam);
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


	long m_nCallFuncRetryTimes;

// 生成的消息映射函数
protected:
	LRESULT SaveAllMmsDevicesRcdFiles(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsCmdFinish(WPARAM wParam,LPARAM lParam);
	LRESULT OnMmsReport(WPARAM wParam,LPARAM lParam);
	LRESULT OnReset(WPARAM wParam,LPARAM lParam);
	LRESULT OnConnectAllDevice(WPARAM wParam,LPARAM lParam);

};


