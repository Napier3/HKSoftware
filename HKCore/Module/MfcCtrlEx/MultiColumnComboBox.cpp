// MultiColumnComboBox.cpp : implementation file   
//   
   
#include "stdafx.h"   
#include "MultiColumnComboBox.h"   
   
#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   
   
/////////////////////////////////////////////////////////////////////////////   
// CMultiColumnComboBox   
   
CMultiColumnComboBox::CMultiColumnComboBox()   
{   
    m_TotalColumn       = 0;   
    m_BoundColumn       = 0;   
    m_TextItemHeight    = 12;   
    m_LightGrayPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DLIGHT));   
    m_ColumnWidth       = NULL;   
    m_ColumnAlignStyle  = NULL;   
    m_ColumnItemList    = NULL;   
}   
   
CMultiColumnComboBox::~CMultiColumnComboBox()   
{   
    if (m_TotalColumn != 0)   
    {   
        delete[] m_ColumnWidth;   
        delete[] m_ColumnAlignStyle;   
        delete[] m_ColumnItemList;   
    }   
    m_LightGrayPen.DeleteObject();   
}   
   
BEGIN_MESSAGE_MAP(CMultiColumnComboBox, CComboBox)   
    //{{AFX_MSG_MAP(CMultiColumnComboBox)   
    //}}AFX_MSG_MAP   
END_MESSAGE_MAP()   
   
/////////////////////////////////////////////////////////////////////////////   
// CMultiColumnComboBox message handlers   
void CMultiColumnComboBox::FormatComboBox(UINT TotalColumn, UINT BoundColumn)   
{   
    ASSERT(TotalColumn > 1); //You can use CComboBox class instead of this class   
   
    m_TotalColumn = TotalColumn;   
    m_BoundColumn = BoundColumn;   
   
    m_ColumnWidth       = new UINT[m_TotalColumn];   
    m_ColumnAlignStyle  = new UINT[m_TotalColumn];   
    m_ColumnItemList    = new CStringList[m_TotalColumn];   
   
    if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) != CBS_SIMPLE)   
    {   
        UINT ComboBoxWidth = GetDroppedWidth() - LEFTMARGIN_OF_DROPDOWNLIST - SPACE_BETWEEN_COLUMN - 1;   
		UINT TotalColumnWidth = LEFTMARGIN_OF_DROPDOWNLIST + RIGHTMARGIN_OF_DROPDOWNLIST;
     
			for (UINT Index = 0; Index < m_TotalColumn; Index++)   
        {   //Assign default value    
            m_ColumnWidth[Index] = ComboBoxWidth;   
            m_ColumnAlignStyle[Index] = DT_LEFT;   
            TotalColumnWidth += (ComboBoxWidth + SPACE_BETWEEN_COLUMN);   
        }   
   
        SetDroppedWidth(TotalColumnWidth);   
    }   
   
    CDC * pDC = GetWindowDC();   
	CSize sz = pDC->GetTextExtent(_T("0"), 1);
    m_TextItemHeight =sz.cy - 1;   
    SetItemHeight(-1, m_TextItemHeight);   
    ReleaseDC(pDC);   
}   
   
void CMultiColumnComboBox::SetColumnWidth(UINT ColumnWidth0, ...)   
{      
    va_list widthlist;   
    UINT TotalColumnWidth;   
   
    ASSERT(m_TotalColumn > 1);   //call FormatComboBox first   
   
    m_ColumnWidth[0] = ColumnWidth0;   
    TotalColumnWidth = ColumnWidth0 + SPACE_BETWEEN_COLUMN + LEFTMARGIN_OF_DROPDOWNLIST + RIGHTMARGIN_OF_DROPDOWNLIST;   
   
    va_start(widthlist, ColumnWidth0);   
    for (UINT Index = 1; Index < m_TotalColumn; Index++)   
    {   
        m_ColumnWidth[Index] = va_arg(widthlist, UINT);   
        if (m_ColumnWidth[Index] > 0)   
            TotalColumnWidth += (m_ColumnWidth[Index] + SPACE_BETWEEN_COLUMN);   
    }   
    va_end(widthlist);   
   
    if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) == CBS_SIMPLE)   
    {   
        CRect       WindowRectangle;   
        GetWindowRect(WindowRectangle);   
        SetWindowPos(NULL, 0, 0, TotalColumnWidth, WindowRectangle.bottom - WindowRectangle.top, SWP_NOMOVE | SWP_NOZORDER);   
    }   
    else   
        SetDroppedWidth(TotalColumnWidth);   
}   
   
