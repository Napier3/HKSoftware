// CycleMemBuffer.h: interface for the CCycleMemBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CycleMemBuffer_h__)
#define _CycleMemBuffer_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XMemBufferBse.h"

struct CycleMemBufferPos : public XMEMBUFFERBASEPOS
{
	//BYTE *pBuffer;
	//long nBufLength;
	long nBuf1BeginPos;
	long nBuf1EndPos;
	long nBuf2BeginPos;
	long nBuf2EndPos;
};

typedef struct CycleMemBufferPos*PCYCLEMEMBUFFERPOS;
typedef struct CycleMemBufferPos CYCLEMEMBUFFERPOS;

class CCycleMemBuffer : public CXMemBufferBse
{
public:	
	CCycleMemBuffer();
	virtual ~CCycleMemBuffer();


#ifdef CYCLEMEMBUFER_USE_BUF_ID
	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一
#endif

public:
	//初始化
	void Init();
	void Init(BYTE *pBuffer, long nLength);
	virtual void SetBufferLength(long nBufferLen, BOOL bAllocAlways=TRUE);
	virtual void SetDataLength(long nDataLen)//SetDataLength函数比较危险，非常规使用
	{
		m_nDataLength = nDataLen;
	}
	virtual void SetBuffer(BYTE *pBuffer, long nLen);

	//内存释放
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);

	//内存拷贝
	virtual long GetBufferAppendPos(long nBeginPos, long nLen, long nGap, BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	virtual long AppendBuffer(long nLen, long nGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	virtual long AppendBuffer(CCycleMemBuffer *pBuffer, long &lCopyBeginPos, long nGap = 1);
	virtual long AppendBuffer(BYTE *pBuffer, long nLen, long nGap = 1);
	virtual long AppendBufferByPos(BYTE *pBuffer, long nBeginPos, long nEndPos, long nGap = 1);
	virtual long CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap = 1);
	
	//缓存关联
	virtual void AttachBuffer(CCycleMemBuffer *pBuffer, BOOL bClearScr=FALSE);
	virtual void AttachBuffer(BYTE *pBuffer, long nLen);
	virtual void SetAttach(bool bAttach)	{		m_bAttach = bAttach;	}
	virtual void ClearBuffer();

	//缓存相关参数的获取
	virtual long GetDataLength()                       {    return m_nDataLength;                                  }
	virtual long GetDataFillBeginPosition()            {    return m_nDataFillBeginPos;                            }
	virtual long GetDataFillEmptyLen()                 {    return m_nBufferLength - m_nDataFillBeginPos;          }
	virtual BYTE* GetDataFillBeginBuffer()             {    return m_pBuffer + m_nDataFillBeginPos;                }
	virtual long GetBufferLength()                     {    return m_nBufferLength;                                }
	virtual BYTE* GetBuffer()                          {    return m_pBuffer;                                      }
	virtual BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < m_nBufferLength); }
	virtual void OffsetDataFillBeginPosition(long nLen);
	virtual long GetLenFromCurrToFillBeginPos(long nBeginPos);
	virtual long GetBufferPos(long nBeginPos, long nLen, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	
	virtual long GetBufferPos(CYCLEMEMBUFFERPOS &oBufPos)
	{
		oBufPos.nBuf1BeginPos = 0;
		oBufPos.nBuf1EndPos = m_nDataLength;
		oBufPos.nBuf2BeginPos = -1;
		oBufPos.nBuf2EndPos = -1;
		oBufPos.nBufLength = m_nBufferLength;
		oBufPos.pBuffer = m_pBuffer;
		return m_nDataLength;
	}
	virtual long GetBufferPos(XMEMBUFFERBASEPOS &oBufPos)
	{
		oBufPos.nBufLength = m_nBufferLength;
		oBufPos.pBuffer = m_pBuffer;
		return m_nBufferLength;
	}

	virtual long GetBufferPos(long nBeginPos, long nLen, CYCLEMEMBUFFERPOS &oBufPos)
	{
		GetBufferPos(nBeginPos, nLen, oBufPos.nBuf1BeginPos, oBufPos.nBuf1EndPos, oBufPos.nBuf2BeginPos, oBufPos.nBuf2EndPos);
		oBufPos.nBufLength = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos + 1;
		oBufPos.pBuffer = m_pBuffer;
		
		if (oBufPos.nBuf2BeginPos >= 0)
		{
			oBufPos.nBufLength += oBufPos.nBuf2EndPos - oBufPos.nBuf2BeginPos;
		}

		return oBufPos.nBufLength;
	}
	virtual long GetBufferPos(long nBeginPos, long nLen, PCYCLEMEMBUFFERPOS pBufPos)
	{
		return GetBufferPos(nBeginPos, nLen, *pBufPos);
	}
	virtual long GetDataLength(long nBeginPos);
	virtual BOOL GetBuffer(BYTE *pDestBuffer, long nBeginPos, long nLen);
	virtual void ResetOffsetDataFillBeginPosition()  {    m_nDataFillBeginPos = 0;    m_nDataLength = 0;    }
	virtual void ResetOffsetDataFillBeginPosition(long nDataFillBeginPos, long nDataLength);
	
protected:
	//long m_nBufferLength;	
	long m_nDataFillBeginPos;
	long m_nDataLength;
	//BYTE *m_pBuffer;
	//BOOL m_bAttach;
};


#endif // !defined(_CycleMemBuffer_h__)
