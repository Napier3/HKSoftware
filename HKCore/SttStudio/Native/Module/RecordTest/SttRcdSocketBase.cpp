#include "stdafx.h"
#include "SttRcdSocketBase.h"
#include "../TestClient/SttMacroTestInterface.h"

__int64 CSttRcdSocketBase::m_n64RecvTotalSize = 0;
__int64 CSttRcdSocketBase::m_n64RecvPrevSize = 0;
CString CSttRcdSocketBase::m_strWriteFilePath;

FILE* CSttRcdSocketBase::m_pWriteAt02dRcdFile = NULL;

long CSttRcdSocketBase::CalRecvSizeRate()
{
	long nRate = m_n64RecvTotalSize - m_n64RecvPrevSize;
	m_n64RecvPrevSize = m_n64RecvTotalSize;
	return nRate;
}

void CSttRcdSocketBase::CreateAt02dRcdFileWrite(const CString &strFile)
{
	m_n64RecvTotalSize = 0;
	m_n64RecvPrevSize = 0;

	if (m_pWriteAt02dRcdFile != NULL)
	{
		return;
	}

	m_strWriteFilePath = strFile;
    m_pWriteAt02dRcdFile = fopen(strFile.GetString(), "w+b");
//	m_pWriteAt02dRcdFile->read();
}

void CSttRcdSocketBase::CloseAt02dRcdFileWrite()
{
	if (m_pWriteAt02dRcdFile != NULL)
	{
		fclose(m_pWriteAt02dRcdFile);
		m_pWriteAt02dRcdFile = NULL;
	}
}

bool CSttRcdSocketBase::IsWriteAt02dRcdFileWrite()
{
	return (m_pWriteAt02dRcdFile != NULL);
}

CSttRcdSocketBase::CSttRcdSocketBase()
{
	m_nSocketIdleLong = 0;
	m_nCurrRcdRcvLen = 0;
	m_nRcdBuffMaxLen = 0;
	//SetRcdRcvBuffMaxLen(RCDRCV_BUFFER_MAX_LEN);
	m_pSttRcdBufferRcvMsg = NULL;
	m_pSttSocket = NULL;
	m_pSttRcdRecvThread = NULL;
	m_bRcdSocketClosing = FALSE;
}

CSttRcdSocketBase::~CSttRcdSocketBase()
{
	SttRcdSocketClose();

	long nCount =0;
	while(m_pSttRcdRecvThread != NULL)
	{
		if (nCount >= 2000)
		{
			break;
		}

		Sleep(1);
	}

	CloseAt02dRcdFileWrite();
}

void CSttRcdSocketBase::AttatchSocketDatabase(CSttSocketDataBase *pSttSocket)
{
	SttRcdSocketClose();

	long nCount =0;
	while(m_pSttRcdRecvThread != NULL)
	{
		if (nCount >= 2000)
		{
			break;
		}

		Sleep(1);
	}

	m_pSttSocket = pSttSocket;
	Attach(pSttSocket->Detatch());

#ifndef  _PSX_IDE_QT_
	m_pSttRcdRecvThread = AfxBeginThread(SttRcdRecvThread, (LPVOID)this);
	m_pSttRcdRecvThread->m_bAutoDelete = TRUE;
#else
	m_pSttRcdRecvThread = new CWinThread(SttRcdRecvThread, this);
	m_pSttRcdRecvThread->m_bAutoDelete = false;//20220622 zhouhj暂时不自动删除,防止退出线程线程是软件崩溃
	m_pSttRcdRecvThread->ResumeThread();
#endif

}

//判断是远程还是本地断链
void CSttRcdSocketBase::OnClose(int nErrorCode)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttRcdSocketBase::OnClose.............."));

	m_pSttSocket->OnSocketClose(nErrorCode);
}

long CSttRcdSocketBase::OnReceive(BYTE *pRcvBuf, int iLen)
{
	if (m_nCurrRcdRcvLen + iLen >= m_nRcdBuffMaxLen)
	{//如果缓冲区不够接收了，则发送报文进行处理
		FireRcdBufRcvMsg();
	}
	else
	{
		if (m_oSendTickCount.GetTickCountLong() > 500)
		{
			FireRcdBufRcvMsg();
		}
	}

	//接收报文
	memcpy(m_pRcdRcvBuff + m_nCurrRcdRcvLen, pRcvBuf, iLen);
	m_nCurrRcdRcvLen += iLen;

	return 0;
}


