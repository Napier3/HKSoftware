#include "StdAfx.h"
#include "XDialogBase.h"

BOOL CALLBACK DialogProc (HWND, UINT, WPARAM, LPARAM) ;


CXDialogBase::CXDialogBase(HWND hwndOwner)
{
	m_hInst = AfxGetApp()->m_hInstance;

	if (hwndOwner == NULL)
	{
		hwndOwner = AfxGetMainWnd()->m_hWnd;

		if (hwndOwner == NULL)
		{
			hwndOwner =::GetDesktopWindow();
		}
	}

	m_hOwnerWnd = hwndOwner;
}

CXDialogBase::~CXDialogBase(void)
{
}

BOOL CALLBACK CXDialogBase::XDialogProc(HWND hDlg,
								  UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG :
		//OnInitionDialog();
		return TRUE ;

	case WM_COMMAND :
		switch (LOWORD (wParam))
		{
// 		case ID_EDIT :
// 			//GetDlgItemText (hDlg, ID_EDIT, nEditTwo, 127);
// 			return TRUE;
// 		case ID_HELP :
// 			
// 			return TRUE;
		case IDOK :
			EndDialog (hDlg, 0) ;
			return TRUE ;
		}
		break ;
	case WM_CLOSE:
		EndDialog (hDlg, 0) ;
		return TRUE ;
	default:
		break;
	}

	return FALSE ;
}

INT_PTR CXDialogBase::DoModal(long x, long y, long cx, long cy, DWORD dwStyle)
{
	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPDLGITEMTEMPLATE lpdit;
	LPWORD lpw;
	LPWSTR lpwsz;
	LRESULT ret;
	int nchar;

	hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if (!hgbl)
		return -1;

	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

	// Define a dialog box.

	lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU
		| DS_MODALFRAME | WS_CAPTION;
	lpdt->cdit = 0;  // number of controls
	lpdt->x  = 10;
	lpdt->y  = 10;
	lpdt->cx = 100;
	lpdt->cy = 70;

	lpw = (LPWORD) (lpdt + 1);
	*lpw++ = 0;   // no menu
	*lpw++ = 0;   // predefined dialog box class (by default)

// 	lpwsz = (LPWSTR) lpw;
// 	nchar = 1+ MultiByteToWideChar (CP_ACP, 0, "内存对话框", -1,
// 		lpwsz, 50);
// 	lpw   += nchar;
// 
// 	//-----------------------
// 	// Define an OK button.
// 	//-----------------------
// 	lpw = lpwAlign (lpw);
// 
// 	lpdit = (LPDLGITEMTEMPLATE) lpw;
// 	lpdit->x  = 10;
// 	lpdit->y  = 50;
// 	lpdit->cx = 80;
// 	lpdit->cy = 15;
// 	lpdit->id = IDOK;  // OK button identifier
// 	lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;
// 
// 	lpw = (LPWORD) (lpdit + 1);
// 	*lpw++ = 0xFFFF;
// 	*lpw++ = 0x0080;    // button class
// 
// 	lpwsz = (LPWSTR) lpw;
// 	nchar = 1+MultiByteToWideChar (CP_ACP, 0, "退出", -1, lpwsz, 50);
// 	lpw   += nchar;
// 	*lpw++ = 0;              // no creation data
// 
// 
// 	//-----------------------
// 	// Define a Help button.
// 	//-----------------------
// 	lpw = lpwAlign (lpw);
// 
// 	lpdit = (LPDLGITEMTEMPLATE) lpw;
// 	lpdit->x  = 10;
// 	lpdit->y  = 30;
// 	lpdit->cx = 80;
// 	lpdit->cy = 15;
// 	lpdit->id = ID_HELP;    // Help button identifier
// 	lpdit->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
// 
// 	lpw = (LPWORD) (lpdit + 1);
// 	*lpw++ = 0xFFFF;
// 	*lpw++ = 0x0080;                 // button class atom
// 
// 	lpwsz = (LPWSTR) lpw;
// 	nchar = 1+MultiByteToWideChar (CP_ACP, 0, "显示输入", -1, lpwsz, 50);
// 	lpw   += nchar;
// 	*lpw++ = 0;                      // no creation data
// 
// 
// 	//-----------------------
// 	// Define a EDIT.
// 	//-----------------------
// 	lpw = lpwAlign (lpw);
// 
// 	lpdit = (LPDLGITEMTEMPLATE) lpw;
// 	lpdit->x  = 10;
// 	lpdit->y  = 10;
// 	lpdit->cx = 80;
// 	lpdit->cy = 12;
// 	lpdit->id = ID_EDIT;    // Help button identifier
// 	lpdit->style = ES_LEFT | WS_BORDER | WS_TABSTOP | WS_CHILD | WS_VISIBLE;
// 
// 	lpw = (LPWORD) (lpdit + 1);
	*lpw++ = 0xFFFF;
	*lpw++ = 0x0081;                 // edit class atom
	*lpw++ = 0;                      // no creation data

	GlobalUnlock(hgbl);

	ret = DialogBoxIndirect(m_hInst,
		(LPDLGTEMPLATE) hgbl,
		m_hOwnerWnd,
		(DLGPROC) XDialogProc);

	GlobalFree(hgbl);
	return ret;
}

BOOL CXDialogBase::DoModeless(long x, long y, long cx, long cy, DWORD dwStyle)
{
	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPDLGITEMTEMPLATE lpdit;
	LPWORD lpw;
	LPWSTR lpwsz;
	int nchar;

	hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if (!hgbl)
		return FALSE;

	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

	// Define a dialog box.

	lpdt->style = dwStyle;
	lpdt->cdit = 0;  // number of controls
	lpdt->x  = x;
	lpdt->y  = y;
	lpdt->cx = cx;
	lpdt->cy = cy;

	lpw = (LPWORD) (lpdt + 1);
	*lpw++ = 0;   // no menu
	*lpw++ = 0;   // predefined dialog box class (by default)

// 	lpwsz = (LPWSTR) lpw;
// 	nchar = 1+ MultiByteToWideChar (CP_ACP, 0, "内存对话框", -1,
// 		lpwsz, 50);
// 	lpw   += nchar;

	*lpw++ = 0xFFFF;
	*lpw++ = 0x0081;                 // edit class atom
	*lpw++ = 0;                      // no creation data

	GlobalUnlock(hgbl);

	m_hDialog = CreateDialogIndirect(m_hInst,
		(LPDLGTEMPLATE) hgbl,
		m_hOwnerWnd,
		(DLGPROC) XDialogProc);
	if(NULL==m_hDialog)
		return FALSE;

	::ShowWindow(m_hDialog,SW_SHOW);

	GlobalFree(hgbl);
	return TRUE;
}

