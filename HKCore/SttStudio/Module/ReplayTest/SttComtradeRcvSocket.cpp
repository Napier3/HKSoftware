#include "stdafx.h"
#include "SttComtradeRcvSocket.h"
#include "../Engine/SttTestServerBase.h"

#define COMTRADE_SOCKET_RECV_LEN	20480

CSttComtradeRcvSocket g_oSttComtradeRcvSocket;

CSttComtradeRcvSocket::CSttComtradeRcvSocket()
{
	m_nSocketIdleLong = 0;
	m_nReceiveBufLen = COMTRADE_ABBUF_SIZE;
	m_nCurrRcdRcvLen = 0;
	m_nRecvPacketState = 0;

	m_nSendFinishIndex = -1;
	m_nSendNum = 0;
	m_nNeedNum = 0;

	CComtradeBufMngr::Create(COMTRADE_LOOPBUF_SIZE,COMTRADE_ABBUF_SIZE);
	m_pPacketBuff = NULL;
}

CSttComtradeRcvSocket::~CSttComtradeRcvSocket()
{
	Close();
	WaitForThreadExit();

	CComtradeBufMngr::Release();
}

void CSttComtradeRcvSocket::ResetRcvLen()
{
	m_pPacketBuff = NULL;
	m_nCurrRcdRcvLen = 0;
	m_nRecvPacketState = 0;
	m_nSendFinishIndex = -1;
	m_nSendNum = 0;
}

void CSttComtradeRcvSocket::WaitForThreadExit()
{
	CTickCount32 oTick(FALSE);

	while(m_pSttComtradeRcvThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

//收到发送完成后，通知接收线程
void CSttComtradeRcvSocket::OnSendDataFinish(int nIndex,int nSendNum)
{
	m_nSendFinishIndex = nIndex;
	m_nSendNum = nSendNum;
}

void CSttComtradeRcvSocket::OnSendDataStart(int nIndex,int nSendNum)
{
	CComtradeDataBuffer *pDestComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nIndex);
	ASSERT(pDestComtradeBuf->CanWrite());
	pDestComtradeBuf->ResetWritePos();
	m_pPacketBuff = (BYTE *)pDestComtradeBuf->GetBuffer();

	m_nCurrRcdRcvLen = 0;
	m_nNeedNum = nSendNum;
	m_nStartSendIndex = nIndex;
	m_nRecvPacketState = 1;
}

//收到发送完成后，将接收数据解压，填充到指定ComtradeBuf中
BOOL CSttComtradeRcvSocket::MoveToComtradeBuf()
{
	if (m_nSendNum != m_nCurrRcdRcvLen)
	{//收发不等，异常
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MoveToComtradeBuf error m_nSendNum[%d] m_nCurrRcdRcvLen[%d]"),m_nSendNum,m_nCurrRcdRcvLen);
		return FALSE;
	}

	long nSrcLen = m_nSendNum,nSendIndex = m_nSendFinishIndex;

	CComtradeDataBuffer *pDestComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nSendIndex);
	ASSERT(pDestComtradeBuf->CanWrite());
	pDestComtradeBuf->ResetWritePos(nSrcLen/sizeof(float));
	pDestComtradeBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);
	
	ResetRcvLen();

	CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
	ASSERT(pServerEngine != NULL);
	pServerEngine->OnAfterMoveToComtradeBuf(nSendIndex,nSrcLen/sizeof(float));

	return TRUE;	
}

void CSttComtradeRcvSocket::AttatchSocketDatabase(CSttSocketDataBase *pSttSocket)
{
	Close();
	WaitForThreadExit();

	m_pSttSocket = pSttSocket;
	Attach(pSttSocket->Detatch());

#ifdef _PSX_QT_LINUX_
	pthread_create(&m_pSttComtradeRcvThread,NULL,SttComtradeRcvThread,(LPVOID)this );
#else
	m_pSttComtradeRcvThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttComtradeRcvThread,(LPVOID)this,0,NULL);
#endif	
}

void CSttComtradeRcvSocket::OnClose(int nErrorCode)
{
	if(m_pSttSocket != NULL)
	{
		m_pSttSocket->OnSocketClose(nErrorCode);
		m_pSttSocket = NULL;
	}
}

void CSttComtradeRcvSocket::OnSocketIdle(long nMs)
{
	return;
	if (nMs == 0)
	{
		m_nSocketIdleLong = 0;
		return;
	}

	m_nSocketIdleLong += nMs;

	if (m_nSocketIdleLong >= 1000)
	{//如果超过1000ms没有收到报文，则发送已经收到的报文
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttComtradeRcvSocket::OnSocketIdle 1000ms"));
		m_nSocketIdleLong = 0;
	}
}

