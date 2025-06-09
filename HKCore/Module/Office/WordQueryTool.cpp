// WordQueryTool.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordQueryTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CWordStrings::CWordStrings(long nStart, long nEnd)
{
	SetStringPos(nStart, nEnd);
}

CWordStrings::CWordStrings()
{
	m_nStart = -1;
	m_nEnd = -1;
}

CWordStrings::~CWordStrings()
{
	
}

void CWordStrings::GetStringBuffer(MSWord::_Document &doc, CBufferBase &oBuffer)
{

}

//////////////////////////////////////////////////////////////////////////
//CWordTable
CWordTable::CWordTable()
{
	SetTableIndex(-1);
}

CWordTable::CWordTable(long nTableIndex)
{
	SetTableIndex(nTableIndex);
}

CWordTable::~CWordTable()
{

}

//////////////////////////////////////////////////////////////////////////
//CWordDocQueryTool

CWordDocQueryTool::CWordDocQueryTool(MSWord::_Document &oDoc)
{
	DocQuery(oDoc);
}

CWordDocQueryTool::CWordDocQueryTool()
{
	
}

CWordDocQueryTool::~CWordDocQueryTool()
{
	m_oDoc = NULL;
}

BOOL CWordDocQueryTool::DocQuery(MSWord::_Document &oDoc)
{
	m_oDoc = oDoc;
	MSWord::Tables oTables = NULL;
	MSWord::Table  oTable = NULL;
	long nIndex = 1;
	long nCount = 0;
	MSWord::Range oRange = NULL;
	BOOL bTrue = TRUE;
	
	try
	{
		oTables = m_oDoc.GetTables();
		nCount = oTables.GetCount();
		long nStart = 0;
		long nEnd = 0;
		long nTableStart = 0;
		long nTableEnd = 0;

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oTable = oTables.Item(nIndex);
			oRange = oTable.GetRange();
			nTableStart = oRange.GetStart();
			nTableEnd = oRange.GetEnd();

			if (nEnd != nTableStart)
			{
				CWordStrings *pWordStrings = CreateWordStrings(nEnd, nTableStart-1);
			}

			CWordTable *pTable = CreateWordTable(nIndex);

			nEnd = nTableEnd;
		}

		MSWord::_Application oApp = oDoc.GetApplication();
		MSWord::Selection oSelection = oApp.GetSelection();

		COleVariant vUnit((long)MSWord::wdStory);
		COleVariant vCount((long)1);
		COleVariant vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		oSelection.EndKey(&vUnit, &vCount);
		nEnd = oSelection.GetEnd();

		if (nEnd != nTableEnd)
		{
			CWordStrings *pWordStrings = CreateWordStrings(nTableEnd, nEnd);
		}
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}

CWordStrings* CWordDocQueryTool::CreateWordStrings(long nStart, long nEnd)
{
	CWordStrings *pWordStrings = new CWordStrings(nStart, nEnd);
	AddNewChild(pWordStrings);
	return pWordStrings;
}

CWordTable* CWordDocQueryTool::CreateWordTable(long nIndex)
{
	CWordTable *pTable = new CWordTable(nIndex);
	AddNewChild(pTable);
	return pTable;
}

