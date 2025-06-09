#pragma once
#include "GuideBook.h"
#include "MacroTest.h"
#include "../../../Module/DataMngr/ValuesParse.h"

//////////////////////////////////////////////////////////////////////////
//CGbUnqualifiedItem
/*
�뵱ǰ���ϸ���Ŀ�������ȫ����Ŀ������ǰ����Ŀ+��ǰ���ϸ���Ŀ+���к�����Ŀ
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

//����������ڵ㣬�������CGbUnqualifiedItemEx
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
ǰ����Ŀ�趨����
a�����ϸ���ĸ��ڵ�Ϊ������ڵ�ʱ�����²��Ըø��ڵ�����������Ŀ
b���Ӳ��ϸ�����ǰ�ҹ�����ڵ㣬�����ڵ���ֵܽڵ�Ϊ������ڵ㣬�򸸽ڵ���ֵܽڵ㲻�����ԣ������ڵ���ֵܽڵ�Ϊ�ǹ�����ڵ㣬����Ը��ֵܽڵ�������ǰ����Ŀ��
c���Ҹ��ڵ�ĸ��ڵ㣬�����ڵ�Ϊ������ڵ㣬����Ըø��ڵ������зǹ�����ڵ������Ŀ������ǰ����������Ŀ����
d���ظ�c��
ǰ����Ŀ��ID=_BFT_***
������Ŀ��ID=_AFT_***
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
