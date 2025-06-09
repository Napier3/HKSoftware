#pragma once

#include "../VmXImpBase.h"
#include "SimpacTestAscii2.h"

//2021-8-29  lijunqing
//ÎÂ¿ØÏä
class CVmSimpacApp : public CVmXImpBase
{
public:
	CVmSimpacApp();
	virtual ~CVmSimpacApp(void);

	CSimpacTestAscii2 m_oSimpacTestAscii2;

public:
	virtual void OnXTimer(DWORD dwTimerID);
	virtual long TestExec(CDataGroup *pParas);
	virtual long StopTest();
	virtual BOOL ConnectDeviceExec();
	virtual BOOL IsConnectSuccess();

public:
	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);

	virtual long GetRtDatas(CDataGroup *pSttParas);
	virtual void OnConfigDevice(WPARAM wParam, LPARAM lParam);
	
	virtual void OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);

public:
	virtual void SendRtData();

};

