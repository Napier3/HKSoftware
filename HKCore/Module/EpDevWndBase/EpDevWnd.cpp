#include "stdafx.h"
#include "EpDevWnd.h"
#include "EpDevPoint.h"

CEpDevWnd::CEpDevWnd()
{
	m_pDevMinimizeButton = NULL;
	m_pEpDevDeleteButton = NULL;
}

CEpDevWnd::~CEpDevWnd()
{

}

void CEpDevWnd::DrawSelectedState()
{

}

long CEpDevWnd::AdjustOwnPos(long nLeft,long nTop)
{
	if (this->GetClassID() == EPDCLASSID_DEVPOINT)
	{
		return 0;
	}

	//如何收缩状态则不考虑子对象区域
	if (!m_bExpand)
	{
		Show(EPDES_HIDE);	//2010-11-18
		m_pWindow->MoveWindow(nLeft,nTop,m_nWidth,m_nHeight);
		Show(m_nShow);
		//InitPpPos();
		return 0;
	}

	int oldTop = m_nTop;
	int oldLeft = m_nLeft;

	CEpDevPoint* pDevPoint = NULL;
	POS pos = GetHeadPosition();
	long nChildVirtualHeight = 0;
	LONG nChildTop,nChildBottom,nCount;
	nCount = 0;
	nChildBottom = nTop;
	nChildTop = nTop;

	while(pos != NULL)
	{
		pDevPoint = (CEpDevPoint*)GetNext(pos);
		ASSERT(pDevPoint->GetClassID() == EPDCLASSID_DEVPOINT);
		if(pDevPoint->IsExpand()&&pDevPoint->GetCount()>0)
		{
			pDevPoint->GetChildSize();

			if (nCount == 0)
			{
				nChildTop = pDevPoint->m_nChildTop;
			}
			nChildBottom =pDevPoint->m_nChildBottom;

			nCount++;
		}
	}

	int nHeight = nChildBottom - nChildTop;

	if(m_nHeight < nHeight)
	{
		
		m_nTop = (nTop>nChildTop?nTop:nChildTop) + (nHeight - m_nHeight)/2;
	}
	else
	{
		if (m_nHeight < m_nVirtualHeight)
		{
			m_nTop = (nTop>nChildTop?nTop:nChildTop);
		}
		else
		{
			m_nTop = nTop;
		}
		
	}

	m_nLeft = nLeft;

	if (m_nTop != oldTop||m_nLeft != oldLeft)
	{
		m_pWindow->Invalidate(TRUE);
	}

	m_pWindow->MoveWindow(m_nLeft,m_nTop,m_nWidth,m_nHeight);
	Show(m_nShow);
	
	return 0;
}

long CEpDevWnd::AdjustChildrenPos(long nLeft,long nTop)
{
	//如何属于收缩状态则返回
	if (!m_bExpand)
	{
		return 0;
	}

	POS pos = GetHeadPosition();
	CEpDevPoint* pDevPoint = NULL;

	//子对象的水平位置
	nLeft += m_nWidth + EPDWND_GAP_HORZ;

	while(pos != NULL)
	{
		pDevPoint = (CEpDevPoint*)GetNext(pos);
		//如果pDevPoint不是展开的，则不调整
		if(pDevPoint->IsExpand()&&pDevPoint->GetCount()>0)
		{
			pDevPoint->AdjustPos(nLeft,nTop);
			nTop += pDevPoint->m_nVirtualHeight  +EPDWND_GAP_VERT;

			CEpDevWnd* pWnd = (CEpDevWnd*)pDevPoint->GetTail();

			if (pWnd != NULL)
			{	
				while (nTop <= pWnd->GetWndBottom())
				{
					nTop += EPDWND_GAP_VERT;
				}
			}
		}
	}

	return 0;
}

long CEpDevWnd::CalSize(CSize &sz)
{
	CSize totalSize(0,0);
	sz.cx = m_nWidth;
	sz.cy = m_nHeight;

	int nCount = 0;

	//计算展开的子对象个数
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		CEpDevPoint* pPoint = (CEpDevPoint*)GetNext(pos);
		if (pPoint->GetCount()>0&&pPoint->IsExpand())
		{
			nCount++;
		}
	}


	//if(m_bExpand == EPDES_EXPAND)
	if(m_nShow == EPDES_SHOW)
	{
		CSize szChildren(0,0);
		CalChildrenSize(szChildren);
		if(szChildren.cx == 0 || szChildren.cy == 0)
		{
			//sz.cx = m_nWidth;
			//sz.cy = m_nHeight;
		}
		else
		{
			
			totalSize.cx += EPDWND_GAP_HORZ + szChildren.cx;
			totalSize.cy += (nCount-1)*EPDWND_GAP_VERT+  szChildren.cy;
		}
	}
	else
	{
		sz.cx = 0;
		sz.cy = 0;
	}

	if(totalSize.cy > sz.cy)
	{
		sz.cy = totalSize.cy;
	}
	if(totalSize.cx > sz.cx)
	{
		sz.cx += totalSize.cx;
	}

	m_nVirtualWidth = sz.cx;
	m_nVirtualHeight = sz.cy;

	return 0;
}

BOOL CEpDevWnd::UICreateChildren(CWnd *pParent)
{
	//遍历CEpDevWnd的子对象EpDevPoint，创建EpDevPoint的子对象
	//因为实际的CEpDevWnd为Dialog，所以其子对象已经存在
	//并且在其UICreateOwn中已经添加到链表中了

	ASSERT(m_pData != NULL);

	if(m_pData == NULL)
	{
		return FALSE;
	}

	//ASSERT(m_pData->IsBaseList());
	if(!m_pData->IsBaseList())
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();
	CEpDevBase* pDevPoint = NULL;
	
	while(pos != NULL)
	{
		pDevPoint = (CEpDevPoint*)GetNext(pos);
		ASSERT(pDevPoint != NULL);
		pDevPoint->UICreateChildren(pParent);//不是调用UICreateOwn
	}

	return TRUE;
}

BOOL CEpDevWnd::DestroyChildren()
{
	return TRUE;
}

void CEpDevWnd::Show(UINT nShow)
{
	//if(CEpDevBase::Show(nShow) == 0)
	//{
	//	return 0;
	//}
	
	CEpDevBase::Show(nShow);
	ShowChildren(nShow);
}

long CEpDevWnd::Expand(long nExpand)
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

CPoint CEpDevWnd::GetConnectPoint()
{
	ASSERT(m_pWindow != NULL);
	//InitPpPos();
	CRect rc;
	m_pWindow->GetWindowRect(rc);
	CWnd* pParent = m_pWindow->GetParent();
	pParent->ScreenToClient(rc);
	
	CPoint ptRet(0,0);
	ptRet.x = rc.left;
	ptRet.y = rc.top + 10;

	return ptRet;
}

void CEpDevWnd::DrawLinkLines(CDC *pDC)
{
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		CEpDevWnd* pDevBase = (CEpDevWnd*)GetNext(pos);
		if(pDevBase->IsShow())
		{
			pDevBase->DrawLinkLines(pDC);
		}
	}
}

void  CEpDevWnd::UnExpandChildren()
{
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		CEpDevPoint* pDevPoint = (CEpDevPoint*)GetNext(pos);
		pDevPoint->Expand(EPDES_CLOSE);
	}
}

