// GridCtrlClient.h : main header file for the GRIDCTRLCLIENT application
//

#if !defined(AFX_GRIDCTRLCLIENT_H__885DA12A_DCC2_497C_9652_C4D9D6E3B682__INCLUDED_)
#define AFX_GRIDCTRLCLIENT_H__885DA12A_DCC2_497C_9652_C4D9D6E3B682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlClientApp:
// See GridCtrlClient.cpp for the implementation of this class
//

class CGridCtrlClientApp : public CWinApp
{
public:
	CGridCtrlClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGridCtrlClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLCLIENT_H__885DA12A_DCC2_497C_9652_C4D9D6E3B682__INCLUDED_)
