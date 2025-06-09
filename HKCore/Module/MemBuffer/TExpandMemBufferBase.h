// TExpandMemBufferBse.h: interface for the CTExpandMemBufferBse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TExpandMemBufferBse_h__)
#define _TExpandMemBufferBse_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../OSInterface/OSInterface.h"
#define TExpandMemBuffer_ALLOC_SIZE_EX  4

template <class T>
class TExpandMemBufferBase
{
public:	
	TExpandMemBufferBase()
	{
		m_nBufferLength		= 0;	
		m_pBuffer			= NULL;
		m_bAttach           = FALSE;
		m_pCurrPos = NULL;
	}

	virtual ~TExpandMemBufferBase()
	{
		FreeBuffer();
	}

public:
	//初始化
	virtual void Init()
	{
		m_pBuffer = NULL;
		m_nBufferLength = 0;
		m_bAttach = FALSE;
		m_pCurrPos = NULL;
	}

	virtual void Init(T *pBuffer, long nLength)
	{
		FreeBuffer(FALSE);

		SetBufferLength(nLength);
		memcpy(m_pBuffer, pBuffer, nLength);
		m_pCurrPos = m_pBuffer;
	}

	virtual void SetBufferLength(long nBufferLen, BOOL bAllocAlways=TRUE)
	{
		if (nBufferLen < 0)
		{
			nBufferLen = 1;
		}

		if (bAllocAlways)
		{
			FreeBuffer();
			m_nBufferLength = nBufferLen;
			m_pBuffer = new T[nBufferLen+TExpandMemBuffer_ALLOC_SIZE_EX];
		}
		else
		{
			if (nBufferLen > m_nBufferLength)
			{
				FreeBuffer();
				m_nBufferLength = nBufferLen;
				m_pBuffer = new T[nBufferLen+TExpandMemBuffer_ALLOC_SIZE_EX];
			}
		}

		m_pCurrPos = m_pBuffer;
	}
	virtual void SetBuffer(T *pBuffer, long nLen)
	{
		if (m_nBufferLength < nLen)
		{
			SetBufferLength(nLen);
		}

		memcpy(m_pBuffer, pBuffer, nLen);
	}


	//内存释放
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE)
	{
		if (!m_bAttach)
		{
			if (m_pBuffer!= NULL)
			{
				delete m_pBuffer;
				m_pBuffer = NULL;
			}
		}

		if (!bOnlyDeleteBuffer)
		{
			m_nBufferLength	= 0;	
		}

		m_pCurrPos = NULL;
	}

	//内存拷贝
	virtual long CopyBuffer(T *pBuffer, long nLen, long nBeginPos, long nGap = 1)
	{
		if (nGap <= 1)
		{
			ASSERT (m_nBufferLength >= nLen);
			memcpy(m_pBuffer, pBuffer, nLen);
		}
		else
		{
			ASSERT(FALSE);
		}

		return 0;
	}

	//缓存关联
	virtual void AttachBuffer(TExpandMemBufferBase *pBuffer, BOOL bClearScr=FALSE)
	{
		FreeBuffer();
		m_pBuffer = pBuffer->GetBuffer();
		m_nBufferLength = pBuffer->GetBufferLength();
		m_bAttach = TRUE;

		if (bClearScr)
		{
			pBuffer->ClearBuffer();
		}
	}

	virtual void AttachBuffer(T *pBuffer, long nLen)
	{
		FreeBuffer();
		m_pBuffer = pBuffer;
		m_nBufferLength = nLen;
		m_bAttach = TRUE;
	}
	virtual void SetAttach(bool bAttach)	{		m_bAttach = bAttach;	}
	virtual void ClearBuffer()
	{
		m_pBuffer = NULL;
		m_nBufferLength = 0;
	}


	//缓存相关参数的获取
	virtual long GetBufferLength()                     {    return m_nBufferLength;                                }
	virtual T* GetBuffer()                          {    return m_pBuffer;                                      }

public:
	virtual long GetDataLength()	{	return (m_pCurrPos - m_pBuffer);	}
	virtual long GetLeftDataLength()	{	return (m_pBuffer + m_nBufferLength - m_pCurrPos);	}

	BOOL AllocBuffer(long nBufLen,long nExpendPercent)
	{
		if (nBufLen == 0)
		{
			nBufLen = 4096000;
		}

		long nCapacity = nBufLen + nBufLen * nExpendPercent / 100;

		SetBufferLength(nCapacity);
		m_pCurrPos = m_pBuffer;

		return TRUE;
	}

	BOOL AddBufferDataLen(long nAddLen)
	{
		if (nAddLen == 0)
		{
			return TRUE;
		}

		long nPos = m_pCurrPos - m_pBuffer;
		long nCapacity = m_nBufferLength + nAddLen;
		T *pNew = new T[nCapacity];
		memcpy(pNew, m_pBuffer, m_nBufferLength);
		FreeBuffer();
		m_pBuffer = pNew;
		m_pCurrPos = pNew + nPos;
		m_nBufferLength = nCapacity;

		return TRUE;
	}


	BOOL AppendBuffer(T *pBuf,long nLen)
	{
		long nCapacity = GetLeftDataLength();

		if (nCapacity > nLen)
		{
			memcpy(m_pCurrPos,pBuf,nLen);
			m_pCurrPos = m_pCurrPos + nLen;
			return TRUE;
		}

		AddBufferDataLen(nLen);
		memcpy(m_pCurrPos,pBuf,nLen);
		m_pCurrPos = m_pCurrPos + nLen;

		return TRUE;
	}


	void PosMoveByUsedLen(long nLenUsed)
	{
		long nDataLen = GetDataLength();
		long nLeftLen = nDataLen - nLenUsed;
		ASSERT (nLeftLen >= 0);

		if (nLeftLen > 0)
		{
			//将剩余数据移到缓存开头
			memcpy(m_pBuffer, m_pBuffer + nLenUsed, nLeftLen);
			//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PosMoveByUsedLen:%d"),nLeftLen);
		}
		else
		{
			//避免出现代码错误导致小于0
			nLeftLen = 0;
		}

		m_pCurrPos = m_pBuffer + nLeftLen;
	}


	void ZeroBuffer()
	{
		m_pCurrPos = m_pBuffer;
		memset(m_pBuffer, 0, m_nBufferLength);
	}


protected:
	long m_nBufferLength;	
	T *m_pBuffer;
	BOOL m_bAttach;

	T *m_pCurrPos;

};


#endif // !defined(_TExpandMemBufferBse_h__)
