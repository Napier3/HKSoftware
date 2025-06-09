// XRcdAnalysisBase.h: interface for the CXRcdAnalysisBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdAnalysisBase_H__)
#define _XRcdAnalysisBase_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRcdCalFilter.h"
#include "../Comtrade/ComtradeMngr.h"
#include "../../DataMngr/DvmDataset.h"

class CRcdCalFilterConfig : public CExBaseObject
{
public:
	CRcdCalFilterConfig();
	virtual ~CRcdCalFilterConfig();

	void InitBySampleRate(long nSampleRate);
public:
	long m_nPointsMode;  //0=ֱ�����ã� 1=�����ʵİٷֱȣ�1~20��
	long m_nPrevPoints;
	long m_nNextPoints;
	long m_nPointsEx; //ǰ�����ݵ����չ

};

typedef CXRcdCalFilter<unsigned short, short, long> CXRcdCalFilter_Short;

class CXRcdAnalysisBase : public CExBaseList
{
public:
	CXRcdAnalysisBase();
	virtual ~CXRcdAnalysisBase();

protected:
	CRcdComtradeFile *m_pComtradeFile;
	BOOL m_bNewComtradeFile;  //�Ƿ���������������Ķ���
	CDvmDataset m_oResults;  //��������������

	CRcdCalFilterConfig *m_pRespConfig;
	long m_nSampleRate;
	long m_nCalPoints;
	long m_nFilterPoints;
	long m_nTotalPoints;

public:
	void FreeAnalysis();
	void SetRcdComtradeFile(const CString &strComtradeFile);
	void SetRcdComtradeFile(CRcdComtradeFile *pComtradeFile);
	CDvmDataset* GetResults()	{	return &m_oResults;	}

public:
	virtual BOOL Analysis();
};

#endif // !defined(_XRcdAnalysisBase_H__)
