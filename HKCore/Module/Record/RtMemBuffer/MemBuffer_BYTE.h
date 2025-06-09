// MemBuffer_BYTE.h: interface for the CMemBuffer_BYTE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MemBuffer_BYTE_H__)
#define _MemBuffer_BYTE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtMemBufScript.h"
#include "MemBuffer_UnsignedShort.h"
#include "MemBufferDef.h"

class CMemBuffer_BYTE  : public CMemBufferInterface
{
public:	
	CMemBuffer_BYTE();
	virtual ~CMemBuffer_BYTE();

	virtual UINT GetClassID()    {    return MEMCLASSID_LONG;     }
	
	virtual long CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap);

public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//��ʼ��
	void SetBufferLength(long lBufferLen);

	//�ڴ��ͷ�
	void FreeBuffer();

	//�ڴ濽��
	//long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_BYTE *pBuffer, long &lCopyBeginPos, long lGap = 1);
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

	//�������
	void AttachBuffer(CMemBuffer_BYTE *pBuffer);
	void AttachBuffer(long *pBuffer, long lLen);

	//������ز����Ļ�ȡ
	long* GetDataFillBeginBuffer()   {    return m_pBuffer + m_nDataFillBeginPos;    }
	long* GetBuffer_long()                {    return m_pBuffer;                          }
	
protected:
	long *m_pBuffer;

};

/*
class CComplexMemBuffer_BYTE : public CMemBuffer_BYTE
{
public:
	CComplexMemBuffer_BYTE();
	virtual ~CComplexMemBuffer_BYTE();
	
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
*/

#endif // !defined(_MemBuffer_BYTE_H__)
