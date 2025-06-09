// XRcdCalRespTime.h: interface for the CXRcdCalRespTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdCalRespTime_H__)
#define _XRcdCalRespTime_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRcdAnalysisBase.h"

class CXRcdCalRespConfig : public CRcdCalFilterConfig
{
public:
	CXRcdCalRespConfig();
	virtual ~CXRcdCalRespConfig();

	CString m_strChID;  //������ͨ��ID
	float m_fChValue; //ͨ��������ֵ��������DELTAԤ������
};

class CXRcdCalRespTime : public CXRcdAnalysisBase
{
public:
	CXRcdCalRespTime();
	virtual ~CXRcdCalRespTime();

	long m_nHasRising, m_nHasFaling; //�Ƿ��������غ��½���
	
	//�����ؽ��
	double m_fTimeRising_0, m_fTimeRising_10, m_fTimeRising_90, m_fTimeRising_100; //10%��90%��ʱ��λ��
	long m_nRisingBegin, m_nRisingEnd;  //�����ؿ�ʼ������
	double m_fPeakVal;    //��ֵ

	//�½��ؽ��
	double m_fTimeFalling_0, m_fTimeFalling_10, m_fTimeFalling_90, m_fTimeFalling_100; //10%��90%��ʱ��λ��
	long m_nFallingBegin, m_nFallingEnd;  //�½��ؿ�ʼ������
	double m_fValleyVal;    //��ֵ

public:
	virtual BOOL Analysis(CRcdCalFilterConfig *pRcdCalConfig);
	
protected:
	CComtradeAnalogData* FindAnalog(const CString &strChID);
	virtual BOOL InitCurrAnalogData();
	virtual void InitAnalysisParas();
	virtual BOOL AnalysisRespRising(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter);
	virtual BOOL AnalysisRespFalling(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter);
	virtual void CalRising(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag);
	virtual void CalFalling(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag);

protected:
	CComtradeAnalogData *m_pAnalogData;
	unsigned short m_nDeltaValue;
	

	long FindRising(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter);
	long FindFalling(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter);

	short* ValidAndCreateBuffer(CComtradeAnalogData *pAnalog, short* &pNewValBuf, short* &pBufEnd);
	double CalRisingPointTime(short *pBuf, short *pBufEnd, double dValue, double dCoef, double dZero);
	double CalFallingPointTime(short *pBuf, short *pBufEnd, double dValue, double dCoef, double dZero);
	double CalRisingPointTime(short *pBuf, short *pBufEnd, double dValue);
	double CalFallingPointTime(short *pBuf, short *pBufEnd, double dValue);
	double CalRisingPointTime(CComtradeAnalogData *pAnalog, double dValue);
	double CalFallingPointTime(CComtradeAnalogData *pAnalog, double dValue);

	void CalRising(long nBeginPos, long nEndPos,  long nMaxMagPos, short vMaxMag);
	void CalFalling(long nBeginPos, long nEndPos,  long nMaxMagPos, short vMaxMag);

	
	void WriteRcdAnalysisFile(long nBeginPos, long nEndPos, const CString &strNameAppend
		, double fTime10, double fTime90, double fVal10, double fVal90);
};

#endif // !defined(_XRcdCalRespTime_H__)
