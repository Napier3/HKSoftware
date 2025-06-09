// DFTBase.h: interface for the CDFTBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DFT_BASE_H__)
#define _DFT_BASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DFT_PI          3.14159265359
#define DFT_LENGTH  36000 

#define PI_RADIAN_PER_DEG	   0.01745329	// 3.141592654/180
#define PI_DEG_PER_RADIAN	   57.29577951	// 180/3.141592654

class CDFTBase  
{
public:
	BOOL DFTSINGL(BOOL bFirst,double *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	void TermTriangle();
	void InitTriangle(long nMaxDegree,long nDataLength ,long nCircleAmount = 2);
	void AttatchSinCos(double* pdSin, double* pdCos);
	void InitSinCos();
	void ClearSinCos();

	BOOL DFTCalByMap(BOOL bFirst,float* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);

	BOOL DFTCalByMap(float* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree);	
	BOOL CalDFT(double dCoef,float* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue);

public:
	virtual void SetDftCalGap(long nGap = 1)				{	m_nDftCalGap = nGap;	    }
	virtual void SetCurrentDataLength(long nDataLen)		{	m_nDataLength = nDataLen;	}

protected:
	CDFTBase();
	virtual ~CDFTBase();

protected:
	double **m_pCos;
	double **m_pSin;
	long m_nCalPos;
	long m_nMaxDegree;
	long m_nDataLength;
	
	long m_nDftCalGap;

	//////////////////ʹ�ò������DFT����غ����ͱ���
	double* m_pdSin;
	double* m_pdCos;
	BOOL m_bAttatch;
};

#endif // !defined(_DFT_BASE_H__)
