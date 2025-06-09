// KeyHookBaseDialog.cpp: implementation of the CKeyHookBaseDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TttTestCtrl.h"
#include "KeyHookBaseDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CKeyHookBaseDialog *g_pKeyHookBaseDialog = NULL;

LRESULT __stdcall  CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{	
	if(((DWORD)lParam&0x40000000) && (HC_ACTION==nCode))
	{
		if (g_pKeyHookBaseDialog != NULL)
		{
			g_pKeyHookBaseDialog->OnKeyHook(wParam);
		}
	} 
	
	LRESULT RetVal = CallNextHookEx( hkb, nCode, wParam, lParam );	
	return  RetVal;
}

BOOL __stdcall InstallKeyHook()
{
	hkb=SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)KeyboardProc,g_hCurrDllInstance,0);
	return TRUE;
}
BOOL UnHook()
{
	BOOL unhooked = UnhookWindowsHookEx(hkb);
	return unhooked;
} 


CKeyHookBaseDialog::CKeyHookBaseDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd)
{

}

CKeyHookBaseDialog::~CKeyHookBaseDialog()
{

}

void CKeyHookBaseDialog::ShowDialog()
{
	InstallKeyHook();

	ShowWindow(SW_SHOW);
	g_pKeyHookBaseDialog = this;		
}

void CKeyHookBaseDialog::HideDialog()
{
	UnHook();
	ShowWindow(SW_HIDE);
	g_pKeyHookBaseDialog = NULL;		
}

