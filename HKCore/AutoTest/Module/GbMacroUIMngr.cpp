// EpotoInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GbMacroUIMngr.h"

CWndGbMacroUI::CWndGbMacroUI()
{
	m_pWndGbMacroUI = NULL;
}

CWndGbMacroUI::~CWndGbMacroUI()
{
	if (m_pWndGbMacroUI != NULL)
	{
		m_pWndGbMacroUI->DestroyWindow();
		delete m_pWndGbMacroUI;
	}
}

//////////////////////////////////////////////////////////////////////////
//
long CWndGbMacroUIList::g_nGbMacroUILibMngrRef = 0;
CWndGbMacroUIList* CWndGbMacroUIList::g_pGbMacroUILibMngr = NULL;

CWndGbMacroUIList* CWndGbMacroUIList::Create()
{
	g_nGbMacroUILibMngrRef++;

	if (g_nGbMacroUILibMngrRef == 1)
	{
		g_pGbMacroUILibMngr = new CWndGbMacroUIList();
	}

	return g_pGbMacroUILibMngr;
}

void CWndGbMacroUIList::Release()
{
	if (g_nGbMacroUILibMngrRef == 0)
	{
		return;
	}

	g_nGbMacroUILibMngrRef--;

	if (g_nGbMacroUILibMngrRef == 0)
	{
		delete g_pGbMacroUILibMngr;
		g_pGbMacroUILibMngr = NULL;
	}
}

CWndGbMacroUI* CWndGbMacroUIList::CreateGbMacroUI(CWnd *pWnd)
{
	if (g_pGbMacroUILibMngr == NULL)
	{
		return NULL;
	}

	return g_pGbMacroUILibMngr->In_CreateGbMacroUI(pWnd);
}

void CWndGbMacroUIList::FreeGbMacroUI(CWnd *pMacroUI)
{
	if (g_pGbMacroUILibMngr == NULL)
	{
		return;
	}

	return g_pGbMacroUILibMngr->In_FreeGbMacroUI(pMacroUI);
}

CWndGbMacroUI* CWndGbMacroUIList::FindUIWnd(CWnd *pWnd)
{
	if (g_pGbMacroUILibMngr == NULL)
	{
		return NULL;
	}

	return g_pGbMacroUILibMngr->In_FindUIWnd(pWnd);
}

CWndGbMacroUIList::CWndGbMacroUIList()
{

}

CWndGbMacroUIList::~CWndGbMacroUIList()
{

}


CWndGbMacroUI* CWndGbMacroUIList::In_CreateGbMacroUI(CWnd *pWnd)
{
	CWndGbMacroUI *pNew = new CWndGbMacroUI();
	pNew->m_pWndGbMacroUI = pWnd;
	AddNewChild(pNew);

	return pNew;
}

void CWndGbMacroUIList::In_FreeGbMacroUI(CWnd *pMacroUI)
{
	CWndGbMacroUI *pGbUIWnd = In_FindUIWnd(pMacroUI);

	Delete(pGbUIWnd);
}

CWndGbMacroUI* CWndGbMacroUIList::In_FindUIWnd(CWnd *pWnd)
{
	CWndGbMacroUI *p = NULL;
	CWndGbMacroUI *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CWndGbMacroUI *)GetNext(pos);

		if (p->m_pWndGbMacroUI == pWnd)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

