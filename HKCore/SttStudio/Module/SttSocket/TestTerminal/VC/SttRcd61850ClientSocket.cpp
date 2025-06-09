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

//�ж���Զ�̻��Ǳ��ض���
void CSttRcd61850ClientSocket::OnClose(int nErrorCode)
{
	
}

long CSttRcd61850ClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	if (m_nCurrRcdRcvLen + iLen >= m_nRcdBuffMaxLen)
	{//������������������ˣ����ͱ��Ľ��д���
		FireRcdBufRcvMsg();
	}
	
	//���ձ���
	memcpy(m_pRcdRcvBuff + m_nCurrRcdRcvLen, pRcvBuf, iLen);
	m_nCurrRcdRcvLen += iLen;

	return 0;
}

void CSttRcd61850ClientSocket::OnSocketIdle(long nMs)
{
	m_nSocketIdleLong += nMs;

	if (m_nSocketIdleLong >= 20)
	{//�������20msû���յ����ģ������Ѿ��յ��ı���
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
	{//û�н��ܶ�����λ������λ��
		m_nCurrRcdRcvLen = 0;
		return;
	}

	m_pSttRcdBufferRcvMsg->OnRcdBufRcv(m_pRcdRcvBuff, m_nCurrRcdRcvLen);
	m_nCurrRcdRcvLen = 0;
}
