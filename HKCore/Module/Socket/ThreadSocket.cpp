// ThreadSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadSocket

CThreadSocket::CThreadSocket()
{
	m_hSocket = NULL;
	m_nIPAddr = 0;
	m_nSocketPort = 10001;
}

CThreadSocket::~CThreadSocket()
{
}

BOOL CThreadSocket::CreateOwnSocket(char* lpszSocketAddress, UINT nSocketPort , int nSocketType, int nProtocol)
{
	if (m_hWnd == NULL)
	{
		CreateEx(0, AfxRegisterWndClass(0), _T("_Thread_Socket_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	}
	
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	CString strErrorMsg;
	unsigned short nPort = nSocketPort;
	
	wVersionRequested = MAKEWORD(2,2);
	
	err = WSAStartup(wVersionRequested, &wsaData);

	int nErr = WSAGetLastError();
	
	if (err != 0) 
	{
		// 加载Socket库失败
		WSACleanup();
		return FALSE;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) 
	{
		// 版本不对,卸载库
		WSACleanup();
		return FALSE; 
	}
	
	m_hSocket = socket(AF_INET,nSocketType, nProtocol);					// 创建socket

	nErr = WSAGetLastError();
	
	if (nSocketPort > 0)
	{
		sockaddr_in addrSocket;
		
		addrSocket.sin_addr.S_un.S_addr = INADDR_ANY;
		addrSocket.sin_family = AF_INET;
		addrSocket.sin_port = htons(nPort);
		addrSocket.sin_addr.s_addr = inet_addr(lpszSocketAddress);
		int nRet = bind(m_hSocket,(sockaddr *)&addrSocket,sizeof(addrSocket));
		
		if(nRet == SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			WSACleanup();
			return FALSE;
		}
		
		nRet = WSAAsyncSelect(m_hSocket, m_hWnd, WM_TCPIP, FD_ACCEPT|FD_READ|FD_CLOSE);
		nErr = WSAGetLastError();
		
		if(nRet == SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			WSACleanup();
			return FALSE;
		}
	}
	
	m_nSocketPort = nSocketPort;

	return TRUE;
}

BOOL CThreadSocket::ListenOwnSocket()
{
	if (listen(m_hSocket,10) == SOCKET_ERROR)
	{
		closesocket(m_hSocket);
		WSACleanup();
		return FALSE;
	}

	int nErr = WSAGetLastError();	

	return TRUE;
}

void CThreadSocket::CloseOwnSocket()
{
	//WSAAsyncSelect(m_hSocket, m_hWnd, WM_TCPIP, 0);
	shutdown(m_hSocket, SD_BOTH);
	closesocket(m_hSocket);
	//WSACleanup();
	m_hSocket = NULL;
}

void CThreadSocket::Close()
{
	CloseOwnSocket();
	CloseWindow();
	m_hWnd = NULL;
}

BOOL CThreadSocket::ConnectOwnSocket(char* lpszHostAddress, UINT nHostPort)
{
	int err;
	sockaddr_in addrSocket;
	
	addrSocket.sin_addr.S_un.S_addr = inet_addr(lpszHostAddress);
	addrSocket.sin_family = AF_INET;
	addrSocket.sin_port = htons(nHostPort);
	
	err = connect(m_hSocket,(SOCKADDR*)&addrSocket,sizeof(SOCKADDR));		// 向服务器发出连接请求
	int nErr = WSAGetLastError();	
	
	if (err != 0)
	{
		// 连接失败
		closesocket(m_hSocket);
		WSACleanup();
		return FALSE; 
	}
	
	if (WSAAsyncSelect(m_hSocket, m_hWnd, WM_TCPIP, FD_ACCEPT|FD_READ|FD_CLOSE))
	{
		closesocket(m_hSocket);
		WSACleanup();
		return FALSE;
	}

	nErr = WSAGetLastError();	
	m_nIPAddr = inet_addr(lpszHostAddress);
	m_nSocketPort = nHostPort;

	nErr = WSAGetLastError();	
	
	return TRUE;
}

int CThreadSocket::SendOwnSocket(const void* lpBuf, int nBufLen, int nFlags)
{
	sockaddr_in addrSocket;	
	addrSocket.sin_addr.S_un.S_addr = m_nIPAddr;
	addrSocket.sin_family = AF_INET;
	addrSocket.sin_port = htons(m_nSocketPort);
	
	return sendto(m_hSocket, (char*)lpBuf, nBufLen, 0,(SOCKADDR*)&addrSocket,sizeof(SOCKADDR));
}

int CThreadSocket::SendOwnSocket(int nFlags)
{
	BYTE *pData = m_oBufferSend.GetBuffer();
	long nBeginPos = 0;
	long nLen = m_oBufferSend.GetDataFillBeginPosition();
	return SendOwnSocket(pData, nLen);
}

int CThreadSocket::ReceiveOwnSocket(void* lpBuf, int nBufLen, int nFlags)
{
	sockaddr_in addrSocket;	
	addrSocket.sin_addr.S_un.S_addr = m_nIPAddr;
	addrSocket.sin_family = AF_INET;
	addrSocket.sin_port = htons(m_nSocketPort);
	
	return recv(m_hSocket, (char*)lpBuf, nBufLen, 0);
}

BOOL CThreadSocket::AcceptOwnSocket(CThreadSocket& rConnectedSocket, SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
	int nLen = sizeof(SOCKADDR);
	sockaddr_in addrSocket;	
	rConnectedSocket.m_hSocket = accept(m_hSocket, (sockaddr*)&addrSocket, &nLen);
	
	if (rConnectedSocket.m_hSocket == INVALID_SOCKET)
	{
		return FALSE;
	}

	rConnectedSocket.m_nIPAddr = addrSocket.sin_addr.S_un.S_addr;
	rConnectedSocket.m_nSocketPort = addrSocket.sin_port;
	//rConnectedSocket.CreateEx(0, AfxRegisterWndClass(0), _T("Socket"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	
	if (rConnectedSocket.m_hWnd == NULL)
	{
		rConnectedSocket.CreateEx(0, AfxRegisterWndClass(0), _T("_Thread_Socket_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	}

	if(WSAAsyncSelect(rConnectedSocket.m_hSocket, rConnectedSocket.m_hWnd, WM_TCPIP, FD_ACCEPT|FD_READ|FD_CLOSE))
	{
		closesocket(m_hSocket);
		WSACleanup();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CThreadSocket::GetPeerName(CString& rPeerAddress, UINT& rPeerPort)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);
	if (bResult)
	{
		rPeerPort = ntohs(sockAddr.sin_port);
		rPeerAddress = inet_ntoa(sockAddr.sin_addr);
	}
	else
	{
		int nErr = WSAGetLastError();
	}

	return bResult;
}

BOOL CThreadSocket::GetSockName(CString& rSocketAddress, UINT& rSocketPort)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = GetSockName((SOCKADDR*)&sockAddr, &nSockAddrLen);
	
	if (bResult)
	{
		rSocketPort = ntohs(sockAddr.sin_port);
		rSocketAddress = inet_ntoa(sockAddr.sin_addr);
	}
	return bResult;
}

BEGIN_MESSAGE_MAP(CThreadSocket, CWnd)
	//{{AFX_MSG_MAP(CThreadSocket)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TCPIP,OnTCPIP)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CThreadSocket message handlers

LRESULT CThreadSocket::OnTCPIP(WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam)) {
	case FD_ACCEPT:
		OnAccept();
		break;
	case FD_READ:
		OnReceive();
		break;
	case FD_CLOSE:
		OnClose();
		break;
	default:
		break;
	}

	return S_OK;
}

long CThreadSocket::OnReceive()
{
	BYTE *pBuffer = m_oBufferReceive.GetBuffer();
	long nLen = 0;
	BYTE pTempBuffer[RECEIVEBUFFER_LENGTH];
	long nLenTotal = 0;
	
	if (pBuffer != NULL)
	{
		while (TRUE)
		{
			nLen = ReceiveOwnSocket(pTempBuffer, RECEIVEBUFFER_LENGTH);
			
			if (nLen <= 0)
			{
				break;
			}
			
			nLenTotal += nLen;
			m_oBufferReceive.AppendBuffer(pTempBuffer, nLen);
		}
	}
	else
	{
		char buff[MAX_PATH];
		nLen = ReceiveOwnSocket(buff,MAX_PATH);
	}

	return nLenTotal;
}

CThreadSocketList::CThreadSocketList()
{
}

CThreadSocketList::~CThreadSocketList()
{
}

CThreadSocket* CThreadSocketList::FindByIP(const char* pstrIP, UINT nPort)
{
	CString strPeerName;
	UINT nPortTemp;
	CThreadSocket *pSocket = NULL;
	CThreadSocket *pFind = NULL;

	POS pos = m_listChild.GetHeadPosition();

	while (pos != NULL)
	{
		pSocket = (CThreadSocket*)m_listChild.GetNext(pos);
		pSocket->GetPeerName(strPeerName, nPortTemp);

		if (strPeerName == pstrIP && nPortTemp == nPort)
		{
			pFind = pSocket;
			break;
		}
	}

	return pFind;
}

CThreadSocket* CThreadSocketList::FindByIP(DWORD dwIP, UINT nPort)
{
	BYTE b1 = (BYTE)((dwIP >> 24) & 0xFF);
	BYTE b2 = (BYTE)((dwIP >> 16) & 0xFF);
	BYTE b3 = (BYTE)((dwIP >> 8) & 0xFF); 
	BYTE b4 = (BYTE)(dwIP & 0xFF);
	return FindByIP(b1, b2, b3, b4, nPort);
}

CThreadSocket* CThreadSocketList::FindByIP(BYTE b1, BYTE b2, BYTE b3, BYTE b4, UINT nPort)
{
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	UINT rPeerPort = 0;
	BOOL bResult = FALSE;
	
	CThreadSocket *pSocket = NULL;
	CThreadSocket *pFind = NULL;
	POS pos = m_listChild.GetHeadPosition();
	
	while (pos != NULL)
	{
		pSocket = (CThreadSocket*)m_listChild.GetNext(pos);
		bResult = pSocket->GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen);

		if (bResult)
		{
			rPeerPort = ntohs(sockAddr.sin_port);

			if (nPort == rPeerPort 
				&& sockAddr.sin_addr.S_un.S_un_b.s_b1 == b1
				&& sockAddr.sin_addr.S_un.S_un_b.s_b2 == b2
				&& sockAddr.sin_addr.S_un.S_un_b.s_b3 == b3
				&& sockAddr.sin_addr.S_un.S_un_b.s_b4 == b4)
			{
				pFind = pSocket;
				break;
			}
		}	
	}
	
	return pFind;
}

