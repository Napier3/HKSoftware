#include "stdafx.h"
#include "CXCtrl_QT_CWinApp.h"
#include "../../API/StringApi.h"

CWinApp g_theApp;
extern CWinApp* g_ptheApp = &g_theApp;

CWinApp* AfxGetApp()
{
    return g_ptheApp;
}

#ifdef _PSX_QT_LINUX_
void SetCursor(long nCursor)
{
}

void ClipCursor(CRect *pRect)
{

}

void ReleaseCapture()
{

}
#endif
