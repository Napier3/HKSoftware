#pragma once
#include "..\VmXImpBase.h"
#include "SourceDK51E1.h"

class CVmDKSourceApp : public CVmXImpBase
{
public:
	CVmDKSourceApp();
	virtual ~CVmDKSourceApp();

	CSourceDK51E1 m_oDK51E1;
	long m_nLock;

private:


public:
	virtual void OnXTimer(DWORD dwTimerID);
	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);
	virtual long StopTest();
	virtual void OnConfigDevice(WPARAM wParam, LPARAM lParam);

	virtual long TestExec(CDataGroup *pParas);
	virtual void OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);
	virtual BOOL IsConnectSuccess();
	virtual void SendRtData();
};