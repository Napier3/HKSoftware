#include "StdAfx.h"
#include "WPSRptExport.h"
#include "..\..\TestControl/TCtrlCntrBaseApp.h"
#include "..\GuideBookUpdateTool.h"
#include "ExcelRptExport_Office.h"
#include "..\..\SmartTestRpcEventApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWPSRptExport::CWPSRptExport()
{

}

CWPSRptExport::~CWPSRptExport()
{

}

void CWPSRptExport::ExportReports(CExBaseList &listTestControls, CExBaseList &listTestProject, CWnd *pMsgWnd)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(4194304);
	oBuffer.AllocBuffer(0);
	ASSERT (g_theTCtrlCntrApp != NULL);
	g_theTCtrlCntrApp->CreateReportApp();
	ASSERT (g_theRptFillApp != NULL);
//	MSWord::_Application oWordApp = g_theTCtrlCntrApp->GetWordApp(m_bShowWordApp);
	WPS::_Application oWPSApp = ((CRptFillWPSApp*)g_theRptFillApp)->GetWPSApp(m_bShowWordApp);

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

		CString strTasksWPSFile=pTestTasks->ExportWordReport_Summary(oWPSApp);

		if (m_bCmbnMgrp && strTasksWPSFile.GetLength() > 3)
		{
			CString strDestFile = m_strCmbnDestPath;
			strDestFile += GetPathFileNameFromFilePathName(strTasksWPSFile);
			::CopyFile(strTasksWPSFile, strDestFile, FALSE);
		}
	}

	if (m_bCloseWordApp)
	{
		g_theRptFillApp->CloseApplication();
	}
}

void CWPSRptExport::CmbnReports(CExBaseList &listTestControls, CWnd *pMsgWnd)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetBufferLength(4194304);
	oBuffer.AllocBuffer(0);
	ASSERT (g_theTCtrlCntrApp != NULL);
	g_theTCtrlCntrApp->CreateReportApp();
	ASSERT (g_theRptFillApp != NULL);
//	MSWord::_Application oWordApp = g_theTCtrlCntrApp->GetWordApp(m_bShowWordApp);
	WPS::_Application oWPSApp = ((CRptFillWPSApp*)g_theRptFillApp)->GetWPSApp(m_bShowWordApp);

	POS pos = listTestControls.GetHeadPosition();
	CTestControlBase *pTestControl = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControlBase *)listTestControls.GetNext(pos);
		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportBegin);
		CmbnMgrpReport(pTestControl, NULL, pMsgWnd);
		pTestControl->m_oTCtrlMsgRcv.OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportFinish);
		atsrpc_OnExportRptEvent(pTestControl, SYS_STATE_XEVENT_EVENTID_ExportFinish);
	}

	if (m_bCloseWordApp)
	{
		g_theRptFillApp->CloseApplication();
	}
}

void CWPSRptExport::ExportReport(CTestControlBase *pTestControl)
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

void CWPSRptExport::ExportDetailWord(CTestControlBase *pTestControl)
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

BOOL CWPSRptExport::AddReportFileWord(const CString &strGbFile)
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

	CRptFillWPSApp* pRptFillWPSApp = (CRptFillWPSApp*)g_theRptFillApp;
	WPS::Documents docs = pRptFillWPSApp->m_WPSApp.get_Documents();

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
			covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	}
	catch (...)
	{	
	}

	return bTrue;
}

