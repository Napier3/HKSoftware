#pragma once

#include "../VmXImpBase.h"
#include "GuBeiTest.h"

//2022-4-08  mashujian
//È«ÇòÔº-ÎÂ¿ØÎÂ¿Ø²Û
class CVmGuBeiApp : public CVmXImpBase
{
public:
	CVmGuBeiApp();
	virtual ~CVmGuBeiApp(void);

	CGuBeiTest m_oGuBeiTest;

public:
	virtual void OnXTimer(DWORD dwTimerID);
	virtual long TestExec(CDataGroup *pParas);
	virtual long StopTest();
	virtual BOOL ConnectDeviceExec();
	virtual BOOL IsConnectSuccess();
	CString GetLastError()	{	return m_oGuBeiTest.GetLastError();	}

public:
	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);

	virtual long GetRtDatas(CDataGroup *pSttParas);

private:
	virtual void OnConfigDevice(WPARAM wParam, LPARAM lParam);
	
public:
	virtual void OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);

public:
	virtual void SendRtData();

};

