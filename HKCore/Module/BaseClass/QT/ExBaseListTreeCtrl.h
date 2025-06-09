#pragma once

#include "../ExBaseOptrInterface.h"

#include <QTreeWidget>
#include <QStyleFactory>
#include <QTreeWidgetItem>

class QExBaseTreeWidgetItem : public QTreeWidgetItem
{
public:
	QExBaseTreeWidgetItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QExBaseTreeWidgetItem(QTreeWidget *parent, CExBaseObject *pData);
	virtual ~QExBaseTreeWidgetItem();

	CExBaseObject *m_pItemData;

};

//2021-8-24  lijunqing
class CExBaseListTreeCtrl;

class CExBaseListTreeOptrInterface
{
public:
	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)	{		}
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)	{		}
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	{	return FALSE;	}
};

// CExBaseListTreeCtrl
class CExBaseListTreeCtrl : public QTreeWidget, public CExBaseCtrlOptrInterface
{
	Q_OBJECT

public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

public:
	CExBaseListTreeCtrl(QWidget *parent);
	virtual ~CExBaseListTreeCtrl();

	void AttachOptrInterface(CExBaseListTreeOptrInterface *pOptrInterface)	{	m_pOptrInterface = pOptrInterface;	}

	virtual QExBaseTreeWidgetItem* NewItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	virtual QExBaseTreeWidgetItem* InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	virtual QExBaseTreeWidgetItem* InsertItem(QTreeWidgetItem *parent, const CString &strText);

protected:
	CExBaseListTreeOptrInterface *m_pOptrInterface;

	QExBaseTreeWidgetItem* PrevSiblingItem(QExBaseTreeWidgetItem *hItem);
	QExBaseTreeWidgetItem* NextSiblingItem(QExBaseTreeWidgetItem *hItem);

public:
	virtual void ShowBaseList(CExBaseList *pList, BOOL bAddRoot=TRUE);
	virtual void ShowBaseListEx(CExBaseList *pList, BOOL bAddRoot=TRUE ,BOOL bExpand = FALSE);//增加展开树形控件节点  zhouhj  20221022
	virtual CExBaseList* GetBaseList(){return m_pList;}
	virtual void SetCurrSelObj(CExBaseObject *pObj);
	virtual CExBaseObject* GetSelectObject();	
	virtual CString GetSelectID();
	virtual CString GetSelectName();
	virtual BOOL GetSelectID(CString &strID);
	virtual BOOL GetSelectName(CString &strName);

	virtual BOOL DeleteObject(CExBaseObject *pObj, BOOL bSelOther=TRUE);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, BOOL bExpand=FALSE);
	virtual void AddObjChildren(CExBaseList *pList, QExBaseTreeWidgetItem* hItem, BOOL bExpand=FALSE);
	virtual void UpdateObject(CExBaseObject *pObj, BOOL bUpdateChildren=FALSE, BOOL bExpand=FALSE);

	virtual CExBaseObject* GetCurrSelObject()						{	return GetSelectObject();					}
	virtual BOOL GetSelID(CString &strID)								{	return GetSelectID(strID);				}
	virtual BOOL GetSelName(CString &strName)					{	return GetSelectName(strName);		}

protected:
	CExBaseList *m_pList;
	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual BOOL CanAdd(UINT nClassID);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand=FALSE); 
	virtual QExBaseTreeWidgetItem* InsertObj(UINT nClassID, const  CString &strName, QExBaseTreeWidgetItem* hParent); 

public:
	void ClearArrClassID();
	void AddClassID(UINT nClassID);
	void RemoveClassID(UINT nClassID);

protected:
	CDWordArray m_arrdwClassID;
	long GetIndexOfClassID(UINT nClassID);

public:
signals:
	void sig_TreeItemClicked(QTreeWidgetItem *, int);
	void sig_TreeItemDoubleClicked(QTreeWidgetItem *, int);

public slots:
	void slot_TreeItemClicked(QTreeWidgetItem *pTreeItem, int nCol);
	void slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol);
	void slot_TreeItemDoubleClicked(QTreeWidgetItem *pTreeItem, int nCol);

};


