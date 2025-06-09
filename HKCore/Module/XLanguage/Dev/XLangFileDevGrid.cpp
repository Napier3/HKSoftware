#include "StdAfx.h"
#include "XLangFileDevGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define		COLOR_ERROR_BACK  RGB(153, 217, 234)
#define		COLOR_ERROR_TEXT  RGB(255, 0, 0)

BOOL CXLangFileDevGrid::g_bHideSameXLangItem = TRUE;
//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CXLangFileDevGrid::CXLangFileDevGrid()
{
	m_pLanguageRef = NULL;
	m_pListXLangFile = NULL;
	m_pMsgRcvWnd = NULL;
}


CXLangFileDevGrid::~CXLangFileDevGrid(void)
{

}

void CXLangFileDevGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(2);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXLangFileDevGrid::InitGridTitle()
{
	CString cTempStr[2]={_T("序号")	,_T("资源名（总）")};
	int iWidth[2]={60,250};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 2);
}

void CXLangFileDevGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	
}


BOOL CXLangFileDevGrid::UpdateData(CExBaseObject *pData)
{
	//获取验证更新节点在当前grid节点的序号
	int nRow = GetDataRow(pData);
	CXLangItemDev *pItemDev = (CXLangItemDev*)pData;
	CXLangItem *pItem = NULL;

	if (nRow < 1)
	{
		return FALSE;
	}

	long nLangIndex = 0;
	long nLangCount = pItemDev->GetCount();
	long nCol = 0;
	PEXBASECELLDATA pVCellData = NULL;

	for (nLangIndex=2; nLangIndex<= nLangCount; nLangIndex++)
	{
		nCol = (nLangIndex-1) * 3 + 2;
		pVCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
		m_listVCellData.Delete(pVCellData);
		pVCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol+1);
		m_listVCellData.Delete(pVCellData);
		pVCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol+2);
		m_listVCellData.Delete(pVCellData);
	}

	for (nLangIndex=2; nLangIndex<= nLangCount; nLangIndex++)
	{
		pItem = pItemDev->FindXLangItem(nLangIndex);
		nCol = (nLangIndex-1) * 3 + 2;

		if (pItem == NULL)
		{
			SetItemBkColour(nRow, nCol, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+1, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+2, COLOR_ERROR_BACK);
			continue;
		}

		Show_StaticString(pItemDev, nRow, nCol, &pItem->m_strID);
		Show_StaticString(pItemDev, nRow, nCol+1, &pItem->m_strSrcText);
		Show_String(pItemDev, nRow, nCol+2, &pItem->m_strTranslation);
		SetItemFormat(nRow, nCol, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
		SetItemFormat(nRow, nCol+1, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
		SetItemFormat(nRow, nCol+2, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);

		if ((pItem->m_strID != pItemDev->m_pRefItem->m_strID)
			|| (pItem->m_strSrcText != pItemDev->m_pRefItem->m_strSrcText))
		{
			SetItemFgColour(nRow, nCol, COLOR_ERROR_TEXT);
			SetItemFgColour(nRow, nCol+1, COLOR_ERROR_TEXT);
			SetItemFgColour(nRow, nCol+2, COLOR_ERROR_TEXT);
			SetItemBkColour(nRow, nCol, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+1, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+2, COLOR_ERROR_BACK);
		}
		else
		{
			SetItemFgColour(nRow, nCol, RGB(0, 0, 0));
			SetItemFgColour(nRow, nCol+1, RGB(0, 0, 0));
			SetItemFgColour(nRow, nCol+2, RGB(0, 0, 0));
			SetItemBkColour(nRow, nCol, RGB(255, 255, 255));
			SetItemBkColour(nRow, nCol+1, RGB(255, 255, 255));
			SetItemBkColour(nRow, nCol+2, RGB(255, 255, 255));
		}
	}

	return TRUE;
}

void CXLangFileDevGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pListXLangFile = pDatas;
	CXLangFileRsItemMngr *pXLangFileRsItemMngr = (CXLangFileRsItemMngr*)m_pListXLangFile;
	InitGridRows();

	CExBaseList *pListFiles = &pXLangFileRsItemMngr->m_listFiles;
	CXLangFile *pFile = NULL;
	POS pos = pListFiles->GetHeadPosition();
	CExBaseObject *pFolder = NULL;
	long nCol = 2;
	long nCols = 2 + pListFiles->GetCount() * 3;
	SetColumnCount(nCols);

	while (pos != NULL)
	{
		pFile = (CXLangFile *)pListFiles->GetNext(pos);
		pFolder = (CExBaseObject *)pFile->GetParent();
		SetItemText(0, nCol, pFolder->m_strName + _T(" : 资源ID"));
		SetItemText(0, nCol+1, pFolder->m_strName + _T(" : 中文文本"));
		SetItemText(0, nCol+2, pFolder->m_strName + _T(" : 翻译文本"));
		SetColumnWidth(nCol, 150);
		SetColumnWidth(nCol+1, 250);
		SetColumnWidth(nCol+2, 250);
		ShowDatas(pFile, nCol);
		nCol += 3;
	}
}

