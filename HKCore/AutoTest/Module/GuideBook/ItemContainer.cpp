#include "StdAfx.h"
#include "ItemContainer.h"
#include "GuideBook.h"
#include "GbItemBase.h"
#include "Items.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CGbItemBase_IndexUpdateTool : CExBaseList
{
public:
	class CGbItemBase_IndexUpdate : public CExBaseObject
	{
	public:
		CGbItemBase *m_pItem;
		long m_nOldIndex;

		void AfterUpdateItemIndex()
		{
			if (m_nOldIndex == 0)
			{
				return;
			}

			if (m_pItem->GetIndex() == m_nOldIndex)
			{
				return;
			}

			m_pItem->AfterUpdateItemIndex(m_nOldIndex);
		}
	};

public:
	void AddIndexUpdate(CGbItemBase *pItem, long nOldIndex)
	{
		CGbItemBase_IndexUpdate *p = new CGbItemBase_IndexUpdate();
		p->m_pItem = pItem;
		p->m_nOldIndex = nOldIndex;
		AddNewChild(p);
	}

	void AfterUpdateItemIndex()
	{
		POS pos = GetTailPosition();
		CGbItemBase_IndexUpdate *p = NULL;

		while (pos != NULL)
		{
			p = (CGbItemBase_IndexUpdate *)GetPrev(pos);
			p->AfterUpdateItemIndex();
		}
	}
};

CGbItemBase_IndexUpdateTool *g_pIndexUpdateTool = NULL;
//////////////////////////////////////////////////////////////////////////
//
CItemContainerBase::CItemContainerBase()
{
    m_nItemCount = 0;
	m_nTestMode = TestOptrMode_StartTest;
	m_nCurrFinishItem = 0;
}

CItemContainerBase::~CItemContainerBase()
{
	m_oListItems.RemoveAll();
}


void CItemContainerBase::SetItemIndex(CGbItemBase *pItem, long *pnItemIndex, BOOL bSetIndex)
{
	if (bSetIndex)
	{
		if (g_pIndexUpdateTool != NULL)
		{//如果是从测试模板更新参数，只有新增加的项目，才更新m_nIndex  2020-02-06
			g_pIndexUpdateTool->AddIndexUpdate(pItem, pItem->GetIndex());
		}

		pItem->SetIndex(*pnItemIndex);
		*pnItemIndex = *pnItemIndex + 1;
	}
	else
	{//如果不是设置ItemIndex，则更新Container的m_nIndex，用于从测试模板更新参数用  2020-0206
		*pnItemIndex = max(*pnItemIndex, pItem->GetIndex());
	}
}

void CItemContainerBase::InitItems(CExBaseObject *pObj, long *pnItemIndex, BOOL bSetIndex, BOOL bBackRpt)
{
	UINT nClassID = pObj->GetClassID();

	if (!Gb_IsItemBaseClassID(nClassID))
	{
		return;
	}

	if (pnItemIndex != NULL)
	{
		SetItemIndex(((CGbItemBase*)pObj), pnItemIndex, bSetIndex);
	}

	if (bBackRpt)
	{
		CGbItemBase *pItemBase = (CGbItemBase *)pObj;
		pItemBase->ClearReport();
	}

	m_oListItems.AddTail(pObj);

	if (!pObj->IsBaseObject())
	{
		InitItemsChildren((CExBaseList*)pObj, pnItemIndex, bSetIndex, bBackRpt);
	}
}


