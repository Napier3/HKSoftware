#include "StdAfx.h"
#include "WordRptExport.h"
#include "..\..\TestControl/TCtrlCntrBaseApp.h"
#include "..\GuideBookUpdateTool.h"
#include "ExcelRptExport_Office.h"
#include "..\..\SmartTestRpcEventApi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWordRptExport::CWordRptExport()
{
	
}

CWordRptExport::~CWordRptExport()
{

}

void CWordRptExport::ExportReports(CExBaseList &listTestControls, CExBaseList &listTestProject, CWnd *pMsgWnd)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(4194304);
	oBuffer.AllocBuffer(0);
	ASSERT (g_theTCtrlCntrApp != NULL);
	g_theTCtrlCntrApp->CreateReportApp();
	ASSERT (g_theRptFillApp != NULL);
//	MSWord::_Application oWordApp = g_theTCtrlCntrApp->GetWordApp(m_bShowWordApp);
	MSWord::_Application oWordApp = ((CRptFillWordApp*)g_theRptFillApp)->GetWordApp(m_bShowWordApp);

	POS pos = listTestControls.GetHeadPosition();
	CTestControlBase *pTestControl = NULL;
	CTestProject *pTestProject = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pTestControl = (CTestControlBase *)listTestControls.GetNext(pos);
		pTestProject = (CTestProject *)listTestProject.GetAtIndex(nIndex);

		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportBegin);

		atsrpc_OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportBegin);
		CWordRptExportBase::ExportReport(pTestControl, pTestProject, oBuffer, pMsgWnd); //导出单个报告

		if (m_bCmbnMgrp)
		{//导出汇总报告，如果没有子报告，则将自身拷贝到目标地址；否则导出汇总报告并拷贝到目标地址
			CmbnMgrpReport(pTestControl, pTestProject, pMsgWnd);
		}
		else
		{
			CopyReportFileToDest(pTestControl);
		}

		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportFinish);

		atsrpc_OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportFinish);
		//stt_Return_Ats_Event_ExportFinish(pTestControl);
		nIndex++;
	}

	//对于批量测试，单独导出一批测试的汇总记录
	if (CTCtrlCntrConfig::IsFacBatchTestMode())
	{//将装置属性填写到测试记录中
		CTestTasks *pTestTasks = NULL;
		pTestTasks = CFactoryBatchTestMngr::GetCurrTestTasks();

		CString strTasksWordFile=pTestTasks->ExportWordReport_Summary(oWordApp);

		if (m_bCmbnMgrp && strTasksWordFile.GetLength() > 3)
		{
			CString strDestFile = m_strCmbnDestPath;
			strDestFile += GetPathFileNameFromFilePathName(strTasksWordFile);
			::CopyFile(strTasksWordFile, strDestFile, FALSE);
		}
	}

	if (m_bCloseWordApp)
	{
		g_theRptFillApp->CloseApplication();
	}
}

void CWordRptExport::CmbnReports(CExBaseList &listTestControls, CWnd *pMsgWnd)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(4194304);
	oBuffer.AllocBuffer(0);
	ASSERT (g_theTCtrlCntrApp != NULL);
	g_theTCtrlCntrApp->CreateReportApp();
	ASSERT (g_theRptFillApp != NULL);
	MSWord::_Application oWordApp = ((CRptFillWordApp*)g_theRptFillApp)->GetWordApp(m_bShowWordApp);

	POS pos = listTestControls.GetHeadPosition();
	CTestControlBase *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControlBase *)listTestControls.GetNext(pos);
		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportBegin);
		CmbnMgrpReport(pTestControl, NULL, pMsgWnd);
		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportFinish);
	}

	if (m_bCloseWordApp)
	{
		g_theRptFillApp->CloseApplication();
	}
}

