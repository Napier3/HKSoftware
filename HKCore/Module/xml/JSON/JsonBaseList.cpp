#include "StdAfx.h"
#include "JsonBaseList.h"

CJsonBaseList::CJsonBaseList()
{
	m_nMaxItemCount = -1;
	m_nCurrCount = 0;
	m_pJsonDest = NULL;
	m_pJsonSrc = NULL;
}

CJsonBaseList::~CJsonBaseList()
{
	FreeAll();
}

void CJsonBaseList::FreeAll()
{
	POS pos = GetHeadPosition();
	CJSON *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		CJSON_Delete(p);
	}

	RemoveAll();
}

BOOL CJsonBaseList::get_json_all_path(CJSON* itemFind, CJSON* itemSrc,  CJsonBaseList &listPath)
{
	if (json_is_object_or_array(itemSrc) <= 0)
	{
		return FALSE;
	}

	if (itemSrc->child == NULL)
	{//�Ӷ���Ϊ�գ�����
		return FALSE;
	}

	//����json�����ӽڵ�
	CJSON *child = itemSrc->child;

	while (child != NULL)
	{
		if (child == itemFind)
		{
			listPath.AddHead(child);
			return true;
		}
		else
		{
			if (json_is_object_or_array(child) > 0)
			{
				if (get_json_all_path(itemFind, child, listPath))
				{
					listPath.AddHead(child);//��Ӹ�����
					return TRUE;
				}
			}
			
			child=child->next;
		}
	}

	return FALSE;
}

CJSON* CJsonBaseList::add_to_json(CJSON *pCurr, CJSON *pParent)
{
	CJSON *child = pParent->child;

	while ( child != NULL)
	{
		if (json_cmp_object(child, pCurr) == 1)
		{
			return child;
		}

		child = child->next;
	}

	//����JSON��ֻ������������
	CJSON *pNew = CJSON_Copy(pCurr);
	CJSON_AddItemToArray(pParent, pNew);
	return pNew;
}

void CJsonBaseList::add_to_json(CJsonBaseList &listPath)
{
	//long m_nCurrCount;
	//std::list<CJSON*> m_listJsonRslt;
	if (m_pJsonDest == NULL)
	{
		m_pJsonDest = CJSON_Duplicate(m_pJsonSrc, 0);
		AddTail(m_pJsonDest);
		m_nCurrCount = 1;
	}
	else
	{
		if (m_nMaxItemCount > 0)
		{
			if (m_nCurrCount >= 5)
			{//�����ǰ��Ԫ���Ѿ�����5�����򴴽�һ���µĸ��ڵ����
				m_pJsonDest = CJSON_Duplicate(m_pJsonSrc, 0);
				AddTail(m_pJsonDest);
				m_nCurrCount = 1;
			}
			else
			{
				m_nCurrCount++;
			}
		}
		else
		{
			m_nCurrCount++;
		}
	}

	//����listPathԪ�أ������һ����ʼ��������ݶ���
	POS pos = listPath.GetHeadPosition();
	CJSON *p = NULL;
	CJSON *pParent = m_pJsonDest;
	CJSON *item = (CJSON*)listPath.GetTail();

	while (pos != NULL)
	{
		p = (CJSON *)listPath.GetNext(pos);

		if (item == p)
		{
			break;
		}

		pParent = add_to_json(p, pParent);

		if (pParent == NULL)
		{
			break;
		}
	}

	if (item == p)
	{
		CJSON *pNew = CJSON_Duplicate(item, 1);
		CJSON_AddItemToArray(pParent, pNew);
	}
}

void CJsonBaseList::add_to_json(CJSON* item)
{
	CJsonBaseList listPath;

	if (get_json_all_path(item, m_pJsonSrc, listPath))
	{
		add_to_json(listPath);
	}

	listPath.RemoveAll();
}

void CJsonBaseList::ClearList()
{
	m_pJsonDest = NULL;
	FreeAll();
	m_nCurrCount = 0;
}
