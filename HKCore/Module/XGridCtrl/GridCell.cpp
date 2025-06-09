// GridCell.cpp: implementation of the CGridCell class.
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


BOOL CGridCell::DrawCell(CDC *pDC, CRect rect, CXGridCtrlBase *pGrid, BOOL bCalMerge, BOOL bEraseBk)
{
//	if (!CellRange.IsValid())
	CRect rcCell = rect;

	if (m_pMergeTo != NULL)
	{
		if (m_pMergeTo == this)
		{
			if (bCalMerge)
			{
				rcCell = GetMergeCellRect(rect);
			}
		}
		else
		{
			return FALSE;
		}
	}

	if (!pGrid->m_bAllowDraw)
	{
		return FALSE;
	}

	rcCell.DeflateRect(0, 0, 1, 1);
	
    COLORREF TextBkClr = (crBkClr == CLR_DEFAULT)? pGrid->GetTextBkColor() : crBkClr;
    COLORREF TextClr   = (crFgClr == CLR_DEFAULT)? pGrid->GetTextColor() : crFgClr;

    // Force redraw of background if custom colour
    if (TextBkClr != CLR_DEFAULT)
        bEraseBk = TRUE;

    int nSavedDC = pDC->SaveDC();

    pDC->SetBkMode(TRANSPARENT);

    if (state & GVIS_FOCUSED && !pDC->IsPrinting()) 
    {
		if (pGrid->m_bDrawSelCellFrame)
		{
			rcCell.right++; 
			rcCell.bottom++;    // FillRect doesn't draw RHS or bottom

			if (bEraseBk) 
			{
				CBrush brush(TextBkClr);
				pDC->FillRect(rcCell, &brush);
			}

			rcCell.right--; 
			rcCell.bottom--;    
			pDC->SelectStockObject(BLACK_PEN);
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(rcCell);
			pDC->SetTextColor(TextClr);
		}
  
		//rcCell.DeflateRect(1,1);
		rcCell.right++; 
		rcCell.bottom++;    // FillRect doesn't draw RHS or bottom
        pDC->FillSolidRect(rcCell, ::GetSysColor(COLOR_HIGHLIGHT));
        rcCell.right--; 
		rcCell.bottom--;
		
    }
    else if (state & GVIS_SELECTED && !pDC->IsPrinting()) 
    {
        rcCell.right++; 
		rcCell.bottom++;    // FillRect doesn't draw RHS or bottom
        pDC->FillSolidRect(rcCell, ::GetSysColor(COLOR_HIGHLIGHT));
        rcCell.right--; 
		rcCell.bottom--;
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    } 
	else
	{
        rcCell.right++; 
		rcCell.bottom++;    // FillRect doesn't draw RHS or bottom

        if (bEraseBk) 
        {
            CBrush brush(TextBkClr);
            pDC->FillRect(rcCell, &brush);
        }

        rcCell.right--;
		rcCell.bottom--;
        pDC->SetTextColor(TextClr);
    }

    if (state & GVIS_DROPHILITED && !pDC->IsPrinting())
	{
        pDC->SelectStockObject(BLACK_PEN);
        pDC->SelectStockObject(NULL_BRUSH);
        pDC->Rectangle(rcCell);
    }

    // Create the appropriate font and select into DC
    CFont Font;
	Font.CreateFontIndirect(&lfFont);
    CFont* pOldFont = pDC->SelectObject(&Font);
    
    pDC->SelectObject(&Font);
    rcCell.DeflateRect(pGrid->m_nMargin, 0);
	CImageList *pImageList = pGrid->m_pImageList;

    if (pImageList && iImage >= 0) 
	{
        IMAGEINFO Info;
        if (pImageList->GetImageInfo(iImage, &Info))
		{
            int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
            pImageList->Draw(pDC, iImage, rcCell.TopLeft(), ILD_NORMAL);
            rcCell.left += nImageWidth + pGrid->m_nMargin;
        }
    }

    if(nDataType == GVET_CHECKBOX)
	{
		long nOffset = rcCell.Width() - 16;
		nOffset /= 2;
		rcCell.left += nOffset;
		Grid_DrawCheckBox(pDC, dwValue, rcCell);
//		TRACE(_T("DrawCheckBox(%d, %d, %d, %d) = %d\n"), rcCell.left, rcCell.top, rcCell.right, rcCell.bottom, dwValue);
		rcCell.left += 16;
	}

	if (nDataType == GVET_COMBO_CHECKBOX)
	{
		int nCount = nFormat;
		BOOL bValue = dwValue;
		for (int i = 0; i < nFormat; i++)
		{
			Grid_DrawCheckBox(pDC, bValue & 0x1, rcCell);
			bValue = bValue >> 1;
			rcCell.left += 16;
		}
	}
	
	if ( (nDataType != GVET_CHECKBOX) && (nDataType != GVET_COMBO_CHECKBOX) )
	{
		if (m_pStrCmpBlocks == NULL)
		{
			DrawText(pDC->m_hDC, szText, -1, rcCell, nFormat);
		}
		else
		{
			//DrawText(pDC->m_hDC, *m_pStrCmpBlocks->m_pStringRef, -1, rcCell, nFormat);
			m_pStrCmpBlocks->Draw(pDC, rcCell);
		}
	}

    pDC->RestoreDC(nSavedDC);

	return TRUE;
}

