#include "stdafx.h"
#include "WinTcpSocket.h"

CWinTcpSocket::CWinTcpSocket()
{

}

CWinTcpSocket::~CWinTcpSocket()
{

}

int CWinTcpSocket::Connect(char* strRemote, unsigned int iPort )
{
	if( strlen( strRemote ) == 0 || iPort == 0 )
	{
		return CODE_ERROR;
	}
	
	hostent *hostEnt = NULL;
	long lIPAddress = 0;
	
	hostEnt = gethostbyname( strRemote );
	
	if( hostEnt != NULL )
	{
		lIPAddress = ((in_addr*)hostEnt->h_addr)->s_addr;
		m_sockaddr.sin_addr.s_addr = lIPAddress;
	}
	else
	{
		m_sockaddr.sin_addr.s_addr = inet_addr( strRemote );
	}
	
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons( iPort );
	
	if( connect( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	{
        set_LastError( "connect() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;
}

int CWinTcpSocket::Send( SOCKET s, char* strData, int iLen )
{
	if( strData == NULL || iLen == 0 )
	{
		return CODE_ERROR;
	}
	
	if( send( s, strData, iLen, 0 ) == SOCKET_ERROR )
	{
        set_LastError( "send() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;

}


int CWinTcpSocket::Send(char* strData, int iLen )
{
	if( strData == NULL || iLen == 0 )
	{
		return CODE_ERROR;
	}
	
	if( send( m_hSocket, strData, iLen, 0 ) == SOCKET_ERROR )
	{
        set_LastError( "send() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;
}


int CWinTcpSocket::Receive(char* strData, int iLen )
{
	if( strData == NULL )
	{
		return CODE_ERROR;
	}
	
	int len = 0;
	int ret = 0;
	
	ret = recv( m_hSocket, strData, iLen, 0 );
	
	if ( ret == SOCKET_ERROR )
	{
        set_LastError( "recv() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return ret;
}

int CWinTcpSocket::Receive(SOCKET s, char* strData, int iLen )
{
	if( strData == NULL )
	{
		return CODE_ERROR;
	}
	
	int len = 0;
	int ret = 0;
	
	ret = recv( s, strData, iLen, 0 );
	
	if ( ret == SOCKET_ERROR )
	{
        set_LastError( "recv() failed", WSAGetLastError() );
        return CODE_ERROR;
	}

	return ret;
}

int CWinTcpSocket::Listen(int iQueuedConnections )
{
	if( iQueuedConnections == 0 )
	{
		return CODE_ERROR;
	}
	
	if( listen( m_hSocket, iQueuedConnections ) == SOCKET_ERROR )
	{
        set_LastError( "listen() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;
}


int CWinTcpSocket::Accept(SOCKET s )
{
	int Len = sizeof( m_rsockaddr );
	
	memset( &m_rsockaddr, 0, sizeof( m_rsockaddr ) );
	
	if( ( m_hSocket = accept( s, (SOCKADDR*)&m_rsockaddr, &Len ) ) == INVALID_SOCKET )
	{
        set_LastError( "accept() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	
	return CODE_SUCCESS;
}


int CWinTcpSocket::asyncSelect(HWND hWnd, unsigned int wMsg, long lEvent )
{
	if( !IsWindow( hWnd ) || wMsg == 0 || lEvent == 0 )
	{
        return CODE_ERROR;
	}
	
	if( WSAAsyncSelect( m_hSocket, hWnd, wMsg, lEvent ) == SOCKET_ERROR )
	{
        set_LastError( "WSAAsyncSelect() failed", WSAGetLastError() );
        return CODE_ERROR;
	}
	return CODE_SUCCESS;
}