#ifdef _PSX_QT_LINUX_
void *SttComtradeRcvThread(LPVOID pParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttComtradeRcvThread <<<<<<<<"));

	int numrcv;
	CSttComtradeRcvSocket *pSocket = (CSttComtradeRcvSocket*)pParam;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	pSocket->m_nCurrRcdRcvLen = 0;
	pSocket->m_nRecvPacketState = 0;
	pSocket->m_bClosing  =  FALSE;
	long nSocketErrCnt = 0;
	long nNeedLen = 0;
	long nRequireRecvLen = 0;

	char buffer[COMTRADE_SOCKET_RECV_LEN+10] = {0};

	while (1)
	{
		if (pSocket->m_hSocket == NULL)
		{//非阻塞模式，主动断链
			break;
		}

		if( pSocket->m_bClosing)
		{
			pSocket->m_bClosing = FALSE;
			pSocket->CWinBaseSocket::Close();
			break;
		}

		if (pSocket->m_nRecvPacketState == 1)
		{
			pSocket->m_nRecvPacketState = 2;

			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("应答Comtrade数据块开始发送命令"));
			CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
			pServerEngine->Comtrade_SendDataStartAck(pSocket->m_nStartSendIndex);
		}

		if ((pSocket->m_nNeedNum > 0) && (pSocket->m_nNeedNum == pSocket->m_nCurrRcdRcvLen))
		{//数据已接受完，等待取走
			if (pSocket->m_nSendFinishIndex >= 0)
			{//收到发送已完成消息
				pSocket->MoveToComtradeBuf();
			}
			else
			{
				Sleep(5);
			}
		}

		nNeedLen = COMTRADE_SOCKET_RECV_LEN;
		if (pSocket->m_nNeedNum > 0)
		{
			nRequireRecvLen =  pSocket->m_nNeedNum - pSocket->m_nCurrRcdRcvLen;
			nNeedLen = min((int)nRequireRecvLen,COMTRADE_SOCKET_RECV_LEN);
		}
	
		numrcv = recv(clientSocket, buffer, nNeedLen, 0);
		if (numrcv == SOCKET_ERROR)
		{
			int nErrNo = errno;
			if((nErrNo == EINTR) || (nErrNo == EWOULDBLOCK) || (nErrNo == EAGAIN))
			{//非阻塞模式接收超时,11,4
				Sleep(5);
				pSocket->OnSocketIdle(5);
				continue;
			}
			else if (pSocket->IsSocketClose())
			{//非阻塞模式主动断链【一般不会触发】,9
				nSocketErrCnt++;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("#####nErrNo:%d,nSocketErrCnt=%d"),nErrNo,nSocketErrCnt);

				if(nSocketErrCnt >= 5)
				{
					pSocket->CWinTcpSocket::Close();
					break;
				}
			}

			Sleep(5);
			pSocket->OnSocketIdle(5);
			continue;
		}

		if (numrcv == 0)
		{
			//非阻塞模式，主动断链
			//阻塞模式，主动、被动断链
			int nErrNo = errno;//0
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
				break;
			}

			Sleep(5);
			pSocket->OnSocketIdle(5);
			continue;
		}

		nSocketErrCnt = 0;

		if (pSocket->m_nRecvPacketState < 2)
		{
			continue;
		}

		if (pSocket->m_pPacketBuff == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("+++++++SttComtradeRcvThread m_pPacketBuff == NULL"));
			continue;
		}

		if (pSocket->m_nCurrRcdRcvLen == 0)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("+++++++StartRecv SttComtradeRcvThread"));
		}

		if (nRequireRecvLen <= numrcv)
		{
			memcpy(pSocket->m_pPacketBuff+pSocket->m_nCurrRcdRcvLen,buffer,nRequireRecvLen);
			pSocket->m_nCurrRcdRcvLen += nRequireRecvLen;

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++++EndRecv SttComtradeRcvThread::m_nCurrRcdRcvLen[%d]"),pSocket->m_nCurrRcdRcvLen);
		}
		else
		{
			memcpy(pSocket->m_pPacketBuff+pSocket->m_nCurrRcdRcvLen,buffer,numrcv);
			pSocket->m_nCurrRcdRcvLen += numrcv;
			nRequireRecvLen -= numrcv;
		}
	}
	
	pSocket->ResetRcvLen();
	pSocket->OnClose(0);
	pSocket->m_pSttComtradeRcvThread = NULL;

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttComtradeRcvThread >>>>>>>>"));
	return 0;
}

