#include "StdAfx.h"
#include "CapDeviceGrid.h"

#include "CapDevice/CapDevice91.h"
#include "CapDevice/CapDevice92.h"
#include "CapDevice/CapDeviceGoose.h"

#include "CapDeviceChGrid.h"

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
	SetRowCount(1);
	SetColumnCount(CAPDEVICEGRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
	ResetScrollBars();
}

void CCapDeviceGrid::InitGridTitle()
{
	CString cTempStr[CAPDEVICEGRID_COLS]={_T("编号"),_T("类型"),_T("目标MAC"),/*_T("源MAC"),*/_T("通道数"),/*_T("控制块ID"),*/_T("AppID"),_T("输出口")};
	int iWidth[CAPDEVICEGRID_COLS]={40, 100, 150, 80, 80, 80};
	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, CAPDEVICEGRID_COLS);
}

void CCapDeviceGrid::ShowData(CExBaseObject *pStData, int& nRow, BOOL bInsertRow)
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pStData;

	if (bInsertRow)
	{
		InsertRow(NULL);
		SetRowHeight(nRow, EXBASEGRID_ROWHEIGHT);
	}

	Show_Index(pStData, nRow, CAPDEVICEGRID_INDEX);
    Show_61850Type(pStData, nRow, CAPDEVICEGRID_TYPE, pCapDevice->m_nType);
	Show_Mac(pStData, nRow, CAPDEVICEGRID_DESTMAC, pCapDevice->m_byteDestMac);
//	Show_Mac(pStData, nRow, CAPDEVICEGRID_SRCMAC, pCapDevice->m_byteSrcMac);
	long nCount = pCapDevice->GetCount();
	Show_Long(pStData, nRow, CAPDEVICEGRID_CHCOUNT, &nCount,FALSE);
	Show_Hex(pStData, nRow, CAPDEVICEGRID_APPID, &pCapDevice->m_dwAppID, SIZEOF_SHORT, FALSE);
/*
	UINT nClassID = pCapDevice->GetClassID();
	if(nClassID==CPDCLASSID_DEVICE92)
	{
		p92Data = (CCapDevice92*)pCapDevice;
		Show_StaticString(pStData, nRow, CAPDEVICEGRID_CTRLBLOCK, p92Data->m_strSVID);
	}
	else if (nClassID==CPDCLASSID_DEVICE91)
	{
		p91Data = (CCapDevice91*)pCapDevice;
		Show_StaticString(pStData, nRow, CAPDEVICEGRID_CTRLBLOCK, p91Data->m_strID);
	}
	else if (nClassID == CPDCLASSID_DEVICEGOOSE)
	{
		pGooseData = (CCapDeviceGoose*)pCapDevice;
		Show_StaticString(pStData, nRow, CAPDEVICEGRID_CTRLBLOCK, pGooseData->m_strGooseId);
	}
*/
	Show_Fiber(pStData, nRow, CAPDEVICEGRID_FIBER, pCapDevice->m_nFiberIndex);
	ShowColorRow(this, pCapDevice->m_nMatchState, nRow, CAPDEVICEGRID_COLS);

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

void CCapDeviceGrid::Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex)
{
	CString strFiber;
	strFiber.Format(_T("光口%d"),nFiberIndex+1);
	Show_StaticString(pStData, nRow, nCol, strFiber);
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

void CCapDeviceGrid::SelectRecordDevice(CExBaseObject *pStData, BOOL bSel)
{
	long nRowIndex = GetDataRow(pStData, 1);
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

BOOL CCapDeviceGrid::UpdateData(CExBaseObject *pData)
{
	int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowData(pData, nRow, FALSE);
		AdjustAllCols(TRUE);
		Invalidate(FALSE);
	}

	return TRUE;
}

void CCapDeviceGrid::UpdateCapDeviceLinkState()
{
	CCapDeviceBase *pCapDevice = NULL;
	long nRow = 1;

	for (nRow=1; nRow<m_nRows; nRow++)
	{
		pCapDevice = (CCapDeviceBase*)GetData(nRow, 1);

		if (pCapDevice == NULL)
		{
			break;
		}

		if (pCapDevice->m_bLinkState)
		{
			SetItemBkColour(nRow, 0, RGB(255, 255, 255));
		}
		else
		{
			SetItemBkColour(nRow, 0, RGB(255, 0, 0));
		}
	}

	Invalidate(FALSE);
}

