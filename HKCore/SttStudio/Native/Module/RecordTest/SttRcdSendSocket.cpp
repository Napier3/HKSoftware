#include "stdafx.h"
#include "SttRcdSendSocket.h"

extern CRingMemBuf *g_pSttRcdSndRingBuf;

__int64  CSttRcdSendSocket::g_n64RcdSendSize = 0;
__int64  CSttRcdSendSocket::g_n64RcdSendPrevSize = 0;
__int64  CSttRcdSendSocket::g_n64RcdDrvRcvSize = 0;
__int64  CSttRcdSendSocket::g_n64RcdDrvRcvPrevSize = 0;
long CSttRcdSendSocket::g_nRcdSendOverTimeCount = 0;
long CSttRcdSendSocket::g_nRcdSendOverTimeMax = 0;
#define RCDSENDOVERTIMEMAX  300

long CSttRcdSendSocket::CalRcdSendRate()
{
	long nRate = g_n64RcdSendSize - g_n64RcdSendPrevSize;

	return nRate;
}

long CSttRcdSendSocket::CalRcdDrvRcvRate()
{
	long nRate = g_n64RcdDrvRcvSize - g_n64RcdDrvRcvPrevSize;

	return nRate;
}

CSttRcdSendSocket g_oSttRcdSendSocket;

CSttRcdSendSocket::CSttRcdSendSocket()
{
	memset(m_chSendBuf,0,RCD_BUFFER_MAX_LEN+10);

	m_pSttRcdSendThread = NULL;
	m_pSttSocket = NULL;

	if  (!stt_rcd_buf_zip_init())
	{
		g_nSttRcdSocketUseZip = 0;
		CLogPrint::LogString(XLOGLEVEL_ERROR, "internal error - lzo_init() failed !!!\n");
		CLogPrint::LogString(XLOGLEVEL_ERROR, "(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
	}
}

CSttRcdSendSocket::~CSttRcdSendSocket()
{
	
}

void CSttRcdSendSocket::AttatchSocketDatabase(CSttSocketDataBase *pSttSocket)
{
	Close();
	while(m_pSttRcdSendThread != NULL)
	{
		Sleep(1);
	}

	m_pSttSocket = pSttSocket;
	Attach(pSttSocket->Detatch());
}

void CSttRcdSendSocket::OnClose(int nErrorCode)
{
	if(m_pSttSocket != NULL)
	{
		m_pSttSocket->OnSocketClose(nErrorCode);
		m_pSttSocket = NULL;
	}
}

void CSttRcdSendSocket::InitRecordBuf()
{
	memset(m_chSendBuf,0,RCD_BUFFER_MAX_LEN+10);

    m_nRingBufReadPos = g_pSttRcdSndRingBuf->GetWritePos();
    m_n64ReadSizeTotal = 0;
	g_n64RcdSendSize = 0;
	g_n64RcdSendPrevSize = 0;
	g_n64RcdDrvRcvSize = 0;
	g_n64RcdDrvRcvPrevSize = 0;
	m_bExitTcpClientThread = FALSE;
}

BOOL CSttRcdSendSocket::WriteRecordBuf(char *pSrcBuf,long nLen)
{
	if(nLen > g_pSttRcdSndRingBuf->GetRingBufLen())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("CSttRcdSendSocket::WriteRecordBuf nLen > RingBufLen"));
		return FALSE;
	}

    BOOL bRet = g_pSttRcdSndRingBuf->WriteBuf(pSrcBuf, nLen);

	if (bRet)
	{
		g_n64RcdDrvRcvSize += nLen;
	}

	return bRet;
}

long CSttRcdSendSocket::ReadRecordBuf()
{
    long nReadLen = g_pSttRcdSndRingBuf->ReadBuf(m_chSendBuf,m_nRingBufReadPos,m_n64ReadSizeTotal,RCD_BUFFER_MAX_LEN);
    m_n64ReadSizeTotal += nReadLen;
    return nReadLen;
}

