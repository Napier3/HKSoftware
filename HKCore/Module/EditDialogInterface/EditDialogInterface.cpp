#include "StdAfx.h"
#include "EditDialogInterface.h"


void CEditDialogInterface::AddEditDialog(CExBaseObject *pEditObj, CEditDialogInterface *pEditDialog)
{
	m_oEditDialogContainer.AddEditDialog(pEditObj, pEditDialog);
}

void CEditDialogInterface::AddEditDialog(UINT nClassID, CEditDialogInterface *pEditDialog)
{
	m_oEditDialogContainer.AddEditDialog(nClassID, pEditDialog);
}

CEditDialogInterface* CEditDialogInterface::Find(CExBaseObject *pEditObj)
{
	return m_oEditDialogContainer.Find(pEditObj);
}

CEditDialogInterface* CEditDialogInterface::Find(UINT nClassID)
{
	return m_oEditDialogContainer.Find(nClassID);
}

void CEditDialogInterface::DeleteEditDialog()
{
// 	if (m_pEditDialog != NULL)
// 	{
// 		m_pEditDialog->DestroyWindow();
// 		delete m_pEditDialog;
// 		m_pEditDialog = NULL;
// 	}
}

//////////////////////////////////////////////////////////////////////////
//CEditDialogInterfaceContainer
CEditDialogInterfaceContainer::CEditDialogInterfaceContainer()
{

}

CEditDialogInterfaceContainer::~CEditDialogInterfaceContainer()
{
	DeleteAll();
}

void CEditDialogInterfaceContainer::AddEditDialog(CExBaseObject *pEditObj, CEditDialogInterface *pEditDialog)
{
	UINT nClassID = pEditObj->GetClassID();
	AddEditDialog(nClassID, pEditDialog);
}

void CEditDialogInterfaceContainer::AddEditDialog(UINT nClassID, CEditDialogInterface *pEditDialog)
{
	CEditDialogInterface *pFind = Find(nClassID);

	if (pFind != NULL)
	{
		return;
	}

	insert(std::pair<UINT,CEditDialogInterface*>(nClassID, pEditDialog));
}

CEditDialogInterface* CEditDialogInterfaceContainer::Find(CExBaseObject *pEditObj)
{
	return Find(pEditObj->GetClassID());
}

CEditDialogInterface* CEditDialogInterfaceContainer::Find(UINT nClassID)
{
	if (empty())
	{
		return NULL;
	}

	CIterEditDialogInterface pFind = find(nClassID);

	if (pFind == end())
	{
		return NULL;
	}
	else
	{
		return pFind->second;
	}
}

void CEditDialogInterfaceContainer::DeleteAll()
{
	CIterEditDialogInterface iter;

	while (!empty())
	{
		iter = begin();
		iter->second->DeleteEditDialog();
		delete iter->second;
		erase(iter);
	}
}

void CEditDialogInterfaceContainer::RemoveAll()
{
	clear();
}


void CEditDialogInterface::InitEditObjectClone()
{
	FreeEditObjectClone();

	m_pEditObjectClone = (CExBaseList *)m_pEditObject->Clone();
}

void CEditDialogInterface::FreeEditObjectClone()
{
	if (m_pEditObjectClone != NULL)
	{
		delete m_pEditObjectClone;
		m_pEditObjectClone = NULL;
	}
}


