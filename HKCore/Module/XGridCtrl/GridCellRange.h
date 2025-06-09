// GridCellRange.h: interface for the CGridCellRange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GRIDCELL_RANGE_H__)
#define _GRIDCELL_RANGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGridCell;
class CXGridCtrlBase;


class CCellID
{    
// Attributes
public:
    int row, col;
	
// Operations
public:
    CCellID(int nRow = -1, int nCol = -1) : row(nRow), col(nCol) {}
	
    int IsValid() const { return (row >= 0 && col >= 0); }
    CCellID& operator=(const CCellID& rhs)    { row = rhs.row; col = rhs.col; return *this;  }
    int operator==(const CCellID& rhs)    { return (row == rhs.row && col == rhs.col); }
    int operator!=(const CCellID& rhs)    { return !operator==(rhs); }
};

class CGridCellRange
{ 
	friend class CXGridCtrlBase;
	friend class CGridCell;
	
public:
    CGridCellRange()
	{
		m_pGrid = NULL;
		Set();
	}
    CGridCellRange(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol)
    {
		m_pGrid = NULL;
        Set(nMinRow, nMinCol, nMaxRow, nMaxCol);
    }
	
    void Set(int nMinRow = -1, int nMinCol = -1, int nMaxRow = -1, int nMaxCol = -1);
    
    int  IsValid() const;
    int  InRange(int row, int col) const;
    int  InRange(const CCellID& cellID) const;
    int  Count() { return (m_nMaxRow - m_nMinRow + 1) * (m_nMaxCol - m_nMinCol + 1); }
    
    CCellID  GetTopLeft() const;
    CGridCellRange  Intersect(const CGridCellRange& rhs) const;
    
    int GetMinRow() const {return m_nMinRow;}
    void SetMinRow(int minRow) {m_nMinRow = minRow;}
    
    int GetMinCol() const {return m_nMinCol;}
    void SetMinCol(int minCol) {m_nMinCol = minCol;}
    
    int GetMaxRow() const {return m_nMaxRow;}
    void SetMaxRow(int maxRow) {m_nMaxRow = maxRow;}
    
    int GetMaxCol() const {return m_nMaxCol;}
    void SetMaxCol(int maxCol) {m_nMaxCol = maxCol;}
	
    int GetRowSpan() const {return m_nMaxRow - m_nMinRow + 1;}
    int GetColSpan() const {return m_nMaxCol - m_nMinCol + 1;}
    
    int  operator==(const CGridCellRange& rhs);
	int  operator!=(const CGridCellRange& rhs);
	CGridCellRange&  operator=(const CGridCellRange& rhs);
   
	void SetGridCtrl(CXGridCtrlBase *pGrid)    {    m_pGrid = pGrid;  }
	void Merge(BOOL bMerge = TRUE);
	CGridCell* TopLeft();
	CGridCell* RightBottom();
	BOOL CanMergeCells();
	
	
protected:
    int m_nMinRow;
    int m_nMinCol;
    int m_nMaxRow;
    int m_nMaxCol;
	
	CXGridCtrlBase *m_pGrid;
};

inline void CGridCellRange::Set(int minRow, int minCol, int maxRow, int maxCol)
{
	m_nMinRow = minRow;
	m_nMinCol = minCol;
	m_nMaxRow = maxRow;
	m_nMaxCol = maxCol;
}

inline int CGridCellRange::operator==(const CGridCellRange& rhs)
{
	return ((m_nMinRow == rhs.m_nMinRow) && (m_nMinCol == rhs.m_nMinCol) &&
		(m_nMaxRow == rhs.m_nMaxRow) && (m_nMaxCol == rhs.m_nMaxCol));
}

inline int CGridCellRange::operator!=(const CGridCellRange& rhs)
{
	return !operator==(rhs);
}

inline CGridCellRange&  CGridCellRange::operator=(const CGridCellRange& rhs)
{
	m_nMinRow = rhs.m_nMinRow;
	m_nMinCol = rhs.m_nMinCol;
	m_nMaxRow = rhs.m_nMaxRow;
	m_nMaxCol = rhs.m_nMaxCol;
	m_pGrid   = rhs.m_pGrid;

	return *this;
}

inline int CGridCellRange::IsValid() const
{
	return (m_nMinRow >= 0 && m_nMinCol >= 0 && m_nMaxRow >= 0 && m_nMaxCol >= 0 &&
		m_nMinRow <= m_nMaxRow && m_nMinCol <= m_nMaxCol);
}

inline int CGridCellRange::InRange(int row, int col) const
{
	return (row >= m_nMinRow && row <= m_nMaxRow && col >= m_nMinCol && col <= m_nMaxCol);
}

inline int CGridCellRange::InRange(const CCellID& cellID) const
{
	return InRange(cellID.row, cellID.col);
}

inline CCellID CGridCellRange::GetTopLeft() const
{
	return CCellID(m_nMinRow, m_nMinCol);
}

inline CGridCellRange CGridCellRange::Intersect(const CGridCellRange& rhs) const
{
	return CGridCellRange(max(m_nMinRow,rhs.m_nMinRow), max(m_nMinCol,rhs.m_nMinCol),
		min(m_nMaxRow,rhs.m_nMaxRow), min(m_nMaxCol,rhs.m_nMaxCol));
}

#endif // !defined(_GRIDCELL_RANGE_H__)
