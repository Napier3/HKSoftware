// EpCapQueryFrameListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapQueryFrameListCtrlEx.h"

#include "EpCapTextFuncs.h"
// CEpCapQueryFrameListCtrlEx



IMPLEMENT_DYNAMIC(CEpCapQueryFrameListCtrlEx, CListCtrl)

CEpCapQueryFrameListCtrlEx::CEpCapQueryFrameListCtrlEx()
{
	m_nAddNew = 0;
	m_nCurrCount = 0;
	m_nCurrIndex = 0;
	m_pQueryResults = NULL;
	m_pCapSmDb = NULL;
}

CEpCapQueryFrameListCtrlEx::~CEpCapQueryFrameListCtrlEx()
{
	
}


BEGIN_MESSAGE_MAP(CEpCapQueryFrameListCtrlEx, CListCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CAP_QUERY, OnShowWatch)
	ON_MESSAGE(WM_CAP_QUERYS, OnShowWatchs)
	ON_NOTIFY_REFLECT(NM_CLICK, &CEpCapQueryFrameListCtrlEx::OnNMClick)
	ON_NOTIFY(HDN_ITEMCLICKA, 0, &CEpCapQueryFrameListCtrlEx::OnHdnItemclick)
	ON_NOTIFY(HDN_ITEMCLICKW, 0, &CEpCapQueryFrameListCtrlEx::OnHdnItemclick)
	ON_NOTIFY(HDN_ITEMCHANGEDA, 0, &CEpCapQueryFrameListCtrlEx::OnHdnItemchanged)
	ON_NOTIFY(HDN_ITEMCHANGEDW, 0, &CEpCapQueryFrameListCtrlEx::OnHdnItemchanged)
	ON_NOTIFY_REFLECT(NM_THEMECHANGED, &CEpCapQueryFrameListCtrlEx::OnNMThemeChanged)
END_MESSAGE_MAP()



// CEpCapQueryFrameListCtrlEx 消息处理程序


int CEpCapQueryFrameListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
//	this->ModifyStyle(NULL, LVS_OWNERDRAWFIXED);

	return 0;
}

void CEpCapQueryFrameListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	long nIndex = lpDrawItemStruct->itemID;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	CEpCapDbBufferIndex *pDbIndex = m_pQueryResults->GetAtIndex(nIndex);//(CEpCapDbBufferIndex*)lpDrawItemStruct->itemData;
	PEPCAPDBBUFFERINDEX pIndex = &pDbIndex->m_oEpCapBufferIndex;

	if (pIndex == NULL)
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
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 

		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(pIndex->nProtocol);
		COLORREF crText;
		
		if (nFrameType == 0)
		{
			crText = RGB(0, 0, 0);
		}
		else
		{
			if (Ep_GetProtocol_FrameDir(pIndex->nProtocol) == 1) 
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
		
			GetItemText(pDbIndex, i, szText); 

			rcItem.left += 5; rcItem.right -= 1; 
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	} 
}

void CEpCapQueryFrameListCtrlEx::GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest)
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


void CEpCapQueryFrameListCtrlEx::GetDir(EP_ETHER_CAP_IP cap_ip, CString &strText)
{
	EpTxt_GetDir((CMonitorQueryConfig*)m_pCapConfig, cap_ip, strText);
// 	long nDir = -1;
// 	CMonitorQueryConfig *pMonitorCapConfig = (CMonitorQueryConfig*)m_pCapConfig;
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

void CEpCapQueryFrameListCtrlEx::GetContentText(PEPCAPDBBUFFERINDEX pIndex, CString &strText)
{
	EpTxt_GetContentText(pIndex, strText);
// 	WORD nFrameType = (WORD)Ep_GetProtocol_FrameType(pIndex->nProtocol);
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
// 		switch (pIndex->oDataHead.nDeviceDataType)
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
// 		case EP_DEVICE_DATA_NONE:
// 		case EP_DEVICE_DATA_EMPTY:
// 			strText = _T("");
// 			break;
// 		case EP_DEVICE_DATA_YK:
// 			strText = _T("遥控报文");
// 			break;
// 		case EP_DEVICE_DATA_TSYN:
// 			strText = _T("对时报文");
// 			break;
// 		}
// 
// 		strText.AppendFormat(_T("(ASDU %02X)"), Ep_GetProtocol_FrameType(pIndex->nProtocol));
// 	}
	
}

BOOL CEpCapQueryFrameListCtrlEx::GetItemTextBuffer(CEpCapDbBufferIndex *pDbIndex,CString &strText)
{
	return EpTxt_GetItemTextBuffer(m_pCapSmDb, pDbIndex, strText);
// 	BYTE *pBuffer = pDbIndex->GetBuffer();
// 	long nLen = pDbIndex->GetBufferLength();
// 
// 	if (pBuffer == NULL)
// 	{
// 		if (m_pCapSmDb != NULL)
// 		{
// 			m_pCapSmDb->ReadCapBuffer(&(pDbIndex->m_oEpCapBufferIndex), &(pDbIndex->m_oBuffer) );
// 			pBuffer = pDbIndex->GetBuffer();
// 			nLen = pDbIndex->m_oEpCapBufferIndex.nFrameLen;//pDbIndex->GetBufferLength();
// 		}
// 	}
// 
// 	if (pBuffer == NULL)
// 	{
// 		strText = _T("Error......");
// 		return FALSE;
// 	}
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
// 			strText += pText;
// 		}
// 	}
// 
// 	return TRUE;
}

BOOL CEpCapQueryFrameListCtrlEx::GetItemText(CEpCapDbBufferIndex *pDbIndex, long nSubItem, CString &strText)
{
	PEPCAPDBBUFFERINDEX pIndex = &pDbIndex->m_oEpCapBufferIndex;
	strText.Empty();

	if (pIndex == NULL)
	{
		return FALSE;
	}

	switch (nSubItem)
	{
	case EPCAP_QUERYFRAME_COL_TIME:
		Ep_EPTIME64_To_String(pIndex->tm, strText);
		//strText.Format(_T("%I64u"), pIndex->m_tm);
		break;

	case EPCAP_QUERYFRAME_COL_SRCADDR:
		GetAddrText (pIndex->ipGroup.src, strText);
		break;

	case EPCAP_QUERYFRAME_COL_DESTADDR:
		GetAddrText (pIndex->ipGroup.dst, strText, TRUE);
		break;

	case EPCAP_QUERYFRAME_COL_DIR:
		GetDir(pIndex->ipGroup.src, strText);
		break;

	case EPCAP_QUERYFRAME_COL_FRAME_DESC:
		GetContentText(pIndex, strText);
		break;

	case EPCAP_QUERYFRAME_COL_FRAME_TEXT:
		{
			GetItemTextBuffer(pDbIndex, strText);
		}
		break;
	case EPCAP_QUERYFRAME_COL_CAPID:
		{
			strText.Format(_T("%I64d (%I64d)"), pIndex->n64CapID, pIndex->n64CapFramePos);
		}
		break;
	default:
		break;
	}

	return TRUE;
}

void CEpCapQueryFrameListCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

}

