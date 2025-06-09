#include "stdafx.h"
#include "RptDataAnalysisTool.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRptDataAnalysisTool::CRptDataAnalysisTool()
{
	m_dwRptDataAnalysisState = RPTDATA_ANALYSIS_STATE_NONE;
	m_rcBorder = CRect(0, 0, 100, 100);
	m_fXMax = 5.1;
	m_fYMax = 0.5;
	m_fXMin = 0;
	m_fYMin = 0;

	SetAxisName(_T("报告"), _T("数值"), _T(" 报告数据分析"));
	InitAxis();
}

CRptDataAnalysisTool::~CRptDataAnalysisTool()
{
	CloseAnalysis();
}

ULONG CRptDataAnalysisTool::CreateNewAnalysis(const CString &strAnalysisDefFile)
{
	CString strFile;

	if (IsFileExist(strAnalysisDefFile))
	{
		strFile = strAnalysisDefFile;
	}
	else
	{
		strFile = _P_GetConfigPath();

		if (strAnalysisDefFile.GetLength() == 0)
		{
			strFile += _T("AtsRptDataAnalysis.xml");
		}
		else
		{
			strFile +=strAnalysisDefFile;
		}

	}

	CloseAnalysis();
	
	BOOL bRet = m_oRptDataAlsDefsMngr.OpenXmlFile(strFile, CRptAnalysisXmlRWKeys::g_pXmlKeys);

	if (bRet)
	{
		m_dwRptDataAnalysisState = RPTDATA_ANALYSIS_STATE_CREATED;
	}

	return m_dwRptDataAnalysisState;
}

ULONG CRptDataAnalysisTool::CloseAnalysis(void)
{
	m_astrRptFile.RemoveAll();
	m_oRptDataAlsDefsMngr.FreeRptDataAlsDefsMngr();
	DeleteAll();
	m_dwRptDataAnalysisState = RPTDATA_ANALYSIS_STATE_NONE;

	return 0;
}

ULONG CRptDataAnalysisTool::AddRptFile(const CString &strRptFile)
{
	ASSERT (m_dwRptDataAnalysisState == RPTDATA_ANALYSIS_STATE_CREATED);

	long nCount = m_astrRptFile.GetCount();
	long nIndex = 0;
	BOOL bCanAdd = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strRptFile == m_astrRptFile.GetAt(nIndex))
		{
			bCanAdd = FALSE;
			break;
		}
	}
	
	if (bCanAdd)
	{
		m_astrRptFile.Add(strRptFile);
	}

	return bCanAdd;
}

ULONG CRptDataAnalysisTool::RptAnalysis(const CString &strConfigFile)
{
	ASSERT (m_dwRptDataAnalysisState == RPTDATA_ANALYSIS_STATE_CREATED);

	long nCount = m_astrRptFile.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		AddRptFileDatasTo(m_astrRptFile.GetAt(nIndex));
	}

	m_dwRptDataAnalysisState = RPTDATA_ANALYSIS_STATE_ANALYSIS;

	return 0;
}

ULONG CRptDataAnalysisTool::SaveAnalysisFile(const CString &strDestFile)
{
	ASSERT (m_dwRptDataAnalysisState == RPTDATA_ANALYSIS_STATE_ANALYSIS);

	return 0;
}

BOOL CRptDataAnalysisTool::IsRptDataAnalysisCreated()
{
	return m_dwRptDataAnalysisState >= RPTDATA_ANALYSIS_STATE_CREATED;
}

BOOL CRptDataAnalysisTool::IsRptDataAnalysisFinish()
{
	return m_dwRptDataAnalysisState == RPTDATA_ANALYSIS_STATE_ANALYSIS;
}

BOOL CRptDataAnalysisTool::CanAddRptFile()
{
	return (m_dwRptDataAnalysisState == RPTDATA_ANALYSIS_STATE_CREATED);
}

BOOL CRptDataAnalysisTool::CanAnalysis()
{
	if (m_dwRptDataAnalysisState != RPTDATA_ANALYSIS_STATE_CREATED)
	{
		return FALSE;
	}

	return (m_astrRptFile.GetCount() >= 2);
}

void CRptDataAnalysisTool::AddRptFileDatasTo(const CString &strFile)
{
	CGuideBook *pGuideBook = new CGuideBook();
	pGuideBook->OpenXmlReportFile(strFile);
	pGuideBook->InitGuideBook();
	CItemContainer *pItemContainer = (CItemContainer*)pGuideBook->GetItemContainer();

	pItemContainer->ClearFilter();
	long nIndexFilter = pItemContainer->CreateAttrFilter(GbFilterAttrIndex,GbFilterOptrMoreThanEqual,-1);
	pItemContainer->Query(nIndexFilter, TRUE);

	CGbItemBase *pItem = NULL;
	pItem = pItemContainer->GetFirstItem();

	while (pItem != NULL)
	{
		AddRptDataTo(pItem);
		pItem = pItemContainer->GetNextItem();
	}
	
	pItemContainer->RemoveAll();
	delete pGuideBook;
	pGuideBook = NULL;
}

