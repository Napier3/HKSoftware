#include "StdAfx.h"
#include "CommCmdGrid.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCommCmdGrid::CCommCmdGrid(void)
{
	m_pCurCpu = NULL;
}

CCommCmdGrid::~CCommCmdGrid(void)
{
}

void CCommCmdGrid::InitGrid()
{
	SetListMode(TRUE);
	EnableDragAndDrop(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(0);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CCommCmdGrid::InitGridTitle()
{
	int iNum=4;
	CString cTempStr[4]={g_sLangTxt_Name/*"名称"*/,g_sLangTxt_Variable/*"变量"*/,g_sLangTxt_Value/*"数值"*/,g_sLangTxt_Unit/*"单位"*/};
	int  iColType[4]={GVET_NOEDIT,GVET_NOEDIT,GVET_EDITBOX,GVET_NOEDIT};
	int nColWidth[4] = {200, 100, 100, 60};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,iColType[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
		SetColumnWidth(iCol, nColWidth[iCol]);
	}	

	SetRowHeight(0,20);
}

//用于定值、软压板、控制字
void CCommCmdGrid::InitVariables(CCpu* pCpu)
{
	m_pCurCpu = pCpu;
	ASSERT (m_pCurCpu != NULL);

	if (m_pCurCpu == NULL)
	{
		return;
	}

	CExBaseList *pList = GetDatas();

	UpdateVariables(pList);

	ResetScrollBars();
}

void CCommCmdGrid::SaveValue(long nRow,long nCol)
{
	CExBaseObject *pParaObject = (CExBaseObject*)GetItemData(nRow, 0);
	CString strText = GetItemText(nRow, nCol);
	SaveValue(pParaObject, strText);
}

void CCommCmdGrid::UpdateVariables(CExBaseList *pList)
{
	CExBaseObject * pParaObject = NULL;
	long nIndex = 0;
	long nRows = 0;

	if (pList == NULL)
	{
		return;
	}

	long nCount = pList->GetCount();
	SetRowCount(nCount + 1);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pParaObject = (CExBaseObject*)pList->GetNext(pos);
	
		if (ShowOneObject(pParaObject,nRows))
		{
			SetRowHeight(nRows, 20);
		}
	}

	SetRowCount(nRows);
}
