#include "StdAfx.h"
#include "EditDialogInterfaceList.h"


//////////////////////////////////////////////////////////////////////////
//CEditDialogInterfaceList

CEditDialogInterfaceList::CEditDialogInterfaceList()
{
	m_pCurrEditDialog = NULL;
}

CEditDialogInterfaceList::~CEditDialogInterfaceList(void)
{
	RemoveAll();
}

BOOL CEditDialogInterfaceList::GetModified()
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	BOOL bModified = FALSE;
	
	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		bModified |= pEditInterface->GetModified();
	}	
	
	return bModified;
}

void CEditDialogInterfaceList::CreateEdit(CExBaseObject* pObj, CWnd* pParent)
{
	CEditDialogInterface::CreateEdit(pObj, pParent);
};

void CEditDialogInterfaceList::Show()
{
	if (m_pEditDialog != NULL)
	{
		CEditDialogInterface::Show();
	}
}

void CEditDialogInterfaceList::Hide()
{
	if (m_pEditDialog != NULL)
	{
		CEditDialogInterface::Hide();
	}
}

void CEditDialogInterfaceList::AdjustSize(const CRect &rect)
{
	if (m_pEditDialog != NULL)
	{
		CEditDialogInterface::AdjustSize(rect);
	}
	else
	{
	}
}

BOOL CEditDialogInterfaceList::Save()
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	BOOL bTrue = TRUE;
	
	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		bTrue &= pEditInterface->Save();
	}

	return bTrue;
}

BOOL CEditDialogInterfaceList::ShowObject(CExBaseObject* pObj)
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	BOOL bTrue = TRUE;
	
	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		bTrue &= pEditInterface->ShowObject(pObj);
	}

	return bTrue;
}

CSize CEditDialogInterfaceList::GetChildrenSize()
{
	CSize szMax(0, 0);
	CSize sz(0, 0);

	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		sz = pEditInterface->GetSize();
		szMax.cx = max(szMax.cx, sz.cx);
		szMax.cy = max(szMax.cy, sz.cy);
	}

	return szMax;
}

CSize CEditDialogInterfaceList::GetSize()
{
	CSize szMax = GetChildrenSize();
	CSize sz =  CEditDialogInterface::GetSize();
	szMax.cx = max(szMax.cx, sz.cx);
	szMax.cy = max(szMax.cy, sz.cy);

	return szMax;
}

BOOL CEditDialogInterfaceList::ShowObject()
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		bTrue &= pEditInterface->ShowObject();
	}

	return bTrue;
}


CEditDialogInterface* CEditDialogInterfaceList::FindByClassID(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	CEditDialogInterface *pFind = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);
		
		if (pEditInterface->IsClassIDObject(nClassID))
		{
			pFind = pEditInterface;
			break;
		}
	}

	return pFind;
}

void CEditDialogInterfaceList::ShowChildObject(CExBaseObject *pObject, CWnd *pParent)
{
	UINT nClassID = pObject->GetClassID();
	CEditDialogInterface *pFind = FindByClassID(nClassID);

	if (pFind == NULL)
	{
		pFind = CreateChildEdit(nClassID, pParent);
		AddTail(pFind);
	}

	ASSERT( pFind != NULL);

	if (pFind == NULL)
	{
		return;
	}

	if (m_pCurrEditDialog != pFind)
	{
		m_pCurrEditDialog->Hide();
		m_pCurrEditDialog = pFind;
	}

	m_pCurrEditDialog->ShowObject(pObject);
	m_pCurrEditDialog->Show();
}

//////////////////////////////////////////////////////////////////////////
//CEditDialogInterfaces

CEditDialogInterfaces::CEditDialogInterfaces()
{
	m_pCurrEditDlg = NULL;
}

CEditDialogInterfaces::~CEditDialogInterfaces(void)
{
	
}

void CEditDialogInterfaces::DeleteEditDialogs()
{
	m_pCurrEditDlg = NULL;

// 	POS pos = GetHeadPosition();
// 	CEditDialogInterface *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 		p->DeleteEditDialog();
// 	}

	DeleteAll();
}

CEditDialogInterface* CEditDialogInterfaces::FindByClassID(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CEditDialogInterface *pEditInterface = NULL;
	CEditDialogInterface *pFind = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pEditInterface = GetNext(pos);

		if (pEditInterface->IsClassIDObject(nClassID))
		{
			pFind = pEditInterface;
			break;
		}
	}

	return pFind;
}



void CEditDialogInterfaces::ShowEditDlg(CExBaseObject *pObj, CWnd *pParentWnd)
{
	if (pObj == NULL)
	{
		if (m_pCurrEditDlg != NULL)
		{
			m_pCurrEditDlg->Hide();
			m_pCurrEditDlg->ShowObject(NULL);
			m_pCurrEditDlg = NULL;
		}

		return;
	}

	UINT nClassID = pObj->GetClassID();
	CEditDialogInterface *pFind = FindByClassID(nClassID);

	if (pFind == NULL)
	{
		pFind = CreateEditDialog(nClassID);

		if (pFind != NULL)
		{
			pFind->CreateEdit(pObj, pParentWnd);
			AddTail(pFind);
		}
	}

	if (pFind != m_pCurrEditDlg)
	{
		if (m_pCurrEditDlg != NULL)
		{
			m_pCurrEditDlg->Hide();
			m_pCurrEditDlg->ShowObject(NULL);
		}

		m_pCurrEditDlg = pFind;

		if (m_pCurrEditDlg != NULL)
		{
			m_pCurrEditDlg->ShowObject(pObj);
			m_pCurrEditDlg->Show();
		}
	}
	else
	{
		if (m_pCurrEditDlg != NULL)
		{
			m_pCurrEditDlg->ShowObject(pObj);
		}
	}
}