void CRptDataAnalysisTool::AddRptDataTo(CGbItemBase *pItem)
{
	CExBaseList *pListDataRef = m_oRptDataAlsDefsMngr.GetAllDataAlsDef();
	POS pos = pListDataRef->GetHeadPosition();
	CRptDataAlsDef *pRptDataAlsDef = NULL;
	double dValue = 0;
	CReport *pReport = NULL;
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pRptDataAlsDef = (CRptDataAlsDef *)pListDataRef->GetNext(pos);

		if (pRptDataAlsDef->MatchItem(pItem))
		{
			pReport = pItem->GetReport(-1);

			if (pReport == NULL)
			{
				continue;
			}

			if (pReport->m_pValues == NULL)
			{
				continue;
			}

			pValue = (CValue*)pReport->m_pValues->FindByID(pRptDataAlsDef->m_strValueID);

			if (pValue == NULL)
			{
				continue;
			}

			pRptDataAlsDef->AddDataValue(CString_To_double(pValue->m_strValue));
		}
	}
}

void CRptDataAnalysisTool::CreateDraw(CDC *pDC, CRect rcClient)
{
	m_oMemDC->Create(pDC, rcClient);
	m_oMemDC->FillSolidRect(RGB(255, 255, 255));
	rcClient.top += 15;
	m_rcBorder = rcClient;
	m_oAxis.SetBorder(rcClient);
}


void CRptDataAnalysisTool::DrawRptDataAnalysis(CRptDataAlsDef *pRptDataAlsDef)
{
	CDC *pDC = m_oMemDC->GetDC();

	if (pDC == NULL)
	{
		return;
	}

	if (pRptDataAlsDef != NULL)
	{
		m_oAxis.SetAxisTitle(pRptDataAlsDef->m_strName);
		AdjustAxis(pRptDataAlsDef);
	}
	
	m_oMemDC->FillSolidRect(RGB(255, 255, 255));
	m_oAxis.DrawAxis(pDC, 1, 0, 0);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	if (m_nRptDataCount >= 2)
	{
		pDC->Polyline(m_ptRptDataAnalysis, m_nRptDataCount);
	}

	pDC->SelectObject(pOldPen);
}

void CRptDataAnalysisTool::DrawRptDataAnalysis(CDC *pDC)
{
	if (m_oMemDC->GetDC() == NULL)
	{
		return;
	}

	m_oMemDC->Draw(pDC);
}


void CRptDataAnalysisTool::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	m_oAxis.SetXAxisName(strXAxisName);
	m_oAxis.SetYAxisName(strYAxisName);
	m_oAxis.SetAxisTitle(strAxisTitle);
}

void CRptDataAnalysisTool::SetAxisMaxUnitCount(long nXAxisUnitCount, long nYAxisUnitCount)
{
	m_oAxis.SetXAxisMaxUnitCount(nXAxisUnitCount);
	m_oAxis.SetYAxisMaxUnitCount(nYAxisUnitCount);
}


void CRptDataAnalysisTool::InitAxis()
{
	SetAxisMaxUnitCount(40, 40);
	m_oAxis.LockXCarryOneGap(TRUE, 1);
	m_oAxis.SetAxisXYUnitLock(FALSE);
	m_oAxis.SetLeftGap(0);
	m_oAxis.SetTopGap(6);
	m_oAxis.SetRightGap(5);
	m_oAxis.SetBottomGap(0);
	m_oAxis.SetYAxisAreaWidth(45);
	m_oAxis.SetBorder(m_rcBorder);	
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	m_oAxis.ResetAxis();	
	//m_oAxis.SetAxisBackColor(RGB(255, 255, 255));
	m_oAxis.SetWorkAreaBkColor(RGB(255, 255, 255));

	m_oAxis.ClearAxisDrawStyleEx(DESCARTESAXISDRAW_AXISBODER);
	m_oAxis.ClearAxisDrawStyleEx(DESCARTESAXISDRAW_WORKAREA);

	m_oAxis.ClearAxisDrawStyleEx(DESCARTESAXISDRAW_XAXIS_TENTHSCALE);
	m_oAxis.ClearAxisDrawStyleEx(DESCARTESAXISDRAW_XAXIS_HALFSCCALE);
// #define DESCARTESAXISDRAW_XAXIS_TENTHSCALE	0x00000040	//
// #define DESCARTESAXISDRAW_XAXIS_HALFSCCALE	0x00000080	//

}

void CRptDataAnalysisTool::AdjustAxis(CRptDataAlsDef *pRptDataAlsDef)
{
	m_nRptDataCount = pRptDataAlsDef->m_darrRptDataValue.GetCount();

	long nIndex = 0;
	double fMinX = 0,fMaxX = m_nRptDataCount + 0.5;
	double fMaxY = -999999, dValue = 0;

	for (nIndex=0; nIndex<m_nRptDataCount; nIndex++)
	{
		dValue = pRptDataAlsDef->m_darrRptDataValue.GetAt(nIndex);

		if (fMaxY < dValue)
		{
			fMaxY = dValue;
		}	
	}

	fMaxY *= 1.1f;
	m_fXMax = fMaxX; m_fYMax = fMaxY;
	m_oAxis.SetXYAxisMinMaxVal(0, 0, fMaxX, fMaxY);
	m_oAxis.SetBorder(m_rcBorder);
	ResetAxis();

	for (nIndex=0; nIndex<m_nRptDataCount; nIndex++)
	{
		m_oAxis.LogicPointToDevicePoint(nIndex+1, pRptDataAlsDef->m_darrRptDataValue[nIndex], &m_ptRptDataAnalysis[nIndex]);
	}
}

void CRptDataAnalysisTool::ResetAxis()
{
	m_oAxis.SetMinMaxVal(m_fXMin, m_fYMin, m_fXMax, m_fYMax, 0);
	m_oAxis.ResetAxis();
}

void CRptDataAnalysisTool::SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{

}