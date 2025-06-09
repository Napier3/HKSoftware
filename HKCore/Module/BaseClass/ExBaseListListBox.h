#pragma once

#include "ExBaseList.h"
// CExBaseListListBox

class CExBaseListListBox : public CListBox
{
	DECLARE_DYNAMIC(CExBaseListListBox)

public:
	CExBaseListListBox();
	virtual ~CExBaseListListBox();

public:
	virtual void ShowBaseList(CExBaseList *pList, UINT nClassID, BOOL bAddEmptyString,BOOL bAddName);
	virtual void ShowBaseList(CExBaseList *pList);
	virtual void Init(CExBaseList *pList, BOOL bAddEmptyString=FALSE,BOOL bAddName=TRUE);
	virtual long FindIndex(CExBaseObject *pObj);

	virtual CExBaseObject* SetCurrSelByName(const CString &strName);
	virtual CExBaseObject* SetCurrSelByID(const CString &strID);
	virtual CExBaseObject* SetCurrSelObj(CExBaseObject *pObj);


	virtual CExBaseObject* GetSelectObject();	
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
protected:
	CExBaseList *m_pList;
	BOOL m_bAddEmptyString;
	BOOL m_dwAddName_ID_Mode;
	UINT m_nInsertClassID;

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void ShowBaseList();
	
public:
	virtual void SetInsertClassID(UINT nInsertClassID)	{	m_nInsertClassID = nInsertClassID;	}
	virtual UINT GetInsertClassID()	{	return m_nInsertClassID;	}

	virtual void SetAddEmptyString(BOOL bAddEmpty = TRUE)	{	m_bAddEmptyString = bAddEmpty;	}
	virtual BOOL GetAddEmptyString()	{	return m_bAddEmptyString;	}

	virtual void SetAddName(BOOL bAddName);
	virtual BOOL GetAddName()	{	return m_dwAddName_ID_Mode == 0;	}
	
	virtual void SetAddNameMode()	{	m_dwAddName_ID_Mode = 0;	}
	virtual void SetAddIDMode()		{	m_dwAddName_ID_Mode = 1;	}
	virtual void SetAddNameIDMode()	{	m_dwAddName_ID_Mode = 2;	}

protected:
	DECLARE_MESSAGE_MAP()
};


