// D:\WorkSun\Source\61850\Module\SCL\UI\SclIecCfgTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SclCCTreeCtrl.h"

#include "..\..\SclFileTest\SCLCompareCheckDev.h"
// CSclCCTreeCtrl

IMPLEMENT_DYNAMIC(CSclCCTreeCtrl, CTreeCtrl)

CSclCCTreeCtrl::CSclCCTreeCtrl()
{
	m_bCanPostSelChangeMsg = FALSE;
	m_pSvInMsgRcvWnd = NULL;
	m_pSvOutMsgRcvWnd = NULL;
	m_pGsInMsgRcvWnd = NULL;
	m_pGsOutMsgRcvWnd = NULL;
	m_pRptCtrlMsgRcvWnd = NULL;
	m_pLogCtrlMsgRcvWnd = NULL;
	m_pDataSetMsgRcvWnd = NULL;
	m_pSclIedList = NULL;
	m_pCurrSelIed = NULL;
	

	m_nTreeViewIndex = 3;
}

CSclCCTreeCtrl::~CSclCCTreeCtrl()
{
}

void CSclCCTreeCtrl::SetIDB_SclData(UINT nIDB)
{
	m_imgSclData.Create(nIDB, 16, 0, RGB(255, 0, 0));
	SetImageList(&m_imgSclData, TVSIL_NORMAL);
}

void CSclCCTreeCtrl::SetCurrIedID(const CString &strIedID)
{
	m_strCurrIedID = strIedID;
	m_strCurrIedID.MakeLower();
}

BEGIN_MESSAGE_MAP(CSclCCTreeCtrl, CTreeCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSclCCTreeCtrl::OnTvnSelchanged)

	ON_UPDATE_COMMAND_UI(SCLFILE_TREECTRL_MNGRVIEW_NATURAL, &CSclCCTreeCtrl::OnUpdateNaturalGroupShow)
	ON_COMMAND(SCLFILE_TREECTRL_MNGRVIEW_NATURAL, &CSclCCTreeCtrl::OnNaturalGroupShow)
	ON_UPDATE_COMMAND_UI(SCLFILE_TREECTRL_MNGRVIEW_VOLLEVEL, &CSclCCTreeCtrl::OnUpdateVolLevelShow)
	ON_COMMAND(SCLFILE_TREECTRL_MNGRVIEW_VOLLEVEL, &CSclCCTreeCtrl::OnVolLevelShow)
	ON_UPDATE_COMMAND_UI(SCLFILE_TREECTRL_MNGRVIEW_DVMTYPE, &CSclCCTreeCtrl::OnUpdateDvmTypeShow)
	ON_COMMAND(SCLFILE_TREECTRL_MNGRVIEW_DVMTYPE, &CSclCCTreeCtrl::OnDvmTypeShow)
	ON_UPDATE_COMMAND_UI(SCLFILE_TREECTRL_MNGRVIEW_VOLANDDVM, &CSclCCTreeCtrl::OnUpdateVolAndDvmShow)
	ON_COMMAND(SCLFILE_TREECTRL_MNGRVIEW_VOLANDDVM, &CSclCCTreeCtrl::OnVolAndDvmShow)

END_MESSAGE_MAP()



// CSclCCTreeCtrl 消息处理程序
void CSclCCTreeCtrl::Filter(const CString &strText)
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

