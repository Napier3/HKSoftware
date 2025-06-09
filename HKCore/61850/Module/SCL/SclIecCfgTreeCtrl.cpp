// D:\WorkSun\Source\61850\Module\SCL\UI\SclIecCfgTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SclIecCfgTreeCtrl.h"


// CSclIecCfgTreeCtrl

IMPLEMENT_DYNAMIC(CSclIecCfgTreeCtrl, CTreeCtrl)

CSclIecCfgTreeCtrl::CSclIecCfgTreeCtrl()
{
	m_bCanPostSelChangeMsg = FALSE;
	m_pMsgRcvWnd = NULL;
	m_pCurrSelCtrls = NULL;
	m_pSclIedList = NULL;
	m_pCurrSelIed = NULL;
}

CSclIecCfgTreeCtrl::~CSclIecCfgTreeCtrl()
{
}

void CSclIecCfgTreeCtrl::SetIDB_SclData(UINT nIDB)
{
	m_imgSclData.Create(nIDB, 16, 0, RGB(255, 0, 0));
	SetImageList(&m_imgSclData, TVSIL_NORMAL);
}

void CSclIecCfgTreeCtrl::SetCurrIedID(const CString &strIedID)
{
	m_strCurrIedID = strIedID;
	m_strCurrIedID.MakeLower();
}

CSclIed* CSclIecCfgTreeCtrl::GetCurrSelIedEx()
{
	HTREEITEM hItem = GetSelectedItem();
	CSclIed *pIed = NULL;

	if (hItem != NULL)
	{
		pIed = (CSclIed *)GetItemData(hItem);

		if (pIed->GetClassID() != SCLIECCLASSID_IED)
		{
			pIed = (CSclIed *)pIed->GetAncestor(SCLIECCLASSID_IED);
		}
	}

	return pIed;
}

BEGIN_MESSAGE_MAP(CSclIecCfgTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSclIecCfgTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CSclIecCfgTreeCtrl 消息处理程序
void CSclIecCfgTreeCtrl::Filter(const CString &strText)
{
	UINT nMode = 0;

	if (strText.GetLength() == 0)
	{
		m_pSclIedList->Filter(strText, FILTERMODE_CLEAR);
	}
	else
	{
		m_pSclIedList->Filter(strText, FILTERMODE_HAS);
	}

	ShowIecfgSclIeds(m_pSclIedList);
}

void CSclIecCfgTreeCtrl::ShowIecfgSclIeds(CExBaseList *pList, BOOL bShowDetail)
{	
	m_bShowDetail = bShowDetail;
	m_bCanPostSelChangeMsg = FALSE;
	LockWindowUpdate();
	DeleteAllItems();
	m_pSclIedList = pList;
	ShowSclObj(m_pSclIedList, TVI_ROOT);
	UnlockWindowUpdate();
	
	POS pos = m_pSclIedList->GetHeadPosition();
	CExBaseList *p = NULL;
	CExBaseList *pFind = NULL;
	CSclIed *pSclIED = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList *)m_pSclIedList->GetNext(pos);

		if (p->GetClassID() != SCLIECCLASSID_IED)//zhouhj 20211027 确保该对象为IED对象
		{
			continue;
		}

		if (p->m_dwReserved == 0)
		{
			continue;
		}

		pSclIED = (CSclIed *)p;
		pFind = (CSclIed *)pSclIED->GetFirstCtrlObj();

		if (pFind != NULL)
		{
			Expand((HTREEITEM)p->m_dwItemData, TVE_EXPAND);
			break;
		}
	}

	m_bCanPostSelChangeMsg = TRUE;

	if (m_pCurrSelIed != NULL)
	{
		SelectItem((HTREEITEM)m_pCurrSelIed->m_dwItemData);
	}
	else
	{
		if (pFind != NULL)
		{
			SelectItem((HTREEITEM)pFind->m_dwItemData);
		}
		else
		{
			if (m_pMsgRcvWnd != NULL)
			{
				m_pMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)NULL, (LPARAM)NULL);
			}
		}
	}
}

