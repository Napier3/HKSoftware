//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CDocXRead_WPS.cpp  CDocXRead_WPS


#include "stdafx.h"
#include "DocXRead_WPS.h"

CDocXRead_WPS *g_pDocXRead_WPS = NULL;

CDocXRead_WPS::CDocXRead_WPS()
{

}

CDocXRead_WPS::~CDocXRead_WPS()
{
}


void CDocXRead_WPS::Create()
{
	if (g_pDocXRead_WPS == NULL)
	{
		g_pDocXRead_WPS = new CDocXRead_WPS();
		g_pDocXRead_WPS->GetWordApp(TRUE);
	}
}

void CDocXRead_WPS::Release()
{
	if (g_pDocXRead_WPS != NULL)
	{
		g_pDocXRead_WPS->QuitApp();
		g_pDocXRead_WPS = NULL;
	}
}

BOOL CDocXRead_WPS::GetWordApp(BOOL bShow)
{
	if (m_WordApp != NULL)
	{
		return TRUE;
	}

	TickEnter();

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (!m_WordApp.CreateDispatch(_T("kwps.Application")))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("没有安装Word"));
			return FALSE;
		}

		m_WordApp.put_Visible(bShow);  //This shows the application.
		MessageTickCount(_T("Open Word Add"));

		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("******打开WINWORD.EXE异常******"));
		return FALSE;
	}
}

void CDocXRead_WPS::QuitApp()
{
	TickEnter();

	try
	{
		if (m_WordApp != NULL)
		{//关闭Word
			COleVariant vTrue((short)TRUE), vFalse((short)FALSE),
				vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			m_WordApp.Quit(vFalse,vOpt,vOpt);
			m_WordApp = NULL;

			MessageTickCount(_T("Exit Word Add"));
		}
	}
	catch (...) 
	{
	}

}

void CDocXRead_WPS::ShowApp(long nShow)
{
	try
	{
		m_WordApp.put_Visible(nShow);
	}
	catch (...) 
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetVisible  Error"));
	}
}

BOOL CDocXRead_WPS::ReadDocFile(CDocCmp *pDocCmp, const CString &strFile1, const CString strFile2)
{
	BOOL bFile1 = OpenDocFile(pDocCmp, strFile1);
	BOOL bFile2 = OpenDocFile(pDocCmp, strFile2);

	return ( bFile1 &&  bFile2 );

}

BOOL CDocXRead_WPS::OpenDocFile(CDocCmp *pDocCmp, const CString &strFile)
{
	CDocFile *pFile = new CDocFile();
	pFile->m_strID = strFile;

	if (OpenDocFile(pFile, strFile))
	{
		pDocCmp->AddNewChild(pFile);
		MessageTickCount(_T("ReadFile"));
		return TRUE;
	}
	else
	{
		delete pFile;
		return FALSE;
	}
}


BOOL CDocXRead_WPS::OpenDocFile(CDocFile *pFile, const CString &strFile)
{
	WPS::Documents docs =  m_WordApp.get_Documents();
	WPS::_Document oDocSrc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);

	COleVariant vRptFile(strFile);	
	TickEnter();

	try
	{
		//打开试验报告文件
		oDocSrc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue,
			covOptional,covOptional,covOptional,covOptional);

		MessageTickCount(strFile);

	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "file [%s] not exist", strFile.GetString());
		return FALSE;
	}

	pFile->m_strID = strFile;
	OpenDocFile(pFile, oDocSrc);
	MessageTickCount(_T("ReadFile"));

	oDocSrc.Close(covFalse,covOptional,covOptional);

	return TRUE;
}

