// EpCapVirtualListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EpCapVirtualListCtrl.h"

// CEpCapVirtualListCtrl

IMPLEMENT_DYNAMIC(CEpCapVirtualListCtrl, CListCtrl)

CEpCapVirtualListCtrl::CEpCapVirtualListCtrl()
{
	m_nCount = 0;
	m_nMaxItems = 0;
	m_nOrignSize = 1024*1024;

	m_pListBuffer = NULL;
}

void CEpCapVirtualListCtrl::ExpandBuffer()
{
	if (m_pListBuffer == NULL)
	{
		m_pListBuffer = new DWORD[m_nOrignSize];
		m_nMaxItems = m_nOrignSize;
	}
	else
	{
		long nMaxItems = m_nMaxItems + 1024 * 128;
		DWORD *pBuffer = new DWORD[m_nMaxItems];

		if (pBuffer == NULL)
		{
			CLogPrint::LogString(LOGLEVEL_TRACE, _T("内存不足............"));
		}
		else
		{
			memcpy(pBuffer, m_pListBuffer, sizeof(DWORD) * m_nMaxItems);
			m_nMaxItems = nMaxItems;
			delete m_pListBuffer;
			m_pListBuffer = pBuffer;
		}
	}
}

CEpCapVirtualListCtrl::~CEpCapVirtualListCtrl()
{
	if (m_pListBuffer != NULL)
	{
		delete m_pListBuffer;
		m_pListBuffer = NULL;
	}
}

void CEpCapVirtualListCtrl::AddItem(CCapCycleMemBuffer *pBuffer)
{
	if(m_nCount >= m_nMaxItems)
	{
		ExpandBuffer();
	}
	
	if (m_nCount >= m_nMaxItems)
	{
		return;
	}
	
	m_pListBuffer[m_nCount] = (DWORD)pBuffer;	
	m_nCount++;
	SetItemCount(m_nCount);
}

void  CEpCapVirtualListCtrl::AddItems(CCapCycleMemBufferMngr *pBufferMngr)
{
	long nIndex = m_nCount;
	m_nCount += pBufferMngr->GetCount();

	if(m_nCount >= m_nMaxItems)
	{
		ExpandBuffer();
	}

	if (m_nCount >= m_nMaxItems)
	{
		return;
	}

	POS pos = pBufferMngr->GetHeadPosition();
	CCapCycleMemBuffer *pBuffer = NULL;

	while (pos != NULL)
	{
		pBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetNext(pos);
		m_pListBuffer[nIndex] = (DWORD)pBuffer;	
		nIndex++;
	}

	SetItemCount(m_nCount);
}

void CEpCapVirtualListCtrl::DeleteAllItems()
{
	CListCtrl::DeleteAllItems();
	m_nCount = 0;
}

BEGIN_MESSAGE_MAP(CEpCapVirtualListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispinfo)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CEpCapVirtualListCtrl::OnNMDblclk)
END_MESSAGE_MAP()



// CEpCapVirtualListCtrl 消息处理程序

int CEpCapVirtualListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CEpCapVirtualListCtrl::OnDestroy() 
{
	CListCtrl::OnDestroy();
}

void CEpCapVirtualListCtrl::OnGetDispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
//
// 	LV_ITEM* pItem= &(pDispInfo)->i;
// 	int iItemIndex= pItem->iItem;

	*pResult = 0;
}

void CEpCapVirtualListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDrawItemStruct->itemID; 
	BOOL bGet = GetItem(&lvi); 

	CCapCycleMemBuffer *pBuffer = (CCapCycleMemBuffer*)m_pListBuffer[lpDrawItemStruct->itemID];

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
		pDC->SetTextColor(pBuffer->GetColor());
		pDC->FillRect(rcBack, &CBrush(RGB(255,255,255))); 
	} 

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
			
			GetItemText(pBuffer, i, szText);

			rcItem.left += 5; rcItem.right -= 1; 
			
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	} 


}

void CEpCapVirtualListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int iItem = pNMItemActivate->iItem;
	
	if (iItem >= 0 && iItem < m_nCount)
	{
		
	}	
	*pResult = 0;
}

BOOL CEpCapVirtualListCtrl::GetItemText(int iRow, int iCol, CString &strText)
{
	strText = "";

	if (iRow >= m_nCount || iCol >= 6)
	{
		return FALSE;
	}
	else
	{
		return GetItemText((CCapCycleMemBuffer*)m_pListBuffer[iRow], iCol, strText);
	}
}

BOOL CEpCapVirtualListCtrl::GetItemText(CCapCycleMemBuffer *pBuffer, int iCol, CString &strText)
{
	long nDataLen = 0;

	switch (iCol)
	{
	case 0:
		strText.Format(_T("%d"), pBuffer->m_n64CapID);
		break;
	case 1:
		ep_GetIpProtocol(pBuffer->m_nProtocolType, strText);
		break;
	case 2:
		ep_GetIpV4(pBuffer->m_ipGroup.src.ip, strText);
		break;
	case 3:
		strText.Format(_T("%d"), pBuffer->m_ipGroup.src.port);
		break;
	case 4:
		ep_GetIpV4(pBuffer->m_ipGroup.dst.ip, strText);
		break;
	case 5:
		strText.Format(_T("%d"), pBuffer->m_ipGroup.dst.port);
		break;
	case 6:
		nDataLen = pBuffer->GetDataLength();
		strText.Format(_T("%d"), nDataLen);
		break;
	case 7:
		{
			BYTE *pData = pBuffer->GetBuffer();
			BOOL bAddTail = FALSE;

			if (nDataLen > 15)
			{
				nDataLen = 15;
				bAddTail = TRUE;
			}

			strText = _T("");

			for (long i=0; i<nDataLen; i++)
			{
				strText.AppendFormat(_T("%02X "), pData[i]);
			}

			if (bAddTail)
			{
				strText += _T("......");
			}
		}
		break;
	}

	return (0 <= iCol && iCol <= 7);
}

BOOL CEpCapVirtualListCtrl::CreateVirtualList(CRect rcWnd, CWnd *pParent, UINT nID)
{
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT |LVS_OWNERDATA | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS;
	//const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;
	BOOL bTrue = Create(dwStyle, rcWnd, pParent, nID);

	ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, NULL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (bTrue)
	{
		InitVirtualListTitle();
	}

	return bTrue;
}

BOOL CEpCapVirtualListCtrl::InitVirtualListTitle()
{
	//设置列表框
	SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertColumn(0,_T("编号"),LVCFMT_LEFT,50);
	InsertColumn(1,_T("协议"),LVCFMT_LEFT,50);
	InsertColumn(2,_T("源IP"),LVCFMT_LEFT,90);
	InsertColumn(3,_T("源端口"),LVCFMT_LEFT,60);
	InsertColumn(4,_T("目的IP"),LVCFMT_LEFT,90);
	InsertColumn(5,_T("目的端口"),LVCFMT_LEFT,60);
	InsertColumn(6,_T("长度"),LVCFMT_LEFT,40);
	InsertColumn(7,_T("内容"),LVCFMT_LEFT,280);
	return TRUE;
}

CCapCycleMemBuffer* CEpCapVirtualListCtrl::GetItemDataPtr(long nItemIndex)
{
	if (nItemIndex < 0 || nItemIndex >= m_nCount)
	{
		return NULL;
	}

	return (CCapCycleMemBuffer*)m_pListBuffer[nItemIndex];
}
