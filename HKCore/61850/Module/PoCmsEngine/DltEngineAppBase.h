// DltEngine.h : DltEngine 应用程序的主头文件
//
#pragma once

#include "../61850ClientConfig/61850ClientCfgMngrGlobal.h"
#include "../61850ClientConfig/61850ClientConfig.h"
#include "../dlt860/DLT860Api.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"


#define WND_UPDATE_DATA		123456
#define WM_UPDATE_DEVICE_IP_DESC  (WM_USER+1014)
#define WM_PROCEDURE_RESET	(WM_USER+1012)

class CDltEngineAppBase : public CDLT860Api
{
public:
	CDltEngineAppBase();
	virtual ~CDltEngineAppBase();

public://界面相关
	void ShowSpyWnd(LONG nShow);
	void StartProgress();
	void StopProgress(long nDeviceIndex);

// 重写
public:
	virtual BOOL InitInstance();

private:
	CString m_strErrorMsg;
	CAutoCriticSection m_oAutoCriticSectionErrorMsg;

public:
	virtual int ExitInstance();

public:
	void AddErrorString(const CString &strMsg);
	void GetErrorString(CString &strMsg);

	virtual long Client61850_DataOpeProc(CFuncParamEx *pFuncParaEx);
	BOOL SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam);//zhouhj 20210326 发送测试功能结束消息

	virtual BOOL CallFirstFunc(long nDeviceIndex);
	virtual BOOL CallCurrFunc(long nDeviceIndex);
	virtual BOOL InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas);
	virtual BOOL InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas);
	virtual BOOL InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas);
	virtual BOOL InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);
	BOOL IsFuncsAllFinish(long nDeviceIndex);
	long GetCurrSelDeviceIndex();
	void SetReportRet(CFuncParamEx *pFuncParaEx,BOOL bSucc, BOOL bStart_NotStop);
	ACSI_NODE* GetCurrSelDevice();
	LD_NODE* GetCurrSelLDevice();

	BOOL IsCurSelConnectDevice()
	{
		long nDeviceIndex = GetCurrSelDeviceIndex();

		if ((nDeviceIndex<0)||(nDeviceIndex>=MAX_DEVICE))
		{
			return FALSE;
		}

		return m_oFuncParamEx[nDeviceIndex].IsConnectDevice();
	}

	void UpdateDeviceIP_Desc(long nDeviceIndex);
	CString Cms_GetDAUnit(tagDA *pDA);
	/* 2012-10-08  解析变量的单位 */
	ST_VOID My_PareVarUnite(int nValue, CString &strText);
};

extern CDltEngineAppBase *theCmsApp;
