#include "StdAfx.h"
#include "RptTemplate_GenDocTool.h"
#include "RptTemp_Png.h"

#define GRID_CELL_CENTER

CRptTemplate_GenDocTool::CRptTemplate_GenDocTool(void)
{
}

CRptTemplate_GenDocTool::~CRptTemplate_GenDocTool(void)
{
}

BOOL CRptTemplate_GenDocTool::GetWordApp(BOOL bShow)
{
	if (m_WordApp == NULL)
	{
		try
		{
			if (!m_WordApp.CreateDispatch(_T("Word.Application")))
			{
				AfxMessageBox(_T("没有安装Word"));
				return NULL;
			}

			m_WordApp.SetVisible(bShow);  //This shows the application.
		}
		catch (...)
		{
			TRACE("catch error-----");
		}
	}

	return (m_WordApp != NULL);
}

void CRptTemplate_GenDocTool::SetDestRptFile(const CString &strDestFile)
{
	m_strDestRptFile = strDestFile;
}

void CRptTemplate_GenDocTool::SetSrcRptFile(const CString &strSrcRptFile)
{
	m_strSrcRptFile = strSrcRptFile;
}

void CRptTemplate_GenDocTool::SetXmlFile(const CString &strXmlFile)
{
	m_strXmlFile = strXmlFile;
}

BOOL CRptTemplate_GenDocTool::OpenXmlRptFile(const CString &strXmlRptFile)
{
	if (!IsFileExist(strXmlRptFile))
	{
		return FALSE;
	}

	m_strXmlFile = strXmlRptFile;
	m_oRptTemp_TestMacroUiRpt.DeleteAll();

	return m_oRptTemp_TestMacroUiRpt.OpenXmlFile(strXmlRptFile, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
}

BOOL CRptTemplate_GenDocTool::OpenDocRptFile(const CString &strDocRptFile)
{
	CString strRpt;
	strRpt = strDocRptFile;

	if (! GetWordApp(TRUE))
	{
		return FALSE;
	}

	if (!IsFileExist(strRpt))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("找不到word的报告模板文件【%s】"), strRpt.GetString());
		return FALSE;
	}

	m_strSrcRptFile = strRpt;
	strRpt.Replace(_T("/"), _T("\\"));
	MSWord::Documents docs = m_WordApp.GetDocuments();
	COleVariant vDocFile(strRpt);	
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_oRptDoc = docs.Open(&vDocFile,covOptional,covFalse,covFalse,covOptional,covOptional,covFalse,covOptional,covOptional,covOptional,covOptional,covTrue);

	return (m_oRptDoc != NULL);
}

