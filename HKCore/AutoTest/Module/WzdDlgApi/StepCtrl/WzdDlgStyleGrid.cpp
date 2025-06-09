#include "stdafx.h"
#include "WzdDlgStyleGrid.h"
#include "../WzdDlgDef.h"

IMPLEMENT_DYNCREATE(CWzdDlgStyleGrid, CGridCtrl)
BEGIN_MESSAGE_MAP(CWzdDlgStyleGrid, CGridCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

CWzdDlgStyleGrid::CWzdDlgStyleGrid()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
	AddNewImage(strIcon + "btn_n.png");

	m_nCurHotRow = 0;
	m_bHotLight = FALSE;
	m_crHot = RGB(255, 255, 255);
	m_pScrollGrid = NULL;

	SetGridColor(g_crLightBlue);

	m_bUseImage = TRUE;
	m_crNoImage = RGB(0, 0, 0);
	m_crArrow = RGB(240, 240, 240);
	m_crBar = RGB(205, 205, 205);
	m_crScrollBk = RGB(240, 240, 240);
}

CWzdDlgStyleGrid::~CWzdDlgStyleGrid()
{
	ClearImageList();
}

void CWzdDlgStyleGrid::InitGrid()
{

}

void CWzdDlgStyleGrid::InitGridTitle()
{

}

void CWzdDlgStyleGrid::InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols)
{
	CExBaseListGrid::InitGridTitle(pStrTitles, pnWidth, nCols);
}

void CWzdDlgStyleGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}

long CWzdDlgStyleGrid::AddNewImage(const CString& strFilePath)
{
	CImage* pImage = new CImage;
	pImage->Load(strFilePath);
	long nIndex = m_imageList.size();
	m_imageList.insert(std::pair<long, CImage*>(nIndex, pImage));
	return nIndex;
}

void CWzdDlgStyleGrid::ClearImageList()
{
	std::map<long, CImage*>::iterator itor = m_imageList.begin();
	while (itor != m_imageList.end())
	{
		if (itor->second)
		{
			CImage* pImage = (CImage*)itor->second;
			pImage->Destroy();
			delete pImage;
			itor = m_imageList.erase(itor);
		}
		else
		{
			itor++;
		}
	}
}

void CWzdDlgStyleGrid::DrawTransparent(CDC* pDC, HBITMAP hBitmap, CRect rc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(hBitmap));
	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	long Res = pDC->StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	if(pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}
	memDC.DeleteDC();
}

void CWzdDlgStyleGrid::AttachScrollGrid(CWzdDlgStyleGrid* pScrollGrid)
{
	m_pScrollGrid = pScrollGrid;
	m_pScrollGrid->AttachScrollGrid(this);
}

void CWzdDlgStyleGrid::HideColumnBorder(long nColumn)
{
	CString strColumn;
	strColumn.Format("%d", nColumn);
	if(m_oHideColumnBorder.FindByID(strColumn))
	{
		return;
	}
	m_oHideColumnBorder.AddNew(strColumn, strColumn);
}

void CWzdDlgStyleGrid::ShowColumnBorder(long nColumn)
{
	CString strColumn;
	strColumn.Format("%d", nColumn);
	if(!m_oHideColumnBorder.FindByID(strColumn))
	{
		return;
	}
	m_oHideColumnBorder.DeleteByID(strColumn);
}

void CWzdDlgStyleGrid::SetCellImage(long nRow, long nColumn, long nImageIndex)
{
	CString strID;
	strID.Format("%d-%d", nRow, nColumn);
	CWzdDlgStyleImageCell* pCellImage = (CWzdDlgStyleImageCell*)m_oCellImage.FindByID(strID);
	if(!pCellImage)
	{
		pCellImage = new CWzdDlgStyleImageCell;
		m_oCellImage.AddNewChild(pCellImage);
	}
	pCellImage->m_strID = strID;
	pCellImage->m_nRow = nRow;
	pCellImage->m_nColumn = nColumn;
	pCellImage->m_nImageIndex = nImageIndex;
}

void CWzdDlgStyleGrid::DeleteCellImage(long nRow, long nColumn)
{
	CString strID;
	strID.Format("%d-%d", nRow, nColumn);
	m_oCellImage.DeleteByID(strID);
}

void CWzdDlgStyleGrid::UseImage(BOOL bUsed, COLORREF clr)
{
	m_bUseImage = bUsed;
	m_crNoImage = clr;

	if(m_bUseImage)
	{
		SetGridColor(g_crLightBlue);
		LONG_PTR style = ::GetWindowLongPtr(m_hWnd, GWL_STYLE);  
		style = style & WS_BORDER;
		::SetWindowLongPtr(m_hWnd, GWL_STYLE, style);
	}
	else
	{
		SetGridColor(m_crNoImage);
		LONG_PTR style = ::GetWindowLongPtr(m_hWnd, GWL_STYLE);  
		style = style & ~WS_BORDER;
		::SetWindowLongPtr(m_hWnd, GWL_STYLE, style);
	}
}

