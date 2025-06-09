// MemBuffer_CPoint.h: interface for the CMemBuffer_CPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_)
#define AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MemBuffer_UnsignedShort.h"
#include "MemBuffer.h"

class CMemBuffer_CPoint  
{
public:
	CMemBuffer_CPoint();
	virtual ~CMemBuffer_CPoint();

public:
	//�ͷŻ���
	virtual void FreeBuffer();

	//��û�ͼ���ݼ���Ӧ�Ĳ���
	void InitValueXY(double fCoefX, double fOffsetX, CMemBuffer_UShort *pBufferX, double fCoefY, double fOffsetY,  CMemBuffer_UShort *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueXY(double fCoefX, double fOffsetX, CMemBuffer_Long *pBufferX, double fCoefY, double fOffsetY,  CMemBuffer_Long *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueXY(double fCoefX, double fOffsetX, double fCoefY, double fOffsetY , long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void InitValueY(double fCoef, double fOffset, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueY(double fCoef, double fOffset, CMemBuffer_UShort *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueY(double fCoef, double fOffset, CMemBuffer_Long *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueY(double fCoef, double fOffset, CMemBuffer_Float *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void InitValueX(double fCoef, double fOffset,long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);
	void InitValueX(double fCoef, double fOffset, CMemBuffer_UShort *pBufferX, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);	
	void InitValueX(double fCoef, double fOffset, CMemBuffer_Long *pBufferX, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);	
	void InitValueX(double fCoef, double fOffset, CMemBuffer_Float *pBufferY, long nSrcBeginPos = -1, long nSrcLength = -1, long nGap=1);

	void CalValueY(double fCoef, double fOffset,CMemBuffer_UShort *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin = -1 ,long nBuffer2End = -1, long nGap = 1);
	void CalValueY(double fCoef, double fOffset,CMemBuffer_Long *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin = -1 ,long nBuffer2End = -1, long nGap = 1);
	void CalValueY(double fCoef, double fOffset,CMemBuffer_Float *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin = -1 ,long nBuffer2End = -1, long nGap = 1);
	//�������
	void AttachBuffer(CMemBuffer_UShort *pBufferX, CMemBuffer_UShort *pBufferY);
	void AttachBufferY(CMemBuffer_UShort *pBufferY);
	void AttachBufferX(CMemBuffer_UShort *pBufferX);
	void AttachBuffer(CMemBuffer_Long *pBufferX, CMemBuffer_Long *pBufferY);
	void AttachBufferY(CMemBuffer_Long *pBufferY);
	void AttachBufferX(CMemBuffer_Long *pBufferX);
	void SetBufferLength(long nBufferLen);
	long GetBufferLength()      {   return m_nBufferLength;   };

	//ȡ���������
	void DettachBuffer();
	void DettachBufferY();
	void DettachBufferX();

	//��û�ͼ�������С
	long GetCurrUseLength()     {  return m_nCurrUseLength;    }
	CPoint* GetBuffer()         {  return m_pBuffer;           }

    void GetBeginAndEndPosition(long nBufferLength, long nDataLength, long nDataFillBeginPos
		, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1
		, long &nSrcBeginPos2, long &nSrcEndPos2);

// 	void GetBeginAndEndPosition2(CMemBuffer_UShort* pBuffer, long nSrcBeginPos, long nSrcLength
// 		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2, long nSpace=0);
	void GetBeginAndEndPosition(CMemBuffer_UShort* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2);
// 	void GetBeginAndEndPosition2(CMemBuffer_Long* pBuffer, long nSrcBeginPos, long nSrcLength
// 		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2, long nSpace=0);
	void GetBeginAndEndPosition(CMemBuffer_Long* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2);
	void GetBeginAndEndPosition(CMemBuffer_Float* pBuffer, long nSrcBeginPos, long nSrcLength
		, long &nSrcBeginPos1, long &nSrcEndPos1, long &nSrcBeginPos2, long &nSrcEndPos2);
	
	void SetCurrUseLength(long nCurrUseLength) {	m_nCurrUseLength = nCurrUseLength;	} //fdp add 2010.5.1 ��Ϊ�е�ʱ����Ҫ���ⲿ���û������ݣ�������Ҫ����ʹ�õĳ���
protected:
	long m_nCurrUseLength;
	long m_nBufferLength;	
	CPoint *m_pBuffer;

	CMemBuffer_UShort *m_pBufferX;
	CMemBuffer_UShort *m_pBufferY;
	CMemBuffer_Long *m_pBufferX_Long;
	CMemBuffer_Long *m_pBufferY_Long;
	
	double m_dCoefX,m_dCoefY;
	double m_dOffSetX,m_dOffSetY;
	
};

#endif // !defined(AFX_MEMBUFFER_CPOINT_H__275F21D0_9FFD_408F_B566_5ADD14B23C4F__INCLUDED_)
