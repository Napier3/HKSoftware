#include "StdAfx.h"
#include "EpCmmUdpClientChannel.h"
#include "EpDeviceCmmChannel.h"

#include "..\..\Socket\WinUdpScoket.h"

CEpCmmUdpClientChannel::CEpCmmUdpClientChannel(void)
{
	m_bNeedSend = FALSE;
	m_pConfig = NULL;
	m_pThread = NULL;
	m_bExitThread = FALSE;
}

CEpCmmUdpClientChannel::~CEpCmmUdpClientChannel(void)
{
	m_bExitThread = TRUE;

// 	DWORD dwData = ::WaitForSingleObject(m_pThread->m_hThread, 5000/*INFINITE*/);
// 	if(WAIT_OBJECT_0  == dwData)
// 	{
// 		m_pThread = NULL;
// 		return;
// 	}	

	//m_oCycleMemBufferPosMngr.DeleteAll();
}

//UDP客户端函数
UINT CEpCmmUdpClientChannel::UdpClientThread(LPVOID pParam)
{
	CWinUdpSoket oUdpSocket;
	CEpCmmUdpClientChannel *pUdpClientChannel = (CEpCmmUdpClientChannel*)pParam;
	char pBuffer[1024]="\0";
	char pBufferEx[1024]="\0";
	BOOL bSendSuc = TRUE;
	CEpCmmUdpConfig *pConfig = pUdpClientChannel->m_pConfig;
	CString_to_char(pConfig->m_strRemoteIP, pBuffer);
	CString_to_char(pConfig->m_strLocalIP, pBufferEx);
	oUdpSocket.CreateClient(pBuffer ,pConfig->m_nRemotePort, pBufferEx, pConfig->m_nLocalPort);
	oUdpSocket.set_ReceiveTimeout(pConfig->m_nReceiveTimeout);
	oUdpSocket.set_SendTimeout(pConfig->m_nSendTimeout);
	long nLen = 0;
	
	//////////////////////////////////////////////////////////////////////////
	//组播地址定义
	CString_to_char(pConfig->m_strMulticastIP, pBuffer);
	sockaddr_in sktMultiCast;
	sktMultiCast.sin_family = AF_INET;

	if (strlen(pBuffer) >= 7)
	{
		if(!Socket_JoinLeaf(pBuffer, oUdpSocket.m_hSocket))
		{//加入组播
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("UDP  join board cast [%s] failed"),  pConfig->m_strMulticastIP);
		}

		sktMultiCast.sin_addr.s_addr = inet_addr(pBuffer);
		sktMultiCast.sin_port = htons( pConfig->m_nMulticastPort );  //1889
	}

	//////////////////////////////////////////////////////////////////////////
	//广播地址定义
	CString_to_char(pConfig->m_strRemoteIP, pBuffer);
	
	sockaddr_in sktBroadCast;
	sktBroadCast.sin_family = AF_INET;
	sktBroadCast.sin_addr.S_un.S_addr=inet_addr(pBuffer);//广播地址
	sktBroadCast.sin_addr.S_un.S_un_b.s_b4 = 255;
	sktBroadCast.sin_port=htons(pConfig->m_nRemotePort); 
	BYTE b1, b2, b3, b4;
	BOOL bEnable = 1;

	if (pConfig->m_nUseBroadcast == 1)
	{
		setsockopt(oUdpSocket.m_hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
	}

	if (Socket_GetSubNetMask(b1, b2, b3, b4))
	{
	
	}

	while (TRUE)
	{
 		CEpFrameBase *pSend = (CEpFrameBase*)pUdpClientChannel->GetFrameSend();
 		
 		if (pSend != NULL)
 		{//有需要发送的报文
			CCycleMemBuffer *pCycleBuffer = pSend->m_pBuffer;
			char *pBuffer = (char*)pCycleBuffer->GetBuffer();
			long nLen = pCycleBuffer->GetDataLength();
			pSend->InitTime();

			if (pSend->IsChModeMultiCast())
			{
				nLen = sendto(oUdpSocket.m_hSocket,pBuffer, nLen, 0,(SOCKADDR*)&sktMultiCast,sizeof(SOCKADDR));
				bSendSuc = (nLen > 0);
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("UDP Multicast:%08x %d"), sktMultiCast.sin_addr.S_un.S_addr, sktMultiCast.sin_port);
			}
			else if (pSend->IsChModeBroadCast())
			{
				//nLen = sendto(oUdpSocket.m_hSocket, pBuffer, nLen, 0,(SOCKADDR*)&sktBroadCast,sizeof(SOCKADDR));
				//bSendSuc = (nLen > 0);
				nLen = oUdpSocket.Send(pBuffer, nLen);
				bSendSuc = (nLen > 0);
			}
			else
			{
				nLen = oUdpSocket.Send(pBuffer, nLen);
				bSendSuc = (nLen > 0);

				if (!bSendSuc)
				{
					CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("向\"%s\"发送报文失败"), pUdpClientChannel );
				}
			}
			
			if (bSendSuc)
			{
				pSend->LogAndRecordProtocol();
				pUdpClientChannel->RemoveHead();
			}
		}
		else
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			nLen = oUdpSocket.Receive(pUdpClientChannel->m_pReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);

			if (nLen != SOCKET_ERROR)
			{
				CEpCmmRcvSndTime *pEpCmmTime = new CEpCmmRcvSndTime();
				pEpCmmTime->InitTime(tm);
				pUdpClientChannel->AppendRcvBuffer((BYTE*)pUdpClientChannel->m_pReceiveBuffer, nLen, pEpCmmTime);
				pUdpClientChannel->OnChannelReceive(pEpCmmTime);
			}
		}

		if (pUdpClientChannel->m_bExitThread)
		{
			break;
		}

		Sleep(50);
	}

	oUdpSocket.Close();
	CMM_SetAllSendPkgState(pUdpClientChannel);
	pUdpClientChannel->m_pThread = NULL;

	return 0;
}

BOOL CEpCmmUdpClientChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CEpCmmUdpConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CEpCmmUdpClientChannel::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	m_nSendIndex++;
	CEpCmmChannel::Send(pPkgSend);
	oLock.Free();
}


BOOL CEpCmmUdpClientChannel::Connect()
{
	// 启动Socket
	m_bExitThread = FALSE;
	m_pThread = AfxBeginThread(UdpClientThread,this);
	m_pThread->m_bAutoDelete = TRUE;
	
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//启动OnConnect定义的过程
	CEpDeviceCmmChannel *pEpDeviceCmmChannel = (CEpDeviceCmmChannel*)GetParent();
	
	POS pos = m_pConfig->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	while (pos != NULL)
	{
		pObj = m_pConfig->GetNext(pos);
// 		if (pObj != NULL && pObj->GetClassID() == EPCLASSID_CMM_ONCONNECT)
// 		{
// 			((CEpEngineThread*)pEpDeviceCmmChannel->m_pThread)->RunProcedure(((CEpCmmOnConnect*)pObj)->m_strText, NULL);
// 		}
	}

	OnConnectFinished();
	return TRUE;
}

BOOL CEpCmmUdpClientChannel::DisConnect()
{
	m_bExitThread = TRUE;
	return TRUE;
}


BOOL CEpCmmUdpClientChannel::IsConnectSuccessful()
{
	return CEpCmmChannel::IsConnectSuccessful();
}


BOOL CEpCmmUdpClientChannel::IsEpCmmChannelExit()
{
	return (m_pThread == NULL);
}

