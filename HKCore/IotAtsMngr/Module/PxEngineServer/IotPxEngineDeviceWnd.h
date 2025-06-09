#pragma once

//通讯规约引擎程序的异常处理时钟
#define TIMER_PPENGINE_EXCEPTION        10
#define TIMER_PPENGINE_EXCEPTION_LONG   20000

//通讯规约引擎程序的实时数据上报时钟
#define TIMER_PPENGINE_RTDATA         11
#define TIMER_PPENGINE_RTDATA_LONG   5000

#include "../../../Protocol/Module/Engine/PpGlobalDefine.h"
#include "IotPxEngineDeviceBase.h"

// class CIotPxEngineDeviceBase;

class CIotPxEngineDeviceWnd : public CWnd
{
public:
	CIotPxEngineDeviceWnd();
	virtual ~CIotPxEngineDeviceWnd();
	
	virtual BOOL CreateIotPxEngineDeviceWnd();

public:

	void SetPpEngineTimer(UINT nIDEvent, long nTimerLong);
	void SetPpEngineTimer();
	void KillPpEngineTimer(UINT nIDEvent);
	void KillPpEngineTimer();

public:
	CIotPxEngineDeviceBase* m_pIotPxEngineDevice;
	CExBaseObject *m_pTestItemRef;

protected:
	unsigned long OnProcedureEndMsg(unsigned long wParam, unsigned long lParam);
	unsigned long OnEngineSystemMessage(unsigned long wPara,unsigned long lPara);
	unsigned long OnEngineEventMessage(unsigned long wPara,unsigned long lPara);
	unsigned long OnMmsReportMessage(unsigned long wPara,unsigned long lPara);

public:
	virtual void OnTimer(unsigned int  nIDEvent);
};


