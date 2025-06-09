#pragma once

#include "../GuideBookDefine.h"
#include "../../../../Module/API/StringApi.h"
#include "../ScriptText.h"

#include "XScriptBase.h"

class CSmartTestXvm;
extern CSmartTestXvm g_theSmartTestXvm;

extern char g_pLuaReturnString[MAX_PATH];

BOOL xvm_InitScrpitEngine();
BOOL xvm_InitScrpitEngine(CSmartTestXvm *pXvm, CExBaseObject *pRefObject);

void xvm_CloseScrpitEngine();
void xvm_CloseScrpitEngine(CSmartTestXvm *pXvm);
CSmartTestXvm* xvm_GetSmartTestXvm(CExBaseObject *p=NULL);

long xvm_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE);
long xvm_CompileScript(CScriptText *pScript, CString &strSyntaxError);
BOOL xvm_BuildScript(CExBaseObject *pGbObj);
BOOL xvm_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer);

BOOL xvm_BuildScript(CSmartTestXvm *pXvm, const char *pszScript, long nBufferLen);
BOOL xvm_BuildScript(CSmartTestXvm *pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer);

BOOL xvm_BuildScript_GuideBook(CExBaseObject *pGuideBook);



//2020-6-2  lijunqing  
class CGbXvmScriptBuilder : public CXvmScriptBuilder
{
public:
	CGbXvmScriptBuilder();
	virtual ~CGbXvmScriptBuilder();

protected:
	virtual BOOL IsScript(CExBaseObject *p)	{		return Gb_IsScript(p);		}
	virtual void SerializeScript(CExBaseObject *p, long &nScriptIndex);
	virtual void SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex);

	virtual void SerializeScript(CExBaseList *pList, long &nScriptIndex);
	virtual void SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex);

	BOOL IsScriptParent(CExBaseList *pList);
};

extern 	CGbXvmScriptBuilder g_oGbXvmScriptBuilder;
