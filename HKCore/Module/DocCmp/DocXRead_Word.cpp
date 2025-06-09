//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CDocXRead_Word.cpp  CDocXRead_Word


#include "stdafx.h"
#include "DocXRead_Word.h"

CDocXRead_Word *g_pDocXRead_Word = NULL;

CDocXRead_Word::CDocXRead_Word()
{

}

CDocXRead_Word::~CDocXRead_Word()
{
}


void CDocXRead_Word::Create()
{
	if (g_pDocXRead_Word == NULL)
	{
		g_pDocXRead_Word = new CDocXRead_Word();
		g_pDocXRead_Word->GetWordApp(TRUE);
	}
}

void CDocXRead_Word::Release()
{
	if (g_pDocXRead_Word != NULL)
	{
		g_pDocXRead_Word->QuitApp();
		g_pDocXRead_Word = NULL;
	}
}

BOOL CDocXRead_Word::GetWordApp(BOOL bShow)
{
	if (m_WordApp != NULL)
	{
		return TRUE;
	}

	TickEnter();

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("没有安装Word"));
			return FALSE;
		}

		m_WordApp.SetVisible(bShow);  //This shows the application.
		MessageTickCount(_T("Open Word Add"));

		return TRUE;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("******打开WINWORD.EXE异常******"));
		return FALSE;
	}
}

void CDocXRead_Word::QuitApp()
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

void CDocXRead_Word::ShowApp(long nShow)
{
	try
	{
		m_WordApp.SetVisible(nShow);
	}
	catch (...) 
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetVisible  Error"));
	}
}

BOOL CDocXRead_Word::ReadDocFile(CDocCmp *pDocCmp, const CString &strFile1, const CString strFile2)
{
	BOOL bFile1 = OpenDocFile(pDocCmp, strFile1);
	BOOL bFile2 = OpenDocFile(pDocCmp, strFile2);

	return ( bFile1 &&  bFile2 );

}

BOOL CDocXRead_Word::OpenDocFile(CDocCmp *pDocCmp, const CString &strFile)
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


BOOL CDocXRead_Word::OpenDocFile(CDocFile *pFile, const CString &strFile)
{
	MSWord::Documents docs =  NULL;
	MSWord::_Document oDocSrc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);

	COleVariant vRptFile(strFile);	
	TickEnter();

	try
	{
		docs =  m_WordApp.GetDocuments();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "m_WordApp.GetDocuments error....");
		return FALSE;
	}

	try
	{
		//打开试验报告文件
		oDocSrc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
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


	try
	{
		oDocSrc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "oDocSrc.Close error....");
		return FALSE;
	}

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
void CDocXRead_Word::OpenDocFile(CDocFile *pFile, MSWord::_Document &oDoc)
{
	MSWord::Paragraphs oParagraphs = NULL;
	MSWord::Paragraph  oParagraph = NULL, oParagraphEnd = NULL;
	MSWord::Range oRange = NULL;
	MSWord::Tables oTables = NULL;
	CDocText *pText = NULL;
	CDocTable *pTable = NULL;
	COleVariant vCount((long)1);
	long nStart1, nEnd1, nStart2, nEnd2, nStart, nEnd;

	try
	{
		oParagraphs = oDoc.GetParagraphs();
		oParagraph = oParagraphs.Item(1);
		oParagraphEnd = oParagraphs.Item(oParagraphs.GetCount());
		GetParagraphPos(oParagraph, nStart1, nEnd1);
		GetParagraphPos(oParagraphEnd, nStart2, nEnd2);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "OpenDocFile error  1....");
		return;
	}


	if (m_pProgress != NULL)
	{
		m_pProgress->SetMaxRange(100);
	}

	while (oParagraph != NULL)
	{
		try
		{
			oRange = oParagraph.GetRange();
			oTables = oRange.GetTables();
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, "read file error  2 ....");
			break;
		}


		if (oTables == NULL)
		{
			pText = new CDocText();
			ReadText(pText, oRange);
			pFile->AddNewChild(pText);
			
			try
			{
				oParagraph = oParagraph.Next(vCount);
			}
			catch (...)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, "read file error 3....");
				break;
			}
		}
		else
		{
			if (oTables.GetCount() == 0)
			{
				pText = new CDocText();
				ReadText(pText, oRange);
				pFile->AddNewChild(pText);

				try
				{
					oParagraph = oParagraph.Next(vCount);
				}
				catch (...)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, "read file  error 4....");
					break;
				}
			}
			else
			{
				ReadTables(pFile, oTables, oParagraph);
				try
				{
					oParagraph = oParagraph.Next(vCount);  //表格后面都还有一个空白行
					oParagraph = oParagraph.Next(vCount); //表格后面空白行的下一行
				}
				catch (...)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, "read file error 5 ....");
					break;
				}

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


