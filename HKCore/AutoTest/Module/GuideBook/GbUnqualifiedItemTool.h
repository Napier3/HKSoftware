#pragma once
#include "GuideBook.h"
#include "MacroTest.h"
#include "../../../Module/DataMngr/ValuesParse.h"

//////////////////////////////////////////////////////////////////////////
//CGbUnqualifiedItem
/*
与当前不合格项目相关联的全部项目：所有前驱项目+当前不合格项目+所有后驱项目
*/
class CGbUnqualifiedItem : public CExBaseList
{
public:
	CGbUnqualifiedItem()	;
	virtual ~CGbUnqualifiedItem();

	CGbItemBase *m_pItem;

	virtual void QueryBftAftItems();

protected:
	virtual void QueryBftAftItems_AllChildItem(CItems *pItems, BOOL bAddItems);
	virtual void QueryBftAftItems_ChildItem_B_A(CItems *pItems);
	virtual void QueryBftAftItems(CExBaseList *pListItems);

};

//保留功能类节点，因此引入CGbUnqualifiedItemEx
class CGbUnqualifiedItemEx : public CGbUnqualifiedItem
{
public:
	CGbUnqualifiedItemEx()	;
	virtual ~CGbUnqualifiedItemEx();

	virtual void QueryBftAftItems();

protected:
	virtual void QueryBftAftItems_AllChildItem(CItems *pItems);
	virtual void QueryBftAftItems_ChildItem_B_A(CItems *pItems);
	virtual void QueryBftAftItems(CExBaseList *pListItems);

};

/*
前驱项目设定规则：
a）不合格项的父节点为功能类节点时，重新测试该父节点下所有子项目
b）从不合格项往前找功能类节点，若父节点的兄弟节点为功能类节点，则父节点的兄弟节点不做测试；若父节点的兄弟节点为非功能类节点，则测试该兄弟节点下所有前驱项目；
c）找父节点的父节点，若父节点为功能类节点，则测试该父节点下所有非功能类节点的子项目（需是前驱、后驱项目）。
d）重复c）
前驱项目：ID=_BFT_***
后驱项目：ID=_AFT_***
*/
class CGbUnqualifiedItemTool : public CExBaseList
{
public:
	CGbUnqualifiedItemTool();
	virtual ~CGbUnqualifiedItemTool();

	void QueryUnqualifiedItems(CGuideBook *pGuideBook, CExBaseList *pContainer);
	void Query_BFT_Items(CGuideBook *pGuideBook, CExBaseList *pContainer);

protected:
	CExBaseList *m_pContainer;
	void QueryUnqualifiedItems(CExBaseList *pList);
	void AddGbUnqualifiedItem(CGbItemBase *pItem);

	void ArrangeAllItems();
	void ArrangeAllItem(CGbUnqualifiedItem *pUnqualifiedItem);
	CGbItemBase* FindItemByIndex(long nIndex);
	void InsertItem(CGbItemBase *pItem);
};
