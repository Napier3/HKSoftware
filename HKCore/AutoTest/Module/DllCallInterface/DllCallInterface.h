#pragma once

#include "../../../Module/System/DllLoadMngr.h"

typedef LONG (__cdecl *GB_DLLCALL_FUNC)(const char *pszParaData, char **ppszResult);

class CSafetyDllCallMngr : public CDllLoadMngr
{
private:
	CSafetyDllCallMngr();
	virtual ~CSafetyDllCallMngr();

	static long g_nSafetyDllCallMngrRef;
	static CSafetyDllCallMngr* g_pSafetyDllCallMngr;

public:
	static CSafetyDllCallMngr* Create();
	static void Release();

	static BOOL DllCall(CExBaseObject *pDllCall, CShortDatas *pResult, CExBaseList *pSysParas, CExBaseList *pGlobalDatas);

protected:
	HINSTANCE LoadLib(CExBaseObject *pDllCall);
	char* DllCall(HINSTANCE hLib, CExBaseObject *pDllCall, CExBaseList *pSysParas, CExBaseList *pGlobalDatas);
	void CalParaData(CExBaseObject *pDllCall, char *pszPara, CExBaseList *pSysParas, CExBaseList *pGlobalDatas);
};
