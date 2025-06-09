#include "stdafx.h"
#include "WinUdpScoket.h"

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

BOOL CWinUdpSocket::CreateMulticastServerEx(char *pszMultiIP,char *pszLocalIP,unsigned int iPort)
{
	if (!CreateServer(pszLocalIP, iPort))
	{
		return FALSE;
	}

	ip_mreq multiCast; 
    multiCast.imr_interface.s_addr = INADDR_ANY;
    multiCast.imr_multiaddr.s_addr = inet_addr(pszMultiIP);

	setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast)); 

	CreateThead();

	return TRUE;
}

//nType=0:表示发送端和接收端必须位于同一机器上， 
//nType=1:那么发送端和接收端位于同一个子网内
BOOL CWinUdpSocket::CreateMulticastClientEx(char *pszMultiIP, unsigned int iPort,int nType)
{
	BOOL bRet = FALSE;

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

    socklen_t  len=sizeof(SOCKADDR);
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
         pthread_create(&m_pThread,NULL,UdpClientThread,(LPVOID)this ); //创建线程
	}
}

void *UdpClientThread(LPVOID pData)
{
	int numrcv;
	CWinUdpSocket *pSocket = (CWinUdpSocket*)pData;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
    socklen_t  len=sizeof(SOCKADDR);
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