BOOL CGridCell::DrawFixedCell(CDC* pDC, CRect rect, CXGridCtrlBase *pGrid, int nRow, int nCol, BOOL bCalMerge, BOOL bEraseBk)
{
	CRect rcCell = rect;
	
	if (m_pMergeTo != NULL)
	{
		if (m_pMergeTo == this)
		{
			if (bCalMerge)
			{
				rcCell = GetMergeCellRect(rect);
			}
		}
		else
		{
			return FALSE;
		}
	}
	
	if (!pGrid->m_bAllowDraw) return FALSE;
	
    if (crBkClr != CLR_DEFAULT)
        bEraseBk = TRUE;
	
    if (!pDC->IsPrinting() && bEraseBk)
    {
        CBrush brush((crBkClr == CLR_DEFAULT)? pGrid->GetFixedBkColor() : crBkClr);
        pDC->FillRect(rcCell, &brush);
    }
    pDC->SetTextColor((crFgClr == CLR_DEFAULT)? pGrid->GetFixedTextColor() : crFgClr);
    
    int nSavedDC = pDC->SaveDC();
    
    // Create the appropriate font and select into DC
    LOGFONT lf;
	memcpy(&lf, &lfFont, sizeof(LOGFONT));

	CGridCell *pFocus = NULL;
    CCellID FocusCell = pGrid->GetFocusCell();

    if ( (FocusCell.col == nCol) || (FocusCell.row == nRow) )
        lf.lfWeight = SELECTED_CELL_FONT_WEIGHT;
    
    CFont Font;
    Font.CreateFontIndirect(&lfFont);
    pDC->SelectObject(&Font);
	
    if (pGrid->IsValid(FocusCell) &&  (FocusCell.row == nRow || FocusCell.col == nCol))
    {
        rcCell.right++; 
		rcCell.bottom++;
        pDC->DrawEdge(rcCell, EDGE_RAISED, BF_RECT);
        rcCell.DeflateRect(1,1);
    }
    else
    {
        CPen lightpen(PS_SOLID, 1,  ::GetSysColor(COLOR_3DHIGHLIGHT)),
			darkpen(PS_SOLID,  1, ::GetSysColor(COLOR_3DDKSHADOW)),
			*pOldPen = pDC->GetCurrentPen();
		
        pDC->SelectObject(&lightpen);
        pDC->MoveTo(rcCell.right, rcCell.top);
        pDC->LineTo(rcCell.left, rcCell.top);
        pDC->LineTo(rcCell.left, rcCell.bottom);
		
        pDC->SelectObject(&darkpen);
        pDC->MoveTo(rcCell.right, rcCell.top);
        pDC->LineTo(rcCell.right, rcCell.bottom);
        pDC->LineTo(rcCell.left, rcCell.bottom);
		
        pDC->SelectObject(pOldPen);
        rcCell.DeflateRect(1,1);
    }
	
    pDC->SetBkMode(TRANSPARENT);
    rcCell.DeflateRect(pGrid->m_nMargin, 0);
	
    if (pGrid->m_pImageList && iImage >= 0) {
        IMAGEINFO Info;
        if (pGrid->m_pImageList->GetImageInfo(iImage, &Info)) {
            int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
            pGrid->m_pImageList->Draw(pDC, iImage, rcCell.TopLeft(), ILD_NORMAL);
            rcCell.left += nImageWidth+pGrid->m_nMargin;
        }
    }
	
    DrawText(pDC->m_hDC, szText, -1, rcCell, nFormat);
	
    pDC->RestoreDC(nSavedDC);

	return TRUE;
}

