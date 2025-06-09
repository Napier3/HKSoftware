#pragma once

#include "UIBaseGlobal.h"
#include "UIWndPage.h"

#include "..\CriticalSection\SynCriticalSection.h"

class _CUILuaScriptGlobalDefine
{
public:
	_CUILuaScriptGlobalDefine()
	{
		m_pEvent = NULL;
	}

	virtual ~_CUILuaScriptGlobalDefine()
	{
		
	}

	static long g_nUILuaScriptGlobalDefineRef;
	static _CUILuaScriptGlobalDefine *g_pUILuaScriptGlobalDefine;

	static _CUILuaScriptGlobalDefine* Create()
	{
		g_nUILuaScriptGlobalDefineRef++;

		if (g_nUILuaScriptGlobalDefineRef == 1)
		{
			g_pUILuaScriptGlobalDefine = new _CUILuaScriptGlobalDefine();
		}

		return g_pUILuaScriptGlobalDefine;
	}

	static void Release()
	{
		g_nUILuaScriptGlobalDefineRef--;

		if (g_nUILuaScriptGlobalDefineRef == 0)
		{
			delete g_pUILuaScriptGlobalDefine;
			g_pUILuaScriptGlobalDefine = NULL;
		}
	}

	static CUIWindowBase* UIS_GetUIWindow(const char *pszWindowID);
	static CUIWndLayer* UIS_GetUILayer(const char *pszLayerID);


public:
	CAutoCriticSection m_oAutoCriticSection;	//脚本执行的互斥量

	CUIEvent *m_pEvent;					//当前执行的脚本
	void SetScriptText(CUIEvent *pScript);
	long SelectUIWnds(const char* pszPath, CExBaseList &oListDest);
	CExBaseObject* SelectUIWnd();

	CUIWindowBase* GetUIWindow(const char *pszWindowID);
	CUIWndLayer* GetUILayer(const char *pszLayerID);

public:
	CExBaseObject *m_pCurrSelectUIWnd;   //当前选中的项目
	CExBaseObject* SelectUIWnd(const char* pszPath);

	CExBaseList m_oListRptExFilter;

private:
	CUIWndPage *m_pParentPage;
};
