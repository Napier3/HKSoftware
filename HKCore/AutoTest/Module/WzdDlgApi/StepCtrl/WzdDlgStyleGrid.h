#pragma once

#include "../../../../Module/GridBase/ExBaseListGrid.h"
#include <map>

class CWzdDlgStyleImageCell : public CExBaseList
{
public:
	long m_nRow;
	long m_nColumn;
	long m_nImageIndex;

public:
	CWzdDlgStyleImageCell() 
	{
		m_nRow = 0;
		m_nColumn = 0;
		m_nImageIndex = 0;
	}
	virtual ~CWzdDlgStyleImageCell() {}
};

class CWzdDlgStyleGrid : public CExBaseListGrid
{
	DECLARE_DYNCREATE(CWzdDlgStyleGrid)
public:
	CWzdDlgStyleGrid();
	virtual ~CWzdDlgStyleGrid();

private:
	long m_nCurHotRow;//当前悬浮行
	BOOL m_bHotLight;//悬浮高亮
	COLORREF m_crHot;
	std::map<long, CImage*> m_imageList;//CImageList容易内存泄漏,所以使用map管理

	CWzdDlgStyleGrid* m_pScrollGrid;
	CExBaseList m_oHideColumnBorder;
	CExBaseList m_oCellImage;

	BOOL m_bUseImage;	//默认使用图片模式
	COLORREF m_crNoImage;//没有图片的情况下颜色
	COLORREF m_crArrow;
	COLORREF m_crBar;
	COLORREF m_crScrollBk;

protected:
	virtual void DrawHideColumn(CDC* pDC, long nColumn);
	virtual BOOL DrawCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	virtual BOOL DrawFixedCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	virtual void DrawBorder(CDC* pDC);
	virtual void DrawScrollBar();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual long AddNewImage(const CString& strFilePath);
	virtual void ClearImageList();
	//virtual BOOL DrawFixedfCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge = TRUE, BOOL bEraseBk = FALSE);
	virtual void DrawTransparent(CDC* pDC, HBITMAP hBitmap, CRect rc);

	virtual void LButtonDblClk(UINT nFlags, CPoint point){}
	virtual void RButtonUp(UINT nFlags, CPoint point){}
	virtual void RButtonDown(UINT nFlags, CPoint point){}

	virtual void AttachScrollGrid(CWzdDlgStyleGrid* pScrollGrid);
	virtual void HideColumnBorder(long nColumn);
	virtual void ShowColumnBorder(long nColumn);
	virtual void SetCellImage(long nRow, long nColumn, long nImageIndex);
	virtual void DeleteCellImage(long nRow, long nColumn);

	virtual void UseImage(BOOL bUsed, COLORREF clr);
	virtual void UseScorllBar(COLORREF clrBk, COLORREF clrArrow, COLORREF clrBar);

public:
	virtual void OnDraw(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};