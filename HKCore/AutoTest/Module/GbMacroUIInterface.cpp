// EpotoInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GbMacroUIInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbMacroUI::CGbMacroUI()
{
	m_pGbUICreate = NULL;
	m_pGbUIFree = NULL;
	m_pGbUIShowParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIShow = NULL;
	m_pGbUIHide = NULL;
	m_pGbUIResultEx = NULL;
	m_pGbUIFaultParaEx = NULL;

	m_pWndGbMacroUI = NULL;
	m_pGuideBook = NULL;
}

CGbMacroUI::~CGbMacroUI()
{

}

void CGbMacroUI::GbUICreate (CExBaseList *pCpus, CExBaseList *pSysParas, CWnd *pParent, HINSTANCE hInstance)
{
	if (m_pWndGbMacroUI != NULL)
	{
		return;
	}

	if (m_pGbUICreate == NULL)
	{
		return;
	}

	m_pWndGbMacroUI = m_pGbUICreate(pCpus, pSysParas, pParent, hInstance);
}

void CGbMacroUI::GbUIFree ()
{
	if (m_pGbUIFree != NULL)
	{
		m_pGbUIFree(m_pWndGbMacroUI);
	}
}

void CGbMacroUI::GbUIShowParas(const CString &strParas)
{
	if (m_pGbUIShowParas != NULL)
	{
		m_pGbUIShowParas(m_pWndGbMacroUI, strParas);
	}
}

void CGbMacroUI::GbUIGetParas(CString &strParas)
{
	if (m_pGbUIGetParas != NULL)
	{
		m_pGbUIGetParas(m_pWndGbMacroUI, strParas);
	}
}

void CGbMacroUI::GbUIShow (CWnd *pParent)
{
	if (m_pGbUIShow != NULL)
	{
		m_pGbUIShow(m_pWndGbMacroUI, pParent);
	}
}


void CGbMacroUI::GbUIHide ()
{
	if (m_pGbUIHide != NULL)
	{
		m_pGbUIHide(m_pWndGbMacroUI);
	}
}

void CGbMacroUI::GbUIResultEx(CString &strResultsEx)
{
	if (m_pGbUIResultEx != NULL)
	{
		m_pGbUIResultEx(m_pWndGbMacroUI, strResultsEx);
	}
}

void CGbMacroUI::GbUIFaultParaEx(CString &strFaultParaEx)
{
	if (m_pGbUIFaultParaEx != NULL)
	{
		m_pGbUIFaultParaEx(m_pWndGbMacroUI, strFaultParaEx);
	}
}


//////////////////////////////////////////////////////////////////////////
//
CGbMacroUILib::CGbMacroUILib()
{
	m_hMacroUILib = NULL;
	m_pGbUICreate = NULL;
	m_pGbUIFree = NULL;
	m_pGbUIShowParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIShow = NULL;
	m_pGbUIHide = NULL;
	m_pGbUIResultEx = NULL;
	m_pGbUIFaultParaEx = NULL;
}

CGbMacroUILib::~CGbMacroUILib()
{
	ReleaseLib();
}

BOOL CGbMacroUILib::LoadLib(const CString &strDllFile)
{
	ReleaseLib();

	CString strDll;
	strDll = _P_GetBinPath();
	strDll += strDllFile;
	
	BOOL bSucc = TRUE;
	m_hMacroUILib = ::LoadLibrary(strDll);

	if(m_hMacroUILib != NULL)
	{
		m_pGbUICreate =     (EP_GbUICreate)GetProcAddress(m_hMacroUILib, "GbUICreate");
		m_pGbUIFree =       (EP_GbUIFree)GetProcAddress(m_hMacroUILib, "GbUIFree");
		m_pGbUIShowParas =  (EP_GbUIShowParas)GetProcAddress(m_hMacroUILib, "GbUIShowParas");
		m_pGbUIGetParas =   (EP_GbUIGetParas)GetProcAddress(m_hMacroUILib, "GbUIGetParas");
		m_pGbUIShow =       (EP_GbUIShow)GetProcAddress(m_hMacroUILib, "GbUIShow");
		m_pGbUIHide =       (EP_GbUIHide)GetProcAddress(m_hMacroUILib, "GbUIHide");
		m_pGbUIResultEx =   (EP_GbUIResultEx)GetProcAddress(m_hMacroUILib, "GbUIResultEx");
		m_pGbUIFaultParaEx =(EP_GbUIResultEx)GetProcAddress(m_hMacroUILib, "GbUIFaultParaEx");

		if (m_pGbUICreate == NULL)
		{
			AfxMessageBox(_T("函数GbUICreate入口地址没有找到"));
		}
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("LoadLibrary(%s)失败"), strDll);
		AfxMessageBox(strMsg);
		bSucc = FALSE;
	}	

	return bSucc;
	
}

