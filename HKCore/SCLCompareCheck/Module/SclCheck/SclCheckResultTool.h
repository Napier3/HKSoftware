#pragma once
#include "..\..\..\Module\Office\msword9.h"
#include "ResultsRec.h"

class CSclCheckResultTool
{
public:
	CSclCheckResultTool(void);
	~CSclCheckResultTool(void);

public:
	void ExportReportFile(const CString &strReportTitle ,CResultsRec *pScheckResults = NULL,CResultsRec *pDLT860Results = NULL,CResultsRec *pProjAppResults = NULL ,CResultsRec *pVirLoopResults = NULL);
	void ExportReportOfWord(const CString &strReportTitle ,CResultsRec *pScheckResults = NULL,CResultsRec *pDLT860Results = NULL,CResultsRec *pProjAppResults = NULL ,CResultsRec *pVirLoopResults = NULL);
	void ExportReportOfTxt(const CString &strReportTitle ,CResultsRec *pScheckResults = NULL,CResultsRec *pDLT860Results = NULL,CResultsRec *pProjAppResults = NULL ,CResultsRec *pVirLoopResults = NULL);
	void ExportResultsTxt(CString &strFileText, CResultsRec *pResults);
	void SetRptFile(const CString &strRptFile){m_strRptFile = strRptFile;}
	void ExportReport_SetFont(MSWord::Selection oSelection, LPCTSTR lpszFontName,float fFontSize,int nBold);

protected:
	MSWord::_Application m_WordApp;
	MSWord::_Document		m_doc;
	float    m_fWidthCol1, m_fWidthCol2, m_fWidthCol3, m_fWidthCol4, m_fWidthCol5, m_fWidthCol6, m_fWidthCol7, m_fWidthCol8;
	CString m_strRptFile;

protected:
	BOOL CreateWordApplication(BOOL bVisible);
	BOOL NewWordReportFile();
	void InsertTitle(const CString &strTitle, long nTitleLevel);
	void ExportReport_Results(const CString &strSecondTitle, CResultsRec *pResults);
	void ExportReport_Result(MSWord::Table &oTable, CResultRec *pResult, long &nRowIndex);
	void InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit=TRUE);
	void MergeRow(MSWord::Row &oRow);
	BOOL ExitWordApplation();

	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color);
};
