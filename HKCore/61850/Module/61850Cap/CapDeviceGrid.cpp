#include "StdAfx.h"
#include "CapDeviceGrid.h"


//////////////////////////////////////////////////////////////////////////
//CCapDeviceGrid

CCapDeviceGrid::CCapDeviceGrid()
{
	
}


CCapDeviceGrid::~CCapDeviceGrid(void)
{
	
}


void CCapDeviceGrid::InitGrid()
{
	SetRowCount(3);
	SetColumnCount(CAPDEVICEGRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CCapDeviceGrid::InitGridTitle()
{
	CString cTempStr[CAPDEVICEGRID_COLS]={_T("编号"),_T("类型"),_T("通道数"),_T("目标MAC"),_T("源MAC"),_T("AppID")};
	int iWidth[CAPDEVICEGRID_COLS]={40, 60,60,140,140,50};
	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, CAPDEVICEGRID_COLS);
}

void CCapDeviceGrid::ShowData(CExBaseObject *pStData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pStData->GetClassID();

// 	if (nClassID != CFGCLASSID_CSTCFG91CH)
// 	{
// 		return;
// 	}

	if (bInsertRow)
	{
		InsertRow(NULL);
		SetRowHeight(nRow, EXBASEGRID_ROWHEIGHT);
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pStData;
	CString strText;
	strText.Format(_T("%d"), pCapDevice->GetCount());

	Show_Index(pStData, nRow, CAPDEVICEGRID_INDEX);
	//Show_CheckBox(pStData, nRow, CAPDEVICEGRID_SELECT, 1);
	Show_Hex(pStData, nRow, CAPDEVICEGRID_APPID, &pCapDevice->m_dwAppID, 4);
	Show_Mac(pStData, nRow, CAPDEVICEGRID_MAC, pCapDevice->m_byteSrcMac);
	Show_Mac(pStData, nRow, CAPDEVICEGRID_DESTMAC, pCapDevice->m_byteDestMac);
	Show_StaticString(pStData, nRow, CAPDEVICEGRID_CHCOUNT, &strText);
	Show_61850Type(pStData, nRow, CAPDEVICEGRID_TYPE, pCapDevice->m_nType);
// 	ShowCfgCh_Desc(pStData, nRow, CAPDEVICEGRID_APPID);
// 	ShowCfgCh_AppCh(pStData, nRow, CAPDEVICEGRID_CHCOUNT);
// 	ShowCfgCh_Type(pStData, nRow, CAPDEVICEGRID_MAC);
// 	ShowCfgCh_Type(pStData, nRow, CAPDEVICEGRID_TYPE);

	nRow++;
}

void CCapDeviceGrid::Show_Mac(CExBaseObject *pStData, const int& nRow, const int& nCol, BYTE *pMac)
{
	CString strMac;
	strMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5]);
	Show_StaticString(pStData, nRow, nCol, strMac);
}

void CCapDeviceGrid::Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType)
{
	CString strType = ep_Get61850ProtocolType(nType);
	Show_StaticString(pStData, nRow, nCol, strType);
}

void CCapDeviceGrid::AddCapDevice(CExBaseObject *pCapDevice)
{
	if (pCapDevice == NULL)
	{
		SetRowCount(1);
	}
	else
	{
		int nRow = GetRowCount();
		ShowData(pCapDevice, nRow, TRUE);
		ResetScrollBars();
	}

	Invalidate(FALSE);
}

void CCapDeviceGrid::SelectRecordDevice(long nRowIndex, BOOL bSel)
{
	GV_ITEM Item;
	InitDataCellItem(Item, NULL);

	Item.row = nRowIndex;
	Item.mask = GVIF_FGCLR | GVIF_BKCLR;

	if (bSel)
	{
		Item.crBkClr = RGB(255, 255, 0);
		Item.crFgClr = RGB(255, 0, 0);
	}


	for (long nCol = 1; nCol<CAPDEVICEGRID_COLS; nCol++)
	{
		Item.col = nCol;
		SetItem(&Item);
		SetItemFontBold(nRowIndex, nCol, bSel);
	}

}


