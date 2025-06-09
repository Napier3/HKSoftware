// MemBuffer_CPoint.h: interface for the CMemBuffer_CPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_)
#define AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MemBuffer_Long.h"
#include "MemBufferDef.h"
#include "MemBuffer_Long.h"
#include "MemBuffer_Float.h"

class CMemBuffer_CPoint  
{
public:
	CMemBuffer_CPoint();
	virtual ~CMemBuffer_CPoint();

public:
	//释放缓存
	virtual void FreeBuffer();

	//获得绘图数据及相应的参数
	void InitValueXY(double fCoefX, double fOffsetX, CMemBuffer_Long *pBufferX, double fCoefY, double fOffsetY,  CMemBuffer_Long *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueXY(double fCoefX, double fOffsetX, double fCoefY, double fOffsetY , long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void InitValueY(double fCoef, double fOffset, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueY(double fCoef, double fOffset, CMemBuffer_Long *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueY(double fCoef, double fOffset, CMemBuffer_Float *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void InitValueX(double fCoef, double fOffset,long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueX(double fCoef, double fOffset, CMemBuffer_Long *pBufferX, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);	
	void InitValueX(double fCoef, double fOffset, CMemBuffer_Float *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void CalValueY(double fCoef, double fOffset,CMemBuffer_Long *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin = -1 ,long nBuffer2End = -1, long nGap = 1);
	void CalValueY(double fCoef, double fOffset,CMemBuffer_Float *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin = -1 ,long nBuffer2End = -1, long nGap = 1);
	//缓存关联
	void AttachBuffer(CMemBuffer_Long *pBufferX, CMemBuffer_Long *pBufferY);
	void AttachBufferY(CMemBuffer_Long *pBufferY);
	void AttachBufferX(CMemBuffer_Long *pBufferX);
	void SetBufferLength(long nBufferLen);
	long GetBufferLength()      {   return m_nBufferLength;   };

	//取消缓存关联
	void DettachBuffer();
	void DettachBufferY();
	void DettachBufferX();

	//获得绘图的区域大小
	long GetCurrUseLength()     {  return m_nCurrUseLength;    }
	CPoint* GetBuffer()         {  return m_pBuffer;           }

	void GetBeginAndEndPosition2(CMemBuffer_Long* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2, long nSpace=0);
	void GetBeginAndEndPosition(CMemBuffer_Long* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2);
	void GetBeginAndEndPosition(CMemBuffer_Float* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2);
	
	void SetCurrUseLength(long nCurrUseLength) {	m_nCurrUseLength = nCurrUseLength;	} //fdp add 2010.5.1 因为有的时候需要在外部设置缓存数据，所以需要设置使用的长度
protected:
	long m_nCurrUseLength;
	long m_nBufferLength;	
	CPoint *m_pBuffer;

	CMemBuffer_Long *m_pBufferX;
	CMemBuffer_Long *m_pBufferY;
	
	double m_dCoefX,m_dCoefY;
	double m_dOffSetX,m_dOffSetY;
	
};

#endif // !defined(AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_)
