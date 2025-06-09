// GridCellRange.cpp: implementation of the CGridCellRange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCell.h"
#include "GridCellRange.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CGridCellRange::Merge(BOOL bMerge)
{
	if (!CanMergeCells())
	{
		return;
	}
	
	CGridCell *pCell = NULL;
	CGridCell *pMergeTo = m_pGrid->GetCell(m_nMinRow, m_nMinCol);
	int nRow = 0;
	int nCol = 0;

	for (nRow = m_nMinRow; nRow <= m_nMaxRow; nRow++)
	{
		for (nCol=m_nMinCol; nCol<= m_nMaxCol; nCol++)
		{
			pCell = m_pGrid->GetCell(nRow, nCol);
			pCell->m_pMergeTo = pMergeTo;
		}
	}
}

CGridCell* CGridCellRange::TopLeft()
{
	ASSERT (m_pGrid != NULL);
	return m_pGrid->GetCell(m_nMinRow, m_nMinCol);
}

CGridCell* CGridCellRange::RightBottom()
{
	ASSERT (m_pGrid != NULL);
	return m_pGrid->GetCell(m_nMaxRow, m_nMaxCol);
}

BOOL CGridCellRange::CanMergeCells()
{
	CGridCell *pCell = NULL;
	int nRow = 0;
	int nCol = 0;
	BOOL bTrue = TRUE;
	
	for (nRow = m_nMinRow; nRow <= m_nMaxRow; nRow++)
	{
		for (nCol=m_nMinCol; nCol<= m_nMaxCol; nCol++)
		{
			pCell = m_pGrid->GetCell(nRow, nCol);
			if (pCell->m_pMergeTo != NULL)
			{
				bTrue = FALSE;
				break;
			}
		}
	}
	
	return bTrue;
}