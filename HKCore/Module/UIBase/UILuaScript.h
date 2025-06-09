#pragma once

#include "..\API\StringApi.h"
#include "UIEvent.h"

namespace UILuaScript
{
	extern char g_pLuaReturnString[MAX_PATH];
	
	BOOL UI_InitLua();
	void UI_CloseLua();
	long UI_RunScript(CUIEvent *pScript, CString &strSyntaxError);
	long UI_CompileScript(CUIEvent *pScript, CString &strSyntaxError);

}

