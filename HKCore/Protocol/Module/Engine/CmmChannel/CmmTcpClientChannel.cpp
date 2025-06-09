#include "StdAfx.h"
#include "CmmTcpClientChannel.h"
#include "DeviceCmmChannel.h"
#include "../PpEngineThreadBase.h"
#include "../DeviceModel/CmmOnConnect.h"

CCmmTcpClientChannel::CCmmTcpClientChannel(void)
{
	m_bExitThread = FALSE;
	m_pThread = NULL;
	m_pConfig = NULL;
	//m_hWnd = NULL;
}

CCmmTcpClientChannel::~CCmmTcpClientChannel(void)
{

}


BOOL CCmmTcpClientChannel::Create(CExBaseObject *pConfig)
{
	m_pConfig = (CCmmTcpClientConfig*)pConfig;
	SetReceiveBufferLength(1048576); //1024*1024  1M
	return TRUE;
}

void CCmmTcpClientChannel::Send(CExBaseObject *pPkgSend)
{
	m_nSendIndex++;

	CPpPackageSend *pSend = (CPpPackageSend*)pPkgSend;
	char *pBuffer = (char*)pSend->m_oBuffer.GetBuffer();
	long nLen = pSend->m_oBuffer.GetDataLength();
	pSend->SetSendState(TRUE);
	pSend->LogAndRecordProtocol();

	BOOL bValid = IsSocketValid();
	long nWaiteIndex = 0;

	while (! bValid)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("!!!!CCmmTcpClientChannel::Send IsSocketValid=false!!!!"));
		Sleep(10);
		bValid = IsSocketValid();
		nWaiteIndex++;

		if (nWaiteIndex >= 10)
		{
			break;
		}
	}

    if (! bValid)
    {	
        Close();
        m_dwConnectState = CONNECT_STATE_FAILED;
        OnConnectFailed();
        return ;
    }

    int iReturn = CWinTcpSocket::Send(pBuffer, nLen);//SendOwnSocket(pBuffer, nLen);

	if (iReturn <= 0)
	{
		m_dwConnectState = CONNECT_STATE_FAILED;

		OnConnectFailed();
	}
}


BOOL CCmmTcpClientChannel::Connect()
{
#ifndef _PSX_IDE_QT_
    InitSocket();
#endif

// 	if (m_hWnd == NULL)
// 	{
// 		InitSocket();
// 		CreateEx(0, AfxRegisterWndClass(0), _T("_Thread_Socket_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
// 	}

	ASSERT (m_pConfig != NULL);
	m_dwConnectState = CONNECT_STATE_FAILED;
	m_bResetRcvBufPos = FALSE;
	m_pCycleRcvBuffer->ResetOffsetDataFillBeginPosition();

	if (m_pConfig->m_strRemoteIP.GetLength() < 7)
	{
		return FALSE;
	}

	char pszBuffer[MAX_PATH];

	pszBuffer[0] = 0;

	CString_to_char(m_pConfig->m_strLocalIP, pszBuffer);

	if ( !CWinBaseSocket::Create(SOCK_STREAM) )
	{
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TcpClientChannel Create [%s] = %d"), m_pConfig->m_strLocalIP.GetString(), IsConnectSuccessful());
		return FALSE;
	}

	if (!Bind(pszBuffer, CmmCfg_GetPort(m_pConfig->m_nLocalPort)))
	{
		Close();
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TcpClientChannel Bind eroor [%s][%d] = %d")
                                   , m_pConfig->m_strLocalIP.GetString(), m_pConfig->m_nLocalPort, IsConnectSuccessful());
        return FALSE;
	}

	CString_to_char(m_pConfig->m_strRemoteIP, pszBuffer);

	if (!CWinTcpSocket::Connect(pszBuffer, m_pConfig->m_nRemotePort))
	{
        //int n = WSAGetLastError();
		Close();
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TcpClientChannel Connect(%s    %d) = %d ")
                                   , m_pConfig->m_strLocalIP.GetString(), m_pConfig->m_nRemotePort, IsConnectSuccessful());

        //改到基类中调用 shaolei 20201214
       //OnConnectFinished();
		return FALSE;
	}

    IsSocketValid();

	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
    set_SendTimeout(200);
    set_ReceiveTimeout(200);

    IsSocketValid();

    if (IsConnectSuccessful())
    {
        if (m_pThread == NULL)
        {
            m_bExitThread = FALSE;

    #ifdef _PSX_IDE_QT_
             pthread_create(&m_pThread,NULL,Cmm_TcpClientThread,(LPVOID)this ); //创建线程
    #else
            m_pThread = AfxBeginThread(Cmm_TcpClientThread, this);
            m_pThread->m_bAutoDelete = TRUE;
    #endif
        }

        //执行过程
        CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)(CCmmChannel::GetParent());
        CMM_OnChannelConnectSucc(m_pConfig, pDeviceCmmChannel->m_pThread);
    }

	OnConnectFinished();
	
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%08X]:TcpClientChannel Connect [%s][%d] = %d"), (unsigned long)m_pConfig, m_pConfig->m_strLocalIP.GetString()
		, m_pConfig->m_nRemotePort, IsConnectSuccessful());

    IsSocketValid();

	return IsConnectSuccessful();
}

