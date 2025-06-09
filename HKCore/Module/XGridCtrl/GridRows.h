// GridRows.h: interface for the CGridRows class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDROWS_H__5217F72C_4BEE_4C64_ACD8_1634C3B69483__INCLUDED_)
#define AFX_GRIDROWS_H__5217F72C_4BEE_4C64_ACD8_1634C3B69483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class CGridColumn;
class CGridColumns;
class CGridRows;

class CGridRow : public CGridCells
{
public:
	CGridRow(CXGridCtrlBase *pGid);
	virtual ~CGridRow();
	
	int m_nRow;
	int m_nRowHeight;
	CXGridCtrlBase *m_pGridCtrl;
	CGridRow *m_pParent;
	CGridRows *m_pRows;

public:
	void DeleteAllCells();

private:
	CGridRow(){};	
};

typedef CTypedPtrArray<CObArray, CGridRow*> GRID_ROWS;

class CGridRows : public GRID_ROWS
{
public:
	CGridRows();
	virtual ~CGridRows();

	CXGridCtrlBase *m_pGrid;

public:
    int InsertRow(LPCTSTR strHeading, int nRow = -1);
	int GetRowCount()   {    return GetSize();    }
	void UpdateRowsIndex();
	void SetRowHeight(int nRow, int nHeight);
	int GetRowHeight(int nRow) const;
};

#endif // !defined(AFX_GRIDROWS_H__5217F72C_4BEE_4C64_ACD8_1634C3B69483__INCLUDED_)