long CSttRcdSocketBase::OnReceive_Zip(BYTE *pRcvBuf, int iLen)
{
	long nZipLen = 0;
	long nLenLeft = 0;

	if (m_pWriteAt02dRcdFile != NULL)
	{
		fwrite(pRcvBuf, 1, iLen, m_pWriteAt02dRcdFile);
		return 0;
	}

	if (m_nCurrRcdRcvLen == 0)
	{
		memcpy(m_pRcdRcvBuff + m_nCurrRcdRcvLen, pRcvBuf, iLen);
		m_nCurrRcdRcvLen += iLen;
	}
	else
	{
		memcpy(m_pRcdRcvBuff + m_nCurrRcdRcvLen, pRcvBuf, iLen);
		m_nCurrRcdRcvLen += iLen;
	}

	BYTE *p = m_pRcdRcvBuff;
	BYTE *pEnd = m_pRcdRcvBuff + m_nCurrRcdRcvLen;
	BYTE *pBack = NULL;

	while (TRUE)
	{
		pBack = p;
		stt_rcd_zip_buf_get_zip_begin(p, pEnd);  //跳转到正确的位置

		if (p != pBack)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Package Loss Len = %d"), p - pBack);
		}

		if (pEnd - p >= STT_RCD_BUFF_ZIP_HEAD_LEN)
		{//长度足够
			nZipLen = stt_rcd_zip_buf_get_len_zip(p);

			if (nZipLen <= pEnd - p - STT_RCD_BUFF_ZIP_HEAD_LEN)
			{
				FireRcdBufRcvMsg_Zip(p);
				p += STT_RCD_BUFF_ZIP_HEAD_LEN + nZipLen;
				continue;
			}
			else
			{
				if (m_pRcdRcvBuff != p)
				{
					m_nCurrRcdRcvLen = pEnd - p;
					memcpy(m_pRcdRcvBuff, p, m_nCurrRcdRcvLen);
				}

				break;
			}
		}
		else
		{
			if (p != m_pRcdRcvBuff)
			{
				m_nCurrRcdRcvLen = pEnd - p;
				memcpy(m_pRcdRcvBuff, p, m_nCurrRcdRcvLen);
				break;
			}
		}
	}


	return 0;
}

void CSttRcdSocketBase::OnSocketIdle(long nMs)
{
	if (nMs == 0)
	{
		m_nSocketIdleLong = 0;
		return;
	}

	m_nSocketIdleLong += nMs;

	if (m_nSocketIdleLong >= 1000)
	{//如果超过1000ms没有收到报文，则发送已经收到的报文
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttRcdSocketBase::OnSocketIdle 1000ms"));
		m_nSocketIdleLong = 0;
	}
}

// void CSttRcdSocketBase::SetRcdRcvBuffMaxLen(long nLen)
// {
// 	if (nLen <= m_nRcdBuffMaxLen)
// 	{
// 		return;
// 	}
// 
// 	if (m_pRcdRcvBuff != NULL)
// 	{
// 		delete m_pRcdRcvBuff;
// 	}
// 
// 	m_nRcdBuffMaxLen = nLen;
// 	m_pRcdRcvBuff = new BYTE [nLen + 10];
// }

void CSttRcdSocketBase::SttRcdSocketClose()
{
	m_bRcdSocketClosing = TRUE;

	CTickCount32 oTick;

	while(m_pSttRcdRecvThread != NULL)
	{
		Sleep(5);
//		oTick.DoEvents(5);
	}

	Close();
	// 	if (m_pSttRcdRecvThread != NULL)
	// 	{
	// 		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Exit SttRcdRecvThread"));
	// 
	// 		m_pSttRcdRecvThread->SuspendThread();
	// 		delete m_pSttRcdRecvThread;
	// 		Close();
	// 		m_pSttSocket = NULL;
	// 	}
}