void CItemContainerBase::InitItemsChildren(CExBaseList *pList, long *pnItemIndex, BOOL bSetIndex, BOOL bBackRpt)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		InitItems(p, pnItemIndex, bSetIndex, bBackRpt);
	}

	//重复测试  2023-3-19，需要重复添加。重复添加时，按照层次结构，整体重复添加
	if (pList->GetClassID() == GBCLASSID_ITEMS)
	{
		CItems* pItems = (CItems*)pList;

		if (pItems->m_nTestTimes > 1)
		{
			long nRepeatTimes = pItems->m_nTestTimes;

			while (nRepeatTimes > 1)
			{
				pos = pItems->GetHeadPosition();

				while (pos != NULL)
				{
					p = pItems->GetNext(pos);
					//重复测试的，不再重新设置索引号
					if (nRepeatTimes == 2)
					{
						//最后一次循环，备份报告
						//此处，备份报告的目的是，对于重复测试，保证每个重复循环中，只有本次循环的报告。这样判断当前测试次数才准确。
						InitItems(p, pnItemIndex, FALSE, TRUE);
					}
					else
					{
						InitItems(p, pnItemIndex, FALSE, FALSE);
					}
				}

				nRepeatTimes--;
			}
		}
	}
}

CExBaseObject* CItemContainerBase::FindItemByAttrIndex(long nIndex)
{
	POS pos = m_oListItems.GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = m_oListItems.GetNext(pos);

		if (Gb_IsItemBaseClassID(p->GetClassID()))
		{
			if (nIndex == ((CGbItemBase*)p)->m_nIndex )
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//CItemsLoopContainer
CItemsLoopContainer::CItemsLoopContainer(CItems *pItems, long *pnIndex, BOOL bSetIndex)
{
	m_pItems = pItems;
	InitItemsChildren((CExBaseList*)pItems, pnIndex, bSetIndex);
}

CItemsLoopContainer::~CItemsLoopContainer()
{

}

//////////////////////////////////////////////////////////////////////////
//CItemContainer
CItemContainer::CItemContainer(void):m_pGuideBook(NULL)
{
	m_nIndex = 0;
	m_pGotoItem = NULL;
	m_pos = NULL;
}

CItemContainer::~CItemContainer(void)
{
	m_listItemsLoop.DeleteAll();
	m_listMdvGuideBook.RemoveAll();
	m_oListItems.RemoveAll();
	ClearFilter();
}

void CItemContainer::ResetItemContainer()
{
	m_pos = NULL;
	m_listItemsLoop.DeleteAll();
	m_listMdvGuideBook.RemoveAll();
}

CGbItemBase* CItemContainer::FindItemByIndex(long nIndex)
{
	POS pos = m_oListItems.GetHeadPosition();
	CGbItemBase *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CGbItemBase *)m_oListItems.GetNext(pos);

		if (p->m_nIndex == nIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CItemContainer::SetGuideBook(CGuideBook* pGuideBook)
{
	m_pGuideBook = pGuideBook;
	ASSERT (m_pGuideBook != NULL);
	m_oListItems.RemoveAll();
	m_listItemsLoop.DeleteAll();

	if (m_pGuideBook->m_nIndex == 0)
	{
		InitItemsChildren((CExBaseList*)m_pGuideBook, &m_nIndex, TRUE);
	}
	else
	{
		InitItemsChildren((CExBaseList*)m_pGuideBook, &m_nIndex, FALSE);
	}

	m_pGuideBook->m_nIndex = 0x0F0F0F0F;
}

BOOL CItemContainer::UpdateItem_NeedUpdateIndex(CExBaseList *pList)
{
	UINT nClassID = pList->GetClassID();

	if (!Gb_IsItemBaseClassID(nClassID))
	{
		return FALSE;
	}

	if ( ((CGbItemBase*)pList)->GetIndex() == 0)
	{
		return TRUE;
	}
	
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (UpdateItem_NeedUpdateIndex((CExBaseList*)p))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CItemContainer::UpdateItem(CGbItemBase *pItem)
{
	if (!UpdateItem_NeedUpdateIndex(pItem))
	{
		return;
	}

	g_pIndexUpdateTool = new CGbItemBase_IndexUpdateTool();
	m_nIndex = 0;
	InitItemsChildren((CExBaseList*)m_pGuideBook, &m_nIndex, TRUE);
	g_pIndexUpdateTool->AfterUpdateItemIndex();
	
	delete g_pIndexUpdateTool;
}

void CItemContainer::InitItems(CExBaseObject *pObj, long *pnItemIndex, BOOL bSetIndex)
{
	UINT nClassID = pObj->GetClassID();

	if (!Gb_IsItemBaseClassID(nClassID))
	{
		return;
	}

	if (pnItemIndex  != NULL)
	{
		SetItemIndex(((CGbItemBase*)pObj), pnItemIndex, bSetIndex);
	}

	m_oListItems.AddTail(pObj);

	if (pObj->GetClassID() == GBCLASSID_ITEMS)
	{
		CItems *pItems = (CItems*)pObj;

		//如果是多装置下的单独测试项目分类，则CItemContainer不再做处理
		if ( pItems->IsMdvTestEach() )
		{
			AddItemsLoop(pItems, pnItemIndex, bSetIndex);
			return;
		}
	}

	if (!pObj->IsBaseObject())
	{
		InitItemsChildren((CExBaseList*)pObj, pnItemIndex, bSetIndex);
	}
}


// void CItemContainer::InitItems(CExBaseList *pList)
// {
// 	POS pos = pList->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pList->GetNext(pos);
// 		InitItems(p);
// 	}
// }

/*
对于“属性等于”来说，如果一个项目为Items对象，则需要检索出其下的全部子对象
所以需要将“属性等于”条件分为两个条件：“属性大于等于”、“属性小于等于”
对于其他属性操作来说，例如“属性大于”，不关事单个对象还是集合对象，都可以同样处理
因为集合对象的子对象的Index比其自身的Index大
*/
long CItemContainer::CreateAttrFilter(long nAttrType, long nOptr, long nValue)
{
	LONG nReturn = 0;
	ASSERT (m_pGuideBook != NULL);

	LONG nCount = 0;
	LONG nIndex = 0;
	LONG nClassID = 0;
	nCount = m_oListItems.GetCount();

	CGbItemBase* pItem = NULL;

	if (nAttrType==GbFilterAttrIndex && nOptr == GbFilterOptrEqual)
	{//创建属性等于过滤条件
		nReturn = CreateAttrIndexEqualFilter( nValue);
	}
	else
	{
		nReturn = CreateAttrFilterEx(nAttrType,nOptr,nValue);
	}

	return nReturn;
}


long CItemContainer::CreateAttrFilterEx(long nAttrType,long nOptr, long nValue)
{
	PGBFILTERNODE pLeft = new GBFILTERNODE;
	PGBFILTERNODE pRight = new GBFILTERNODE;
	PGBFILTERNODE pRoot =new GBFILTERNODE;
	LONG nReturn = 0;

	//属性值节点
	pLeft->nType = nAttrType;

	//常数节点
	pRight->nValue = nValue;

	//计算节点
	pRoot->nOperID = nOptr;
	pRoot->pLeft = pLeft;
	pRoot->pRight = pRight;

	m_FilterNodeList.AddTail(pLeft);
	m_FilterNodeList.AddTail(pRight);
	m_FilterNodeList.AddTail(pRoot);
	nReturn = m_FilterNodeList.GetCount()-1;

	return nReturn;
}

//创建属性等于过滤条件
//对于“属性等于”来说，如果一个项目为Items对象，则需要检索出其下的全部子对象
//所以需要将“属性等于”条件分为两个条件：“属性大于等于”、“属性小于等于”
long CItemContainer::CreateAttrIndexEqualFilter(long nValue)
{
	long nReturn = 0;
	CGbItemBase *p = (CGbItemBase*)FindItemByAttrIndex(nValue);
	ASSERT (p != NULL);
	UINT nClassID = p->GetClassID();

	if (Gb_IsItemsBaseClassID(nClassID))
	{
		long nMinIndex = 0x0FFFFFFF;
		long nMaxIndex = -1;
		GetItemAttrIndexRange(p, nMinIndex, nMaxIndex);
		long nFilter1 = CreateAttrFilterEx(GbFilterAttrIndex, GbFilterOptrMoreThanEqual, nMinIndex);
		long nFilter2 = CreateAttrFilterEx(GbFilterAttrIndex, GbFilterOptrLessThanEqual, nMaxIndex);
		nReturn = CreateFilter(nFilter1, GbFilterOptrAnd, nFilter2);
	}
	else if (nClassID == GBCLASSID_MACROCHARITEMS)
	{
		long nMinIndex = 0x0FFFFFFF;
		long nMaxIndex = -1;
		GetItemAttrIndexRange(p, nMinIndex, nMaxIndex);

		nMinIndex = min(nMinIndex, nValue);
		long nFilter1 = CreateAttrFilterEx(GbFilterAttrIndex, GbFilterOptrMoreThanEqual, nMinIndex);
		long nFilter2 = CreateAttrFilterEx(GbFilterAttrIndex, GbFilterOptrLessThanEqual, nMaxIndex);
		nReturn = CreateFilter(nFilter1, GbFilterOptrAnd, nFilter2);
	}
	else
	{
		nReturn = CreateAttrFilterEx(GbFilterAttrIndex, GbFilterOptrEqual, nValue);
	}

	return nReturn;
}

void CItemContainer::GetItemAttrIndexRange(CExBaseList *pItems, long &nMinIndex, long &nMaxIndex)
{
	POS pos = pItems->GetHeadPosition();
	CGbItemBase *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CGbItemBase*)pItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			nMinIndex = min(nMinIndex, p->m_nIndex);
			nMaxIndex = max(nMaxIndex, p->m_nIndex);
		}

		if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			GetItemAttrIndexRange(p, nMinIndex, nMaxIndex);
		}

		if (Gb_IsItemsBaseClassID(nClassID))
		{
			GetItemAttrIndexRange(p, nMinIndex, nMaxIndex);
		}
	}
}