void CWzdDlgStyleGrid::UseScorllBar(COLORREF clrBk, COLORREF clrArrow, COLORREF clrBar)
{
	m_crArrow = clrArrow;
	m_crBar = clrBar;
	m_crScrollBk = clrBk;
}

BOOL CWzdDlgStyleGrid::DrawFixedCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge, BOOL bEraseBk)
{
	CString strColumn;
	strColumn.Format("%d", nCol);
	if(m_oHideColumnBorder.FindByID(strColumn))
	{
		return TRUE;
	}

	CGridCell *pCell = GetCell(nRow, nCol);
	UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	CRect rcCell = rect;
	CString strText = GetItemText(nRow, nCol);

	if(m_bUseImage)
	{
		CImage* pImage = (CImage*)m_imageList.find(0)->second;
		DrawTransparent(pDC, *pImage, rcCell);
	}
	else
	{
		pDC->FillSolidRect(rcCell, m_crNoImage);
	}

	CFont* font = GetParent()->GetFont();
	pDC->SelectObject(font);
	pDC->DrawText(strText, -1, rcCell, nFormat);
	return TRUE;
}

void CWzdDlgStyleGrid::DrawBorder(CDC* pDC)
{
	CBrush Brush(RGB(255, 255, 255));
	CBrush* pOldBrush = pDC->SelectObject(&Brush);

	CRect rtWnd;
	GetWindowRect(&rtWnd);

	CPoint point;
	//填充顶部框架
	point.x = rtWnd.Width();
	point.y = GetSystemMetrics(SM_CYFRAME)+1;
	pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
	//填充左侧框架
	point.x = GetSystemMetrics(SM_CXFRAME);
	point.y = rtWnd.Height();
	pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
	//填充底部框架
	point.x = rtWnd.Width();
	point.y = GetSystemMetrics(SM_CYFRAME) + 1;
	pDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
	//填充右侧框架
	point.x = GetSystemMetrics(SM_CXFRAME);
	point.y = rtWnd.Height();
	pDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);
}

void CWzdDlgStyleGrid::DrawScrollBar()
{
	//CGridCtrl无法获取到滚动条，似乎他不是一个控件，但也没找手绘的代码
	//看起来他是存放在多重继承的CWnd中，派生类很难获取到
	CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
	if(pScrollBar)
	{
		CDC* pDC = pScrollBar->GetDC();

		CRect rc;
		pScrollBar->GetClientRect(rc);
		pDC->FillSolidRect(rc, m_crScrollBk);

		SCROLLBARINFO info;
		info.cbSize = sizeof(SCROLLBARINFO);
		pScrollBar->GetScrollBarInfo(&info);

		pDC->FillSolidRect(&info.rcScrollBar, m_crBar);

		ReleaseDC(pDC);
	}
}

BOOL CWzdDlgStyleGrid::DrawCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge, BOOL bEraseBk)
{
	//禁止在OnDraw之外更改设置了图片的Cell
	CString strCellImage;
	strCellImage.Format("%d-%d", nRow, nCol);
	if(m_oCellImage.FindByID(strCellImage))
	{
		return TRUE;
	}

	//禁止设置了隐藏列的Cell高亮
	CString strColumn;
	strColumn.Format("%d", nCol);
	COLORREF crHighLight = m_crHighLight;
	COLORREF crHighLightText = m_crHighLightText;
	if(m_oHideColumnBorder.FindByID(strColumn) )
	{
		m_crHighLight = GetBkColor();
		m_crHighLightText = GetTextColor();
	}

	BOOL bRes = CGridCtrl::DrawCell(oCells, pDC, nRow, nCol, rect, bCalMerge, bEraseBk);

	m_crHighLight = crHighLight;
	m_crHighLightText = crHighLightText;

	return bRes;
}

void CWzdDlgStyleGrid::DrawHideColumn(CDC* pDC, long nColumn)
{
	COLORREF crBk = GetBkColor();
	CGridCell* pCell = GetCell(0, nColumn);
	CRect rc = pCell->GetMergeCellRect();
	pDC->FillSolidRect(rc, crBk);

	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID , 2, crBk);
	CPen* poldPen = pDC->SelectObject(&pNewPen);

	long nWidth = GetColumnWidth(nColumn);
	long nRows = GetRowCount();
	for (int i = 1; i < nRows; i++)
	{
		pCell = GetCell(i, nColumn);
		rc = pCell->GetMergeCellRect();
		pDC->MoveTo(rc.left, rc.top);
		pDC->LineTo(rc.right, rc.top);
		pDC->MoveTo(rc.left, rc.bottom);
		pDC->LineTo(rc.right, rc.bottom);
	}

	pDC->SelectObject(poldPen);
}

