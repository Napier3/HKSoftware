
#if !defined(SINGLEAPPMUTEXAPI_H__)
#define SINGLEAPPMUTEXAPI_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

BOOL CreateSingleAppMutex(const CString &pszMutexName, const CString &strWndTitle=_T(""));
BOOL ReleaseSingleAppMutex();

#endif // !defined(SINGLEAPPMUTEXAPI_H__)
