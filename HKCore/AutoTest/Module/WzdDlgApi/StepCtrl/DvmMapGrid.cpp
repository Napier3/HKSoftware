#include "stdafx.h"
#include "DvmMapGrid.h"
#include "DlgDvmDatasetMap.h"
#include "../WzdDlgDef.h"
#include "../StepDlg/WzdMainDlg.h"

CDvmMapGrid::CDvmMapGrid()
{

}

void CDvmMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmMapGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[4] = {_T("序号"),_T("数据集描述"),_T("ID"),_T("配置结果")};
	const int nSclIedsWidth[4]={50, 200, 200, 180};
	SetColumnCount(4);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, 4);
}

void CDvmMapGrid::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	CString strText = *pString;
	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_STRBLOCKS | GVIF_FGCLR;
	Item.row = nRow;
	Item.col = nCol;
	if(CString_To_long(strText.Mid(0, strText.Find('/'))) == CString_To_long(strText.Mid(strText.Find('/') + 1)))
	{
		Item.crFgClr = RGB(0, 0, 0);
	}
	else
	{
		Item.crFgClr = RGB(255, 0, 0);
	}	
	Item.nDataType = GVET_NOEDIT;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pString, pData,NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText = *pString;
	Item.pStrCmpBlocks = NULL;

	Item.pEditFunc = NULL;

	SetItem(&Item);
}

void CDvmMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmDatasetMap* pDataset = (CDvmDatasetMap*)pData;
	Show_Index(pDataset, nRow, 0);
	Show_StaticString(pDataset, nRow, 1, &pDataset->m_strName);
	//Show_StaticString(pDataset, nRow, 2, &pDataset->m_strID);
	Show_StaticString(pDataset, nRow, 2, &pDataset->m_strMapID);	//20231031 huangliang 显示为SCD中的ID
	long nTotal = 0, nFull = 0;
	pDataset->GetMapsCount(nFull, nTotal);
	CString strErr;
	strErr.Format("%d/%d", nFull, nTotal);
	Show_StaticString(pDataset, nRow, 3, &strErr);

	SetItemData(nRow, 0, (LPARAM)pDataset);
	SetItemData(nRow, 1, (LPARAM)pDataset);
	SetItemData(nRow, 2, (LPARAM)pDataset);
	SetItemData(nRow, 3, (LPARAM)pDataset);

	nRow++;
}

void CDvmMapGrid::LButtonDblClk(UINT nFlags, CPoint point)
{
	long nRow = GetCurrSelRow();
	CDvmDatasetMap* pDvmCmp = (CDvmDatasetMap*)GetItemData(nRow, 0);
	if(pDvmCmp == NULL)
		return ;

	if (pDvmCmp->m_pMap == NULL || pDvmCmp->m_pStand == NULL)
	{
		return;
	}

	
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);

	CDlgDvmDatasetMap oDlg;
	CString strTitle;
	strTitle.Format(_T("数据集映射【%s-%s】"), pDvmCmp->m_strName, pDvmCmp->m_strID);
	oDlg.m_strTitle = strTitle;
	oDlg.m_pDvmCmpObj = pDvmCmp;

	if (oDlg.DoModal() != IDOK)
	{
		UpdateDatas();
		g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
		g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
		return;
	}

	UpdateDatas();
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	g_pWzdMainDlg->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
}

void CDvmMapGrid::RButtonDown(UINT nFlags, CPoint point)
{
	CDvmMapGrid::OnLButtonDown(nFlags, point);
}

void CDvmMapGrid::RButtonUp(UINT nFlags, CPoint point)
{
	GetParent()->SendMessage(WM_DVMMAP_MENU, point.x, point.y);
}

CDvmDatasetMap* CDvmMapGrid::AddDatasetMap(CDvmDataset *pDestDataset, BOOL bNewStandDataset)
{
	long nRow = GetCurrSelRow();
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)GetItemData(nRow, 0);

	if (pDatasetMap == NULL)
	{
		return NULL;
	}

	CDvmLDeviceMap *pLdeviceMap = (CDvmLDeviceMap*)pDatasetMap->GetParent();
	CDvmDatasetMap *pAdd = pLdeviceMap->AddDvmMap(pDatasetMap, pDestDataset, bNewStandDataset);

	if (pDatasetMap == pAdd)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("选择的数据集与当前的映射一致！"));
	}

	CExBaseObject *pMapParent = (CExBaseObject*)pDestDataset->GetParent();
	pAdd->m_strMapName = pDestDataset->m_strName;
	pAdd->m_strMapID   = pDestDataset->m_strID;
	pAdd->m_strLdviceMap = pMapParent->m_strID;

	return pAdd;
}