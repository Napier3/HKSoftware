#ifndef _WINUDPSOCKET_H__
#define _WINUDPSOCKET_H__

#include "WinBaseSocket.h"

class CWinUdpSocket : public CWinBaseSocket
{
public:
	CWinUdpSocket();
	virtual ~CWinUdpSocket();

public:
	virtual BOOL CreateServer(char *strIP, unsigned int iPort);
	virtual BOOL CreateClient(char *strIP, unsigned int iPort, char *strLocalIP=NULL, unsigned int iLocalPort=0);
	virtual void CreateThead();

	virtual BOOL CreateServerEx(char *strIP, unsigned int iPort);
	virtual BOOL CreateClientEx(char *strIP, unsigned int iPort);

	virtual BOOL CreateMulticastServerEx(char *pszMultiIP,char *pszLocalIP, unsigned int iPort);
	virtual BOOL CreateMulticastClientEx(char *pszMultiIP, unsigned int iPort,int nType=1);

	virtual long Receive(char *chReciveBuf,int nLen);
	virtual long Send(char *chSendBuf,int nLen,sockaddr_in* tsockaddr=NULL);
	virtual BOOL SetRemoteIPAndPort(char *chRemoteIP,int nPort);

	virtual long OnReceive(BYTE *pRcvBuf, int iLen,sockaddr_in* fsockaddr);
	virtual void OnClose(int nErrorCode);
	
public:
    DWORD m_dwReceiveBuffLen;
    BYTE  *m_pReceiveBuff;
	void SetReceiveBuffLen(DWORD dwLen);

public:
    pthread_t m_pThread;
};

 void *UdpClientThread(LPVOID pParam);
#endif