/*
Sub ShowAllText()
	Dim paras As Paragraphs
	Dim para As Paragraph
	Dim retPara As Paragraph
	Dim tabs As Tables
	Dim rng As Range
	Dim tb As Table

	Set paras = ActiveDocument.Paragraphs
	Set para = paras.Item(1)

	'LogParagraph para

	Do While True
		Set rng = para.Range
		Set tabs = rng.Tables

		If tabs.Count = 0 Then
			LogRange rng
			Set para = para.Next
		Else
			Debug.Print "\r\n\r\n>>>>>>>>>>>>>>>>>>>>>> begin table >>>>>>>>>>>>>>>>>>>>>>>>>"
			Set para = ShowTablesText(tabs, retPara)
			Debug.Print "\r\n\r\n>>>>>>>>>>>>>>>>>>>>>> end table >>>>>>>>>>>>>>>>>>>>>>>>>"
			Set para = retPara.Next
			Set para = para.Next  '表格后面都还有一个空白行
		End If

		If para Is Nothing Then
			Exit Do
		End If

		'LogParagraph para
	Loop

End Sub
*/
void CDocXRead_WPS::OpenDocFile(CDocFile *pFile, WPS::_Document &oDoc)
{
	WPS::Paragraphs oParagraphs = NULL;
	WPS::Paragraph  oParagraph = NULL, oParagraphEnd = NULL;
	WPS::Range oRange = NULL;
	WPS::Tables oTables = NULL;
	CDocText *pText = NULL;
	CDocTable *pTable = NULL;
	COleVariant vCount((long)1);
	long nStart1, nEnd1, nStart2, nEnd2, nStart, nEnd;

	oParagraphs = oDoc.get_Paragraphs();
	oParagraph = oParagraphs.Item(1);
	oParagraphEnd = oParagraphs.Item(oParagraphs.get_Count());
	GetParagraphPos(oParagraph, nStart1, nEnd1);
	GetParagraphPos(oParagraphEnd, nStart2, nEnd2);

	if (m_pProgress != NULL)
	{
		m_pProgress->SetMaxRange(100);
	}

	while (oParagraph != NULL)
	{
		oRange = oParagraph.get_Range();
		oTables = oRange.get_Tables();

		if (oTables == NULL)
		{
			pText = new CDocText();
			ReadText(pText, oRange);
			pFile->AddNewChild(pText);
			oParagraph = oParagraph.Next(vCount);
		}
		else
		{
			if (oTables.get_Count() == 0)
			{
				pText = new CDocText();
				ReadText(pText, oRange);
				pFile->AddNewChild(pText);
				oParagraph = oParagraph.Next(vCount);
			}
			else
			{
				ReadTables(pFile, oTables, oParagraph);
				oParagraph = oParagraph.Next(vCount);  //表格后面都还有一个空白行
				oParagraph = oParagraph.Next(vCount); //表格后面空白行的下一行

				if (oParagraph == NULL)
				{
					break;
				}

				if (m_pProgress != NULL)
				{
					GetParagraphPos(oParagraph, nStart, nEnd);
					m_pProgress->SetPos( (nEnd - nStart1) * 100 / nEnd2);
				}
			}
		}
	}
}


void CDocXRead_WPS::ReadTables(CDocFile *pFile, WPS::Tables &oTables, WPS::Paragraph  &oRetParagrap)
{
	long nCount = oTables.get_Count();
	WPS::Table oTable = NULL;
	long k = 0;
	CDocTable *pTable = NULL;

	for (k=1; k<=nCount; k++)
	{
		oTable = oTables.Item(k);
		pTable = new CDocTable();
		//ReadTable(pTable, oTable, oRetParagrap);
		ReadTable_Cells(pTable, oTable, oRetParagrap);
		pFile->AddNewChild(pTable);
	}
}

/*
Function ShowTableText(ByVal tb As Table, ByRef retPara As Paragraph) As Paragraph
	Dim rws As Rows
	Dim cels As Cells
	Dim cel As Cell
	Dim rw As Row
	Dim para As Paragraph

	Set rws = tb.Rows

	For Each rw In rws
		Set cels = rw.Cells

		For Each cel In cels
			Set retPara = cel.Range.Paragraphs.Item(1)
			Set para = retPara
			Debug.Print "cel(" & cel.RowIndex; "," & cel.ColumnIndex; ")="
			LogRange cel.Range
		Next cel
	Next rw

	Set ShowTableText = para
End Function
*/
void CDocXRead_WPS::ReadTable(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap)
{
	WPS::Rows oRows = NULL;
	WPS::Row oRow = NULL;
	oRows = oTable.get_Rows();
	long nCount = oRows.get_Count();
	long k = 1;
	CDocRow *pRow = NULL;
	BOOL bError  = FALSE;

	for (k=1; k<=nCount; k++)
	{
		try
		{
			oRow = oRows.Item(k);
		}
		catch(...)
		{
			bError = TRUE;
			break;
		}
		pRow = new CDocRow();
		ReadRow(pRow, oRow, oRetParagrap);
		pTable->AddNewChild(pRow);
	}

	if (bError)
	{
		ReadTable_Cells(pTable, oTable, oRetParagrap);
	}
}

void CDocXRead_WPS::ReadTable_Cells(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap)
{
	WPS::Rows oRows = NULL;
	WPS::Columns oCols = NULL;
	WPS::Cell oCell = NULL;
	oRows = oTable.get_Rows();
	oCols = oTable.get_Columns();
	long nRows = oRows.get_Count();
	long nCols = oCols.get_Count();
	long nRow = 1, nCol = 1;
	CDocRow *pRow = NULL;
	BOOL bError  = FALSE;
	CDocCel *pCell = NULL;

	for (nRow=1; nRow<=nRows; nRow++)
	{
		pRow = new CDocRow();
		pTable->AddNewChild(pRow);

		for (nCol=1; nCol<= nCols; nCol++)
		{
			try
			{
				oCell = oTable.Cell(nRow, nCol);
			}
			catch(...)
			{
				continue;
			}

			pCell = new CDocCel();
			pRow->AddNewChild(pCell);
			ReadCel(pCell, oCell);
			pRow->m_fWidth += pCell->m_fWidth;
		}
	}
}


