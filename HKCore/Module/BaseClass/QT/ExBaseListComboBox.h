#pragma once

#include "../ExBaseOptrInterface.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttStudio/Module/UI/Module/ScrollCtrl/ScrollComboBox.h"
#else
#include <QComboBox>
#endif

void ex_InsertChildreComboBox(CExBaseList *pDatas, QComboBox *pComboBox, BOOL bAddParentNameID = FALSE, long nSel=0);

//2022-9-28  lijunqing 直接获取对象
CExBaseObject* ex_ComboBox_GetSelObj(QComboBox *pComboBox, long nIndex);
CExBaseObject* ex_ComboBox_GetSelObj(QComboBox *pComboBox);

//2022-11-3  lijunqing
void ex_ComboBox_adjustItemWidth(QComboBox *pComboBox);



#ifdef _PSX_QT_LINUX_
class CExBaseListComboBox : public QScrollComboBox, public CExBaseCtrlOptrInterface
#else
class CExBaseListComboBox : public QComboBox, public CExBaseCtrlOptrInterface
#endif
{
	Q_OBJECT
public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

public:
	CExBaseListComboBox(QWidget *parent);
	virtual ~CExBaseListComboBox();
	void UnsubclassChildWindow();

public:
	virtual void ShowBaseList(CExBaseList *pList, UINT nClassID, BOOL bAddEmptyString,BOOL bAddName);
	virtual void ShowBaseList(CExBaseList *pList);
	virtual void Init(CExBaseList *pList, BOOL bAddEmptyString=FALSE,BOOL bAddName=TRUE);
#ifndef NO_XDbBaseLib
	virtual void InitEx(CExBaseList *pList, long nPkValue, BOOL bAddEmptyString=FALSE,BOOL bAddName=TRUE);
#endif
	virtual long FindIndex(CExBaseObject *pObj);

	virtual CExBaseObject* SetCurrSelByName(const CString &strName);
	virtual CExBaseObject* SetCurrSelByID(const CString &strID);
	virtual CExBaseObject* SetCurrSelObj(CExBaseObject *pObj);
#ifndef NO_XDbBaseLib
	virtual CExBaseObject* SetCurrSelObj(long nPkValue);
#endif

	virtual CExBaseObject* GetSelectObject();	
	virtual CString GetSelectID();
	virtual CString GetSelectName();
	virtual BOOL GetSelectID(CString &strID);
	virtual BOOL GetSelectName(CString &strName);
#ifndef NO_XDbBaseLib
	virtual long GetSelectPKValue();
#endif

	virtual BOOL DeleteObject(CExBaseObject *pObj);
	virtual BOOL DeleteCurrSelObject();  //2021-1-8  lijunqing
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

	//20230419 zhouhj 新增接口函数
	DWORD GetItemData(long nIndex);
	void SetCurSel(int index);
	int GetCount(){return count();}
	int GetCurSel();
	int DeleteString(UINT nIndex);
	int AddString(CString &lpszString);
	int InsertString(int nIndex, CString &lpszString);
	void SetItemData(int nIndex, long nData);

protected:
	CExBaseList *m_pList;
	BOOL m_bAddEmptyString;
	BOOL m_bAddName;
	UINT m_nInsertClassID;
	BOOL m_bUseFilter;
	BOOL m_bUseRbtnDelete;

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void ShowBaseList();

// 	CExBaseListComboBoxEdit    m_Edit;
// 	CExBaseListComboBoxList    m_ListBox;
	BOOL m_bUseComboBoxList;

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
};