CExBaseObject* CItemContainer::FindItemByAttrIndex(long nIndex)
{
	CExBaseObject *pFind = NULL;

	pFind = FindItemByAttrIndex(nIndex, &m_oListItems);

	if (pFind == NULL)
	{
		POS pos = m_listItemsLoop.GetHeadPosition();
		CItemsLoopContainer *pLoop = NULL;

		while (pos != NULL)
		{
			pLoop = (CItemsLoopContainer *)m_listItemsLoop.GetNext(pos);
			pFind = pLoop->FindItemByAttrIndex(nIndex);

			if (pFind != NULL)
			{
				break;
			}
		}

		//CItemContainer *pLoop = (CItemContainer *)m_listItemsLoop.GetHead();
		//pFind = pLoop->FindItemByAttrIndex(nIndex);
	}

	return pFind;
}

CExBaseObject* CItemContainer::FindItemByAttrIndex(long nIndex, CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (Gb_IsItemBaseClassID(p->GetClassID()))
		{
			if (nIndex == ((CGbItemBase*)p)->m_nIndex )
			{
				pFind = p;
				break;
			}
		}
	}

	return pFind;
}

long CItemContainer::CreateFilter(long nFilter1, long nOptr, long nFilter2)
{
	PGBFILTERNODE pLeft =NULL;
	PGBFILTERNODE pRight =NULL;
	PGBFILTERNODE pRoot = new GBFILTERNODE;
	pLeft = m_FilterNodeList.GetAtIndex(nFilter1);
	pRight = m_FilterNodeList.GetAtIndex(nFilter2);

	ASSERT (pLeft != NULL);
	ASSERT (pRight != NULL);

	pRoot->nOperID = nOptr;
	pRoot->pLeft = pLeft;
	pRoot->pRight = pRight;

	m_FilterNodeList.AddTail(pRoot);
	return m_FilterNodeList.GetCount()-1;
}

