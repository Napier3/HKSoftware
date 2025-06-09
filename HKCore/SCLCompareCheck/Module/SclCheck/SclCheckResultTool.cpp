#include "StdAfx.h"
#include "SclCheckResultTool.h"
#include "..\..\..\Module\API\FileApi.h"

#include <string>

CSclCheckResultTool::CSclCheckResultTool(void)
{
	m_WordApp = NULL;
	m_doc     = NULL;
}

CSclCheckResultTool::~CSclCheckResultTool(void)
{
	ExitWordApplation();
}

#include "DlgExportWRep.h"
void CSclCheckResultTool::ExportReportFile(const CString &strReportTitle ,CResultsRec *pScheckResults,CResultsRec *pDLT860Results,CResultsRec *pProjAppResults ,CResultsRec *pVirLoopResults)
{
	CDlgExportWRep oDlgRpt;

	if (oDlgRpt.DoModal() != IDOK)
	{
		return;
	}

	if ((!oDlgRpt.m_bCheckSchema)&&(!oDlgRpt.m_bCheckDataTypeTmp)&&(!oDlgRpt.m_bCheckAppModel)&&(!oDlgRpt.m_bCheckVirCircuit))
	{
		return;
	}

	if (pScheckResults != NULL)
		pScheckResults->m_bExportRpt = oDlgRpt.m_bCheckSchema;

	if (pDLT860Results != NULL)
		pDLT860Results->m_bExportRpt = oDlgRpt.m_bCheckDataTypeTmp;

	if (pProjAppResults != NULL)
		pProjAppResults->m_bExportRpt = oDlgRpt.m_bCheckAppModel;

	if (pVirLoopResults != NULL)
		pVirLoopResults->m_bExportRpt = oDlgRpt.m_bCheckVirCircuit;

	if (!PopupSaveAsFileDialog(NULL, m_strRptFile, _T("word报告格式(*.doc)|*.doc|文本文档报告(*.txt)|*.txt||"),_T("")))
		return;

	CString strPostFix;
	strPostFix = ParseFilePostfix(m_strRptFile);

	if (strPostFix == _T("doc"))
	{
		ExportReportOfWord(strReportTitle ,pScheckResults ,pDLT860Results ,pProjAppResults ,pVirLoopResults);
	} 
	else if (strPostFix == _T("txt"))
	{
		ExportReportOfTxt(strReportTitle ,pScheckResults ,pDLT860Results ,pProjAppResults ,pVirLoopResults);
	}
}

void CSclCheckResultTool::ExportReportOfWord(const CString &strReportTitle ,CResultsRec *pScheckResults,CResultsRec *pDLT860Results,CResultsRec *pProjAppResults ,CResultsRec *pVirLoopResults)
{
	if(!CreateWordApplication(TRUE))
	{
		return;
	}

	if (!NewWordReportFile())
	{
		return;
	}

	InsertTitle(strReportTitle, 1);
	CString strSecondTile;

	if (pScheckResults != NULL)
	{
		if (pScheckResults->m_bExportRpt)
		{
			strSecondTile.Format(_T("Schema语法检查结果"));
			ExportReport_Results(strSecondTile ,pScheckResults);
		}
	}

	if (pDLT860Results != NULL)
	{
		if (pDLT860Results->m_bExportRpt)
		{
			strSecondTile.Format(_T("DL/T860数据类型模板库检查结果"));
			ExportReport_Results(strSecondTile ,pDLT860Results);
		}
	}

	if (pProjAppResults != NULL)
	{
		if (pProjAppResults->m_bExportRpt)
		{
			strSecondTile.Format(_T("工程应用模型规范性检查结果"));
			ExportReport_Results(strSecondTile ,pProjAppResults);
		}
	}

	if (pVirLoopResults != NULL)
	{
		if (pVirLoopResults->m_bExportRpt)
		{
			strSecondTile.Format(_T("虚回路规范性检查结果"));
			ExportReport_Results(strSecondTile ,pVirLoopResults);
		}
	}

	//Doc文件保存
	COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  	

	m_doc.SaveAs(COleVariant(m_strRptFile), vOpt, vOpt, vOpt,
		vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);

	MessageBox( NULL,_T("导出报告完成") ,_T("报告导出"),MB_OK);
}

