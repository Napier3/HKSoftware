#include "stdafx.h"
#include "SttRcd61850ClientSocket.h"

CSttRcd61850ClientSocket::CSttRcd61850ClientSocket()
{
	m_nSocketIdleLong = 0;
	m_nCurrRcdRcvLen = 0;
	m_nRcdBuffMaxLen = 0;
	SetRcdRcvBuffMaxLen(RCDRCV_BUFFER_MAX_LEN);
	m_pSttRcdBufferRcvMsg = NULL;
}

CSttRcd61850ClientSocket::~CSttRcd61850ClientSocket()
{
	delete m_pRcdRcvBuff;
}

//判断是远程还是本地断链
void CSttRcd61850ClientSocket::OnClose(int nErrorCode)
{
	
}

long CSttRcd61850ClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	if (m_nCurrRcdRcvLen + iLen >= m_nRcdBuffMaxLen)
	{//如果缓冲区不够接收了，则发送报文进行处理
		FireRcdBufRcvMsg();
	}
	
	//接收报文
	memcpy(m_pRcdRcvBuff + m_nCurrRcdRcvLen, pRcvBuf, iLen);
	m_nCurrRcdRcvLen += iLen;

	return 0;
}

void CSttRcd61850ClientSocket::OnSocketIdle(long nMs)
{
	m_nSocketIdleLong += nMs;

	if (m_nSocketIdleLong >= 20)
	{//如果超过20ms没有收到报文，则发送已经收到的报文
		FireRcdBufRcvMsg();
		m_nSocketIdleLong = 0;
	}
}

void CSttRcd61850ClientSocket::SetRcdRcvBuffMaxLen(long nLen)
{
	if (nLen <= m_nRcdBuffMaxLen)
	{
		return;
	}

	if (m_pRcdRcvBuff != NULL)
	{
		delete m_pRcdRcvBuff;
	}

	m_nRcdBuffMaxLen = nLen;
	m_pRcdRcvBuff = new BYTE [nLen + 10];
}

void CSttRcd61850ClientSocket::FireRcdBufRcvMsg()
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

	m_pSttRcdBufferRcvMsg->OnRcdBufRcv(m_pRcdRcvBuff, m_nCurrRcdRcvLen);
	m_nCurrRcdRcvLen = 0;
}
