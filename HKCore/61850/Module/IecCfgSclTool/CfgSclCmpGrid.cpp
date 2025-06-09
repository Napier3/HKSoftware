#include "StdAfx.h"
#include "CfgSclCmpGrid.h"


//////////////////////////////////////////////////////////////////////////
//CCfgSclCmpGrid

CCfgSclCmpGrid::CCfgSclCmpGrid()
{
	m_crBkColor = RGB(255, 255, 255);
	m_crTextColor = RGB(0, 0, 0);
	m_crTitleTextBkColor = RGB(192, 192, 192);
	m_crDataTextBkColor = RGB(255, 255, 255);

	m_Logfont.lfHeight = 12;
	SetFixedRowCount(1);
	SetFixedColumnCount(3);
}


CCfgSclCmpGrid::~CCfgSclCmpGrid(void)
{
	
}


void CCfgSclCmpGrid::InitStGrid()
{
	SetRowCount(1);
	SetColumnCount(5);

	CString astrTitle[] = {_T("编号"), _T("参数"), _T(""), _T("配置数据"), _T("SCL数据")};
	long pnWidth[] = {50, 60, 100, 200, 200};
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<5;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,GVET_NOEDIT);
		SetColumnWidth(iCol,pnWidth[iCol]);
		Item.szText=astrTitle[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	Merge(0, 1, 0, 2);
	
	SetRowHeight(0,CFGSCLCMP_GRID_ROWHEIGHT);
}


void CCfgSclCmpGrid::ShowCfgSclCmp(CCfgSclCmpData *pSclData, CCfgSclCmpData *pCfgData)
{
	SetRowCount(1500);

	long nRow = 1;

	CCfgSclCmpParaObjects *pCfgParas = pCfgData->GetDataParas();
	CCfgSclCmpParaObjects *pSclParas = pSclData->GetDataParas();
	ShowDataAttrCmp(pSclParas, pCfgParas, nRow);

	TPOS posScl = pSclData->GetHeadPosition();
	TPOS posCfg = pCfgData->GetHeadPosition();

	while (posCfg != NULL && posScl != NULL)
	{
		pCfgParas = (CCfgSclCmpParaObjects*)pCfgData->GetNext(posCfg);
		pSclParas = (CCfgSclCmpParaObjects*)pSclData->GetNext(posScl);
		ShowDataChCmp(pSclParas, pCfgParas, nRow);
	}

	while (posCfg != NULL)
	{
		pCfgParas = (CCfgSclCmpParaObjects*)pCfgData->GetNext(posCfg);
		ShowDataChCmp(NULL, pCfgParas, nRow);
	}

	while (posScl != NULL)
	{
		pSclParas = (CCfgSclCmpParaObjects*)pSclData->GetNext(posScl);
		ShowDataChCmp(pSclParas, NULL, nRow);
	}

	AutoSizeColumn(3);
	AutoSizeColumn(4);
	SetRowCount(nRow);
	ResetScrollBars();
}

void CCfgSclCmpGrid::ShowDataAttrCmp(CCfgSclCmpParaObjects *pSclParas, CCfgSclCmpParaObjects *pCfgParas, long& nRow)
{
	CExList listSclRef, listSclEmpty;
	CExList listCfgRef, listCfgEmpty;
	pSclParas->GetCmpParas(listSclRef, listSclEmpty);
	pCfgParas->GetCmpParas(listCfgRef, listCfgEmpty);

	TPOS pos = listSclRef.GetHeadPosition();
	CCfgSclCmpParaObject *pSclPara = NULL, *pCfgPara = NULL;

	while (pos != NULL)
	{
		pSclPara = (CCfgSclCmpParaObject *)listSclRef.GetNext(pos);
		Merge(nRow, 1, nRow, 2);
		ShowDataPara(pSclPara, pSclPara->m_pRef, nRow, 1);
	}

	pos = listSclEmpty.GetHeadPosition();
	while (pos != NULL)
	{
		pSclPara = (CCfgSclCmpParaObject *)listSclEmpty.GetNext(pos);
		Merge(nRow, 1, nRow, 2);
		ShowDataPara(pSclPara, NULL, nRow, 1);
	}

	pos = listCfgEmpty.GetHeadPosition();
	while (pos != NULL)
	{
		pCfgPara = (CCfgSclCmpParaObject *)listCfgEmpty.GetNext(pos);
		Merge(nRow, 1, nRow, 2);
		ShowDataPara(NULL, pCfgPara, nRow, 1);
	}

	listSclRef.RemoveAll();
	listSclEmpty.RemoveAll();
	listCfgRef.RemoveAll();
	listCfgEmpty.RemoveAll();
}

