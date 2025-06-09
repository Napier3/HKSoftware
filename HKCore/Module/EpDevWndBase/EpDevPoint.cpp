#include "stdafx.h"
#include "EpDevPoint.h"
#include "EpDevWndFactory.h"
#include "EpDevGlobalDefine.h"

CEpDevPoint::CEpDevPoint()
{
	m_bExpand = TRUE;
	m_nShow = EPDES_SHOW;
	m_nChildBottom = 0;
	m_nChildTop = 0;
}

CEpDevPoint::~CEpDevPoint()
{

}

long CEpDevPoint::AdjustChildrenPos(long nLeft,long nTop)
{
	POS pos = GetHeadPosition();
	CEpDevWnd* pWnd = NULL;
	
	while(pos != NULL)
	{
		pWnd = (CEpDevWnd*)GetNext(pos);
		pWnd->AdjustPos(nLeft,nTop);
		
		nTop += pWnd->m_nVirtualHeight + EPDWND_GAP_VERT;

		while (nTop <= pWnd->GetWndBottom())
		{
                   nTop += EPDWND_GAP_VERT;
		}
		
	}

	return 0;
}

long CEpDevPoint::CalSize(CSize &sz)
{
	if(m_bExpand == EPDES_CLOSE)
	{
		sz.cx = 0;
		sz.cy = 0;
	}
	else
	{
		CalChildrenSize(sz);
		int nCount = GetCount();

		if (nCount>1)
		{
			sz.cy +=(nCount-1)*EPDWND_GAP_VERT;
		}
	}
	m_nVirtualWidth = sz.cx;
	m_nVirtualHeight = sz.cy;

	return 0;
}

BOOL CEpDevPoint::UICreateChildren(CWnd *pParent)
{
	if(m_pData == NULL)
	{
		return FALSE;
	}

	if(!m_pData->IsBaseList())
	{
		return FALSE;
	}

	CExBaseList* pList = (CExBaseList*)m_pData;
	POS pos = pList->GetHeadPosition();
	CExBaseObject* pChildData = NULL;
	CEpDevBase* pDevWnd = NULL;

	while(pos != NULL)
	{
		pChildData = pList->GetNext(pos);

		pDevWnd = CEpDevWndFactory::CreateDevWnd(pChildData,pParent);
		ASSERT(pDevWnd != NULL);

		if(pDevWnd != NULL)
		{
			AddTail(pDevWnd);
			pDevWnd->m_pData = pChildData;
			pDevWnd->CBaseObject::SetParent(this);
			//在CreateDevWnd函数中调用了UICreateOwn...
			//pDevWnd->UICreateOwn(pParent);
		}
	}

	return TRUE;
}

BOOL CEpDevPoint::DestroyChildren()
{
	return TRUE;
}

BOOL CEpDevPoint::DestroyOwn()
{
	return TRUE;
}

void CEpDevPoint::DrawLinkLines(CDC *pDC)
{
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		CEpDevWnd* pDevBase = (CEpDevWnd*)GetNext(pos);

		if(pDevBase->IsShow())
		{
			EPD_DrawLinkLine(this->GetConnectPoint(),pDevBase->GetConnectPoint(),pDC);
			pDevBase->DrawLinkLines(pDC);
		}
	}
}

void CEpDevPoint::Show(UINT nShow)
{
	if (m_bExpand)
	{
		ShowChildren(nShow);

		////如果隐藏子对象
		//if (nShow == 0)
		//{
		//	m_bExpand = 0;
		//}
	}
	else
	{
		ShowChildren(EPDES_HIDE);
	}
	
}

long CEpDevPoint::Expand(long nExpand)
{
	if(nExpand == EPDES_EXPAND)
	{
		ShowChildren(EPDES_SHOW);
	}
	else
	{
		ShowChildren(EPDES_HIDE);
	}

	m_bExpand = nExpand;

	return m_bExpand;
}

void CEpDevPoint::GetChildSize()
{
	POS pos = GetHeadPosition();
	CEpDevWnd* pWnd = NULL;

	if(pos != NULL)
	{
		pWnd = (CEpDevWnd*)GetAt(pos);
		m_nChildTop = pWnd->GetWndTop();
		pos = GetTailPosition();
		pWnd = (CEpDevWnd*)GetAt(pos);
		if (GetCount() == 1)
		{
			m_nChildBottom = pWnd->GetWndTop() + pWnd->GetWndHeight();
		}
		else
		{
			m_nChildBottom = pWnd->GetWndTop();
		}
		
	}
	else
	{
		m_nChildTop = 0;
		m_nChildBottom = 0;
	}
}

void CEpDevPoint::ReArrangeChildren()
{
	int nCount = GetCount();
	CEpDevWnd* pWndCur = NULL;
	CEpDevWnd* pWndNext = NULL;

	for (int i=0;i<nCount-1;i++)
	{
		for (int j=0;j<nCount-1;j++)
		{
			pWndCur = (CEpDevWnd*)GetAt(j);
			pWndNext = (CEpDevWnd*)GetAt(j+1);
		
			if (pWndCur->GetWndTop() > pWndNext->GetWndTop())
			{
// 				if (pWndCur->m_pData->GetClassID() == EPDCLASSID_EPDPARSEPACKGE||pWndCur->m_pData->GetClassID() == EPDCLASSID_EPDPROCEDURE||
// 					pWndCur->m_pData->GetClassID() == EPDCLASSID_EPDPODUCEPACKGE || pWndCur->m_pData->GetClassID() == EPDCLASSID_EPDTTPACKAGE)
// 				{
// 					continue;
// 				}
				MoveDown(pWndCur);
			}
		}
	}
}

void CEpDevPoint::SetChildrenShowEx(CEpDevBase* pDevBase)
{
	if(pDevBase->IsBaseList())
	{
		CEpDevWnd* pWnd = (CEpDevWnd*)pDevBase;
		POS pos = pWnd->GetHeadPosition();

		while(pos != NULL)
		{
			CEpDevPoint* pDevPoint = (CEpDevPoint*)GetNext(pos);
		
			if(pDevPoint->IsExpand() && pDevBase->IsExpand())
			{
				pDevPoint->SetChildrenShow(EPDES_SHOW);
			}
			else
			{
				pDevPoint->SetChildrenShow(EPDES_HIDE);
			}
		}
	}
}

void CEpDevPoint::SetChildrenShow(long nShow)
{
	POS pos = GetHeadPosition();

	CEpDevBase* pDevBase = NULL;

	while(pos != NULL)
	{
		pDevBase = (CEpDevBase*)GetNext(pos);
		pDevBase->SetShow(nShow);
		SetChildrenShowEx(pDevBase);
	}
}

