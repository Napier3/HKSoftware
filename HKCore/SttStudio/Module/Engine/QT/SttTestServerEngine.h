#pragma once

#include "../SttTestServerBase.h"

class CSttTestServerEngine :public QObject, public  CSttTestServerBase
{
	Q_OBJECT

public:
    static CSttTestServerEngine* Create(int fd, char *pszIP, int nTestPort,int nReplayPort = 0);
    static void Release();

private:
	CSttTestServerEngine();
	virtual ~CSttTestServerEngine();

	void Init(int fd);

public:
    virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
    virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

	virtual void OnCallBackTimer();
	BOOL m_bRunTimer;
private:
	// CSttTestCmd m_oSttTestCmd;
	// QTimer *m_pServerTimer;


public slots:
	// void OnServerTimer();
	// void OnCallBackTimer();
};
void *TimerThread(LPVOID pParam);
//extern CSttServerTestCtrlCntr  *g_pTestCtrlEngine;
