#include "stdafx.h"
#include "SclFileTreeCtrl.h"

#include "..\..\SclFileTest\SCLCompareCheckDev.h"


IMPLEMENT_DYNAMIC(CSclFileTreeCtrl, CTreeCtrl)

CSclFileTreeCtrl::CSclFileTreeCtrl()
{
	m_bCanPostSelChangeMsg = FALSE;

	m_nIEDNumber = 0;
	m_hIedItem = NULL;
	m_pTreeMsgRcvWnd = NULL;
}

CSclFileTreeCtrl::~CSclFileTreeCtrl()
{
}

void CSclFileTreeCtrl::SetIDB_SclData(UINT nIDB)
{
	m_imgSclData.Create(nIDB, 16, 0, RGB(255, 0, 0));
	SetImageList(&m_imgSclData, TVSIL_NORMAL);
}

BEGIN_MESSAGE_MAP(CSclFileTreeCtrl, CTreeCtrl)
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSclFileTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()

void CSclFileTreeCtrl::Filter(const CString &strText)
{
	UINT nMode = 0;

	ShowModelTree();
}

void CSclFileTreeCtrl::ShowModelTree()
{	
	m_bCanPostSelChangeMsg = FALSE;
	LockWindowUpdate();
	DeleteAllItems();

	ShowMainTreeCtrl();

	UnlockWindowUpdate();
	m_bCanPostSelChangeMsg = TRUE;
	return;

}

void CSclFileTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
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

	TiXmlElement *pSel = (TiXmlElement *)GetItemData(hItem);

	if (pSel == NULL)
	{
		*pResult = 0;
		return;
	}

	m_strNodeName = GetItemText(hItem);

	ASSERT(m_pTreeMsgRcvWnd != NULL);

	m_pTreeMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRLS_SELECTED, (WPARAM)pSel, (LPARAM)&m_strNodeName);
	
	*pResult = 0;
}

void CSclFileTreeCtrl::ShowMainTreeCtrl()
{
	pugi::xml_node oPugixmlRoot = theApp.GetPugixmlSourceRoot();

	CString nodeName = theApp.m_strSCLFilePath;
	long nIndex = nodeName.ReverseFind('\\');
	nodeName = nodeName.Mid(nIndex+1);

	TVINSERTSTRUCT tvInsert;	
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = TVI_LAST;	
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.lParam = NULL;

	tvInsert.item.pszText = (TCHAR*)(LPCTSTR)nodeName;
	HTREEITEM hItem = InsertItem(&tvInsert);

	pugi::xml_node oPugiChild = oPugixmlRoot.first_child();

	CString strName;

	while(oPugiChild != NULL)
	{
		strName = oPugiChild.name();
		if (strName != _T("Private") )
		{
			PopulateMainTreeCtrl(oPugiChild, hItem);
		}

		oPugiChild = oPugiChild.next_sibling();
	}

	MyExpandTree(this ,this->GetRootItem());
}

void CSclFileTreeCtrl::MyExpandTree(CTreeCtrl *pTreeCtrl ,HTREEITEM hTreeItem)
{
	if(!pTreeCtrl->ItemHasChildren(hTreeItem))
	{
		return;
	}
	HTREEITEM hNextItem = pTreeCtrl->GetChildItem(hTreeItem);
	while (hNextItem != NULL)
	{
		MyExpandTree( pTreeCtrl , hNextItem);
		hNextItem = pTreeCtrl->GetNextItem(hNextItem, TVGN_NEXT);
	}
	pTreeCtrl->Expand(hTreeItem,TVE_EXPAND);
}