long CItemContainer::ClearFilter()
{
// 	PGBFILTERNODE pNode;
// 	unsigned int i =0;
// 	for (i=0;i<m_FilterNodeList.size();i++)
// 	{
// 		pNode = m_FilterNodeList[i];
// 		delete pNode;
// 	}
// 
// 	m_FilterNodeList.clear();
	m_FilterNodeList.DeleteAll();
	RemoveAll();
	return TRUE;
}

/*************************************************
函数名称：		_CalFilterNode
描述：    		计算二叉树值.
*************************************************/
BOOL CItemContainer::_CalFilterNode(PGBFILTERNODE node)
{
	if (node->pLeft!=NULL&&node->nOperID!=NULL)
	{
		_CalFilterNode(node->pLeft);
	}

	if (node->pRight!=NULL&&node->nOperID!=NULL)
	{
		_CalFilterNode(node->pRight);
	}

	switch (node->nOperID)
	{
	case GbFilterOptrLessThan:
		node->nValue = node->pLeft->nValue < node->pRight->nValue;
		break;

	case GbFilterOptrMoreThan:
		node->nValue = node->pLeft->nValue > node->pRight->nValue;
		break;

	case GbFilterOptrLessThanEqual:
		node->nValue = node->pLeft->nValue <= node->pRight->nValue;
		break;

	case GbFilterOptrMoreThanEqual:
		node->nValue = node->pLeft->nValue >= node->pRight->nValue;
		break;
	case GbFilterOptrEqual:
		node->nValue = node->pLeft->nValue == node->pRight->nValue;
		break;

	case GbFilterOptrAnd:
		node->nValue = node->pLeft->nValue && node->pRight->nValue;
		break;

	case GbFilterOptrNotEqual:
		node->nValue = node->pLeft->nValue != node->pRight->nValue;
		break;

	default:
		break;
	}

	return node->nValue;
}
/*************************************************
函数名称：		_InitFilerNode
描述：    		遍历m_FilterNodeList链表，根据pIGbNode设置节点Value值。
*************************************************/
BOOL CItemContainer::_InitFilerNode(CGbItemBase* pObject)
{
	//LONG nValue;
	PGBFILTERNODE pNode = NULL;

	//std::vector<PGBFILTERNODE>::iterator iter;
	POS pos = m_FilterNodeList.GetHeadPosition();

	//for (iter = m_FilterNodeList.begin();iter!=m_FilterNodeList.end();iter++)
	while (pos != NULL)
	{
		pNode = m_FilterNodeList.GetNext(pos);

		switch (pNode->nType)
		{
		case -1:
			break;
		case GbFilterAttrIndex:
			pNode->nValue = pObject->GetIndex();
			break;
		case GbFilterAttrShow:
			pNode->nValue = pObject->GetShow();
			break;
		case GbFilterAttrEnable:
			pNode->nValue = pObject->GetEnable();
			break;
		case GbFilterAttrSelect:
			pNode->nValue = pObject->GetSelect();
			break;
		case GbFilterAttrState:
			pNode->nValue = pObject->GetState();
			break;
		case GbFilterAttrTkid:
			pNode->nValue = pObject->GetTkID();
			break;
		default:
			break;
		}
	}

	return TRUE;
}