void CSclCheckResultTool::ExportReportOfTxt(const CString &strReportTitle ,CResultsRec *pScheckResults,CResultsRec *pDLT860Results,CResultsRec *pProjAppResults ,CResultsRec *pVirLoopResults)
{
	CString strFileText,strTmp;
	long nNum = 1;
	strFileText.Format(_T("%s \n") ,strReportTitle);

	CStdioFile filReport;

	if (filReport.Open(m_strRptFile,CFile::modeCreate|CFile::modeWrite))
	{
		if (pScheckResults != NULL)
		{
			if (pScheckResults->m_bExportRpt)
			{
				strTmp.Format(_T("%d Schema语法检查结果 \n") ,nNum);
				strFileText += strTmp;
				ExportResultsTxt(strFileText ,pScheckResults);
				nNum++;
			}
		}

		if (pDLT860Results != NULL)
		{
			if (pDLT860Results->m_bExportRpt)
			{
				strTmp.Format(_T("%d DL/T860数据类型模板库检查结果 \n") ,nNum);
				strFileText += strTmp;
				ExportResultsTxt(strFileText ,pDLT860Results);
				nNum++;
			}
		}

		if (pProjAppResults != NULL)
		{
			if (pProjAppResults->m_bExportRpt)
			{
				strTmp.Format(_T("%d 工程应用模型规范性检查结果 \n") ,nNum);
				strFileText += strTmp;
				ExportResultsTxt(strFileText ,pProjAppResults);
				nNum++;
			}
		}

		if (pVirLoopResults != NULL)
		{
			if (pVirLoopResults->m_bExportRpt)
			{
				strTmp.Format(_T("%d 虚回路规范性检查结果 \n") ,nNum);
				strFileText += strTmp;
				ExportResultsTxt(strFileText ,pVirLoopResults);
				nNum++;
			}	
		}
		std::string stText;

#ifdef UNICODE
		CT2CA pszConvertedAnsiString(strFileText); 
		stText = pszConvertedAnsiString;
#else
		stText = strFileText;
#endif
		filReport.SeekToEnd();
		filReport.Write(stText.c_str() ,stText.length());
		filReport.Close();

		MessageBox( NULL,_T("导出报告完成") ,_T("报告导出"),MB_OK);
	}
	else
		MessageBox( NULL,_T("导出txt报告失败") ,_T("报告导出"),MB_OK);
}

void CSclCheckResultTool::ExportResultsTxt(CString &strFileText, CResultsRec *pResults)
{
	CResultRec *pResult = NULL;
	POS posResult = pResults->GetHeadPosition();

	CString strTmp;

	while (posResult != NULL)
	{
		pResult = (CResultRec *)pResults->GetNext(posResult);
		strTmp.Format(_T("%s: %s; \r\n\r错误定位: %s;\r\n") ,pResult->m_strErrorType ,pResult->m_strErrorText ,pResult->m_strErrorPos);
		strFileText += strTmp;
	}
	strTmp.Format(_T("提示总数: %d 个; 告警总数: %d 个; 错误总数: %d 个; 严重错误总数: %d 个;\r\n") ,pResults->m_nAllTipIndex ,pResults->m_nAllWarningIndex ,
		pResults->m_nAllErrorIndex ,pResults->m_nAllFatalErrorIndex);
	strFileText += strTmp;
}

//目前不使用这种方式创建、打开word，因为这种方式下当word已打开时会弹出**已打开对话框。
BOOL CSclCheckResultTool::CreateWordApplication(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		m_WordApp.ReleaseDispatch();
		m_WordApp = NULL;
	}

	//创建对象
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			AfxMessageBox(_T("没有安装Word"));
			return FALSE;
		}

		m_WordApp.SetVisible(bVisible);  //This shows the application.
	}
	catch (...)
	{
	}

	return TRUE;
}