long CXLangFileDevGrid::GetXLangIndexByCol(long nCol)
{
	long nXLangIndex = (nCol - 2 ) / 3 + 1;
	return nXLangIndex;
}

void CXLangFileDevGrid::InitGridRows()
{
	CXLangFileRsItemMngr *pXLangFileRsItemMngr = (CXLangFileRsItemMngr*)m_pListXLangFile;
	long nIndex = 1;
	CXLangItemDev *pItem = NULL;
	long nRows = pXLangFileRsItemMngr->GetCount();
	SetRowCount(nRows+1);
	POS pos = pXLangFileRsItemMngr->GetHeadPosition();

	while (pos != NULL)
	{
		pItem = (CXLangItemDev*)pXLangFileRsItemMngr->GetNext(pos);

		if (g_bHideSameXLangItem)
		{//如果是要隐藏没有错误的资源
			if (!pItem->HasError())
			{//如果资源没有错误，则进入下一个资源
				continue;
			}
		}

		Show_Index(pItem, nIndex, XLANGFILE_COL_ID_INDEX);
		Show_StaticString(pItem, nIndex, XLANGFILE_COL_ID_XLANGID, &pItem->m_pRefItem->m_strSrcText);
		SetItemFormat(nIndex, XLANGFILE_COL_ID_XLANGID, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
		nIndex++;
	}

	SetRowCount(nIndex);
}

void CXLangFileDevGrid::ShowDatas(CExBaseList *pDatas, long nCol)
{
	CXLangFileRsItemMngr *pXLangFileRsItemMngr = (CXLangFileRsItemMngr*)m_pListXLangFile;
	long nXLangIndex = (nCol - 2 ) / 3 + 1;
	CXLangItemDev *pItemDev = NULL;
	CXLangItem *pItem = NULL;
	POS pos = pXLangFileRsItemMngr->GetHeadPosition();
	long nRow = 0;

	while (pos != NULL)
	{
		pItemDev = (CXLangItemDev *)pXLangFileRsItemMngr->GetNext(pos);

		if (g_bHideSameXLangItem)
		{//如果是要隐藏没有错误的资源
			if (!pItemDev->HasError())
			{//如果资源没有错误，则进入下一个资源
				continue;
			}
		}

		nRow++;
		pItem = pItemDev->FindXLangItem(nXLangIndex);
		SetItemBkColour(nRow, nCol, RGB(255,255,255));
		SetItemBkColour(nRow, nCol+1, RGB(255,255,255));
		SetItemBkColour(nRow, nCol+2, RGB(255,255,255));
		SetItemFgColour(nRow, nCol, RGB(0, 0, 0));
		SetItemFgColour(nRow, nCol+1, RGB(0, 0, 0));
		SetItemFgColour(nRow, nCol+2, RGB(0, 0, 0));
		
		if (pItem == NULL)
		{
			SetItemFgColour(nRow, nCol, RGB(255, 0, 0));
			SetItemFgColour(nRow, nCol+1, RGB(255, 0, 0));
			SetItemFgColour(nRow, nCol+2, RGB(255, 0, 0));
			SetItemBkColour(nRow, nCol, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+1, COLOR_ERROR_BACK);
			SetItemBkColour(nRow, nCol+2, COLOR_ERROR_BACK);
			Show_StaticString(pItemDev, nRow, nCol, m_strEmptyString);
			Show_StaticString(pItemDev, nRow, nCol+1, m_strEmptyString);
			Show_StaticString(pItemDev, nRow, nCol+2, m_strEmptyString);
			continue;
		}

		Show_StaticString(pItemDev, nRow, nCol, &pItem->m_strID);
		Show_StaticString(pItemDev, nRow, nCol+1, &pItem->m_strSrcText);
		Show_StaticString(pItemDev, nRow, nCol+2, &pItem->m_strTranslation);
		SetItemFormat(nRow, nCol, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
		SetItemFormat(nRow, nCol+1, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
		SetItemFormat(nRow, nCol+2, DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);

		if (pItem->m_strID != pItemDev->m_pRefItem->m_strID)
		{
			SetItemFgColour(nRow, nCol, RGB(255, 0, 0));
			SetItemBkColour(nRow, nCol, COLOR_ERROR_BACK);
		}

		if(pItem->m_strSrcText != pItemDev->m_pRefItem->m_strSrcText)
		{
			SetItemFgColour(nRow, nCol+1, RGB(255, 0, 0));
			SetItemBkColour(nRow, nCol+1, COLOR_ERROR_BACK);
		}
	}
}

long CXLangFileDevGrid::GetXLangFileIndex()
{
	if (!IsValid(m_idCurrentCell))
	{
		return -1;
	}

	if (m_idCurrentCell.col < 2)
	{
		return -1;
	}

	return GetXLangIndexByCol(m_idCurrentCell.col);
}


BOOL CXLangFileDevGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	ASSERT (m_pMsgRcvWnd != NULL);
	SetFocus();
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项

	menu.AppendMenu(MF_STRING,XLANGID_FILEDEV_DELETEITEMS, _T("删除资源对象"));
	menu.AppendMenu(MF_STRING,XLANGID_FILEDEV_COPYITEMS, _T("拷贝资源对象"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,XLANGID_FILEDEV_OVERWRITE_ID, _T("覆盖-资源ID"));
	menu.AppendMenu(MF_STRING,XLANGID_FILEDEV_OVERWRITE_SRCTEXT, _T("覆盖-资源文本"));
	menu.AppendMenu(MF_STRING,XLANGID_FILEDEV_MATCH_TRANSTEXT, _T("匹配-翻译文本"));

	//确定弹出式菜单的位置
	ClientToScreen(&point);
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y, m_pMsgRcvWnd);			

	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	

	return TRUE;
}


void CXLangFileDevGrid::NextError()
{
	long nCurrRow = m_idCurrentCell.row;

	if (nCurrRow <= 0)
	{
		nCurrRow = 0;
	}
	else
	{
		//nCurrRow -= 1;
	}

	CXLangFileRsItemMngr *pXLangFileRsItemMngr = (CXLangFileRsItemMngr*)m_pListXLangFile;
	POS pos = pXLangFileRsItemMngr->FindIndex(nCurrRow);
	CXLangItemDev *pItemDev = NULL;

	while (pos != NULL)
	{
		pItemDev = (CXLangItemDev *)pXLangFileRsItemMngr->GetNext(pos);

		if (pItemDev->HasError())
		{
			break;
		}

		if (!g_bHideSameXLangItem)
		{
			nCurrRow++;
		}
	}

	if (nCurrRow >= m_nRows)
	{
		return;
	}

	SelectRow(nCurrRow+1);
	EnsureVisible(nCurrRow+1, 1);
	Invalidate(FALSE);
}

void CXLangFileDevGrid::PrevError()
{
	long nCurrRow = m_idCurrentCell.row;

	if (nCurrRow <= 1)
	{
		return;
	}
	else
	{
		nCurrRow -= 1;
	}

	CXLangFileRsItemMngr *pXLangFileRsItemMngr = (CXLangFileRsItemMngr*)m_pListXLangFile;
	POS pos = pXLangFileRsItemMngr->FindIndex(nCurrRow);
	CXLangItemDev *pItemDev = NULL;

	while (pos != NULL)
	{
		pItemDev = (CXLangItemDev *)pXLangFileRsItemMngr->GetPrev(pos);
		pItemDev = (CXLangItemDev *)pXLangFileRsItemMngr->GetAt(pos);

		if (pItemDev->HasError())
		{
			break;
		}

		if (!g_bHideSameXLangItem)
		{
			nCurrRow--;
		}
	}

	if (nCurrRow <= 0)
	{
		return;
	}

	SelectRow(nCurrRow);
	EnsureVisible(nCurrRow, 1);
	Invalidate(FALSE);
}