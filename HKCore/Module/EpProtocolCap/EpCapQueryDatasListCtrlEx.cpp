// EpCapQueryDatasListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapQueryDatasListCtrlEx.h"
#include "..\MemBuffer\BinaryTextConvert.h"
#include "..\Protocol\101\EpGlobalDefine_101.h"

#include "Config\MonitorCapConfig.h"
// CEpCapQueryDatasListCtrlEx

#define EPCAP_QUERYDATA_COL_INDEX   0
// #define EPCAP_QUERYDATA_COL_ITEMINDEX   1
 #define EPCAP_QUERYDATA_COL_NAME   1
#define EPCAP_QUERYDATA_COL_DATA   2
#define EPCAP_QUERYDATA_COL_TIME   3


IMPLEMENT_DYNAMIC(CEpCapQueryDatasListCtrlEx, CListCtrl)

CEpCapQueryDatasListCtrlEx::CEpCapQueryDatasListCtrlEx()
{
	m_nAddNew = 0;
	m_nCurrCount = 0;
	m_nCurrIndex = 0;
	m_pQueryResults = NULL;
	m_pCapSmDb = NULL;
	m_dwDeviceDataType = 0;
	m_pDeviceDatas = NULL;
	m_dwProtocol = 0;
}

CEpCapQueryDatasListCtrlEx::~CEpCapQueryDatasListCtrlEx()
{
	
}


BEGIN_MESSAGE_MAP(CEpCapQueryDatasListCtrlEx, CListCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CAP_QUERY, OnShowWatch)
	ON_MESSAGE(WM_CAP_QUERYS, OnShowWatchs)
END_MESSAGE_MAP()



// CEpCapQueryDatasListCtrlEx 消息处理程序


int CEpCapQueryDatasListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	this->ModifyStyle(NULL, LVS_OWNERDRAWFIXED);

	return 0;
}

void CEpCapQueryDatasListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	long nIndex = lpDrawItemStruct->itemID;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	CEpY4Data *pData = (CEpY4Data*)m_pDeviceDatas->GetAtIndex(lpDrawItemStruct->itemID);

	if (pData == NULL)
	{
		return;
	}

	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDrawItemStruct->itemID; 
	BOOL bGet = GetItem(&lvi); 

	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && 
		((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS)))); 

	// 画文本背景 
	CRect rcBack = lpDrawItemStruct->rcItem; 
	pDC->SetBkMode(TRANSPARENT); 
	if( bHighlight ) 
	{ 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 

		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		pDC->SetTextColor(RGB(0, 0, 0)); 
		pDC->FillRect(rcBack, &CBrush(RGB(255,255,255))); 
	} 

	//设置字体颜色 
	CString str; 

	//得到焦点大小 
	CRect rcFocus = lpDrawItemStruct->rcItem; 
	rcFocus.DeflateRect(1,1,1,1); 

	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
	{ 
		//写文本 
		CString szText;
		long nColumnCount = GetHeaderCtrl()-> GetItemCount();

		CRect rcItem; 
		if ( GetSubItemRect(lpDrawItemStruct->itemID, 0, LVIR_LABEL, rcItem )) 
		{
			szText.Format(_T("%d"), lpDrawItemStruct->itemID+1);
			rcItem.left += 5; rcItem.right -= 1; 
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		}
	
		for (int i = 0; i < nColumnCount; i++) 
		{ //循环得到文本 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
		
			GetItemText(pData, i, szText); 

			rcItem.left += 5; rcItem.right -= 1; 
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	} 
}

