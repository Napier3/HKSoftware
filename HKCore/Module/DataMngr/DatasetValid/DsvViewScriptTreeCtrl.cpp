// DsvViewScriptTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "DsvViewScriptTreeCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CDsvViewScriptTreeCtrl

IMPLEMENT_DYNAMIC(CDsvViewScriptTreeCtrl, CTreeCtrl)

CDsvViewScriptTreeCtrl::CDsvViewScriptTreeCtrl()
{

}

CDsvViewScriptTreeCtrl::~CDsvViewScriptTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CDsvViewScriptTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDsvViewScriptTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CDsvViewScriptTreeCtrl 消息处理程序



void CDsvViewScriptTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	CExBaseObject *pSel = (CExBaseObject *)pNMTreeView->itemNew.lParam;

	if (pSel == NULL)
	{
		return;
	}

	if (dsv_IsElement(pSel))
	{
		CDsvElement *pDsvElement = (CDsvElement*)pSel;
		m_pDatasetListCtrl->ViewDsvElement(pDsvElement);
		//pDataset->InsertChildToListCtrl(m_pDatasetListCtrl, 0);
	}

	*pResult = 0;
}

void CDsvViewScriptTreeCtrl::ShowDsvObjects(CExBaseList *pList, HTREEITEM hParent)
{
	POS pos = pList->GetHeadPosition();
	CDsvBase *p = NULL;
	HTREEITEM hItem = NULL;
	CString strText;
	UINT nImg = 0;

	while (pos != NULL)
	{
		p = (CDsvBase*)pList->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDSVELIMINATE)
		{
			continue;
		}

		strText = p->GetText();
		nImg = 2;

		if (p->IsElement())
		{
			if (!p->IsValidateSucc())
			{
				nImg = 3;
			}
		}

		hItem = InsertItem(strText, nImg, nImg, hParent);
		SetItemData(hItem, (DWORD)p);

		if (!p->IsElement())//if (p->GetClassID() != DVMCLASSID_CDSVELEMENT)
		{
			ShowDsvObjects((CExBaseList*)p, hItem);
		}
	}
}

void CDsvViewScriptTreeCtrl::ShowDsvScript(CDsvScript *pDsvScript)
{
	ShowDsvObjects(pDsvScript, TVI_ROOT);
}

void CDsvViewScriptTreeCtrl::SetImageListBmp(UINT nImageList)
{
	if (nImageList == 0)
	{
		return;
	}

	m_oImageList.DeleteImageList();
	m_oImageList.Create(nImageList, 16, 16, RGB(0, 255, 0));
	SetImageList(&m_oImageList, TVSIL_NORMAL);
}