BOOL CSclCheckResultTool::NewWordReportFile()
{
	if (m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs(m_WordApp.GetDocuments());

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_WordApp.SetVisible(TRUE);
	BOOL bTrue = TRUE,bFileExist = FALSE;

	CString strSrcFile;

	strSrcFile = _P_GetResourcePath();
	strSrcFile += _T("RptResFile.docx");

	if (IsFileExist(strSrcFile))
	{
		bFileExist = TRUE;
	}
	else
	{
		strSrcFile = ChangeFilePostfix(strSrcFile,_T("doc"));

		if (IsFileExist(strSrcFile))
		{
			bFileExist = TRUE;
		}
	}

	if (bFileExist)
	{
		CopyFile(strSrcFile,m_strRptFile,FALSE);//将主报告拷贝一份并改名为目标报告名

		COleVariant destfile(m_strRptFile);
		m_doc = docs.Open(destfile,covTrue,covFalse,covFalse,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
		if(m_doc == NULL)
		{
			ExitWordApplation();
			bTrue = FALSE;
		}
	} 
	else
	{
		try
		{
			CComVariant Template(_T("")); 
			CComVariant NewTemplate(false),DocumentType(0),Visible;
			m_doc = docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
		}
		catch(...)
		{
			bTrue = FALSE;
		}
	}

	return bTrue;
}

BOOL CSclCheckResultTool::ExitWordApplation()
{
	//退出WORD应用
	try
	{
		if(m_WordApp)
		{
			COleVariant vTrue((short)TRUE);
			COleVariant vFalse((short)FALSE);
			COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

			m_WordApp.ReleaseDispatch();
			m_WordApp.Quit(vFalse, vOpt, vOpt);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	return TRUE;
}

void CSclCheckResultTool::InsertTitle(const CString &strTitle, long nTitleLevel)
{
	COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	MSWord::Selection wordSelection = m_WordApp.GetSelection();

	wordSelection = m_WordApp.GetSelection();
	wordSelection.EndKey(&vUnit, &vOpt);
	wordSelection.TypeParagraph();

	if (nTitleLevel > 0)
	{
		wordSelection.TypeText(strTitle);
		MSWord::Styles oStyles = m_doc.GetStyles();
		CString strStyle;
		strStyle.Format(_T("标题 %d"), nTitleLevel);
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

void CSclCheckResultTool::ExportReport_SetFont(MSWord::Selection oSelection, LPCTSTR lpszFontName,float fFontSize,int nBold)
{
	MSWord::_Font ftWord;
	ftWord	= oSelection.GetFont();
	ftWord.SetName(lpszFontName);
	ftWord.SetSize(fFontSize);
	ftWord.SetBold(nBold);
	oSelection.SetFont(ftWord);
}

void CSclCheckResultTool::ExportReport_Results(const CString &strSecondTitle, CResultsRec *pResults)
{
	InsertTitle(strSecondTitle, 2);

	long nVal = MSWord::wdWord9TableBehavior;
	CComVariant vTableBehavior(nVal); 
	nVal = MSWord::wdAutoFitFixed;
	CComVariant vAutoFitBehavior(nVal); 

	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	MSWord::Tables oTables = m_doc.GetTables();
	MSWord::Table oTable   = oTables.Add(oRange, 1, 8, &vTableBehavior, &vAutoFitBehavior);
	MSWord::Columns oCols = oTable.GetColumns();
	MSWord::Column  oCol  = NULL;

	try
	{
		oCol  = oCols.Item(1);
		float fWidth = oCol.GetWidth();
		float fWidthTotl = fWidth * 8;
		float fTemp = fWidth / 2;
		m_fWidthCol1 = fTemp;
		oCol.SetWidth(fTemp);
		fWidthTotl -= fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("序号"));

		oCol  = oCols.Item(2);
		fTemp = fWidth;
		fWidthTotl -= fTemp;
		oCol.SetWidth(fTemp);
		m_fWidthCol2 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("类型"));

		oCol  = oCols.Item(3);
		fTemp = fWidth * 3;
		fWidthTotl -= fTemp;
		oCol.SetWidth(fTemp);
		m_fWidthCol3 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("描述信息"));

		oCol  = oCols.Item(4);
		fTemp = fWidth*1.5;
		fWidthTotl -= fTemp;
		oCol.SetWidth(fTemp);
		m_fWidthCol4 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("异常定位"));

		oCol  = oCols.Item(5);
		fTemp = fWidthTotl/4;
		oCol.SetWidth(fTemp);
		m_fWidthCol5 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("提示"));

		oCol  = oCols.Item(6);
		oCol.SetWidth(fTemp);
		m_fWidthCol6 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("告警"));

		oCol  = oCols.Item(7);
		oCol.SetWidth(fTemp);
		m_fWidthCol7 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("错误"));

		oCol  = oCols.Item(8);
		oCol.SetWidth(fTemp);
		m_fWidthCol8 = fTemp;
		oCol.Select();
		ExportReport_SetFont(oSelection,_T("宋体"),10.5,1);
		oSelection.TypeText(_T("严重错"));

		CResultRec *pResult = NULL;
		POS posResult = pResults->GetHeadPosition();

		long nRowIndex = 1;

		while (posResult != NULL)
		{
			pResult = (CResultRec *)pResults->GetNext(posResult);
			ExportReport_Result(oTable ,pResult ,nRowIndex);
			nRowIndex++;
		}

	}
	catch (...)
	{

	}

	long nRowIndex = 1;
}

