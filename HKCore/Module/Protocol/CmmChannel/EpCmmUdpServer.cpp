#include "StdAfx.h"
#include "EpCmmUdpServer.h"
#include "EpCmmChannelCreateMngr.h"
#include "..\..\Socket\WinUdpScoket.h"

CEpCmmUdpServer::CEpCmmUdpServer(void)
{
	m_bNeedSend = FALSE;
	m_bExitThread = FALSE;
	m_nReceiveLen = 0;
}

CEpCmmUdpServer::~CEpCmmUdpServer(void)
{
	m_bExitThread = TRUE;
}


BOOL CEpCmmUdpServer::CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort)
{
	m_strIP = strIP;
	m_nPort = nPort;
	m_strMulticastIP = strBoardcastIP;
	m_nMulticastPort = nMulticastPort;
	m_oReceiveByffer.FreeBuffer();
	m_oReceiveByffer.SetBufferLength(1048576);
	m_bExitThread = FALSE;
	m_pThread = AfxBeginThread(UdpServerThread,this);
	m_pThread->m_bAutoDelete = TRUE;

	return TRUE;
}

BOOL CEpCmmUdpServer::CreateServer()
{
	return FALSE;
}

BOOL CEpCmmUdpServer::CloseServer(CExBaseObject *pChannel)
{
	m_bExitThread = TRUE;
	POS pos = CExBaseList::Find(pChannel);

	if (pos != NULL)
	{
		RemoveAt(pos);
	}

	if (GetCount() == 0)
	{
		m_bExitThread = TRUE;
	}

	return TRUE;
}


BOOL CEpCmmUdpServer::IsServerClosed()
{
	if (m_pThread != NULL)
	{
		return FALSE;
	}

	return TRUE;
}

