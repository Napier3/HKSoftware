// XMemBufferBse.h: interface for the CXMemBufferBse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XMemBufferBse_h__)
#define _XMemBufferBse_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../OSInterface/OSInterface.h"

#define XMEMBUF_ALLOC_SIZE_EX   4

typedef struct XMemBufferBsePos
{
	BYTE *pBuffer;
	long nBufLength;
}* PXMEMBUFFERBASEPOS, XMEMBUFFERBASEPOS;

class CXMemBufferBse
{
public:	
	CXMemBufferBse();
	virtual ~CXMemBufferBse();

public:
	//初始化
	virtual void Init();
	virtual void Init(BYTE *pBuffer, long nLength);
	virtual void SetBufferLength(long nBufferLen, BOOL bAllocAlways=TRUE);
	virtual void SetBuffer(BYTE *pBuffer, long nLen);

	//内存释放
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);

	//内存拷贝
	virtual long CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap = 1);

	//缓存关联
	virtual void AttachBuffer(CXMemBufferBse *pBuffer, BOOL bClearScr=FALSE);
	virtual void AttachBuffer(BYTE *pBuffer, long nLen);
	virtual void SetAttach(bool bAttach)	{		m_bAttach = bAttach;	}
	virtual void ClearBuffer();

	//缓存相关参数的获取
	virtual long GetBufferLength()                     {    return m_nBufferLength;                                }
	virtual BYTE* GetBuffer()                          {    return m_pBuffer;                                      }
	
	virtual long GetBufferPos(XMEMBUFFERBASEPOS &oBufPos)
	{
		oBufPos.nBufLength = m_nBufferLength;
		oBufPos.pBuffer = m_pBuffer;
		return m_nBufferLength;
	}
	
protected:
	long m_nBufferLength;	
	BYTE *m_pBuffer;
	BOOL m_bAttach;
};


inline void xmem_get_cycle_range_index(long nMaxCount, long nCurrCount, long nCurrIndex
									   , long nIndex
									   , long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	if (nCurrCount == nMaxCount)
	{
		if (nIndex <= nCurrIndex)
		{
			nBegin1 = nIndex;
			nEnd1 = nCurrIndex-1;
			nBegin2 = -1;
			nEnd2 = -1;
		}
		else
		{
			nBegin1 = nIndex;
			nEnd1 = nCurrCount-1;
			nBegin2 = 0;
			nEnd2 = nCurrIndex-1;
		}
	}
	else
	{
		nBegin1 = nIndex;
		nEnd1 = nCurrIndex-1;
		nBegin2 = -1;
		nEnd2 = -1;
	}
}

#endif // !defined(_XMemBufferBse_h__)
