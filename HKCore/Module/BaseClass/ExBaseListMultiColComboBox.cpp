// ExBaseListMultiColComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "ExBaseListMultiColComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExBaseListMultiColComboBox

CExBaseListMultiColComboBox::CExBaseListMultiColComboBox()
{
	m_nTotalColumn = 0;
	m_nBoundColumn = 0;
	m_nTextItemHeight = 12;
	m_oLightGrayPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DLIGHT));
	m_pnColumnWidth = NULL;
	m_pnColumnAlignStyle= NULL;
	m_bUseComboBoxList = FALSE;
}

CExBaseListMultiColComboBox::~CExBaseListMultiColComboBox()
{
	FreeMultiColComboBox();
	m_oLightGrayPen.DeleteObject();
}

void CExBaseListMultiColComboBox::ShowBaseList(CExBaseList *pList)
{
	InitMultiColComboBox();
	CExBaseListComboBox::ShowBaseList(pList);
}

void CExBaseListMultiColComboBox::FreeMultiColComboBox()
{
	if (m_nTotalColumn != 0)
	{
		m_nTotalColumn = 0;
		delete[] m_pnColumnWidth;
		delete[] m_pnColumnAlignStyle;
		m_pnColumnWidth = NULL;
		m_pnColumnAlignStyle = NULL;
	}
}

void CExBaseListMultiColComboBox::GetItemColText(long nIndex, long nCol, CString &strText)
{
	GetLBText(nIndex, strText);
}

void CExBaseListMultiColComboBox::GetItemSelText(long nIndex, CString &strText)
{
	GetLBText(nIndex, strText);
}

/////////////////////////////////////////////////////////////////////////////
// CExBaseListMultiColComboBox message handlers
void CExBaseListMultiColComboBox::FormatComboBox(UINT nTotalColumn, UINT nBoundColumn)
{
	ASSERT(nTotalColumn > 1); //You can use CComboBox class instead of this class
	FreeMultiColComboBox();

	m_nTotalColumn = nTotalColumn;
	m_nBoundColumn = nBoundColumn;

	m_pnColumnWidth = new UINT[m_nTotalColumn];
	m_pnColumnAlignStyle= new UINT[m_nTotalColumn];

	if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) != CBS_SIMPLE)
	{
		UINT ComboBoxWidth = GetDroppedWidth() - MCCB_LEFTMARGIN_OF_DROPDOWNLIST - MCCB_SPACE_BETWEEN_COLUMN - 1;
		UINT TotalColumnWidth = MCCB_LEFTMARGIN_OF_DROPDOWNLIST + MCCB_RIGHTMARGIN_OF_DROPDOWNLIST;

		for (UINT Index = 0; Index < m_nTotalColumn; Index++)
		{//Assign default value 
			m_pnColumnWidth[Index] = ComboBoxWidth;
			m_pnColumnAlignStyle[Index] = DT_LEFT;
			TotalColumnWidth += (ComboBoxWidth + MCCB_SPACE_BETWEEN_COLUMN);
		}

		SetDroppedWidth(TotalColumnWidth);
	}

	CDC * pDC = GetWindowDC();
	CSize sz = pDC->GetTextExtent(_T("0"), 1);
	m_nTextItemHeight =sz.cy - 1;
	SetItemHeight(-1, m_nTextItemHeight);
	ReleaseDC(pDC);
}

void CExBaseListMultiColComboBox::SetColumnWidth(UINT nColumnWidth0, ...)
{
	va_list widthlist;
	UINT nTotalColumnWidth;

	ASSERT(m_nTotalColumn > 1);//call FormatComboBox first

	m_pnColumnWidth[0] = nColumnWidth0;
	nTotalColumnWidth = nColumnWidth0 + MCCB_SPACE_BETWEEN_COLUMN + MCCB_LEFTMARGIN_OF_DROPDOWNLIST + MCCB_RIGHTMARGIN_OF_DROPDOWNLIST;

	va_start(widthlist, nColumnWidth0);

	for (UINT Index = 1; Index < m_nTotalColumn; Index++)
	{
		m_pnColumnWidth[Index] = va_arg(widthlist, UINT);
		if (m_pnColumnWidth[Index] > 0)
			nTotalColumnWidth += (m_pnColumnWidth[Index] + MCCB_SPACE_BETWEEN_COLUMN);
	}

	va_end(widthlist);

	if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) == CBS_SIMPLE)
	{
		CRect WindowRectangle;
		GetWindowRect(WindowRectangle);
		SetWindowPos(NULL, 0, 0, nTotalColumnWidth, WindowRectangle.bottom - WindowRectangle.top, SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetDroppedWidth(nTotalColumnWidth);
	}
}

