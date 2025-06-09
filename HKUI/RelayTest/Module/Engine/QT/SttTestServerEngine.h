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

	BOOL m_bRunThread;
};

void *ProTimerThread(LPVOID pParam);
