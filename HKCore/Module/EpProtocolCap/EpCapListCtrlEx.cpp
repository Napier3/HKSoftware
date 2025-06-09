// EpCapListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapListCtrlEx.h"
#include "..\MemBuffer\BinaryTextConvert.h"
#include "..\Protocol\101\EpGlobalDefine_101.h"

#include "Config\MonitorCapConfig.h"
#include "EpCapTextFuncs.h"

// CEpCapListCtrlEx

IMPLEMENT_DYNAMIC(CEpCapListCtrlEx, CListCtrl)

CEpCapListCtrlEx::CEpCapListCtrlEx()
{
	m_nAddNew = 0;
	m_nCurrCount = 0;
	m_nCurrIndex = 0;
	ZeroMemory(m_dwFrameRecord, sizeof(DWORD) * CAP_SPY_MAX_COUNT);
}

CEpCapListCtrlEx::~CEpCapListCtrlEx()
{
	
}


BEGIN_MESSAGE_MAP(CEpCapListCtrlEx, CListCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CAP_MONITOR, OnShowWatch)
	ON_MESSAGE(WM_CAP_MONITORS, OnShowWatchs)
END_MESSAGE_MAP()



// CEpCapListCtrlEx 消息处理程序


int CEpCapListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	this->ModifyStyle(NULL, LVS_OWNERDRAWFIXED);

	return 0;
}

void CEpCapListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	long nIndex = lpDrawItemStruct->itemID;
//	CDC* pDC = GetDC();//
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	if (m_nCurrCount >= CAP_SPY_MAX_COUNT)
	{
		nIndex = nIndex + m_nCurrIndex;

		if (nIndex >= CAP_SPY_MAX_COUNT)
		{
			nIndex -= CAP_SPY_MAX_COUNT;
		}
	}
	
	CEpFrameRecord *pRecord = (CEpFrameRecord *)m_dwFrameRecord[nIndex];//lpDrawItemStruct->itemData;

	if (pRecord == NULL)
	{
// 		ReleaseDC(pDC);
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
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 

		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(pRecord->m_nProtocol);
		COLORREF crText;
		
		if (nFrameType == 0)
		{
			crText = RGB(0, 0, 0);
		}
		else
		{
			if (Ep_GetProtocol_FrameDir(pRecord->m_nProtocol) == 1) 
			{ 
				crText = RGB(0, 0, 255);
			} 
			else 
			{ 
				crText = RGB(0, 0, 0);
			} 
		}

		pDC->SetTextColor(crText); 
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
	
		for (int i = 0; i < nColumnCount; i++) 
		{ //循环得到文本 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
		
			GetItemText( pRecord, i, szText); 

			rcItem.left += 5; rcItem.right -= 1; 
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	} 

//	::ReleaseDC(pDC);
}

void CEpCapListCtrlEx::GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest)
{
	EpTxt_GetAddrText(cap_ip, strText, bDest);

// 	if (cap_ip.ip.s_addr == 0)
// 	{
// 		if (bDest)
// 		{
// 			strText = _T("----");
// 		}
// 		else
// 		{
// 			strText.Format(_T("COM%d"), cap_ip.port+1);
// 		}
// 	}
// 	else
// 	{
// 		ep_GetIpV4_H_L(&cap_ip.ip, strText);
// 	}
}

void CEpCapListCtrlEx::GetDir(EP_ETHER_CAP_IP cap_ip, CString &strText)
{
	//EpTxt_GetDir((CMonitorQueryConfig*)m_pCapConfig, cap_ip, strText);
// 	long nDir = -1;
// 	CMonitorCapConfig *pMonitorCapConfig = (CMonitorCapConfig*)m_pCapConfig;
// 
// 	if (cap_ip.ip.s_addr == 0)
// 	{
// 		CEmcSerialConfig *pSerial = pMonitorCapConfig->m_pEmcSerialsConfig->FindByPort(cap_ip.port);
// 		if (pSerial != NULL)
// 		{
// 			nDir = pSerial->m_nDir;
// 		}
// 	}
// 	else
// 	{
// 		CString strIP;
// 		ep_GetIpV4_H_L(&cap_ip.ip, strIP);
// 		CEmcNetConfig *pNet = (CEmcNetConfig*)pMonitorCapConfig->m_pEmcNetsConfig->FindByID(strIP);
// 		if (pNet != NULL)
// 		{
// 			nDir = pNet->m_nDir;
// 		}
// 	}
// 
// 	if (nDir == -1)
// 	{
// 		strText = _T("------");
// 	}
// 	else
// 	{
// 		strText = Ep_GetProtocolDir(nDir);
// 	}
}