BOOL CSttRcdSendSocket::CreateRcdSendThread()
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T(">>>>>>CreateRcdSendThread"));

	if(m_hSocket <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CSttRcdSendSocket::CreateRcdSendThread m_hSocket <= 0"));
		return FALSE;
	}

    InitRecordBuf();

	if(m_pSttRcdSendThread == NULL)
	{
#ifdef _PSX_QT_LINUX_
		pthread_create(&m_pSttRcdSendThread,NULL,SttRcdSendThread,(LPVOID)this );
#else
		m_pSttRcdSendThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttRcdSendThread,(LPVOID)this,0,NULL);
		// 		m_pSttRcdSendThread = AfxBeginThread(SttRcdSendThread, (LPVOID)this);
		// 		m_pSttRcdSendThread->m_bAutoDelete = TRUE;
#endif	
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("CSttRcdSendSocket::CreateRcdSendThread: Thread is not null "));
	}

	return TRUE;
}

void CSttRcdSendSocket::ExitRcdSendThread()
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T(">>>>>>ExitRcdSendThread"));
	ExitRcvTrhead();
}

void CSttRcdSendSocket::CheckRcdInfo()
{
	long nHasDataSize = 0;

    if (g_pSttRcdSndRingBuf->ValidateBufErr(FALSE,m_nRingBufReadPos,m_n64ReadSizeTotal,nHasDataSize))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ValidateBufErr:%d"),nHasDataSize);
	}
}

long CSttRcdSendSocket::SttRcdSocketSend(BYTE *buffer, long nLen)
{
	long nSendCnt = 0;
	long nZipLen = nLen;
	BYTE *buffer_zip = (BYTE*)m_chSendBuf_Zip;

	if (g_nSttRcdSocketUseZip)
	{
		BOOL bRet = stt_rcd_buf_zip(buffer, nLen, buffer_zip, nZipLen);

		if (bRet)
		{
			if (m_hSocket != 0)
			{//测试用
				nSendCnt = Send(m_hSocket, (char*)buffer_zip, nZipLen);
			}
		}
	}
	else
	{
		if (m_hSocket != 0)
		{//测试用
			nSendCnt = Send(m_hSocket, (char*)buffer, nZipLen);
		}
	}

	return nSendCnt;
}

#ifdef _PSX_QT_LINUX_
void *SttRcdSendThread(LPVOID pParam)
{
#else
UINT CSttRcdSendSocket::SttRcdSendThread(LPVOID pParam)
{
	InitSocket();
#endif

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T(">>>>>>SttRcdSendThread"));

	long nReadCnt = 0;
	long nSendCnt = 0;
	CSttRcdSendSocket *pSocket = (CSttRcdSendSocket*)pParam;
	pSocket->m_bClosing=FALSE;
	char *buffer = (char*)pSocket->m_chSendBuf;
	BYTE *buffer_zip = (BYTE*)pSocket->m_chSendBuf_Zip;

	stt_rcd_zip_buf_match_head(buffer_zip);

	while (1)
	{
		if (pSocket->m_bExitTcpClientThread)
		{//主动停止录波
			break;
		}

		if (pSocket->m_bClosing)
		{
			pSocket->m_bClosing = FALSE;
			pSocket->CWinBaseSocket::Close();
			break;
		}

		nReadCnt = pSocket->ReadRecordBuf();

		if (nReadCnt == 0)
		{//没读到数据
			Sleep(1);
			continue;
		}

		nSendCnt = pSocket->SttRcdSocketSend((BYTE*)buffer, nReadCnt);

		if (nSendCnt > 0)
		{
			pSocket->g_n64RcdSendSize += nReadCnt;
		}
		else
		{//disconnect
			pSocket->Close();
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttRcdSocketSend error  IsSocketClose==TRUE"));
			break;
		}
	}

	if(!pSocket->m_bExitTcpClientThread)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttRcdSendThread pSocket->OnClose(0)"));
		pSocket->OnClose(0);
	}
	pSocket->m_bExitTcpClientThread = FALSE;
	pSocket->m_pSttRcdSendThread = NULL;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttRcdSendThread>>>>>>"));
	return 0;
}
