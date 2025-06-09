// SingleAppMutexApi.cpp: interface for the CSingleAppMutexApi class.
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SingleAppMutexApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HANDLE g_hSigleAppInstLock = NULL;

#ifdef _DEBUG
class CSingleAppMutexApiDestructor
{
public:
	CSingleAppMutexApiDestructor(){}
	virtual ~CSingleAppMutexApiDestructor()
	{
		ASSERT(g_hSigleAppInstLock == NULL);
	}
}g_SingleAppMutexApiDestructor;
#endif


BOOL CreateSingleAppMutex(const CString &pszMutexName, const CString &strWndTitle)
{
	g_hSigleAppInstLock = ::CreateMutex(NULL,true,pszMutexName);
	BOOL bTrue = TRUE;

	if ((g_hSigleAppInstLock == NULL) // 无法创建！
		|| (::GetLastError() == ERROR_ALREADY_EXISTS)) // 已经存在！
	{
		bTrue = false;

// 		CWnd *pWnd = CWnd::FindWindow(NULL, strWndTitle);
// 
// 		if (pWnd != NULL)
// 		{
// 			pWnd->SetActiveWindow();
// 			pWnd->BringWindowToTop();
// 			pWnd->ShowWindow(SW_SHOWMAXIMIZED);
// 		}
	}

	return bTrue;
}

BOOL ReleaseSingleAppMutex()
{
	if (g_hSigleAppInstLock != NULL)
	{
		::CloseHandle(g_hSigleAppInstLock);
	}	

	g_hSigleAppInstLock = NULL;

	return TRUE;
}

