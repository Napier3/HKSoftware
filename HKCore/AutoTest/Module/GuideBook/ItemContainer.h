#pragma once

#include "../../../Module/baseclass/exbaselist.h"

class CItems;
class CGuideBook;

/*
GbFilterNode::nType���壺
	-1    = Filter�ڵ�
	0     = GbFilterAttrIndex
	......
	5     = GbFilterAttrTkid
*/

typedef struct GbFilterNode 
{
	LONG nType;
	LONG nValue;
	LONG nOperID;
	GbFilterNode* pLeft;
	GbFilterNode* pRight;

	GbFilterNode()
	{	
		nType = -1; 
		nValue = 0; 
		pLeft =NULL ; 
		pRight = NULL; 
		nOperID = -1;	
	}
}GBFILTERNODE,*PGBFILTERNODE;

// typedef std::vector<PGBFILTERNODE> FILTERNODELIST;
typedef CTLinkList<GBFILTERNODE>  FILTERNODELIST;

class CGuideBook;
class CGbItemBase;
class CItemContainer;

enum TestOptrMode
{
	TestOptrMode_StartTest=0,
	TestOptrMode_TestSingle=1,
	TestOptrMode_TestFrom=2
};

class CItemContainerBase : public CExBaseList
{
public:
	CItemContainerBase();
	virtual ~CItemContainerBase();

protected:
	UINT m_nTestMode;
public:
    long m_nItemCount;   //��ǰ���ԣ���Ҫ���ԵĲ�������������������Ŀ   shaolei 20201217
	long m_nCurrFinishItem;//��ǰ�������Ե���Ŀ�ţ���1��ʼ���ۼ���
	CExBaseList m_oListItems;
	//shaolei 2023-9-14 �������������������β�bBackRpt���Ƿ񱸷ݱ���
	virtual void InitItems(CExBaseObject *pObj, long *pnItemIndex, BOOL bSetIndex, BOOL bBackRpt);  
	virtual void InitItemsChildren(CExBaseList *pList, long *pnItemIndex, BOOL bSetIndex, BOOL bBackRpt=FALSE);
	void SetItemIndex(CGbItemBase *pItem, long *pnItemIndex, BOOL bSetIndex);
	void SetTestMode(UINT nTestMode)	{	m_nTestMode = nTestMode;	}
	long GetTestMode()	{	return m_nTestMode;	}

//	friend CItemContainer;

public:
	virtual CExBaseObject *FindItemByAttrIndex(long nIndex);
};

class CItemsLoopContainer : public CItemContainerBase
{
public:
	CItemsLoopContainer(CItems *pItems, long *pnIndex, BOOL bSetIndex);
	virtual ~CItemsLoopContainer();

	CItems* GetItems()	{	return m_pItems;	}

protected:
	CItemsLoopContainer()	{}

	CItems *m_pItems;
	
};

class CItemContainer :	public CItemContainerBase
{
public:
	CItemContainer(void);
	virtual ~CItemContainer(void);

public:
	FILTERNODELIST m_FilterNodeList;
	CGuideBook* m_pGuideBook;
	LONG m_nJumpMode;
	CString m_strJumpItemID;
	LONG m_nIndex;
	

public:
	void ResetItemContainer();
	CGbItemBase* FindItemByIndex(long nIndex);
	void SetGuideBook(CGuideBook* pGuideBook);
	void UpdateItem(CGbItemBase *pItem);

	//Interface Mathods
	long CreateAttrFilter(long nAttrType,long nOptr, long nValue);
	long CreateFilter(long nFilter1,long nOptr,long nFilter2);
	long ClearFilter();
	virtual long Query(long nFilter, BOOL bUseSel=FALSE);

	CGbItemBase* GetFirstItem();
	CGbItemBase* GetNextItem();
	CGbItemBase* GetCurrItem();
	CGbItemBase* GetPrevItem();
	CGbItemBase* GetNextItem_Ex();   //����ȡ��Ŀ�����ı�m_pos
	CGbItemBase* GetNextItemForHdResReqFailed();  //2023-5-13  lijunqing
	void RemoveItemTestFinished(CGbItemBase *pItem);
	void SetCurrPosByItem(CGbItemBase *pItem);  //���õ�ǰλ�ã�ָ������Ŀ

	BOOL ReachTailPos();
	void GotoItem(CGbItemBase *pGotoItem, CGbItemBase* pCurrItem=NULL);
	CGbItemBase* GetGotoItem()	{	return m_pGotoItem;	}
	void SetGotoItem(CGbItemBase *pGotoItem)	{	m_pGotoItem = pGotoItem;	}

	CExBaseList* GetGuideBookAllItems();

	//�쳣�ָ����ܽӿ�
	//���������еĲ�����Ŀ��״̬���ļ���
	long SaveItemsStateToFile(const CString &strFile);
	//�ָ�������Ŀ�Ĳ���״̬
	long RestoreFromFile(const CString &strFile);

	long AddItemsBeforeCurr(CExBaseList &oList);
protected:
	long CreateAttrFilterEx(long nAttrType,long nOptr, long nValue);
	long CreateAttrIndexEqualFilter(long nValue);

	BOOL _InitFilerNode(CGbItemBase* pObject);
	BOOL _CalFilterNode(PGBFILTERNODE node);

	//CExBaseList m_oListItems;
	virtual void InitItems(CExBaseObject *pObj, long *pnItemIndex, BOOL bSetIndex);
	//virtual void InitItems(CExBaseList *pList);
	void GetItemAttrIndexRange(CExBaseList *pItems, long &nMinIndex, long& nMaxIndex);
	virtual CExBaseObject* FindItemByAttrIndex(long nIndex);
	CExBaseObject* FindItemByAttrIndex(long nIndex, CExBaseList *pList);
	
	POS  m_pos;
	CGbItemBase *m_pGotoItem;		

	//�쳣�ָ�����
	long BinarySerialize(CBinarySerialBuffer &oBinaryBuffer);

//////////////////////////////////////////////////////////////////////////
//2019-4-26   ��װ�ò���ģʽ�£�ÿ̨װ�ö���ִ�в��Ե�ģʽ
public:
	void AddMdvGuideBook(CGuideBook *pGuideBook);
	void GetAllTestItems(CExBaseList &listAllItems);

protected:
	CItemsLoopContainer* FindLoopByItems(CItems *pItems);
	void AddItemsLoop(CItems *pItems, long *pnItemIndex, BOOL bSetIndex);
	void QueryItemsLoop(CItems *pItems, PGBFILTERNODE pNode, BOOL bUseSel);
	void QueryItemsLoop(CItemsLoopContainer *pLoop, PGBFILTERNODE pNode, BOOL bUseSel);
	void QueryItemsLoop(CItemsLoopContainer *pLoop, CGuideBook *pGuideBook, PGBFILTERNODE pNode, BOOL bUseSel);
	void QueryItem(CGbItemBase *pGbItem, UINT nClassID, PGBFILTERNODE pNode, BOOL bUseSel);
	void GetAllTestItemsLoop(CExBaseList &listAllItems, CItems *pItems);

	CExBaseList m_listMdvGuideBook;
	CExBaseList m_listItemsLoop;

	BOOL UpdateItem_NeedUpdateIndex(CExBaseList *pList);

//////////////////////////////////////////////////////////////////////////
//2021-8-5  lijunqing  ���Խ���
public:
	void GetTestProcess(long &nTotalItems, long &nCurrItem, long &nTotalTime, long &nRemainTime);
	void SetPosByItem(CExBaseObject *pItem);
};
