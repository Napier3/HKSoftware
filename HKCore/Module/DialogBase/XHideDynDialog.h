#if !defined(_HideDynDialog_h__) 
#define _HideDynDialog_h__ 

#include "DynDialogEx.h"

#if _MSC_VER > 1000 
#pragma once 
#endif

// HideDynDialog.h : header file 
// 

class CXHideDynDialog : public CDynDialogEx 
{ 
// Construction 
public: 
	static CXHideDynDialog* CreateHideDynDialog();
	static CXHideDynDialog* GetHideDynDialog();
	static void Release();

protected:
	CXHideDynDialog(CWnd* pParent = NULL);   // standard constructor 
	virtual ~CXHideDynDialog(); 

	static long g_nHideDynDialogRef;
	static CXHideDynDialog *g_pHideDynDialog;

protected: 
	virtual void OnCancel(); 
	virtual void OnOK(); 
}; 

#endif // !defined(_HideDynDialog_h__)