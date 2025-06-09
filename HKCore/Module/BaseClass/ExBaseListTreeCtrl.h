#pragma once

#include "ExBaseOptrInterface.h"

//2021-8-24  lijunqing
class CExBaseListTreeCtrl;

class CExBaseListTreeOptrInterface
{
public:
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)	{		}
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	{	return FALSE;	}
};

// CExBaseListTreeCtrl
class CExBaseListTreeCtrl : public CTreeCtrl, public CExBaseCtrlOptrInterface
{
	DECLARE_DYNAMIC(CExBaseListTreeCtrl)

public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

public:
	CExBaseListTreeCtrl();
	virtual ~CExBaseListTreeCtrl();

//2021-8-24  lijunqing
	void AttachOptrInterface(CExBaseListTreeOptrInterface *pOptrInterface)	{	m_pOptrInterface = pOptrInterface;	}

protected:
	CExBaseListTreeOptrInterface *m_pOptrInterface;

public:
	virtual void ShowBaseList(CExBaseList *pList, BOOL bAddRoot=TRUE);
	virtual CExBaseList* GetBaseList(){return m_pList;}
	virtual void SetCurrSelObj(CExBaseObject *pObj);
	virtual CExBaseObject* GetSelectObject();	
	virtual CString GetSelectID();
	virtual CString GetSelectName();
	virtual BOOL GetSelectID(CString &strID);
	virtual BOOL GetSelectName(CString &strName);

	virtual BOOL DeleteObject(CExBaseObject *pObj, BOOL bSelOther=TRUE);
	virtual HTREEITEM AddObj(CExBaseObject *pObj, BOOL bExpand=FALSE);
	virtual void UpdateObject(CExBaseObject *pObj);

	virtual CExBaseObject* GetCurrSelObject()						{	return GetSelectObject();					}
	virtual BOOL GetSelID(CString &strID)								{	return GetSelectID(strID);				}
	virtual BOOL GetSelName(CString &strName)					{	return GetSelectName(strName);		}

protected:
	CExBaseList *m_pList;
	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual BOOL CanAdd(UINT nClassID);
	virtual HTREEITEM AddObj(CExBaseObject *pObj, HTREEITEM hParent); 
	virtual HTREEITEM InsertObj(UINT nClassID, const  CString &strName, HTREEITEM hParent); 

public:
	void ClearArrClassID();
	void AddClassID(UINT nClassID);
	void RemoveClassID(UINT nClassID);

protected:
	CDWordArray m_arrdwClassID;
	long GetIndexOfClassID(UINT nClassID);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);

};


