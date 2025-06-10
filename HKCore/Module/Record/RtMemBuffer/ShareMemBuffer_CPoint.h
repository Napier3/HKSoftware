// ShareMemBuffer_CPoint.h: interface for the CShareMemBuffer_CPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SHAREMEMBUFFER_CPOINT_H__)
#define _SHAREMEMBUFFER_CPOINT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemBuffer.h"

#define	MR1200_POINT_MEMFILENAME    "_mr1200_point_buffer.mrsm"
#define	MR1200_POINT_MAPNAME        "_mr1200_point_buffer"
#define	MR1200_POINT_MAPSIZE        104857600 //100M == 800M byte

#include "../../Module/ShareMem/ShareMemServerEx.h"
#include "MemBuffer_CPoint.h"

class CShareMemBuffer_CPoint  : public CMemBuffer_CPoint
{
public:
	CShareMemBuffer_CPoint();
	virtual ~CShareMemBuffer_CPoint();

	void CreateShareMemBufferCPoint(LPCTSTR pszMapName, long nPointSize);
public:
	// Õ∑≈ª∫¥Ê
	virtual void FreeBuffer();
	
protected:

	CShareMemServerEx *m_pMemServer;
	
};

#endif // !defined(_SHAREMEMBUFFER_CPOINT_H__)
