#pragma once

#include "SerialMonitor.h"


class CSerialMonitorMngr : public CExBaseList
{
public:
	CSerialMonitorMngr(void);
	~CSerialMonitorMngr(void);

	CWinThread *m_pDataProcessThread;

	BOOL m_bOnProcess;

	int StartCapture();
	void StopCapture();
	int ProcessData(const BYTE *byData, int iLen, int iType, BOOL &bHasDealOneFrame, int &iState);
	void ResetAllData();

	void ShowMsg(LPCSTR strMsg);

	static UINT DataProcessThread(LPVOID pParam);						// 数据处理
};
