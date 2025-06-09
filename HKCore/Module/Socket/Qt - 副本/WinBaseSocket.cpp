#include "stdafx.h"
#include "WinBaseSocket.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../XLanguage/XLanguageResource.h"
#endif

CWinBaseSocket::CWinBaseSocket()
{
	memset(&m_sockaddr,0,sizeof(sockaddr_in));
	memset(&m_rsockaddr,0,sizeof(sockaddr_in));
	m_hSocket = NULL;
	m_bAttachFlag = FALSE;
}


CWinBaseSocket::~CWinBaseSocket()
{

}

BOOL CWinBaseSocket::IsSocketClose()
{
	fd_set rfd; 
	FD_ZERO(& rfd); 
	FD_SET(m_hSocket,& rfd); 
	timeval tv = {0}; 
	select(m_hSocket + 1, & rfd ,0, 0, &tv); 

	if(!FD_ISSET(m_hSocket,& rfd))
		return FALSE; 

	return TRUE;
} 

void CWinBaseSocket::Attach(SOCKET hSocket)
{
	m_hSocket = hSocket;
}

BOOL  CWinBaseSocket::Create(int nNetTYpe)
{
	/****************************** 	
	功能：创建socket，
	nNetTYpe:传输要创建tcp 还是Udp
	TCp方式传输：SOCK_STREAM
	Udp方式传输：SOCK_DGRAM
	*******************************/

	if(nNetTYpe!=SOCK_STREAM && nNetTYpe!=SOCK_DGRAM)
	{
		return FALSE;
	}

	if ( (m_hSocket = socket( AF_INET, nNetTYpe, 0 )) == INVALID_SOCKET )
	{
        set_LastError( "socket() failed", WSAGetLastError() );
        return FALSE;
	}
	
	return TRUE;	
}


BOOL CWinBaseSocket::Close()
{
	if (m_hSocket == NULL)
	{
		return TRUE;
	}

	shutdown(m_hSocket, SD_BOTH);

    if ( close( m_hSocket ) == SOCKET_ERROR )
	{
        set_LastError( "closesocket() failed", WSAGetLastError() );
	}
	
	memset( &m_sockaddr, 0, sizeof( sockaddr_in ) );
	memset( &m_rsockaddr, 0, sizeof( sockaddr_in ) );
	m_hSocket = NULL;
	
	return TRUE;
}


/*
socket bind;
strIp:要绑定的IP地址
iPort:要绑定的端口号
*/
BOOL CWinBaseSocket::Bind(const char* strIP, unsigned int iPort )
{
	 if(iPort == 0 )
	 {
		 return FALSE;
	 }
	 
	 memset( &m_sockaddr,0, sizeof( m_sockaddr ) );
	 m_sockaddr.sin_family = AF_INET;

	 if  (strIP != NULL)
	 {
		if (*strIP == 0)
		{
			m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else
		{
			m_sockaddr.sin_addr.s_addr = inet_addr( strIP );
		}
	 }
	 else
	 {
		 m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	 }

	 m_sockaddr.sin_port = htons( iPort );
	 
	 if ( bind( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "bind() failed", WSAGetLastError() );
		 return FALSE;
	 }

	return TRUE;

 }
 

BOOL CWinBaseSocket::get_LocalIP(char* strIP )
 {
	 if( strIP == NULL )
	 {
		 return FALSE;
	 }
	 
     socklen_t  namelen = sizeof( m_sockaddr );
//	 HOSTENT* hEnt = NULL;
	 char szHostName[512] = {0};
	 char szIP[16] = {0};
	 char szAddrField[4] = {0};
	 unsigned int ufield = 0;
	 
	 if( getsockname( m_hSocket, (SOCKADDR*)&m_sockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 return FALSE;
	 }
	 
	 longToDottedQuad( m_sockaddr.sin_addr.s_addr, strIP );
	 
	return TRUE;
 }


BOOL CWinBaseSocket::get_LocalPort(int* iPort )
 {
	 if( iPort == NULL )
	 {
		 return FALSE;
	 }
	 
	 *iPort = ntohs(m_sockaddr.sin_port);
	 
	return TRUE;
 }



BOOL CWinBaseSocket::get_RemoteIP(char* strIP )
 {
	 if( strIP == NULL )
	 {
		 return FALSE;
	 }

     socklen_t namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 set_LastError( "getpeername() failed", WSAGetLastError() );

		 return FALSE;
	 }
	 
	 longToDottedQuad( m_rsockaddr.sin_addr.s_addr, strIP );
	 
	 return TRUE;
 }


BOOL CWinBaseSocket::get_RemotePort(int* iPort )
 {
	 if( iPort == NULL )
	 {
		 return FALSE;
	 }
	 
     socklen_t namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 set_LastError( "getpeername() failed", WSAGetLastError() );
		 return FALSE;
	 }
	 
	 *iPort = ntohs( m_rsockaddr.sin_port );
	 
	return TRUE;
 }

BOOL CWinBaseSocket::get_RemoteIP_Port( char* strIP,   int* iPort)
{
	if( iPort == NULL || strIP == NULL)
	{
		return FALSE;
	}

    socklen_t namelen = sizeof( m_rsockaddr );

	if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	{
		set_LastError( "getpeername() failed", WSAGetLastError() );
		return FALSE;
	}

	*iPort = ntohs( m_rsockaddr.sin_port );
	longToDottedQuad( m_rsockaddr.sin_addr.s_addr, strIP );

	return TRUE;
}