void CWzdDlgStyleGrid::OnDraw(CDC* pDC)
{
	CRect rect;
	int row,col;

	CRect clipRect;
	if (GetGridClipRect(pDC, clipRect) == ERROR) return;

	EraseBkgnd(pDC);

	DrawGridLines(pDC);

	int nFixedRowHeight = GetFixedRowHeight();
	int nFixedColWidth  = GetFixedColumnWidth();

	CCellID idTopLeft = GetTopleftNonFixedCell();
	int minVisibleRow = idTopLeft.row,
		minVisibleCol = idTopLeft.col;

	CRect VisRect;
	CGridCellRange VisCellRange = GetVisibleNonFixedCellRange(VisRect);
	int maxVisibleRow = VisCellRange.GetMaxRow(),
		maxVisibleCol = VisCellRange.GetMaxCol();

	rect.bottom = nFixedRowHeight-1 + m_posTopLeft.y;
	CGridCells oCells;

	for (row = minVisibleRow; row <= maxVisibleRow; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = nFixedColWidth-1 + m_posTopLeft.x;
		for (col = minVisibleCol; col <= maxVisibleCol; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;   
			if (rect.right < clipRect.left) continue;

			if(m_nCurHotRow == row && m_bHotLight)
			{
				//画悬浮高亮
				CGridCell *pCell = GetCell(row, col);
				pCell->crBkClr = m_crHot;
				DrawCell(oCells, pDC, row, col, rect);
				pCell->crBkClr = CLR_DEFAULT;
			}
			else
			{
				DrawCell(oCells, pDC, row, col, rect);
			}
		}
	}

	oCells.RemoveAll();

	//绘制Fixed-固定行的固定列单元
	rect.bottom = -1 + m_posTopLeft.y;
	for (row = 0; row < m_nFixedRows; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;
		rect.right = m_posTopLeft.x - 1;

		for (col = 0; col < m_nFixedCols; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}

	//绘制可见行的固定列单元
	rect.bottom = nFixedRowHeight-1;
	for (row = minVisibleRow; row <= maxVisibleRow; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = -1;
		for (col = 0; col < m_nFixedCols; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;   
			if (rect.right < clipRect.left) continue;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}

	//绘制固定行的各列
	rect.bottom = m_posTopLeft.y-1;
	for (row = 0; row < m_nFixedRows; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = m_posTopLeft.x + nFixedColWidth-1;

		for (col = minVisibleCol; col <= maxVisibleCol; col++)
		{                                       
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;    
			if (rect.right < clipRect.left) continue;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}

	//绘制隐藏列的背景色
	POS pos = m_oHideColumnBorder.GetHeadPosition();
	while(pos)
	{
		CExBaseObject* pObj = (CExBaseObject*)m_oHideColumnBorder.GetNext(pos);
		long nColumn = CString_To_long(pObj->m_strID);
		DrawHideColumn(pDC, nColumn);
	}

	//画附加Cell图片
	pos = m_oCellImage.GetHeadPosition();
	while(pos)
	{
		CWzdDlgStyleImageCell* pCellImage = (CWzdDlgStyleImageCell*)m_oCellImage.GetNext(pos);
		CGridCell* pCell = GetCell(pCellImage->m_nRow, pCellImage->m_nColumn);
		if(pCell)
		{
			CRect rc = pCell->GetMergeCellRect();
			CImage* pImage = m_imageList.find(pCellImage->m_nImageIndex)->second;
			DrawTransparent(pDC, *pImage, rc);
		}
	}

	DrawScrollBar();
}

void CWzdDlgStyleGrid::OnMouseMove(UINT nFlags, CPoint point)
{
	CGridCtrl::OnMouseMove(nFlags, point);

	if(m_bHotLight)
	{
		CCellID oCellID = GetCellFromPt(point);
		if(oCellID.row > 0 && oCellID.col > 0)
		{
			m_nCurHotRow = oCellID.row;
		}
		else
		{
			m_nCurHotRow = 0;
		}

		Invalidate();
	}
}

void CWzdDlgStyleGrid::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CGridCtrl::OnLButtonDblClk(nFlags, point);
	LButtonDblClk(nFlags, point);
}

void CWzdDlgStyleGrid::OnRButtonUp(UINT nFlags, CPoint point)
{
	CGridCtrl::OnRButtonUp(nFlags, point);
	RButtonUp(nFlags, point);
}

void CWzdDlgStyleGrid::OnRButtonDown(UINT nFlags, CPoint point)
{
	CGridCtrl::OnRButtonDown(nFlags, point);
	RButtonDown(nFlags, point);
}