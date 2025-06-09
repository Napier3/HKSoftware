// GridColumns.h: interface for the CGridColumns class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCOLUMNS_H__202D442B_8232_4D8B_999D_51E8028027A9__INCLUDED_)
#define AFX_GRIDCOLUMNS_H__202D442B_8232_4D8B_999D_51E8028027A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class CGridRow;
class CGridRows;
class CXGridCtrlBase;

class CGridColumn : public CGridCells
{
public:
	CGridColumn(CXGridCtrlBase *pGrid);
	virtual ~CGridColumn();

	int m_nWidth;
	int m_nColumn;

	CXGridCtrlBase *m_pGrid;

public:
	void SetColumnType(UINT nType);
	
private:
	CGridColumn() {    }
};

typedef CTypedPtrArray<CObArray, CGridColumn*> GRID_COLUMNS;

class CGridColumns : public GRID_COLUMNS
{
public:
	CGridColumns();
	virtual ~CGridColumns();

	CGridRows *m_pRows;

public:
	void SetRowCount(int nRows);
	void DeleteAll();
	void UpdateColsIndex();

};



#endif // !defined(AFX_GRIDCOLUMNS_H__202D442B_8232_4D8B_999D_51E8028027A9__INCLUDED_)