void CSttRcdSocketBase::FireRcdBufRcvMsg()
{
	if (m_nCurrRcdRcvLen == 0)
	{
		return;
	}

	if (m_pSttRcdBufferRcvMsg == NULL)
	{//没有接受对象，则复位接受首位置
		m_nCurrRcdRcvLen = 0;
		return;
	}

	m_oSendTickCount.Enter();
	m_pSttRcdBufferRcvMsg->OnRcdBufRcv(m_pRcdRcvBuff, m_nCurrRcdRcvLen);
	m_nCurrRcdRcvLen = 0;
}

long CSttRcdSocketBase::FireRcdBufRcvMsg_Zip(BYTE *pBuff)
{
	m_oSendTickCount.Enter();
	long nSrcLen = 0, nDataLen = 0;

	BOOL bRet = stt_rcd_buf_unzip(pBuff, nSrcLen, m_pRcdRcvBuff_Uzip, nDataLen);

	if (bRet)
	{
		m_pSttRcdBufferRcvMsg->OnRcdBufRcv(m_pRcdRcvBuff_Uzip, nDataLen);
	}

	return nDataLen;
}

UINT SttRcdRecvThread(LPVOID pParam)
{
#ifndef _PSX_QT_LINUX_
    CWinBaseSocket::InitSocket();
#endif
	int numrcv;
	CSttRcdSocketBase *pSocket = (CSttRcdSocketBase*)pParam;
	pSocket->m_bRcdSocketClosing = FALSE;
	SOCKET clientSocket = (SOCKET)pSocket->m_hSocket;
	char *buffer = (char*)pSocket->m_pReceiveBuff;
	DWORD dwReceiveBuffLen = pSocket->m_dwReceiveBuffLen;
	DWORD dwRcvGap = pSocket->m_dwReceiveGap;
	CSttRcdBufferRcvMsg *pSttRcdBufferRcvMsg = pSocket->GetRcdBufRcvMsg();
	long n_SOCKET_ERROR_CLOSE = 0;
	int nPort = 0;
	pSocket->get_LocalPort(&nPort);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Begin SttRcdRecvThread Port = %d"), nPort);
	long nSocketErrCnt = 0;

	while (1)
	{
		if (pSocket->m_hSocket == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttRcdRecvThread m_hSocket == NULL"));

			break;
		}

		if (pSocket->m_bRcdSocketClosing)
		{
			pSocket->m_bRcdSocketClosing = FALSE;
			break;
		}

		numrcv = recv(clientSocket, buffer, dwReceiveBuffLen, 0);

		if (numrcv == SOCKET_ERROR)
		{
#ifdef _PSX_QT_LINUX_
            int nErrNo = errno;
            if (/*(nErrNo == EINIR)||*/(nErrNo == EWOULDBLOCK)||(nErrNo == EAGAIN))
#else
            int nErrNo = GetLastError();
            if (nErrNo == WSAETIMEDOUT)
#endif
			{//接收超时：10060
				Sleep(dwRcvGap);
				pSocket->OnSocketIdle(dwRcvGap);
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

			Sleep(dwRcvGap);
			pSocket->OnSocketIdle(dwRcvGap);
			continue;
		}


		if (numrcv == 0)
		{//被动断链：0
#ifdef _PSX_QT_LINUX_
            int nErrNo = pSocket->GetLastError();
#else
            int nErrNo = GetLastError();
#endif
			if (pSocket->IsSocketClose())
			{
				pSocket->CWinTcpSocket::Close();
				break;
			}

			Sleep(dwRcvGap);
			pSocket->OnSocketIdle(dwRcvGap);
			continue;
		}

		nSocketErrCnt = 0;
		pSocket->m_n64RecvTotalSize += numrcv;
		pSocket->OnSocketIdle(0);

		if (g_nSttRcdSocketUseZip)
		{
			pSocket->OnReceive_Zip((BYTE*)buffer, numrcv);
		}
		else
		{
			pSocket->OnReceive((BYTE*)buffer, numrcv);
		}
	}

	pSocket->m_pSttRcdRecvThread = NULL;
	pSocket->OnClose(0);
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SttRcdRecvThread end"));

	pSttRcdBufferRcvMsg->OnRcdRcvClosed();  ////2022-6-30  lijunqing 

	return 0;
}
