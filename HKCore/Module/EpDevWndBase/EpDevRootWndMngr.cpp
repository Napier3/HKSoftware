#include "stdafx.h"
#include "EpDevRootWndMngr.h"
#include "EpDevWndFactory.h"

CEpDevRootWndMngr::CEpDevRootWndMngr()
{
	m_bSaveDevWndMode = TRUE;
	m_pCurDevRootWnd = NULL;
	m_pParentWnd = NULL;
}

CEpDevRootWndMngr::~CEpDevRootWndMngr()
{
	Destroy();
}

CEpDevWnd* CEpDevRootWndMngr::CreateEpDevRootWnd(CExBaseObject *pData)
{
	return (CEpDevWnd*)CEpDevWndFactory::CreateDevWnd(pData, m_pParentWnd);
}

BOOL CEpDevRootWndMngr::ShowData(CExBaseObject *pData)
{
	CEpDevWnd *pDevWnd = (CEpDevWnd*)FindDevWnd(pData);

	if (pDevWnd == NULL)
	{
		pDevWnd = CreateEpDevRootWnd(pData);

		if (pDevWnd != NULL && IsSaveDevWndMode())
		{
			AddTail(pDevWnd);
		}
	}

	if (m_pCurDevRootWnd == pDevWnd)
	{
		return TRUE;
	}

	if (m_pCurDevRootWnd != NULL)
	{
		m_pCurDevRootWnd->Show(EPDES_HIDE);
	}

	m_pCurDevRootWnd = pDevWnd;

	if (m_pCurDevRootWnd != NULL)
	{
		m_pCurDevRootWnd->Show(EPDES_SHOW);
	}
	
	return TRUE;
}

CEpDevBase* CEpDevRootWndMngr::FindDevWnd(CExBaseObject *pData)
{
	POS pos = GetHeadPosition();
	CEpDevBase *pDevBase = NULL;

	while(pos != NULL)
	{
		pDevBase = (CEpDevBase*)GetNext(pos);

		if(pDevBase->m_pData == pData)
		{
			return pDevBase;
		}
	}

	return NULL;
}


void CEpDevRootWndMngr::Show()
{
	if(m_pCurDevRootWnd != NULL)
	{
		m_pCurDevRootWnd->Show(EPDES_SHOW);
	}
}

void CEpDevRootWndMngr::Hide()
{
	if(m_pCurDevRootWnd != NULL)
	{
		m_pCurDevRootWnd->Show(EPDES_HIDE);
	}
}

void CEpDevRootWndMngr::DrawLinkLines(CEpDevWnd* pDevWnd,CDC* pDC, COLORREF crColor)
{
	ASSERT (pDevWnd != NULL);

	if(pDevWnd == NULL)
	{
		return;
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, crColor);
	CPen *pOldPen = pDC->SelectObject(&pen);

	POS pos = pDevWnd->GetHeadPosition();

	while(pos != NULL)
	{
		CEpDevBase* pObj = (CEpDevWnd*)pDevWnd->GetNext(pos);
		pObj->DrawLinkLines(pDC);
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void CEpDevRootWndMngr::DrawLinkLines(CEpDevWnd* pDevWnd,CDC* pDC)
{
	if(pDevWnd==NULL)
	{
		pDevWnd = (CEpDevWnd*)m_pCurDevRootWnd;
	}

	if(pDevWnd == NULL)
	{
		return;
	}

	DrawLinkLines(pDevWnd, pDC, EPD_GetDevViewForeColor());
}

void CEpDevRootWndMngr::EraseLinkLines(CEpDevWnd* pDevWnd,CDC* pDC)
{
	if(pDevWnd==NULL)
	{
		pDevWnd = (CEpDevWnd*)m_pCurDevRootWnd;
	}

	if(pDevWnd == NULL)
	{
		return;
	}

	DrawLinkLines(pDevWnd, pDC, EPD_GetDevViewBackColor());
}

void CEpDevRootWndMngr::AdjustAllWnds(long nLeft,long nTop)
{
	if (m_pCurDevRootWnd == NULL)
	{
		return;
	}
	CSize sz;
	m_pCurDevRootWnd->CalSize(sz);
	
	m_pCurDevRootWnd->AdjustPos(nLeft,nTop);
}