void CItemContainer::QueryItem(CGbItemBase *pItem, UINT nClassID, PGBFILTERNODE pNode, BOOL bUseSel)
{
	if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST
		|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SYSPARAEDIT
		|| nClassID == GBCLASSID_MACROCHARITEMS || nClassID == GBCLASSID_HDRESREQUEST)
	{
		if (bUseSel)
		{
			if (pItem->m_nSelect > 0)
			{
				_InitFilerNode(pItem);

				if (_CalFilterNode(pNode) > 0)
				{
                    m_nItemCount += pItem->GetSubGbItemsCount() +1;
					AddTail(pItem);
				}
			}
		}
		else
		{
			_InitFilerNode(pItem);

			if (_CalFilterNode(pNode) > 0)
			{
               m_nItemCount += pItem->GetSubGbItemsCount() +1;
				AddTail(pItem);
			}
		}
	}
}

long  CItemContainer::Query(long nFilter, BOOL bUseSel)
{
    m_nItemCount = 0;
	m_nCurrFinishItem = 0;
	RemoveAll();
	POS pos = m_oListItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	PGBFILTERNODE pNode = m_FilterNodeList.GetAtIndex(nFilter);
	UINT nClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase*)m_oListItems.GetNext(pos);
		nClassID = pItem->GetClassID();

		if (Gb_ISTestingSubtem(pItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			pItems = (CItems *)pItem;

			if (pItems->IsMdvTestEach())
			{
				QueryItemsLoop(pItems, pNode, bUseSel);
				continue;
			}
		}

		QueryItem(pItem, nClassID, pNode, bUseSel);
	}

	return GetCount();
}

