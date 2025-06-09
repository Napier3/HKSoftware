#include "stdafx.h"
#include "WinTcpSocketClient.h"
#include "../System/TickCount32.h"

#ifndef _PSX_QT_LINUX_
#define _WIND_TCPSOCKET_CLIENT_TIMEOUT_    5000
#endif

CWinTcpSocketClient::CWinTcpSocketClient()
{
	m_pThread = NULL;
	m_dwReceiveGap = 1;

	//lijq 2020-04-25  将SttSocket转换为单独的发送、接受数据的通道
	m_bExitTcpClientThread = FALSE;
	m_bDetach = FALSE;
	m_bClosing = FALSE;
}

CWinTcpSocketClient::~CWinTcpSocketClient()
{
	//如果是析构，则不触发OnClose
	m_bDetach = TRUE;
	Close();
	WaitForThreadExit();
}

void CWinTcpSocketClient::Attach(SOCKET hSocket)
{
	CWinBaseSocket::Attach(hSocket);
}

SOCKET CWinTcpSocketClient::Detatch()
{
	m_bDetach = TRUE;
	SOCKET hSocket = m_hSocket;
	m_hSocket = NULL;
	return hSocket;
}


void CWinTcpSocketClient::CreateRcvThread()
{
	if (m_pThread == NULL)
	{
#ifdef _PSX_QT_LINUX_
		pthread_create(&m_pThread,NULL,TcpClientThread,(LPVOID)this ); //创建线程
#else
		m_pThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)TcpClientThread,(LPVOID)this,0,NULL);
#endif
	}
}

BOOL CWinTcpSocketClient::Connect(const char* strRemote, unsigned int iPort )
{
	BOOL bTrue = CWinTcpSocket::Connect(strRemote, iPort);

	if (!bTrue)
	{
		return FALSE;
	}

#ifdef _PSX_QT_LINUX_
    pthread_create(&m_pThread,NULL,TcpClientThread,(LPVOID)this ); //创建线程
#else
	m_pThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)TcpClientThread,(LPVOID)this,0,NULL);
#endif
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
	return 0;
}