void Grid_DrawCheckBox(CDC*pDC,BOOL bCheck, CRect rect)
{
	CRect rcCheck = rect;
	rcCheck.right = rcCheck.left + 14;
	CPoint pt = rcCheck.CenterPoint();
	Grid_DrawCheckBoxRect(pt.x, pt.y, bCheck, pDC, TRUE);
}

void Grid_DrawCheckBoxRect(long xCenter,long yCenter,long nCheckState,CDC *pDC,BOOL bEnable)
{
	
	COLORREF crFrm = RGB(0,0,0);
	COLORREF crChk = RGB(34,161,34);
	
	if (!bEnable)
	{
		crFrm = RGB(128,128,128);
		crChk = RGB(192,192,192);
	}
	
	long xp1 = xCenter-3;
	long yp1 = yCenter-1;
	long xp2 = xCenter-1;
	long yp2 = yCenter+1;
	long xp3 = xCenter+4;
	long yp3 = yCenter-4;
	
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	//±ß¿ò
	CRect rectBtn(xCenter-6,yCenter-6,xCenter+6,yCenter+6);
	
	pDC->MoveTo(rectBtn.left,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.top);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
	CBrush brush(RGB(255,255,255));
	rectBtn.DeflateRect(1,1,1,1);
	pDC->FillRect(rectBtn,&brush);
	brush.DeleteObject();
	
	//Ñ¡ÖÐ
	CPen pen2(PS_SOLID,1,crChk);
	pOldPen = pDC->SelectObject(&pen2);
	if (nCheckState == 1)
	{
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
		yp1++;		yp2++;		yp3++;
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
		yp1++;		yp2++;		yp3++;
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
	}
	else if (nCheckState == 2)
	{
		CRect rect(xCenter-3,yCenter-3,xCenter+4,yCenter+4);
		CBrush brush(crChk);
		pDC->FillRect(&rect,&brush);
		brush.DeleteObject();
	}
	pDC->SelectObject(pOldPen);
	pen2.DeleteObject();
}

void CGridCell::EmptyCell()
{
	SetItemState(0);
	szText.Empty();
}

void CGridCell::SetItemState(UINT state)
{
	m_pRow->m_pGridCtrl->SetItemState(this, state);
}

void CGridCell::GetRowCol(int &row, int &col)
{
	row = m_pRow->m_nRow;
	col = m_pColumn->m_nColumn;
}

void CGridCell::UnMerge()
{
	int nRow = m_pRow->FindIndex(this);
	int nCol = m_pColumn->FindIndex(this);
	int nRows = m_pRow->GetSize();
	int nCols = m_pColumn->GetSize();
	CGridCell *pCell = this;
	CXGridCtrlBase *pGrid = m_pRow->m_pGridCtrl;

	for (; nRow < nRows; nRow++)
	{
		for (; nCol<nCols; nCol++)
		{
			pCell = pGrid->GetCell(nRow, nCol);

			if (pCell->m_pMergeTo == this)
			{
				pCell->m_pMergeTo = NULL;
			}
		}
	}
}

CRect CGridCell::GetMergeCellRect(const CRect &rcCell)
{
	if (m_pMergeTo != this)
	{
		return rcCell;
	}

	CRect rcMerge = rcCell;
	int nCol = m_pRow->FindIndex(this);
	int nRow = m_pColumn->FindIndex(this);

	if (nRow == -1 || nCol == -1)
	{
		return rcMerge;
	}
	
	nRow++;
	nCol++;

	int nCols = m_pRow->GetSize();
	int nRows = m_pColumn->GetSize();
	CGridCell *pCell = this;
	CXGridCtrlBase *pGrid = m_pRow->m_pGridCtrl;
	
	for (; nRow < nRows; nRow++)
	{
		pCell = m_pColumn->GetAt(nRow);
		
		if (pCell->m_pMergeTo == this)
		{
			rcMerge.bottom += pGrid->GetRowHeight(nRow);
		}
		else
		{
			break;
		}
	}

	for (; nCol<nCols; nCol++)
	{
		pCell = m_pRow->GetAt(nCol);
	
		if (pCell->m_pMergeTo == this)
		{
			rcMerge.right += pGrid->GetColumnWidth(nCol);
		}
		else
		{
			break;
		}
	}

	return rcMerge;
}


