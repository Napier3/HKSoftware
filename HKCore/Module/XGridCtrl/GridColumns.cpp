// GridColumns.cpp: implementation of the CGridColumns class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellRange.h"
#include "GridColumns.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridColumn::CGridColumn(CXGridCtrlBase *pGrid)
{
	m_nColumn = -1;
	m_nWidth  = 0;
	m_pGrid = pGrid;
}

CGridColumn::~CGridColumn()
{
	RemoveAll();
}

void CGridColumn::SetColumnType(UINT nType)
{
	CGridCell *pCell = NULL;
	int nRow = 0;
	int nRows = GetSize();

	for (nRow=0; nRow<nRows; nRow++)
	{
		pCell = GetAt(nRow);
		pCell->nDataType = nType;
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridColumns::CGridColumns()
{
	m_pRows = NULL;
}

CGridColumns::~CGridColumns()
{
	DeleteAll();
}

void CGridColumns::SetRowCount(int nRows)
{
	int nCols = GetSize();
	int nCol = 0;
	CGridColumn *pCol = NULL;

	for (nCol = 0; nCol <nCols; nCol++)
	{
		pCol = GetAt(nCol);
		pCol->SetSize(nRows);
	}
}

void CGridColumns::DeleteAll()
{
	int nCols = GetSize();
	int nCol = 0;
	CGridColumn *pCol = NULL;
	
	for (nCol = 0; nCol <nCols; nCol++)
	{
		pCol = GetAt(nCol);
		delete pCol;
	}

	RemoveAll();
}

void CGridColumns::UpdateColsIndex()
{
	int nCol = 0;
	int nCols = GetSize();
	CGridColumn *pCol = NULL;
	
	for (nCol=0; nCol<nCols; nCol++)
	{
		pCol = GetAt(nCol);
		pCol->m_nColumn = nCol;
	}
}
