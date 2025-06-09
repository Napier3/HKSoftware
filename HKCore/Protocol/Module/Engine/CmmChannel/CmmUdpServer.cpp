#include "StdAfx.h"
#include "CmmUdpServer.h"
#include "../PpPackageSend.h"
#include "CmmChannelCreateMngr.h"
#include "../../../../Module/Socket/WinUdpScoket.h"
#include "../../XLanguageResourcePp.h"
#include "CmmGlobalDefine_Socket.h"

CCmmUdpServer::CCmmUdpServer(void)
{
	m_bNeedSend = FALSE;
	m_bExitThread = FALSE;
	m_nReceiveLen = 0;
	m_pThread = NULL;
}

CCmmUdpServer::~CCmmUdpServer(void)
{
	m_bExitThread = TRUE;
}


BOOL CCmmUdpServer::CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort)
{
	m_strIP = strIP;
	m_nPort = nPort;
	m_strMulticastIP = strBoardcastIP;
	m_nMulticastPort = nMulticastPort;
	m_bExitThread = FALSE;

	if (m_pThread == NULL)
	{
		m_oReceiveByffer.FreeBuffer();
		m_oReceiveByffer.SetBufferLength(1048576);
		m_pThread = AfxBeginThread(UdpServerThread,this);
		m_pThread->m_bAutoDelete = TRUE;
	}

	return TRUE;
}

BOOL CCmmUdpServer::CreateServer()
{
	return FALSE;
}

BOOL CCmmUdpServer::CloseServer(CExBaseObject *pChannel)
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


BOOL CCmmUdpServer::IsServerClosed()
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
UINT CCmmUdpServer::UdpServerThread(LPVOID pParam)
{
	if (! InitWinSocket() )
	{
		return 0;
	}

	SOCKET hSocket;
	CCmmUdpServer *pUdpServer = (CCmmUdpServer*)pParam;
	char *pReceiveBuffer = (char*)(pUdpServer->m_oReceiveByffer.GetBuffer());

	char pszLocalIP[1024]="\0";
	char pszMulticastIP[1024]="\0";
	CString_to_char(pUdpServer->m_strIP, pszLocalIP);
	CString_to_char(pUdpServer->m_strMulticastIP, pszMulticastIP);

	struct sockaddr_in sktLocal;
	struct sockaddr_in from;
	struct sockaddr_in sendAddr;
	int fromlen =sizeof(from);

	Socket_InitSocketAddr(sktLocal, pszLocalIP, pUdpServer->m_nPort);

	hSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	int ms = 200;
	
	if( setsockopt( hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	{
		CLogPrint::LogString(XLOGLEVEL_WARNING, _T("setsockopt() failed"));
	}

	bind(hSocket,(struct sockaddr*)&sktLocal,sizeof sktLocal);

	//////////////////////////////////////////////////////////////////////////
	//�鲥��ַ����
	sockaddr_in sktMultiCast;
	sktMultiCast.sin_family = AF_INET;

	if (strlen(pszMulticastIP) > 7)
	{
		if(!Socket_JoinLeaf(pszMulticastIP, hSocket))
		{//�����鲥
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("UDP server[%s %d] join board cast [%s] failed")
				, pUdpServer->m_strIP, pUdpServer->m_nPort, pUdpServer->m_strMulticastIP);
		}

		Socket_InitSocketAddr(sktMultiCast, pszMulticastIP, pUdpServer->m_nMulticastPort);
	}

	//////////////////////////////////////////////////////////////////////////
	//�㲥��ַ����
	//m_nMulticastPort��Ϊ�豸�Ķ˿ڣ�Ŀǰû�п����鲥���㲥ͬʱ���ڵĿ����ԣ�����ʹ��ͬһ���˿�
	sockaddr_in sktBroadCast;
	Socket_InitSocketAddr(sktBroadCast, pszLocalIP, pUdpServer->m_nMulticastPort);	
	Socket_GetBroadcastAddr(sktBroadCast, pszLocalIP);

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
			LogReceivePackage(pUdpServer->m_pszPpLogProtocol, (BYTE*)pReceiveBuffer, pUdpServer->m_nReceiveLen);
			CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
			pCmmTime->InitTime();
			pUdpServer->OnReceive(pCmmTime, &from);
		}
		
		CPpPackageSend *pSend = (CPpPackageSend*)pUdpServer->GetPackageSend();

		if (pSend != NULL)
		{//����Ҫ���͵ı���
			char *pBuffer = (char*)pSend->m_oBuffer.GetBuffer();
			long nLen = pSend->m_oBuffer.GetDataLength();

			if (pSend->IsChCmmModeMultiCast())
			{
				if (pUdpServer->m_nMulticastPort > 0)
				{
					sktBroadCast.sin_port = htons( pUdpServer->m_nMulticastPort ); 
				}

				BOOL bEnable = FALSE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sktMultiCast,sizeof(SOCKADDR));
			}
			else if (pSend->IsChCmmModeBroadCast())
			{
				if (pUdpServer->m_nMulticastPort > 0)
				{
					sktBroadCast.sin_port = htons( pUdpServer->m_nMulticastPort ); 
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"UDP Broadcast:%08x %d", sktBroadCast.sin_addr.S_un.S_addr, pUdpServer->m_nMulticastPort);
				}
				else
				{
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"UDP Broadcast:%08x %d", sktBroadCast.sin_addr.S_un.S_addr, sktBroadCast.sin_port);
				}
				
				BOOL bEnable = TRUE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sktBroadCast,sizeof(SOCKADDR));
			}
			else
			{//ȱʡ����Ϊ��Ե㷽ʽ
				BOOL bEnable = FALSE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				sendAddr = ((CCmmUdpServerChannel*)pSend->m_pChannel)->m_oSocketAddrIn;
		
				if (pUdpServer->m_nMulticastPort > 0)
				{//Զ�̶˿�
					sendAddr.sin_port = htons( pUdpServer->m_nMulticastPort ); 
				}

				nLen = sendto(hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sendAddr,sizeof(SOCKADDR));
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"UDP Point:%08x %d", sendAddr.sin_addr.S_un.S_addr, sendAddr.sin_port);
			}

			if (nLen == SOCKET_ERROR)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SendMessageFail/*L"��\"%s\"���ͱ���ʧ��"*/, pUdpServer );
			
				//����ʧ�ܴ���
				///???????????????????????????????
				pSend->SetSendState(TRUE);
				pSend->LogAndRecordProtocol();
				pSend->m_pChannel->m_dwConnectState = CONNECT_STATE_NORMAL;
				pUdpServer->RemoveHead();
			}
			else
			{
				pSend->SetSendState(TRUE);
				pSend->LogAndRecordProtocol();
				pUdpServer->RemoveHead();
			}
		}

		if (pUdpServer->m_bExitThread)
		{
			break;
		}
		Sleep(5);
	}

	closesocket(hSocket);

	CMM_SetAllSendPkgState(&(pUdpServer->m_listPkgSend));
	pUdpServer->m_pThread = NULL;

	return 0;
}