BOOL CWinBaseSocket::get_LocalHost(char* strBuffer, int iBufLen )
 {
	 if( strBuffer == NULL )
	 {
		 return FALSE;
	 }
	 
	 char strHost[512] = {0};
	 hostent* hostEnt = NULL;
	 int iLen = 0;
	 
	 gethostname( strHost, 512 );
	 hostEnt = gethostbyname( strHost );
	 
	 if( hostEnt == NULL )
	 {
		 return FALSE;
	 }
	 
	 iLen = strlen( hostEnt->h_name );
	 
	 if( iLen > iBufLen )
	 {
		 return FALSE;
	 }
	 
	 memset( strBuffer, 0, iBufLen );
	 memcpy( strBuffer, hostEnt->h_name, iLen );
	 
	return TRUE;
 }


BOOL CWinBaseSocket::get_RemoteHost(char* strBuffer, int iBufLen )
 {
	 if( strBuffer == NULL )
	 {
		 return FALSE;
	 }
	 
	 hostent* hostEnt = NULL;
	 int iLen = 0;
     socklen_t namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 return FALSE;
	 }
	 
	 hostEnt = gethostbyaddr( (char*)&m_rsockaddr.sin_addr.s_addr, 4 ,PF_INET );
	 
	 if( hostEnt != NULL )
	 {
		 iLen = strlen( hostEnt->h_name );

		 if( iLen > iBufLen )
		 {
			 return FALSE;
		 }
		 
		 memcpy( strBuffer, hostEnt->h_name, iLen );
		 return TRUE;
	 }
	 
	return FALSE;
 }


BOOL CWinBaseSocket::set_ReceiveTimeout(int ms )
 {
	 if( ms < 0 )
	 {
		 return FALSE;
	 }
	 
	 if( setsockopt( m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "setsockopt() failed.", WSAGetLastError() );

		 return FALSE;
	 }
	 
   	 return TRUE;
 }



BOOL CWinBaseSocket::set_SendTimeout(int ms )
 {
	 if( ms < 0 )
	 {
		 return FALSE;
	 }
	 
	 if( setsockopt( m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "setsockopt() failed.", WSAGetLastError() );
		 return FALSE;
	 }
	 
	return TRUE;
 }


 void CWinBaseSocket::longToDottedQuad(unsigned long ulLong, char* pBuffer )
 {
	 if(pBuffer==NULL)
	 {
		 return;
	 }

	sprintf( pBuffer, "%d.%d.%d.%d",(int)((BYTE*)&ulLong)[0],
				(int)((BYTE*)&ulLong)[1],(int)((BYTE*)&ulLong)[2],(int)((BYTE*)&ulLong)[3] );
 }



BOOL CWinBaseSocket::GetInitFlag()
 {
     return TRUE;
 }


void CWinBaseSocket::get_LastError(char* strBuffer, int* iErrNum )
 {
	 int len = strlen( m_LastError );
	 
	 if( len > 0 )
	 {
		 memset( strBuffer, 0, len );
		 memcpy( strBuffer, m_LastError, len );
		 strBuffer[len+1] = '\0';
		 *iErrNum = m_ErrorNumber;
	}
 }

 void CWinBaseSocket::set_LastError( char* newError, int errNum )
 {
	 memset( m_LastError, 0, ERR_MAXLENGTH ); 
	 memcpy( m_LastError, newError, strlen( newError ) );
	 m_LastError[strlen(newError)+1] = '\0';
	 m_ErrorNumber = errNum;
 }

 CString CWinBaseSocket::GetError(DWORD error)
 {
	 return _T("");
 }

CString CWinBaseSocket::GetError()
{
	return GetError(GetLastError());
}


#ifndef OS_QT_LINUX

//////////////////////////////////////////////////////////////////////////
#include <mstcpip.h>
BOOL Socket_SetSocketKeepAlive(SOCKET sock, long keepalivetime, long keepaliveinterval, bool onoff)
{
	BOOL bKeepAlive = TRUE;  
	int nRet = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,   
		(char*)&bKeepAlive, sizeof(bKeepAlive));  
	if (nRet == SOCKET_ERROR)  
	{  
		TRACE("setsockopt failed: %d/n", WSAGetLastError());  
		return FALSE;  
	}  
	// set KeepAlive parameter  

	tcp_keepalive alive_in;  
	tcp_keepalive alive_out;  
	alive_in.keepalivetime  = keepalivetime * 1000;//900 * 1000; // TCP连接多长时间(毫秒)没有数据就开始发送心跳包，有数据传递的时候不发送心跳包。
	//系统默认2小时，我设置15分钟，不宜设置过小
	alive_in.keepaliveinterval  = keepaliveinterval;//1000; //当keepalivetime时间到达后，每隔多长时间(毫秒)发送一个心跳包，发5次(系统默认值)
	alive_in.onoff              = onoff;//TRUE;  
	unsigned long ulBytesReturn = 0;  

	nRet = WSAIoctl(sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in),  
		&alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);  
	if (nRet == SOCKET_ERROR)  
	{  
		TRACE("WSAIoctl failed: %d/n", WSAGetLastError());  
		return FALSE;  
	}  

	return TRUE;
}

#endif
