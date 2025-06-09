#pragma once
#include "IotTestCtrlBase.h"
#include "../../SttStudio/Module/SttCmd/SttIotDevices.h"

class CIotTestCtrl : public CIotTestCtrlBase
{
public:
	CIotTestCtrl();
	virtual ~CIotTestCtrl();

	CSttIotDevices m_oSttIotDevices;

	virtual BOOL IsIotTestCtrl(){return TRUE;}
	void SetIotDevice(const CString &strDeviceSN,long nDeviceType);

	virtual long Test_QueryDeviceState();
	virtual long Test_SendSensorModel(const CString &strSensorType
		,const CString &strSensorTypeID,CDataGroup *pParas);
	virtual long Test_GetTestMacros();
	virtual long Test_GetTopo();
	virtual long Test_StartTest();
	virtual long Test_StopTest();

	virtual void OnProcessOverTime();
public:
	//com接口调用
	virtual BSTR GetConfig(void){return NULL;}
	virtual LONG SetConfig(const CString & bstrConfig){return 1;}
	virtual LONG CloseDevice(void){return CIotTestCtrlBase::CloseDevice();}
	virtual BSTR GetSearchReport(void){return NULL;}
	virtual DWORD FinishTest(DWORD dwState){return 1;}

public:
	//应答或事件处理
	virtual long Process_SysState_Report(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_Exception(CSttSysState &oSysState){return 1;}

	virtual long Process_SysState_Reply_QueryDeviceState(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_SendSensorModel(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetTestMacros(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetTopo(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_StartTest(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_StopTest(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_SetParameter(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_Reply_UpdateParameter(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_Reply_GetReport(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_Reply_CloseDevice(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_Reply_GetSystemState(CSttSysState &oSysState){return 1;}
	virtual long Process_SysState_TriggerTest(CSttSysState &oSysState){return 1;}

	virtual long Process_SysState_Event_OnTestStarted(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnTestStoped(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnTestFinished(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnSearchPointReport(CSttSysState &oSysState){return 1;}
};
