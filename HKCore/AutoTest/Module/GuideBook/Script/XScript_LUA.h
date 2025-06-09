//XScript_LUA.h

#ifndef _CXScript_LUA_h__
#define _CXScript_LUA_h__

#include "XScriptBase.h"
#include "GbScriptFunctions_lua.h"

class CXScript_LUA : public CXScriptBase
{
public:
	CXScript_LUA();
	virtual ~CXScript_LUA();

public:
	virtual BOOL InitScript();
	virtual BOOL CloseScript();

	virtual long RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE);
	virtual long CompileScript(CScriptText *pScript, CString &strSyntaxError);

	virtual BOOL Gb_BuildScript(CExBaseObject *pGbObj);
	virtual BOOL Gb_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer);

	virtual BOOL Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen);
	virtual BOOL Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer);

	virtual BOOL Gb_BuildScript_GuideBook(CExBaseObject *pGuideBook);
	virtual BOOL Gb_LoadScript(CExBaseObject *pGuideBook);
	virtual BOOL Gb_UnloadScript();
	
};

#endif

