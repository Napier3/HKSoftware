// XRcdAnalysisTool.h: interface for the CXRcdAnalysisTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdAnalysisTool_H__)
#define _XRcdAnalysisTool_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRcdCalRespTime.h"
#include "../../DataMngr/DataGroup.h"

class CXRcdAnalysisTool : public CDataGroup
{
public:
	CXRcdAnalysisTool();
	virtual ~CXRcdAnalysisTool();
	CValues m_oResults;   //分析的结果

protected:
	CString m_strRcdAnalysisID; //分析功能ID
	CString m_strChID;
	float     m_fChValue;

	//波形绘图的宽度和高度
	long m_nWidth;
	long m_nHeight;

	CDvmData *m_pRcdAnalysis; //波形分析对象
	CDataGroup *m_pRcdDraw;   //绘图定义对象

public:
	virtual void InitAfterRead();
	void OpenRcdAnalysisFile(const CString &strFile);

	BOOL RcdAnalysis(const CString &strComtradeFile);
	BOOL RcdAnalysis(CRcdComtradeFile *pComtradeFile);

protected:
	BOOL RcdAnalysis_RespTime(CRcdComtradeFile *pComtradeFile);
	BOOL RcdAnalysis_Sync(CRcdComtradeFile *pComtradeFile);

};

#endif // !defined(_XRcdAnalysisTool_H__)