CRect CGridCell::GetMergeCellRect()
{
	CRect rcCell(0, 0, 0, 0);
	ASSERT (m_pRow != NULL);

	if (m_pRow == NULL)
	{
		return rcCell;
	}

	CXGridCtrlBase *pGrid = m_pRow->m_pGridCtrl;
	ASSERT (pGrid != NULL);

	if (pGrid == NULL)
	{
		return rcCell;
	}

	int nRow = 0;
	int nCol = 0;

	if (!GetCellID(nRow, nCol))
	{
		return rcCell;
	}

	if (nRow == -1 || nCol == -1)
	{
		return rcCell;
	}

	if (! pGrid->GetCellRect(nRow, nCol, &rcCell))
	{
		return rcCell;
	}

	if (m_pMergeTo != this)
	{
		return rcCell;
	}
	
	CRect rcMerge = rcCell;
	nRow++;
	nCol++;
	
	int nCols = m_pRow->GetSize();
	int nRows = m_pColumn->GetSize();
	CGridCell *pCell = this;
	
	for (; nRow < nRows; nRow++)
	{
		pCell = m_pColumn->GetAt(nRow);
		
		if (pCell->m_pMergeTo == this)
		{
			rcMerge.bottom += pGrid->GetRowHeight(nRow);
		}
		else
		{
			break;
		}
	}
	
	for (; nCol<nCols; nCol++)
	{
		pCell = m_pRow->GetAt(nCol);
		
		if (pCell->m_pMergeTo == this)
		{
			rcMerge.right += pGrid->GetColumnWidth(nCol);
		}
	}
	
	return rcMerge;
}

BOOL CGridCell::GetCellID(int &nRow, int &nCol)
{
	ASSERT (m_pRow != NULL && m_pColumn != NULL);

	if (m_pRow == NULL || m_pColumn == NULL)
	{
		return FALSE;
	}

	nRow = m_pColumn->FindIndex(this);
	nCol = m_pRow->FindIndex(this);

	return TRUE;
}

void CGridCell::GetCellRange(CGridCellRange &oCellRange)
{
	int nRow = 0;
	int nCol = 0;

	if (m_pMergeTo == NULL)
	{
		GetCellID(nRow, nCol);
		oCellRange.m_nMinRow = nRow;
		oCellRange.m_nMinCol = nCol;
		oCellRange.m_nMaxRow = nRow;
		oCellRange.m_nMaxCol = nCol;
	}
	else if (m_pMergeTo != this)
	{
		m_pMergeTo->GetCellRange(oCellRange);
	}
	else
	{
		GetCellID(nRow, nCol);
		oCellRange.m_nMinRow = nRow;
		oCellRange.m_nMinCol = nCol;
		
		int nCols = m_pRow->GetSize();
		int nRows = m_pColumn->GetSize();
		CGridCell *pCell = this;
		
		for (; nRow < nRows; nRow++)
		{
			pCell = m_pColumn->GetAt(nRow);
			
			if (pCell->m_pMergeTo == this)
			{
				oCellRange.m_nMaxRow = nRow;
			}
			else
			{
				break;
			}
		}
		
		for (; nCol<nCols; nCol++)
		{
			pCell = m_pRow->GetAt(nCol);
			
			if (pCell->m_pMergeTo == this)
			{
				oCellRange.m_nMaxCol = nCol;
			}
			else
			{
				break;
			}
		}
	}
}


CGridCells::CGridCells()
{

}

CGridCells::~CGridCells()
{

}


int CGridCells::FindIndex(CGridCell *pCell)
{
	int nIndexFind = -1;
	int nIndex = 0;
	int nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (pCell == GetAt(nIndex))
		{
			nIndexFind = nIndex;
			break;
		}
	}
	
	return nIndexFind;
}

