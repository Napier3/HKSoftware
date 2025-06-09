#pragma once

#include "../VmXImpBase.h"

//2021-8-29  lijunqing
class CVmTmprtrCtrlApp : public CVmXImpBase
{
public:
	CVmTmprtrCtrlApp();
	virtual ~CVmTmprtrCtrlApp(void);

	virtual long TestExec();
	virtual BOOL ConnectDeviceExec();
	virtual BOOL IsConnectSuccess();

public:
	virtual void Release();
	virtual CString GetConfig();
	virtual long SetConfig(CSttTestAppCfg *pSttTestAppCfg);
	virtual long SetConfig(const CString & bstrConfig);
	virtual long StopTest();
	virtual long CloseDevice();
	virtual CString GetSearchReport();
	virtual long FinishTest(long nState);
	virtual long ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter);
	virtual unsigned long StopDevice(void);

	virtual long System_Login();
};

