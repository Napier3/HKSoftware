#ifndef  _WINTCPSOCKET_CLIENT_H__
#define  _WINTCPSOCKET_CLIENT_H__

#include "WinTcpSocket.h"
#include "pthread.h"

void Signal_Handler(int nSigNo);

class CWinTcpSocketClient : public CWinTcpSocket
{
public:
	CWinTcpSocketClient();
	virtual ~CWinTcpSocketClient();

public:
	virtual BOOL Connect(const char* strRemote, unsigned int iPort );	
	virtual void Attach(SOCKET hSocket);
	virtual SOCKET Detatch();
	virtual void CreateRcvThread();
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnSocketIdle(long nMs);
	virtual void OnClose(int nErrorCode);
	virtual BOOL InitSocketClient(int nMs);
	virtual BOOL Close();

	//lijq 2020-4-25  结束接受线程
	virtual void ExitRcvTrhead();
    void WaitForThreadExit();

public:
//lijq 2020-04-25  将SttSocket转换为单独的发送、接受数据的通道
	pthread_t m_pThread;
	BOOL m_bExitTcpClientThread;
	BOOL m_bDetach; //如果是Detatch，则不能发送OnClose
    BOOL m_bClosing;
};

void *TcpClientThread(LPVOID pParam);
 
#endif
