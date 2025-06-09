// DFT.h: interface for the CDFT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_)
#define AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PI 3.14159265359
#define DFT_LENGTH 36000 

#define PI_RADIAN_PER_DEG	0.01745329	// 3.141592654/180
#define PI_DEG_PER_RADIAN	57.29577951	// 180/3.141592654

class CDFT  
{
public:
	static CDFT* CreateDft();
	void ReleaseDFT();
	BOOL DFTSINGL(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTSINGL(BOOL bFirst,double *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	void TermTriangle();
	void InitTriangle(long nMaxDegree,long nDataLength ,long nCircleAmount = 2);
	void InitBuffer();
	void ClearBuffer();

	void SetDftCalGap(long nGap = 1)				{	m_nDftCalGap = nGap;	    }
	void SetCurrentDataLength(long nDataLen)		{	m_nDataLength = nDataLen;	}
	BOOL DFTCalByMap(BOOL bFirst,short* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTCalByMap(BOOL bFirst,float* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);

	BOOL DFTCalByMap(short* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree);
	BOOL CalDFT(double dCoef,short* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue);

	BOOL DFTCalByMap(float* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree);	
	BOOL CalDFT(double dCoef,float* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue);
private:
	CDFT();
	virtual ~CDFT();
	static CDFT*g_pDft;

	double **m_pCos;
	double **m_pSin;
	long m_nCalPos;
	long m_nMaxDegree;
	long m_nDataLength;
	
	long m_nDftCalGap;
	//////////////////使用查表法计算DFT的相关函数和变量
	double* m_pdSin;
	double* m_pdCos;
};

#endif // !defined(AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_)
