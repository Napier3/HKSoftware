#include "stdafx.h"
#include "WinTcpSocketClient.h"

CWinTcpSocketClient::CWinTcpSocketClient()
{
    m_pThread = NULL;
    m_pHeartbeatThread = NULL;
    m_dwReceiveGap = 1;

    m_nHeartbeatTimeOut = 5000;
}

CWinTcpSocketClient::~CWinTcpSocketClient()
{
	Close();

    while((m_pThread != NULL) || (m_pHeartbeatThread != NULL))
	{
		Sleep(1);
	}
}

void CWinTcpSocketClient::Attach(SOCKET hSocket)
{
	CWinBaseSocket::Attach(hSocket);
}

void CWinTcpSocketClient::CreateThead()
{
	if (m_pThread == NULL)
	{
        pthread_create(&m_pThread,NULL,TcpClientThread,(LPVOID)this ); //创建线程
        pthread_create(&m_pHeartbeatThread,NULL,TcpClientHeartbeatThread,(LPVOID)this );
	}
}

BOOL CWinTcpSocketClient::Connect(const char* strRemote, unsigned int iPort )
{
	BOOL bTrue = CWinTcpSocket::Connect(strRemote, iPort);

	if (!bTrue)
	{
		return FALSE;
	}

    pthread_create(&m_pThread,NULL,TcpClientThread,(LPVOID)this ); //创建线程
    pthread_create(&m_pHeartbeatThread,NULL,TcpClientHeartbeatThread,(LPVOID)this );

	return TRUE;
}


BOOL CWinTcpSocketClient::InitSocketClient(int nMs)
{
	BOOL bRet1 = set_SendTimeout(nMs);

#ifdef _CLogPrint_h__
	if (!bRet1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("设置发送超时失败"));
	}
#endif

	BOOL bRet2 = set_ReceiveTimeout( nMs );

#ifdef _CLogPrint_h__
	if (!bRet2)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("设置接受超时失败"));
	}
#endif

	return bRet1 && bRet2;
}

long CWinTcpSocketClient::OnReceive(BYTE *pRcvBuf, int iLen)
{
//	TRACE("%s\r\n", (char*)pRcvBuf);
	return 0;
}

void *TcpClientThread(LPVOID pData)
{
	int numrcv;
	CWinTcpSocketClient *pSocket = (CWinTcpSocketClient*)pData;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
	DWORD dwRcvGap = pSocket->m_dwReceiveGap;

	while (1)
	{
		if (pSocket->m_hSocket == NULL)
		{
			break;
		}

		numrcv = recv(clientSocket, buffer, dwReceiveBuffLen, 0);

		if (numrcv == SOCKET_ERROR)
		{
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
			}

			Sleep(dwRcvGap);
			continue;
			//break;
		}

		if (numrcv == 0)
		{
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
				break;
			}

			Sleep(dwRcvGap);
			continue;
		}

		pSocket->OnReceive((BYTE*)buffer, numrcv);
	}

	pSocket->m_pThread = NULL;
	pSocket->OnClose(0);

	return 0;
}

void *TcpClientHeartbeatThread(LPVOID pData)
{
    CWinTcpSocketClient *pSocket = (CWinTcpSocketClient*)pData;

    while (1)
    {
        if (pSocket->m_hSocket == NULL)
        {
            break;
        }

        if (pSocket->m_nHeartbeatTimeOut <= 0)
        {
            break;
        }

        if (pSocket->CheckHeartbeatTimeOut())
        {
            if(pSocket->SendHeartbeatCmd() < 0)
            {//没有重载发心跳命令，直接退出
                break;
            }
        }

        Sleep(100);
    }

    pSocket->m_pHeartbeatThread = NULL;

    return 0;
}

BOOL CWinTcpSocketClient::CheckHeartbeatTimeOut()
{
    if (m_oHeartbeatTick.GetTickCountLong(FALSE) >= m_nHeartbeatTimeOut)
    {
        m_oHeartbeatTick.Enter();

        return TRUE;
    }

    return FALSE;
}

void CWinTcpSocketClient::OnSocketIdle(long nMs)
{
	
}

void CWinTcpSocketClient::OnClose(int nErrorCode)
{
	
}

BOOL CWinTcpSocketClient::Close()
{
	CWinTcpSocket::Close();

	return TRUE;
}