CGbItemBase*  CItemContainer::GetFirstItem()
{
	m_pos = GetHeadPosition();

	if (m_pos == NULL)
	{
		return NULL;
	}
	else
	{
		CGbItemBase *pItem = (CGbItemBase*)GetAt(m_pos);

		if (pItem->IsEnableAndShow())
		{
			return pItem;
		}
		else
		{
			return GetNextItem();
		}
	}
}

CGbItemBase*  CItemContainer::GetNextItem()
{
	if (m_pGotoItem != NULL)
	{
		CGbItemBase *pGotoItem = m_pGotoItem;
		m_pGotoItem = NULL;
		return pGotoItem;
	}

	if (m_pos == NULL)
	{
		return NULL;
	}
	else 
	{
		CGbItemBase *pFind = NULL;
		CGbItemBase *p = NULL;

		while (TRUE)
		{
			GetNext(m_pos);

			if(m_pos == NULL)
			{
				break;
			}
			else
			{
				p = (CGbItemBase*)GetAt(m_pos);

				if ((p->m_nSelect > 0) && (p->IsEnableAndShow()))
				{
					pFind = p;
					break;
				}
			}
		}

		return pFind;
	}

}



CGbItemBase*  CItemContainer::GetCurrItem()
{
	if (m_pos == NULL)
	{
		return NULL;
	}
	else
	{
		return (CGbItemBase*)GetAt(m_pos);
	}
}

CGbItemBase*  CItemContainer::GetNextItem_Ex()
{
	if (m_pGotoItem != NULL)
	{
		CGbItemBase *pGotoItem = m_pGotoItem;
		//m_pGotoItem = NULL;
		return pGotoItem;
	}

	POS pos = m_pos;

	if (pos == NULL)
	{
		return NULL;
	}
	else 
	{
		CGbItemBase *pFind = NULL;
		CGbItemBase *p = NULL;

		while (TRUE)
		{
			GetNext(pos);

			if(pos == NULL)
			{
				break;
			}
			else
			{
				p = (CGbItemBase*)GetAt(pos);

				if ((p->m_nSelect > 0) && (p->IsEnableAndShow()))
				{
					pFind = p;
					break;
				}
			}
		}

		return pFind;
	}
}

//2023-5-13  lijunqing
CGbItemBase* CItemContainer::GetNextItemForHdResReqFailed()
{
	CGbItemBase *pFind = NULL;
	CGbItemBase *p = NULL;
	CHdResReqest *pHdResRelease = NULL;

	while (TRUE)
	{
		GetNext(m_pos);

		if(m_pos == NULL)
		{
			break;
		}
		else
		{
			p = (CGbItemBase*)GetAt(m_pos);

			if (p->GetClassID() == GBCLASSID_HDRESREQUEST)
			{
				if (((CHdResReqest*)p)->IsRelease())
				{
					pHdResRelease = (CHdResReqest*)p;
					break;
				}
			}
		}
	}

	if (pHdResRelease == NULL)
	{
		return NULL;
	}

	return GetNextItem();
}