void CSclIecCfgTreeCtrl::ShowSelectIED(const CString &strIedId)
{
	SetCurrIedID(strIedId);

	if (m_pSclIedList == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("当前SclIedList为空."));

		if (m_pMsgRcvWnd != NULL)
		{
			m_pMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)NULL, (LPARAM)NULL);
		}
		return;
	}

	m_pCurrSelIed = (CSclIed *)m_pSclIedList->FindByID(strIedId);

	if (m_pCurrSelIed == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("未找到【%s】对应IED."),strIedId);

		if (m_pMsgRcvWnd != NULL)
		{
			m_pMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)NULL, (LPARAM)NULL);
		}
		return;
	}

	SelectItem((HTREEITEM)m_pCurrSelIed->m_dwItemData);
}

CString CSclIecCfgTreeCtrl::GetSclObjName(CExBaseObject *pSclObj, UINT &nClassID)
{
	if (pSclObj->GetClassID() == SCLIECCLASSID_IED)
	{
		CString strName;
		CSclIed *pIed = (CSclIed*)pSclObj;

		if (pIed->m_strName == pIed->m_strID)
		{
			strName.Format(_T("%s [%s]"), pIed->m_strName, pIed->m_strModel);
		}
		else
		{
			strName.Format(_T("%s  [%s][%s]"), pIed->m_strName, pIed->m_strID, pIed->m_strModel);
		}

		CString strTemp;
		strTemp = pIed->m_strID;
		strTemp.MakeLower();

		if (strTemp == m_strCurrIedID)
		{
			m_pCurrSelIed = pIed;
			nClassID = 6;
		}
// 		if (pIed->m_strIP.GetLength() > 0)
// 		{
// 			strName.AppendFormat(_T("(%s)"), pIed->m_strIP);
// 		}

		return strName;
	}
	else
	{
		return pSclObj->m_strName;
	}
}

void CSclIecCfgTreeCtrl::ShowSclObj(CExBaseList *pList, HTREEITEM hParent)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	HTREEITEM hItem = NULL;
	UINT nClassID = 0;
	CString strName;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if ( !CanInsert(p) )
		{
			continue;
		}

		nClassID = p->GetOwnClassID();
		strName = GetSclObjName(p, nClassID);
		hItem = InsertItem(strName, nClassID, nClassID, hParent);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;

		ShowSclObj((CExBaseList*)p, hItem);
	}
}

BOOL CSclIecCfgTreeCtrl::CanInsert(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	BOOL bCan = CanInsert(nClassID);

	if (bCan && (nClassID == SCLIECCLASSID_IED))
	{
		bCan = (pObj->m_dwReserved != 0);
	}

	return bCan;
}

BOOL CSclIecCfgTreeCtrl::CanInsert(UINT nClassID)
{
	if ((nClassID == SCLIECCLASSID_IED) )
	{
		return TRUE;
	}

	if (   (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT) )
	{
		return m_bShowDetail;
	}
	else
	{
		return FALSE;
	}
}

void CSclIecCfgTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bCanPostSelChangeMsg)
	{
		return;
	}

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	DWORD   dwpos = GetMessagePos();   
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return;
	}

	CExBaseList *pSel = (CExBaseList *)GetItemData(hItem);

	if (pSel->GetClassID() == SCLIECCLASSID_IED)
	{
		if (m_bShowDetail)
		{
			HTREEITEM hChildItem = GetChildItem(hItem);

			if (hChildItem != NULL)
			{
				m_pCurrSelCtrls = (CExBaseList *)GetItemData(hItem);
				Expand(hItem,TVE_EXPAND);
				SelectItem(hChildItem); 
			}
		}
		else
		{
			if (m_pMsgRcvWnd != NULL)
			{
				m_pMsgRcvWnd->PostMessage(WM_SCLIECIED_SELECTED, (WPARAM)pSel, (LPARAM)pSel);
			}
		}
	}
	else
	{
		m_pCurrSelCtrls = (CExBaseList *)GetItemData(hItem);
		ASSERT( m_pMsgRcvWnd != NULL);


		if (m_pMsgRcvWnd != NULL)
		{
			m_pMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)m_pCurrSelCtrls, (LPARAM)m_pCurrSelCtrls);
		}
	}

	*pResult = 0;
}
