#ifndef  _WINTCPSOCKET_CLIENT_H__
#define  _WINTCPSOCKET_CLIENT_H__

#include "WinTcpSocket.h"
#include "pthread.h"
#include "../System/TickCount32.h"

class CWinTcpSocketClient : public CWinTcpSocket
{
public:
	CWinTcpSocketClient();
	virtual ~CWinTcpSocketClient();

public:
	virtual BOOL Connect(const char* strRemote, unsigned int iPort );	
	virtual void Attach(SOCKET hSocket);
	virtual void CreateThead();
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnSocketIdle(long nMs);
	virtual void OnClose(int nErrorCode);
	virtual BOOL InitSocketClient(int nMs);
	virtual BOOL Close();

public:
    //连接心跳计时
    long m_nHeartbeatTimeOut;
    CTickCount32 m_oHeartbeatTick;
    virtual long SendHeartbeatCmd(){return -1;}
    BOOL CheckHeartbeatTimeOut();
    void SetHeartbeatTimeOut(long nTimeOut){m_nHeartbeatTimeOut = nTimeOut;}

public:
    pthread_t m_pThread;
    pthread_t m_pHeartbeatThread;

};

 void *TcpClientThread(LPVOID pParam);
 void *TcpClientHeartbeatThread(LPVOID pParam);

#endif
