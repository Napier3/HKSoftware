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

    //作为共享内存使用时，只有服务端才会初始化写相关的位置，客户端是不能初始化写的位置的
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
    {//作为共享内存使用时，只有服务端才会初始化写相关的位置，客户端是不能初始化写的位置的
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

	//从写的位置开始，总的数据长度小于缓冲区长度
    if (nWritePos + nLen <= *m_nRingBufLen)
	{
		memcpy(m_pszRingBuf+nWritePos,pSrcBuf,nLen);
		nWritePos += nLen;

        if (nWritePos >= *m_nRingBufLen)
		{//位置大于缓冲区起始位置，回归到0,循环覆盖：因为总的条件是不会越过缓冲区
			nWritePos = 0;
		}
	}
	else
	{
		//从nWritePos到缓冲区末尾的数据个数
        long nLeft = *m_nRingBufLen - nWritePos;
		memcpy(m_pszRingBuf+nWritePos, pSrcBuf, nLeft);

		//从缓冲区开头的数据个数
		memcpy(m_pszRingBuf, pSrcBuf+nLeft, nLen-nLeft);
		nWritePos = nLen-nLeft;
	}

    if (nDataLen != *m_nRingBufLen)
	{//循环缓冲区还没有被循环覆盖
		nDataLen += nLen;

        if (nDataLen >= *m_nRingBufLen)
		{//缓冲区有效数据的数：如果大于缓冲区长度，有效数据长度等于缓冲区大小
            nDataLen = *m_nRingBufLen;
		}
	}

    *m_nWritePos = nWritePos;
    *m_nDataLen = nDataLen;
    m_n64WriteSizeTotal += nLen;

	return TRUE;
}

//获取当前缓冲区有效数据的长度
long CRingMemBuf::GetReadDataTotalLen(long nWritePos, long nReadPos, long nDataLen, long nBufLen)
{
	if (nDataLen < nBufLen)
	{//数据没填满缓冲区，从读的起始位置到写的位置之间的数据
        return nWritePos - nReadPos;
	}
	else
	{//循环缓冲区已经填满
        if (nWritePos >= nReadPos)
		{//读的位置落后于写的位置，从读的起始位置到写的位置之间的数据，不考虑读的位置被写的位置套圈的情况
            return nWritePos - nReadPos;
		}
		else
		{//两段有效数据：读的位置到缓冲区末尾 + 缓冲区开头到当前写的位置
            return nBufLen - nReadPos + nWritePos;
		}
	}
}

long CRingMemBuf::ReadBuf(char *pDestBuf,long &nReadPos,long n64ReadSizeTotal,long nLen)
{
    //验证报文缓冲是否错误
	long nHasDataSize = 0;
    ValidateBufErr(FALSE,nReadPos,n64ReadSizeTotal,nHasDataSize);

	//首先记录写的两个变量，降低写、读冲突的可能性
    long nWritePos = *m_nWritePos;
    long nDataLen = *m_nDataLen;

	long nReadLen = 0;

	//获取有效数据的总数
    long nTotalLen = GetReadDataTotalLen(nWritePos, nReadPos, nDataLen, *m_nRingBufLen);
	nReadLen = min(nTotalLen, nLen);

	if (nReadLen <= 0)
	{
		return 0;
	}

	//此处使用m_nRingBufLen：因为nTotalLen已经考虑了有效数据的个数
    if (nReadPos + nReadLen <= *m_nRingBufLen)
	{//读的区域没有越过缓冲区长度：只读取一段数据
        memcpy(pDestBuf, m_pszRingBuf+nReadPos, nReadLen);
        nReadPos += nReadLen;

        if (nReadPos >= *m_nRingBufLen)
		{//如果读的位置超过缓冲区:因为总的条件时，不会越过缓冲区
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

//读取指定长度的数据，如果不足则不读取
long CRingMemBuf::ReadBuf2(char *pDestBuf,long &nReadPos ,long n64ReadSizeTotal, long nLen)
{
	//验证报文缓冲是否错误
	long nHasDataSize = 0;
	ValidateBufErr(FALSE,nReadPos,n64ReadSizeTotal,nHasDataSize);

	//首先记录写的两个变量，降低写、读冲突的可能性
	long nWritePos = *m_nWritePos;
	long nDataLen = *m_nDataLen;

	long nReadLen = 0;

	//获取有效数据的总数
	long nTotalLen = GetReadDataTotalLen(nWritePos, nReadPos, nDataLen, *m_nRingBufLen);
	nReadLen = nLen;

	if (nTotalLen < nLen)
	{//缓存的长度小于需要读取的长度，则不读取
		return 0;
	}

	//此处使用m_nRingBufLen：因为nTotalLen已经考虑了有效数据的个数
	if (nReadPos + nReadLen <= *m_nRingBufLen)
	{//读的区域没有越过缓冲区长度：只读取一段数据
		memcpy(pDestBuf, m_pszRingBuf+nReadPos, nReadLen);
		nReadPos += nReadLen;

		if (nReadPos >= *m_nRingBufLen)
		{//如果读的位置超过缓冲区:因为总的条件时，不会越过缓冲区
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

 //作废并丢弃套圈的报文数据
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
