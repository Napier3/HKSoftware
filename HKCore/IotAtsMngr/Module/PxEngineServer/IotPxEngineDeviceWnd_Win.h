#pragma once

#include "IotPxEngineDeviceWnd.h"

class CIotPxEngineDeviceWnd_Win : public CIotPxEngineDeviceWnd
{
    DECLARE_DYNAMIC(CIotPxEngineDeviceWnd_Win)

public:
	CIotPxEngineDeviceWnd_Win();
	virtual ~CIotPxEngineDeviceWnd_Win();
	
	virtual BOOL CreateIotPxEngineDeviceWnd();
	
protected:
    DECLARE_MESSAGE_MAP()

	LRESULT XOnProcedureEndMsg(WPARAM wParam, LPARAM lParam);
	LRESULT XOnEngineSystemMessage(WPARAM wPara,LPARAM lPara);
	LRESULT XOnEngineEventMessage(WPARAM wPara,LPARAM lPara);
	LRESULT XOnMmsReportMessage(WPARAM wPara,LPARAM lPara);

public:
	virtual void OnTimer(unsigned int  nIDEvent);
};


