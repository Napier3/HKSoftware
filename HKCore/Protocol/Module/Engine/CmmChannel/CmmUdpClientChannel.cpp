#include "StdAfx.h"
#include "CmmUdpClientChannel.h"
#include "../PpPackageSend.h"
#include "DeviceCmmChannel.h"
#include "../PpEngineThreadBase.h"

#include "../../../../Module/Socket/WinUdpScoket.h"
#include "../DeviceModel/CmmOnConnect.h"
#include "../../XLanguageResourcePp.h"
#include "CmmGlobalDefine_Socket.h"

#ifdef _PSX_QT_LINUX_
#include <net/if.h>
#else
#include "ws2ipdef.h"
#endif


CCmmUdpClientChannel::CCmmUdpClientChannel(void)
{
	m_bNeedSend = FALSE;
	m_pConfig = NULL;
	m_pThread = NULL;
	m_bExitThread = FALSE;
}

CCmmUdpClientChannel::~CCmmUdpClientChannel(void)
{
	m_bExitThread = TRUE;
}



void CCmmUdpClientChannel::CreateThead()
{
	if (m_pThread == NULL)
	{
#ifdef _PSX_QT_LINUX_
		pthread_create(&m_pThread,NULL,cmm_UdpClientThread,(LPVOID)this ); //创建线程
#else
		m_pThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)cmm_UdpClientThread,(LPVOID)this,0,NULL);
#endif
	}
}

//UDP客户端函数
#ifdef _PSX_QT_LINUX_
void* cmm_UdpClientThread(LPVOID pParam)
#else
UINT cmm_UdpClientThread(LPVOID pParam)
#endif
{
	if (! InitWinSocket() )
	{
		CLogPrint::LogString(XLOGLEVEL_WARNING, _T("InitWinSocket() failed"));
		return 0;
	}

	CCmmUdpClientChannel *pUdpClientChannel = (CCmmUdpClientChannel*)pParam;
	CCmmUdpClientConfig *pConfig = pUdpClientChannel->m_pConfig;
	char pszRemoteIP[1024]="\0";
	char pszLocalIP[1024]="\0";
	char pszMulticastIP[1024]="\0";
	BOOL bSendSuc = TRUE;
	long nLen = 0;
	SOCKET hSocket;
	int ms = 200;

	CString_to_char(pConfig->m_strRemoteIP, pszRemoteIP);
	CString_to_char(pConfig->m_strLocalIP, pszLocalIP);
	CString_to_char(pConfig->m_strMulticastIP, pszMulticastIP);
	hSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	if( setsockopt( hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof( ms ) ) == SOCKET_ERROR )
	{
		CLogPrint::LogString(XLOGLEVEL_WARNING, _T("setsockopt() failed"));
	}

	struct sockaddr_in sktLocal;
	struct sockaddr_in sktBroadCast;
	struct sockaddr_in sktRemote;
	struct sockaddr_in sktReceive;
	sockaddr_in sktMultiCast;
	BOOL bEnable = 1;

	 ///本机
	Socket_InitSocketAddr(sktLocal, pszLocalIP, CmmCfg_GetPort(pConfig->m_nLocalPort));
	bind(hSocket,(struct sockaddr*)&sktLocal,sizeof(sktLocal) );

	//组播地址定义
	if (strlen(pszMulticastIP) > 7)
	{
		if(!Socket_JoinLeaf(pszMulticastIP, hSocket))
		{//加入组播
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("UDP  join board cast [%s] failed"),  pConfig->m_strMulticastIP.GetString());
		}

		Socket_InitSocketAddr(sktMultiCast, pszMulticastIP, pConfig->m_nMulticastPort);
	}

	//广播地址定义
	Socket_InitSocketAddr(sktBroadCast, pszRemoteIP, pConfig->m_nRemotePort);	
	Socket_GetBroadcastAddr(sktBroadCast, pszRemoteIP);

	Socket_InitSocketAddr(sktRemote, pszRemoteIP, pConfig->m_nRemotePort);	//远程地址定义
	Socket_InitSocketAddr(sktReceive, pszRemoteIP, pConfig->m_nRemotePort);
	DWORD dwLastSendTick = ::GetTickCount();

	while (TRUE)
	{
 		CPpPackageSend *pSend = (CPpPackageSend*)pUdpClientChannel->GetPackageSend();
 		
 		if (pSend != NULL)
 		{//有需要发送的报文
			DWORD dwCurrTick = ::GetTickCount();
			dwCurrTick -= dwLastSendTick;

			if ( dwCurrTick < 50)
			{
				Sleep(50);
			}

			dwLastSendTick = ::GetTickCount();

			char *pBuffer = (char*)pSend->m_oBuffer.GetBuffer();
			long nLen = pSend->m_oBuffer.GetDataLength();
			pSend->m_pPackageDetail->InitPackageTime();

			if (pSend->IsChCmmModeMultiCast())
			{
				bEnable = FALSE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				nLen = sendto(hSocket, pBuffer, nLen, 0, (SOCKADDR*)&sktMultiCast, sizeof(SOCKADDR));
				bSendSuc = (nLen > 0);
			}
			else if (pSend->IsChCmmModeBroadCast())
			{
				bEnable = TRUE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				nLen = sendto(hSocket, pBuffer, nLen, 0,(SOCKADDR*)&sktBroadCast,sizeof(SOCKADDR));
				bSendSuc = (nLen > 0);
			
				if (!bSendSuc)
				{
#ifdef NOT_USE_XLANGUAGE
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "向\"%s\"发送BroadCast报文失败", pUdpClientChannel->m_strID.GetString() );
#else
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SendMessageFail2/*L"向\"%s\"发送BroadCast报文失败"*/, pUdpClientChannel->m_strID.GetString() );
#endif
				}
			}
			else
			{
				bEnable = FALSE;
				setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
				nLen = sendto(hSocket, pBuffer, nLen, 0, (SOCKADDR*)&sktRemote, sizeof(SOCKADDR));
				bSendSuc = (nLen > 0);

				if (!bSendSuc)
				{
#ifdef NOT_USE_XLANGUAGE
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "向\"%s\"发送报文失败", pUdpClientChannel->m_strID.GetString() );
#else
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SendMessageFail/*L"向\"%s\"发送报文失败"*/, pUdpClientChannel->m_strID.GetString() );
#endif
					pUdpClientChannel->m_dwConnectState = CONNECT_STATE_NORMAL;
				}
			}
			
			if (bSendSuc)
			{
				pSend->SetSendState(TRUE);
				pSend->LogAndRecordProtocol();
				pUdpClientChannel->RemoveHead();
			}
			else
			{
				pSend->m_nSendtimes++;

				if (pSend->m_nSendtimes > 3)
				{
					pUdpClientChannel->RemoveHead();
				}
			}
		}
		else
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
            SOCKLEN fromlen =sizeof(SOCKADDR);

			if (pConfig->m_nUseBroadcast)
			{
				bEnable = TRUE;
			}
			else
			{
				bEnable = FALSE;
			}

			setsockopt(hSocket,SOL_SOCKET,SO_BROADCAST,(char *)&bEnable,sizeof(BOOL));
			char *pReceiveBuffer = pUdpClientChannel->m_pReceiveBuffer;
			long nLenRcv = 0;
			nLen = 0;

			while (TRUE)
			{
                nLenRcv = recvfrom(hSocket, pReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH, 0, (SOCKADDR*)&sktReceive, &fromlen);

				if (nLenRcv == SOCKET_ERROR)
				{
					break;
				}

				LogReceivePackage(pUdpClientChannel->m_pszPpLogProtocol, (BYTE*)pReceiveBuffer, nLenRcv);
				pReceiveBuffer += nLenRcv;
				nLen += nLenRcv;
				Sleep(1);
			}
			//nLen = oUdpSocket.Receive(pUdpClientChannel->m_pReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);

			if (nLen > 0)
			{
				pUdpClientChannel->ResetOffsetDataFillBeginPosition();
				CCmmRcvSndTime *pCmmTime = new CCmmRcvSndTime();
				pCmmTime->InitTime(tm);
				//LogReceivePackage((BYTE*)pUdpClientChannel->m_pReceiveBuffer, nLen);
				pUdpClientChannel->AppendRcvBuffer((BYTE*)pUdpClientChannel->m_pReceiveBuffer, nLen, pCmmTime);
				pUdpClientChannel->OnChannelReceive(pCmmTime);
				delete pCmmTime;//20170623
			}
		}

		if (pUdpClientChannel->IsExitThread() )
		{
			break;
		}

		Sleep(50);
	}

