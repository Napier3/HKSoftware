//XScriptBase.h

#ifndef _XScriptBase_h__
#define _XScriptBase_h__

#include "../GuideBook.h"

class CXScriptBase
{
public:
	virtual BOOL InitScript() = 0;
	virtual BOOL CloseScript() = 0;

	virtual long RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter=FALSE) = 0;
	virtual long CompileScript(CScriptText *pScript, CString &strSyntaxError) = 0;

	virtual BOOL Gb_BuildScript(CExBaseObject *pGbObj) = 0;
	virtual BOOL Gb_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer) = 0;

	virtual BOOL Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen) = 0;
	virtual BOOL Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer) = 0;

	virtual BOOL Gb_BuildScript_GuideBook(CExBaseObject *pGuideBook) = 0;
	virtual BOOL Gb_LoadScript(CExBaseObject *pGuideBook) = 0;
	virtual BOOL Gb_UnloadScript() = 0;
	
};

#endif