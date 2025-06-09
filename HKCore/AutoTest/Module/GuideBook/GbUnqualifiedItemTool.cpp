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
����
1����ǰ���ϸ���ĿM���丸��Ŀ����N�£����N������Ŀ�����а��� _BeforeTest_��_AfterTest_��Ŀ���࣬��ȡ����Ŀ��������ǰ׺����_AFT_��_BFT_����Ŀ
2������Ŀ����NΪ��ǰ���󣬻�ȡ�丸��Ŀ����Q�����Q������Ŀ�����а��� _BeforeTest_��_AfterTest_��Ŀ���࣬��ȡ����Ŀ��������ǰ׺����_AFT_��_BFT_����Ŀ
3�����μ�����������
4��������ϸ���Ŀ������_AFT_��_BFT_��Ŀ����Ϊ��ͨ��Ŀ����
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
	//������ӵ�ǰ���ϸ����Ŀ�ڵ�
	AddTail(m_pItem);

	//��ǰ�ڵ�ĸ��ڵ�
	CItems *pItems = (CItems*)m_pItem->GetParent();

	//�ز���������Ŀģʽ
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
{//��ȫ����ĿҪ���в���
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

//ֻ��CItems�����_BFT_��_AFT_���д���
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
		{//��Ŀ�ڵ�
			pItem = (CGbItemBase *)p;
			strTemp = pItem->m_strID.Left(5);

			if (strTemp == GBID_ItemPrefix_BeforeTest)
			{//Ϊ_BFT_��Ŀ
				if (pItem->m_nIndex < m_pItem->m_nIndex)
				{//��ĿΪ��ǰ��Ŀ��ǰ����Ŀ
					AddHead(pItem);
				}
			}
			else if (strTemp == GBID_ItemPrefix_AfterTest)
			{//Ϊ_AFT_��Ŀ
				if (pItem->m_nIndex > m_pItem->m_nIndex)
				{//��ĿΪ��ǰ��Ŀ�ĺ�����Ŀ
					AddTail(pItem);
				}
			}
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			if (p->m_strID.Find(GBID_BeforeTest_) >= 0)
			{//����ǰ������Ŀ�����д���
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
			else if (p->m_strID.Find(GBID_AfterTest_) >= 0)
			{//���Ժ�ָ���Ŀ�����д���
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
		}
	}

	nClassID = pListItems->GetParent()->GetClassID();

	if (nClassID == GBCLASSID_GUIDEBOOK)
	{//����������ڵ㣬�򷵻�
		return;
	}

	//��ȡ��һ����Ŀ����ڵ���д���
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
	//������ӵ�ǰ���ϸ����Ŀ�ڵ�
	AddTail(m_pItem);

	//��ǰ�ڵ�ĸ��ڵ�
	CItems *pItems = (CItems*)m_pItem->GetParent();

	//�����ǰ�ڵ�ĸ��ڵ�CItems��Ϊ��Ŀ����ڵ㣬��ȫ����ĿҪ���в���
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
{//��ȫ����ĿҪ���в���
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

//ֻ��CItems�����_BFT_��_AFT_���д���
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
		{//��Ŀ�ڵ�
			pItem = (CGbItemBase *)p;
			strTemp = pItem->m_strID.Left(5);

			if (strTemp == GBID_ItemPrefix_BeforeTest)
			{//Ϊ_BFT_��Ŀ
				if (pItem->m_nIndex < m_pItem->m_nIndex)
				{//��ĿΪ��ǰ��Ŀ��ǰ����Ŀ
					AddHead(pItem);
				}
			}
			else if (strTemp == GBID_ItemPrefix_AfterTest)
			{//Ϊ_AFT_��Ŀ
				if (pItem->m_nIndex > m_pItem->m_nIndex)
				{//��ĿΪ��ǰ��Ŀ�ĺ�����Ŀ
					AddTail(pItem);
				}
			}
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			if (((CItems*)p)->IsTypeRootNode())
			{//�������Ŀ���࣬�򲻽��д���
				continue;
			}

			if (p->m_strID.Find(GBID_BeforeTest_) >= 0)
			{//����ǰ������Ŀ�����д���
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
			else if (p->m_strID.Find(GBID_AfterTest_) >= 0)
			{//���Ժ�ָ���Ŀ�����д���
				QueryBftAftItems_ChildItem_B_A((CItems*)p);
			}
		}
	}

	nClassID = pListItems->GetParent()->GetClassID();

	if (nClassID == GBCLASSID_GUIDEBOOK)
	{//����������ڵ㣬�򷵻�
		return;
	}

	//��ȡ��һ����Ŀ����ڵ���д���
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

	//�������в��ϸ����Ŀ���Լ���Ŀ��ǰ����Ŀ�ͺ�����Ŀ
	QueryUnqualifiedItems(pGuideBook);

	//����Ŀ������Ѷ������
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
		{//��Ŀ����ڵ�
			if ( ((CItems*)p)->GetState() != TEST_STATE_ELIGIBLE)
			{//���ϸ�����д���
				QueryUnqualifiedItems((CExBaseList*)p);
			}
			
		}
		else if (nClassID == GBCLASSID_DEVICE)
		{
			QueryUnqualifiedItems((CExBaseList*)p);
		}
		else if (Gb_IsGbItemClassID(nClassID))
		{//��Ŀ�ڵ�
			AddGbUnqualifiedItem((CGbItemBase*)p);
		}
	}
}

void CGbUnqualifiedItemTool::AddGbUnqualifiedItem(CGbItemBase *pItem)
{
	if (pItem->GetState() != TEST_STATE_INLEGIBLE)
	{//������ǲ��ϸ�ڵ㣬�򷵻�
		return;
	}

	//��ʱ�򵥻����������Ǵ������
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
����ж�����ϸ���Ŀ����ͬ��Ŀ����ӵ����ͬ��ǰ����Ŀ�ͺ�����Ŀ��
��ˣ���Ҫ�Լ���������������Ŀ������Ŀ�ı�Ž���˳�����У�
���ұ�֤�������ظ���Ŀ
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
	//��Ŀ�Ѿ����ڣ��򷵻�
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

