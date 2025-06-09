#include "stdafx.h"
#include "WinBaseSocket.h"

#ifndef _PSX_QT_LINUX_
#include "ws2ipdef.h"
#include "iptypes.h"

#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")
#endif

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifndef _PSX_QT_LINUX_
BOOL CWinBaseSocket::g_bInitFlag = FALSE;
#else
BOOL CWinBaseSocket::g_bInitFlag = TRUE;
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

#ifdef _PSX_QT_LINUX_
#include <netinet/tcp.h>
#endif

BOOL CWinBaseSocket::IsSocketValid()
{
#ifdef _PSX_QT_LINUX_

    struct tcp_info info;
      int len=sizeof(info);
      getsockopt(m_hSocket, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);

      if(info.tcpi_state==TCP_ESTABLISHED)  //则说明未断开  else 断开
      {
        return TRUE;
      }
      else//2023.7.13 zhouhj  在Linux下TCP_CLOSE、TCP_CLOSE_WAIT判断无效 改为当前方式
      {
        return FALSE;
      }
//      else if (info.tcpi_state==TCP_CLOSE
//               || info.tcpi_state==TCP_CLOSE_WAIT)
//      {
//          return FALSE;
//      }
//      else
//      {
//          return TRUE;
//      }
#else
    if ( IsSocketClose() )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
#endif
}

BOOL CWinBaseSocket::IsSocketClose()
{
	if (m_hSocket == 0)
	{
		return TRUE;
	}

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

BOOL CWinBaseSocket::InitSocket()
{
#ifndef _PSX_QT_LINUX_
	//初始化socket
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	
	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) 
	{
		g_bInitFlag=FALSE;
		return FALSE;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		ExitSocket();
		return FALSE; 
	}
#endif

	g_bInitFlag=TRUE;
	return TRUE;
}

void CWinBaseSocket::ExitSocket()
{
#ifndef _PSX_QT_LINUX_
	WSACleanup( );
#endif

	g_bInitFlag=FALSE;
}