void CCfgSclCmpGrid::ShowDataChCmp(CCfgSclCmpParaObjects *pSclParas, CCfgSclCmpParaObjects *pCfgParas, long& nRow)
{
	long nBeginRow = nRow;
	CExList listSclRef, listSclEmpty;
	CExList listCfgRef, listCfgEmpty;

	if (pSclParas != NULL)
	{
		pSclParas->GetCmpParas(listSclRef, listSclEmpty);
	}

	if (pCfgParas != NULL)
	{
		pCfgParas->GetCmpParas(listCfgRef, listCfgEmpty);
	}

	TPOS pos = listSclRef.GetHeadPosition();
	CCfgSclCmpParaObject *pPara = NULL;

	while (pos != NULL)
	{
		pPara = (CCfgSclCmpParaObject *)listSclRef.GetNext(pos);
		ShowDataPara(pPara, pPara->m_pRef, nRow, 2);
	}

	pos = listSclEmpty.GetHeadPosition();
	while (pos != NULL)
	{
		pPara = (CCfgSclCmpParaObject *)listSclEmpty.GetNext(pos);
		ShowDataPara(pPara, NULL, nRow, 2);
	}

	pos = listCfgEmpty.GetHeadPosition();
	while (pos != NULL)
	{
		pPara = (CCfgSclCmpParaObject *)listCfgEmpty.GetNext(pos);
		ShowDataPara(NULL, pPara, nRow, 2);
	}

	listSclRef.RemoveAll();
	listSclEmpty.RemoveAll();
	listCfgRef.RemoveAll();
	listCfgEmpty.RemoveAll();

	GV_ITEM Item;
	InitDataCellItem(Item);
	Item.col = 1;
	Item.row = nBeginRow;

	if (pSclParas != NULL)
	{
		Item.szText = pSclParas->m_strID;
	}
	else
	{
		Item.szText = pCfgParas->m_strID;
	}

	SetItem(&Item);

	long nEndRow = nRow - 1;
	ASSERT (nEndRow >= nBeginRow);
	Merge(nBeginRow, 1, nEndRow, 1);
}

void CCfgSclCmpGrid::ShowDataPara(CCfgSclCmpParaObject *pSclPara, CCfgSclCmpParaObject *pCfgPara, long& nRow, long nAttrCol)
{
	if (pSclPara == NULL && pCfgPara == NULL)
	{
		return;
	}

	GV_ITEM Item;
	InitDataCellItem(Item);
	Item.row = nRow;

	//Index
	Item.col = 0;
	Item.szText.Format(_T("%d"), nRow);
	SetItem(&Item);
	
	Item.col = nAttrCol;

	if (pSclPara != NULL)
	{
		Item.szText = pSclPara->m_strID;
	}
	else
	{
		Item.szText = pCfgPara->m_strID;
	}

	SetItem(&Item);

	Item.col = 3;
	if (pSclPara != NULL)
	{
		Item.szText = pSclPara->GetValueString();
		Item.crBkClr = m_crDataTextBkColor;
	}
	else
	{
		Item.szText = _T("-------");
		Item.crBkClr = RGB(240,240,240);
	}
	SetItem(&Item);

	Item.col = 4;
	if (pCfgPara != NULL)
	{
		Item.szText = pCfgPara->GetValueString();
		Item.crBkClr = m_crDataTextBkColor;

		if ( (!pCfgPara->m_bSameValue) && (pSclPara != NULL))
		{
			Item.crFgClr = RGB(255, 0, 0);
		}
	}
	else
	{
		Item.szText = _T("-------");
		Item.crBkClr = RGB(240,240,240);
	}


	SetItem(&Item);

	SetRowHeight(nRow,CFGSCLCMP_GRID_ROWHEIGHT);
	nRow++;
}

void CCfgSclCmpGrid::InitDataCellItem(GV_ITEM& Item)
{
	InitGirdItem(Item);
	Item.crFgClr = m_crTextColor;
	Item.crBkClr = m_crDataTextBkColor;
}