void CEpCapListCtrlEx::GetContentText(CEpFrameRecord *pRecord, CString &strText)
{
	EpTxt_GetContentText(pRecord->m_nProtocol, pRecord->m_nDeviceDataType, strText);

// 	WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(pRecord->m_nProtocol);
// 
// 	if (nFrameType == 0)
// 	{
// 		strText = _T("错误的报文");
// 	}
// 	else if (nFrameType == (EPCLASSID_101_TFRAME_E5 & 0x0FF))
// 	{
// 		strText = _T("无数据时的标准回复");
// 	}
// 	else if (nFrameType == (EPCLASSID_101_TFRAME_10 & 0x0FF))
// 	{
// 		strText = _T("固定长度报文帧");
// 	}
// 	else if (nFrameType == (EPCLASSID_104_TFRAME_68_S & 0x0FF))
// 	{
// 		strText = _T("S格式报文");
// 	}
// 	else if (nFrameType == (EPCLASSID_104_TFRAME_68_U & 0x0FF))
// 	{
// 		strText = _T("U格式报文");
// 	}
// 	else
// 	{
// 		switch (pRecord->m_nDeviceDataType)
// 		{
// 		case EP_DEVICE_DATA_YC:
// 			strText = _T("遥测报文");
// 			break;
// 		case EP_DEVICE_DATA_YX:
// 			strText = _T("遥信报文");
// 			break;
// 		case EP_DEVICE_DATA_YT:
// 			strText = _T("遥调报文");
// 			break;
// 		case EP_DEVICE_DATA_EMPTY:
// 			strText = _T("");
// 			break;
// 		case EP_DEVICE_DATA_YK:
// 			strText = _T("遥控报文");
// 			break;
// 		}
// 
// 		strText.AppendFormat(_T("(ASDU %02X)"), Ep_GetProtocol_FrameType(pRecord->m_nProtocol));
// 
// 		if (Ep_GetProtocol_ProtoType(pRecord->m_nProtocol) == EPPROTOCOL_101)
// 		{
// 			strText += _T(" (101)");
// 		}
// 		else
// 		{
// 			strText += _T(" (104)");
// 		}
// 	}
}

BOOL CEpCapListCtrlEx::GetItemTextBuffer(CEpFrameRecord *pRecord,CString &strText)
{

	CCycleMemBuffer *pCycleBuffer = (CCycleMemBuffer*)pRecord->GetRecordBuffer();
	long nLen = 0;
	nLen = pCycleBuffer->GetDataLength();
	BYTE *pBuffer = pCycleBuffer->GetBuffer();
	return EpTxt_GetItemTextBuffer(pBuffer, nLen, strText);
// 
// 	if (nLen  == 0)
// 	{
// 		strText += _T("......");
// 	}
// 	else
// 	{
// 		CBinaryTextConvert oConvert;
// 		long nIndex = 0;
// 		char pText[4];
// 		pText[3] = 0;
// 
// 		for (nIndex=0; nIndex<nLen; nIndex++)
// 		{
// 			CBinaryTextConvert::ValueToString_Hex(*(pBuffer+nIndex), (BYTE*)pText);
// 			strText.AppendFormat(_T("%s"), (CString(pText)));
// 		}
// 	}
// 
// 	return TRUE;
}

BOOL CEpCapListCtrlEx::GetItemText(CEpFrameRecord *pRecord, long nSubItem, CString &strText)
{
	strText.Empty();

	if (pRecord == NULL)
	{
		return FALSE;
	}

	switch (nSubItem)
	{
	case 0:
		Ep_EPTIME64_To_String(pRecord->m_tm, strText);
		//strText.Format(_T("%I64u"), pRecord->m_tm);
		break;

	case 1:
		GetAddrText (pRecord->m_ipGroup.src, strText);
		break;

	case 2:
		GetAddrText (pRecord->m_ipGroup.dst, strText, TRUE);
		break;

	case 3:
		GetDir(pRecord->m_ipGroup.src, strText);
// 		if (Ep_GetProtocol_FrameDir(pRecord->m_nProtocol) == 1) 
// 		{
// 			strText = _T("监视方向");
// 		}
// 		else
// 		{
// 			strText = _T("控制方向");
// 		}
		break;

	case 4:
		GetContentText(pRecord, strText);
		break;

	case 5:
		{
			//CCycleMemBuffer *pCycleBuffer = pRecord->m_pFrmBuffer;
			//long nLen = pCycleBuffer->GetDataLength();
			//BYTE *pBuffer = pCycleBuffer->GetBuffer();
			//nLen =pCycleBuffer->GetDataLength();
			GetItemTextBuffer(pRecord, strText);
		}
		break;
	case 6:
		{
			strText.Format(_T("%I64d [%02X]"), pRecord->m_n64CapID, pRecord->m_oBuffer.GetDataLength());
			;
		}
		break;
	default:
		break;
	}

	return TRUE;
}

void CEpCapListCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	/*CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right = rcClient.left+cx;
	rcClient.bottom = rcClient.top+cy;

	if (m_hWnd != NULL)
	{
		MoveWindow(rcClient);
	}*/
}

void CEpCapListCtrlEx::CreateWatch(CRect rc, CWnd *pParent)
{
	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;

	Create(dwStyle, rc, pParent, ID_EPCAP_LISTCTRL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	InsertColumn(0, _T("时间"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("源地址"), LVCFMT_LEFT, 120);
	InsertColumn(2, _T("目标地址"), LVCFMT_LEFT, 120);
	InsertColumn(3, _T("报文方向"), LVCFMT_LEFT, 100);
	InsertColumn(4, _T("报文内容"), LVCFMT_LEFT, 200);
	InsertColumn(5, _T("报文信息"), LVCFMT_LEFT, 300);
	InsertColumn(6, _T("CAPID"), LVCFMT_LEFT, 80);

// 	SetColumnWidth(0, 200);
// 	SetColumnWidth(1, 120);
// 	SetColumnWidth(2, 120);
// 	SetColumnWidth(3, 100);
// 	SetColumnWidth(4, 200);
// 	SetColumnWidth(5, 300);

}

LRESULT CEpCapListCtrlEx::OnShowWatch(WPARAM wParam, LPARAM lParam)
{
	if (g_nExitCaptrueState == 1)
	{
		return 0;
	}

	CEpFrameRecordMngr *pRecordMngr = (CEpFrameRecordMngr*)wParam;
	long nCurrIndex = lParam;
	
	m_dwFrameRecord[m_nCurrIndex] = (DWORD)pRecordMngr->GetRecord(nCurrIndex);
	m_nCurrIndex ++;
	m_nCurrCount++;

	if (m_nCurrIndex >= CAP_SPY_MAX_COUNT)
	{
		m_nCurrIndex = 0;
	}

	if (m_nCurrCount >= CAP_SPY_MAX_COUNT)
	{
		m_nCurrCount = CAP_SPY_MAX_COUNT;
	}

	m_nAddNew++;
// 	long nListCount = GetItemCount();
// 	long nRecordCount = pRecordMngr->GetCount();
// 	long nMaxCount = pRecordMngr->GetLimit();
// 
// 	if (nListCount == nRecordCount)
// 	{
// 		DeleteItem(0);
// 		nListCount--;
// 	}
// 
// 	int nItemIndex = InsertItem(nListCount, NULL);
// 	SetItemData(nItemIndex, );
// 	EnsureVisible(nItemIndex,FALSE);	

	return 0;
}

void CEpCapListCtrlEx::ExitCap()
{
	m_nCurrCount = 0;
	m_nCurrIndex = 0;
	DeleteAllItems();
	long nCount = GetItemCount();
}

LRESULT CEpCapListCtrlEx::OnShowWatchs(WPARAM wParam, LPARAM lParam)
{
	if (m_nAddNew == 0)
	{
		return 0;
	}

//	SetItemCount(m_nCurrCount);
	long nCount = GetItemCount();
	long nCurrCount = m_nCurrCount;
	long nIndex = 0;
	long nTempCount = nCurrCount - nCount;
	
	for (nIndex=0; nIndex<nTempCount; nIndex++)
	{
		InsertItem(nCount + nIndex, _T(""));
	}

	if (m_nCurrCount > 0)
	{
		EnsureVisible(m_nCurrCount-1,FALSE);	
	}

	if (nTempCount == 0)
	{
		Invalidate(FALSE);
	}
// 	else
// 	{
// 		UpdateData(FALSE);
// 	}

	m_nAddNew = 0;

	return 0;
}

