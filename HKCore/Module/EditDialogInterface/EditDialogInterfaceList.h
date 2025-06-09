#pragma once
#include "EditDialogInterface.h"
#include "EditTabCtrl.h"

class CEditDialogInterfaceList : public CEditDialogInterface , public CTLinkList<CEditDialogInterface>
{
public:
	CEditDialogInterfaceList();
	virtual ~CEditDialogInterfaceList(void);

public:
	virtual BOOL GetModified();
	virtual void CreateEdit(CExBaseObject* pObj, CWnd* pParent);

	virtual BOOL ShowObject(CExBaseObject* pObj);
	virtual BOOL ShowObject();

	virtual void Show();
	virtual void Hide() ;
	virtual void AdjustSize(const CRect &rect);
	virtual BOOL Save();

	virtual CSize GetChildrenSize();
	virtual CSize GetSize();

	CEditDialogInterface* FindByClassID(UINT nClassID);

	virtual void ShowChildObject(CExBaseObject *pObject, CWnd *pParent);
	virtual CEditDialogInterface* CreateChildEdit(UINT nClassID, CWnd *pParent)	{	ASSERT(FALSE);		return NULL;	}

protected:
	CEditDialogInterface *m_pCurrEditDialog;
};

class CEditDialogInterfaces : public CTLinkList<CEditDialogInterface>
{
public:
	CEditDialogInterfaces();
	virtual ~CEditDialogInterfaces(void);
	CEditDialogInterface *m_pCurrEditDlg;

public:
	CEditDialogInterface* FindByClassID(UINT nClassID);
	virtual void ShowEditDlg(CExBaseObject *pObj, CWnd *pParentWnd);
	void DeleteEditDialogs();

	virtual CEditDialogInterface* CreateEditDialog(UINT nClassID) = 0;
};
