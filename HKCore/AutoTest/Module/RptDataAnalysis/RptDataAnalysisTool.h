#pragma once

#include "..\GuideBook\GuideBookDefine.h"
#include "..\GuideBook\GuideBookInterface.h"
#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\..\Module\CriticalSection\SynCriticalSection.h"

#include "RptDataAlsDefsMngr.h"
#include "..\..\..\Module\BaseClass\MemBufferDC.H"
#include "..\..\..\Module\Axis\DescartesAxis.h"

#define RPTDATA_ANALYSIS_STATE_NONE         0
#define RPTDATA_ANALYSIS_STATE_CREATED    1
#define RPTDATA_ANALYSIS_STATE_ANALYSIS   2

class CRptDataAnalysisTool : public CExBaseList
{
public:
	CRptDataAnalysisTool();
	virtual ~CRptDataAnalysisTool();
	
public:
	ULONG CreateNewAnalysis(const CString &strAnalysisDefFile);
	ULONG CloseAnalysis(void);
	ULONG AddRptFile(const CString &strRptFile);
	ULONG RptAnalysis(const CString &strConfigFile);
	ULONG SaveAnalysisFile(const CString &strDestFile);

	BOOL IsRptDataAnalysisCreated();
	BOOL IsRptDataAnalysisFinish();
	BOOL CanAddRptFile();
	BOOL CanAnalysis();


	CRptDataAlsDefsMngr* GetRptDataAlsDefsMngr()	{	return &m_oRptDataAlsDefsMngr;	}
private:
	CStringArray m_astrRptFile;
	CRptDataAlsDefsMngr m_oRptDataAlsDefsMngr;
	DWORD m_dwRptDataAnalysisState;

	void AddRptFileDatasTo(const CString &strFile);
	void AddRptDataTo(CGbItemBase *pItem);

//////////////////////////////////////////////////////////////////////////
//»æÍ¼
public:
	void CreateDraw(CDC *pDC, CRect rcClient);
	void DrawRptDataAnalysis(CRptDataAlsDef *pRptDataAlsDef);
	void DrawRptDataAnalysis(CDC *pDC);


protected:
	CMemBufferDC m_oMemDC;
	CDescartesAxis m_oAxis;
	CRect m_rcBorder;
	double  m_fXMax;
	double  m_fYMax;
	double  m_fXMin;
	double  m_fYMin;

	CPoint m_ptRptDataAnalysis[1024];
	long m_nRptDataCount;

	virtual void InitAxis();
	virtual void AdjustAxis(CRptDataAlsDef *pRptDataAlsDef);
	virtual void ResetAxis();
	virtual void SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void SetAxisMaxUnitCount(long nXAxisUnitCount, long nYAxisUnitCount);
};