BOOL CWinBaseSocket::Create(int nNetTYpe)
{
	/****************************** 	
	功能：创建socket，
	nNetTYpe:传输要创建tcp 还是Udp
	TCp方式传输：SOCK_STREAM
	Udp方式传输：SOCK_DGRAM
	*******************************/

	if(g_bInitFlag!=TRUE)
	{
		return FALSE;
	}

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

#ifndef _PSX_QT_LINUX_
	if ( closesocket( m_hSocket ) == SOCKET_ERROR )
#else
    if ( close( m_hSocket ) == SOCKET_ERROR )
#endif
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
	 if(g_bInitFlag!=TRUE)
	 {
		 return FALSE;
	 }

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
	 
#ifdef _PSX_QT_LINUX_
    socklen_t  namelen = sizeof( m_sockaddr );
#else
    int  namelen = sizeof( m_sockaddr );
#endif

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

#ifdef _PSX_QT_LINUX_
    socklen_t namelen = sizeof( m_rsockaddr );
#else
     int namelen = sizeof( m_rsockaddr );
#endif

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
	 
#ifdef _PSX_QT_LINUX_
    socklen_t namelen = sizeof( m_rsockaddr );
#else
     int namelen = sizeof( m_rsockaddr );
#endif

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

#ifdef _PSX_QT_LINUX_
    socklen_t namelen = sizeof( m_rsockaddr );
#else
     int namelen = sizeof( m_rsockaddr );
#endif

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
#ifdef _PSX_QT_LINUX_
    socklen_t namelen = sizeof( m_rsockaddr );
#else
     int namelen = sizeof( m_rsockaddr );
#endif

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
	 
#ifdef _PSX_QT_LINUX_
    struct timeval tv;
     tv.tv_sec = 0;
     tv.tv_usec = ms * 1000;
     if(setsockopt(m_hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(tv)) == SOCKET_ERROR)
#else
	if( setsockopt( m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
#endif
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
	 
#ifdef _PSX_QT_LINUX_
     struct timeval tv;
     tv.tv_sec = 0;
     tv.tv_usec = ms * 1000;
     if(setsockopt(m_hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) == SOCKET_ERROR)
#else
	 if( setsockopt( m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
#endif
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
	 return g_bInitFlag;
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
#ifdef _PSX_QT_LINUX_

#else


#ifdef NOT_USE_XLANGUAGE
	 switch(error)
	 {
	 case WSANOTINITIALISED:
		 return _T("初始化错误");
		 break;
	 case WSAENOTCONN:
		 return _T("对方没有启动");
		 break;
	 case WSAEWOULDBLOCK :
		 return _T("对方已经关闭");
		 break;
	 case WSAECONNREFUSED:
		 return _T("连接的尝试被拒绝");
		 break;
	 case WSAENOTSOCK:
		 return _T("在一个非套接字上尝试了一个操作");
		 break;
	 case WSAEADDRINUSE:
		 return _T("特定的地址已在使用中");
		 break;
	 case WSAECONNRESET:
		 return _T("与主机的连接被关闭");
		 break;
	 default:
		 return _T("一般错误");	
	 }
#else
	 switch(error)
	 {
	 case WSANOTINITIALISED:
		 return g_sLangTxt_InitiaErrors/*_T("初始化错误")*/;
		 break;
	 case WSAENOTCONN:
		 return g_sLangTxt_OtherStart/*_T("对方没有启动")*/;
		 break;
	 case WSAEWOULDBLOCK :
		 return g_sLangTxt_OtherClose/*_T("对方已经关闭")*/;
		 break;
	 case WSAECONNREFUSED:
		 return g_sLangTxt_ConnectRefuse/*_T("连接的尝试被拒绝")*/;
		 break;
	 case WSAENOTSOCK:
		 return g_sLangTxt_AttemptOperate/*_T("在一个非套接字上尝试了一个操作")*/;
		 break;
	 case WSAEADDRINUSE:
		 return g_sLangTxt_SpecificUse/*_T("特定的地址已在使用中")*/;
		 break;
	 case WSAECONNRESET:
		 return g_sLangTxt_ConnectionClosed/*_T("与主机的连接被关闭")*/;
		 break;
	 default:
		 return g_sLangTxt_GenericError/*_T("一般错误")*/;	
	 }
#endif

#endif

	 return _T("");
 }

CString CWinBaseSocket::GetError()
{
	return GetError(GetLastError());
}

#ifndef _PSX_QT_LINUX_
 //加入组播
 BOOL Socket_JoinLeaf(const char *pszMultIp, SOCKET &sk)
 {
	 if(strlen(pszMultIp)<4)
	 {
		 return FALSE;
	 }

	 ip_mreq ipmreq;

	 ipmreq.imr_multiaddr.s_addr=inet_addr(pszMultIp);
	 ipmreq.imr_interface.s_addr=htons(INADDR_ANY);

	 int nLen=sizeof(ipmreq);

	 if(setsockopt(sk,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&ipmreq,sizeof(ipmreq))!=0)
	 {
		 return FALSE;
	 }

	 return TRUE;
 }

 BOOL Socket_GetSubNetMask(const char *pszIP, BYTE &b1, BYTE &b2, BYTE &b3, BYTE &b4)//获取子网掩码
 {
	 PIP_ADAPTER_INFO pAdapterInfo;
	 PIP_ADAPTER_INFO pAdapter = NULL;
	 DWORD dwRetVal = 0;

	 pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
	 unsigned long ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	 // Make an initial call to GetAdaptersInfo to get
	 // the necessary size into the ulOutBufLen variable
	 //GetAdaptersInfo 可以获得本地计算机的网络信息，从而获得该计算机的子网掩码。
	 //该函数在头文件 Iphlpapi.h.（需安装 Platform  SDK）中声明，库文件 Iphlpapi.lib。
	 if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) 
	 {
		 //GlobalFree (pAdapterInfo);
		 free(pAdapterInfo);
		 pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
	 }

	 PIP_ADAPTER_INFO pAdapterInfoOld = pAdapterInfo;
	 BOOL bFind = FALSE;

	 //获得本地计算机的网络信息函数 
	 if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	 {
		 pAdapter = pAdapterInfo;

		 while (pAdapter) 
		 {			
			 PIP_ADDR_STRING pIpAddressList = &pAdapter->IpAddressList;
			
			 while (pIpAddressList)
			 {
				 long n1,n2,n3,n4;
				 sscanf(pIpAddressList->IpMask.String, "%d.%d.%d.%d", &n1, &n2, &n3, &n4);
				 b1 = (BYTE)n1;
				 b2 = (BYTE)n2;
				 b3 = (BYTE)n3;
				 b4 = (BYTE)n4;

				 long nPos = 0;
				 const char *p = pszIP;
				 while (*p != 0)
				 {
					 if (*p == '.')
					 {
						 nPos = p - pszIP;
					 }

					 p++;
				 }

				 if (strncmp(pszIP, pIpAddressList->IpAddress.String, nPos) == 0)
				 {
					 bFind = TRUE;
					 break;
				 }

				 pIpAddressList = pIpAddressList->Next;
			 }

			if (bFind)
			{
				break;
			}

			 pAdapter = pAdapter->Next;
		 }
	 }
	 else
	 {
		 return FALSE;
	 }

	 free(pAdapterInfoOld);

	 return TRUE;
 }


void Socket_InitSocketAddr(	struct sockaddr_in &skt, const char *pszIP, long nPort)
{
	memset ( &skt,  0 , sizeof(struct sockaddr_in) ); //empty data structure 
	skt.sin_family = AF_INET;

	if (strlen(pszIP) > 7)
	{
		skt.sin_addr.S_un.S_addr=inet_addr(pszIP);//广播地址
	}
	else
	{
		skt.sin_addr.s_addr = INADDR_ANY;
	}

	skt.sin_port = htons( nPort );  //1889
}

void Socket_GetBroadcastAddr(struct sockaddr_in &skt, const char *pszIP)
{
	BYTE b1, b2, b3, b4;

	if (Socket_GetSubNetMask(pszIP, b1, b2, b3, b4))
	{
		skt.sin_addr.S_un.S_un_b.s_b4 = 255;

		if (b3 == 0)
		{
			skt.sin_addr.S_un.S_un_b.s_b3 = 255;
		}

		if (b2 == 0)
		{
			skt.sin_addr.S_un.S_un_b.s_b2 = 255;
		}

		if (b1 == 0)
		{
			skt.sin_addr.S_un.S_un_b.s_b1 = 255;
		}
	}

}
#endif

#ifndef _PSX_QT_LINUX_

//////////////////////////////////////////////////////////////////////////
#include <mstcpip.h>
BOOL Socket_SetSocketKeepAlive(SOCKET sock, long keepalivetime, long keepaliveinterval, bool onoff)
{
	BOOL bKeepAlive = TRUE;  
	int nRet = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,   
		(char*)&bKeepAlive, sizeof(bKeepAlive));  
	if (nRet == SOCKET_ERROR)  
	{ 
#ifndef _PSX_IDE_QT_
		TRACE("setsockopt failed: %d/n", WSAGetLastError()); 
#endif
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
#ifndef _PSX_IDE_QT_
		TRACE("WSAIoctl failed: %d/n", WSAGetLastError());  
#endif
		return FALSE;  
	}  

	return TRUE;
}

#endif
