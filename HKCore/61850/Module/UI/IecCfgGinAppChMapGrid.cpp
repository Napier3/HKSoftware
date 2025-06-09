#include "StdAfx.h"
#include "IecCfgGinAppChMapGrid.h"
#include "..\XLanguageResourceIec.h"

CString CIecCfgGinAppChMapGrid::g_strGinAppChMapEmptyString = _T("--");

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgGinAppChMapGrid::CIecCfgGinAppChMapGrid()
{
	//SetUseRButtonDownForSel();
}


CIecCfgGinAppChMapGrid::~CIecCfgGinAppChMapGrid(void)
{
	
}

void CIecCfgGinAppChMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_GINCHMAP);
	SetFixedRowCount(2);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgGinAppChMapGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_GINCHMAP]=
	{
		 g_sLangTxt_AppBin//_T("�����ǿ���")
		,g_sLangTxt_BindMac//_T("�󶨿��ƿ�MAC")
		,g_sLangTxt_BindAppID//_T("�󶨿��ƿ�APPID")
		,g_sLangTxt_BindChannel//_T("��ͨ��")
	};

	int iWidth[IECCFG_COLS_GINCHMAP]={80,120, 100,100};//, 90};

	
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 1;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<IECCFG_COLS_GINCHMAP;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,GVET_NOEDIT);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	Merge(0, 0, 0, IECCFG_COL_ID_GINCHMAP_CHNAME);
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_WORDBREAK|DT_END_ELLIPSIS;
	//Item.szText=_T("������˫����ѡ�еĿ��ƿ�ͨ���������ǿ��룬�ٴ�˫����ȥ��;��delete��ɾ��ѡ�еİ�");
	Item.szText=g_sLangTxt_OptrBindAppBinInfo;
	Item.col = 0;
	Item.row = 0;
	Item.lParam=0;
	SetItem(&Item);

	SetRowHeight(0,EXBASEGRID_ROWHEIGHT*2-8);
	SetRowHeight(1,EXBASEGRID_ROWHEIGHT);
}


void CIecCfgGinAppChMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	CIecCfgGinAppChMap *pMap = (CIecCfgGinAppChMap*)pData;
	Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_BIN, &pMap->m_strName);

	if (pMap->m_pIecCfgGinCh == NULL)
	{
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_MAC, &g_strGinAppChMapEmptyString);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_APPID, &g_strGinAppChMapEmptyString);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_CHNAME, &g_strGinAppChMapEmptyString);
//		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_CHINDEX, &g_strGinAppChMapEmptyString);
	}
	else
	{
		CIecCfgGinData *pGinData = (CIecCfgGinData*)pMap->m_pIecCfgGinCh->GetAncestor(CFGCLASSID_CIECCFGGINDATA);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_MAC, &pGinData->m_strDestAddress);
		Show_Hex(pData, nRow, IECCFG_COL_ID_GINCHMAP_APPID,    &pGinData->m_dwAppID, 2, FALSE, TRUE);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCHMAP_CHNAME, &pMap->m_pIecCfgGinCh->m_strName);
	}

	nRow++;
}


void CIecCfgGinAppChMapGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_idCurrentCell.col = -1;
	m_idCurrentCell.row = -1;

	ClearSelect();
	m_listVCellData.DeleteAll();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(2);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 2;
	long nCalRows = pDatas->GetCount() + 2;
	SetRowCount(nCalRows);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex);
	long nRows = GetRowCount();


	for (nRowIndex=1; nRowIndex<nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	//AdjustAllCols();
	AutoSizeColumn(IECCFG_COL_ID_GINCHMAP_CHNAME);
	ResetScrollBars();
	Invalidate(FALSE);

	AfterShowDatas(2,bResetScrollBars);
}

void  CIecCfgGinAppChMapGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	if (m_pDatas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰCIecCfgGinAppChMapGrid�������ָ��Ϊ��."));
		return;
	}

	CIecCfgGinAppChMap *pMap = (CIecCfgGinAppChMap*)m_pDatas->GetAt(nRow-2);
//	CIecCfgGinAppChMap *pMap = (CIecCfgGinAppChMap*)GetCurrSelData();//zhouhj 20211020 ������1ȥ������Ĭ�ϲ���0
//	ASSERT (pMap != NULL);

	if (pMap == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�к�(%d)��������δ�ҵ�,����������(%ld)."),nRow,m_pDatas->GetCount());
		return;
	}

	CIecCfgGinCh *pGinCh = NULL;

	if (pMap->m_pIecCfgGinCh == NULL)
	{
		pGinCh = GetCurrSelGinCh();

		if (pGinCh == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("������ߵ�GOOSE����ͨ���б���ѡ��ͨ�����ݶ���"));
			return;
		}

		pMap->m_pIecCfgGinCh = pGinCh;
		pMap->m_pIecCfgGinCh->AddBinString(pMap->m_strID);
	}
	else
	{
		pGinCh = pMap->m_pIecCfgGinCh;
		pGinCh->RemoveBinString(pMap->m_strID);
		pMap->m_pIecCfgGinCh = NULL;
	}

	ShowData(pMap, nRow, FALSE);
	AutoSizeColumn(IECCFG_COL_ID_GINCHMAP_CHNAME);
	Invalidate(FALSE);
	UpdateGinCh(pGinCh);
}
// 
// void  CIecCfgGinAppChMapGrid::OnEditCellRBDblClk(int nRow, int nCol, UINT nChar)
// {
// 	CIecCfgGinAppChMap *pMap = (CIecCfgGinAppChMap*)GetCurrSelData(1);
// 	ASSERT (pMap != NULL);
// 
// 	if (pMap == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pMap->m_pIecCfgGinCh == NULL)
// 	{
// 		return;
// 	}
// 
// 	pMap->m_pIecCfgGinCh->RemoveBinString(pMap->m_strID);
// 	UpdateGinCh(pMap->m_pIecCfgGinCh);
// 	pMap->m_pIecCfgGinCh = NULL;
// 	ShowData(pMap, nRow, FALSE);
// 	Invalidate(FALSE);
// }

CIecCfgGinCh* CIecCfgGinAppChMapGrid::GetCurrSelGinCh()
{
	CWnd *pParentWnd = GetParent();
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pParentWnd->SendMessage(WM_GET_CURR_SEL_GIN_CH, 0, 0);

	return pGinCh;
}

void CIecCfgGinAppChMapGrid::UpdateGinCh(CIecCfgGinCh *pGinCh)
{
	CWnd *pParentWnd = GetParent();
	pParentWnd->PostMessage(WM_UPDATE_GIN_CH, (WPARAM)pGinCh, (LPARAM)pGinCh);
}


BOOL CIecCfgGinAppChMapGrid::OnCellKeyDelete(const CCellID &idCell)
{
	CIecCfgGinAppChMap *pMap = NULL;
	int nRow = 0;
	CExBaseList oList;
	GetAllSelectDatas(&oList);
	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		pMap = (CIecCfgGinAppChMap *)oList.GetNext(pos);

		if (pMap->m_pIecCfgGinCh != NULL)
		{
			pMap->m_pIecCfgGinCh->RemoveBinString(pMap->m_strID);
			UpdateGinCh(pMap->m_pIecCfgGinCh);
			pMap->m_pIecCfgGinCh = NULL;
			nRow = m_pDatas->FindIndex(pMap) + 2;
			ShowData(pMap, nRow, FALSE);
			Invalidate(FALSE);
		}
	}

	oList.RemoveAll();
	AutoSizeColumn(IECCFG_COL_ID_GINCHMAP_CHNAME);
	iecfg_SetModified(m_pDatas);

	return TRUE;
}

