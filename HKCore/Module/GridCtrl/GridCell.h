// GridCell.h: interface for the CGridCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELL_H__52B0FD8A_BCCC_4990_94A6_2AE6422EF418__INCLUDED_)
#define AFX_GRIDCELL_H__52B0FD8A_BCCC_4990_94A6_2AE6422EF418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridDefine.h"

class CGridCellRange;
class CGridRow;
class CGridColumn;
class CXGridCtrlBase;

// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.


class CGridCell : public CObject
{
public:
    CGridCell(int row, int col) 
    {
        state = 0;
        nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
        szText.Empty();
        iImage = -1;
        lParam = 0;
		crBkClr = CLR_DEFAULT;
		crFgClr = CLR_DEFAULT;
		m_pRow    = NULL;
		m_pColumn = NULL;
		m_pMergeTo = NULL;
		dwValue = 0;
		lParam = 0;
		nDataType = 0;
		pEditFunc = NULL;
		iMaxLen = 0;
		m_pStrCmpBlocks=NULL;
	}
	
    DWORD    state;       // Cell state (selected/focus etc)
    UINT     nFormat;     // Cell format
    CString  szText;      // Cell text (or binary data if you wish...)
    CStringCmpBlocks *m_pStrCmpBlocks;
    int      iImage;      // Index of the list view item’s icon 
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item
    LOGFONT  lfFont;      // Cell font
	UINT     nDataType;   //data type
	DWORD    dwValue;     //value ref
	int      iMaxLen;
	GRID_CELL_EDIT_FUNC *pEditFunc;

	CGridRow *m_pRow;
	CGridColumn *m_pColumn;
	CGridCell *m_pMergeTo;
	
public:
	virtual BOOL DrawCell(CDC *pDC, CRect rect, CXGridCtrlBase *pGrid, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	//virtual BOOL RedrawCell(CDC* pDC, CRect rect);
	virtual BOOL DrawFixedCell(CDC* pDC, CRect rect, CXGridCtrlBase *pGrid, int nRow, int nCol, BOOL bCalMerge = TRUE, BOOL bEraseBk=FALSE);
	void EmptyCell();
	void SetItemState(UINT state);
	void GetRowCol(int &row, int &col);
	void UnMerge();
	CRect GetMergeCellRect(const CRect &rcCell);
	CRect GetMergeCellRect();
	BOOL IsMergeCell()   {      return (m_pMergeTo != NULL);     }
	BOOL GetCellID(int &nRow, int &nCol);
	void GetCellRange(CGridCellRange &oCellRange);

	BOOL IsReadOnly()    {    return ((state & GVIS_READONLY) == GVIS_READONLY);  }
	BOOL IsStatic()      {    return ((state & GVIS_STATIC) == GVIS_STATIC);      }
	void SetReadOnly(BOOL bReadOnly)
	{
		if (bReadOnly)
		{
			state |= GVIS_READONLY;
		}
		else
		{
			state &= (~GVIS_READONLY);
		}
	}

private:
}; 

void Grid_DrawCheckBox(CDC*pDC,BOOL bCheck,CRect rect);
void Grid_DrawCheckBoxRect(long xCenter,long yCenter,long nCheckState,CDC *pDC,BOOL bEnable);

// storage typedef for each row in the grid
typedef CTypedPtrArray<CObArray, CGridCell*> GRID_CELLS;

class CGridCells : public GRID_CELLS
{
public:
	CGridCells();
	virtual ~CGridCells();

	int FindIndex(CGridCell *pCell);
	
};


#endif // !defined(AFX_GRIDCELL_H__52B0FD8A_BCCC_4990_94A6_2AE6422EF418__INCLUDED_)