/*
Function ShowTableText(ByVal tb As Table, ByRef retPara As Paragraph) As Paragraph
	Dim rws As Rows
	Dim cels As Cells
	Dim cel As Cell
	Dim rw As Row
	Dim para As Paragraph

	Set rws = tb.Rows

	For Each rw In rws
		Set cels = rw.Cells

		For Each cel In cels
			Set retPara = cel.Range.Paragraphs.Item(1)
			Set para = retPara
			Debug.Print "cel(" & cel.RowIndex; "," & cel.ColumnIndex; ")="
			LogRange cel.Range
		Next cel
	Next rw

	Set ShowTableText = para
End Function
*/

void CDocXRead_WPS::ReadRow(CDocRow *pRow, WPS::Row &oRow, WPS::Paragraph  &oRetParagrap)
{
	pRow->m_fHeigh = oRow.get_Height();
	pRow->m_fWidth = 0;
	
	WPS::Cells oCells = NULL;
	WPS::Cell oCell = NULL;
	long nCount = 0;
	long k = 1;
	CDocCel *pCell = NULL;

	oCells = oRow.get_Cells();
	nCount = oCells.get_Count();

	for (k=1; k<=nCount; k++)
	{
		oCell = oCells.Item(k);
		pCell = new CDocCel();
		pRow->AddNewChild(pCell);
		ReadCel(pCell, oCell);
		pRow->m_fWidth += pCell->m_fWidth;
	}

	if (oCell != NULL)
	{
		WPS::Paragraphs oParagraphs = NULL;
		WPS::Range oRange = NULL;
		oRange = oCell.get_Range();
		oParagraphs = oRange.get_Paragraphs();
		oRetParagrap = oParagraphs.Item(oParagraphs.get_Count());
	}
}


/*
Function ShowTableText(ByVal tb As Table, ByRef retPara As Paragraph) As Paragraph
	Dim rws As Rows
	Dim cels As Cells
	Dim cel As Cell
	Dim rw As Row
	Dim para As Paragraph

	Set rws = tb.Rows

	For Each rw In rws
		Set cels = rw.Cells

		For Each cel In cels
			Set retPara = cel.Range.Paragraphs.Item(1)
			Set para = retPara
			Debug.Print "cel(" & cel.RowIndex; "," & cel.ColumnIndex; ")="
			LogRange cel.Range
		Next cel
	Next rw

	Set ShowTableText = para
End Function
*/
void CDocXRead_WPS::ReadCel(CDocCel *pCell, WPS::Cell &oCell)
{
	try
	{
		pCell->m_nCol = oCell.get_ColumnIndex();
		pCell->m_nRow = oCell.get_RowIndex();
		pCell->m_fWidth = oCell.get_Width();
		pCell->m_fHeight = oCell.get_Height();
	}
	catch (...)
	{
	}
	
	try
	{
		WPS::Range oRange = oCell.get_Range();
		ReadText(pCell ,oRange);
	}
	catch (...)
	{
	}

}


void CDocXRead_WPS::ReadText(CDocText *pText, WPS::Range &oRange)
{
	pText->m_nStart = oRange.get_Start();
	pText->m_nEnd = oRange.get_End();
	pText->m_strTxt = oRange.get_Text();

	pText->Init();
}

void CDocXRead_WPS::GetParagraphPos(WPS::Paragraph  &oParagraph, long &nStart, long &nEnd)
{
	WPS::Range oRange = oParagraph.get_Range();
	nStart = oRange.get_Start();
	nEnd = oRange.get_End();
}

BOOL CDocXRead_WPS::DocToXml(const CString &strFile)
{
	CDocFile oFile;
	oFile.m_strID = strFile;

	if (OpenDocFile(&oFile, strFile))
	{
		MessageTickCount(_T("ReadFile finish"));
		CString strFileXml;
		strFileXml = strFile;
		doctoxml_change_file_postfix(strFileXml);
		
		oFile.SaveXmlFile(strFileXml, CDocCmpXmlRWKeys::g_pXmlKeys, g_nDocToXmlFormat);

		//进行分组测试
		oFile.Group(CDocCmp::GetDocCmpConfig() );

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

