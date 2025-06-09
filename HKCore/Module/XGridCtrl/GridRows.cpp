// GridRows.cpp: implementation of the CGridRows class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellRange.h"
#include "GridRows.h"
#include "GridCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGridRow::CGridRow(CXGridCtrlBase *pGid)
{
	m_pRows     = NULL;
	m_pGridCtrl = pGid;
	m_pParent   = NULL;
	m_nRow		= 0;
	m_nRowHeight = 15;

}

CGridRow::~CGridRow()
{
	DeleteAllCells();
}

void CGridRow::DeleteAllCells()
{
	ASSERT (m_pGridCtrl != NULL);
	int nCols = GetSize();
	
	for (int col = 0; col < nCols; col++)
	{
		CGridCell* pCell = GetAt(col);
		
		if (pCell) 
		{
			m_pGridCtrl->EmptyCell(pCell, m_nRow, col);  // TODO - this is a bit of a performance hit.
			delete pCell;                // better to call m_SelectedCells.RemoveAll()
		}                                // instead. This is safer for changes though.
	}
	RemoveAll();
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridRows::CGridRows()
{
	m_pGrid = NULL;
}

CGridRows::~CGridRows()
{
	
}

int CGridRows::InsertRow(LPCTSTR strHeading, int nRow)
{
   return 0;
}

void CGridRows::UpdateRowsIndex()
{
	int nRow = 0;
	int nRows = GetSize();
	CGridRow *pRow = NULL;

	for (nRow=0; nRow<nRows; nRow++)
	{
		pRow = GetAt(nRow);
		pRow->m_nRow = nRow;
	}
}

void CGridRows::SetRowHeight(int nRow, int nHeight)
{
	CGridRow *pRow = GetAt(nRow);
	
	if (pRow != NULL)
	{
		pRow->m_nRowHeight = nHeight;
	}
}

int CGridRows::GetRowHeight(int nRow) const
{
	CGridRow *pRow = GetAt(nRow);
	
	if (pRow != NULL)
	{
		return pRow->m_nRowHeight;
	}
	else
	{
		return 0;
	}
}