void CDocXRead_Word::ReadTables(CDocFile *pFile, MSWord::Tables &oTables, MSWord::Paragraph  &oRetParagrap)
{
	long nCount = oTables.GetCount();
	MSWord::Table oTable = NULL;
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
void CDocXRead_Word::ReadTable(CDocTable *pTable, MSWord::Table &oTable, MSWord::Paragraph  &oRetParagrap)
{
	MSWord::Rows oRows = NULL;
	MSWord::Row oRow = NULL;
	long nCount = 0;
	
	try
	{
		oRows = oTable.GetRows();
		nCount = oRows.GetCount();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "ReadTable error 1....");
		return;
	}

	
	long k = 1;
	CDocRow *pRow = NULL;

	for (k=1; k<=nCount; k++)
	{
		try
		{
			oRow = oRows.Item(k);
			pRow = new CDocRow();
			ReadRow(pRow, oRow, oRetParagrap);
			pTable->AddNewChild(pRow);
		}
		catch (...)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, "ReadTable error 2....");
		}
	}
}

void CDocXRead_Word::ReadTable_Cells(CDocTable *pTable, MSWord::Table &oTable, MSWord::Paragraph  &oRetParagrap)
{
	MSWord::Rows oRows = NULL;
	MSWord::Columns oCols = NULL;
	MSWord::Cell oCell = NULL;
	oRows = oTable.GetRows();
	oCols = oTable.GetColumns();
	long nRows = oRows.GetCount();
	long nCols = oCols.GetCount();
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

void CDocXRead_Word::ReadRow(CDocRow *pRow, MSWord::Row &oRow, MSWord::Paragraph  &oRetParagrap)
{
	try
	{
		pRow->m_fHeigh = oRow.GetHeight();
		pRow->m_fWidth = 0;
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "ReadRow error 1....");
	}

	
	MSWord::Cells oCells = NULL;
	MSWord::Cell oCell = NULL;
	long nCount = 0;
	long k = 1;
	CDocCel *pCell = NULL;

	try
	{
		oCells = oRow.GetCells();
		nCount = oCells.GetCount();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "read row error 2....");
		return;
	}


	for (k=1; k<=nCount; k++)
	{
		oCell = oCells.Item(k);
		pCell = new CDocCel();
		pRow->AddNewChild(pCell);
		ReadCel(pCell, oCell);
		pRow->m_fWidth += pCell->m_fWidth;
	}

	try
	{
		if (oCell != NULL)
		{
			MSWord::Paragraphs oParagraphs = NULL;
			MSWord::Range oRange = NULL;
			oRange = oCell.GetRange();
			oParagraphs = oRange.GetParagraphs();
			oRetParagrap = oParagraphs.Item(oParagraphs.GetCount());
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "read row error 3....");
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
void CDocXRead_Word::ReadCel(CDocCel *pCell, MSWord::Cell &oCell)
{
	try
	{
		MSWord::Range oRange = oCell.GetRange();
		ReadText(pCell ,oRange);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "read cell error 1....");
		return;
	}


	try
	{
		pCell->m_nCol = oCell.GetColumnIndex();
		pCell->m_nRow = oCell.GetRowIndex();
		pCell->m_fWidth = oCell.GetWidth();
		pCell->m_fHeight = oCell.GetHeight();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "read cell error 2....");
		return; 
	}
}


void CDocXRead_Word::ReadText(CDocText *pText, MSWord::Range &oRange)
{
	try
	{
		pText->m_strTxt = oRange.GetText();
		pText->m_nStart = oRange.GetStart();
		pText->m_nEnd = oRange.GetEnd();
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "read text error....");
	}

	pText->Init();
}

void CDocXRead_Word::GetParagraphPos(MSWord::Paragraph  &oParagraph, long &nStart, long &nEnd)
{
	MSWord::Range oRange = oParagraph.GetRange();
	nStart = oRange.GetStart();
	nEnd = oRange.GetEnd();
}

BOOL CDocXRead_Word::DocToXml(const CString &strFile)
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