BOOL CRptTemplate_GenDocTool::SaveDocRptFile(const CString &strFilePath)
{
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	if (strFilePath.IsEmpty())
	{
		return FALSE;
		//此处不能保持，否则模板中将有数据，会导致下一次导出出错
		//m_oRptDoc.Save();
	}
	else
	{
		CString strPath, strName;
		strPath = GetPathFromFilePathName(strFilePath);
		strName = GetFileNameFromFilePath(strFilePath);
		m_WordApp.ChangeFileOpenDirectory(strPath);
		COleVariant vDocFile(strName);
		COleVariant vFormat((long)MSWord::wdFormatDocument);
		COleVariant vFalse((long)FALSE), vTrue((long)TRUE);
		COleVariant vPassWord("");
		m_oRptDoc.SaveAs(vDocFile, vFormat, vFalse, vPassWord, vTrue
			, vPassWord, vFalse, vFalse, vFalse, vFalse, vFalse);
	}

	return TRUE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word()
{
	return GenRpt_Word(m_strXmlFile, m_strSrcRptFile);
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word(const CString &strXmlFile, const CString &strDocRptFile)
{
	if (! KillWordProgram())
	{
		return FALSE;
	}

	BOOL bRet = TRUE;

	if (!OpenXmlRptFile(strXmlFile))
	{
		return FALSE;
	}

	if (!IsFileExist(strDocRptFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开word文件【%s】失败！"), strDocRptFile.GetString());
		return FALSE;
	}

	CString strDestFile = m_strDestRptFile;
	X_CopyFile(strDocRptFile, strDestFile);  //先拷贝doc模板到目标路径下

	if (!OpenDocRptFile(strDestFile))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开word文件【%s】失败！"), m_strDestRptFile.GetString());
		return FALSE;
	}

	//MSWord::Documents docs = m_WordApp.GetDocuments();

	bRet = GenRpt_Word_TestMacroUiRpt(&m_oRptTemp_TestMacroUiRpt);
	//SaveDocRptFile(m_strDestRptFile);
	m_oRptDoc.Save();

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_TestMacroUiRpt(CRptTemp_TestMacroUiRpt *pRptRemp_TestMacroUiRpt)
{
	if (pRptRemp_TestMacroUiRpt == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pRptRemp_TestMacroUiRpt->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pRptRemp_TestMacroUiRpt->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
		{
			CRptTemp_Items *pRptTemp_Items = (CRptTemp_Items *)pObj;

		if (! GenRpt_Word_Items(pRptTemp_Items))
		{
			bRet = FALSE;
		}

			continue;
		}

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
		{
			CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate *)pObj;

			if (! GenRpt_Word_ReportTemplate(pRptTemp_ReportTemplate))
			{
				bRet = FALSE;
			}

			continue;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Items(CRptTemp_Items *pRptTemp_Items)
{
	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;

	if (pRptTemp_Items->m_nRpt_Title == 1)
	{
		if (!InsertTitle(pRptTemp_Items->m_strName, pRptTemp_Items->m_ntitle_level))
		{
			bRet = FALSE;
		}
	}

	POS pos = pRptTemp_Items->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pRptTemp_Items->GetNext(pos);
		nClassID = pObj->GetClassID();

		switch (nClassID)
		{
		case MNGRCLASSID_CRPTTEMP_ITEMS:
			{
				CRptTemp_Items *pRptTemp_ChildItems = (CRptTemp_Items *)pObj;

				if (! GenRpt_Word_Items(pRptTemp_ChildItems))
				{
					bRet = FALSE;
				}
			}
			break;

		case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
			{
				CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate *)pObj;

				if (! GenRpt_Word_ReportTemplate(pRptTemp_ReportTemplate))
				{
					bRet = FALSE;
				}
			}
			break;
		case MNGRCLASSID_CRPTTEMP_MACROCHARITEMS:
			{
				CRptTemp_MacroCharItems *pRptTemp_MacroCharItems = (CRptTemp_MacroCharItems *)pObj;

				if (! GenRpt_Word_MacroCharItems(pRptTemp_MacroCharItems))
				{
					bRet = FALSE;
				}
			}
			break;
		default:
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

//阻抗搜索项目，一定是所有的子项目生成一个表格。所以直接处理report-template
BOOL CRptTemplate_GenDocTool::GenRpt_Word_MacroCharItems(CRptTemp_MacroCharItems *pRptTemp_MacroCharItems)
{
	CRptTemp_ReportTemplate *pReportTemplate = pRptTemp_MacroCharItems->GetReportTemplate();
	ASSERT(pReportTemplate != NULL);

	if (pReportTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("阻抗搜索项目下，找不到“report-template”节点"));
		return FALSE;
	}

	return GenRpt_Word_ReportTemplate(pReportTemplate);
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_ReportTemplate(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate)
{
	if (pRptTemp_ReportTemplate == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pRptTemp_ReportTemplate->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pRptTemp_ReportTemplate->GetNext(pos);
		nClassID = pObj->GetClassID();

		switch (nClassID)
		{
		case MNGRCLASSID_CRPTTEMP_TITLE:
			{
				CRptTemp_Title *pTitle = (CRptTemp_Title *)pObj;
				
				if (! GenRpt_Word_Title(pTitle))
				{
					bRet = FALSE;
				}
			}
			break;
		case MNGRCLASSID_CRPTTEMP_TEXT:
			{
				CRptTemp_Text *pText = (CRptTemp_Text *)pObj;

				if (! InsertText(pText->m_strText, pText->m_strHAlignType, pText->m_strFont, pText->m_nBold, pText->m_fSize))
				{
					bRet = FALSE;
				}
			}
			break;
		case MNGRCLASSID_CRPTTEMP_GRID:
			{
				CRptTemp_Grid *pGrid = (CRptTemp_Grid *)pObj;

				if (! GenRpt_Word_Grid(pGrid))
				{
					bRet = FALSE;
				}
			}
			break;
		case MNGRCLASSID_CRPTTEMP_PNG:
			{
				CRptTemp_Png *pPng = (CRptTemp_Png *)pObj;

				if (! InsertPng(pPng->m_strPngPath))
				{
					bRet = FALSE;
				}
			}
			break;
		case MNGRCLASSID_CRPTTEMP_NEWPAGE:  //ftt 2024.12.9

			{
				if (! InsertNewPage())
				{
					bRet = FALSE;
				}
			}
			break;
		default:
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Title(CRptTemp_Title *pRptTemp_Title)
{
	if (pRptTemp_Title == NULL)
	{
		return FALSE;
	}

	long nTitleLevel = pRptTemp_Title->m_nLevel;
	return InsertTitle(pRptTemp_Title->m_strText, nTitleLevel);
}

/*
//表格填写模式：
/*1、row-item：行为测试项目。针对单点测试，一行对应一个测试项目（电气量，macrotest）。
  2、col-item：列为测试项目。（暂不实现）
  3、row-rpt：行为测试报告。针对重复测试，一行对应一个report-def
  4、col-rpt：列为测试报告。（暂不实现）
#define RPT_TEMPLATE_DATAMODE_ROW_ITEM    _T("row-item")
#define RPT_TEMPLATE_DATAMODE_COL_ITEM    _T("col-item")
#define RPT_TEMPLATE_DATAMODE_ROW_RPT     _T("row-rpt")
#define RPT_TEMPLATE_DATAMODE_COL_RPT     _T("col-rpt")
#define RPT_TEMPLATE_DATAMODE_NOT_DEF     _T("not-def")   //未定义，非法
*/
BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid(CRptTemp_Grid *pRptTemp_Grid)
{
	if (pRptTemp_Grid == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;

	if (pRptTemp_Grid->IsDataMode_Row())
	{
		if (! GenRpt_Word_Grid_RowMode(pRptTemp_Grid))
		{
			bRet = FALSE;
		}
	}
	else if (pRptTemp_Grid->IsDataMode_Col())
	{
		if (! GenRpt_Word_Grid_ColMode(pRptTemp_Grid))
		{
			bRet = FALSE;
		}
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

/*
<grid>
	<head>
		<cell row-span="2" text="整定值（s）"/>
		<cell row-span="2" text="测次"/>
		<cell text="实测动作时间（ms）" col-span="2"/>
		<cell/>
		<cell text="误差（ms）" col-span="2"/>
		<cell/>
	</head>
	<head>
		<cell/>
		<cell/>
		<cell text="实测值"/>
		<cell text="误差"/>
		<cell text="最大"/>
		<cell text="最小"/>
	</head>
	<row>
		<cell row-span="5" text="0.05"/>
		<cell text="1"/>
		<cell text="49.000"/>
		<cell text="0.0"/>
		<cell row-span="5" text="-0.1"/>
		<cell row-span="5" text="0.0"/>
	</row>
</grid>
*/
BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_RowMode(CRptTemp_Grid *pRptTemp_Grid)
{
	if (pRptTemp_Grid == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	long nCols = pRptTemp_Grid->GetColsCount();   //获取列的数量
	long nRows = pRptTemp_Grid->GetRowsCount();   //获取行的数量
	MSWord::Table oTable = InsertGrid(nRows, nCols, pRptTemp_Grid->m_nShowBorders);   //插入表格

	POS pos = pRptTemp_Grid->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	long nRow = 0;

	//表格头写入数据
	while (pos != NULL)
	{
		pObj = pRptTemp_Grid->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
		{
			nRow++;
			CRptTemp_Head *pHead = (CRptTemp_Head *)pObj;

			//表格头，填写数据
			if (! GenRpt_Word_Head(nRow, pHead, oTable))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ROW)
		{
			nRow++;
			CRptTemp_Row *pRow = (CRptTemp_Row *)pObj;

			//表格数据行，填写数据
			if (! GenRpt_Word_Row(nRow, pRow, oTable))
			{
				bRet = FALSE;
			}
		}
		{
			bRet = FALSE;
		}
	}

	//合并单元格：针对表格头
	if (! GenRpt_Word_Grid_MergeCells_RowMode(pRptTemp_Grid, oTable))
	{
		bRet = FALSE;
	}

	//表格单元格格式居中
	//word中录制的宏如下：
	//oSel.ParagraphFormat.Alignment = wdAlignParagraphCenter;
	//oSel.Cells.VerticalAlignment = wdCellAlignVerticalCenter;
	//表格各单元格，已经配置了对齐方式，此处注释：2025-2-20
// 	oTable.Select();
// 	MSWord::Selection oSel = m_WordApp.GetSelection();
// #ifdef GRID_CELL_CENTER
// 	MSWord::Cells oCells = oSel.GetCells();
// 	oCells.SetVerticalAlignment(MSWord::wdAlignParagraphCenter);   //表格单元格上下居中
// 	MSWord::Range oRange = oSel.GetRange();
// 	MSWord::_ParagraphFormat oFormat = oSel.GetParagraphFormat();
// 	oFormat.SetAlignment(MSWord::wdAlignParagraphCenter);  //表格单元格左右居中
// #endif

	//合并完成后，移动光标到表格下方
	oTable.Select();
	MSWord::Selection oSel = m_WordApp.GetSelection();
	COleVariant vWdUnits((long)MSWord::wdLine);
	COleVariant vRowCount(nRows);
	COleVariant covFalse((long)FALSE);
	oSel.MoveDown(vWdUnits, vRowCount, covFalse);  //光标移到表格下方一行

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_ColMode(CRptTemp_Grid *pRptTemp_Grid)
{
	//列模式  暂不实现
	return -1;
}

//合并单元格，行模式
BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_RowMode(CRptTemp_Grid *pRptTemp_Grid, MSWord::Table oTable)
{
	BOOL bRet = TRUE;
	POS pos = pRptTemp_Grid->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	long nRow = 0;

	while (pos != NULL)
	{
		pObj = pRptTemp_Grid->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
		{
			nRow++;
			CRptTemp_Head *pHead = (CRptTemp_Head *)pObj;

			if (! GenRpt_Word_Grid_MergeCells_RowMode_Head(nRow, pHead, oTable))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ROW)
		{
			nRow++;
			CRptTemp_Row *pRow = (CRptTemp_Row *)pObj;

			if (! GenRpt_Word_Grid_MergeCells_RowMode_Row(nRow, pRow, oTable))
			{
				bRet = FALSE;
			}
		}
		else
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_ColMode(CRptTemp_Grid *pRptTemp_Grid, MSWord::Table oTable)
{
	//暂不实现
	return FALSE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_RowMode_Head(long nRow, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	long nCol = 0;
	POS pos = pRptTemp_Head->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pRptTemp_Head->GetNext(pos);
		nCol++;

		if (! GenRpt_Word_Grid_MergeCells_Cell(nRow, nCol, pCell, oTable))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_RowMode_Row(long nRow, CRptTemp_Row *pRptTemp_Row, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	long nCol = 0;
	POS pos = pRptTemp_Row->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pRptTemp_Row->GetNext(pos);
		nCol++;

		if (! GenRpt_Word_Grid_MergeCells_Cell(nRow, nCol, pCell, oTable))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_ColMode_Head(long nCol, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable)
{
	//暂不实现
	return FALSE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_ColMode_Col(long nCol, CRptTemp_Col *pRptTemp_Col, MSWord::Table oTable)
{
	//暂不实现
	return FALSE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Grid_MergeCells_Cell(long nRow, long nCol, CRptTemp_Cell *pRptTemp_Cell, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	CRptTemp_Head *pHead = NULL;
	CRptTemp_Row *pRow = NULL;
	long nColHasMerge = 0;

	if (pRptTemp_Cell->m_nCol_Span > 1
		|| pRptTemp_Cell->m_nRow_Span > 1)
	{
		CExBaseObject *pParent = (CExBaseObject *)pRptTemp_Cell->GetParent();

		//此处暂不考虑CRptTemp_Col
		if (pParent->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
		{
			pHead = (CRptTemp_Head *)pParent;
		}
		else if (pParent->GetClassID() == MNGRCLASSID_CRPTTEMP_ROW)
		{
			pRow = (CRptTemp_Row *)pParent;
		}
		
		if (pHead != NULL)
		{
			nColHasMerge = pHead->m_nMergeCol;
		}

		if (pRow != NULL)
		{
			nColHasMerge = pRow->m_nMergeCol;
		}

		nCol -= nColHasMerge;
		long nMergeRow = nRow + pRptTemp_Cell->m_nRow_Span - 1;
		long nMergeCol = nCol + pRptTemp_Cell->m_nCol_Span - 1;
		
		MSWord::Cell oCell = oTable.Cell(nRow, nCol);
		//计算目标单元格
		MSWord::Cell oCellMergeTo = oTable.Cell(nMergeRow, nMergeCol);

		if (oCellMergeTo != NULL && oCell != NULL)
		{
			//合并单元格时，单元格的内容不会合并；
			//同时，报告合并时，不会出现行、列同时合并的，此处只考虑合并同一列，多行合并
			if (nMergeRow > nRow)
			{
				//表头合并时，保留第一行的数据
				long nBegin = nRow + 1;
				long nEnd = nMergeRow;

				if (nMergeRow > 5)
				{
					//表示不是表头合并
					//数据行合并时，保留最后一行的数据
					nBegin = nRow;
					nEnd = nMergeRow - 1;
				}
				//先将需要合并的单元格的值，设置为空。这样合并后，就只剩下一个数据了
				for (int i=nBegin; i<=nEnd; i++)
				{
					MSWord::Cell oCellNext = oTable.Cell(i, nCol);
					MSWord::Range oRange = oCellNext.GetRange();
					oRange.SetText(_bstr_t(_T("")));
				}
			}

			//合并单元格
			oCell.Merge(oCellMergeTo);

			//合并后，记录合并的列数
			if (pHead != NULL)
			{
				pHead->m_nMergeCol += pRptTemp_Cell->m_nCol_Span;
				pHead->m_nMergeCol -= 1;
			}

			if (pRow != NULL)
			{
				pRow->m_nMergeCol += pRptTemp_Cell->m_nCol_Span;
				pRow->m_nMergeCol -= 1;
			}
		}
	}

	return TRUE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Head(long nRow, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	//ftt 2024.12.23 修改表头行高(head)
	if(pRptTemp_Head->m_fHeadHeight > 0.0)
	{
		MSWord::Rows oRows = oTable.GetRows();
		MSWord::Row oRow = oRows.Item(1);
		oRow.SetHeight(pRptTemp_Head->m_fHeadHeight * 28.346); //cm -> pt 28.3464566929134
	}

	//ftt 2024.12.24 修改表格所有列的列宽
	if (pRptTemp_Head->m_fColWidth > 0.0)
	{
		MSWord::Columns oColumns = oTable.GetColumns();
		MSWord::Column oColumn;
		for (long i = 1; i <= oColumns.GetCount(); ++i)
		{
			oColumn = oColumns.Item(i);
			oColumn.SetWidth(pRptTemp_Head->m_fColWidth * 28.346); //cm -> pt 28.3464566929134
		}
	}

	BOOL bRet = TRUE;
	long nCol = 0;
	POS pos = pRptTemp_Head->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pRptTemp_Head->GetNext(pos);
		nCol++;

		if (! GenRpt_Word_Cell(nRow, nCol, pCell, oTable))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Row(long nRow, CRptTemp_Row *pRptTemp_Row, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	//ftt 2024.12.24 修改行高(row)
	if (pRptTemp_Row->m_fRowHeight > 0.0)
	{
		MSWord::Rows oRows = oTable.GetRows();
		MSWord::Row oRow = oRows.Item(nRow);
		oRow.SetHeight(pRptTemp_Row->m_fRowHeight * 28.346);  //cm -> pt 28.3464566929134
	}

	BOOL bRet = TRUE;
	long nCol = 0;
	POS pos = pRptTemp_Row->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pRptTemp_Row->GetNext(pos);
		nCol++;

		if (! GenRpt_Word_Cell(nRow, nCol, pCell, oTable))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Col(long nCol, CRptTemp_Col *pRptTemp_Col, MSWord::Table oTable)
{
	//暂不实现 
	return FALSE;
}

BOOL CRptTemplate_GenDocTool::GenRpt_Word_Cell(long nRow, long nCol, CRptTemp_Cell *pRptTemp_Cell, MSWord::Table oTable)
{
	if (oTable == NULL)
	{
		return FALSE;
	}

	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	MSWord::Cell oCell = oTable.Cell(nRow, nCol);
	MSWord::Range oRange = oCell.GetRange();
	//oRange.SetText(_bstr_t(pRptTemp_Cell->m_strText)); //ftt 2024.12.20
	 
	//ftt 2024.12.20
	MSWord::Selection sel = m_WordApp.GetSelection();
	sel.SetRange(oRange.GetStart(), oRange.GetEnd());
	sel.TypeText(_bstr_t(pRptTemp_Cell->m_strText));

	MSWord::Cells oCells = sel.GetCells();
	CString strVAlignType = pRptTemp_Cell->m_strVAlignType;

	if (strVAlignType == "AlignTop")
	{
		oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalTop);
	}
	else if (strVAlignType == "AlignCenter" || strVAlignType == "")
	{
		oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalCenter);
	}
	else if (strVAlignType == "AlignBottom")
	{
		oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalBottom);
	}
	else 
	{
		//表格对垂直对齐方式，默认上下居中
		oCells.SetVerticalAlignment(MSWord::wdCellAlignVerticalCenter);
	}
	
	MSWord::_ParagraphFormat oFormat = sel.GetParagraphFormat();
	CString strHAlignType = pRptTemp_Cell->m_strHAlignType;
	
	if (strHAlignType == "AlignLeft")
	{ 
		oFormat.SetAlignment(MSWord::wdAlignParagraphLeft);
	}
	else if (strHAlignType == "AlignCenter" || strHAlignType == "")
	{
		oFormat.SetAlignment(MSWord::wdAlignParagraphCenter);
	}
	else if (strHAlignType == "AlignRight")
	{  
		oFormat.SetAlignment(MSWord::wdAlignParagraphRight);
	}
	else 
	{
		//表格对左右对齐方式，默认左右两端对齐
		oFormat.SetAlignment(MSWord::wdAlignParagraphJustify);
	}

	return TRUE;
}

BOOL CRptTemplate_GenDocTool::InsertNewPage()
{
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	MSWord::Selection sel;
	sel = m_WordApp.GetSelection();

	COleVariant vType((long)MSWord::wdPageBreak);
	sel.InsertBreak(vType);

	return TRUE;
}

//插入一张图片
/*
ActiveDocument.Shapes.AddPicture(Anchor:=Selection.Range, FileName:= _
"D:\Program Files\EPOTO\Stt\Workspace\Img\LineDiffCurr6ITest$DiffCurrChar$DiffTCurr_AImg.png" _
, LinkToFile:=False, SaveWithDocument:=True).WrapFormat.Type = _
wdWrapTopBottom
*/
BOOL CRptTemplate_GenDocTool::InsertPng(const CString &strPngFile)
{
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	if (!IsFileExist(strPngFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("找不到图片【%s】"), strPngFile.GetString());
		return FALSE;
	}

	MSWord::Shapes		 oShapes;
	MSWord::Shape		 oShape;
	MSWord::WrapFormat	 oWordWrpFormat;
	MSWord::ShapeRange   oShapeRange;
	MSWord::Range  range;

	COleVariant vUnit((long)MSWord::wdCharacter);
	COleVariant vCount((long)1);
	COleVariant vHeight((long)150);
	COleVariant vWidth((long)225);
	COleVariant vMove((long)MSWord::wdMove);
	COleVariant vWdUnits((long)MSWord::wdLine);
	COleVariant covTrue((long)TRUE), covFalse((long)FALSE);
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	COleVariant vRange;

	MSWord::Selection sel;
	sel = m_WordApp.GetSelection();
	range = sel.GetRange();
	
	vRange.vt=VT_DISPATCH;
	vRange.pdispVal = range.m_lpDispatch;
	range.m_lpDispatch->AddRef();
	long nStsrt = range.GetStart();
	long nEnd = range.GetEnd();
	COleVariant vLeft(nStsrt);
	COleVariant vTop(nEnd);

	sel.TypeParagraph();//回车
	sel.MoveUp(vWdUnits, vCount, vMove);
 	oShapes = m_oRptDoc.GetShapes();
 	oShape = oShapes.AddPicture(_bstr_t(strPngFile), covFalse, covTrue, vLeft, vTop, vWidth, vHeight, vRange);
  	oWordWrpFormat = oShape.GetWrapFormat();
  	oWordWrpFormat.SetType(MSWord::wdWrapTopBottom);   //文字环绕：上下型
  	oShape.Select(vRange);
 	sel = m_WordApp.GetSelection();
 	oShapeRange = sel.GetShapeRange();
 	//图片位置：垂直方向，相对于“行”，顶端对齐
	oShapeRange.SetRelativeVerticalPosition(MSWord::wdRelativeVerticalPositionLine);  
	oShapeRange.SetTop(MSWord::wdShapeTop);
	//图片位置：水平方向，相对于“页边距”，居中
 	oShapeRange.SetRelativeHorizontalPosition(MSWord::wdRelativeVerticalPositionMargin);
 	oShapeRange.SetLeft(MSWord::wdShapeCenter);
 	vRange.Detach();
	
	sel.MoveDown(vWdUnits, vCount, vMove);
	//sel.TypeParagraph();//回车
	return TRUE;
}


//插入一个文本
BOOL CRptTemplate_GenDocTool::InsertText(const CString &strText, const CString & strHAlignType, const CString &strFont, long nBold, float fSize)
{
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	CString strOldFontName;
	MSWord::Selection sel;
	sel = m_WordApp.GetSelection();

	
 	MSWord::_ParagraphFormat oFormat = sel.GetParagraphFormat();

	//ftt 2024.12.19 文本对齐方式：居左且首行缩进、居中无缩进、居右有缩进(居右对齐时不管有无缩进，视觉效果都一样)
	if (strHAlignType == "AlignLeft" || strHAlignType == "")
	{		
		oFormat.SetCharacterUnitFirstLineIndent(2);  //设置段落格式：首行缩进两个字符 
		oFormat.SetAlignment(MSWord::wdAlignParagraphLeft);
	}
	else if (strHAlignType == "AlignCenter")
	{
		oFormat.SetAlignment(MSWord::wdAlignParagraphCenter);
	}
	else if (strHAlignType == "AlignRight")
	{
		oFormat.SetCharacterUnitFirstLineIndent(2);  //设置段落格式：首行缩进两个字符   
		oFormat.SetAlignment(MSWord::wdAlignParagraphRight);
	}
	else
	{
		//默认左对齐
		oFormat.SetCharacterUnitFirstLineIndent(2);  //设置段落格式：首行缩进两个字符 
		oFormat.SetAlignment(MSWord::wdAlignParagraphLeft);
	}

	//设置字体
	MSWord::_Font font;
	font = sel.GetFont();
	strOldFontName = font.GetName();

	CString strLeft, strRight;
	long nPos = strText.Find(_T("不合格"));	

	if(nPos < 0)
	{
		nPos = strText.Find(_T("合格"));
	}

	if (nPos >= 0)
	{
		//结论固定为黑体
		CString strFont_HeiTi;
		strFont_HeiTi = _T("黑体");
		strLeft = strText.Left(nPos);
		strRight = strText.Mid(nPos);

		font.SetSize(fSize);

		if (nBold == 1)
		{
			font.SetBold(MSWord::wdToggle);
		}

		sel.TypeText(_bstr_t(strLeft)); //插入文本。结论部分不处理字体
		font.SetName(_bstr_t(strFont_HeiTi));  //插入右半部分，固定设置为黑体
		sel.TypeText(_bstr_t(strRight)); 

		//插入文本后，恢复成初始态
		font.SetSize(10.5);
		font.SetName(_bstr_t(strOldFontName));

		if (nBold == 1)
		{
			font.SetBold(MSWord::wdToggle);
		}
	}
	else
	{
		font.SetSize(fSize);
		font.SetName(_bstr_t(strFont));

		if (nBold == 1)
		{
			font.SetBold(MSWord::wdToggle);
		}

		sel.TypeText(_bstr_t(strText)); //插入文本

		//插入文本后，恢复成初始态
		font.SetName(_bstr_t(strOldFontName));
		if (nBold == 1)
		{
			font.SetBold(MSWord::wdToggle);
		}
		font.SetSize(10.5);
	}
	
	sel.TypeParagraph();//回车
	oFormat.SetAlignment(MSWord::wdAlignParagraphLeft);  //ftt 2024.12.19 

	return TRUE;
}

//插入一个标题
BOOL CRptTemplate_GenDocTool::InsertTitle(const CString &strTitleText, long nTitleLevel)
{
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	CString strTitleLevel;
	GetTitleLevel(nTitleLevel, strTitleLevel);
	COleVariant vTitleLevel(strTitleLevel);
	COleVariant vTitleText(strTitleLevel);
	COleVariant vWdUnits((long)MSWord::wdWord);
	long nCount = 1;
	COleVariant vCount(nCount);

	BOOL bRet = TRUE;
	MSWord::Selection sel;
	sel = m_WordApp.GetSelection();
	sel.MoveEnd(vWdUnits, vCount);
	sel.SetStyle(vTitleLevel);   //将标题设置成对应的标题等级
	sel.TypeText(_bstr_t(strTitleText)); //插入标题文本
	sel.TypeParagraph();//回车
	return bRet;
}

//插入一个表格
MSWord::Table CRptTemplate_GenDocTool::InsertGrid(long nRows, long nCols, long nShowBorders)
{
	MSWord::Table oNewTable;
	if (m_oRptDoc == NULL)
	{
		return FALSE;
	}

	MSWord::Range  range;
	MSWord::Selection sel;
	sel = m_WordApp.GetSelection();
	range = sel.GetRange();
	COleVariant vaultTableBehavior((long)MSWord::wdWord9TableBehavior);
	COleVariant vAutoFitBehavior((long)MSWord::wdAutoFitFixed);
	COleVariant vWdUnits((long)MSWord::wdLine);
	COleVariant vRowCount(nRows);
	COleVariant covTrue((long)TRUE), covFalse((long)FALSE);
	float fWidth = 15.24 * 28.3527;  //磅。表格宽15.24厘米

	MSWord::Tables oTables = m_oRptDoc.GetTables();
	oNewTable = oTables.Add(range, nRows, nCols, vaultTableBehavior, vAutoFitBehavior);   //插入表格

	if (nShowBorders == 0)
	{
		MSWord::Borders oBorders = oNewTable.GetBorders();
		oBorders.SetInsideLineStyle((long)MSWord::wdLineStyleNone);
		oBorders.SetOutsideLineStyle((long)MSWord::wdLineStyleNone);
		oBorders.SetShadow(false);
	}

	//根据列的数量，设置每列为固定宽度：使得表格总宽度15.24厘米
	MSWord::Columns oCols = oNewTable.GetColumns();
	oCols.SetWidth(fWidth / nCols);

	//表格居中
	MSWord::Rows oRows = oNewTable.GetRows();
	oRows.SetAlignment((long)MSWord::wdAlignRowCenter);
	//sel.MoveDown(vWdUnits, vRowCount, covFalse);  //光标移到表格下方一行

	return oNewTable;
}

BOOL CRptTemplate_GenDocTool::KillWordProgram(BOOL bShowMsg)
{
	if (! IsProgramExist(_T("winword.exe")))
	{
		return TRUE;
	}

	int nRet = IDOK;
	
	if (bShowMsg)
	{
		nRet = 	::MessageBox(NULL,_T("检测到WORD进程正在运行，请先关闭WORD进程后，再导出报告……"),_T("关闭WORD进程"),MB_OKCANCEL);
	}

	switch(nRet)
	{
	case IDOK:
		{
			if (m_WordApp != NULL)
			{
				COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				m_WordApp.Quit(covFalse, covOptional, covOptional);
				m_WordApp = NULL;
			}

			if (m_oRptDoc != NULL)
			{
				m_oRptDoc = NULL;
			}

			TerminateProgram(_T("winword.exe"));
			return TRUE;
		}
	case IDCANCEL:
		return FALSE;
	}

	return FALSE;
}

void CRptTemplate_GenDocTool::GetTitleLevel(long nTitleLevel, CString &strTitleLevel)
{
	switch (nTitleLevel)
	{
	case 1: strTitleLevel.Format(_T("标题 %d"), nTitleLevel);
		break;
	case 2: strTitleLevel.Format(_T("标题 %d"), nTitleLevel);
		break;
	case 3: strTitleLevel.Format(_T("三级题目"));
		break;
	case 4: strTitleLevel.Format(_T("四级题目"));
		break;
	case 5: strTitleLevel.Format(_T("五级题目"));
		break;
	case 6: strTitleLevel.Format(_T("六级题目"));
		break;
	case 7: strTitleLevel.Format(_T("七级题目"));
		break;
	case 8: strTitleLevel.Format(_T("八级题目"));
		break;
	case 9: strTitleLevel.Format(_T("九级题目"));
		break;
	case 10: strTitleLevel.Format(_T("十级题目"));
		break;
	default:strTitleLevel.Format(_T("标题 %d"), nTitleLevel);
		break;
	}
}