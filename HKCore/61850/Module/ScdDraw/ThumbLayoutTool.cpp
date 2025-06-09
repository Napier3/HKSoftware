//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "ThumbLayoutTool.h"

//////////////////////////////////////////////////////////////////////////
//CThumbLayoutElement
CThumbLayoutElement::CThumbLayoutElement()
{
	m_pIedRef = NULL;
	m_nPos = ThumbLayoutElement_pos_None;
	m_nPosBackup = ThumbLayoutElement_pos_None;
}

CThumbLayoutElement::~CThumbLayoutElement()
{

}

void CThumbLayoutElement::BackupPos()
{
	m_nPosBackup = m_nPos;
}

void CThumbLayoutElement::RestorePos()
{
	m_nPos = m_nPosBackup;
}

//////////////////////////////////////////////////////////////////////////
//CThumbLayoutGroup
CThumbLayoutGroup::CThumbLayoutGroup()
{
	m_nLinkCount = 0;
	m_pMainElement = NULL;
	m_nLength = 0;
}

CThumbLayoutGroup::~CThumbLayoutGroup()
{
	m_listNeedLayoutElement.RemoveAll();
	m_listHasLayoutElement.RemoveAll();
}

void CThumbLayoutGroup::InitGroup(CThumbLayoutElement *pIedElement)
{
	m_pMainElement = pIedElement;

	CXScdDrawIedThumbnail *pIed = pIedElement->m_pIedRef;
	CXScdDrawIedThumbnail *pIedFind = NULL;
	POS pos = pIed->GetHeadPosition();
	CXScdDrawCtrl_ThumbBase *pCtrlThumb = NULL;
	CXScdDrawLine_Ctrls *pLine = NULL;
	POS posLine = NULL;
	CThumbLayoutElement *pFindElement = NULL;

	//遍历每一个缩略图控制块
	while (pos != NULL)
	{
		pCtrlThumb = (CXScdDrawCtrl_ThumbBase *)pIed->GetNext(pos);
		posLine = pCtrlThumb->GetHeadPosition();

		//遍历每一个缩略图控制块的连接线
		while (posLine != NULL)
		{
			pLine = (CXScdDrawLine_Ctrls *)pCtrlThumb->GetNext(posLine);
			
			//连接线相关联的合并单元、智能终端
			if(pLine->m_pBeginElement == pCtrlThumb)
			{
				pIedFind = (CXScdDrawIedThumbnail *)pLine->m_pEndElement->GetParent();
			}
			else
			{
				pIedFind = (CXScdDrawIedThumbnail *)pLine->m_pBeginElement->GetParent();
			}

			//在管理对象中查找合并单元、智能终端对象，在此避开保护对象、测控对象本身之间的连接
			pFindElement = CThumbLayoutTool::FindMuStElement(pIedFind);

			if (pFindElement != NULL)
			{
				m_nLinkCount++;
				m_listNeedLayoutElement.AddTail(pFindElement);
			}
		}
	}
}

long CThumbLayoutGroup::CalTotalLength()
{
	POS pos = m_listHasLayoutElement.GetHeadPosition();
	CThumbLayoutElement *pElement = NULL;
	m_nLength = 0;

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)m_listHasLayoutElement.GetNext(pos);
		m_nLength += abs(pElement->m_nPos - m_pMainElement->m_nPos);
	}

	return m_nLength;
}

void CThumbLayoutGroup::InitGroupLements()
{
	POS pos = m_listNeedLayoutElement.GetHeadPosition();
	CThumbLayoutElement *pElement = NULL;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pElement = (CThumbLayoutElement *)m_listHasLayoutElement.GetNext(pos);
		
		if (pElement->HasLayout())
		{
			m_listHasLayoutElement.AddTail(pElement);
			m_listNeedLayoutElement.RemoveAt(posPrev);
		}
	}
}