//UDP�������˽��ܺ���
//���ݴ����m_oReceiveBuffer��
//�յ����ݵ���OnReceive
UINT CEpCmmUdpServer::UdpServerThread(LPVOID pParam)
{
	if (! Ep_InitWinSocket() )
	{
		return 0;
	}

	SOCKET hSocket;
	char pszIP[60];
	CEpCmmUdpServer *pUdpServer = (CEpCmmUdpServer*)pParam;

	struct sockaddr_in local;
	struct sockaddr_in from;
	struct sockaddr_in sendAddr;
	int fromlen =sizeof(from);
	local.sin_family=AF_INET;
	local.sin_port=htons(pUdpServer->m_nPort);             ///�����˿�

	if (pUdpServer->m_strIP.GetLength() >= 7)
	{//ָ��IP��ַ
		CString_to_char(pUdpServer->m_strIP, pszIP);
		local.sin_addr.s_addr =  inet_addr(pszIP);       ///����
	}
	else
	{//��ָ��IP��ַ
		local.sin_addr.s_addr = INADDR_ANY;       ///����
	}

	hSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	int ms = 200;
	
	if( setsockopt( hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	{
		CLogPrint::LogString(LOGLEVEL_WARNING, _T("setsockopt() failed"));
	}

	bind(hSocket,(struct sockaddr*)&local,sizeof local);
	char *pReceiveBuffer = (char*)(pUdpServer->m_oReceiveByffer.GetBuffer());

	//////////////////////////////////////////////////////////////////////////
	//�鲥��ַ����
	CString_to_char(pUdpServer->m_strMulticastIP, pszIP);
	sockaddr_in sktMultiCast;
	sktMultiCast.sin_family = AF_INET;

	if (strlen(pszIP) >= 7)
	{
		if(!Socket_JoinLeaf(pszIP, hSocket))
		{//�����鲥
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("UDP server[%s %d] join board cast [%s] failed")
				, pUdpServer->m_strIP, pUdpServer->m_nPort, pUdpServer->m_strMulticastIP);
		}

		sktMultiCast.sin_addr.s_addr = inet_addr(pszIP);
		sktMultiCast.sin_port = htons( pUdpServer->m_nMulticastPort );  //1889
	}

	//////////////////////////////////////////////////////////////////////////
	//�㲥��ַ����
	CString_to_char(pUdpServer->m_strIP, pszIP);

	sockaddr_in sktBroadCast;
	sktBroadCast.sin_family = AF_INET;
	sktBroadCast.sin_addr.S_un.S_addr=inet_addr(pszIP);//�㲥��ַ
	sktBroadCast.sin_addr.S_un.S_un_b.s_b4 = 255;
	BYTE b1, b2, b3, b4;
	
	if (Socket_GetSubNetMask(b1, b2, b3, b4))
	{
		if (b3 == 0)
		{
			//sktBroadCast.sin_addr.S_un.S_un_b.s_b3 = 255;
		}
	}

	//m_nMulticastPort��Ϊ�豸�Ķ˿ڣ�Ŀǰû�п����鲥���㲥ͬʱ���ڵĿ����ԣ�����ʹ��ͬһ���˿�
	sktBroadCast.sin_port=htons(pUdpServer->m_nMulticastPort); 

	ASSERT (pReceiveBuffer != NULL);
	long nBufferLen = pUdpServer->m_oReceiveByffer.GetBufferLength();

	while (1)
	{
		if (pUdpServer->m_bExitThread)
		{
			break;
		}

		pUdpServer->m_nReceiveLen = recvfrom(hSocket, pReceiveBuffer,nBufferLen, 0, (struct sockaddr*)&from, &fromlen);
	
		if (pUdpServer->m_nReceiveLen != SOCKET_ERROR)
		{
			CEpCmmRcvSndTime *pEpCmmTime = new CEpCmmRcvSndTime();
			pEpCmmTime->InitTime();
			pUdpServer->OnReceive(pEpCmmTime, &from);
		}
		
		CEpFrameBase *pSend = (CEpFrameBase*)pUdpServer->GetFrameSend();

		if (pSend != NULL)
		{//����Ҫ���͵ı���
			CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
			char *pBuffer = (char*)pCycleBuffer->GetBuffer();
			long nLen = pCycleBuffer->GetDataLength();

			if (pSend->IsChModeMultiCast())
			{
				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sktMultiCast,sizeof(SOCKADDR));
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Multicast:%08x %d"), sktMultiCast.sin_addr.S_un.S_addr, sktMultiCast.sin_port);
			}
			else if (pSend->IsChModeToPoint())
			{
				sendAddr = ((CEpCmmUdpServerChannel*)pSend->m_pChannel)->m_oSocketAddrIn;
				if (pUdpServer->m_nMulticastPort > 0)
				{
					sendAddr.sin_port = htons( pUdpServer->m_nMulticastPort ); 
				}
				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sendAddr,sizeof(SOCKADDR));
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Point:%08x %d"), sendAddr.sin_addr.S_un.S_addr, sendAddr.sin_port);
			}
			else if (pSend->IsChModeBroadCast())
			{
				if (pUdpServer->m_nMulticastPort > 0)
				{
					sktBroadCast.sin_port = htons( pUdpServer->m_nMulticastPort ); 
					CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Broadcast:%08x %d"), sktBroadCast.sin_addr.S_un.S_addr, pUdpServer->m_nMulticastPort);
				}
				else
				{
					CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Broadcast:%08x %d"), sktBroadCast.sin_addr.S_un.S_addr, sktBroadCast.sin_port);
				}

				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sktBroadCast,sizeof(SOCKADDR));
			}
			else
			{//ȱʡ����Ϊ��Ե㷽ʽ
				sendAddr = ((CEpCmmUdpServerChannel*)pSend->m_pChannel)->m_oSocketAddrIn;
				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sendAddr,sizeof(SOCKADDR));
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Point:%08x %d"), sendAddr.sin_addr.S_un.S_addr, sendAddr.sin_port);
			}

			if (nLen == SOCKET_ERROR)
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("��\"%s\"���ͱ���ʧ��"), pUdpServer );
			
				//����ʧ�ܴ���
			}
			else
			{
				pSend->LogAndRecordProtocol();
				pUdpServer->RemoveHead();
			}
		}

		if (pUdpServer->m_bExitThread)
		{
			break;
		}
	}

	closesocket(hSocket);

	CMM_SetAllSendPkgState(&(pUdpServer->m_listPkgSend));
	pUdpServer->m_pThread = NULL;

	return 0;
}