BOOL CEpCapQueryDatasListCtrlEx::GetItemText(CEpY4Data *pData, long nSubItem, CString &strText)
{
	strText.Empty();

	if (pData == NULL)
	{
		return FALSE;
	}

	switch (nSubItem)
	{
// 	case EPCAP_QUERYDATA_COL_ITEMINDEX:
// 		strText.Format(_T("%d"), pData->m_nDataAddr);
// 		//strText.Format(_T("%I64u"), pIndex->m_tm);
// 		break;
// 
	case EPCAP_QUERYDATA_COL_NAME:
		{
			strText = m_pDeviceDatas->GetName(pData->m_nDataAddr);
		}
		break;

	case EPCAP_QUERYDATA_COL_DATA:
		strText = Ep_GetCapDataText(m_dwProtocol, pData, m_dwDeviceDataType);
		break;

	case EPCAP_QUERYDATA_COL_TIME:
		Ep_EPTIME64_To_String(pData->m_tm, strText);
		break;

	default:
		break;
	}

	return TRUE;
}

void CEpCapQueryDatasListCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

}

void CEpCapQueryDatasListCtrlEx::CreateWatch(CRect rc, CWnd *pParent)
{
	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	//const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT |LVS_OWNERDATA | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS;

	Create(dwStyle, rc, pParent, ID_EPCAP_DATAS_LISTCTRL);
	//ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, NULL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	InsertColumn(EPCAP_QUERYDATA_COL_INDEX, _T("编号"), LVCFMT_LEFT, 80);
// 	InsertColumn(EPCAP_QUERYDATA_COL_ITEMINDEX, _T("条目号"), LVCFMT_LEFT,60);
 	InsertColumn(EPCAP_QUERYDATA_COL_NAME, _T("名称"), LVCFMT_LEFT, 200);
	InsertColumn(EPCAP_QUERYDATA_COL_DATA, _T("数据"), LVCFMT_LEFT, 100);
	InsertColumn(EPCAP_QUERYDATA_COL_TIME, _T("时间"), LVCFMT_LEFT, 120);
}


void CEpCapQueryDatasListCtrlEx::ShowResults(CEpDeviceDatas *pDeviceDatas, DWORD dwProtocol)
{
	DeleteAllItems();

	if (pDeviceDatas == NULL)
	{
		return;
	}

	AddResults(pDeviceDatas, dwProtocol);
}

void CEpCapQueryDatasListCtrlEx::AddResults(CEpDeviceDatas *pDeviceDatas, DWORD dwProtocol)
{
	m_dwProtocol = dwProtocol;
	m_pDeviceDatas = pDeviceDatas;
	m_dwDeviceDataType = m_pDeviceDatas->m_nDeviceDataType;
	SetItemCount(m_pDeviceDatas->GetCount());
// 	POS pos = pDeviceDatas->GetHeadPosition();
// 	CEpY4Data *pData = NULL;
// 	long nIndex = 0;//GetItemCount();
// 	m_dwDeviceDataType = pDeviceDatas->m_nDeviceDataType;
// 
// 	while (pos != NULL)
// 	{
// 		pData = pDeviceDatas->GetNext(pos);
// 		long nItem = InsertItem(nIndex, _T(""), 0);
// 		SetItemData(nItem, (DWORD)pData);
// 		nIndex++;
// 	}

}

LRESULT CEpCapQueryDatasListCtrlEx::OnShowWatch(WPARAM wParam, LPARAM lParam)
{
	PEPCAPDBBUFFERINDEX pIndexMngr = (PEPCAPDBBUFFERINDEX)wParam;
	long nCurrIndex = lParam;
	
	m_nCurrCount++;
	m_nAddNew++;

	return 0;
}



LRESULT CEpCapQueryDatasListCtrlEx::OnShowWatchs(WPARAM wParam, LPARAM lParam)
{
	if (m_nAddNew == 0)
	{
		return 0;
	}

	long nCount = GetItemCount();
	long nCurrCount = m_nCurrCount;
	long nIndex = 0;
	long nTempCount = nCurrCount - nCount;
	
	for (nIndex=0; nIndex<nTempCount; nIndex++)
	{
		long nItem = InsertItem(nCount + nIndex, _T(""));
	}

	if (m_nCurrCount > 0)
	{
		EnsureVisible(m_nCurrCount-1,FALSE);	
	}

	if (nTempCount == 0)
	{
		Invalidate(FALSE);
	}

	m_nAddNew = 0;

	return 0;
}
