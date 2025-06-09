// MemBuffer_Long.h: interface for the CMemBuffer_Long class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFER_LONG_H__)
#define _MEMBUFFER_LONG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtMemBufScript.h"
#include "MemBuffer_UnsignedShort.h"
#include "MemBufferDef.h"

class CMemBuffer_Long  : public CMemBufferInterface
{
public:	
	CMemBuffer_Long();
	virtual ~CMemBuffer_Long();

	virtual UINT GetClassID()    {    return MEMCLASSID_LONG;     }
	
	virtual long CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap);

public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//初始化
	//void Init();
	void SetBufferLength(long lBufferLen);

	//内存释放
	void FreeBuffer();

	//内存拷贝
	//long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_Long *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(long *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(long *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);
	long AddValue(long *pValue);
	long AddValue(long nValue);

	void SetValue(long nValue, long nPos)
	{
		ASSERT ( (0 <= nPos) && (nPos < m_nBufferLength) );
		m_pBuffer[nPos] = nValue;
	}
// 	void SetPosition(long nPos, long nDataCount)
// 	{
// 		m_nDataFillBeginPos = nPos;
// 		m_nDataLength = nDataCount;
// 	}

	//缓存关联
	void AttachBuffer(CMemBuffer_Long *pBuffer);
	void AttachBuffer(long *pBuffer, long lLen);

	//缓存相关参数的获取
	long* GetDataFillBeginBuffer()   {    return m_pBuffer + m_nDataFillBeginPos;    }
	long* GetBuffer_long()                {    return m_pBuffer;                          }
// 	BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < m_nBufferLength); }
// 	void OffsetDataFillBeginPosition(long nLen);
	
protected:
	long *m_pBuffer;

};

class CComplexMemBuffer_Long : public CMemBuffer_Long
{
public:
	CComplexMemBuffer_Long();
	virtual ~CComplexMemBuffer_Long();
	
	virtual UINT GetClassID()    {    return MEMCLASSID_COMPLEXLONG;     }
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End);
	void SetSrcMemBufferCount(long nnSrcMemBufCount)                  {   m_nSrcMemBufferCount = nnSrcMemBufCount;   }
	void SetSrcBuffer(long nIndex, CMemBuffer_UnsignedShort *pBuffer) {   m_pSrcBuffer[nIndex] = pBuffer;              }
	
public:
	long  m_nSrcMemBufferCount;
	CMemBuffer_UnsignedShort *m_pSrcBuffer[COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT];
	
	CRtComplexBufLongScript *m_pScript;

#ifdef _debug_complex_channel
	void CreateScript();
#endif
};

#endif // !defined(_MEMBUFFER_LONG_H__)
