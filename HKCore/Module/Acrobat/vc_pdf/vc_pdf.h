// vc_pdf.h : main header file for the VC_PDF application
//

#if !defined(AFX_VC_PDF_H__679F0654_E9E1_41C7_9653_8956548A54ED__INCLUDED_)
#define AFX_VC_PDF_H__679F0654_E9E1_41C7_9653_8956548A54ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVc_pdfApp:
// See vc_pdf.cpp for the implementation of this class
//

class CVc_pdfApp : public CWinApp
{
public:
	CVc_pdfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVc_pdfApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVc_pdfApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC_PDF_H__679F0654_E9E1_41C7_9653_8956548A54ED__INCLUDED_)
