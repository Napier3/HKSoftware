// CapListCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CapListCtrlEx.h"
#include "CapDevice\CapDeviceGlobal.h"

// CCapListCtrlEx

IMPLEMENT_DYNAMIC(CCapListCtrlEx, CListCtrl)

CCapListCtrlEx::CCapListCtrlEx()
{
	m_nAddNew = 0;
	m_nViewCurrCount = 0;
	m_nViewCurrIndex = 0;
	m_pFrameMemBufferMngr = NULL;
	m_dBeginTime = 0;
	m_bFirstTime = TRUE;

#ifndef FrameMemBuffer_use_FrameID
	m_n64FrameID = 1;
#endif
}

CCapListCtrlEx::~CCapListCtrlEx()
{
	
}


BEGIN_MESSAGE_MAP(CCapListCtrlEx, CListCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CAP_MONITOR, OnShowWatch)
	ON_MESSAGE(WM_CAP_MONITORS, OnShowWatchs)
	ON_NOTIFY_REFLECT(NM_CLICK, &CCapListCtrlEx::OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CCapListCtrlEx::OnNMRClick)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, &CCapListCtrlEx::OnLvnKeydown)
END_MESSAGE_MAP()



// CCapListCtrlEx ��Ϣ�������


int CCapListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	this->ModifyStyle(NULL, LVS_OWNERDRAWFIXED);

	return 0;
}

void CCapListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	long nIndex = lpDrawItemStruct->itemID;
//	CDC* pDC = GetDC();//
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	if (m_nViewCurrCount >= CAP_SPY_MAX_COUNT)
	{
		nIndex = nIndex + m_nViewCurrIndex;

		if (nIndex >= CAP_SPY_MAX_COUNT)
		{
			nIndex -= CAP_SPY_MAX_COUNT;
		}
	}
	
	CFrameMemBuffer *pCapBuffer = (CFrameMemBuffer *)m_pFrameMemBufferMngr->GetFrameBuffer(nIndex);

	if (pCapBuffer == NULL)
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

	// ���ı����� 
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
		COLORREF crText;
		crText = RGB(0, 0, 0);
		pDC->SetTextColor(crText); 
		pDC->FillRect(rcBack, &CBrush(RGB(255,255,255))); 
	} 

	//����������ɫ 
	CString str; 

	//�õ������С 
	CRect rcFocus = lpDrawItemStruct->rcItem; 
	rcFocus.DeflateRect(1,1,1,1); 

	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
	{ 
		//д�ı� 
		CString szText;
		long nColumnCount = GetHeaderCtrl()-> GetItemCount();
	
		for (int i = 0; i < nColumnCount; i++) 
		{ //ѭ���õ��ı� 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
		
			GetItemText( pCapBuffer, i, szText); 

			rcItem.left += 5; rcItem.right -= 1; 
			pDC->DrawText(szText/*szText*/, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	} 

//	::ReleaseDC(pDC);
}
// 
// void CCapListCtrlEx::GetContentText(CFrameMemBuffer *pCapBuffer, CString &strText)
// {
// 	Txt_GetContentText(pCapBuffer->m_nProtocol, pCapBuffer->m_nDeviceDataType, strText);
// 
// // 	WORD nFrameType = (WORD)_GetProtocol_FrameType(pCapBuffer->m_nProtocol);
// // 
// // 	if (nFrameType == 0)
// // 	{
// // 		strText = _T("����ı���");
// // 	}
// // 	else if (nFrameType == (CLASSID_101_TFRAME_E5 & 0x0FF))
// // 	{
// // 		strText = _T("������ʱ�ı�׼�ظ�");
// // 	}
// // 	else if (nFrameType == (CLASSID_101_TFRAME_10 & 0x0FF))
// // 	{
// // 		strText = _T("�̶����ȱ���֡");
// // 	}
// // 	else if (nFrameType == (CLASSID_104_TFRAME_68_S & 0x0FF))
// // 	{
// // 		strText = _T("S��ʽ����");
// // 	}
// // 	else if (nFrameType == (CLASSID_104_TFRAME_68_U & 0x0FF))
// // 	{
// // 		strText = _T("U��ʽ����");
// // 	}
// // 	else
// // 	{
// // 		switch (pCapBuffer->m_nDeviceDataType)
// // 		{
// // 		case _DEVICE_DATA_YC:
// // 			strText = _T("ң�ⱨ��");
// // 			break;
// // 		case _DEVICE_DATA_YX:
// // 			strText = _T("ң�ű���");
// // 			break;
// // 		case _DEVICE_DATA_YT:
// // 			strText = _T("ң������");
// // 			break;
// // 		case _DEVICE_DATA_EMPTY:
// // 			strText = _T("");
// // 			break;
// // 		case _DEVICE_DATA_YK:
// // 			strText = _T("ң�ر���");
// // 			break;
// // 		}
// // 
// // 		strText.AppendFormat(_T("(ASDU %02X)"), _GetProtocol_FrameType(pCapBuffer->m_nProtocol));
// // 
// // 		if (_GetProtocol_ProtoType(pCapBuffer->m_nProtocol) == PROTOCOL_101)
// // 		{
// // 			strText += _T(" (101)");
// // 		}
// // 		else
// // 		{
// // 			strText += _T(" (104)");
// // 		}
// // 	}
// }

// BOOL CCapListCtrlEx::GetItemTextBuffer(CFrameMemBuffer *pCapBuffer,CString &strText)
// {
// 
// 	CCycleMemBuffer *pCycleBuffer = (CCycleMemBuffer*)pCapBuffer->GetRecordBuffer();
// 	long nLen = 0;
// 	nLen = pCycleBuffer->GetDataLength();
// 	BYTE *pBuffer = pCycleBuffer->GetBuffer();
// 	return Txt_GetItemTextBuffer(pBuffer, nLen, strText);
// 
// 	return TRUE;
// }

BOOL CCapListCtrlEx::GetItemText(CFrameMemBuffer *pCapBuffer, long nSubItem, CString &strText)
{
	strText.Empty();

	if (pCapBuffer == NULL)
	{
		return FALSE;
	}

	switch (nSubItem)
	{
	case 0://Index
#ifdef FrameMemBuffer_use_FrameID
		strText.Format(_T("%I64u"), pCapBuffer->m_n64FrameID);
#else
	strText.Format(_T("%I64u"), m_n64FrameID);
	m_n64FrameID++;
#endif
		break;

	case 1:
		strText.Format(_T("%f"), pCapBuffer->m_oCapBufferItem.Time - m_dBeginTime);;
		break;

	case 2:	
		{
			BYTE *val = pCapBuffer->m_oCapBufferItem.addr_61850.srcMac;
			strText.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), val[0], val[1], val[2], val[3], val[4], val[5]);
		}

		break;

	case 3:
		{
			BYTE *val = pCapBuffer->m_oCapBufferItem.addr_61850.dstMac;
			strText.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), val[0], val[1], val[2], val[3], val[4], val[5]);
		}
		break;

	case 4:
		strText.Format(_T("%.4X"), pCapBuffer->m_oCapBufferItem.addr_61850.APPID);
		break;

	case 5:
		{
			switch (pCapBuffer->m_oCapBufferItem.nProtocol)
			{
			case PROTOCOL_61850_TYPE_92:
				strText = _T("SMV9-2");
				break;
			case PROTOCOL_61850_TYPE_91:
				strText = _T("SMV9-1");
				break;
			case PROTOCOL_61850_TYPE_60448:
				strText = _T("SMV6044-8");
				break;
			case PROTOCOL_61850_TYPE_GOOSE:
				strText = _T("GOOSE");
				break;
			default:
				strText = _T("error");
			}
		}
		break;
	default:
		break;
	}

	return TRUE;
}

void CCapListCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	/*CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right = rcClient.left+cx;
	rcClient.bottom = rcClient.top+cy;

	if (m_hWnd != NULL)
	{
		MoveWindow(rcClient);
	}*/
}