void CThumbLayoutGroup::LayoutElements(long nBeginIndex, long nFlag)
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;
	CThumbLayoutElement *pElement2 = NULL;
	long nIndex = 0;

	if (nFlag > 0)
	{
		pos = m_listNeedLayoutElement.GetHeadPosition();

		while (pos != NULL)
		{
			pElement = (CThumbLayoutElement *)m_listNeedLayoutElement.GetNext(pos);
			pElement->m_nPos = nBeginIndex + nIndex;
			nIndex++;
		}
	}
	else
	{
		pos = m_listNeedLayoutElement.GetTailPosition();

		while (pos != NULL)
		{
			pElement = (CThumbLayoutElement *)m_listNeedLayoutElement.GetPrev(pos);
			pElement->m_nPos = nBeginIndex - nIndex;
			nIndex++;
		}
	}
}

void CThumbLayoutGroup::ResetLayout()
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;

	pos = m_listNeedLayoutElement.GetHeadPosition();

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)m_listNeedLayoutElement.GetNext(pos);
		pElement->ResetLayout();
	}
}

void CThumbLayoutGroup::CalMainElementPos()
{
	long nMin1=65536, nMin2=65536;
	long nMax1=-65536, nMax2=-65536;
	long nMin = 65536, nMax=-65536;

	GetMinPos(&m_listHasLayoutElement, nMin1);
	GetMaxPos(&m_listHasLayoutElement, nMax1);
	GetMinPos(&m_listNeedLayoutElement, nMin2);
	GetMaxPos(&m_listNeedLayoutElement, nMax2);

	nMin = min(nMin1, nMin2);
	nMax = min(nMax1, nMax2);

	if (nMin == 65536)
	{
		return;
	}

	m_pMainElement->m_nPos = (nMin + nMax2) / 2;
}

void CThumbLayoutGroup::BackupPos()
{
	BackupPos(&m_listHasLayoutElement);
	BackupPos(&m_listNeedLayoutElement);
}

void CThumbLayoutGroup::RestorePos()
{
	RestorePos(&m_listHasLayoutElement);
	RestorePos(&m_listNeedLayoutElement);
}

void CThumbLayoutGroup::BackupPos(CExBaseList *pList)
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pList->GetNext(pos);
		pElement->BackupPos();
	}

}

void CThumbLayoutGroup::RestorePos(CExBaseList *pList)
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pList->GetNext(pos);
		pElement->RestorePos();
	}
}

long CThumbLayoutGroup::GetMinPos(CExBaseList *pList, long &nValue)
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pList->GetNext(pos);

		if (nValue > pElement->m_nPos)
		{
			nValue = pElement->m_nPos;
		}
	}

	return nValue;
}

long CThumbLayoutGroup::GetMaxPos(CExBaseList *pList, long &nValue)
{
	POS pos = NULL;
	CThumbLayoutElement *pElement = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pList->GetNext(pos);

		if (nValue < pElement->m_nPos)
		{
			nValue = pElement->m_nPos;
		}
	}

	return nValue;
}
//////////////////////////////////////////////////////////////////////////
//CThumbLayoutTool

CThumbLayoutTool* CThumbLayoutTool::g_pThumbLayoutTool = NULL;
long CThumbLayoutTool::g_nThumbLayoutToolRef = 0;

CThumbLayoutTool::CThumbLayoutTool()
{
	
}

CThumbLayoutTool::~CThumbLayoutTool()
{
	m_listProtLayout.RemoveAll();
	m_listMeasLayout.RemoveAll();
}

CThumbLayoutTool* CThumbLayoutTool::Create()
{
	g_nThumbLayoutToolRef++;

	if (g_nThumbLayoutToolRef == 1)
	{
		g_pThumbLayoutTool = new CThumbLayoutTool();
	}

	return g_pThumbLayoutTool;
}

void CThumbLayoutTool::Release()
{
	g_nThumbLayoutToolRef--;

	if (g_nThumbLayoutToolRef == 0)
	{
		delete g_pThumbLayoutTool;
		g_pThumbLayoutTool = NULL;
	}
}