void CMultiColumnComboBox::SetColumnAlignStyle(UINT ColumnAlignStyle0, ...)   
{      
    va_list ColumnAlignStyleList;   
   
    ASSERT(m_TotalColumn > 1);   //call FormatComboBox first   
   
    m_ColumnAlignStyle[0] = ColumnAlignStyle0;   
   
    va_start(ColumnAlignStyleList, ColumnAlignStyle0);   
    for (UINT Index = 1; Index < m_TotalColumn; Index++)   
        m_ColumnAlignStyle[Index] = va_arg(ColumnAlignStyleList, UINT);   
    va_end(ColumnAlignStyleList);   
}   
   
int CMultiColumnComboBox::AddRow(LPCTSTR lpszString0, ...)   
{      
    va_list strlist;   
    UINT    Index, ItemIndex;   
    LPCTSTR str;   
   
    ASSERT(m_TotalColumn > 1);   //call FormatComboBox first   
   
    if (m_BoundColumn == 0)   
        ItemIndex = CComboBox::AddString(lpszString0);   
    else   
    {   
        va_start(strlist, lpszString0);   
        for (Index = 1; Index < m_TotalColumn; Index++)   
        {   
            str = va_arg(strlist, LPCTSTR);   
            if (m_BoundColumn == Index)   
                ItemIndex = CComboBox::AddString(str);   
        }   
    }   
   
    if (ItemIndex == 0)   
        m_ColumnItemList[0].AddHead(lpszString0);   
    else   
        if (ItemIndex == (UINT) CComboBox::GetCount() - 1)   
            m_ColumnItemList[0].AddTail(lpszString0);   
        else   
            m_ColumnItemList[0].InsertBefore(m_ColumnItemList[0].FindIndex(ItemIndex), lpszString0);   
   
    va_start(strlist, lpszString0);   
    for (Index = 1; Index < m_TotalColumn; Index++)   
    {   
        str = va_arg(strlist, LPCTSTR);   
   
        if (ItemIndex == 0)   
            m_ColumnItemList[Index].AddHead(str);   
        else   
            if (ItemIndex == (UINT) CComboBox::GetCount() - 1)   
                m_ColumnItemList[Index].AddTail(str);   
            else   
                m_ColumnItemList[Index].InsertBefore(m_ColumnItemList[Index].FindIndex(ItemIndex), str);   
    }   
    va_end(strlist);   
   
    return TRUE;   
}   
   
void CMultiColumnComboBox::ResetContent()   
{   
    CComboBox::ResetContent();   
    for (UINT ColumnIndex = 0; ColumnIndex < m_TotalColumn; ColumnIndex++)   
        m_ColumnItemList[ColumnIndex].RemoveAll();   
};   
   
void CMultiColumnComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)    
{   
    ASSERT(m_TotalColumn > 1);   //You can use CComboBox class instead of this class   
   
	UINT ColumnIndex = 0;
    CPen*       pPen;   
    CDC*        pDC = CDC::FromHandle(lpDrawItemStruct->hDC);   
    CWnd*       pListBox = pDC->GetWindow();   
    BOOL        IsHighLightText = lpDrawItemStruct->itemAction & ODA_FOCUS || lpDrawItemStruct->itemState & ODS_SELECTED;   
    CRect       TextRectangle = lpDrawItemStruct->rcItem;   
       
    pDC->SetTextColor(GetSysColor(IsWindowEnabled() ? (IsHighLightText ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT) : COLOR_WINDOWTEXT));   
    pDC->SetBkColor(GetSysColor(IsWindowEnabled() ? (IsHighLightText ? COLOR_HIGHLIGHT : COLOR_WINDOW) : COLOR_3DFACE));   
    pDC->FillRect(TextRectangle, &CBrush(pDC->GetBkColor()));   
   
    if (IsHighLightText)   
        pDC->DrawFocusRect(TextRectangle);   
   
    if (lpDrawItemStruct->itemID != (UINT)-1)   
    {   
       // if (/*pListBox != this && */pListBox != NULL)       //Draw items in drop down list   
		if (TextRectangle.top != 3 )//lpDrawItemStruct->hwndItem != m_hWnd)
        {   
			TRACE(_T("pListBox != NULL %d  (top=%d) \r\n"), lpDrawItemStruct->itemID, TextRectangle.top);
//             if (TextRectangle.top == 0 && (GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) != CBS_SIMPLE)   
//             {   //Only "dropdwon" & "drop list" combo box can move their drop down window   
//                 CRect       WindowRectangle;   
//                 pListBox->GetWindowRect(WindowRectangle);   
//    
//                 if (WindowRectangle.right > GetSystemMetrics(SM_CXSCREEN))   //Move drop down window to left if its left side is out of screen   
//                 {   
//                     WindowRectangle.OffsetRect(GetSystemMetrics(SM_CXSCREEN) - WindowRectangle.right, 0);   
//                     pListBox->MoveWindow(WindowRectangle);   
//                 }   
//             }   
   
            if (!IsHighLightText)   
            {   
                pPen = pDC->SelectObject(&m_LightGrayPen);   
                pDC->MoveTo(TextRectangle.left, TextRectangle.bottom - 1);   
                pDC->LineTo(TextRectangle.right, TextRectangle.bottom - 1);   
            }   
   
            TextRectangle.left += LEFTMARGIN_OF_DROPDOWNLIST;   
            TextRectangle.right = TextRectangle.left;   
   
            for (UINT ColumnIndex = 0; ColumnIndex < m_TotalColumn; ColumnIndex++)   
            {   
                TextRectangle.left = TextRectangle.right;   
   
                if (m_ColumnWidth[ColumnIndex] != 0)   
                {   
                    if (ColumnIndex > 1 || (ColumnIndex == 1 && m_ColumnWidth[0] != 0))   
                    {      
                        TextRectangle.left += SPACE_BETWEEN_COLUMN;   
                        if (!IsHighLightText)   
                        {   //draw vertical gray line   
                            pDC->MoveTo(TextRectangle.left - SPACE_BETWEEN_COLUMN / 2, TextRectangle.top);   
                            pDC->LineTo(TextRectangle.left - SPACE_BETWEEN_COLUMN / 2, TextRectangle.bottom);   
                        }   
                    }   
   
                    TextRectangle.right = TextRectangle.left + m_ColumnWidth[ColumnIndex];   
                    TextRectangle.left++;   
   
                    // if vertical scrool bar is visible   
                    if ((ColumnIndex == m_TotalColumn - 1 || (ColumnIndex == m_TotalColumn - 2 && m_ColumnWidth[m_TotalColumn - 1] == 0)) /*&& (GetWindowLong(pListBox->m_hWnd, GWL_STYLE) & WS_VSCROLL)*/)   
                            TextRectangle.right -= GetSystemMetrics(SM_CXVSCROLL);   
   
                    pDC->DrawText(m_ColumnItemList[ColumnIndex].GetAt(m_ColumnItemList[ColumnIndex].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,   
                        m_ColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);   
                }   
            }   
   
            if (!IsHighLightText)   
                pDC->SelectObject(pPen);   
        }   
        else                                                //Draw item in edit box control/static text control   
        {   
			TRACE(_T("edit box %d \r\n"), lpDrawItemStruct->itemID);
            TextRectangle.left += LEFTMARGIN_OF_CONTROL;   
   
            if (m_ColumnWidth[m_BoundColumn] > 0)   
                pDC->DrawText(m_ColumnItemList[m_BoundColumn].GetAt(m_ColumnItemList[m_BoundColumn].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,   
                    m_ColumnAlignStyle[m_BoundColumn] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);   
            else                                            //Bound column is hidden   
            {   
                //Seek a column that its width is not 0   
                for (ColumnIndex = 0; !m_ColumnWidth[ColumnIndex] && ColumnIndex < m_TotalColumn; ColumnIndex++);   
   
                pDC->DrawText(m_ColumnItemList[ColumnIndex].GetAt(m_ColumnItemList[ColumnIndex].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,   
                    m_ColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);   
            }   
        }   
    }  
	else
	{
		TRACE(_T("edit box %d \r\n"), lpDrawItemStruct->itemID);
		TextRectangle.left += LEFTMARGIN_OF_CONTROL;   

		if (m_ColumnWidth[m_BoundColumn] > 0)   
			pDC->DrawText(m_ColumnItemList[m_BoundColumn].GetAt(m_ColumnItemList[m_BoundColumn].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,   
			m_ColumnAlignStyle[m_BoundColumn] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);   
		else                                            //Bound column is hidden   
		{   
			//Seek a column that its width is not 0   
			for (ColumnIndex = 0; !m_ColumnWidth[ColumnIndex] && ColumnIndex < m_TotalColumn; ColumnIndex++);   

			pDC->DrawText(m_ColumnItemList[ColumnIndex].GetAt(m_ColumnItemList[ColumnIndex].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,   
				m_ColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);   
		}    
	}
}   
   
void CMultiColumnComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)    
{   
    lpMeasureItemStruct->itemHeight = m_TextItemHeight;   
}  