void CCapListCtrlEx::CreateWatch(CRect rc, CWnd *pParent)
{
	// TODO:  �ڴ������ר�õĴ�������
	CRect rectDummy;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT | LVS_OWNERDATA;

	Create(dwStyle, rc, pParent, ID_CAP_LISTCTRL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	InsertColumn(0, _T("���"), LVCFMT_LEFT, 80);
	InsertColumn(1, _T("ʱ��"), LVCFMT_LEFT, 100);
	InsertColumn(2, _T("ԴMAC"), LVCFMT_LEFT, 120);
	InsertColumn(3, _T("Ŀ��MAC"), LVCFMT_LEFT, 120);
	InsertColumn(4, _T("AppID"), LVCFMT_LEFT, 80);
	InsertColumn(5, _T("����"), LVCFMT_LEFT, 80);
	InsertColumn(6, _T("������Ϣ"), LVCFMT_LEFT, 300);

// 	SetColumnWidth(0, 200);
// 	SetColumnWidth(1, 120);
// 	SetColumnWidth(2, 120);
// 	SetColumnWidth(3, 100);
// 	SetColumnWidth(4, 200);
// 	SetColumnWidth(5, 300);

}

LRESULT CCapListCtrlEx::OnShowWatch(WPARAM wParam, LPARAM lParam)
{
	long nBufferIndex = m_pFrameMemBufferMngr->GetCurrIndex();
	long nBufferCount = m_pFrameMemBufferMngr->GetCurrCount();
	long nBufferMax = m_pFrameMemBufferMngr->GetMaxCount();
	m_nViewCurrCount = nBufferCount;
	m_nViewCurrIndex = nBufferIndex;

	if (nBufferCount == 0)
	{
		return 0;
	}

	if (m_bFirstTime )
	{
		m_dBeginTime = m_pFrameMemBufferMngr->GetCapBeginTime();
		m_bFirstTime = FALSE;
	}

	if (m_nViewCurrCount == nBufferMax)
	{
		Invalidate(FALSE);
	}
	else
	{
		SetItemCountEx(m_nViewCurrCount);
		//EnsureVisible(m_nViewCurrCount, TRUE);
		EnsureVisible(m_nViewCurrCount-1,FALSE);
	}
// 	if (nBufferCount == nBufferMax)
// 	{
// 		Invalidate(FALSE);
// 	}
// 	else
// 	{
// 	}


	return 0;
}

void CCapListCtrlEx::ExitCap()
{
	m_nViewCurrCount = 0;
	m_nViewCurrIndex = 0;
	DeleteAllItems();
	long nCount = GetItemCount();
}

void CCapListCtrlEx::SetFrameMemBufferMngr(CFrameMemBufferMngr *pFrameMemBufferMngr)
{
	m_pFrameMemBufferMngr = pFrameMemBufferMngr;
	CAP_SPY_MAX_COUNT = m_pFrameMemBufferMngr->GetMaxCount();
	m_nViewCurrIndex = 0;
	m_nViewCurrCount = 0;
	m_dBeginTime = 0;
	m_bFirstTime = TRUE;
	SetItemCount(0);
}


LRESULT CCapListCtrlEx::OnShowWatchs(WPARAM wParam, LPARAM lParam)
{
	if (m_nAddNew == 0)
	{
		return 0;
	}

//	SetItemCount(m_nCurrCount);
	long nCount = GetItemCount();
	long nCurrCount = m_nViewCurrCount;
	long nIndex = 0;
	long nTempCount = nCurrCount - nCount;
	
	for (nIndex=0; nIndex<nTempCount; nIndex++)
	{
		InsertItem(nCount + nIndex, _T(""));
	}

	if (m_nViewCurrCount > 0)
	{
		EnsureVisible(m_nViewCurrCount-1,FALSE);	
	}

	if (nTempCount == 0)
	{
		Invalidate(FALSE);
	}

	m_nAddNew = 0;

	return 0;
}


void CCapListCtrlEx::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	PostItemSelChangeMsg();
	*pResult = 0;
}

void CCapListCtrlEx::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	PostItemSelChangeMsg();
	*pResult = 0;
}

void CCapListCtrlEx::OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostItemSelChangeMsg();

	*pResult = 0;
}

void CCapListCtrlEx::PostItemSelChangeMsg()
{
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		long nSel = GetNextSelectedItem(pos);
		CFrameMemBuffer *pBuffer = m_pFrameMemBufferMngr->GetFrameBuffer(nSel);
		GetParent()->PostMessage(WM_CAPLIST_ITEM_SEL, nSel, (DWORD)pBuffer);
	}
}
