#include "stdafx.h"
#include "GbUnqualifiedItemTool.h"
#include "../../../Module/DataMngr/ValuesParse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
Device
...._BeforeTest_    _BFT_a1   _BFT_b1    _BFT_c1
....Items_1
........_BeforeTest_     _BFT_a2   _BFT_b2    _BFT_c2
........Items
........_AfterTest_    _	AFT_a2   _AFT_b2    _AFT_c2
....Items_2
........_BeforeTest_    _BFT_a3   _BFT_b3    _BFT_c3
........Items
........Items    Item###
........Items
........_AfterTest_   _AFT_a3   _AFT_b3    _AFT_c3
....Items_3
........_BeforeTest_    _BFT_a4   _BFT_b4    _BFT_c4
........_AfterTest_   _	AFT_a4   _AFT_b4    _AFT_c4
...._AfterTest_   _	AFT_a1   _AFT_b1    _AFT_c1
*/

/*
规则：
1、当前不合格项目M，其父项目分类N下，如果N的子项目分类中包含 _BeforeTest_和_AfterTest_项目分类，提取此项目分类下面前缀包含_AFT_和_BFT_的项目
2、以项目分类N为当前对象，获取其父项目分类Q，如果Q的子项目分类中包含 _BeforeTest_和_AfterTest_项目分类，提取此项目分类下面前缀包含_AFT_和_BFT_的项目
3、依次继续往上类推
4、如果不合格项目本身是_AFT_和_BFT_项目，作为普通项目处理
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGbUnqualifiedItem::CGbUnqualifiedItem()
{
	m_pItem = NULL;
}

CGbUnqualifiedItem::~CGbUnqualifiedItem()
{
	RemoveAll();
}


void CGbUnqualifiedItem::QueryBftAftItems()
{
	//首先添加当前不合格的项目节点
	AddTail(m_pItem);

	//当前节点的父节点
	CItems *pItems = (CItems*)m_pItem->GetParent();

	//重测所有子项目模式
	if (pItems->IsReTestAllChildMode())
	{
		QueryBftAftItems_AllChildItem(pItems, TRUE);

		pItems = (CItems*)pItems->GetParent();

		if (pItems->GetClassID() != GBCLASSID_GUIDEBOOK)
		{
			QueryBftAftItems(pItems);
		}
	}
	else
	{
		QueryBftAftItems(pItems);
	}
}

void CGbUnqualifiedItem::QueryBftAftItems_AllChildItem(CItems *pItems, BOOL bAddItems)
{//则全部项目要进行测试
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		if (Gb_IsGbItemClassID(p->GetClassID()))
		{
			AddTail(p);
		}
		else if (Gb_IsItemsBaseClassID(p->GetClassID()))
		{
			if (bAddItems)
			{
				QueryBftAftItems_AllChildItem((CItems*)p, bAddItems);
			}
		}
	}
}

//只对CItems下面的_BFT_、_AFT_进行处理
void CGbUnqualifiedItem::QueryBftAftItems_ChildItem_B_A(CItems *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	CString strTemp;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (!Gb_IsGbItemClassID(nClassID))
		{
			continue;
		}

		pItem = (CGbItemBase *)p;
		strTemp = pItem->m_strID.Left(5);

		if (strTemp == GBID_ItemPrefix_BeforeTest)
		{
			if (pItem->m_nIndex < m_pItem->m_nIndex)
			{
				AddHead(pItem);
			}
		}
		else if (strTemp == GBID_ItemPrefix_AfterTest)
		{
			if (pItem->m_nIndex > m_pItem->m_nIndex)
			{
				AddTail(pItem);
			}
		}
	}
}

void CGbUnqualifiedItem::QueryBftAftItems(CExBaseList *pListItems)
{
	POS pos = pListItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	CString strTemp;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pListItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{//项目节点
			pItem = (CGbItemBase *)p;
			strTemp = pItem->m_strID.Left(5);

			if (strTemp == GBID_ItemPrefix_BeforeTest)
			{//为_BFT_项目
				if (pItem->m_nIndex < m_pItem->m_nIndex)
				{//项目为当前项目的前驱项目
					AddHead(pItem);
				}
			}
			else if (strTemp == GBID_ItemPrefix_AfterTest)
			{//为_AFT_项目
				if (pItem->m_nIndex > m_pItem->m_nIndex)
				{//项目为当前项目的后驱项目
					AddTail(pItem);
				}
			}
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			if (p->m_strID.Find(GBID_BeforeTest_) >= 0)
			{//测试前处理项目，进行处理
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
			else if (p->m_strID.Find(GBID_AfterTest_) >= 0)
			{//测试后恢复项目，进行处理
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
		}
	}

	nClassID = pListItems->GetParent()->GetClassID();

	if (nClassID == GBCLASSID_GUIDEBOOK)
	{//如果遇到根节点，则返回
		return;
	}

	//获取上一级项目分类节点进行处理
	QueryBftAftItems((CExBaseList*)pListItems->GetParent());
}

//////////////////////////////////////////////////////////////////////////
CGbUnqualifiedItemEx::CGbUnqualifiedItemEx()
{
	m_pItem = NULL;
}

CGbUnqualifiedItemEx::~CGbUnqualifiedItemEx()
{
	RemoveAll();
}


void CGbUnqualifiedItemEx::QueryBftAftItems()
{
	//首先添加当前不合格的项目节点
	AddTail(m_pItem);

	//当前节点的父节点
	CItems *pItems = (CItems*)m_pItem->GetParent();

	//如果当前节点的父节点CItems，为项目分类节点，则全部项目要进行测试
	if (pItems->IsTypeRootNode())
	{
		QueryBftAftItems_AllChildItem(pItems);

		pItems = (CItems*)pItems->GetParent();
		if (pItems->GetClassID() != GBCLASSID_GUIDEBOOK)
		{
			QueryBftAftItems(pItems);
		}
	}
	else
	{
		QueryBftAftItems(pItems);
	}
}

void CGbUnqualifiedItemEx::QueryBftAftItems_AllChildItem(CItems *pItems)
{//则全部项目要进行测试
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		if (Gb_IsGbItemClassID(p->GetClassID()))
		{
			AddTail(p);
		}
	}
}

//只对CItems下面的_BFT_、_AFT_进行处理
void CGbUnqualifiedItemEx::QueryBftAftItems_ChildItem_B_A(CItems *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	CString strTemp;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (!Gb_IsGbItemClassID(nClassID))
		{
			continue;
		}

		pItem = (CGbItemBase *)p;
		strTemp = pItem->m_strID.Left(5);

		if (strTemp == GBID_ItemPrefix_BeforeTest)
		{
			if (pItem->m_nIndex < m_pItem->m_nIndex)
			{
				AddHead(pItem);
			}
		}
		else if (strTemp == GBID_ItemPrefix_AfterTest)
		{
			if (pItem->m_nIndex > m_pItem->m_nIndex)
			{
				AddTail(pItem);
			}
		}
	}
}

void CGbUnqualifiedItemEx::QueryBftAftItems(CExBaseList *pListItems)
{
	POS pos = pListItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	CString strTemp;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pListItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{//项目节点
			pItem = (CGbItemBase *)p;
			strTemp = pItem->m_strID.Left(5);

			if (strTemp == GBID_ItemPrefix_BeforeTest)
			{//为_BFT_项目
				if (pItem->m_nIndex < m_pItem->m_nIndex)
				{//项目为当前项目的前驱项目
					AddHead(pItem);
				}
			}
			else if (strTemp == GBID_ItemPrefix_AfterTest)
			{//为_AFT_项目
				if (pItem->m_nIndex > m_pItem->m_nIndex)
				{//项目为当前项目的后驱项目
					AddTail(pItem);
				}
			}
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			if (((CItems*)p)->IsTypeRootNode())
			{//如果是项目分类，则不进行处理
				continue;
			}

			if (p->m_strID.Find(GBID_BeforeTest_) >= 0)
			{//测试前处理项目，进行处理
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
			else if (p->m_strID.Find(GBID_AfterTest_) >= 0)
			{//测试后恢复项目，进行处理
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
		}
	}

	nClassID = pListItems->GetParent()->GetClassID();

	if (nClassID == GBCLASSID_GUIDEBOOK)
	{//如果遇到根节点，则返回
		return;
	}

	//获取上一级项目分类节点进行处理
	QueryBftAftItems((CExBaseList*)pListItems->GetParent());
}

//////////////////////////////////////////////////////////////////////////
//CGbUnqualifiedItemTool
CGbUnqualifiedItemTool::CGbUnqualifiedItemTool()
{
	m_pContainer = NULL;
}

CGbUnqualifiedItemTool::~CGbUnqualifiedItemTool()
{

}

void CGbUnqualifiedItemTool::QueryUnqualifiedItems(CGuideBook *pGuideBook, CExBaseList *pContainer)
{
	m_pContainer = pContainer;

	//检索所有不合格的项目，以及项目的前驱项目和后驱项目
	QueryUnqualifiedItems(pGuideBook);

	//对项目进行拍讯、整理
	ArrangeAllItems();
}

void CGbUnqualifiedItemTool::QueryUnqualifiedItems(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{//项目分类节点
			if ( ((CItems*)p)->GetState() != TEST_STATE_ELIGIBLE)
			{//不合格，则进行处理
				QueryUnqualifiedItems((CExBaseList*)p);
			}
			
		}
		else if (nClassID == GBCLASSID_DEVICE)
		{
			QueryUnqualifiedItems((CExBaseList*)p);
		}
		else if (Gb_IsGbItemClassID(nClassID))
		{//项目节点
			AddGbUnqualifiedItem((CGbItemBase*)p);
		}
	}
}

void CGbUnqualifiedItemTool::AddGbUnqualifiedItem(CGbItemBase *pItem)
{
	if (pItem->GetState() != TEST_STATE_INLEGIBLE)
	{//如果不是不合格节点，则返回
		return;
	}

	//暂时简单化处理，不考虑此种情况
	if (pItem->GetParent()->GetClassID() == GBCLASSID_DEVICE)
	{
		return;
	}

	CGbUnqualifiedItem *pNew = new CGbUnqualifiedItem();
	pNew->m_pItem = pItem;
	AddNewChild(pNew);
	
	pNew->QueryBftAftItems();
}

/*
如果有多个不合格项目，不同项目可能拥有相同的前驱项目和后驱项目，
因此，需要对检索出来的所有项目按照项目的编号进行顺序排列，
并且保证不出现重复项目
*/
void CGbUnqualifiedItemTool::ArrangeAllItems()
{
	POS pos = GetHeadPosition();
	CGbUnqualifiedItem *pUnqualifiedItem = NULL;

	while (pos != NULL)
	{
		pUnqualifiedItem = (CGbUnqualifiedItem *)GetNext(pos);
		ArrangeAllItem(pUnqualifiedItem);
	}
}

