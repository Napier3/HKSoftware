#include "StdAfx.h"
#include "XScript_LUA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXScript_LUA::CXScript_LUA()
{

}

CXScript_LUA::~CXScript_LUA()
{

}


BOOL CXScript_LUA::InitScript()
{
	return Gb_InitLua();
}

BOOL CXScript_LUA::CloseScript()
{
	Gb_CloseLua();
	return TRUE;
}


long CXScript_LUA::RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
{
	return lua_RunScript(pScript, strSyntaxError, bInitFilter);
}

long CXScript_LUA::CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
	return lua_CompileScript(pScript, strSyntaxError);
}


BOOL CXScript_LUA::Gb_BuildScript(CExBaseObject *pGbObj)
{
	return TRUE;
}

BOOL CXScript_LUA::Gb_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer)
{
	return TRUE;
}


BOOL CXScript_LUA::Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen)
{
	return TRUE;
}

BOOL CXScript_LUA::Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer)
{
	return TRUE;
}


BOOL CXScript_LUA::Gb_BuildScript_GuideBook(CExBaseObject *pGuideBook)
{
	return TRUE;
}

BOOL CXScript_LUA::Gb_LoadScript(CExBaseObject *pGuideBook)
{
	return TRUE;
}

BOOL CXScript_LUA::Gb_UnloadScript()
{
	return TRUE;
}