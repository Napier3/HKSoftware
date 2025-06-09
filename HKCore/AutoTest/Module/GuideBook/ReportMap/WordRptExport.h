#pragma once

#include "WordRptExportBase.h"
#include "WordReport\WordRptFill.h"
#include "..\..\TaskMngr\TestProject.h"
#include "..\..\TestControl\TestControl.h"

#include "..\..\Module\Office\ExcelReadWrite.h"

//#define WM_EXPORT_REPORT_WORD  (WM_USER + 915)
//#define WM_EXPORT_REPORT_RPC    (WM_USER + 916)

class CWordRptExport : public CWordRptExportBase
{
public:
	CWordRptExport(void);
	virtual ~CWordRptExport(void);

public:
	MSWord::Window m_oWindowDevice;
	MSWord::Window m_oWindowGbrpt;
	MSWord::_Document m_doc;

public:
	virtual void ExportReports(CExBaseList &listTestControls, CExBaseList &listTestProject, CWnd *pMsgWnd);
	virtual void CmbnReports(CExBaseList &listTestControls, CWnd *pMsgWnd);
	
	//导出单个报告
	virtual void ExportReport(CTestControlBase *pTestControl);

	virtual void ExportDetailWord(CTestControlBase *pTestControl);
	virtual BOOL AddReportFileWord(const CString &strGbFile);

	virtual void ExportReport_Values(const CString &strTitle, CValues *pValues);
	virtual void ExportReport_Datasets(const CString &strTitle, CDvmDataset *pDvmDataset);
	virtual void InsertTitle(const CString &strTitle, long nTitleLevel);
	virtual void GotoDocEnd();

	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText);
	void SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color);

protected:
// 	CExcelReadWrite m_oExcelWrite;
// 
 	virtual void ExportDetailExcel(CTestControlBase *pTestControl);
// 	virtual BOOL AddReportFileExcel(const CString &strGbFile);
// 	virtual void ExportDetailExcel_GbItem(CGbItemBase *pGbItem);
// 	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues);
// 	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListParas);
// 	virtual void ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset);
// 	virtual void InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel);
};