void CWordRptExport::ExportReport(CTestControlBase *pTestControl)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(4194304);
	oBuffer.AllocBuffer(0);
	ASSERT (g_theTCtrlCntrApp != NULL);

	CWordRptExportBase::ExportReport(pTestControl, NULL, oBuffer, NULL);

	if (m_bCloseWordApp)
	{
		g_theRptFillApp->CloseApplication();
	}	
}

void CWordRptExport::ExportDetailWord(CTestControlBase *pTestControl)
{
	AddReportFileWord(pTestControl->GetGbBinaryFile());

	CExBaseList *pListItems = pTestControl->m_pItemContainer->GetGuideBookAllItems();
	POS pos = pListItems->GetHeadPosition();
	CGbItemBase *pItem = NULL;
	
	while (pos != NULL)
	{
		pItem = (CGbItemBase *)pListItems->GetNext(pos);
		ExportDetailWord_GbItem(pItem);
	}

	try
	{
		COleVariant vTrue((long)TRUE), vFalse((long)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		m_doc.Save();
		m_doc.Close(vFalse,covOptional,covOptional);
	}
	catch (...)
	{
		
	}
}

BOOL CWordRptExport::AddReportFileWord(const CString &strGbFile)
{
	ASSERT (g_theRptFillApp != NULL);

	BOOL bTrue = TRUE;
	CString strWordFile;

	//如果打开了报告文档，则保存并关闭文档
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));

	COleVariant TmplFile(strWordFile);

	CRptFillWordApp* pRptFillWordApp = (CRptFillWordApp*)g_theRptFillApp;
	MSWord::Documents docs = pRptFillWordApp->m_WordApp.GetDocuments();

	try
	{
		m_doc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	strWordFile = strGbFile;
	strWordFile = GetPathFromFilePathName(strWordFile);
	strWordFile += ParseFileName(strGbFile);
	strWordFile += _T("_原始记录");
	strWordFile += _T(".doc");

	try
	{
		m_doc.SaveAs(COleVariant(strWordFile), covOptional, covOptional, covOptional,
			covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	}
	catch (...)
	{	
	}

	return bTrue;
}

void CWordRptExport::ExportReport_Values(const CString &strTitle, CValues *pValues)
{
	if (pValues == NULL)
	{
		return;
	}

	if (pValues->GetCount() == 0)
	{
		return;
	}


	InsertTitle(strTitle, 0);

	long nVal = MSWord::wdWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = MSWord::wdAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 
	long nRows = pValues->GetCount() + 1;

	MSWord::Selection oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	MSWord::Tables oTables = m_doc.GetTables();
	MSWord::Table oTable   = oTables.Add(oRange, nRows, 3, &vTableBehavior, &vAutoFitBehavior);
	MSWord::Columns oCols = oTable.GetColumns();
	MSWord::Column  oCol  = NULL;
	MSWord::Row  oRow  = NULL;
	MSWord::Rows  oRows  = NULL;
	MSWord::Cell  oCell  = NULL;
	MSWord::Cells  oCells  = NULL;

	try
	{
		oRows = oTable.GetRows();
		oRow = oRows.Item(1);
		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.Select();
		oSelection.TypeText(_T("编号"));

		oCell = oCells.Item(2);
		oCell.Select();
		oSelection.TypeText(_T("ID"));

		oCell = oCells.Item(3);
		oCell.Select();
		oSelection.TypeText(_T("数据值"));
	}
	catch (...)
	{
		
	}

	long nRowIndex = 2;
	CValue *pValue = NULL;
	POS pos = pValues->GetHeadPosition();
	CString strIndex;

	try
	{
		oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
		oRows = oTable.GetRows();

		while (pos != NULL)
		{
			pValue = (CValue*)pValues->GetNext(pos);
			oRow = oRows.Item(nRowIndex);
			oCells = oRow.GetCells();
			oCell = oCells.Item(1);
			oCell.Select();
			strIndex.Format(_T("%d"), nRowIndex-1);
			oSelection.TypeText(strIndex);

			oCell = oCells.Item(2);
			oCell.Select();
			oSelection.TypeText(pValue->m_strID);

			oCell = oCells.Item(3);
			oCell.Select();
			oSelection.TypeText(pValue->m_strValue);

			nRowIndex++;
		}
	}
	catch (...)
	{
		
	}

	GotoDocEnd();
}

void CWordRptExport::ExportReport_Datasets(const CString &strTitle, CDvmDataset *pDvmDataset)
{
	if (pDvmDataset == NULL)
	{
		return;
	}

	if (pDvmDataset->GetCount() == 0)
	{
		return;
	}

	InsertTitle(strTitle, 0);

	long nVal = MSWord::wdWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = MSWord::wdAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 
	long nRows = pDvmDataset->GetCount() + 1;

	MSWord::Selection oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	MSWord::Tables oTables = m_doc.GetTables();
	MSWord::Table oTable   = oTables.Add(oRange, nRows, 4, &vTableBehavior, &vAutoFitBehavior);
	MSWord::Columns oCols = oTable.GetColumns();
	MSWord::Column  oCol  = NULL;
	MSWord::Row  oRow  = NULL;
	MSWord::Rows  oRows  = NULL;
	MSWord::Cell  oCell  = NULL;
	MSWord::Cells  oCells  = NULL;

	try
	{
		oRows = oTable.GetRows();
		oRow = oRows.Item(1);
		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.Select();
		oSelection.TypeText(_T("编号"));

		oCell = oCells.Item(2);
		oCell.Select();
		oSelection.TypeText(_T("名称"));

		oCell = oCells.Item(3);
		oCell.Select();
		oSelection.TypeText(_T("ID"));

		oCell = oCells.Item(4);
		oCell.Select();
		oSelection.TypeText(_T("数据值"));
	}
	catch (...)
	{

	}

	long nRowIndex = 2;
	CDvmData *pData = NULL;
	POS pos = pDvmDataset->GetHeadPosition();
	CString strIndex;

	try
	{
		oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
		oRows = oTable.GetRows();

		while (pos != NULL)
		{
			pData = (CDvmData*)pDvmDataset->GetNext(pos);
			oRow = oRows.Item(nRowIndex);
			oCells = oRow.GetCells();
			oCell = oCells.Item(1);
			oCell.Select();
			strIndex.Format(_T("%d"), nRowIndex-1);
			oSelection.TypeText(strIndex);

			oCell = oCells.Item(2);
			oCell.Select();
			oSelection.TypeText(pData->m_strName);

			oCell = oCells.Item(3);
			oCell.Select();
			oSelection.TypeText(pData->m_strID);

			oCell = oCells.Item(4);
			oCell.Select();
			oSelection.TypeText(pData->m_strValue);
		
			nRowIndex++;
		}
	}
	catch (...)
	{

	}

	GotoDocEnd();
}

void CWordRptExport::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	MSWord::Selection wordSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();

	wordSelection.EndKey(&vUnit, &vOpt);
	wordSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wordSelection.TypeText(strTitle);
		MSWord::Styles oStyles = m_doc.GetStyles();
		CString strStyle;
		strStyle.Format(g_sLangTxt_Title/*_T("标题 %d")*/, nTitleLevel);
		COleVariant vStyleID = strStyle;
		wordSelection.SetStyle(vStyleID);
	}
	else
	{
		MSWord::_Font font = wordSelection.GetFont();
		float fSize = font.GetSize();
		font.SetBold(TRUE);
		font.SetSize(16);
		wordSelection.TypeText(strTitle);
		font.SetSize(fSize);
		font.SetBold(FALSE);
	}

	wordSelection.TypeParagraph();
}

