#include "stdafx.h"
#include "RingMemBuf.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CRingMemBuf::CRingMemBuf()
{
	m_pszRealBuffer = NULL;
	//Init();
	m_bIsCreateOwn = true;
	m_pszRingBuf = NULL;
	m_pszRingBuf = NULL;
	m_nRingBufLen = NULL;
	m_nDataLen = NULL;
	m_nWritePos = NULL;
}

CRingMemBuf::~CRingMemBuf()
{
	if (m_pszRealBuffer != NULL)
	{
		delete m_pszRealBuffer;
	}
}

void CRingMemBuf::Free()
{
	if (m_bIsCreateOwn)
	{
		if (m_pszRealBuffer != NULL)
		{
			delete m_pszRealBuffer;
		}
	}
	else
	{
		m_pszRealBuffer = NULL;
	}

	m_bIsCreateOwn = true;
	m_pszRingBuf = NULL;
	m_pszRingBuf = NULL;
	m_nRingBufLen = NULL;
	m_nDataLen = NULL;
	m_nWritePos = NULL;
}

void CRingMemBuf::Reset()
{
	if (m_pszRingBuf == NULL)
	{
		return;
	}

	*m_nDataLen = 0;
	*m_nWritePos = 0;
	m_n64WriteSizeTotal = 0;
}

void CRingMemBuf::Create(long nLen)
{
	Free();

	if (nLen <= 0 || nLen >= DEFAULT_CIRCLEBUF_LEN)
	{
		nLen = DEFAULT_CIRCLEBUF_LEN;
	}

	m_pszRealBuffer = new char[nLen+128];
	memset(m_pszRealBuffer,0,sizeof(char)*(nLen+128));
	*((long*)m_pszRealBuffer) = nLen;
	Init();
}

void CRingMemBuf::Attatch(char *pBuffer, long nBufferLen, bool bInitBuffer)
{
	Free();

	m_bIsCreateOwn = false;
	m_pszRealBuffer = pBuffer;

    //��Ϊ�����ڴ�ʹ��ʱ��ֻ�з���˲Ż��ʼ��д��ص�λ�ã��ͻ����ǲ��ܳ�ʼ��д��λ�õ�
    if (bInitBuffer)
    {
        memset(m_pszRealBuffer,0,sizeof(char)*nBufferLen);
        *((long*)m_pszRealBuffer) = nBufferLen - 12;
    }

    Init(bInitBuffer);
}

void CRingMemBuf::Init(bool bInitBuffer)
{
    m_pszRingBuf = m_pszRealBuffer + 12;
    m_nRingBufLen = (long*)m_pszRealBuffer;
    m_nDataLen = (long*)(m_pszRealBuffer +4);
    m_nWritePos = (long*)(m_pszRealBuffer + 8);

    if (bInitBuffer)
    {//��Ϊ�����ڴ�ʹ��ʱ��ֻ�з���˲Ż��ʼ��д��ص�λ�ã��ͻ����ǲ��ܳ�ʼ��д��λ�õ�
        *m_nDataLen = 0;
        *m_nWritePos = 0;
        m_n64WriteSizeTotal = 0;
    }
}

BOOL CRingMemBuf::WriteBuf(char *pSrcBuf,long nLen)
{
	if (nLen <= 0)
	{
		return FALSE;
	}

    long nWritePos = *m_nWritePos;
    long nDataLen = *m_nDataLen;

	//��д��λ�ÿ�ʼ���ܵ����ݳ���С�ڻ���������
    if (nWritePos + nLen <= *m_nRingBufLen)
	{
		memcpy(m_pszRingBuf+nWritePos,pSrcBuf,nLen);
		nWritePos += nLen;

        if (nWritePos >= *m_nRingBufLen)
		{//λ�ô��ڻ�������ʼλ�ã��ع鵽0,ѭ�����ǣ���Ϊ�ܵ������ǲ���Խ��������
			nWritePos = 0;
		}
	}
	else
	{
		//��nWritePos��������ĩβ�����ݸ���
        long nLeft = *m_nRingBufLen - nWritePos;
		memcpy(m_pszRingBuf+nWritePos, pSrcBuf, nLeft);

		//�ӻ�������ͷ�����ݸ���
		memcpy(m_pszRingBuf, pSrcBuf+nLeft, nLen-nLeft);
		nWritePos = nLen-nLeft;
	}

    if (nDataLen != *m_nRingBufLen)
	{//ѭ����������û�б�ѭ������
		nDataLen += nLen;

        if (nDataLen >= *m_nRingBufLen)
		{//��������Ч���ݵ�����������ڻ��������ȣ���Ч���ݳ��ȵ��ڻ�������С
            nDataLen = *m_nRingBufLen;
		}
	}

    *m_nWritePos = nWritePos;
    *m_nDataLen = nDataLen;
    m_n64WriteSizeTotal += nLen;

	return TRUE;
}

