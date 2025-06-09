// XRcdSyncAnalysis.h: interface for the CXRcdSyncAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdSyncAnalysis_H__)
#define _XRcdSyncAnalysis_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRcdCalRespTime.h"

class CXRcdSyncAnalysis : public CXRcdCalRespTime
{
public:
	CXRcdSyncAnalysis();
	virtual ~CXRcdSyncAnalysis();

	//�����ؽ��
	double m_fTime_50_U, m_fTime_50_I; //��ѹ����50%��λ��
	double m_fValue_50_U, m_fValue_50_I; //��ѹ����50%��λ��

public:
	virtual BOOL Analysis(CRcdCalFilterConfig *pRespConfig);
	
	virtual void CalRising(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag);
	virtual void CalFalling(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag);

protected:
	BOOL CalIChannel(long nBegin ,long nEnd);
	void CalIChannel(CComtradeAnalogData *pAnalogI);
};

#endif // !defined(_XRcdSyncAnalysis_H__)
