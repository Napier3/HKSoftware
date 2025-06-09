#include "StdAfx.h"
#include "StesFileWordTool.h"
#include "..\..\XLanguageResourceAts.h"

CStesFileWordTool::CStesFileWordTool(void)
{
	m_pWordAppBase = NULL;
	m_pWordDocBase = NULL;
}

CStesFileWordTool::~CStesFileWordTool(void)
{
	ReleaseWord();
}

void CStesFileWordTool::CreateWordBaseApp(LPDISPATCH lpDispatch)
{
	if (m_pWordAppBase != NULL)
	{
		return;
	}

	MSWord::_Application oWordApp = NULL;

	if (lpDispatch == NULL)
	{
		m_pWordAppBase = new CWordAppBase();
		oWordApp = m_pWordAppBase->GetWordApp(FALSE);
	}
	else
	{
		oWordApp = lpDispatch;
		m_pWordAppBase = new CWordAppBase(oWordApp);
	}
}

void CStesFileWordTool::ReleaseWord()
{
	if (m_pWordDocBase != NULL)
	{
		m_pWordDocBase->Close(1);
		delete m_pWordDocBase;
		m_pWordDocBase = NULL;
	}

	if (m_pWordAppBase != NULL)
	{
		m_pWordAppBase->CloseWordApplication();
		delete m_pWordAppBase;
		m_pWordAppBase = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//export functions
BOOL CStesFileWordTool::ExportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	CreateWordBaseApp(lpDispatch);
	ASSERT (m_pWordAppBase != NULL);

	MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();
	ASSERT (oWordApp != NULL);

	m_pWordDocBase = new CWordDocBase(oWordApp);
	oWordApp.SetVisible(TRUE);

	if (!m_pWordDocBase->New(strFile))
	{
		return FALSE;
	}

	ExportSets();
	m_pWordDocBase->Save();

	ReleaseWord();

	return TRUE;
}

void CStesFileWordTool::ExportSets()
{
	ExportTitle();

// 	CSysParaEditGroups *pGroups = (CSysParaEditGroups*)m_pRefObject;
// 	POS pos = pGroups->GetHeadPosition();
// 	CSysParaEditGroup *pGroup = NULL;
// 	BOOL bAddGroupTitle = (pGroups->GetCount() > 1);
// 
// 	while (pos != NULL)
// 	{
// 		pGroup = (CSysParaEditGroup *)pGroups->GetNext(pos);
// 		ExportGroup(pGroup, bAddGroupTitle);
// 	}
}

void CStesFileWordTool::ExportTitle()
{
	MSWord::_Document doc = m_pWordDocBase->GetDoc();
	MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();

	CString strTitle;
	strTitle.Format(g_sLangTxt_FixedValueData/*_T("%s(%s)定值单数据")*/, m_pRefObject->m_strName, m_pRefObject->m_strID);
	
	try
	{
		//如果覆盖，则删除文档内容
		doc.Activate();
		MSWord::Selection oSelection = oWordApp.GetSelection();
		oSelection.WholeStory();
		COleVariant vUnit((long)MSWord::wdCharacter);
		COleVariant vCount((long)1);
		oSelection.Delete(&vUnit, &vCount);
		oSelection.TypeText(_bstr_t(strTitle));
	}
	catch (...)
	{
		
	}
}
// 
// void CStesFileWordTool::ExportGroup(CSysParaEditGroup *pGroup, BOOL bAddTitle)
// {
// 	ExportGroupTitle(pGroup, bAddTitle);
// 	MSWord::_Document doc = m_pWordDocBase->GetDoc();
// 	MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();
// 
// 	try
// 	{
// 		doc.Activate();
// 		MSWord::Selection oSelection = oWordApp.GetSelection();
// 		oSelection.TypeParagraph();
// 
// 		long nRows = pGroup->GetCount() + 1;
// 		long nCols = 5;
// 
// 		COleVariant vDefaultTable((long)MSWord::wdWord9TableBehavior);
// 		COleVariant vAutoFit((long)MSWord::wdAutoFitFixed);
// 
// 		MSWord::Tables oTables = doc.GetTables();
// 		MSWord::Table  oTable  = oTables.Add(oSelection.GetRange(), nRows, nCols, &vDefaultTable, &vAutoFit);
// 		MSWord::Rows oRows = oTable.GetRows();
// 		MSWord::Row  oRow  = NULL;
// 		long nIndex = 1;
// 		POS pos = pGroup->GetHeadPosition();
// 		CSet *pSet = NULL;
// 
// 		ExportTableTitle(oTable);
// 		nIndex++;
// 
// 		while (pos != NULL)
// 		{
// 			pSet = (CSet *)pGroup->GetNext(pos);
// 			oRow = oRows.Item(nIndex);
// 			ExportSet(pSet, oRow, nIndex);
// 			nIndex++;
// 		}
// 	}
// 	catch(...)
// 	{
// 
// 	}
// }
// 
// void CStesFileWordTool::ExportGroupTitle(CSysParaEditGroup *pGroup, BOOL bAddTitle)
// {
// 	MSWord::_Document doc = m_pWordDocBase->GetDoc();
// 	MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();
// 
// 	try
// 	{
// 		doc.Activate();
// 		MSWord::Selection oSelection = oWordApp.GetSelection();
// 		oSelection.TypeParagraph();
// 
// 		if (bAddTitle)
// 		{
// 			CString strTitle;
// 			strTitle.Format(_T("%s(%s)定值单数据"), pGroup->m_strName, pGroup->m_strID);
// 			oSelection.TypeParagraph();
// 			oSelection.TypeText(_bstr_t(strTitle));
// 		}
// 	}
// 	catch (...)
// 	{
// 		
// 	}
// }

void CStesFileWordTool::ExportTableTitle(MSWord::Table  oTable)
{
	try
	{
		MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();
		MSWord::Selection oSelection = oWordApp.GetSelection();
		MSWord::Columns oCols = oTable.GetColumns();
		MSWord::Rows oRows = oTable.GetRows();
		MSWord::Row oRow = oRows.Item(1);
		MSWord::Cells oCells = oRow.GetCells();
		MSWord::Cell oCell = NULL;
		long nIndex = 0;

		//Index 30   name(65%)  ID(35%) value(60) Unit(30)
		_bstr_t abstr[5] = {g_sLangTxt_Index/*L"编号"*/, g_sLangTxt_Name/*L"名称"*/, g_sLangTxt_Marking/*L"标示"*/, g_sLangTxt_Value/*L"数值"*/, g_sLangTxt_Unit/*L"单位"*/};
		float fColWidth[5] = {50, 0, 0, 80, 50};
		float fWidth = 0;

		for (nIndex=1; nIndex<=5; nIndex++)
		{
			MSWord::Column oCol = oCols.Item(nIndex);
			fWidth += oCol.GetWidth();
		}

		fWidth = fWidth - fColWidth[0] - fColWidth[3] - fColWidth[4];
		fColWidth[1] = fWidth * 0.65f;
		fColWidth[2] = fWidth - fColWidth[1];

		for (nIndex=1; nIndex<=5; nIndex++)
		{
			MSWord::Column oCol = oCols.Item(nIndex);
			oCol.SetWidth(fColWidth[nIndex-1]);
			oCell = oCells.Item(nIndex);
			oCell.Select();
			oSelection.TypeText(abstr[nIndex-1]);
		}
	}
	catch(...)
	{

	}

}
// 
// void CStesFileWordTool::ExportSet(CSet *pSet, MSWord::Row &oRow, long nRow)
// {
// 	MSWord::_Application oWordApp = m_pWordAppBase->GetWordApp();
// 
// 	try
// 	{
// 		MSWord::Selection oSelection = oWordApp.GetSelection();
// 		MSWord::Cells oCells = oRow.GetCells();
// 		MSWord::Cell oCell = NULL;
// 		long nCol = 1;
// 
// 		CString strIndex;
// 		strIndex.Format(_T("%d"), nRow-1);
// 		oCell = oCells.Item(nCol++);
// 		oCell.Select();
// 		oSelection.TypeText(_bstr_t(strIndex));
// 		
// 		oCell = oCells.Item(nCol++);
// 		oCell.Select();
// 		oSelection.TypeText(_bstr_t(pSet->m_strName));
// 
// 		oCell = oCells.Item(nCol++);
// 		oCell.Select();
// 		oSelection.TypeText(_bstr_t(pSet->m_strID));
// 
// 		oCell = oCells.Item(nCol++);
// 		oCell.Select();
// 		oSelection.TypeText(_bstr_t(pSet->m_strValue));
// 
// 		oCell = oCells.Item(nCol++);
// 		oCell.Select();
// 		oSelection.TypeText(_bstr_t(pSet->m_strUnit));
// 	}
// 	catch(...)
// 	{
// 
// 	}
// }

//////////////////////////////////////////////////////////////////////////
//import files
BOOL CStesFileWordTool::ImportFile(const CString &strFile, LPDISPATCH lpDispatch)
{
	return FALSE;
}

