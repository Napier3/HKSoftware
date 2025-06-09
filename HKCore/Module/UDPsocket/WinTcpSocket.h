#ifndef WINBASESOCKET_H_H_H
#define WINBASESOCKET_H_H_H

#include "WinBaseSocket.h"

class CWinTcpSocket : public CWinBaseSocket
{
public:
	CWinTcpSocket();
	virtual ~CWinTcpSocket();
public:
	virtual int Connect( char* strRemote, unsigned int iPort );	
	virtual int Send( SOCKET s, char* strData, int iLen );					
	virtual int Send( char* strData, int iLen );	
	virtual int Receive( SOCKET s, char* strData, int iLen );				
	virtual int Receive( char* strData, int iLen );
	virtual int Listen( int iQueuedConnections );								
	virtual int Accept( SOCKET s );											
	virtual int asyncSelect( HWND hWnd,	unsigned int wMsg, long lEvent );
};
#endif