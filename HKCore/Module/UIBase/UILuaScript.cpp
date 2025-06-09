#include "StdAfx.h"
#include "UILuaScript.h"
#include "UIScript_Functions.h"
#include "UILuaScript_GlobalDefine.h"

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"

namespace UILuaScript
{

	lua_State* g_pGuideBookLua = NULL;
	char g_pLuaReturnString[MAX_PATH];

	void UI_RegisterFunctions()
	{
		luabind::module( g_pGuideBookLua ) 
			[ 
				luabind::def("GetPageWidth", &UIS_GetPageWidth ),
				luabind::def("SetPageWidth", &UIS_SetPageWidth ), 
				luabind::def("GetPageHeight", &UIS_GetPageHeight),
				luabind::def("SetPageHeigh", &UIS_SetPageHeight),
				luabind::def("SetPagePosition", &UIS_SetPagePosition),
				luabind::def("SetPageSize", &UIS_SetPageSize),
				luabind::def("ShowPage", &UIS_ShowPage),
				luabind::def("ClosePage", &UIS_ClosePage),
				luabind::def("SetWndHeigh", &UIS_SetWndHeight),
				luabind::def("GetWndHeight", &UIS_GetWndHeight),
				luabind::def("SetWndWidth", &UIS_SetWndWidth),
				luabind::def("GetWndWidth", &UIS_GetWndWidth),
				luabind::def("SetWndLeft", &UIS_SetWndLeft),
				luabind::def("GetWndLeft", &UIS_GetWndLeft),
				luabind::def("SetWndTop", &UIS_SetWndTop),
				luabind::def("GetWndTop", &UIS_GetWndTop),
				luabind::def("SetWndRight", &UIS_SetWndRight),
				luabind::def("GetWndRight", &UIS_GetWndRight),
				luabind::def("SetWndBottom", &UIS_SetWndBottom ),
				luabind::def("GetWndBottom", &UIS_GetWndBottom),
				luabind::def("SetWndSize", &UIS_SetWndSize ),
				luabind::def("SetWndPosition", &UIS_SetWndPosition ), 
				luabind::def("GetWndText", &UIS_GetWndText),
				luabind::def("SetWndText", &UIS_SetWndText ), 
				luabind::def("ShowWnd", &UIS_ShowWnd),
				luabind::def("IsWndShow", &UIS_IsWndShow),
				luabind::def("EnableWnd", &UIS_EnableWnd),
				luabind::def("IsWndEnabl", &UIS_IsWndEnable),
				luabind::def("GetWndCurrSel", &UIS_GetWndCurrSel),
				luabind::def("SetWndCurrSel", &UIS_SetWndCurrSel),
				luabind::def("GetCheckState", &UIS_GetCheckState),
				luabind::def("SetCheckState", &UIS_SetCheckState),
				luabind::def("ChangeLanguage", &UIS_ChangeLanguage),
				luabind::def("ReDrawWnd", &UIS_ReDrawWnd),
				luabind::def("TraceSysInfor", &UIS_TraceSysInfor),
				luabind::def("GetLanguageStringByID", &UIS_GetLanguageStringByID),
				luabind::def("ExecWndCmd", &UIS_ExecWndCmd),
				luabind::def("ExecCmd", &UIS_ExecCmd),
				luabind::def("WndAttrEqL", &UIS_WndAttrEqL),
				luabind::def("WndAttrEqD", &UIS_WndAttrEqD),
				luabind::def("WndAttrEqS", &UIS_WndAttrEqS),
				luabind::def("SetWndAttrL", &UIS_SetWndAttrL),
				luabind::def("SetWndAttrD", &UIS_SetWndAttrD),
				luabind::def("SetWndAttrS", &UIS_SetWndAttrS),
				luabind::def("ShellExec", &UIS_ShellExec)
			]; 
	}

	BOOL UI_InitLua()
	{
		if( g_pGuideBookLua == NULL)  // 确保只会初始化一次 
		{ 
			g_pGuideBookLua = luaL_newstate(); // 创建Lua状态 

			if( g_pGuideBookLua == NULL) 
			{
				return false; 
			}

			luaL_openlibs( g_pGuideBookLua ); // 为该Lua状态打开所有Lua库 
			luabind::open( g_pGuideBookLua ); // 为该Lua状态打开luabind库 

			UI_RegisterFunctions();		//绑定全局脚本函数
		} 

		return TRUE;
	}

	void UI_CloseLua()
	{
		if (g_pGuideBookLua != NULL)
		{
			lua_settop(g_pGuideBookLua,0);
			lua_close(g_pGuideBookLua);
		}
	}


	long UI_RunScript(CUIEvent *pScript, CString &strSyntaxError)
	{
		ASSERT (_CUILuaScriptGlobalDefine::g_pUILuaScriptGlobalDefine != NULL);
		//ASSERT (pScript != NULL && g_pGuideBookLua != NULL);
		long nErr = 0;

		CAutoSimpleLock oLock(&(_CUILuaScriptGlobalDefine::g_pUILuaScriptGlobalDefine->m_oAutoCriticSection));

		if (pScript == NULL || g_pGuideBookLua == NULL)
		{
			return 0;
		}

		if (pScript->m_strScript.GetLength() == 0)
		{
			return 0;
		}

		_CUILuaScriptGlobalDefine::g_pUILuaScriptGlobalDefine->SetScriptText( pScript );
		long nLen = 0;
		char *pszScript = NULL;

// 		if (pScript->m_nIsRef)
// 		{
// 			CUIEvent *pRef = pScript->GetRefScriptText();
// 
// 			if(pRef != NULL)
// 			{
// 				nLen = pRef->m_strScript.GetLength();
// 				CString_to_char(pRef->m_strScript, &pszScript);
// 			}
// 			else
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("引用脚本【%s】不存在，请检查脚本库文件是否为最新版本"), pScript->m_strID);
// 				nLen = 0;//pScript->m_strScript.GetLength();
// 				//CString_to_char(pScript->m_strScript, &pszScript);
// 				nErr = 1;
// 			}
// 		}
//		else
		{
			nLen = pScript->m_strScript.GetLength();
			CString_to_char(pScript->m_strScript, &pszScript);
		}

		if (nErr > 0)
		{
			if (pszScript != NULL)
			{
				delete pszScript;
			}

			return nErr;
		}

		ASSERT (pszScript != NULL);
		nErr = luaL_loadstring(g_pGuideBookLua, pszScript);

		if (nErr)
		{
			strSyntaxError = lua_tostring(g_pGuideBookLua, -1);
			lua_pop(g_pGuideBookLua, -1);
			CLogPrint::LogString(XLOGLEVEL_ERROR, strSyntaxError);
		}
		else
		{
			nErr = lua_pcall(g_pGuideBookLua, 0, LUA_MULTRET, 0);

			if (nErr)
			{
				strSyntaxError = lua_tostring(g_pGuideBookLua, -1);
				lua_pop(g_pGuideBookLua, -1);
				CLogPrint::LogString(XLOGLEVEL_ERROR, strSyntaxError);
			}
		}

		// 	UI_GetLuaGolbalVariables();
		delete pszScript;
		lua_settop(g_pGuideBookLua, 0);

		return nErr;
	}

	long UI_CompileScript(CUIEvent *pScript, CString &strSyntaxError)
	{
		return UI_RunScript(pScript, strSyntaxError);
	}

}