void CWordRptExport::GotoDocEnd()
{
	COleVariant vUnit((long)MSWord::wdStory);
	COleVariant vCount((long)0);

	//定位到文档末尾
	MSWord::Selection wordSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
	MSWord::_ParagraphFormat oFormat = wordSelection.GetParagraphFormat();
	wordSelection.EndKey(&vUnit, &vCount);
}

void CWordRptExport::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(RGB(0, 0, 0));
	oSelection.TypeText(strText);
}

void CWordRptExport::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = ((CRptFillWordApp*)g_theRptFillApp)->m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(color);
	oSelection.TypeText(strText);
	oFont.SetColor(RGB(0, 0, 0));
}

//////////////////////////////////////////////////////////////////////////
//
void CWordRptExport::ExportDetailExcel(CTestControlBase *pTestControl)
{
	CExcelRptExport_Office oExcelExport;
	oExcelExport.m_bShowWordApp = m_bShowWordApp;
	oExcelExport.ExportDetailExcel(pTestControl);
// 	AddReportFileExcel(pTestControl->GetGbBinaryFile());
// 
// 	CExBaseList *pListItems = pTestControl->m_pItemContainer->GetGuideBookAllItems();
// 	POS pos = pListItems->GetHeadPosition();
// 	CGbItemBase *pItem = NULL;
// 
// 	try
// 	{
// 		m_oExcelWrite.LoadSheet(1, TRUE);
// 	}
// 	catch (...)
// 	{
// 
// 	}
// 
// 	m_nExcelRowIndex = 1;
// 
// 	try
// 	{
// 		while (pos != NULL)
// 		{
// 			pItem = (CGbItemBase *)pListItems->GetNext(pos);
// 			ExportDetailExcel_GbItem(pItem);
// 		}
// 	}
// 	catch (...)
// 	{
// 	}
// 
// 	try
// 	{
// 		m_oExcelWrite.SaveXSLFile();
// 	}
// 	catch (...)
// 	{
// 	}
// 
// 	try
// 	{
// 		m_oExcelWrite.CloseExcelFile(FALSE);
// 	}
// 	catch (...)
// 	{
// 	}
}
// 
// BOOL CWordRptExport::AddReportFileExcel(const CString &strGbFile)
// {
// 	ASSERT (g_theRptFillApp != NULL);
// 
// 	m_oExcelWrite.InitExcel();
// 	BOOL bTrue = TRUE;
// 	CString strExcelFile;
// 
// 	m_oExcelWrite.ShowInExcel(m_bShowWordApp);
// 	m_oExcelWrite.OpenExcelFile(_T(""));
// 
// 	strExcelFile = strGbFile;
// 	strExcelFile = GetPathFromFilePathName(strExcelFile);
// 	strExcelFile += ParseFileName(strGbFile);
// 	strExcelFile += _T(".xlsx");
// 
// 	try
// 	{
// 		m_oExcelWrite.SaveasXSLFile(strExcelFile);
// 	}
// 	catch (...)
// 	{	
// 	}
// 
// 	return bTrue;
// }
// 
// void CWordRptExport::ExportDetailExcel_GbItem(CGbItemBase *pGbItem)
// {
// 	UINT nClassID = pGbItem->GetClassID();
// 
// 	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_JOBGUIDE || nClassID == GBCLASSID_ITEMS)
// 	{
// 		return;
// 	}
// 
// 	CReports *pReports = pGbItem->GetReports();
// 
// 	if (pReports->GetCount() == 0)
// 	{
// 		return;
// 	}
// 
// 	CString strTitle = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
// 	InsertTitle_Excel(strTitle, 1, 0);
// 
// 	CReport *pReort = NULL;
// 	POS pos = pReports->GetHeadPosition();
// 	long nIndex = 1;
// 	CExBaseList *pListParas = NULL;
// 
// 	if (nClassID == GBCLASSID_MACROTEST)
// 	{
// 		CMacroTest *pMacroTest = (CMacroTest*)pGbItem;
// 		pListParas = pMacroTest->GetFaultParaDatas();
// 	}
// 
// 	if (pReports->GetCount() == 1)
// 	{
// 		pReort = (CReport *)pReports->GetNext(pos);
// 
// 		ExportReport_Values_Excel(_T(""), pReort->m_pValues, pListParas);
// 		ExportReport_Datasets_Excel(_T("报文数据"), pReort->m_pRptDvmDataset);
// 	}
// 	else
// 	{
// 		while (pos != NULL)
// 		{
// 			pReort = (CReport *)pReports->GetNext(pos);
// 			strTitle.Format(_T("第%d次测试报告"), nIndex);
// 			InsertTitle_Excel(strTitle, 2, 0);
// 			ExportReport_Values_Excel(_T(""), pReort->m_pValues, pListParas);
// 			ExportReport_Datasets_Excel(_T("报文数据"), pReort->m_pRptDvmDataset);
// 			nIndex++;
// 		}
// 	}
// }
// 
// void CWordRptExport::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues)
// {
// 	long nRowIndex = 1;
// 	CValue *pValue = NULL;
// 	POS pos = pValues->GetHeadPosition();
// 	CString strIndex;
// 
// 	try
// 	{
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("数据值"));
// 	}
// 	catch (...)
// 	{
// 		
// 	}
// 
// 	m_nExcelRowIndex++;
// 
// 	try
// 	{
// 		while (pos != NULL)
// 		{
// 			pValue = (CValue*)pValues->GetNext(pos);
// 			strIndex.Format(_T("%d"), nRowIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pValue->m_strID);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pValue->m_strValue);
// 			m_nExcelRowIndex++;
// 			nRowIndex++;
// 		}
// 	}
// 	catch (...)
// 	{
// 
// 	}
// }
// 
// void CWordRptExport::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListPara)
// {
// 	if (pListPara == NULL)
// 	{
// 		return ExportReport_Values_Excel(strTitle, pValues);
// 	}
// 
// 	long nRowIndex = 1;
// 	CValue *pValue = NULL;
// 	POS pos = pValues->GetHeadPosition();
// 	CString strIndex;
// 
// 	try
// 	{
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("数据值"));
// 	}
// 	catch (...)
// 	{
// 
// 	}
// 
// 	m_nExcelRowIndex++;
// 
// 	try
// 	{
// 		while (pos != NULL)
// 		{
// 			pValue = (CValue*)pValues->GetNext(pos);
// 
// 			if (pListPara->FindByID(pValue->m_strID) == NULL)
// 			{
// 				continue;
// 			}
// 
// 			strIndex.Format(_T("%d"), nRowIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pValue->m_strID);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pValue->m_strValue);
// 			m_nExcelRowIndex++;
// 			nRowIndex++;
// 		}
// 	}
// 	catch (...)
// 	{
// 
// 	}
// }
// 
// void CWordRptExport::ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset)
// {
// 	if (pDvmDataset->GetCount() == 0)
// 	{
// 		return;
// 	}
// 
// 	long nRowIndex = 1;
// 	CDvmData *pData = NULL;
// 	POS pos = pDvmDataset->GetHeadPosition();
// 	CString strIndex;
// 	InsertTitle_Excel(strTitle, 2, 0);
// 
// 	try
// 	{
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, _T("编号"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, _T("名称"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, _T("ID"));
// 		m_oExcelWrite.SetCellString(m_nExcelRowIndex, 6, _T("数据值"));
// 	}
// 	catch (...)	{	}
// 
// 	m_nExcelRowIndex++;
// 
// 	try
// 	{
// 		while (pos != NULL)
// 		{
// 			pData = (CDvmData*)pDvmDataset->GetNext(pos);
// 			strIndex.Format(_T("%d"), nRowIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 3, strIndex);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 4, pData->m_strName);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 5, pData->m_strID);
// 			m_oExcelWrite.SetCellString(m_nExcelRowIndex, 6, pData->m_strValue);
// 
// 			nRowIndex++;
// 			m_nExcelRowIndex++;
// 		}
// 	}
// 	catch (...)	{	}
// }
// 
// void CWordRptExport::InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel)
// {
// 	m_oExcelWrite.SetCellString(m_nExcelRowIndex, nCol, strTitle);
// 	m_nExcelRowIndex++;
// }