void CGbMacroUILib::ReleaseLib()
{
	if (m_hMacroUILib != NULL)
	{
		FreeLibrary(m_hMacroUILib);
		m_hMacroUILib = NULL;
	}

	m_pGbUICreate = NULL;
	m_pGbUIFree = NULL;
	m_pGbUIShowParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIGetParas = NULL;
	m_pGbUIShow = NULL;
	m_pGbUIHide = NULL;
	m_pGbUIResultEx = NULL;
	m_pGbUIFaultParaEx = NULL;
}


BOOL CGbMacroUILib::HasLoadLib()
{
	return (m_hMacroUILib != NULL);
}

CGbMacroUI* CGbMacroUILib::FindByGuideBook(CExBaseObject *pGuideBook)
{
	CGbMacroUI *p = NULL;
	CGbMacroUI *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbMacroUI *)GetNext(pos);

		if (p->m_pGuideBook == pGuideBook)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CGbMacroUI* CGbMacroUILib::CreateGbMacroUI(CExBaseObject *pGuideBook)
{
	CGbMacroUI *pNew = FindByGuideBook(pGuideBook);
	
	if (pNew != NULL)
	{
		return pNew;
	}
	
	pNew = new CGbMacroUI();

	pNew->m_pGbUICreate = m_pGbUICreate;
	pNew->m_pGbUIFree = m_pGbUIFree;
	pNew->m_pGbUIShowParas = m_pGbUIShowParas;
	pNew->m_pGbUIGetParas = m_pGbUIGetParas;
	pNew->m_pGbUIGetParas = m_pGbUIGetParas;
	pNew->m_pGbUIShow = m_pGbUIShow;
	pNew->m_pGbUIHide = m_pGbUIHide;
	pNew->m_pGbUIResultEx = m_pGbUIResultEx;
	pNew->m_pGbUIFaultParaEx = m_pGbUIFaultParaEx;
	pNew->m_pGuideBook = pGuideBook;

	AddNewChild(pNew);

	return pNew;
}

void CGbMacroUILib::FreeGbMacroUI(CGbMacroUI *pMacroUI)
{
	pMacroUI->GbUIFree();
	Delete(pMacroUI);
}


//////////////////////////////////////////////////////////////////////////
//
long CGbMacroUILibMngr::g_nGbMacroUILibMngrRef = 0;
CGbMacroUILibMngr* CGbMacroUILibMngr::g_pGbMacroUILibMngr = NULL;

CGbMacroUILibMngr* CGbMacroUILibMngr::Create()
{
	g_nGbMacroUILibMngrRef++;

	if (g_nGbMacroUILibMngrRef == 1)
	{
		g_pGbMacroUILibMngr = new CGbMacroUILibMngr();
	}

	return g_pGbMacroUILibMngr;
}

void CGbMacroUILibMngr::Release()
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

CGbMacroUI* CGbMacroUILibMngr::CreateGbMacroUI(const CString &strDllFile, CExBaseObject *pGuideBook)
{
	if (g_pGbMacroUILibMngr == NULL)
	{
		return NULL;
	}

	CGbMacroUI *pNew = g_pGbMacroUILibMngr->In_CreateGbMacroUI(strDllFile, pGuideBook);
	pNew->m_strDLL = strDllFile;

	return pNew;
}

void CGbMacroUILibMngr::FreeGbMacroUI(CGbMacroUI *pMacroUI)
{
	if (g_pGbMacroUILibMngr == NULL)
	{
		return;
	}

	return g_pGbMacroUILibMngr->FreeGbMacroUI(pMacroUI);
}


CGbMacroUILibMngr::CGbMacroUILibMngr()
{

}

CGbMacroUILibMngr::~CGbMacroUILibMngr()
{

}


CGbMacroUI* CGbMacroUILibMngr::In_CreateGbMacroUI(const CString &strDllFile, CExBaseObject *pGuideBook)
{
	CGbMacroUILib *pFind = (CGbMacroUILib*)FindByID(strDllFile);

	if (pFind == NULL)
	{
		pFind = new CGbMacroUILib();
		pFind->m_strID = strDllFile;
		pFind->m_strName = strDllFile;
		pFind->LoadLib(strDllFile);
		AddNewChild(pFind);
	}

	return pFind->CreateGbMacroUI(pGuideBook);
}

void CGbMacroUILibMngr::In_FreeGbMacroUI(CGbMacroUI *pMacroUI)
{
	CGbMacroUILib *pLib = (CGbMacroUILib*)pMacroUI->GetParent();
	pLib->FreeGbMacroUI(pMacroUI);
}

