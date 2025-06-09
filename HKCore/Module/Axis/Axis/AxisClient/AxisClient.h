// AxisClient.h : main header file for the AXISCLIENT application
//

#if !defined(AFX_AXISCLIENT_H__F2526F4E_EC72_4E09_B228_BADF239531F1__INCLUDED_)
#define AFX_AXISCLIENT_H__F2526F4E_EC72_4E09_B228_BADF239531F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAxisClientApp:
// See AxisClient.cpp for the implementation of this class
//

class CAxisClientApp : public CWinApp
{
public:
	CAxisClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxisClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAxisClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISCLIENT_H__F2526F4E_EC72_4E09_B228_BADF239531F1__INCLUDED_)