#ifndef _PSX_QT_LINUX_
    closesocket(hSocket);
#else
    close(hSocket);
#endif

	CMM_SetAllSendPkgState(pUdpClientChannel);
	pUdpClientChannel->m_pThread = NULL;

	return 0;
}

BOOL CCmmUdpClientChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CCmmUdpClientConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CCmmUdpClientChannel::Send(CExBaseObject *pPkgSend)
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);
	m_nSendIndex++;
	CCmmChannel::Send(pPkgSend);
	oLock.Free();
}


BOOL CCmmUdpClientChannel::Connect()
{
	// 启动Socket
	m_bExitThread = FALSE;

	CreateThead();
	
	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;

	//启动OnConnect定义的过程
	CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)GetParent();
	
	POS pos = m_pConfig->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = m_pConfig->GetNext(pos);

		if (pObj != NULL && pObj->GetClassID() == DMCLASSID_CMM_ONCONNECT)
		{
			((CPpEngineThreadBase*)pDeviceCmmChannel->m_pThread)->RunProcedure(((CCmmOnConnect*)pObj)->m_strText, NULL, TRUE);
		}
	}

	OnConnectFinished();

	return TRUE;
}

BOOL CCmmUdpClientChannel::DisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CCmmUdpClientChannel::DisConnect"));
	//TerminateChannel();//20170623
	m_bExitThread = TRUE;
	m_dwConnectState = CONNECT_STATE_NORMAL;//20170623
	//DestroyWindow();
	return TRUE;
}


BOOL CCmmUdpClientChannel::IsConnectSuccessful()
{
	return CCmmChannel::IsConnectSuccessful();
}

void CCmmUdpClientChannel::OnChannelReceive(CCmmRcvSndTime *pCmmTime)
{
	CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime, NULL);
}

BOOL CCmmUdpClientChannel::IsCmmChannelExit()
{
	return (m_pThread == NULL);
}

BOOL CCmmUdpClientChannel::TerminateChannel()
{
#ifdef _PSX_QT_LINUX_
//	if (m_pThread != NULL)
//	{
//		DWORD exitCode;
//		BOOL bRet = FALSE;
//		bRet = GetExitCodeThread(m_pThread->m_hThread,&exitCode);
//		if (bRet && exitCode == STILL_ACTIVE)
//		{
//			TerminateThread(m_pThread->m_hThread,0);
//		}
//
//		m_pThread = NULL;
//	}
#endif
	return TRUE;
}
