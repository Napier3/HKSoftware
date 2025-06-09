#ifndef  _WINTCPSOCKET_H__
#define _WINTCPSOCKET_H__

#include "WinBaseSocket.h"

class CWinTcpSocket : public CWinBaseSocket
{
public:
	CWinTcpSocket();
	virtual ~CWinTcpSocket();

public:
	virtual BOOL Connect(const char* strRemote, unsigned int iPort );	
	virtual long Send( SOCKET s, char* strData, int iLen );					
	virtual long Send( char* strData, int iLen );	
	virtual long Receive( SOCKET s, char* strData, int iLen );				
	virtual long Receive( char* strData, int iLen );
	virtual BOOL Listen( int iQueuedConnections );								
	virtual BOOL Accept( SOCKET s );											
	virtual BOOL asyncSelect( HWND hWnd,	unsigned int wMsg, long lEvent );

public:
	DWORD m_dwReceiveBuffLen;
	BYTE  *m_pReceiveBuff;
	DWORD m_dwReceiveGap;
	DWORD m_dwIdleCount;

public:
	void SetReceiveBuffLen(DWORD dwLen);
	void SetReceiveGap(DWORD dwReceiveGap_Ms)	{	m_dwReceiveGap = dwReceiveGap_Ms;	}
	void SetIdleCount(DWORD dwIdleCount)	{	m_dwIdleCount = dwIdleCount;	}
};
#endif