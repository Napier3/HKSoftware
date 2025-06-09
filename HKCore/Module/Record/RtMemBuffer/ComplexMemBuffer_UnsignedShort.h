// ComplexMemBuffer_UnsignedShort.h: interface for the CMemBuffer_UnsignedShort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_COMPLEXMEMBUFFER_UNSIGNEDSHORT_H__)
#define _COMPLEXMEMBUFFER_UNSIGNEDSHORT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtMemBufScript.h"
#include "MemBufferDef.h"
#include "MemBuffer_UnsignedShort.h"


class CComplexMemBuffer_UnsignedShort : public CMemBuffer_UnsignedShort
{
public:
	CComplexMemBuffer_UnsignedShort();
	virtual ~CComplexMemBuffer_UnsignedShort();
	
	virtual UINT GetClassID()    {    return MEMCLASSID_COMPLEXUSHORT;     }
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End);
	void SetSrcMemBufferCount(long nnSrcMemBufCount)                  {   m_nSrcMemBufferCount = nnSrcMemBufCount;   }
	void SetSrcBuffer(long nIndex, CMemBuffer_UnsignedShort *pBuffer) {   m_pSrcBuffer[nIndex] = pBuffer;              }
	
public:
	long  m_nSrcMemBufferCount;
	CMemBuffer_UnsignedShort *m_pSrcBuffer[COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT];
	
	CRtComplexBufUShortScript *m_pScript;

#ifdef _debug_complex_channel
	void CreateScript();
#endif
};

#endif // !defined(_COMPLEXMEMBUFFER_UNSIGNEDSHORT_H__)
