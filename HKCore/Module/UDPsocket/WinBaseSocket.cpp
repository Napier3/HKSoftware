#include "stdafx.h"
#include "WinBaseSocket.h"

CWinBaseSocket::CWinBaseSocket()
{
	memset(&m_sockaddr,0,sizeof(sockaddr_in));
	memset(&m_rsockaddr,0,sizeof(sockaddr_in));
	m_wVersion=MAKEWORD(2,2);
	m_nInitFlag=CODE_ERROR;
}


CWinBaseSocket::~CWinBaseSocket()
{
	WSACleanup();
}


int CWinBaseSocket::InitSocket()
{
	//初始化socket

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) 
	{
		m_nInitFlag=CODE_ERROR;
		return CODE_ERROR;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup( );
		m_nInitFlag=CODE_ERROR;
		return CODE_ERROR; 
	}

	m_nInitFlag=CODE_SUCCESS;
	return CODE_SUCCESS;
}


int CWinBaseSocket::Creat(int nNetTYpe)
{
	/****************************** 	
	功能：创建socket，
	nNetTYpe:传输要创建tcp 还是Udp
	TCp方式传输：SOCK_STREAM
	Udp方式传输：SOCK_DGRAM
	*******************************/

	if(m_nInitFlag!=CODE_SUCCESS)
	{
		return CODE_ERROR;
	}

	if(nNetTYpe!=SOCK_STREAM && nNetTYpe!=SOCK_DGRAM)
	{
		return CODE_ERROR;
	}

	if ( (m_hSocket = socket( AF_INET, nNetTYpe, 0 )) == INVALID_SOCKET )
	{
        set_LastError( "socket() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;	
}


int CWinBaseSocket::Close()
{
	if ( closesocket( m_hSocket ) == SOCKET_ERROR )
	{
        set_LastError( "closesocket() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	memset( &m_sockaddr, 0, sizeof( sockaddr_in ) );
	memset( &m_rsockaddr, 0, sizeof( sockaddr_in ) );
	
	return CODE_SUCCESS;
}


 int CWinBaseSocket::Bind( char* strIP, unsigned int iPort )
 {
	/*
	socket bind;
	strIp:要绑定的IP地址
	iPort:要绑定的端口号
	*/

	 if(m_nInitFlag!=CODE_SUCCESS)
	 {
		 return CODE_ERROR;
	 }

	 if( strlen( strIP ) == 0 || iPort == 0 )
	 {
		 return CODE_ERROR;
	 }
	 
	 memset( &m_sockaddr,0, sizeof( m_sockaddr ) );
	 m_sockaddr.sin_family = AF_INET;
	 m_sockaddr.sin_addr.s_addr = inet_addr( strIP );
	 m_sockaddr.sin_port = htons( iPort );
	 
	 if ( bind( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "bind() failed", WSAGetLastError() );
		 return CODE_ERROR;
	 }

	return CODE_SUCCESS;

 }
 

 int CWinBaseSocket::get_LocalIP(char* strIP )
 {
	 if( strIP == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 int  namelen = sizeof( m_sockaddr );
	 HOSTENT* hEnt = NULL;
	 char szHostName[512] = {0};
	 char szIP[16] = {0};
	 char szAddrField[4] = {0};
	 unsigned int ufield = 0;
	 
	 if( getsockname( m_hSocket, (SOCKADDR*)&m_sockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 return CODE_ERROR;
	 }
	 
	 longToDottedQuad( m_sockaddr.sin_addr.s_addr, strIP );
	 
	return CODE_SUCCESS;
 }


 int CWinBaseSocket::get_LocalPort(int* iPort )
 {
	 if( iPort == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 *iPort = ntohs(m_sockaddr.sin_port);
	 
	return CODE_SUCCESS;
 }



 int CWinBaseSocket::get_RemoteIP(char* strIP )
 {
	 if( strIP == NULL )
	 {
		 return CODE_ERROR;
	 }

	 int namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 set_LastError( "getpeername() failed", WSAGetLastError() );

		 return CODE_ERROR;
	 }
	 
	 longToDottedQuad( m_rsockaddr.sin_addr.s_addr, strIP );
	 
	 return CODE_SUCCESS;
 }


 int CWinBaseSocket::get_RemotePort(int* iPort )
 {
	 if( iPort == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 int namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 set_LastError( "getpeername() failed", WSAGetLastError() );
		 return CODE_ERROR;
	 }
	 
	 *iPort = ntohs( m_rsockaddr.sin_port );
	 
	return CODE_SUCCESS;
 }

 int CWinBaseSocket::get_LocalHost(char* strBuffer, int iBufLen )
 {
	 if( strBuffer == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 char strHost[512] = {0};
	 hostent* hostEnt = NULL;
	 int iLen = 0;
	 
	 gethostname( strHost, 512 );
	 hostEnt = gethostbyname( strHost );
	 
	 if( hostEnt == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 iLen = strlen( hostEnt->h_name );
	 
	 if( iLen > iBufLen )
	 {
		 return CODE_ERROR;
	 }
	 
	 memset( strBuffer, 0, iBufLen );
	 memcpy( strBuffer, hostEnt->h_name, iLen );
	 
	return CODE_SUCCESS;
 }


 int CWinBaseSocket::get_RemoteHost(char* strBuffer, int iBufLen )
 {
	 if( strBuffer == NULL )
	 {
		 return CODE_ERROR;
	 }
	 
	 hostent* hostEnt = NULL;
	 int iLen = 0;
	 int namelen = sizeof( m_rsockaddr );
	 
	 if( getpeername( m_hSocket, (SOCKADDR*)&m_rsockaddr, &namelen ) == SOCKET_ERROR )
	 {
		 return CODE_ERROR;
	 }
	 
	 hostEnt = gethostbyaddr( (char*)&m_rsockaddr.sin_addr.s_addr, 4 ,PF_INET );
	 
	 if( hostEnt != NULL )
	 {
		 iLen = strlen( hostEnt->h_name );

		 if( iLen > iBufLen )
		 {
			 return CODE_ERROR;
		 }
		 
		 memcpy( strBuffer, hostEnt->h_name, iLen );
		 return CODE_SUCCESS;
	 }
	 
	return CODE_ERROR;
 }


 int CWinBaseSocket::set_RecvTimeout(int ms )
 {
	 if( ms < 0 )
	 {
		 return CODE_ERROR;
	 }
	 
	 if( setsockopt( m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "setsockopt() failed.", WSAGetLastError() );

		 return CODE_ERROR;
	 }
	 
   	 return CODE_SUCCESS;
 }



 int CWinBaseSocket::set_SendTimeout(int ms )
 {
	 if( ms < 0 )
	 {
		 return CODE_ERROR;
	 }
	 
	 if( setsockopt( m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	 {
		 set_LastError( "setsockopt() failed.", WSAGetLastError() );
		 return CODE_ERROR;
	 }
	 
	return CODE_SUCCESS;
 }


 void CWinBaseSocket::longToDottedQuad(unsigned long ulLong, char* cBuffer )
 {
	 if(cBuffer==NULL)
	 {
		 return;
	 }

	sprintf( cBuffer, "%d.%d.%d.%d",(int)((BYTE*)&ulLong)[3],
				(int)((BYTE*)&ulLong)[2],(int)((BYTE*)&ulLong)[1],(int)((BYTE*)&ulLong)[0] );
 }



 int CWinBaseSocket::GetInitFlag()
 {
	 /**********************
		返回值：
		CODE_ERROR：初始化失败
		CODE_SUCCESS：初始化成功
	 **********************/
	 return m_nInitFlag;
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