void CEpCapQueryFrameListCtrlEx::CreateWatch(CRect rc, CWnd *pParent)
{
	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	//const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT |LVS_OWNERDATA | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS;

	Create(dwStyle, rc, pParent, ID_EPCAP_FRAME_LISTCTRL);
//	ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, NULL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	InsertColumn(EPCAP_QUERYFRAME_COL_INDEX, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_INDEX), LVCFMT_LEFT, 80);
	InsertColumn(EPCAP_QUERYFRAME_COL_TIME, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_TIME), LVCFMT_LEFT, 200);
	InsertColumn(EPCAP_QUERYFRAME_COL_SRCADDR, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_SRCADDR), LVCFMT_LEFT, 120);
	InsertColumn(EPCAP_QUERYFRAME_COL_DESTADDR, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_DESTADDR), LVCFMT_LEFT, 120);
	InsertColumn(EPCAP_QUERYFRAME_COL_DIR, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_DIR), LVCFMT_LEFT, 100);
	InsertColumn(EPCAP_QUERYFRAME_COL_FRAME_DESC, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_FRAME_DESC), LVCFMT_LEFT, 200);
	InsertColumn(EPCAP_QUERYFRAME_COL_FRAME_TEXT, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_FRAME_TEXT), LVCFMT_LEFT, 300);
	InsertColumn(EPCAP_QUERYFRAME_COL_CAPID, EpTxt_GetCapFrameTitle(EPCAP_QUERYFRAME_COL_CAPID), LVCFMT_LEFT, 80);

}

LRESULT CEpCapQueryFrameListCtrlEx::OnShowWatch(WPARAM wParam, LPARAM lParam)
{
	PEPCAPDBBUFFERINDEX pIndexMngr = (PEPCAPDBBUFFERINDEX)wParam;
	long nCurrIndex = lParam;
	
	m_nCurrIndex ++;
	m_nCurrCount++;
	m_nAddNew++;

	return 0;
}



LRESULT CEpCapQueryFrameListCtrlEx::OnShowWatchs(WPARAM wParam, LPARAM lParam)
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

void CEpCapQueryFrameListCtrlEx::ShowResults()
{
	DeleteAllItems();

	if (m_pQueryResults == NULL)
	{
		return;
	}

	m_nAddNew = m_pQueryResults->GetCount();
	POS pos = m_pQueryResults->GetHeadPosition();
	CEpCapDbBufferIndex *pIndex = NULL;
	long nIndex = 0;
	SetItemCount(m_nAddNew);

// 	while (pos != NULL)
// 	{
// 		pIndex = m_pQueryResults->GetNext(pos);
// 		long nItem = InsertItem(nIndex, _T(""));
// 		SetItemData(nItem, (DWORD)pIndex);
// 		nIndex++;
// 	}
}


void CEpCapQueryFrameListCtrlEx::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	if (pNMItemActivate->iItem >= 0)
	{//显示报文分析信息
		DWORD dwData = (DWORD)m_pQueryResults->GetAtIndex(pNMItemActivate->iItem);
		AfxGetMainWnd()->PostMessage(WM_CAPQUERY_ITEM_CLICK, dwData, dwData);
	}

	*pResult = 0;
}

void CEpCapQueryFrameListCtrlEx::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	TRACE("OnHdnItemclick\n");
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CEpCapQueryFrameListCtrlEx::OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	TRACE("OnHdnItemchanged\n");
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CEpCapQueryFrameListCtrlEx::OnNMThemeChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	TRACE("OnNMThemeChanged\n");
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