BOOL CCmmTcpClientChannel::DisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CCmmTcpClientChannel::DisConnect"));
	CWinBaseSocket::Close();
	m_bExitThread = TRUE;
	m_dwConnectState = CONNECT_STATE_NORMAL;
    long nCount = 0;

    while (nCount <= 200)
    {
        if (m_pThread == NULL)
        {
            break;
        }
        else
        {
            nCount++;
            Sleep(10);
        }
    }
	//DestroyWindow();
	//m_hWnd = NULL;
	return TRUE;
}


BOOL CCmmTcpClientChannel::IsConnectSuccessful()
{
	return CCmmChannel::IsConnectSuccessful();
}


int CCmmTcpClientChannel::ReceiveOwnSocket(void* lpBuf, int nBufLen, int nFlags)
{
	long nLen = Receive((char*)lpBuf, nBufLen);
	return nLen;
// 	sockaddr_in addrSocket;	
// 	addrSocket.sin_addr.S_un.S_addr = m_nIPAddr;
// 	addrSocket.sin_family = AF_INET;
// 	addrSocket.sin_port = htons(m_nSocketPort);
// 
// // 	long nLen =  recv(m_hSocket, (char*)lpBuf, nBufLen, 0);
// // 	int nErr = WSAGetLastError();
// 
// 	struct sockaddr_in sktReceive;
// 	int fromlen =sizeof(sktReceive);
// 	long nLen = recvfrom(m_hSocket, (char*)lpBuf,nBufLen, 0, (struct sockaddr*)&sktReceive, &fromlen);
// 	return nLen;//recvfrom(m_hSocket, (char*)lpBuf, nBufLen, 0);
}

#ifndef _PSX_IDE_QT_
UINT Cmm_TcpClientThread(LPVOID pParam)
#else
void* Cmm_TcpClientThread(LPVOID pParam)
#endif
{
	CCmmTcpClientChannel *pClientChannel = (CCmmTcpClientChannel*)pParam;
    SOCKET hSocket = pClientChannel->m_hSocket;

	while (TRUE)
	{
		pClientChannel->OnReceive();

        if (pClientChannel->m_nReceiveLen < 0)
        {
            CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SOCKET error......"));
            break;
        }

		if (pClientChannel->Is_ExitThread())
		{
			break;
		}

/*       {
            struct tcp_info info;
              int len=sizeof(info);
              getsockopt(hSocket, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
              if((info.tcpi_state==TCP_ESTABLISHED))
              {

              }
              else
              {
                  CLogPrint::LogString(XLOGLEVEL_ERROR, "Cmm_TcpClientThread: socket is broken");
              }
        }
*/

		Sleep(5);
	}

	CMM_SetAllSendPkgState(pClientChannel);
	pClientChannel->SetThread_NULL();

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("****************Cmm_TcpClientThread Exit****************"));

#ifndef _PSX_IDE_QT_
    return 0;
#endif
}

long CCmmTcpClientChannel::OnReceive()
{
	m_nReceiveLen = 0;

	if (m_pCycleRcvBuffer == NULL)
	{
		return 0;
	}

#ifdef _use_CMemBufferList
#else
	BYTE *pBuffer = m_pCycleRcvBuffer->GetBuffer();

	if (pBuffer == NULL)
	{
		return 0;
	}
#endif

	CCmmRcvSndTime *pCmmTime = NULL;//new CCmmRcvSndTime();
	//long nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();

	ResetOffsetDataFillBeginPosition();

	while (TRUE)
	{
		long nLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);

		if (nLen <= 0)
		{
			break;
		}

		LogReceivePackage(m_pszPpLogProtocol, m_byteReceiveBuffer, nLen);
		pCmmTime = new CCmmRcvSndTime();
		pCmmTime->InitTime();
		m_nReceiveLen += nLen;

// 		nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();
// 		m_pCycleRcvBuffer->AppendBuffer(m_byteReceiveBuffer, nLen);
// 		m_pCycleRcvBuffer->GetBufferPos(nFillBeginPos, nLen, pCmmTime->m_oCycleBufferPos);
		AppendRcvBuffer((BYTE*)m_byteReceiveBuffer, nLen, pCmmTime);

		CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime,  NULL);
	}

	return m_nReceiveLen;
}

BOOL CCmmTcpClientChannel::IsCmmChannelExit()
{
	if (m_pThread == NULL)
	{
		if (m_hSocket != NULL)
		{
			Close();
			m_hSocket = NULL;
		}
	}

	return (m_hSocket == NULL);// && m_hWnd == NULL);
}

BOOL CCmmTcpClientChannel::TerminateChannel()
{
	return TRUE;
}


// 
// BEGIN_MESSAGE_MAP(CCmmTcpClientChannel, CWnd)
// 	//{{AFX_MSG_MAP(CThreadSocket)
// 	// NOTE - the ClassWizard will add and remove mapping macros here.
// 	//}}AFX_MSG_MAP
// 	ON_MESSAGE(WM_TCPIP,OnTCPIP)
// END_MESSAGE_MAP()

/*
LRESULT CCmmTcpClientChannel::OnTCPIP(WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam)) 
	{
	case FD_ACCEPT:
		//CWinTcpSocket::Accept();
		break;
	case FD_READ:
		OnReceive();
		break;
	case FD_CLOSE:
		//OnClose();
		break;
	default:
		break;
	}

	return S_OK;
}
*/
