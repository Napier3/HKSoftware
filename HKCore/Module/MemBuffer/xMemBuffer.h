// MemBuffer.h: interface for the CMemBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MemBuffer_h__)
#define _MemBuffer_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct StCycleMemBufferPos
{
	BYTE *pBuffer;
	long nBufLength;
	long nBuf1BeginPos;
	long nBuf1EndPos;
	long nBuf2BeginPos;
	long nBuf2EndPos;
}* PCYCLEMEMBUFFERPOS, CYCLEMEMBUFFERPOS;

class CMemBuffer
{
public:	
	CMemBuffer();
	virtual ~CMemBuffer();

public:
	//初始化
	virtual void Init();
	virtual void SetBufferLength(long nBufferLen);
	virtual void SetDataLength(long nDataLen)//SetDataLength函数比较危险，非常规使用
	{
		m_nDataLength = nDataLen;
	}
	virtual void SetBuffer(BYTE *pBuffer, long nLen);

	//内存释放
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);
	
	virtual long CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap = 1);

	//缓存关联
	virtual void ClearBuffer();

	//缓存相关参数的获取
	virtual long GetDataLength()                       {    return m_nDataLength;                                  }
	virtual long GetBufferLength()                     {    return m_nBufferLength;                                }
	virtual BYTE* GetBuffer()                          {    return m_pBuffer;                                      }
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
	virtual BOOL GetBuffer(BYTE *pDestBuffer, long nBeginPos, long nLen);
	
protected:
	long m_nBufferLength;	
	long m_nDataLength;
	BYTE *m_pBuffer;
};


#endif // !defined(_MemBuffer_h__)
