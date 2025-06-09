#pragma once

#include "..\..\TaskMngr\TestProject.h"
#include "..\..\TestControl/TestControl.h"

#include "..\..\Module\Office\ExcelReadWrite.h"

//#define WM_EXPORT_REPORT_WORD  (WM_USER + 915)
//#define WM_EXPORT_REPORT_RPC    (WM_USER + 916)

class CExcelRptExport_Office
{
public:
	CExcelRptExport_Office(void);
	virtual ~CExcelRptExport_Office(void);

	virtual void ExportDetailExcel(CTestControlBase *pTestControl);
	BOOL m_bShowWordApp;

protected:
	CExcelReadWrite m_oExcelWrite;
	long m_nExcelRowIndex;

	virtual BOOL AddReportFileExcel(const CString &strGbFile);
	virtual void ExportDetailExcel_GbItem(CGbItemBase *pGbItem, CBinarySerialBuffer &oBuffer);
	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues);
	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListParas);
	virtual void ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset);
	virtual void InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel);
};
