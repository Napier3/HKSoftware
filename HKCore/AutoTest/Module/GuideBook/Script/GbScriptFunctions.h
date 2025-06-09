#pragma once

#include "../GuideBook.h"
#include "XScriptBase.h"
#include "GbScriptFunctions_lua.h"
#include "GbScriptFunctions_xvm.h"


BOOL Gb_InitScrpitEngine();
void Gb_CloseScrpitEngine();

long Gb_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE);
long Gb_CompileScript(CScriptText *pScript, CString &strSyntaxError);
long Gb_BuildScript_GuideBook(CGuideBook *pGuideBook);
void Gb_UnloadScript();
