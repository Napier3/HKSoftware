#pragma once

#include "..\BaseClass\ExBaseList.h"
#include <map>

class CEditDialogInterface;

class CEditDialogInterfaceContainer : public std::map<UINT,CEditDialogInterface*>
{
private:
	typedef std::map<UINT, CEditDialogInterface*>::iterator CIterEditDialogInterface;

public:
	CEditDialogInterfaceContainer();
	virtual ~CEditDialogInterfaceContainer();

	void AddEditDialog(CExBaseObject *pEditObj, CEditDialogInterface *pEditDialog);
	void AddEditDialog(UINT nClassID, CEditDialogInterface *pEditDialog);
	CEditDialogInterface* Find(CExBaseObject *pEditObj);
	CEditDialogInterface* Find(UINT nClassID);

	void DeleteAll();
	void RemoveAll();
};

class CEditDialogInterface
{
public:
	CEditDialogInterface()
	{
		m_pEditObject = NULL;
		m_pParent = NULL;
		m_bModified = FALSE;
		m_pEditDialog = NULL;
		m_pEditObjectClone = NULL;
	}

	virtual ~CEditDialogInterface()
	{
		FreeEditObjectClone();
	}

protected:
	BOOL m_bModified;
	CEditDialogInterfaceContainer m_oEditDialogContainer;
	UINT m_nClassID;
	
public:
	CExBaseObject* m_pEditObject;
	CWnd *m_pParent;
	CWnd *m_pEditDialog;

	virtual void SetModified(BOOL bFlag=TRUE)	{		m_bModified = bFlag;		}
	virtual BOOL GetModified()			{		return m_bModified;		}
	virtual BOOL IsClassIDObject(UINT nClassID)	{		return (m_nClassID == nClassID);		}

	virtual void SetEditDialog(CWnd *pWnd)	{	m_pEditDialog = pWnd;	}
	virtual void SetEditDialogParent(CWnd *pWnd)	{	m_pParent = pWnd;	}
	virtual CSize GetSize()	
	{
		ASSERT (m_pEditDialog != NULL);

		if (m_pEditDialog == NULL)	
		{	
			return CSize(0, 0);
		}

		CRect rc;
		m_pEditDialog->GetWindowRect(&rc);
		return CSize(rc.Width(), rc.Height());
	}

public:
	virtual BOOL ShowObject(CExBaseObject* pObj)		{	m_pEditObject = pObj;		return ShowObject();	}  //显示对象
	virtual BOOL ShowObject()		{	ASSERT (FALSE);	return TRUE;	}  //显示对象
	virtual BOOL Save() = 0;	//保存编辑对象
	
	virtual void Show()
	{
		ASSERT (m_pEditDialog != NULL);

		if (m_pEditDialog != NULL)	
		{	
			m_pEditDialog->ShowWindow(SW_SHOW);
		}
	}

	virtual void MoveEditDialog()
	{
		ASSERT (m_pEditDialog != NULL && m_pParent != NULL);

		if (m_pEditDialog != NULL && m_pParent != NULL)	
		{	
			CRect rcDlg;
			m_pEditDialog->GetWindowRect(&rcDlg);
			m_pParent->ScreenToClient(&rcDlg);
			m_pEditDialog->ShowWindow(SW_SHOW);
			m_pEditDialog->MoveWindow(rcDlg, TRUE);
		}
	}

	virtual void InvalidateDlg(BOOL b=TRUE)
	{
		ASSERT (m_pEditDialog != NULL);

		if (m_pEditDialog != NULL)	
		{	
			m_pEditDialog->Invalidate(b);
		}
	}

	virtual void Hide()
	{
		ASSERT (m_pEditDialog != NULL);

		if (m_pEditDialog != NULL)	
		{	
			m_pEditDialog->ShowWindow(SW_HIDE);
		}
	}

	virtual void AdjustSize(const CRect &rect)
	{
		ASSERT (m_pEditDialog != NULL);

		if (m_pEditDialog != NULL)	
		{	
			m_pEditDialog->MoveWindow(rect, TRUE);
		}
	}
	
	virtual void CreateEdit(CExBaseObject* pObj, CWnd* pParent)
	{
		m_pEditObject = pObj;
		m_pParent = pParent;
		m_bModified = FALSE;
		m_pEditDialog = NULL;

		if (m_pEditObject != NULL)
		{
			m_nClassID = m_pEditObject->GetClassID();
		}
	}

public:
	void AddEditDialog(CExBaseObject *pEditObj, CEditDialogInterface *pEditDialog);
	void AddEditDialog(UINT nClassID, CEditDialogInterface *pEditDialog);
	CEditDialogInterface* Find(CExBaseObject *pEditObj);
	CEditDialogInterface* Find(UINT nClassID);
	void DeleteEditDialog();

	//属性
protected:
	CExBaseList *m_pEditObjectClone;
	void InitEditObjectClone();
	void FreeEditObjectClone();
};