CThumbLayoutElement* CThumbLayoutTool::FindElement(CXScdDrawIedThumbnail *pIed)
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CThumbLayoutElement *pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listProtIedElement);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listMeasIedElement);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listMuStIedElement);

	if (pFind != NULL)
	{
		return pFind;
	}

	return pFind;
}

CThumbLayoutElement* CThumbLayoutTool::FindProtElement(CXScdDrawIedThumbnail *pIed)
{
	CThumbLayoutElement *pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listProtIedElement);

	return pFind;
}

CThumbLayoutElement* CThumbLayoutTool::FindMeasElement(CXScdDrawIedThumbnail *pIed)
{
	CThumbLayoutElement *pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listMeasIedElement);

	return pFind;
}

CThumbLayoutElement* CThumbLayoutTool::FindMuStElement(CXScdDrawIedThumbnail *pIed)
{
	CThumbLayoutElement *pFind = g_pThumbLayoutTool->FindElement(pIed, &g_pThumbLayoutTool->m_listMuStIedElement);

	return pFind;
}

CThumbLayoutElement* CThumbLayoutTool::FindElement(CXScdDrawIedThumbnail *pIed, CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CThumbLayoutElement *p = NULL;
	CThumbLayoutElement *pFind = NULL;

	while (pos != NULL)
	{
		p = (CThumbLayoutElement *)pList->GetNext(pos);

		if (p->m_pIedRef == pIed)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CThumbLayoutTool::InitProtElement(CExBaseList *pListIed)
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CExBaseList *pList = &g_pThumbLayoutTool->m_listProtIedElement;
	POS pos = pListIed->GetHeadPosition();
	CXScdDrawIedThumbnail *pIed = NULL;
	
	while (pos != NULL)
	{
		pIed = (CXScdDrawIedThumbnail *)pListIed->GetNext(pos);
		CThumbLayoutElement *pNew = new CThumbLayoutElement();
		pNew->m_pIedRef = pIed;
		pList->AddTail(pNew);
	}
}


void CThumbLayoutTool::InitMeasElement(CExBaseList *pListIed)
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CExBaseList *pList = &g_pThumbLayoutTool->m_listMeasIedElement;
	POS pos = pListIed->GetHeadPosition();
	CXScdDrawIedThumbnail *pIed = NULL;

	while (pos != NULL)
	{
		pIed = (CXScdDrawIedThumbnail *)pListIed->GetNext(pos);
		CThumbLayoutElement *pNew = new CThumbLayoutElement();
		pNew->m_pIedRef = pIed;
		pList->AddTail(pNew);
	}
}

void CThumbLayoutTool::InitMuStElement(CExBaseList *pListIed)
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CExBaseList *pList = &g_pThumbLayoutTool->m_listMuStIedElement;
	POS pos = pListIed->GetHeadPosition();
	CXScdDrawIedThumbnail *pIed = NULL;

	while (pos != NULL)
	{
		pIed = (CXScdDrawIedThumbnail *)pListIed->GetNext(pos);
		CThumbLayoutElement *pNew = new CThumbLayoutElement();
		pNew->m_pIedRef = pIed;
		pList->AddTail(pNew);
	}
}

void CThumbLayoutTool::InitProtGroup()
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CExBaseList *pListElement = &g_pThumbLayoutTool->m_listProtIedElement;
	CExBaseList *pListGroup   = &g_pThumbLayoutTool->m_listProtGroup;

	POS pos = pListElement->GetHeadPosition();
	CThumbLayoutElement *pElement = NULL;

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pListElement->GetNext(pos);
		CThumbLayoutGroup *pNew = new CThumbLayoutGroup();
		pNew->InitGroup(pElement);
		pListGroup->AddTail(pNew);
	}
}

