#pragma once

#include "IotTestCtrl.h"
//#include "../../Module/TestMacro/TestMacros.h"

//lijunqing 2021-8-15  数据对象统一放在数据中心中进行管理
class CIotVmAppBase : public CExBaseList
{
public:
	CIotVmAppBase();
	virtual ~CIotVmAppBase();

public:
	void InitIotVmBase();
	void ExitIotVmBase();

	CIotTestCtrlBase *CreateIotTestCtrl(const CString &strConfig);

	virtual CIotTestCtrlBase* OnNewTestApp(const CString &strTestAppSN,const CString &strTestMacrosFile);
	virtual CIotTestCtrlBase* OnNewIotTestApp(const CString &strTestAppSN,const CString &strTestMacrosFile
		,const CString &strDeviceSN,long nDeviceType);

private:
	CExBaseList* CreateConfigDatas(const CString &strConfig);
};

extern CIotVmAppBase *g_theIotVmApp;