void CSclCCTreeCtrl::ShowIecfgSclIeds(CExBaseList *pList)
{	
	m_bCanPostSelChangeMsg = FALSE;
	LockWindowUpdate();
	DeleteAllItems();
	m_pSclIedList = pList;
	
	if (m_nTreeViewIndex == 0)
	{
		ShowSclObj(m_pSclIedList, TVI_ROOT);
	}
	else if (m_nTreeViewIndex == 1)
	{
		ShowSclObjByVolLevel(m_pSclIedList, TVI_ROOT);
	}
	else if (m_nTreeViewIndex == 2)
	{
		ShowSclObjByDvmType(m_pSclIedList, TVI_ROOT);
	} 
	else if (m_nTreeViewIndex == 3)
	{
		ShowSclObjByVolAndDvm(m_pSclIedList, TVI_ROOT);	
	}

	UnlockWindowUpdate();
	
	POS pos = m_pSclIedList->GetHeadPosition();
	CExBaseList *p = NULL;
	CExBaseList *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList *)m_pSclIedList->GetNext(pos);

		if (p->m_dwReserved == 0)
		{
			continue;
		}

		pFind = (CExBaseList *)p->GetHead();

		if (pFind != NULL)
		{
			Expand((HTREEITEM)p->m_dwItemData, TVE_EXPAND);
			break;
		}
	}

	m_bCanPostSelChangeMsg = TRUE;

	if (m_pCurrSelIed != NULL)//此部分代码用于保证至少选中一个IED
	{
		SelectItem((HTREEITEM)m_pCurrSelIed->m_dwItemData);
	}
	else
	{
		if (pFind != NULL)
		{
			SelectItem((HTREEITEM)p->m_dwItemData);
		}
	}

}

CString CSclCCTreeCtrl::GetSclObjName(CExBaseObject *pSclObj, UINT &nClassID)
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

		return strName;
	}
	else
	{
		return pSclObj->m_strName;
	}
}

void CSclCCTreeCtrl::ShowSclObj(CExBaseList *pList, HTREEITEM hParent)
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
		hItem = InsertItem(strName, nClassID-1, nClassID, hParent);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
	}
}