#ifndef _PSX_QT_LINUX_  //2022-12-24  lijunqing，LINUX和Windows线程都单独写，简单处理
UINT TcpClientThread(LPVOID pData)
{
	CWinTcpSocketClient::InitSocket();

	int numrcv;
	CWinTcpSocketClient *pSocket = (CWinTcpSocketClient*)pData;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
	DWORD dwRcvGap = pSocket->m_dwReceiveGap;
	long nSocketErrCnt = 0;
	CTickCount32 oTick;

	pSocket->m_bClosing = FALSE;

	while (1)
	{
		if (pSocket->m_bExitTcpClientThread)
		{
			pSocket->m_bExitTcpClientThread = FALSE;
			break;
		}

		if (pSocket->m_bDetach)
		{
			break;
		}

		if (pSocket->m_hSocket == NULL)
		{
			break;
		}

		if (pSocket->m_bClosing)
		{
			pSocket->m_bClosing = FALSE;
			pSocket->CWinBaseSocket::Close();
			break;
		}

		numrcv = recv(clientSocket, buffer, dwReceiveBuffLen, 0);

		if (numrcv == SOCKET_ERROR)
		{
			int nErrNo = GetLastError();

			if (nErrNo == WSAETIMEDOUT)
			{//接收超时：10060

				//解决外网断链，一直触发超时
				if (oTick.GetTickCountLong(FALSE) > _WIND_TCPSOCKET_CLIENT_TIMEOUT_)
				{
					oTick.Enter();
#ifdef _TcpClientThread_Log_
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("#######nErrNo:%d,TcpClientThread:timeout."));
#endif
				}

				pSocket->OnSocketIdle(dwRcvGap);
				Sleep(dwRcvGap);
				continue;
			}
			else if (pSocket->IsSocketClose())
			{//主动断链,10004
				nSocketErrCnt++;
				if (nSocketErrCnt >= 5)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("#######nErrNo:%d,nSocketErrCnt:%d"),nErrNo,nSocketErrCnt);
					pSocket->CWinTcpSocket::Close();
					break;
				}	
			}

			oTick.Enter();

			pSocket->OnSocketIdle(dwRcvGap);
			Sleep(dwRcvGap);
			continue;
		}

		if (numrcv == 0)
		{//被动断链：0
			//int nErrNo = GetLastError();
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
				break;
			}

			pSocket->OnSocketIdle(dwRcvGap);
			Sleep(dwRcvGap);
			continue;
		}

		oTick.Enter();
		nSocketErrCnt = 0;
		pSocket->OnReceive((BYTE*)buffer, numrcv);
	}

	pSocket->m_pThread = NULL;

	if (!pSocket->m_bDetach)
	{ //如果是Detatch，则不能发送OnClose
		pSocket->OnClose(0);
	}

	return 0;
}
#else
void *TcpClientThread(LPVOID pData)
{
	pthread_detach(pthread_self());

	int numrcv;
	CWinTcpSocketClient *pSocket = (CWinTcpSocketClient*)pData;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
	DWORD dwRcvGap = pSocket->m_dwReceiveGap;
    long nSocketErrCnt = 0;
    pSocket->m_bClosing  =  FALSE;
	long nErrorIndex = 0;

	while (1)
	{
		//lijq 2020-04-25  将SttSocket转换为单独的发送、接受数据的通道
		if (pSocket->m_bExitTcpClientThread)
		{
			pSocket->m_bExitTcpClientThread = FALSE;
			nErrorIndex = 1;
			break;
		}

		if (pSocket->m_bDetach)
		{
			nErrorIndex = 2;
			break;
		}

        if (pSocket->m_hSocket == NULL)
        {//非阻塞模式，主动断链
			nErrorIndex = 3;
            break;
        }

        if( pSocket->m_bClosing)
        {
			nErrorIndex = 4;
            pSocket->m_bClosing = FALSE;
            pSocket->CWinBaseSocket::Close();
            break;
        }

		numrcv = recv(clientSocket, buffer, dwReceiveBuffLen, 0);
		if (numrcv == SOCKET_ERROR)
		{
            int nErrNo = errno;
            if((nErrNo == EINTR) || (nErrNo == EWOULDBLOCK) || (nErrNo == EAGAIN))
            {//非阻塞模式接收超时,11,4
                pSocket->OnSocketIdle(dwRcvGap);
                Sleep(dwRcvGap);
                continue;
            }
            else if (pSocket->IsSocketClose())
            {//非阻塞模式主动断链【一般不会触发】,9
                nSocketErrCnt++;
                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("#####nErrNo:%d,nSocketErrCnt=%d"),nErrNo,nSocketErrCnt);

                if(nSocketErrCnt >= 5)
                {
					nErrorIndex = 5;
				pSocket->CWinTcpSocket::Close();
                break;
			}
			}

            pSocket->OnSocketIdle(dwRcvGap);
			Sleep(dwRcvGap);
			continue;
		}

		if (numrcv == 0)
        {
			//非阻塞模式，主动断链
            //阻塞模式，主动、被动断链
            int nErrNo = errno;//0
			if (pSocket->IsSocketClose())
			{
				nErrorIndex = 6;
				pSocket->CWinTcpSocket::Close();
				break;
			}

			pSocket->OnSocketIdle(dwRcvGap);
			Sleep(dwRcvGap);
			continue;
		}

        nSocketErrCnt = 0;
	if( !pSocket->m_bClosing)
	{
	    pSocket->OnReceive((BYTE*)buffer, numrcv);
	}
		
	}

	pSocket->m_pThread = NULL;
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("nErrorIndex=%ld[TcpClientThread]"),nErrorIndex);

	if (!pSocket->m_bDetach)
	{ //如果是Detatch，则不能发送OnClose
		pSocket->OnClose(0);
	}

	pthread_exit(0);
	return 0;
}
#endif

void CWinTcpSocketClient::OnSocketIdle(long nMs)
{
	
}

void CWinTcpSocketClient::OnClose(int nErrorCode)
{
	
}

BOOL CWinTcpSocketClient::Close()
{
	m_bClosing = TRUE;
	return TRUE;
}

void CWinTcpSocketClient::ExitRcvTrhead()
{
	m_bExitTcpClientThread = TRUE;
	WaitForThreadExit();
}

void CWinTcpSocketClient::WaitForThreadExit()
{
	CTickCount32 oTick(FALSE);
	while(m_pThread != NULL)
	{
		oTick.DoEvents(5);
	}
}