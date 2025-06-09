#include "StdAfx.h"
#include "UILuaScript_GlobalDefine.h"

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"

extern lua_State* g_pGuideBookLua;

//////////////////////////////////////////////////////////////////////////
//_CUILuaScriptGlobalDefine


long _CUILuaScriptGlobalDefine::g_nUILuaScriptGlobalDefineRef = 0;
_CUILuaScriptGlobalDefine* _CUILuaScriptGlobalDefine::g_pUILuaScriptGlobalDefine = NULL;

CUIWindowBase* _CUILuaScriptGlobalDefine::UIS_GetUIWindow(const char *pszWindowID)
{
	ASSERT (g_pUILuaScriptGlobalDefine != NULL);
	return g_pUILuaScriptGlobalDefine->GetUIWindow(pszWindowID);
}

CUIWndLayer* _CUILuaScriptGlobalDefine::UIS_GetUILayer(const char *pszLayerID)
{
	ASSERT (g_pUILuaScriptGlobalDefine != NULL);
	return g_pUILuaScriptGlobalDefine->GetUILayer(pszLayerID);
}


void _CUILuaScriptGlobalDefine::SetScriptText(CUIEvent *pScript)
{
	m_pEvent = pScript;
	m_pParentPage = (CUIWndPage*)m_pEvent->GetAncestor(UICLASSID_CUIWNDPAGE);
}

long _CUILuaScriptGlobalDefine::SelectUIWnds(const char* pszPath, CExBaseList &oListDest)
{
	oListDest.RemoveAll();
	CUIWindowBase *pWndBase = (CUIWindowBase*)m_pEvent->GetParent();

	ASSERT ( pWndBase != NULL );

	if (pWndBase == NULL)
	{
		return -1;
	}

	//路径
	CString strPath(pszPath);
	pWndBase->Select(strPath, oListDest);

	return oListDest.GetCount();
}

CExBaseObject* _CUILuaScriptGlobalDefine::SelectUIWnd()
{
	CUIWindowBase *pWndBase = (CUIWindowBase*)m_pEvent->GetParentWnd();
	return pWndBase;
}


CExBaseObject* _CUILuaScriptGlobalDefine::SelectUIWnd(const char* pszPath)
{
	m_pCurrSelectUIWnd = NULL;

	CUIWindowBase *pWndBase = (CUIWindowBase*)m_pEvent->GetParent();
	ASSERT ( pWndBase != NULL );

	if (pWndBase == NULL)
	{
		return NULL;
	}

	CExBaseList oListDest;
	CString strPath(pszPath);
	pWndBase->Select(strPath, oListDest);
	long nCount = oListDest.GetCount();

	if (nCount == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"路径[%s]没有选择的项目", CString(pszPath));
	}
	else if (nCount > 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"路径[%s]选择的项目不唯一", CString(pszPath));
	}
	else
	{
		m_pCurrSelectUIWnd = oListDest.GetHead();
	}

	oListDest.RemoveAll();
	return m_pCurrSelectUIWnd;
}

CUIWindowBase* _CUILuaScriptGlobalDefine::GetUIWindow(const char *pszWindowID)
{
	ASSERT (m_pParentPage != NULL);

	if (m_pParentPage == NULL)
	{
		return NULL;
	}
	else
	{
		CString strWndID;
		strWndID = pszWindowID;
		CUIWindowBase *pWndFind = NULL;
		CUIWndLayer *pLayer = (CUIWndLayer*)m_pEvent->GetAncestor(UICLASSID_CUIWNDLAYER);

		if (pLayer != NULL)
		{
			pWndFind = pLayer->FindWindowByID(strWndID);
		}

		if (pWndFind == NULL)
		{
			pWndFind = m_pParentPage->FindWindowByID(strWndID);
		}

		return pWndFind;
	}

}

CUIWndLayer* _CUILuaScriptGlobalDefine::GetUILayer(const char *pszLayerID)
{
	ASSERT (m_pParentPage != NULL);

	if (m_pParentPage == NULL)
	{
		return NULL;
	}
	else
	{
		CString strLayerID;
		strLayerID = pszLayerID;
		return m_pParentPage->FindLayerByID(strLayerID);
	}
}

//////////////////////////////////////////////////////////////////////////
//_CUILuaScriptGlobalDefineCreator

class _CUILuaScriptGlobalDefineCreator
{
public:
	_CUILuaScriptGlobalDefine *m_pUILuaScriptGlobalDefine;

	_CUILuaScriptGlobalDefineCreator()
	{
		m_pUILuaScriptGlobalDefine = _CUILuaScriptGlobalDefine::Create();
	}

	virtual ~_CUILuaScriptGlobalDefineCreator()
	{
		m_pUILuaScriptGlobalDefine->Release();
		m_pUILuaScriptGlobalDefine = NULL;
	}
};

_CUILuaScriptGlobalDefineCreator g_oUILuaScriptGlobalDefineCreator;

