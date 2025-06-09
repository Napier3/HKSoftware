#include "stdafx.h"
#include "WinUdpScoket.h"

#ifdef _PSX_QT_LINUX_
#include <net/if.h>
#else
#include "ws2ipdef.h"
#endif


CWinUdpSocket::CWinUdpSocket()
{
	m_pThread = NULL;

	m_dwReceiveBuffLen = 1024;
	m_pReceiveBuff = NULL;
	SetReceiveBuffLen(1024);
}


CWinUdpSocket::~CWinUdpSocket()
{
	Close();

	while(m_pThread != NULL)
	{
		Sleep(1);
	}

	if (m_pReceiveBuff != NULL)
	{
		delete m_pReceiveBuff;
		m_pReceiveBuff = NULL;
	}
}

BOOL CWinUdpSocket::CreateServer(char *strIP, unsigned int iPort)
{
	if (!InitSocket())
	{
		return FALSE;
	}

	if (!Create(SOCK_DGRAM))
	{
		return FALSE;
	}

	return Bind(strIP, iPort);
}

BOOL CWinUdpSocket::CreateServerEx(char *strIP, unsigned int iPort)
{
	BOOL bRet = CreateServer(strIP,iPort);

	if (bRet)
	{
		CreateThead();
	}

	return bRet;
}

BOOL CWinUdpSocket::CreateClient(char *strIP, unsigned int iPort, char *strLocalIP, unsigned int iLocalPort)
{
	BOOL bRet = FALSE;

	if (!InitSocket())
	{
		return FALSE;
	}

	if (!Create(SOCK_DGRAM))
	{
		return FALSE;
	}

	if (strLocalIP != NULL)
	{
		if (strlen(strLocalIP) > 7)
		{
			if (!Bind(strLocalIP, iLocalPort))
			{
				return FALSE;
			}
		}
	}
	
	return SetRemoteIPAndPort(strIP, iPort);
}

BOOL CWinUdpSocket::CreateClientEx(char *strIP, unsigned int iPort)
{
	BOOL bRet = CreateClient(strIP,iPort);

	if (bRet)
	{
		CreateThead();
	}

	return bRet;
}

BOOL CWinUdpSocket::CreateMulticastServerEx(char *pszMultiIP,char *pszLocalIP, unsigned int iPort)
{
#ifdef _PSX_QT_LINUX_
	struct sockaddr_in localaddr;                                                /*组播结构体*/
	m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&localaddr, sizeof(localaddr));                                   /* 初始化*/
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0" , &localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(iPort);

	if(bind(m_hSocket, (struct sockaddr *)&localaddr, sizeof(localaddr))==SOCKET_ERROR)
		return FALSE;

	struct ip_mreqn group;
	inet_pton(AF_INET, pszMultiIP, &group.imr_multiaddr);        /*设置组播组的地址*/
	inet_pton(AF_INET, "0.0.0.0", &group.imr_address);      /* 本地任意IP 自动分配有效IP*/
	group.imr_ifindex = if_nametoindex("eth0");             /* 给出网卡名，转换为对应编号：eth0 --> 编号         ，，  命令:ip ad */

	int loop=0;//1-接送自发消息 0-不接收自发消息
	int bRet = setsockopt(m_hSocket,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));

	bRet = setsockopt(m_hSocket, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));
	if(bRet==SOCKET_ERROR)
		return FALSE;

	bRet = setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));
	if(bRet==SOCKET_ERROR)
		return FALSE;

#else

	if (!CreateServer(pszLocalIP, iPort))
	{
		return FALSE;
	}

	set_ReceiveTimeout(200);

	ip_mreq multiCast; 
	multiCast.imr_interface.s_addr = INADDR_ANY; 
	multiCast.imr_multiaddr.s_addr = inet_addr(pszMultiIP); 
	setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast)); 

#endif

	CreateThead();

	return TRUE;
}

//nType=0:表示发送端和接收端必须位于同一机器上， 
//nType=1:那么发送端和接收端位于同一个子网内
BOOL CWinUdpSocket::CreateMulticastClientEx(char *pszMultiIP, unsigned int iPort,int nType)
{
	BOOL bRet = FALSE;

	if (!InitSocket())
	{
		return FALSE;
	}

	if (!Create(SOCK_DGRAM))
	{
		return FALSE;
	}

	setsockopt(m_hSocket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&nType, sizeof(nType));  

	bRet = SetRemoteIPAndPort(pszMultiIP, iPort);

	if (bRet)
	{
		CreateThead();
	}

	return bRet;
}