//���ҹ�����UDP�ͻ��ˣ�û���򴴽�
//�����ݸ��Ƹ�UDP�ͻ���
//�ٵ���UDP�ͻ��˵���غ���
void CEpCmmUdpServer::OnReceive(CEpCmmRcvSndTime *pEpCmmTime, struct sockaddr_in *pSckAddr, long nPos1Begin , long nPos1End, long nPos2Begin, long nPos2End)
{
	//�����������ӵ�CEpCmmUdpServerChannel
	CEpCmmUdpServerChannel *pChannel = Find(pSckAddr);

	if (pChannel == NULL)
	{
		//û���ҵ������ҵ�һ��û�����ӵ�CEpCmmUdpServerChannel
		//�������Ӳ���
		/*pChannel = FindFirstUnConnected();
		ASSERT (pChannel != NULL);*/

		if (GetCount() > 0)
		{
			pChannel = (CEpCmmUdpServerChannel*)GetHead();
			pChannel->OnServerAccept(pSckAddr);
		}
	}

	if (pChannel != NULL && (GetCount() > 0) )
	{
		BYTE *pReceiveBuffer = (BYTE*)(m_oReceiveByffer.GetBuffer());
		pChannel->AppendRcvBuffer(pReceiveBuffer, m_nReceiveLen, pEpCmmTime);
		pChannel->OnChannelReceive(pEpCmmTime);
	}
}


CEpCmmUdpServerChannel* CEpCmmUdpServer::Find(struct sockaddr_in *pSckAddr)
{
	POS pos = GetHeadPosition();
	CEpCmmUdpServerChannel *pChannel = NULL;
	CEpCmmUdpServerChannel *pFind = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();
		//ASSERT (nClassID != CMMCLASSID_UDP_SERVER_CHANNEL);
		pChannel = (CEpCmmUdpServerChannel*)p;

		//�ж�IP��ַ�Ͷ˿��Ƿ�һ��
		if (pChannel->m_oSocketAddrIn.sin_port == pSckAddr->sin_port
			&& pChannel->m_oSocketAddrIn.sin_addr.S_un.S_addr == pSckAddr->sin_addr.S_un.S_addr)
		{
			pFind = pChannel;
			break;
		}
	}

	return pFind;
}

CEpCmmUdpServerChannel* CEpCmmUdpServer::FindFirstUnConnected()
{
	POS pos = GetHeadPosition();
	CEpCmmUdpServerChannel *pChannel = NULL;
	CEpCmmUdpServerChannel *pFind = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();
		ASSERT (nClassID != EPCMMCLASSID_UDP_SERVER_CHANNEL);
		pChannel = (CEpCmmUdpServerChannel*)p;

		//�ж�IP��ַ�Ͷ˿��Ƿ�һ��
		if (!pChannel->IsConnectSuccessful())
		{
			pFind = pChannel;
			break;
		}
	}

	return pFind;
}

void CEpCmmUdpServer::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	m_listPkgSend.AddTail(pPkgSend);

	oLock.Free();
}

CExBaseObject* CEpCmmUdpServer::GetFrameSend()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	CExBaseObject* pPkgSend = m_listPkgSend.GetHead();

	oLock.Free();
	return pPkgSend;
}


void CEpCmmUdpServer::RemoveHead()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	long nIndex = 0;
	m_listPkgSend.RemoveAt(nIndex);
	oLock.Free();
}