void CSclFileTreeCtrl::PopulateMainTreeCtrl(pugi::xml_node oPugiNode, HTREEITEM hParent)
{
	CString nodeName;
	nodeName = oPugiNode.name();
	CString nodeValue;
	nodeValue = oPugiNode.value();

	CString nodeNameVal = nodeName;

	TVINSERTSTRUCT tvInsert;	
	tvInsert.hParent = hParent;
	tvInsert.hInsertAfter = TVI_LAST;	
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.lParam = NULL;	

	if (nodeNameVal == "Header")
	{
		tvInsert.item.pszText = "头文件";
		HTREEITEM hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
	}
	else if (nodeNameVal == "Substation")
	{
		tvInsert.item.pszText = "变电站";
		HTREEITEM hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
	}
	else if (nodeNameVal == "Communication")
	{
		tvInsert.item.pszText = "通讯网络";
		tvInsert.hParent = InsertItem(&tvInsert);

		nodeValue = "SubNetwork-";

		HTREEITEM hItem = NULL;
		pugi::xml_node oPugiChild = oPugiNode.first_child();
		CString strNode;

		while(oPugiChild != NULL)
		{
			strNode = oPugiChild.name();

			if(_tcscmp(strNode  ,"SubNetwork") != 0)//排除节点名称不是SubNetwork的节点
			{
				oPugiChild = oPugiChild.next_sibling();
				continue;
			}

			GetAttrNameAndDescValue(oPugiChild, &nodeNameVal);

			nodeNameVal = nodeValue + nodeNameVal;
			tvInsert.item.pszText = (TCHAR*)(LPCTSTR)nodeNameVal;
			hItem = InsertItem(&tvInsert);
			SetItemData(hItem ,(DWORD)(oPugiChild.internal_object()));

			oPugiChild = oPugiChild.next_sibling();
		}
	}
	else if (nodeNameVal == "IED")
	{
		if (m_nIEDNumber == 0)
		{
			tvInsert.item.pszText = "IED列表";
			m_hIedItem = InsertItem(&tvInsert);
			tvInsert.hParent = m_hIedItem;

			GetAttrNameAndDescValue(oPugiNode, &nodeNameVal);

			tvInsert.item.pszText = (TCHAR*)(LPCTSTR)nodeNameVal;
			HTREEITEM hItemChild = InsertItem(&tvInsert);
			SetItemData(hItemChild ,(DWORD)(oPugiNode.internal_object()));
			m_nIEDNumber++;
		} 
		else
		{
			GetAttrNameAndDescValue(oPugiNode, &nodeNameVal);

			tvInsert.hParent = m_hIedItem;

			tvInsert.item.pszText = (TCHAR*)(LPCTSTR)nodeNameVal;
			HTREEITEM hItemChild = InsertItem(&tvInsert);
			SetItemData(hItemChild ,(DWORD)(oPugiNode.internal_object()));
			m_nIEDNumber++;
		}
	}
	else if (nodeNameVal == "DataTypeTemplates")
	{
		tvInsert.item.pszText = "数据类型模板库";
		HTREEITEM hItem = InsertItem(&tvInsert);

		tvInsert.hParent = hItem;
		tvInsert.item.pszText = "LNodeType";
		hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
		tvInsert.item.pszText = "DOType";
		hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
		tvInsert.item.pszText = "DAType";
		hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
		tvInsert.item.pszText = "EnumType";
		hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
	}
	else
	{
		tvInsert.item.pszText = (TCHAR*)(LPCTSTR)nodeNameVal;
		HTREEITEM hItem = InsertItem(&tvInsert);
		SetItemData(hItem ,(DWORD)(oPugiNode.internal_object()));
	}
}

void CSclFileTreeCtrl::GetAttrNameAndDescValue(pugi::xml_node oPugiNode,CString *strAttrVal)
{
	CString strName , strDesc;
	strName = oPugiNode.attribute(L"name").value();
	strDesc = oPugiNode.attribute(L"desc").value();

	if (strDesc.IsEmpty())
	{
		*strAttrVal = strName;
	} 
	else
	{
		*strAttrVal = strDesc;
		*strAttrVal += "-";
		*strAttrVal += strName;
	}
}