long CWinUdpSocket::Receive(char *chReciveBuf,int nLen)
{
	if(chReciveBuf==NULL)
	{
		return SOCKET_ERROR;
	}

    SOCKLEN len=sizeof(SOCKADDR);
    int nReieve=recvfrom(m_hSocket,chReciveBuf,nLen,0,(SOCKADDR*)&m_rsockaddr,&len);

	return nReieve;
}


long CWinUdpSocket::Send(char *chSendBuf,int nLen,sockaddr_in* tsockaddr)
{
	if(chSendBuf==NULL)
	{
		return SOCKET_ERROR ;
	}

	sockaddr_in* toSockaddr = tsockaddr;

	if (toSockaddr == NULL)
	{
		toSockaddr = &m_rsockaddr;
	}

//	return sendto(m_hSocket,chSendBuf, nLen, 0,(SOCKADDR*)toSockaddr,sizeof(SOCKADDR));

	int nLeft = nLen;
	char *p = chSendBuf;
	int ntoLen = sizeof(SOCKADDR);

	while (nLeft > 0)
	{
		int nSend = sendto(m_hSocket,p, nLeft, 0,(SOCKADDR*)toSockaddr,ntoLen);

		if (nSend == SOCKET_ERROR )
		{
			set_LastError( "sendto() failed", WSAGetLastError() );
			break;
		}
		else
		{
			p += nSend;
			nLeft -= nSend;
		}
	}
	
	return nLen - nLeft;
}


BOOL CWinUdpSocket::SetRemoteIPAndPort(char *chRemoteIP,int nPort)
{
	if((chRemoteIP==NULL) || (strlen(chRemoteIP)==0))
	{
		return FALSE;
	}

	memset( &m_rsockaddr,0, sizeof( m_rsockaddr ) );
	m_rsockaddr.sin_family = AF_INET;
	m_rsockaddr.sin_addr.s_addr = inet_addr( chRemoteIP );
	m_rsockaddr.sin_port = htons( nPort );

	return TRUE;
}

long CWinUdpSocket::OnReceive(BYTE *pRcvBuf, int iLen,sockaddr_in* fsockaddr)
{
	return 0;
}

void CWinUdpSocket::OnClose(int nErrorCode)
{

}

void CWinUdpSocket::SetReceiveBuffLen(DWORD dwLen)
{
	m_dwReceiveBuffLen = dwLen;

	if (m_pReceiveBuff != NULL)
	{
		delete m_pReceiveBuff;
	}

	m_pReceiveBuff = new BYTE[m_dwReceiveBuffLen+10];
	ZeroMemory(m_pReceiveBuff, m_dwReceiveBuffLen*sizeof(BYTE));
}

void CWinUdpSocket::CreateThead()
{
	if (m_pThread == NULL)
	{
#ifdef _PSX_QT_LINUX_
		pthread_create(&m_pThread,NULL,UdpClientThread,(LPVOID)this ); //创建线程
#else
		m_pThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)UdpClientThread,(LPVOID)this,0,NULL);
#endif
	}
}

#ifdef _PSX_QT_LINUX_
void *UdpClientThread(LPVOID pData)
#else
UINT UdpClientThread(LPVOID pData)
#endif
{
	CWinUdpSocket *pSocket = (CWinUdpSocket*)pData;
	pSocket->InitSocket();

	int numrcv;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
    SOCKLEN len=sizeof(SOCKADDR);
	sockaddr_in fsockaddr;

	while (1)
	{
		if (pSocket->m_hSocket == NULL)
		{
			break;
		}

		numrcv=recvfrom(clientSocket,buffer,dwReceiveBuffLen,0,(SOCKADDR*)&fsockaddr,&len);

		if (numrcv == SOCKET_ERROR)
		{
			if (pSocket->IsSocketClose())
			{
				pSocket->Close();
			}

			Sleep(1);
			continue;
		}

		if (numrcv == 0)
		{
			if (pSocket->IsSocketClose())
			{
				pSocket->Close();
				break;
			}

			Sleep(1);
			continue;
		}

		pSocket->OnReceive((BYTE*)buffer, numrcv,&fsockaddr);
	}

	pSocket->m_pThread = NULL;
	pSocket->OnClose(0);

	return 0;
}