void CGbUnqualifiedItemTool::ArrangeAllItem(CGbUnqualifiedItem *pUnqualifiedItem)
{
	POS pos = pUnqualifiedItem->GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)pUnqualifiedItem->GetNext(pos);
		InsertItem(pItem);
	}
}

CGbItemBase* CGbUnqualifiedItemTool::FindItemByIndex(long nIndex)
{
	POS pos = m_pContainer->GetHeadPosition();
	CGbItemBase *pItem = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)m_pContainer->GetNext(pos);

		if (pItem->m_nIndex == nIndex)
		{
			pFind = pItem;
			break;
		}
	}

	return pFind;
}

void CGbUnqualifiedItemTool::InsertItem(CGbItemBase *pItem)
{
	//项目已经存在，则返回
	if (FindItemByIndex(pItem->m_nIndex))
	{
		return;
	}

	POS pos = m_pContainer->GetHeadPosition();
	CGbItemBase *pCurr = NULL;

	while (pos != NULL)
	{
		pCurr = (CGbItemBase *)m_pContainer->GetAt(pos);

		if (pCurr->m_nIndex > pItem->m_nIndex)
		{
			m_pContainer->InsertBefore(pos, pItem);
			break;
		}

		m_pContainer->GetNext(pos);
	}

	if (pos == NULL)
	{
		m_pContainer->AddTail(pItem);
	}
}

void CGbUnqualifiedItemTool::Query_BFT_Items(CGuideBook *pGuideBook, CExBaseList *pContainer)
{
	CGbItemBase *pFirst =  (CGbItemBase*)pContainer->GetHead();
	CGbUnqualifiedItem oGbUnqualifiedItem;
	oGbUnqualifiedItem.m_pItem = pFirst;
	m_pContainer = pContainer;
	oGbUnqualifiedItem.QueryBftAftItems();

	POS pos = oGbUnqualifiedItem.Find(pFirst);
	oGbUnqualifiedItem.GetPrev(pos);
	CGbItemBase *p = NULL;

	while (pos != NULL)
	{
		p = (CGbItemBase*)oGbUnqualifiedItem.GetPrev(pos);
		InsertItem(p);
	}
}

