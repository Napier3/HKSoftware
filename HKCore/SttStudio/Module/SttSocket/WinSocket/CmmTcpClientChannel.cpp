#include "StdAfx.h"
#include "CmmTcpClientChannel.h"
#include "DeviceCmmChannel.h"
#include "..\PpEngineThread.h"
#include "..\DeviceModel\CmmOnConnect.h"

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
	pSend->LogAndRecordProtocol();

	int iReturn = CWinTcpSocket::Send(pBuffer, nLen);//SendOwnSocket(pBuffer, nLen);

	if (iReturn <= 0)
	{
		m_dwConnectState = CONNECT_STATE_FAILED;

		OnConnectFailed();
	}
}


BOOL CCmmTcpClientChannel::Connect()
{
	InitSocket();

// 	if (m_hWnd == NULL)
// 	{
// 		InitSocket();
// 		CreateEx(0, AfxRegisterWndClass(0), _T("_Thread_Socket_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
// 	}

	ASSERT (m_pConfig != NULL);
	m_dwConnectState = CONNECT_STATE_FAILED;

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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpClientChannel Connect = %d"), IsConnectSuccessful());
		return FALSE;
	}

	if (!Bind(pszBuffer, CmmCfg_GetPort(m_pConfig->m_nLocalPort)))
	{
		Close();
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpClientChannel Connect = %d"), IsConnectSuccessful());
		return FALSE;
	}

// 	{
// 		Socket_SetSocketKeepAlive(m_hSocket);
// 	}

	// 	long nRet = asyncSelect(m_hWnd, WM_TCPIP, FD_ACCEPT|FD_READ|FD_CLOSE);
// 	long nErr = WSAGetLastError();
// 
// 	if (!nRet)
// 	{
// 		Close();
// 		return FALSE;
// 	}

	CString_to_char(m_pConfig->m_strRemoteIP, pszBuffer);

	if (!CWinTcpSocket::Connect(pszBuffer, m_pConfig->m_nRemotePort))
	{
		int n = WSAGetLastError();
		Close();
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpClientChannel Connect = %d"), IsConnectSuccessful());
		return FALSE;
	}

	m_dwConnectState = CONNECT_STATE_SUCCESSFUL;
	set_SendTimeout(200);
	set_ReceiveTimeout(200);

	if (IsConnectSuccessful())
	{
		//Ö´ÐÐ¹ý³Ì
		CDeviceCmmChannel *pDeviceCmmChannel = (CDeviceCmmChannel*)(CCmmChannel::GetParent());

		CMM_OnChannelConnectSucc(m_pConfig, pDeviceCmmChannel->m_pThread);
		
	}

	OnConnectFinished();

	if (m_pThread == NULL)
	{
		m_bExitThread = FALSE;
		m_pThread = AfxBeginThread(TcpClientThread, this);
		m_pThread->m_bAutoDelete = TRUE;
	}
	
	{
		CAutoSimpleLock oLock(g_oCmmLogAutoCriticSection);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpClientChannel Connect = %d"), IsConnectSuccessful());
	}

	return IsConnectSuccessful();
}

BOOL CCmmTcpClientChannel::DisConnect()
{
	CWinBaseSocket::Close();
	m_bExitThread = TRUE;
	m_dwConnectState = CONNECT_STATE_NORMAL;

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

UINT CCmmTcpClientChannel::TcpClientThread(LPVOID pParam)
{
	CCmmTcpClientChannel *pClientChannel = (CCmmTcpClientChannel*)pParam;

	while (TRUE)
	{
		pClientChannel->OnReceive();

		if (pClientChannel->m_bExitThread)
		{
			break;
		}

		Sleep(5);
	}

	CMM_SetAllSendPkgState(pClientChannel);
	pClientChannel->m_pThread = NULL;

	return 0;

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
