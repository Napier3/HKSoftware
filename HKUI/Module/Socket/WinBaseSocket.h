#ifndef _WINBASESOCKET_H__
#define _WINBASESOCKET_H__

#include "../OSInterface/OSInterface.h"

#ifdef _PSX_QT_LINUX_
//for LINUX
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/types.h"
#include <netdb.h>
#include <arpa/inet.h>
#include "stdio.h"
#include <unistd.h>
#include "errno.h"

#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#define LPSOCKADDR sockaddr*
#define SD_BOTH SHUT_RDWR
#define SOCKLEN socklen_t

#else  //_PSX_QT_LINUX_
//for windows
#include <Winsock2.h>
#pragma comment( lib, "ws2_32.lib" )
#define SOCKLEN int
#endif

const int ERR_MAXLENGTH=512;

class CWinBaseSocket
{
public:
	CWinBaseSocket();
	virtual ~CWinBaseSocket();

	static BOOL g_bInitFlag;	//初始化标志
	static BOOL InitSocket();
	static void ExitSocket();

public:
    BOOL IsSocketValid();
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
#ifdef _PSX_QT_LINUX_
    int WSAGetLastError(){ return errno; }
     int GetLastError(){ return 0; }
#endif

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

#ifndef _PSX_QT_LINUX_
BOOL Socket_JoinLeaf(const char *pszMultIp, SOCKET &sk);//加入组播
BOOL Socket_GetSubNetMask(const char *pszIP, BYTE &b1, BYTE &b2, BYTE &b3, BYTE &b4);//获取子网掩码
void Socket_InitSocketAddr(	struct sockaddr_in &skt, const char *pszIP, long nPort);
void Socket_GetBroadcastAddr(struct sockaddr_in &skt, const char *pszIP);

BOOL Socket_SetSocketKeepAlive(SOCKET sock, long keepalivetime=900, long keepaliveinterval=1000, bool onoff=TRUE);
#endif


#endif
