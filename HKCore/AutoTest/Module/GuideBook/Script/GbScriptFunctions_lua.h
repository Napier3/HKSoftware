#pragma once

#include "../GuideBookDefine.h"
#include "../../../../Module/API/StringApi.h"
#include "../ScriptText.h"

void GBS_FilterInit(LPVOID);

extern char g_pLuaReturnString[MAX_PATH];

BOOL Gb_InitLua();
void Gb_CloseLua();
long lua_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE);
long lua_CompileScript(CScriptText *pScript, CString &strSyntaxError);
