#pragma once

#include "ExBaseOptrInterface.h"

// CExBaseListListCtrl

#define LIST_COL_INDEX   0
#define LIST_COL_NAME    1
#define LIST_COL_ID      2

class CExBaseListListCtrl : public CListCtrl, public CExBaseCtrlOptrInterface
{
	DECLARE_DYNAMIC(CExBaseListListCtrl)

public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void Optr_UpdateDataIndex();

public:
	CExBaseListListCtrl();
	virtual ~CExBaseListListCtrl();

	void ModifyListCtrlStyle();
	virtual void SetCurrSelection(long nIndex);

public:
	virtual void CreateListCtrl(CWnd *pParent, CRect rcWnd, UINT nID, BOOL bInitCols=TRUE);
	virtual void InitCollumns();
	virtual void UpdateListCtrl();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);
	virtual void UpdateListCtrl(CExBaseObject *pObj);
	virtual void UpdateIndex(long nIndexFrom=0);
	
	virtual void ShowBaseList(CExBaseList *pList, UINT nClassID);
	virtual void ShowBaseList(CExBaseList *pList);
	virtual void InsertBaseList(CExBaseList *pList);
	virtual void Init(CExBaseList *pList);
	virtual long FindIndex(CExBaseObject *pObj);

	virtual CExBaseObject* SetCurrSelByName(const CString &strName);
	virtual CExBaseObject* SetCurrSelByID(const CString &strID);
	virtual CExBaseObject* SetCurrSelObj(CExBaseObject *pObj);

	virtual long GetAllSelect(CExBaseList &listSel);
	virtual long GetSelectIndex();
	virtual CExBaseObject* GetSelectObject();	
	virtual CExBaseObject* GetObject(long nIndex);	
	virtual CString GetSelectID();
	virtual CString GetSelectName();
	virtual BOOL GetSelectID(CString &strID);
	virtual BOOL GetSelectName(CString &strName);

	virtual BOOL DeleteObject(CExBaseObject *pObj);

	virtual long AddObj(CExBaseObject *pObj);
	virtual long InsertObj(long nIndex, CExBaseObject *pObj);

	virtual void SetBaseList(CExBaseList* pList){	ShowBaseList(pList);}
	virtual CExBaseList* GetBaseList(){return m_pList;}

	virtual CExBaseObject* GetCurrSelObject()						{	return GetSelectObject();					}
	virtual CExBaseObject* SetSelByID(const CString &strID)	{	return SetCurrSelByID(strID);			}
	//BOOL SetSelByID(const CString &strID)				{	return SetCurrSelByID(strID);			}
	virtual CExBaseObject* SetSelByName(const CString &strName)			{	return SetCurrSelByName(strName);	}
	virtual BOOL GetSelID(CString &strID)								{	return GetSelectID(strID);				}
	virtual BOOL GetSelName(CString &strName)					{	return GetSelectName(strName);		}

	virtual void RemoveByID(const CString &strID);
	virtual void PopupMenu(CWnd* /*pWnd*/, CPoint /*point*/){};
protected:
	CExBaseList *m_pList;
	UINT m_nInsertClassID;

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void ShowBaseList(BOOL bDeletaAllItems=TRUE);
	
public:
	virtual void SetInsertClassID(UINT nInsertClassID)	{	m_nInsertClassID = nInsertClassID;	}
	virtual UINT GetInsertClassID()	{	return m_nInsertClassID;	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


