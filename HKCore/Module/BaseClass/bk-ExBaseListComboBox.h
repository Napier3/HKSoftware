#pragma once

#include "ExBaseCtrlOptrInterface.h"
// CExBaseListComboBox

#define WM_FILTER_EXBASELIST   (WM_USER + 1412)
#define WM_RBUTTON_UP_LIST     (WM_USER + 1413)

class CExBaseListComboBoxList : public CListBox
{
	DECLARE_DYNAMIC(CExBaseListComboBoxList)

public:
	CExBaseListComboBoxList();
	virtual ~CExBaseListComboBoxList();
	CComboBox *m_pCmoboBox;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


class CExBaseListComboBoxEdit : public CEdit
{
	DECLARE_DYNAMIC(CExBaseListComboBoxEdit)
public:
	CExBaseListComboBoxEdit();
	virtual ~CExBaseListComboBoxEdit();

	CComboBox *m_pCmoboBox;
	CString m_strText;

	void ShowText();
private:
	int m_nCurrPosBegin;
	int m_nCurrPosEnd;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnChange();
};


class CExBaseListComboBox : public CComboBox, public CExBaseCtrlOptrInterface
{
public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

public:
	CExBaseListComboBox();
	virtual ~CExBaseListComboBox();
	void UnsubclassChildWindow();

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
	virtual long GetSelectPKValue();

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
	BOOL m_bAddName;
	UINT m_nInsertClassID;
	BOOL m_bUseFilter;
	BOOL m_bUseRbtnDelete;

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void ShowBaseList();

	CExBaseListComboBoxEdit    m_Edit;
	CExBaseListComboBoxList    m_ListBox;

public:
	void SetUseFilter(BOOL bFilter = TRUE)	{	m_bUseFilter = bFilter;		}
	BOOL IsUseFilter()						{	return m_bUseFilter;		}
	void SetUseRbtnDelete(BOOL b = TRUE)	{	m_bUseRbtnDelete = b;		}
	BOOL IsUseRbtnDelete()					{	return m_bUseRbtnDelete;	}
	
public:
	virtual void SetInsertClassID(UINT nInsertClassID)	{	m_nInsertClassID = nInsertClassID;	}
	virtual UINT GetInsertClassID()	{	return m_nInsertClassID;	}

	virtual void SetAddEmptyString(BOOL bAddEmpty = TRUE)	{	m_bAddEmptyString = bAddEmpty;	}
	virtual BOOL GetAddEmptyString()	{	return m_bAddEmptyString;	}

	virtual void SetAddName(BOOL bAddName)	{	m_bAddName = bAddName;	}
	virtual BOOL GetAddName()	{	return m_bAddName;	}

public:
	virtual void OnFilterText();
	virtual void OnRbtnDelete();

public:
	DECLARE_MESSAGE_MAP()
	HRESULT OnFilterText(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd *pWnd, UINT nCtlColor);
	HRESULT OnRbtnDelete(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
};