//���ҹ�����UDP�ͻ��ˣ�û���򴴽�
//�����ݸ��Ƹ�UDP�ͻ���
//�ٵ���UDP�ͻ��˵���غ���
void CCmmUdpServer::OnReceive(CCmmRcvSndTime *pCmmTime, struct sockaddr_in *pSckAddr, long nPos1Begin , long nPos1End, long nPos2Begin, long nPos2End)
{
	//�����������ӵ�CCmmUdpServerChannel
	CCmmUdpServerChannel *pChannel = Find(pSckAddr);

	if (pChannel == NULL)
	{
		//û���ҵ������ҵ�һ��û�����ӵ�CCmmUdpServerChannel
		//�������Ӳ���
		/*pChannel = FindFirstUnConnected();
		ASSERT (pChannel != NULL);*/

		if (GetCount() > 0)
		{
			pChannel = (CCmmUdpServerChannel*)GetHead();
			pChannel->OnServerAccept(pSckAddr);
		}
	}

	if (pChannel != NULL && (GetCount() > 0) )
	{
		pChannel->ResetOffsetDataFillBeginPosition();

		BYTE *pReceiveBuffer = (BYTE*)(m_oReceiveByffer.GetBuffer());
		pChannel->AppendRcvBuffer(pReceiveBuffer, m_nReceiveLen, pCmmTime);
		pChannel->OnChannelReceive(pCmmTime);
	}
}


CCmmUdpServerChannel* CCmmUdpServer::Find(struct sockaddr_in *pSckAddr)
{
	POS pos = GetHeadPosition();
	CCmmUdpServerChannel *pChannel = NULL;
	CCmmUdpServerChannel *pFind = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();
		//ASSERT (nClassID != CMMCLASSID_UDP_SERVER_CHANNEL);
		pChannel = (CCmmUdpServerChannel*)p;

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

CCmmUdpServerChannel* CCmmUdpServer::FindFirstUnConnected()
{
	POS pos = GetHeadPosition();
	CCmmUdpServerChannel *pChannel = NULL;
	CCmmUdpServerChannel *pFind = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();
		ASSERT (nClassID != CMMCLASSID_UDP_SERVER_CHANNEL);
		pChannel = (CCmmUdpServerChannel*)p;

		//�ж�IP��ַ�Ͷ˿��Ƿ�һ��
		if (!pChannel->IsConnectSuccessful())
		{
			pFind = pChannel;
			break;
		}
	}

	return pFind;
}

void CCmmUdpServer::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	m_listPkgSend.AddTail(pPkgSend);

	oLock.Free();
}

CExBaseObject* CCmmUdpServer::GetPackageSend()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	CExBaseObject* pPkgSend = m_listPkgSend.GetHead();
	oLock.Free();
	return pPkgSend;
}


void CCmmUdpServer::RemoveHead()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	long nIndex = 0;
	m_listPkgSend.RemoveAt(nIndex);
	oLock.Free();
}