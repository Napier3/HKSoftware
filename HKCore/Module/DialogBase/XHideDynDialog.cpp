#include "stdafx.h"  
#include "XHideDynDialog.h"  

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

/////////////////////////////////////////////////////////////////////////////  
// CHideDynDialog dialog  
long CXHideDynDialog::g_nHideDynDialogRef = 0;
CXHideDynDialog* CXHideDynDialog::g_pHideDynDialog = NULL;

CXHideDynDialog* CXHideDynDialog::CreateHideDynDialog()
{
	g_nHideDynDialogRef++;

	if (g_nHideDynDialogRef == 1)
	{
		g_pHideDynDialog = new CXHideDynDialog();
		g_pHideDynDialog->SetUseModeless(TRUE);
		g_pHideDynDialog->DoModal();
		g_pHideDynDialog->ShowWindow(SW_HIDE);
		g_pHideDynDialog->SetWindowText(_T("Hide Window"));
	}

	return g_pHideDynDialog;
}

CXHideDynDialog* CXHideDynDialog::GetHideDynDialog()
{
	ASSERT (g_pHideDynDialog);
	return g_pHideDynDialog;
}

void CXHideDynDialog::Release()
{
	g_nHideDynDialogRef--;

	if (g_nHideDynDialogRef == 0)
	{
		g_pHideDynDialog->DestroyWindow();
		delete g_pHideDynDialog;
	}
}

CXHideDynDialog::CXHideDynDialog(CWnd* pParent /*=NULL*/) 
: CDynDialogEx(pParent, FALSE) 
{ 

} 

CXHideDynDialog::~CXHideDynDialog() 
{ 

} 

void CXHideDynDialog::OnCancel()
{
	
}


void CXHideDynDialog::OnOK()
{
	
}

