#pragma once

#include "WordRptExportBase.h"
#include "WPSReport\WPSRptFill.h"
#include "..\..\TaskMngr\TestProject.h"
#include "..\..\TestControl\TestControl.h"

//#include "..\..\Module\Office\ExcelReadWrite.h"

//#define WM_EXPORT_REPORT_WORD	  (WM_USER + 915)
//#define WM_EXPORT_REPORT_RPC    (WM_USER + 916)

class CWPSRptExport : public CWordRptExportBase 
{
public:
	CWPSRptExport(void);
	virtual ~CWPSRptExport(void);

public:
	WPS::Window m_oWindowDevice;
	WPS::Window m_oWindowGbrpt;
	WPS::_Document m_doc;

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

	void SetRowCellText(WPS::Row &oRow, long nIndex, const CString &strText);
	void SetRowCellText(WPS::Row &oRow, long nIndex, const CString &strText, COLORREF color);

protected:
	virtual void ExportDetailExcel(CTestControlBase *pTestControl);

};
