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
	long m_nPointsMode;  //0=直接设置； 1=采样率的百分比（1~20）
	long m_nPrevPoints;
	long m_nNextPoints;
	long m_nPointsEx; //前后数据点的扩展

};

typedef CXRcdCalFilter<unsigned short, short, long> CXRcdCalFilter_Short;

class CXRcdAnalysisBase : public CExBaseList
{
public:
	CXRcdAnalysisBase();
	virtual ~CXRcdAnalysisBase();

protected:
	CRcdComtradeFile *m_pComtradeFile;
	BOOL m_bNewComtradeFile;  //是否分析对象自身创建的对象
	CDvmDataset m_oResults;  //分析结果保存对象

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
