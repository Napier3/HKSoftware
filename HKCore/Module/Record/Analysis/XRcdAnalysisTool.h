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
	CValues m_oResults;   //�����Ľ��

protected:
	CString m_strRcdAnalysisID; //��������ID
	CString m_strChID;
	float     m_fChValue;

	//���λ�ͼ�Ŀ�Ⱥ͸߶�
	long m_nWidth;
	long m_nHeight;

	CDvmData *m_pRcdAnalysis; //���η�������
	CDataGroup *m_pRcdDraw;   //��ͼ�������

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
