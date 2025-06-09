#pragma once

#include "../VmXImpBase.h"
#include "Dtvp200Test.h"

//2021-8-29  lijunqing
//ÎÂ¿ØÏä
class CVmDtvp200 : public CVmXImpBase
{
public:
	CVmDtvp200();
	virtual ~CVmDtvp200(void);

	CDtvp200Test m_oDtvp200;
public:
	virtual void OnXTimer(DWORD dwTimerID);
	virtual long TestExec(CDataGroup *pParas);
	virtual long StopTest();
	virtual BOOL ConnectDeviceExec();
	virtual BOOL IsConnectSuccess();
	CString GetLastError()	{	return m_oDtvp200.GetLastError();	}

public:
	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);

	virtual long GetRtDatas(CDataGroup *pSttParas);
	virtual void OnConfigDevice(WPARAM wParam, LPARAM lParam);
	
	virtual void OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);

public:
	virtual void SendRtData();

};