void CThumbLayoutTool::InitMeasGroup()
{
	ASSERT (g_pThumbLayoutTool != NULL);

	CExBaseList *pListElement = &g_pThumbLayoutTool->m_listMeasIedElement;
	CExBaseList *pListGroup   = &g_pThumbLayoutTool->m_listMeasGroup;

	POS pos = pListElement->GetHeadPosition();
	CThumbLayoutElement *pElement = NULL;

	while (pos != NULL)
	{
		pElement = (CThumbLayoutElement *)pListElement->GetNext(pos);
		CThumbLayoutGroup *pNew = new CThumbLayoutGroup();
		pNew->InitGroup(pElement);
		pListGroup->AddTail(pNew);
	}
}

void CThumbLayoutTool::LayoutProtElement()
{
	ASSERT (g_pThumbLayoutTool != NULL);

	g_pThumbLayoutTool->_LayoutProtElement();
}

void CThumbLayoutTool::LayoutMeasElement()
{
	ASSERT (g_pThumbLayoutTool != NULL);

	g_pThumbLayoutTool->_LayoutMeasElement();
}


void CThumbLayoutTool::_LayoutProtElement()
{
	//排序
	_SortProtGroup(&m_listProtGroup);

	POS pos = m_listProtGroup.GetHeadPosition();
	CThumbLayoutGroup *pGroup = NULL;

	while (pos != NULL)
	{
		pGroup = (CThumbLayoutGroup *)m_listProtGroup.GetNext(pos);
		_AddGroup(pGroup, &m_listProtLayout);
	}
}

void CThumbLayoutTool::_SortProtGroup(CExBaseList *pList)
{
	CExBaseList listSort;
	listSort.Append(pList);
	pList->RemoveAll();
	POS pos = listSort.GetHeadPosition();
	CThumbLayoutGroup *pGroup = NULL;
	CThumbLayoutGroup *pCurr = NULL;

	while (pos != NULL)
	{
		pGroup = (CThumbLayoutGroup *)listSort.GetNext(pos);

		POS posDst = pList->GetHeadPosition();

		if (posDst == NULL)
		{
			pList->AddTail(pGroup);
		}
		else
		{
			while (pos != NULL)
			{
				pCurr = (CThumbLayoutGroup *)pList->GetAt(posDst);

				if (pGroup->m_nLinkCount > pCurr->m_nLinkCount)
				{
					pList->InsertBefore(posDst, pGroup);
					break;
				}
				else
				{
					pList->GetNext(posDst);
				}
			}
		}
	}

	listSort.RemoveAll();
}


void CThumbLayoutTool::_AddGroup(CThumbLayoutGroup *pGroup, CExBaseList *pDestList)
{
	pGroup->InitGroupLements();
	
	long nBeginIndex = 0;
	long nCount = pDestList->GetCount();
	long nIndex = 0;

	if (nCount == 0)
	{
		nBeginIndex = m_listMuStIedElement.GetCount();
		pGroup->LayoutElements(nBeginIndex, 1);
	}
	else
	{
		long *pnLayoutValue = new long[nCount+1];

		for (nIndex=0; nIndex<= nCount; nIndex++)
		{
			
		}

		delete pnLayoutValue;
	}
}

long CThumbLayoutTool::_CalLayoutValue(CThumbLayoutGroup *pGroup, CExBaseList *pDestList, long nPos)
{
	long nPosValue = 0;

	BackupPos(&m_listProtGroup);

	RestorePos(&m_listProtGroup);

	return 0;
}


void CThumbLayoutTool::BackupPos(CExBaseList *pList)
{
	POS pos = NULL;
	CThumbLayoutGroup *pGroup = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CThumbLayoutGroup *)pList->GetNext(pos);
		pGroup->BackupPos();
	}

}

void CThumbLayoutTool::RestorePos(CExBaseList *pList)
{
	POS pos = NULL;
	CThumbLayoutGroup *pGroup = NULL;

	pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pGroup = (CThumbLayoutGroup *)pList->GetNext(pos);
		pGroup->RestorePos();
	}
}

void CThumbLayoutTool::_LayoutMeasElement()
{

}

