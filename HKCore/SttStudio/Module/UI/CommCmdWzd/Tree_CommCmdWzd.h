#pragma once
#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CTree_CommCmdWzd :
	public CExBaseListTreeCtrl
{
 	Q_OBJECT

public:
	CTree_CommCmdWzd(QWidget *parent);
	virtual ~CTree_CommCmdWzd();

	virtual void ShowBaseList(CExBaseList *pList, BOOL bAddRoot=TRUE);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand=FALSE);

private:
	int nHC;
	BOOL m_bIsInInitState;

public :
	void on_slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol);
	void on_slot_TreeItemChanged_Aft(QTreeWidgetItem *pTreeItem);
	void updateParentItem(QTreeWidgetItem *item);

signals:
	void sig_CmdTreeItemChanged(QExBaseTreeWidgetItem* pTreeItem);
};