void CExBaseListMultiColComboBox::SetColumnAlignStyle(UINT ColumnAlignStyle0, ...)
{
	va_list ColumnAlignStyleList;

	ASSERT(m_nTotalColumn > 1);//call FormatComboBox first

	m_pnColumnAlignStyle[0] = ColumnAlignStyle0;

	va_start(ColumnAlignStyleList, ColumnAlignStyle0);

	for (UINT Index = 1; Index < m_nTotalColumn; Index++)
	{
		m_pnColumnAlignStyle[Index] = va_arg(ColumnAlignStyleList, UINT);
	}

	va_end(ColumnAlignStyleList);
}

void CExBaseListMultiColComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(m_nTotalColumn > 1);//You can use CComboBox class instead of this class

	if (m_nTotalColumn <= 1)
	{
		return;
	}

	UINT ColumnIndex = 0;
	CPen *pPen;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	BOOL bIsHighLightText = lpDrawItemStruct->itemAction & ODA_FOCUS || lpDrawItemStruct->itemState & ODS_SELECTED;
	CRect rcTextRectangle = lpDrawItemStruct->rcItem;

	pDC->SetTextColor(GetSysColor(IsWindowEnabled() ? (bIsHighLightText ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT) : COLOR_WINDOWTEXT));
	pDC->SetBkColor(GetSysColor(IsWindowEnabled() ? (bIsHighLightText ? COLOR_HIGHLIGHT : COLOR_WINDOW) : COLOR_3DFACE));
	pDC->FillRect(rcTextRectangle, &CBrush(pDC->GetBkColor()));

	if (bIsHighLightText)
	{
		pDC->DrawFocusRect(rcTextRectangle);
	}

	if (lpDrawItemStruct->itemID == (UINT)-1)
	{
		return;
	}

	CString strText;

	if (rcTextRectangle.top != 3 )
	{
		if (!bIsHighLightText)
		{
			pPen = pDC->SelectObject(&m_oLightGrayPen);
			pDC->MoveTo(rcTextRectangle.left, rcTextRectangle.bottom - 1);
			pDC->LineTo(rcTextRectangle.right, rcTextRectangle.bottom - 1);
		}

		rcTextRectangle.left += MCCB_LEFTMARGIN_OF_DROPDOWNLIST;
		rcTextRectangle.right = rcTextRectangle.left;

		for (ColumnIndex = 0; ColumnIndex < m_nTotalColumn; ColumnIndex++)
		{
			rcTextRectangle.left = rcTextRectangle.right;

			if (m_pnColumnWidth[ColumnIndex] != 0)
			{
				if (ColumnIndex > 1 || (ColumnIndex == 1 && m_pnColumnWidth[0] != 0))
				{
					rcTextRectangle.left += MCCB_SPACE_BETWEEN_COLUMN;

					if (!bIsHighLightText)
					{//draw vertical gray line
						pDC->MoveTo(rcTextRectangle.left - MCCB_SPACE_BETWEEN_COLUMN / 2, rcTextRectangle.top);
						pDC->LineTo(rcTextRectangle.left - MCCB_SPACE_BETWEEN_COLUMN / 2, rcTextRectangle.bottom);
					}
				}

				rcTextRectangle.right = rcTextRectangle.left + m_pnColumnWidth[ColumnIndex];
				rcTextRectangle.left++;

				// if vertical scrool bar is visible
				if ((ColumnIndex == m_nTotalColumn - 1 || (ColumnIndex == m_nTotalColumn - 2 && m_pnColumnWidth[m_nTotalColumn - 1] == 0)) /*&& (GetWindowLong(pListBox->m_hWnd, GWL_STYLE) & WS_VSCROLL)*/)
					rcTextRectangle.right -= GetSystemMetrics(SM_CXVSCROLL);

				GetItemColText(lpDrawItemStruct->itemID, ColumnIndex, strText);
				pDC->DrawText(strText, -1, rcTextRectangle,
					m_pnColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
			}
		}

		if (!bIsHighLightText)
		{
			pDC->SelectObject(pPen);
		}
	}
	else//Draw item in edit box control/static text control
	{
		rcTextRectangle.left += MCCB_LEFTMARGIN_OF_CONTROL;

		GetItemSelText(lpDrawItemStruct->itemID, strText);

		if (m_pnColumnWidth[m_nBoundColumn] > 0)
		{
			pDC->DrawText(strText, -1, rcTextRectangle,
				m_pnColumnAlignStyle[m_nBoundColumn] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		}
		else //Bound column is hidden
		{
			//Seek a column that its width is not 0
			for (ColumnIndex = 0; !m_pnColumnWidth[ColumnIndex] && ColumnIndex < m_nTotalColumn; ColumnIndex++);

			pDC->DrawText(strText, -1, rcTextRectangle,
				m_pnColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		}
	}
}

void CExBaseListMultiColComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = m_nTextItemHeight;
}