void CWPSRptExport::ExportReport_Values(const CString &strTitle, CValues *pValues)
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

	long nVal = WPS::wpsWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = WPS::wpsAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 
	long nRows = pValues->GetCount() + 1;

	WPS::Selection oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	WPS::Range oRange = oSelection.get_Range();
	WPS::Tables oTables = m_doc.get_Tables();
	WPS::Table oTable   = oTables.Add(oRange, nRows, 3, &vTableBehavior, &vAutoFitBehavior);
	WPS::Columns oCols = oTable.get_Columns();
	WPS::Column  oCol  = NULL;
	WPS::Row  oRow  = NULL;
	WPS::Rows  oRows  = NULL;
	WPS::Cell  oCell  = NULL;
	WPS::Cells  oCells  = NULL;

	try
	{
		oRows = oTable.get_Rows();
		oRow = oRows.Item(1);
		oCells = oRow.get_Cells();
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
		oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
		oRows = oTable.get_Rows();

		while (pos != NULL)
		{
			pValue = (CValue*)pValues->GetNext(pos);
			oRow = oRows.Item(nRowIndex);
			oCells = oRow.get_Cells();
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

void CWPSRptExport::ExportReport_Datasets(const CString &strTitle, CDvmDataset *pDvmDataset)
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

	long nVal = WPS::wpsWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = WPS::wpsAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 
	long nRows = pDvmDataset->GetCount() + 1;

	WPS::Selection oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	WPS::Range oRange = oSelection.get_Range();
	WPS::Tables oTables = m_doc.get_Tables();
	WPS::Table oTable   = oTables.Add(oRange, nRows, 4, &vTableBehavior, &vAutoFitBehavior);
	WPS::Columns oCols = oTable.get_Columns();
	WPS::Column  oCol  = NULL;
	WPS::Row  oRow  = NULL;
	WPS::Rows  oRows  = NULL;
	WPS::Cell  oCell  = NULL;
	WPS::Cells  oCells  = NULL;

	try
	{
		oRows = oTable.get_Rows();
		oRow = oRows.Item(1);
		oCells = oRow.get_Cells();
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
		oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
		oRows = oTable.get_Rows();

		while (pos != NULL)
		{
			pData = (CDvmData*)pDvmDataset->GetNext(pos);
			oRow = oRows.Item(nRowIndex);
			oCells = oRow.get_Cells();
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

void CWPSRptExport::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)WPS::wpsStory);
	WPS::Selection wpsSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();

	wpsSelection.EndKey(&vUnit, &vOpt);
	wpsSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wpsSelection.TypeText(strTitle);
		WPS::Styles oStyles = m_doc.get_Styles();
		CString strStyle;
		strStyle.Format(g_sLangTxt_Title/*_T("标题 %d")*/, nTitleLevel);
		COleVariant vStyleID = strStyle;
		wpsSelection.put_Style(vStyleID);
	}
	else
	{
		WPS::_Font font = wpsSelection.get_Font();
		float fSize = font.get_Size();
		font.put_Bold(TRUE);
		font.put_Size(16);
		wpsSelection.TypeText(strTitle);
		font.put_Size(fSize);
		font.put_Bold(FALSE);
	}

	wpsSelection.TypeParagraph();
}

void CWPSRptExport::GotoDocEnd()
{
	COleVariant vUnit((long)WPS::wpsStory);
	COleVariant vCount((long)0);

	//定位到文档末尾
	WPS::Selection wpsSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	wpsSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	WPS::_ParagraphFormat oFormat = wpsSelection.get_ParagraphFormat();
	wpsSelection.EndKey(&vUnit, &vCount);
}

void CWPSRptExport::SetRowCellText(WPS::Row &oRow, long nIndex, const CString &strText)
{
	WPS::Cells oCells = oRow.get_Cells();
	WPS::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	WPS::Selection oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	WPS::_Font oFont = oSelection.get_Font();
	oFont.put_Color(RGB(0, 0, 0));
	oSelection.TypeText(strText);
}

void CWPSRptExport::SetRowCellText(WPS::Row &oRow, long nIndex, const CString &strText, COLORREF color)
{
	WPS::Cells oCells = oRow.get_Cells();
	WPS::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	WPS::Selection oSelection = ((CRptFillWPSApp*)g_theRptFillApp)->m_WPSApp.get_Selection();
	WPS::_Font oFont = oSelection.get_Font();
	oFont.put_Color(color);
	oSelection.TypeText(strText);
	oFont.put_Color(RGB(0, 0, 0));
}

//////////////////////////////////////////////////////////////////////////

void CWPSRptExport::ExportDetailExcel(CTestControlBase *pTestControl)
{
	CExcelRptExport_Office oExcelExport;
	oExcelExport.m_bShowWordApp = m_bShowWordApp;
	oExcelExport.ExportDetailExcel(pTestControl);
}