void CItemContainer::RemoveItemTestFinished(CGbItemBase *pItem)
{
	if (m_pGuideBook->CanRemoveItemTestFinished())
	{
		Remove(pItem);
	}
}

//设置当前位置，指定的项目
void CItemContainer::SetCurrPosByItem(CGbItemBase *pItem)
{
	m_pos = Find(pItem);
}

BOOL  CItemContainer::ReachTailPos()
{
	CGbItemBase *pCurr = GetCurrItem();
	CGbItemBase *pTail = (CGbItemBase*)GetTail();

	return (pCurr == pTail);
}

void CItemContainer::GotoItem(CGbItemBase *pGotoItem, CGbItemBase* pCurrItem)
{
	POS posCurr = NULL;
	
	if (pCurrItem != NULL)
	{
		posCurr = Find(pCurrItem);
	}
	
	POS pos = Find(pGotoItem, posCurr);

	if (pos != NULL)
	{
		m_pos = pos;
		m_pGotoItem = pGotoItem;
	}
}

CExBaseList* CItemContainer::GetGuideBookAllItems()
{
	return &m_oListItems;
}

//异常恢复功能接口
//调用CGbItemBase::SerializeState
//保存容器中的测试项目的状态到文件中
long CItemContainer::SaveItemsStateToFile(const CString &strFile)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.SetCalSizeMode();
	BinarySerialize(oBuffer);

	oBuffer.SetWriteMode();
	BinarySerialize(oBuffer);

	oBuffer.SaveToFile(strFile);
	return 0;
}

//恢复测试项目的测试状态
long CItemContainer::RestoreFromFile(const CString &strFile)
{
	DeleteAll();
	CBinarySerialBuffer oBuffer;

	oBuffer.OpenFromFile(strFile);

	oBuffer.SetReadMode();
	BinarySerialize(oBuffer);
	return 0;
}

long CItemContainer::AddItemsBeforeCurr(CExBaseList &oList)
{
	POS pos = oList.GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posCurr = NULL;
	 
	while(pos != NULL)
	{
		p = (CExBaseObject *)oList.GetNext(pos);
		posCurr = InsertBefore(m_pos, p);
	}

	if (posCurr != NULL)
	{
		m_pos = posCurr;
	}

	return 0;
}

//保存容器中的项目的状态
long  CItemContainer::BinarySerialize(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase* pItem = NULL;
	pItem = GetFirstItem();

	while (pItem!=NULL)
	{
		pItem->SerializeState(oBinaryBuffer);
		pItem = GetNextItem();
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//2019-4-26   多装置测试模式下，每台装置独立执行测试的模式
void CItemContainer::AddMdvGuideBook(CGuideBook *pGuideBook)
{
	POS pos = m_listMdvGuideBook.Find(pGuideBook);

	if (pos == NULL)
	{
		m_listMdvGuideBook.AddTail(pGuideBook);
	}
}

void CItemContainer::GetAllTestItems(CExBaseList &listAllItems)
{
	POS pos = m_oListItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	UINT nClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase*)m_oListItems.GetNext(pos);
		nClassID = pItem->GetClassID();

		if (Gb_ISTestingSubtem(pItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			listAllItems.AddTail(pItem); //将分类节点也加进来  shaolei  2019.06.23
			pItems = (CItems *)pItem;

			if (pItems->IsMdvTestEach())
			{
				GetAllTestItemsLoop(listAllItems, pItems);
				continue;
			}
		}
		else
		{
			listAllItems.AddTail(pItem);
		}
	}

}

void CItemContainer::AddItemsLoop(CItems *pItems, long *pnItemIndex, BOOL bSetIndex)
{
	CItemsLoopContainer *pItemsLoop = new CItemsLoopContainer(pItems, pnItemIndex,  bSetIndex);
	m_listItemsLoop.AddTail(pItemsLoop);
}

void CItemContainer::QueryItemsLoop(CItems *pItems, PGBFILTERNODE pNode, BOOL bUseSel)
{
	CItemsLoopContainer *pLoop = FindLoopByItems(pItems);
	ASSERT (pLoop != NULL);

	if (pLoop == NULL)
	{
		return;
	}

	QueryItemsLoop(pLoop, pNode, bUseSel);

	POS pos = m_listMdvGuideBook.GetHeadPosition();
	CGuideBook *pGuideBook = NULL;

	while (pos != NULL)
	{
		pGuideBook = (CGuideBook *)m_listMdvGuideBook.GetNext(pos);
		QueryItemsLoop(pLoop, pGuideBook, pNode, bUseSel);
	}
}

CItemsLoopContainer* CItemContainer::FindLoopByItems(CItems *pItems)
{
	CItemsLoopContainer *pLoop = NULL;
	CItemsLoopContainer *p = NULL;
	POS pos = m_listItemsLoop.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CItemsLoopContainer *)m_listItemsLoop.GetNext(pos);

		if (p->GetItems() == pItems)
		{
			pLoop = p;
			break;
		}
	}

	return pLoop;
}

