#include "StdAfx.h"
#include "ExcelRptExport_Office.h"
#include "..\..\TestControl/TCtrlCntrBaseApp.h"
#include "..\GuideBookUpdateTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CExcelRptExport_Office::CExcelRptExport_Office()
{
	m_nExcelRowIndex = 1;
	m_bShowWordApp = FALSE;
}

CExcelRptExport_Office::~CExcelRptExport_Office()
{
	try
	{
		m_oExcelWrite.CloseExcelFile(TRUE);
	}
	catch (...)
	{

	}
}

void CExcelRptExport_Office::ExportDetailExcel(CTestControlBase *pTestControl)
{
	AddReportFileExcel(pTestControl->GetGbBinaryFile());

	CExBaseList *pListItems = pTestControl->m_pItemContainer->GetGuideBookAllItems();
	POS pos = pListItems->GetHeadPosition();
	CGbItemBase *pItem = NULL;

	try
	{
		m_oExcelWrite.LoadSheet(1, TRUE);
	}
	catch (...)
	{

	}

	m_nExcelRowIndex = 1;
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(1024 * 1024);

	try
	{
		long nIndex = 0;
		while (pos != NULL)
		{
			pItem = (CGbItemBase *)pListItems->GetNext(pos);

			if (nIndex == 9)
			{
				nIndex = 9;
			}

			ExportDetailExcel_GbItem(pItem, oBuffer);
			nIndex++;
		}
	}
	catch (...)
	{
	}

	try
	{
		m_oExcelWrite.SaveXSLFile();
	}
	catch (...)
	{
	}

	try
	{
		m_oExcelWrite.CloseExcelFile(FALSE);
	}
	catch (...)
	{
	}
}

BOOL CExcelRptExport_Office::AddReportFileExcel(const CString &strGbFile)
{
	ASSERT (g_theRptFillApp != NULL);

	m_oExcelWrite.InitExcel();
	BOOL bTrue = TRUE;
	CString strExcelFile;

	m_oExcelWrite.ShowInExcel(m_bShowWordApp);
	m_oExcelWrite.OpenExcelFile(_T(""));

	strExcelFile = strGbFile;
	strExcelFile = GetPathFromFilePathName(strExcelFile);
	strExcelFile += ParseFileName(strGbFile);
	strExcelFile += _T(".xlsx");

	try
	{
		m_oExcelWrite.SaveasXSLFile(strExcelFile);
	}
	catch (...)
	{	
	}

	return bTrue;
}

void CExcelRptExport_Office::ExportDetailExcel_GbItem(CGbItemBase *pGbItem, CBinarySerialBuffer &oBuffer)
{
	UINT nClassID = pGbItem->GetClassID();

	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_JOBGUIDE || nClassID == GBCLASSID_ITEMS)
	{
		return;
	}


	pGbItem->OpenBinaryTempFileReport(oBuffer);
	CReports *pReports = pGbItem->GetReports();

	if (pReports->GetCount() == 0)
	{
		return;
	}

	CString strTitle = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
	InsertTitle_Excel(strTitle, 1, 0);

	CReport *pReort = NULL;
	POS pos = pReports->GetHeadPosition();
	long nIndex = 1;
	CExBaseList *pListParas = NULL;

	if (nClassID == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)pGbItem;
		pListParas = pMacroTest->GetFaultParaDatas();
	}

	if (pReports->GetCount() == 1)
	{
		pReort = (CReport *)pReports->GetNext(pos);

		ExportReport_Values_Excel(_T(""), pReort->m_pValues, pListParas);
		ExportReport_Datasets_Excel(_T("报文数据"), pReort->m_pRptDvmDataset);
	}
	else
	{
		while (pos != NULL)
		{
			pReort = (CReport *)pReports->GetNext(pos);
			strTitle.Format(_T("第%d次测试报告"), nIndex);
			InsertTitle_Excel(strTitle, 2, 0);
			ExportReport_Values_Excel(_T(""), pReort->m_pValues, pListParas);
			ExportReport_Datasets_Excel(_T("报文数据"), pReort->m_pRptDvmDataset);
			nIndex++;
		}
	}
}

void CExcelRptExport_Office::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues)
{
	long nRowIndex = 1;
	CValue *pValue = NULL;
	POS pos = pValues->GetHeadPosition();
	CString strIndex;

	try
	{
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("数据值"));
	}
	catch (...)
	{
		
	}

	m_nExcelRowIndex++;

	try
	{
		while (pos != NULL)
		{
			pValue = (CValue*)pValues->GetNext(pos);
			strIndex.Format(_T("%d"), nRowIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pValue->m_strID);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pValue->m_strValue);
			m_nExcelRowIndex++;
			nRowIndex++;
		}
	}
	catch (...)
	{

	}
}

void CExcelRptExport_Office::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListPara)
{
	if (pListPara == NULL)
	{
		return ExportReport_Values_Excel(strTitle, pValues);
	}

	long nRowIndex = 1;
	CValue *pValue = NULL;
	POS pos = pValues->GetHeadPosition();
	CString strIndex;

	try
	{
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("数据值"));
	}
	catch (...)
	{

	}

	m_nExcelRowIndex++;

	try
	{
		while (pos != NULL)
		{
			pValue = (CValue*)pValues->GetNext(pos);

			if (pListPara->FindByID(pValue->m_strID) == NULL)
			{
				continue;
			}

			strIndex.Format(_T("%d"), nRowIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pValue->m_strID);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pValue->m_strValue);
			m_nExcelRowIndex++;
			nRowIndex++;
		}
	}
	catch (...)
	{

	}
}

void CExcelRptExport_Office::ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset)
{
	if (pDvmDataset->GetCount() == 0)
	{
		return;
	}

	long nRowIndex = 1;
	CDvmData *pData = NULL;
	POS pos = pDvmDataset->GetHeadPosition();
	CString strIndex;
	InsertTitle_Excel(strTitle, 2, 0);

	try
	{
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("ID"));
		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 6, _T("数据值"));
	}
	catch (...)	{	}

	m_nExcelRowIndex++;

	try
	{
		while (pos != NULL)
		{
			pData = (CDvmData*)pDvmDataset->GetNext(pos);
			strIndex.Format(_T("%d"), nRowIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pData->m_strName);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pData->m_strID);
			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 6, pData->m_strValue);

			nRowIndex++;
			m_nExcelRowIndex++;
		}
	}
	catch (...)	{	}
}

void CExcelRptExport_Office::InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel)
{
	m_oExcelWrite.SetCellString(m_nExcelRowIndex, nCol, strTitle);
	m_nExcelRowIndex++;
}