//��ȡ��ǰ��������Ч���ݵĳ���
long CRingMemBuf::GetReadDataTotalLen(long nWritePos, long nReadPos, long nDataLen, long nBufLen)
{
	if (nDataLen < nBufLen)
	{//����û�������������Ӷ�����ʼλ�õ�д��λ��֮�������
        return nWritePos - nReadPos;
	}
	else
	{//ѭ���������Ѿ�����
        if (nWritePos >= nReadPos)
		{//����λ�������д��λ�ã��Ӷ�����ʼλ�õ�д��λ��֮������ݣ������Ƕ���λ�ñ�д��λ����Ȧ�����
            return nWritePos - nReadPos;
		}
		else
		{//������Ч���ݣ�����λ�õ�������ĩβ + ��������ͷ����ǰд��λ��
            return nBufLen - nReadPos + nWritePos;
		}
	}
}

long CRingMemBuf::ReadBuf(char *pDestBuf,long &nReadPos,long n64ReadSizeTotal,long nLen)
{
    //��֤���Ļ����Ƿ����
	long nHasDataSize = 0;
    ValidateBufErr(FALSE,nReadPos,n64ReadSizeTotal,nHasDataSize);

	//���ȼ�¼д����������������д������ͻ�Ŀ�����
    long nWritePos = *m_nWritePos;
    long nDataLen = *m_nDataLen;

	long nReadLen = 0;

	//��ȡ��Ч���ݵ�����
    long nTotalLen = GetReadDataTotalLen(nWritePos, nReadPos, nDataLen, *m_nRingBufLen);
	nReadLen = min(nTotalLen, nLen);

	if (nReadLen <= 0)
	{
		return 0;
	}

	//�˴�ʹ��m_nRingBufLen����ΪnTotalLen�Ѿ���������Ч���ݵĸ���
    if (nReadPos + nReadLen <= *m_nRingBufLen)
	{//��������û��Խ�����������ȣ�ֻ��ȡһ������
        memcpy(pDestBuf, m_pszRingBuf+nReadPos, nReadLen);
        nReadPos += nReadLen;

        if (nReadPos >= *m_nRingBufLen)
		{//�������λ�ó���������:��Ϊ�ܵ�����ʱ������Խ��������
            nReadPos = 0;
		}
	}
	else
	{
        long nLeft = nDataLen - nReadPos;
        memcpy(pDestBuf, m_pszRingBuf+nReadPos, nLeft);

		memcpy(pDestBuf+nLeft, m_pszRingBuf, nReadLen - nLeft);
        nReadPos = nReadLen - nLeft;
	}

	return nReadLen;
}

//��ȡָ�����ȵ����ݣ���������򲻶�ȡ
long CRingMemBuf::ReadBuf2(char *pDestBuf,long &nReadPos ,long n64ReadSizeTotal, long nLen)
{
	//��֤���Ļ����Ƿ����
	long nHasDataSize = 0;
	ValidateBufErr(FALSE,nReadPos,n64ReadSizeTotal,nHasDataSize);

	//���ȼ�¼д����������������д������ͻ�Ŀ�����
	long nWritePos = *m_nWritePos;
	long nDataLen = *m_nDataLen;

	long nReadLen = 0;

	//��ȡ��Ч���ݵ�����
	long nTotalLen = GetReadDataTotalLen(nWritePos, nReadPos, nDataLen, *m_nRingBufLen);
	nReadLen = nLen;

	if (nTotalLen < nLen)
	{//����ĳ���С����Ҫ��ȡ�ĳ��ȣ��򲻶�ȡ
		return 0;
	}

	//�˴�ʹ��m_nRingBufLen����ΪnTotalLen�Ѿ���������Ч���ݵĸ���
	if (nReadPos + nReadLen <= *m_nRingBufLen)
	{//��������û��Խ�����������ȣ�ֻ��ȡһ������
		memcpy(pDestBuf, m_pszRingBuf+nReadPos, nReadLen);
		nReadPos += nReadLen;

		if (nReadPos >= *m_nRingBufLen)
		{//�������λ�ó���������:��Ϊ�ܵ�����ʱ������Խ��������
			nReadPos = 0;
		}
	}
	else
	{
		long nLeft = nDataLen - nReadPos;
		memcpy(pDestBuf, m_pszRingBuf+nReadPos, nLeft);

		memcpy(pDestBuf+nLeft, m_pszRingBuf, nReadLen - nLeft);
		nReadPos = nReadLen - nLeft;
	}

	return nReadLen;
}

 //���ϲ�������Ȧ�ı�������
BOOL CRingMemBuf::ValidateBufErr(BOOL nSetReadPos,long &nReadPos,long n64ReadSizeTotal,long &nHasDataSize)
{
    nHasDataSize = m_n64WriteSizeTotal - n64ReadSizeTotal;

    if (nHasDataSize >= *m_nRingBufLen / 2  )
    {
        if (nSetReadPos)
        {
             nReadPos = *m_nWritePos;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