void CSclCheckResultTool::ExportReport_Result(MSWord::Table &oTable, CResultRec *pResult, long &nRowIndex)
{
	long nRows = 0;
	MSWord::Rows oRows = oTable.GetRows();
	MSWord::Row  oRow  = NULL;
	MSWord::Cell oCell = NULL;
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 

	CString strNum;
	strNum.Format(_T("%d") , nRowIndex);

	InsertRow(oRow, oTable, FALSE);
	SetRowCellText(oRow, 1,  strNum);
	SetRowCellText(oRow, 2,  pResult->m_strErrorType);
	SetRowCellText(oRow, 3,  pResult->m_strErrorText);
	SetRowCellText(oRow, 4,  pResult->m_strErrorPos);
	strNum.Format(_T("%d") , pResult->m_nTipIndex);
	SetRowCellText(oRow, 5,  strNum);
	strNum.Format(_T("%d") , pResult->m_nWarningIndex);
	SetRowCellText(oRow, 6,  strNum);
	strNum.Format(_T("%d") , pResult->m_nErrorIndex);
	SetRowCellText(oRow, 7,  strNum);
	strNum.Format(_T("%d") , pResult->m_nFatalErrorIndex);
	SetRowCellText(oRow, 8,  strNum);
}

void CSclCheckResultTool::InsertRow(MSWord::Row &oRow, MSWord::Table &oTable, BOOL bSplit)
{
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::Range oRange = oSelection.GetRange();
	CComVariant vCount(long(1)); 
	oSelection.InsertRowsBelow(&vCount);
	MSWord::Rows oRows = oTable.GetRows();
	oRow = oRows.Item(oRows.GetCount());
	MSWord::Cells oCells = oRow.GetCells();

	if (!bSplit)
	{
		return;
	}

	if (oCells.GetCount() == 3)
	{
		CComVariant vCols(long(2)); 
		CComVariant vMergeBeforeSplit(long(0)); 
		MSWord::Cell oCell = oCells.Item(1);
		oCell.Select();
		oSelection = m_WordApp.GetSelection();
		oCells = oSelection.GetCells();
		oCells.Split(&vCount, &vCols, &vMergeBeforeSplit);

		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.SetWidth(m_fWidthCol1);

		oCell = oCells.Item(2);
		oCell.SetWidth(m_fWidthCol2);

		oCell = oCells.Item(3);
		oCell.SetWidth(m_fWidthCol3);

		oCell = oCells.Item(4);
		oCell.SetWidth(m_fWidthCol4);
	}
}

void CSclCheckResultTool::MergeRow(MSWord::Row &oRow)
{
	MSWord::Cells oCells = oRow.GetCells();

	if (oCells.GetCount() == 3)
	{
		return;
	}

	MSWord::Cell  oCell = oCells.Item(1);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();

	long nVal;
	nVal = MSWord::wdCharacter;
	CComVariant vUnit(nVal); 
	CComVariant vCount(long(1)); 
	nVal = MSWord::wdExtend;
	CComVariant vExtend(nVal); 
	oSelection.MoveRight(&vUnit, &vCount, &vExtend);
	oCells = oSelection.GetCells();
	oCells.Merge();
}

void CSclCheckResultTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(RGB(0, 0, 0));
	oFont.SetBold(0);
	oSelection.TypeText(strText);
}

void CSclCheckResultTool::SetRowCellText(MSWord::Row &oRow, long nIndex, const CString &strText, COLORREF color)
{
	MSWord::Cells oCells = oRow.GetCells();
	MSWord::Cell  oCell = oCells.Item(nIndex);
	oCell.Select();
	MSWord::Selection oSelection = m_WordApp.GetSelection();
	MSWord::_Font oFont = oSelection.GetFont();
	oFont.SetColor(color);
	oFont.SetBold(0);
	oSelection.TypeText(strText);
	oFont.SetColor(RGB(0, 0, 0));
}