void CSclCCTreeCtrl::ShowSclObjByVolLevel(CExBaseList *pList, HTREEITEM hParent)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	HTREEITEM hItem = NULL;
	long nIndex[9];         //0:750kV   1:500kV    2:330kV       3:220kV      4:110kV      5:66kV      6:35kV      7:10kV      8:Other
	HTREEITEM hItemNO[9];
 
	int nTmp = 0;

	for( ; nTmp<9 ; nTmp++ )
	{
		nIndex[nTmp] = 0;
		hItemNO[nTmp] = NULL;
	}
	
	UINT nClassID = 0;
	
	hItemNO[0] = InsertItem(_T("750kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[0], (DWORD)pList);

	hItemNO[1] = InsertItem(_T("500kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[1], (DWORD)pList);

	hItemNO[2] = InsertItem(_T("330kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[2], (DWORD)pList);

	hItemNO[3] = InsertItem(_T("220kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[3], (DWORD)pList);

	hItemNO[4] = InsertItem(_T("110kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[4], (DWORD)pList);

	hItemNO[5] = InsertItem(_T("66kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[5], (DWORD)pList);

	hItemNO[6] = InsertItem(_T("35kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[6], (DWORD)pList);

	hItemNO[7] = InsertItem(_T("10kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[7], (DWORD)pList);
	
	hItemNO[8] = InsertItem(_T("其它"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[8], (DWORD)pList);

	CString strName ,strTemp;
	CString strVoltage;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if( !CanInsert(p) )
		{
			continue;
		}

		nClassID = p->GetOwnClassID();
		strName = GetSclObjName(p, nClassID);
		strTemp = strName;
		strTemp.MakeLower();
		strVoltage = p->m_strID;

		if ((strVoltage.Find(_T("75")) == 2)||(strTemp.Find(_T("750kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[0]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[0]++;
		} 
		else if ((strVoltage.Find(_T("50")) == 2)||(strTemp.Find(_T("500kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[1]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[1]++;
		} 
		else if ((strVoltage.Find(_T("33")) == 2)||(strTemp.Find(_T("330kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[2]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[2]++;
		}
		else if ((strVoltage.Find(_T("22")) == 2)||(strTemp.Find(_T("220kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[3]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[3]++;
		}
		else if ((strVoltage.Find(_T("11")) == 2)||(strTemp.Find(_T("110kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[4]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[4]++;
		}
		else if ((strVoltage.Find(_T("66")) == 2)||(strTemp.Find(_T("66kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[5]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[5]++;
		}
		else if ((strVoltage.Find(_T("35")) == 2)||(strTemp.Find(_T("35kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[6]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[6]++;
		}
		else if ((strVoltage.Find(_T("10")) == 2)||(strTemp.Find(_T("10kv")) != -1))
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[7]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[7]++;
		}
		else
		{
			hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemNO[8]);
			SetItemData(hItem, (DWORD)p);
			p->m_dwItemData = (DWORD)hItem;
			nIndex[8]++;
		}
	}

	for( nTmp = 0 ; nTmp<9 ; nTmp++ )
	{
		if ( nIndex[nTmp] == 0 )
		{
			DeleteItem(hItemNO[nTmp]);
		}
	}
}


void CSclCCTreeCtrl::ShowSclObjByDvmType(CExBaseList *pList, HTREEITEM hParent)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nIndex[5];         //0:合并单元   1:保护装置    2:测控装置       3:智能终端      4:其它装置   
	HTREEITEM hItemNO[5];

	int nTmp = 0;

	for( ; nTmp<5 ; nTmp++ )
	{
		nIndex[nTmp] = 0;
		hItemNO[nTmp] = NULL;
	}

	UINT nClassID = 0;

	InsertItemByDevice( hParent , hItemNO ,pList );

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if( !CanInsert(p) )
		{
			continue;
		}

		InsertItemByVoltage( p ,hItemNO ,nIndex);
	}

	for( nTmp = 0 ; nTmp<5 ; nTmp++ )
	{
		if ( nIndex[nTmp] == 0 )
		{
			DeleteItem(hItemNO[nTmp]);
		}
	}
}

void CSclCCTreeCtrl::ShowSclObjByVolAndDvm(CExBaseList *pList, HTREEITEM hParent)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	HTREEITEM hItem = NULL;
	long nIndex[9][5];         //0:750kV   1:500kV    2:330kV       3:220kV      4:110kV      5:66kV      6:35kV      7:10kV      8:Other
	HTREEITEM hItemNO[9];
	HTREEITEM hItemDvm[9][5];

	int nTmp = 0;
	int nDvm = 0;

	for( ; nTmp<9 ; nTmp++ )
	{
		hItemNO[nTmp] = NULL;

		for ( nDvm = 0 ; nDvm <5 ; nDvm++ )
		{
			nIndex[nTmp][nDvm] = 0;
			hItemDvm[nTmp][nDvm] = NULL;
		}
	}

	UINT nClassID = 0;

	hItemNO[0] = InsertItem(_T("750kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[0], (DWORD)pList);
	InsertItemByDevice( hItemNO[0] , hItemDvm[0] ,pList );

	hItemNO[1] = InsertItem(_T("500kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[1], (DWORD)pList);
	InsertItemByDevice( hItemNO[1] , hItemDvm[1] ,pList );

	hItemNO[2] = InsertItem(_T("330kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[2], (DWORD)pList);
	InsertItemByDevice( hItemNO[2] , hItemDvm[2] ,pList );

	hItemNO[3] = InsertItem(_T("220kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[3], (DWORD)pList);
	InsertItemByDevice( hItemNO[3] , hItemDvm[3] ,pList );

	hItemNO[4] = InsertItem(_T("110kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[4], (DWORD)pList);
	InsertItemByDevice( hItemNO[4] , hItemDvm[4] ,pList );

	hItemNO[5] = InsertItem(_T("66kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[5], (DWORD)pList);
	InsertItemByDevice( hItemNO[5] , hItemDvm[5] ,pList );

	hItemNO[6] = InsertItem(_T("35kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[6], (DWORD)pList);
	InsertItemByDevice( hItemNO[6] , hItemDvm[6] ,pList );

	hItemNO[7] = InsertItem(_T("10kV电压等级"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[7], (DWORD)pList);
	InsertItemByDevice( hItemNO[7] , hItemDvm[7] ,pList );

	hItemNO[8] = InsertItem(_T("其它"), nClassID, nClassID + 1, hParent);
	SetItemData(hItemNO[8], (DWORD)pList);
	InsertItemByDevice( hItemNO[8] , hItemDvm[8] ,pList );

	CString strTemp;
	CString strVoltage;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if( !CanInsert(p) )
		{
			continue;
		}

		nClassID = p->GetOwnClassID();
		strTemp = GetSclObjName(p, nClassID);
		strTemp.MakeLower();
		strVoltage = p->m_strID;

		if ((strVoltage.Find(_T("75")) == 2)||(strTemp.Find(_T("750kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[0] ,nIndex[0]);
		} 
		else if ((strVoltage.Find(_T("50")) == 2)||(strTemp.Find(_T("500kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[1] ,nIndex[1]);
		} 
		else if ((strVoltage.Find(_T("33")) == 2)||(strTemp.Find(_T("330kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[2] ,nIndex[2]);
		}
		else if ((strVoltage.Find(_T("22")) == 2)||(strTemp.Find(_T("220kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[3] ,nIndex[3]);
		}
		else if ((strVoltage.Find(_T("11")) == 2)||(strTemp.Find(_T("110kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[4] ,nIndex[4]);
		}
		else if ((strVoltage.Find(_T("66")) == 2)||(strTemp.Find(_T("66kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[5] ,nIndex[5]);
		}
		else if ((strVoltage.Find(_T("35")) == 2)||(strTemp.Find(_T("35kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[6] ,nIndex[6]);
		}
		else if ((strVoltage.Find(_T("10")) == 2)||(strTemp.Find(_T("10kv")) != -1))
		{
			InsertItemByVoltage( p  ,hItemDvm[7] ,nIndex[7]);
		}
		else
		{
			InsertItemByVoltage( p  ,hItemDvm[8] ,nIndex[8]);
		}
	}

	for( nTmp = 0 ; nTmp<9 ; nTmp++ )
	{
		for (nDvm = 0; nDvm <5; nDvm++ )
		{
			if ( nIndex[nTmp][nDvm] == 0 )
			{
				DeleteItem(hItemDvm[nTmp][nDvm]);
			}
		}
		if ( (nIndex[nTmp][0] + nIndex[nTmp][1] + nIndex[nTmp][2] + nIndex[nTmp][3] + nIndex[nTmp][4] ) == 0 )
		{
			DeleteItem(hItemNO[nTmp]);
		}
	}
}

BOOL CSclCCTreeCtrl::CanInsert(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	BOOL bCan = CanInsert(nClassID);

	if (bCan && (nClassID == SCLIECCLASSID_IED))
	{
		bCan = (pObj->m_dwReserved != 0);
	}

	return bCan;
}

BOOL CSclCCTreeCtrl::CanInsert(UINT nClassID)
{
	if ((nClassID == SCLIECCLASSID_IED)  )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSclCCTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bCanPostSelChangeMsg)
	{
		return;
	}

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//这是一个类型转换和赋值的语句,是把 NMHDR * 类型的变量 pNMHDR 的值转换成 LPNMTREEVIEW 类型,并赋值给 变量 pNMTreeView 。reinterpret_cast 是将 pNMHDR 值不进行任何改变
	//的赋给变量 pNMTreeView ，或者说是一种强制型的类型转换。
	
	DWORD   dwpos = GetMessagePos();   
	HTREEITEM hItem = GetSelectedItem();

	if (hItem == NULL)
	{
		return;
	}

	CExBaseList *pSel = (CExBaseList *)GetItemData(hItem);

	if (pSel == NULL)
	{
		*pResult = 0;
		return;
	}

	if (pSel->GetClassID() == SCLIECCLASSID_IED)
	{
		UpdateTabForm(pSel);
		theApp.UpdateScdDrawIedByID(pSel->m_strID);
	}

	*pResult = 0;
}

void CSclCCTreeCtrl::UpdateTabForm(CExBaseList *pSel )
{
	POS pos = pSel->GetHeadPosition();

	CExBaseList *pCurrSelCtrls;

	while(pos != NULL)
	{
		pCurrSelCtrls = (CExBaseList *)pSel->GetNext(pos);
		ASSERT( m_pSvInMsgRcvWnd != NULL);

		if ((m_pSvInMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==SCLIECCLASSID_CTRLS_SMV_IN))
		{
			m_pSvInMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 2);
		}

		ASSERT( m_pSvOutMsgRcvWnd != NULL);

		if ((m_pSvOutMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==SCLIECCLASSID_CTRLS_SMV_OUT))
		{
			m_pSvOutMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls,3);
		}

		ASSERT( m_pGsInMsgRcvWnd != NULL);

		if ((m_pGsInMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==SCLIECCLASSID_CTRLS_GS_IN))
		{
			m_pGsInMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 4);
		}

		ASSERT( m_pGsOutMsgRcvWnd != NULL);

		if ((m_pGsOutMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==SCLIECCLASSID_CTRLS_GS_OUT))
		{
			m_pGsOutMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 5);
		}

		ASSERT( m_pRptCtrlMsgRcvWnd != NULL);

		if ((m_pRptCtrlMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==DVMCLASSID_CDVMDEVICE))
		{
			m_pRptCtrlMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 6);
		}

		ASSERT( m_pLogCtrlMsgRcvWnd != NULL);

		if ((m_pLogCtrlMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==DVMCLASSID_CDVMDEVICE))
		{
			m_pLogCtrlMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 7);
		}

		ASSERT( m_pDataSetMsgRcvWnd != NULL);

		if ((m_pDataSetMsgRcvWnd != NULL)&&(pCurrSelCtrls->GetClassID()==DVMCLASSID_CDVMDEVICE))
		{
			m_pDataSetMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pCurrSelCtrls, 8);
		}
	}
}

void CSclCCTreeCtrl::InsertItemByDevice( HTREEITEM hItemNO , HTREEITEM *hItemDvm ,CExBaseList *pList )
{
	UINT nClassID = 0;

	hItemDvm[0] = InsertItem(_T("合并单元"), nClassID, nClassID + 1, hItemNO);
	SetItemData(hItemDvm[0], (DWORD)pList);

	hItemDvm[1] = InsertItem(_T("保护装置"), nClassID, nClassID + 1, hItemNO);
	SetItemData(hItemDvm[1], (DWORD)pList);

	hItemDvm[2] = InsertItem(_T("测控装置"), nClassID, nClassID + 1, hItemNO);
	SetItemData(hItemDvm[2], (DWORD)pList);

	hItemDvm[3] = InsertItem(_T("智能终端"), nClassID, nClassID + 1, hItemNO);
	SetItemData(hItemDvm[3], (DWORD)pList);

	hItemDvm[4] = InsertItem(_T("其它装置"), nClassID, nClassID + 1, hItemNO);
	SetItemData(hItemDvm[4], (DWORD)pList);
}

void CSclCCTreeCtrl::InsertItemByVoltage( CExBaseObject *p  ,HTREEITEM *hItemDvm ,long *nIndex)
{
	HTREEITEM hItem = NULL;
	UINT nClassID = 0;
	nClassID = p->GetOwnClassID();
	CString strName ,strDevice;
	strName = GetSclObjName(p, nClassID);

	strDevice = p->m_strID;
	strDevice.MakeLower();

	if ((strDevice[0] == 'm')||(strName.Find(_T("合并单元")) != -1))
	{
		hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemDvm[0]);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
		nIndex[0]++;
	}
	else if ((strDevice[0] == 'i')||(strName.Find(_T("智能终端")) != -1))
	{
		hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemDvm[3]);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
		nIndex[3]++;
	}
	else if ((strDevice[0] == 'p')||(strName.Find(_T("保护")) != -1))
	{
		hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemDvm[1]);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
		nIndex[1]++;
	} 
	else if ((strDevice[0] == 'c')||(strName.Find(_T("测控")) != -1))
	{
		hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemDvm[2]);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
		nIndex[2]++;
	}
	else
	{
		hItem = InsertItem(strName, nClassID+3, nClassID+4, hItemDvm[4]);
		SetItemData(hItem, (DWORD)p);
		p->m_dwItemData = (DWORD)hItem;
		nIndex[4]++;
	}
}

void CSclCCTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	UINT uFlags;
	HTREEITEM hItem = HitTest(point,&uFlags);
	Select(hItem, TVGN_CARET);

	CExBaseObject* pObj = NULL;
	if( (hItem != NULL) && (TVHT_ONITEM & uFlags) )
	{
		pObj = (CExBaseObject*)GetItemData(hItem);
	}

	if(pObj != NULL)
	{
		OnContextMenuTree(NULL,point,pObj);
	}
}

void CSclCCTreeCtrl::OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pObj)
{
	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	CExBaseObject* pSel = (CExBaseObject*)GetSelObject();

	if(pSel != NULL)
	{
		InitContextMenuTree(menu, pSel);
		SetOwner(m_pViewWnd);

		if (menu.GetMenuItemCount() > 0)
		{
			//CUIWndThread::Attach_Wnd_WM_COMMAND(this);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y, this);
			//资源回收
			//CUIWndThread::Attach_Wnd_WM_COMMAND(NULL);
			HMENU hmenu=menu.Detach();			
			menu.DestroyMenu();	
		}
	}	
}

CExBaseObject* CSclCCTreeCtrl::GetSelObject()
{
	HTREEITEM hSel = GetSelectedItem();

	if (hSel == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hSel);
	return pSel;
}

void CSclCCTreeCtrl::InitContextMenuTree(CMenu &menu,CExBaseObject* pObj)
{
	SetFocus();

	UINT nClassID = pObj->GetClassID();

	if ((SCLIECCLASSID_STATION == nClassID)||(SCLIECCLASSID_IED == nClassID))
	{
		menu.AppendMenu(MF_STRING,SCLFILE_TREECTRL_MNGRVIEW_NATURAL,_T("自然分组显示"));
		menu.AppendMenu(MF_STRING,SCLFILE_TREECTRL_MNGRVIEW_VOLLEVEL,_T("电压等级分组"));
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,SCLFILE_TREECTRL_MNGRVIEW_DVMTYPE,_T("装置类型分组"));

		menu.AppendMenu(MF_STRING,SCLFILE_TREECTRL_MNGRVIEW_VOLANDDVM,_T("组合分组显示"));
	}

}

void CSclCCTreeCtrl::OnUpdateNaturalGroupShow(CCmdUI* pCmdUI)
{

	pCmdUI->Enable(TRUE);
}

void CSclCCTreeCtrl::OnNaturalGroupShow()
{
	m_nTreeViewIndex = 0;
	((CSclTreeCCView*)m_pViewWnd)->ShowVisualTree();
}

void CSclCCTreeCtrl::OnUpdateVolLevelShow(CCmdUI* pCmdUI)
{

	pCmdUI->Enable(TRUE);
}

void CSclCCTreeCtrl::OnVolLevelShow()
{
	m_nTreeViewIndex = 1;
	((CSclTreeCCView*)m_pViewWnd)->ShowVisualTree();
}

void CSclCCTreeCtrl::OnUpdateDvmTypeShow(CCmdUI* pCmdUI)
{

	pCmdUI->Enable(TRUE);
}

void CSclCCTreeCtrl::OnDvmTypeShow()
{
	m_nTreeViewIndex = 2;
	((CSclTreeCCView*)m_pViewWnd)->ShowVisualTree();
}

void CSclCCTreeCtrl::OnUpdateVolAndDvmShow(CCmdUI* pCmdUI)
{

	pCmdUI->Enable(TRUE);
}

void CSclCCTreeCtrl::OnVolAndDvmShow()
{
	m_nTreeViewIndex = 3;
	((CSclTreeCCView*)m_pViewWnd)->ShowVisualTree();
}