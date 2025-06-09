#pragma once

#include "GuideBookDefine.h"
#include "../../../Module/API/StringApi.h"
#include "ScriptText.h"


extern char g_pLuaReturnString[MAX_PATH];

BOOL Gb_InitLua();
void Gb_CloseLua();
long Gb_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE);
long Gb_CompileScript(CScriptText *pScript, CString &strSyntaxError);