void CItemContainer::QueryItemsLoop(CItemsLoopContainer *pLoop, PGBFILTERNODE pNode, BOOL bUseSel)
{
	POS pos = pLoop->m_oListItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	UINT nClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase*)pLoop->m_oListItems.GetNext(pos);
		nClassID = pItem->GetClassID();

		if (Gb_ISTestingSubtem(pItem))
		{
			continue;
		}

		pItem->m_nMdvTestEach = 1;
		QueryItem(pItem, nClassID, pNode, bUseSel);
	}
}

void CItemContainer::QueryItemsLoop(CItemsLoopContainer *pLoop, CGuideBook *pGuideBook, PGBFILTERNODE pNode, BOOL bUseSel)
{
	POS pos = pLoop->m_oListItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CGbItemBase *pItemOther = NULL;
	UINT nClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase*)pLoop->m_oListItems.GetNext(pos);
		nClassID = pItem->GetClassID();

		if (Gb_ISTestingSubtem(pItem))
		{
			continue;
		}

		pItemOther = (CGbItemBase*)Gb_GetItem(pGuideBook, pItem);
		pItemOther->m_nMdvTestEach = 1;
		pItem->m_nMdvTestEach = 1;
		
		QueryItem(pItemOther, nClassID, pNode, bUseSel);
	}
}

void CItemContainer::GetAllTestItemsLoop(CExBaseList &listAllItems, CItems *pItems)
{
	CItemsLoopContainer *pLoop = FindLoopByItems(pItems);
	ASSERT (pLoop != NULL);
	POS pos = pLoop->m_oListItems.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CGbItemBase*)pLoop->m_oListItems.GetNext(pos);
		nClassID = pItem->GetClassID();

		if (Gb_ISTestingSubtem(pItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			listAllItems.AddTail(pItem);  //将分类节点也加进来  shaolei 2019.06.23
			continue;
		}
		else
		{
			listAllItems.AddTail(pItem);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//2021-8-5  lijunqing  测试进度
void CItemContainer::GetTestProcess(long &nTotalItems, long &nCurrItem, long &nTotalTime, long &nRemainTime)
{
	nTotalItems = m_nItemCount;
	nCurrItem = m_nCurrFinishItem + 1;

// 	nCurrItem = FindIndex(m_pos);
// 
// 	if (nCurrItem < 0)
// 	{
// 		nCurrItem = nTotalItems;
// 	}
// 	else
// 	{
// 		nCurrItem++;
// 	}

	nTotalTime = nTotalItems * 30;
	nRemainTime = (nTotalItems - nCurrItem) * 30;
	m_nCurrFinishItem = nCurrItem;
}

void CItemContainer::SetPosByItem(CExBaseObject *pItem)
{
	m_pos = Find(pItem);
}