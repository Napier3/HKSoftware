#include "stdafx.h"
#include "WinUdpScoket.h"
#include <net/if.h>

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
	struct sockaddr_in localaddr;                                                /*�鲥�ṹ��*/
	m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&localaddr, sizeof(localaddr));                                   /* ��ʼ��*/
	localaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0" , &localaddr.sin_addr.s_addr);
	localaddr.sin_port = htons(iPort);

	if(bind(m_hSocket, (struct sockaddr *)&localaddr, sizeof(localaddr))==SOCKET_ERROR)
		return FALSE;

	struct ip_mreqn group;
	inet_pton(AF_INET, pszMultiIP, &group.imr_multiaddr);        /*�����鲥��ĵ�ַ*/
	inet_pton(AF_INET, "0.0.0.0", &group.imr_address);      /* ��������IP �Զ�������ЧIP*/
	group.imr_ifindex = if_nametoindex("eth0");             /* ������������ת��Ϊ��Ӧ��ţ�eth0 --> ���         ����  ����:ip ad */

	int loop=0;//1-�����Է���Ϣ 0-�������Է���Ϣ
	int bRet = setsockopt(m_hSocket,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));

	bRet = setsockopt(m_hSocket, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));
	if(bRet==SOCKET_ERROR)
		return FALSE;

	bRet = setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));
	if(bRet==SOCKET_ERROR)
		return FALSE;

	CreateThead();

	return TRUE;
}

//nType=0:��ʾ���Ͷ˺ͽ��ն˱���λ��ͬһ�����ϣ� 
//nType=1:��ô���Ͷ˺ͽ��ն�λ��ͬһ��������
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
		pthread_create(&m_pThread,NULL,UdpClientThread,(LPVOID)this ); //�����߳�
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
