#include "stdafx.h"
#include "WinTcpSocket.h"
#include "../../System/TickCount32.h"
#include <fcntl.h>


CWinTcpSocket::CWinTcpSocket()
{
	m_dwReceiveBuffLen = 1024;
	m_pReceiveBuff = NULL;
	SetReceiveBuffLen(1024);

	SetReceiveGap(1);
	SetIdleCount(30);
    m_dwWifiSendTimeout = 3;//20220719 zhoulei
    m_dwSendErrCnt = 0;//20220719 zhoulei
}

CWinTcpSocket::~CWinTcpSocket()
{
	if (m_pReceiveBuff != NULL)
	{
		delete m_pReceiveBuff;
		m_pReceiveBuff = NULL;
	}
}

BOOL CWinTcpSocket::Connect(const char* strRemote, unsigned int iPort )
{
	if (strRemote == NULL || iPort == NULL)
	{
		return FALSE;
	}

	if( strlen( strRemote ) == 0 )
	{
		return FALSE;
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
	
	//	int flags = fcntl(m_hSocket,F_GETFL,0);
	//	fcntl(m_hSocket,F_SETFL,flags&~O_NONBLOCK);

	if( connect( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
	{
		int n = errno;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CWinTcpSocket::Connect 1  error=%d") , n);

		set_LastError( "connect() failed", WSAGetLastError() );

		if (n == EINPROGRESS)
		{
			struct timeval stTv;
			fd_set fdSet;
			int iValOpt;
			socklen_t iLength;
			stTv.tv_sec = 20;
			stTv.tv_usec = 0;
			FD_ZERO(&fdSet);
			FD_SET(m_hSocket,&fdSet);

			iLength = sizeof(int);

			if (0 < select( (m_hSocket+1) , NULL,&fdSet,NULL,&stTv))

			{
				if(0 > getsockopt(m_hSocket,SOL_SOCKET,SO_ERROR,(void*)(&iValOpt),&iLength))
				{
					return FALSE;
				}

				if (0 != iValOpt)
				{
					return FALSE;
				}


				return TRUE;
			}
			else
			{
				return FALSE;
			}

		}
		else
		{
			return FALSE;
		}
		//        if(n == 111)  //连接被拒绝
		//        {
		//            CTickCount32 oTick;
		//            oTick.DoEvents(500);

		//            if( connect( m_hSocket, (SOCKADDR*)&m_sockaddr, sizeof( m_sockaddr ) ) == SOCKET_ERROR )
		//            {
		//                int n = errno;
		//                CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CWinTcpSocket::Connect 2  error=%d") , n);

		//                return FALSE;
		//            }
		//        }
		return FALSE;
	}

	//	flags = fcntl(m_hSocket,F_GETFL,0);
	//	fcntl(m_hSocket,F_SETFL,flags|O_NONBLOCK);
	
	return TRUE;
}

long CWinTcpSocket::Send( SOCKET s, char* strData, int iLen )
{
	if( strData == NULL || iLen == 0 ||s<=0)
	{
		return SOCKET_ERROR;
	}

	int nLeft = iLen;
	char *p = strData;
	int nSend =  0;
	int nLoopCnt=0;
	while(nLeft > 0)
	{
		nSend = send(s,p,nLeft,0);
		if (nSend == SOCKET_ERROR )
		{
			if(IsSocketClose())
			{
				set_LastError( "send() failed", WSAGetLastError() );
                m_dwSendErrCnt++;//20220719 zhoulei 发送失败，次数加1
				return -1;
			}
			Sleep(20);
			nLoopCnt++;
            if(nLoopCnt < m_dwWifiSendTimeout)
				continue;//wifi网络延迟
			else
            {
                m_dwSendErrCnt++;//20220719 zhoulei 发送失败，次数加1
				return -1;
            }
		}
		else
		{
			nLoopCnt=0;
			p += nSend;
			nLeft -= nSend;
		}
	}

    m_dwSendErrCnt = 0;//20220719 zhoulei 发送成功，次数置0
	return iLen - nLeft;
}


long CWinTcpSocket::Send(char* strData, int iLen )
{
	return Send(m_hSocket, strData, iLen);
	//if( strData == NULL || iLen == 0 )
	//{
	//	return SOCKET_ERROR;
	//}
	
	//if(m_hSocket == 0)
	//	return SOCKET_ERROR;

	//	long nSend = send( m_hSocket, strData, iLen, 0 );
	
	//	if (nSend == SOCKET_ERROR )
	//{
	//      set_LastError( "send() failed", WSAGetLastError() );
	//}
	
	//	return nSend;
}


long CWinTcpSocket::Receive(char* strData, int iLen )
{
	if( strData == NULL )
	{
		return SOCKET_ERROR;
	}
	
	int len = 0;
	int ret = 0;
	
	ret = recv( m_hSocket, strData, iLen, 0 );
	
	if ( ret == SOCKET_ERROR )
	{
		set_LastError( "recv() failed", WSAGetLastError() );
	}
	
	return ret;
}

long CWinTcpSocket::Receive(SOCKET s, char* strData, int iLen )
{
	if( strData == NULL )
	{
		return SOCKET_ERROR;
	}
	
	int len = 0;
	int ret = 0;
	
	ret = recv( s, strData, iLen, 0 );
	
	if ( ret == SOCKET_ERROR )
	{
		set_LastError( "recv() failed", WSAGetLastError() );
	}

	return ret;
}

BOOL CWinTcpSocket::Listen(int iQueuedConnections )
{
	if( iQueuedConnections == 0 )
	{
		return FALSE;
	}
	
	if( listen( m_hSocket, iQueuedConnections ) == SOCKET_ERROR )
	{
		set_LastError( "listen() failed", WSAGetLastError() );
		return FALSE;
	}
	
	return TRUE;
}


BOOL CWinTcpSocket::Accept(SOCKET s )
{
	socklen_t Len = sizeof( m_rsockaddr );
	
	memset( &m_rsockaddr, 0, sizeof( m_rsockaddr ) );
	
	if( ( m_hSocket = accept( s, (SOCKADDR*)&m_rsockaddr, &Len ) ) == INVALID_SOCKET )
	{
		set_LastError( "accept() failed", WSAGetLastError() );
		return FALSE;
	}
	
	return TRUE;
}


BOOL CWinTcpSocket::asyncSelect(HWND hWnd, unsigned int wMsg, long lEvent )
{
	//	if( !IsWindow( hWnd ) || wMsg == 0 || lEvent == 0 )
	//	{
	//        return FALSE;
	//	}
	
	//	if( WSAAsyncSelect( m_hSocket, hWnd, wMsg, lEvent ) == SOCKET_ERROR )
	//	{
	//        set_LastError( "WSAAsyncSelect() failed", WSAGetLastError() );
	//        return FALSE;
	//	}

	return TRUE;
}

void CWinTcpSocket::SetReceiveBuffLen(DWORD dwLen)
{
	m_dwReceiveBuffLen = dwLen;

	if (m_pReceiveBuff != NULL)
	{
		delete m_pReceiveBuff;
	}

	m_pReceiveBuff = new BYTE[m_dwReceiveBuffLen+10];
	ZeroMemory(m_pReceiveBuff, m_dwReceiveBuffLen*sizeof(BYTE));
}

