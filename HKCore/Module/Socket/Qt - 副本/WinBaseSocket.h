#ifndef _WINBASESOCKET_H__
#define _WINBASESOCKET_H__

#include "../OSInterface/OSInterface.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/types.h"
#include <netdb.h>
#include <arpa/inet.h>
#include "stdio.h"
#include<unistd.h>

#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#define LPSOCKADDR sockaddr*
#define SD_BOTH SHUT_RDWR

const int ERR_MAXLENGTH=512;

class CWinBaseSocket
{
public:
	CWinBaseSocket();
	virtual ~CWinBaseSocket();

public:
	virtual BOOL IsSocketClose();
	virtual void Attach(SOCKET hSocket);
	virtual BOOL Create(int nNetTYpe);
	virtual BOOL Close();
	virtual BOOL Bind(const char* strIP, unsigned int iPort );
	virtual BOOL get_LocalIP( char* strIP );	
	virtual BOOL get_LocalPort( int* iPort );	
	virtual BOOL get_RemoteIP( char* strIP );
	virtual BOOL get_RemotePort( int* iPort );	
	virtual BOOL get_RemoteIP_Port( char* strIP,   int* iPort);
	virtual BOOL get_LocalHost( char* strBuffer, int iBufLen );
	virtual BOOL get_RemoteHost( char* strBuffer, int iBufLen );
	virtual BOOL set_SendTimeout( int ms );
	virtual BOOL set_ReceiveTimeout( int ms );	
	virtual void longToDottedQuad( unsigned long ulLong, char* pBuffer );
	virtual BOOL GetInitFlag();
	virtual void  get_LastError( char* strBuffer, int* iErrNum );
	
	CString GetError(DWORD error);
	CString GetError();
    int WSAGetLastError(){ return 0; }
     int GetLastError(){ return 0; }

public:	
	void set_LastError( char* newError, int errNum );

public:	
	sockaddr_in m_sockaddr;	
	sockaddr_in m_rsockaddr;	
	WORD m_wVersion;
	char m_LastError[ERR_MAXLENGTH+1];
	int	 m_ErrorNumber;

private:
	BOOL m_bAttachFlag;

public:	
	SOCKET m_hSocket;	
};
#endif