#else

UINT CSttComtradeRcvSocket::SttComtradeRcvThread(LPVOID pParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttComtradeRcvThread <<<<<<<<"));

	CWinBaseSocket::InitSocket();

	int numrcv;
	CSttComtradeRcvSocket *pSocket = (CSttComtradeRcvSocket*)pParam;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	pSocket->m_nCurrRcdRcvLen = 0;
	pSocket->m_nRecvPacketState = 0;
	pSocket->m_bClosing  =  FALSE;
	long nSocketErrCnt = 0;
	long nNeedLen = 0;
	long nRequireRecvLen = 0;

	char buffer[COMTRADE_SOCKET_RECV_LEN+10] = {0};

	while (1)
	{
		if (pSocket->m_hSocket == NULL)
		{
			break;
		}

		if( pSocket->m_bClosing)
		{
			pSocket->m_bClosing = FALSE;
			pSocket->CWinBaseSocket::Close();
			break;
		}

		if (pSocket->m_nRecvPacketState == 1)
		{
			pSocket->m_nRecvPacketState = 2;

			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("应答Comtrade数据块开始发送命令"));
			CSttTestServerBase* pServerEngine = CSttTestServerBase::GetServerEngine();
			pServerEngine->Comtrade_SendDataStartAck(pSocket->m_nStartSendIndex);
		}

		if ((pSocket->m_nNeedNum > 0) && (pSocket->m_nNeedNum == pSocket->m_nCurrRcdRcvLen))
		{//数据已接受完，等待取走
			if (pSocket->m_nSendFinishIndex >= 0)
			{//收到发送已完成消息
				pSocket->MoveToComtradeBuf();
			}
			else
			{
				Sleep(5);
			}
		}

		nNeedLen = COMTRADE_SOCKET_RECV_LEN;
		if (pSocket->m_nNeedNum > 0)
		{
			nRequireRecvLen =  pSocket->m_nNeedNum - pSocket->m_nCurrRcdRcvLen;
			nNeedLen = min((int)nRequireRecvLen,COMTRADE_SOCKET_RECV_LEN);
		}
		
		numrcv = recv(clientSocket, buffer, nNeedLen, 0);

		if (numrcv == SOCKET_ERROR)
		{
			int nErrNo = GetLastError();
			if (nErrNo == WSAETIMEDOUT)
			{//接收超时：10060
				Sleep(1);
				pSocket->OnSocketIdle(1);
				continue;
			}
			else if (pSocket->IsSocketClose())
			{//主动断链,10004
				nSocketErrCnt++;
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("#######nErrNo:%d,nSocketErrCnt:%d"),nErrNo,nSocketErrCnt);

				if (nSocketErrCnt >= 5)
				{
					pSocket->CWinTcpSocket::Close();
					break;
				}	
			}

			Sleep(5);
			pSocket->OnSocketIdle(5);
			continue;
		}

		if (numrcv == 0)
		{//被动断链：0
			int nErrNo = GetLastError();
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
				break;
			}

			Sleep(5);
			pSocket->OnSocketIdle(5);
			continue;
		}

		nSocketErrCnt = 0;

		if (pSocket->m_nRecvPacketState < 2)
		{
			continue;
		}

		if (pSocket->m_pPacketBuff == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("+++++++SttComtradeRcvThread m_pPacketBuff == NULL"));
			continue;
		}

		if (pSocket->m_nCurrRcdRcvLen == 0)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("+++++++StartRecv SttComtradeRcvThread"));
		}

		if (nRequireRecvLen <= numrcv)
		{
			memcpy(pSocket->m_pPacketBuff+pSocket->m_nCurrRcdRcvLen,buffer,nRequireRecvLen);
			pSocket->m_nCurrRcdRcvLen += nRequireRecvLen;

			 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++++EndRecv SttComtradeRcvThread::m_nCurrRcdRcvLen[%d]"),pSocket->m_nCurrRcdRcvLen);
		}
		else
		{
			memcpy(pSocket->m_pPacketBuff+pSocket->m_nCurrRcdRcvLen,buffer,numrcv);
			pSocket->m_nCurrRcdRcvLen += numrcv;
			nRequireRecvLen -= numrcv;
		}  
	}

	pSocket->ResetRcvLen();
	pSocket->OnClose(0);
	pSocket->m_pSttComtradeRcvThread = NULL;

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttComtradeRcvThread >>>>>>>>"));
	return 0;
}

#endif
