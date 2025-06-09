//XScript_XVM.h

#ifndef _CXScript_XVM_h__
#define _CXScript_XVM_h__

#include "XScriptBase.h"
#include "SmartTestXvm.h"
#include "GbScriptFunctions_xvm.h"

void GBS_FilterInit(LPVOID);

class CXScript_XVM : public CXScriptBase
{
public:
	CXScript_XVM();
	virtual ~CXScript_XVM();

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

protected:
	//CSmartTestXvm m_oSmartTestXvm;
	BOOL m_bHasLoadScript;

	BOOL InitScript(CSmartTestXvm *pXvm, CExBaseObject *pRefObject);
};

#endif

